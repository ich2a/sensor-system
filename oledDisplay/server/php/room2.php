<?php
include('header.php');
include('menu.php');
?>

<?php

echo "<h1>data Room2:</h1>";

$sql = "SELECT ROUND(AVG(temp),2) AS avg FROM dataRoom2 ORDER BY id DESC LIMIT 5";
foreach ($pdo->query($sql) as $row) {
   echo "Durchschnitt Temperatur last 10h: "; 
   echo $row['avg']."°C";
   echo "<br />"."<br />";
}

$sql = "SELECT ROUND(AVG(hum),2) AS avg FROM dataRoom2 ORDER BY id DESC LIMIT 5";
foreach ($pdo->query($sql) as $row) {
   echo "Durchschnitt Luftfeuchtigkeit last 10h: "; 
   echo $row['avg']."%";
   echo "<br />"."<br />";
}

$sql = "SELECT temp, hum, time FROM dataRoom2 ORDER BY id DESC LIMIT 3";

foreach ($pdo->query($sql) as $row) {
   echo "Temperatur: ";
   echo $row['temp']."<br />";
   echo "Luftfeuchtigkeit: ";
   echo $row['hum']."%"."<br />";
   echo "Time: ";
   echo $row['time']."<br />"."<br />";

}

?>

<?php
include('footer.php');
?>
