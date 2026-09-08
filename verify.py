import sys, pathlib
sys.path.insert(0, str(pathlib.Path(__file__).resolve().parent))
import azotholed as az

sent = []
az.send = lambda dev, data: sent.append(bytes(data))          # capture instead of write

frames, durs = az.load_gif_frames(r"C:\Users\Timeroot\azoth\azoth_test.gif")
az.upload_frames(None, frames, durs)

# sent[0],[1] = 12 03 / 12 01 ; sent[2] = start ; sent[3:-2]=data ; [-2]=end [-1]=commit
print("total sends:", len(sent))
print("mode      :", sent[0].hex(), sent[1].hex())
print("start     :", sent[2].hex()[:20])
print("pkt0      :", sent[3].hex()[:32])
print("pkt1      :", sent[4].hex()[:24])
print("end/commit:", sent[-2].hex()[:8], sent[-1].hex()[:8])
data = sent[3:-2]
print("data pkts :", len(data))
# idx (LE16) sequence: bytes 3-4 of each data packet (after report-id 02, cmd 61 02)
idx = [p[3] | (p[4] << 8) for p in data]
print("idx first8:", idx[:8])
print("idx last4 :", idx[-4:])
print("idx monotonic down by 1:", all(idx[i]-idx[i+1] == 1 for i in range(len(idx)-1)))
