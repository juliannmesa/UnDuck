$proceed = $false
$PortName = "COM8"
foreach ($item in [System.IO.Ports.SerialPort]::GetPortNames())
	{
		if ($item -eq $PortName)
		{
			$proceed = $true
			Write-Output ("Port " + $PortName + " is available, connecting!")
			break
		}
	}
if(!$proceed) {
	Throw
}
[System.IO.Ports.SerialPort]$port = New-Object System.IO.Ports.SerialPort
$port.PortName = $PortName
$port.BaudRate = 9600
try{$port.Open()} catch {echo("The port is unable to be opened, exiting!");exit(1)}
$port.WriteLine("09*_STATUS*_ONLINE")
while ($port.IsOpen) {
    $line = $port.ReadLine()
    if($line -ne $null) {
        $direction,$channel,$message = $line.split("*_").split("*_")
        $direction = [String]$direction
        $channel = [String]$channel
        $message = [String]$message
    	$directionArray = ($direction.ToCharArray() | %{[char]$_})
        $sender = $directionArray[0]
        $reciever = $directionArray[1]
    	if(($reciever -eq ([char]'0')) -and ($reciever -ne([char]'9'))) {
            echo $channel
    		if($channel -eq "COMMAND") {
	    		Invoke-Expression($message) -ErrorAction SilentlyContinue -ErrorVariable $err -OutVariable $response
	    		$port.WriteLine($response)
	    	}
	    } else {
            $port.WriteLine($line)
        }
        if($line -eq "CLOSE") {$port.Close(); exit}
    }
}