"""Interactive packet sender for the ROG Azoth OLED.

Keeps the vendor HID interface open and lets you fire arbitrary reports so you
can poke at the protocol by hand and watch the panel react.

Every OLED report on the wire is:  [report-id] + up-to-64 data bytes, padded to
65.  The report id is 0x02 for all known OLED commands; the "payload" you type is
everything after it (i.e. what tshark showed as usbhid.data, starting with the
command byte like 0x66).

  python azoth_gui.py
"""
import sys, time, pathlib
import tkinter as tk
from tkinter import ttk

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import azotholed as az
from PIL import Image

REPORT_LEN = 65


def parse_hex(s):
    h = "".join(c for c in s.lower() if c in "0123456789abcdef")
    if len(h) % 2:
        raise ValueError("odd number of hex digits")
    return bytes.fromhex(h)


class App:
    def __init__(self, root):
        self.root = root
        root.title("Azoth OLED packet sender")
        self.dev = None

        top = ttk.Frame(root, padding=8); top.pack(fill="x")
        self.status = ttk.Label(top, text="not connected")
        self.status.pack(side="left")
        ttk.Button(top, text="Reconnect", command=self.connect).pack(side="right")

        # ---- raw report -------------------------------------------------
        raw = ttk.LabelFrame(root, text="Raw report", padding=8); raw.pack(fill="x", padx=8, pady=4)
        ttk.Label(raw, text="report id").grid(row=0, column=0, sticky="w")
        self.rid = ttk.Entry(raw, width=5); self.rid.insert(0, "02"); self.rid.grid(row=0, column=1, sticky="w")
        ttk.Label(raw, text="payload (hex, after report id)").grid(row=0, column=2, sticky="w", padx=(12, 0))
        self.payload = ttk.Entry(raw, width=70); self.payload.grid(row=1, column=0, columnspan=4, sticky="we", pady=3)
        self.payload.insert(0, "66 00 01 00 00 ff 05 00 01 ff 40")
        ttk.Button(raw, text="Send", command=self.send_raw).grid(row=2, column=0, sticky="w")
        ttk.Label(raw, text="(padded to 64 data bytes automatically)").grid(row=2, column=1, columnspan=3, sticky="w")

        # ---- sysinfo widgets -------------------------------------------
        si = ttk.LabelFrame(root, text="System-info values (0x66 CPU screen / 0x64 battery)", padding=8)
        si.pack(fill="x", padx=8, pady=4)
        self.v1 = tk.IntVar(value=50); self.v2 = tk.IntVar(value=60); self.bat = tk.IntVar(value=80)
        ttk.Label(si, text="cpu%").grid(row=0, column=0)
        ttk.Scale(si, from_=0, to=255, variable=self.v1, command=lambda e: self.send_66()).grid(row=0, column=1, sticky="we")
        ttk.Label(si, textvariable=self.v1, width=4).grid(row=0, column=2)
        ttk.Label(si, text="temp").grid(row=1, column=0)
        ttk.Scale(si, from_=0, to=255, variable=self.v2, command=lambda e: self.send_66()).grid(row=1, column=1, sticky="we")
        ttk.Label(si, textvariable=self.v2, width=4).grid(row=1, column=2)
        ttk.Button(si, text="send 0x66", command=self.send_66).grid(row=0, column=3, rowspan=2, padx=6)
        ttk.Label(si, text="batt%").grid(row=2, column=0)
        ttk.Scale(si, from_=0, to=255, variable=self.bat, command=lambda e: self.send_64()).grid(row=2, column=1, sticky="we")
        ttk.Label(si, textvariable=self.bat, width=4).grid(row=2, column=2)
        ttk.Button(si, text="send 0x64", command=self.send_64).grid(row=2, column=3, padx=6)
        si.columnconfigure(1, weight=1)

        # ---- presets ----------------------------------------------------
        pr = ttk.LabelFrame(root, text="Presets", padding=8); pr.pack(fill="x", padx=8, pady=4)
        presets = [
            ("picture mode 12 03", "12 03"),
            ("picture mode 12 01", "12 01"),
            ("music mode 12 12", "12 12"),
            ("image start 61 01..71", "61 01 00 00 00 71"),
            ("image end 61 03", "61 03"),
            ("commit 50 55", "50 55"),
            ("time 63..", "63 00 00 00 00 00 ea 07 09 07 0c 00 00"),
        ]
        for i, (label, hexs) in enumerate(presets):
            ttk.Button(pr, text=label, command=lambda h=hexs: self.fill_and_send(h)
                       ).grid(row=i // 3, column=i % 3, sticky="we", padx=2, pady=2)
        for c in range(3): pr.columnconfigure(c, weight=1)

        # ---- full-frame helpers ----------------------------------------
        ff = ttk.LabelFrame(root, text="Full frame (uses 0x61 upload - will blank/redraw)", padding=8)
        ff.pack(fill="x", padx=8, pady=4)
        ttk.Button(ff, text="white", command=lambda: self.image(255)).pack(side="left", padx=2)
        ttk.Button(ff, text="black", command=lambda: self.image(0)).pack(side="left", padx=2)
        ttk.Button(ff, text="grey", command=lambda: self.image(128)).pack(side="left", padx=2)
        self.txt = ttk.Entry(ff, width=20); self.txt.insert(0, "HELLO"); self.txt.pack(side="left", padx=(12, 2))
        ttk.Button(ff, text="text", command=self.text).pack(side="left", padx=2)

        # ---- log --------------------------------------------------------
        self.log = tk.Text(root, height=12, width=90, font=("Consolas", 9))
        self.log.pack(fill="both", expand=True, padx=8, pady=4)

        self.connect()

    def logline(self, s):
        self.log.insert("end", s + "\n"); self.log.see("end")

    def connect(self):
        try:
            if self.dev:
                try: self.dev.close()
                except Exception: pass
            self.dev = az.open_oled()
            self.status.config(text="connected to Azoth OLED (report id 0x02)")
            self.logline("[connected]")
        except Exception as e:
            self.status.config(text=f"connect failed: {e}")
            self.dev = None

    def _send(self, rid, payload):
        if not self.dev:
            self.logline("! not connected"); return
        data = bytes([rid]) + bytes(payload)
        buf = data[:REPORT_LEN] + bytes(max(0, REPORT_LEN - len(data)))
        try:
            n = self.dev.write(buf)
            shown = " ".join(f"{b:02x}" for b in buf[:1 + min(len(payload), 20)])
            self.logline(f"-> id={rid:02x} [{ ' '.join(f'{b:02x}' for b in payload[:20]) }]"
                         f"{' ...' if len(payload) > 20 else ''}  (write={n})")
        except Exception as e:
            self.logline(f"! write error: {e}")

    def send_raw(self):
        try:
            rid = parse_hex(self.rid.get())[0]
            payload = parse_hex(self.payload.get())
        except Exception as e:
            self.logline(f"! bad hex: {e}"); return
        self._send(rid, payload)

    def fill_and_send(self, hexs):
        self.payload.delete(0, "end"); self.payload.insert(0, hexs)
        self.send_raw()

    def send_66(self):
        self._send(0x02, bytes([0x66, 0x00, 0x01, 0x00, 0x00, 0xFF,
                                self.v1.get() & 0xFF, 0x00, 0x01, 0xFF, self.v2.get() & 0xFF]))

    def send_64(self):
        self._send(0x02, bytes([0x64, 0x00, 0x00, 0x00, self.bat.get() & 0xFF]))

    def image(self, level):
        if not self.dev: return
        az.show(self.dev, az.pack_fast(Image.new("L", (az.OLED_W, az.OLED_H), level)))
        self.logline(f"[full image level={level}]")

    def text(self):
        if not self.dev: return
        az.show(self.dev, az.pack_fast(az.text_frame([self.txt.get()])))
        self.logline(f"[text '{self.txt.get()}']")


if __name__ == "__main__":
    root = tk.Tk()
    App(root)
    root.mainloop()
