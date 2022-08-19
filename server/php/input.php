<?php

$pdo = new PDO('mysql:host=localhost;dbname=DB', 'root', 'Anne');

$location = $_GET["location"];
$tableName = "data". $location; 
$sensor = $_GET["sensor"];

$sql = "SELECT temp, hum, press FROM offsets WHERE location = '$location'";
foreach ($pdo->query($sql) as $row) {
   $tempOff = $row['temp'];
   $humOff = $row['hum'];
   $pressOff = $row['press'];

}

if ($sensor == "DHT11"){
   $temp = $_GET["temp"];
   $hum = $_GET["hum"];
   $temp = $temp + $tempOff;
   $hum = $hum + $humOff;
   $statement = $pdo->prepare("INSERT INTO $tableName (temp, hum) VALUES ($temp, $hum)");
   $statement->execute();
} else if ($sensor == "ENV3"){
   $temp = $_GET["temp"];
   $hum = $_GET["hum"];
   $press = $_GET["press"];
   $temp = $temp + $tempOff;
   $hum = $hum + $humOff;
   $press = $hum + $humOff;
   $statement = $pdo->prepare("INSERT INTO $tableName (temp, hum, press) VALUES ($temp, $hum, $press)");
   $statement->execute();
}   


?>
