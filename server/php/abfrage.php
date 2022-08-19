<?php
include('header.php');
include('menu.php');
?>

<html>

<body>

<h1>Abfrage</h1>


<form action="abfrage.php" method="POST">

<span class="formhead">Ort:</span>
<br />
<input type="checkbox" name="location[]" id ="location" value="Room" />Room<br />
<input type="checkbox" name="location[]" id ="location" value="Room2" />Room2<br />
<input type="checkbox" name="location[]" id ="location" value="Out" />Outside<br />
<br />
<span class="formhead">Info:</span>
<br />
<input type="checkbox" name="info[]" id ="info" value = "temp" />Temperature<br />
<input type="checkbox" name="info[]" id ="info" value = "hum" />Humidity<br />
<input type="checkbox" name="info[]" id ="info" value = "press" />Pressure
<br /><br />
  <tr>
    <td><span class="formhead">vor ? Stunden:</span></td>
    <td><input class="form" type="number" name="stunden" /><br /></td>
    <p>keine Stunden Eingabe gibt letzten Eintrag zurück</p>
  </tr>
<br />
<input class="submit" type="submit" name="formSubmit" value="Submit" />

</form>


<?php

if ((isset($_POST['location'])) and (isset($_POST['info'])) and (isset($_POST['stunden']))){
	$location = $_POST['location'];
	foreach ($location as $locationList){
    //echo $locationList;	
	}
	
	$info = $_POST['info'];
	foreach ($info as $infoList){
    //echo $infoList;
	}
    
    $stunden = $_POST['stunden'];
    //echo $stunden;
    $intStunden = (int) $stunden;
    //echo gettype($intStunden);
    
    $locationPlace = $locationList;
    $locationList = "data". $locationList;
    
    //echo $infoList. " ". $locationList;
    echo "<br>";
    echo "<br>";
    echo $infoList. " ". $locationPlace;

    
    //echo "InfoList: ". $infoList. " locationList: ". $locationList;
    
	try{
		$sql = "SELECT $infoList FROM $locationList ORDER BY id DESC LIMIT $intStunden, 1";
		foreach ($pdo->query($sql) as $row) {
			echo"</br>";
			echo "<h1> $row[$infoList]";
		}
		if ($infoList == "temp"){
				echo "°C</h1>";
		}else if($infoList == "hum"){
			echo "%</h1>";
		}else if($infoList == "press"){
			echo "bar</h1>";
		}
    
		
		$sql = "SELECT time FROM $locationList ORDER BY id DESC LIMIT $intStunden, 1";
		foreach ($pdo->query($sql) as $row) {
			echo "<h3>$row[time]</h3>";
		}
	}catch (Exception $e) {
		echo"</br>";
		echo"Eintrag existiert nicht";
	}
}
	
?>

<?php
include('footer.php');
?>
