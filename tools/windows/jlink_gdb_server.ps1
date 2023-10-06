param ($sn, $dev, [Int32]$port=2331, $endianess='little', $interface='swd')

$swo_port = $port+1
$telnet_port = $port+2
$jlink_command = "JLinkGDBServerCL.exe -select USB=$sn -device $dev -endian $endianess -if $interface -speed auto -noir -LocalhostOnly -nologtofile -port $port -SWOPort $swo_port -TelnetPort $telnet_port"

Start-Process powershell -ArgumentList "-Command $jlink_command"
