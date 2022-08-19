<?php
include('header.php');
include('menu.php');
?>

<html>

<h1>Offsets</h1>


</html>

<?php

$sql = "SELECT location, temp, hum, press FROM offsets";
		foreach ($pdo->query($sql) as $row) {
			echo "<h2>". "Location: ". $row['location']. "</h2>";
			echo "temperature: ". $row['temp']. "<br>";
			echo "humidity: ". $row['hum']. "<br>";
			echo "pressure: ". $row['press'];
			echo "<br>". "<br>";

		}

?>

<html>

<h1>Change</h1>

<form action="offsets.php" method="POST">

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
    <td><span class="formhead">Offset:</span></td>
    <td><input class="form" type="number" step="0.01" name="offset" /><br /></td>

  </tr>
<br />
<input class="submit" type="submit" name="formSubmit" value="Submit" />

</form>

</html>

<?php

if ((isset($_POST['location'])) and (isset($_POST['info'])) and (isset($_POST['offset']))){
	$location = $_POST['location'];
	foreach ($location as $locationList){
    //echo $locationList;	
	}
	
	$info = $_POST['info'];
	foreach ($info as $infoList){
    //echo $infoList;
	}
    
    $offset = $_POST['offset'];
    //echo $offset;
    //echo $stunden;
    $floatOffset = floatval($offset);
    //echo gettype($intStunden);
    
	//echo gettype($floatOffset);




    
    //echo "InfoList: ". $infoList. " locationList: ". $locationList
    
    $statement = $pdo->prepare("UPDATE offsets SET $infoList = $floatOffset WHERE location = '$locationList'");
    $statement->execute();
    
    header("Refresh:0");

}
	
?>


<?php
include('footer.php');
?>
