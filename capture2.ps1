param([int]$Seconds = 400,
      [string]$Out = "C:\Users\Timeroot\azoth\azoth_text.pcap",
      [string]$Flag = "C:\Users\Timeroot\azoth\stop.flag")
Get-Process USBPcapCMD -ErrorAction SilentlyContinue | Stop-Process -Force
Start-Sleep 1
if (Test-Path $Out)  { Remove-Item $Out  -Force }
if (Test-Path $Flag) { Remove-Item $Flag -Force }
$exe = "C:\Program Files\USBPcap\USBPcapCMD.exe"
$p = Start-Process -PassThru -FilePath $exe -ArgumentList '-d', '\\.\USBPcap2', '-A', '--inject-descriptors', '-o', $Out
Write-Host "CAPTURING all of USBPcap2 -> $Out (PID $($p.Id)). Stops on $Flag or $Seconds s."
for ($i = 0; $i -lt $Seconds; $i++) { Start-Sleep 1; if (Test-Path $Flag) { break } }
try { Stop-Process -Id $p.Id -Force } catch {}
if (Test-Path $Flag) { Remove-Item $Flag -Force }
Start-Sleep -Milliseconds 500
if (Test-Path $Out) { Write-Host "DONE: $((Get-Item $Out).Length) bytes -> $Out" } else { Write-Host "NO FILE" }
