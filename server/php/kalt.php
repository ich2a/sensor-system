<?php
include('header.php');
include('menu.php');
?>

<h1>Wegweiser</h1>


<?php

$sql = "SELECT temp FROM dataRoom ORDER BY id DESC LIMIT 1";

foreach ($pdo->query($sql) as $row) {
   //echo "Temperatur Room:  ";
   $tempRoom = floatval($row['temp']);
   //echo $row['temp']."°C"."<br />";
   
}

$sql = "SELECT temp FROM dataRoom2 ORDER BY id DESC LIMIT 1";

foreach ($pdo->query($sql) as $row) {
   //echo "Temperatur Room2: ";
   $tempRoom2 = floatval($row['temp']);
   //echo $row['temp']."°C"."<br />";
   
}


$sql = "SELECT temp FROM dataOut ORDER BY id DESC LIMIT 1";

foreach ($pdo->query($sql) as $row) {
   //echo "Temperatur Out: ";
   $tempOut = floatval($row['temp']);
   //echo $row['temp']."°C"."<br />"."<br />";
   
}

if($tempRoom > $tempRoom2 && $tempRoom > $tempOut){
   $amWärmsten = 'Room';
   $maxTemp = $tempRoom;
}else if($tempRoom2 > $tempRoom && $tempRoom2 > $tempOut){
   $amWärmsten = 'Room2';
   $maxTemp = $tempRoom2;
}else if ($tempOut > $tempRoom && $tempOut > $tempRoom2){
   $amWärmsten = 'Out';
   $maxTemp = $tempOut;
}

echo "gehe nach ". $amWärmsten. " dort ist es mit ". $maxTemp. "°C am wärmsten";
echo "<br />"."<br />";



?>




<?php
include('footer.php');
?>

