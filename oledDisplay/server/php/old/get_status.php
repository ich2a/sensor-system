<?php
	$pdo = new PDO('mysql:host=localhost;dbname=DB', 'root', 'Anne');
	$id = $_GET['id'];
	if($id==5){
		$sql = "SELECT temp, hum, time FROM dataRoom ORDER BY id DESC LIMIT 1";
		foreach ($pdo->query($sql) as $row) {
		echo $row['temp'];
		}	
	}else{
		echo "error";
	}
 



?>
