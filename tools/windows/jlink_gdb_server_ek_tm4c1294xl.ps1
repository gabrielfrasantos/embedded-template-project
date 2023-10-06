$ek_tm4c1294xl_board = "$pwd\jlink_gdb_server.ps1 -sn $env:EK_TM4C1294XL_JLINK_SN -dev $env:EK_TM4C1294XL_DEVICE -port $env:EK_TM4C1294XL_PORT"

powershell $ek_tm4c1294xl_board
