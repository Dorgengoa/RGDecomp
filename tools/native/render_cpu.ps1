# SPDX-License-Identifier: CC0-1.0
# Process CPU time of one fixture run (docs/NATIVE-RENDER.md "Tools"): on a shared machine
# wall time swings with other load; the CPU time the process itself used (all threads:
# main + GS worker + driver threads) is a steadier measure of host work.
#   powershell -File tools/native/render_cpu.ps1 -Exe EXE -Milestone battle [-Fields 300] [-Env "A=1 B=2"]
# Prints: cpu_ms, wall_ms, cpu ms per field.  RG_RENDER defaults to native.
param([string]$Exe, [string]$Milestone = "battle", [int]$Fields = 300, [string]$Env = "", [int]$Scale = 1)
$ErrorActionPreference = "Stop"
$env:RG_RENDER = "native"; $env:RG_GPU = "hw"; $env:RG_GPU_SCALE = "$Scale"
if (-not $env:RG_DATA) { $env:RG_DATA = "data" }
foreach ($kv in ($Env -split ' ')) { if ($kv -match '^([^=]+)=(.*)$') { Set-Item -Path "env:$($Matches[1])" -Value $Matches[2] } }
$line = (& python tools\fixtures\run_from.py $Milestone --exe $Exe --no-regen --run $Fields --print 2>&1 | Select-String '^run_from: ' | Select-Object -Last 1).ToString()
$cmd = $line.Substring(10)
$parts = $cmd -split ' '
$bin = $parts[0]; $args = ($parts[1..($parts.Length - 1)] -join ' ')
$saves = [regex]::Match($cmd, '--saves (\S+)').Groups[1].Value
if ($saves) { New-Item -ItemType Directory -Force $saves | Out-Null }
$sw = [Diagnostics.Stopwatch]::StartNew()
$p = Start-Process -FilePath $bin -ArgumentList $args -NoNewWindow -PassThru -RedirectStandardError "$env:TEMP\rg_cpu_err.txt" -RedirectStandardOutput "$env:TEMP\rg_cpu_out.txt"
$h = $p.Handle
$p.WaitForExit()
$sw.Stop()
$cpu = $p.TotalProcessorTime.TotalMilliseconds
"cpu_ms {0:N0} wall_ms {1:N0} cpu_per_field {2:N2} [{3}]" -f $cpu, $sw.ElapsedMilliseconds, ($cpu / $Fields), $Env
