<?php
	$pdo = new PDO('mysql:host=localhost;dbname=DB', 'root', 'Anne');
	$info = $_GET['info'];
	$location = "data". $_GET['location'];
	
	
	if($info == 'temp'){
		$sql = "SELECT temp FROM $location ORDER BY id DESC LIMIT 1";
		foreach ($pdo->query($sql) as $row) {
		echo $row['temp'];
		}
	}else if($info == 'hum'){
		$sql = "SELECT hum, time FROM $location ORDER BY id DESC LIMIT 1";
		foreach ($pdo->query($sql) as $row) {
		echo $row['hum'];
		}	
	}else{
		echo "error";
	}
 



?>
