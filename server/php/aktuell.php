<?php
include('header.php');
include('menu.php');
?>

<?php

echo "<h2>Room:</h2>";
$sql = "SELECT temp, hum, time FROM dataRoom ORDER BY id DESC LIMIT 1";

foreach ($pdo->query($sql) as $row) {
   echo "Temperatur: ";
   echo $row['temp']. "°C". "<br />";
   echo "Luftfeuchtigkeit: ";
   echo $row['hum']."%"."<br />";
   echo "Time: ";
   echo $row['time']."<br />"."<br />";

}

echo "<h2>Room2</h2>";
$sql = "SELECT temp, hum, time FROM dataRoom2 ORDER BY id DESC LIMIT 1";

foreach ($pdo->query($sql) as $row) {
   echo "Temperatur: ";
   echo $row['temp']. "°C". "<br />";
   echo "Luftfeuchtigkeit: ";
   echo $row['hum']."%"."<br />";
   echo "Time: ";
   echo $row['time']."<br />"."<br />";

}

echo "<h2>Outside:</h2>";
$sql = "SELECT temp, hum, time FROM dataOut ORDER BY id DESC LIMIT 1";

foreach ($pdo->query($sql) as $row) {
   echo "Temperatur: ";
   echo $row['temp']. "°C". "<br />";
   echo "Luftfeuchtigkeit: ";
   echo $row['hum']."%"."<br />";
   echo "Time: ";
   echo $row['time']."<br />"."<br />";

}

?>

<?php
include('footer.php');
?>
