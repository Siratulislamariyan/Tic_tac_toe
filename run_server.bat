@echo off
REM Simple HTTP server for Windows using PowerShell
powershell -NoProfile -Command ^
  "$listener = New-Object System.Net.HttpListener; " ^
  "$listener.Prefixes.Add('http://localhost:8000/'); " ^
  "$listener.Start(); " ^
  "Write-Host 'Server running at http://localhost:8000/'; " ^
  "Write-Host 'Press Ctrl+C to stop'; " ^
  "while ($listener.IsListening) { " ^
  "  $context = $listener.GetContext(); " ^
  "  $request = $context.Request; " ^
  "  $response = $context.Response; " ^
  "  $path = [IO.Path]::Combine((Get-Location), $request.Url.LocalPath.TrimStart('/')); " ^
  "  if ($path -eq (Get-Location).Path -or $request.Url.LocalPath -eq '/') { $path = [IO.Path]::Combine((Get-Location), 'index.html') } " ^
  "  if ([IO.File]::Exists($path)) { " ^
  "    $bytes = [IO.File]::ReadAllBytes($path); " ^
  "    if ($path -match '.wasm$') { $response.ContentType = 'application/wasm' } " ^
  "    elseif ($path -match '.js$') { $response.ContentType = 'text/javascript' } " ^
  "    elseif ($path -match '.css$') { $response.ContentType = 'text/css' } " ^
  "    else { $response.ContentType = 'text/html' } " ^
  "    $response.OutputStream.Write($bytes, 0, $bytes.Length); " ^
  "  } else { " ^
  "    $response.StatusCode = 404; " ^
  "    $response.StatusDescription = 'Not Found'; " ^
  "    [byte[]]$buf = [System.Text.Encoding]::UTF8.GetBytes('404 Not Found'); " ^
  "    $response.OutputStream.Write($buf, 0, $buf.Length); " ^
  "  } " ^
  "  $response.Close(); " ^
  "}"
