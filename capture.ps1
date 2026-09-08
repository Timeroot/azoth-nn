param([int]$Seconds = 90, [string]$Out = "C:\Users\Timeroot\azoth\azoth_gif.pcap")
$exe = "C:\Program Files\USBPcap\USBPcapCMD.exe"
if (Test-Path $Out) { Remove-Item $Out -Force }
# Capture only the keyboard (device tree [1]) on hub USBPcap2, straight to pcap.
$p = Start-Process -PassThru -FilePath $exe `
     -ArgumentList '-d', '\\.\USBPcap2', '--devices', '1', '-o', $Out
Write-Host "CAPTURING to $Out for $Seconds s (PID $($p.Id)) - do the GIF upload now..."
Start-Sleep -Seconds $Seconds
try { Stop-Process -Id $p.Id -Force } catch {}
Start-Sleep -Milliseconds 500
if (Test-Path $Out) { Write-Host "DONE: $((Get-Item $Out).Length) bytes -> $Out" }
else { Write-Host "NO FILE WRITTEN - capture failed" }
