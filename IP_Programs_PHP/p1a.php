<html>
<body>
<?php
if(isset($_POST) && $_POST['server'] == "Server info") {
?>
<h3>Server Information:</h3>
<hr>
<?php
	foreach($_SERVER as $key => $value) {
		echo '$_SERVER['.$key.']: '.$_SERVER[$key].'<br>';
	}
}
else {
?>
<form action="p1a.php" method="post">
<label>Click here to view server details:</label>
<input type="submit" value="Server info" name="server">
</form>
<?php 
}
?>
</body>
</html>
