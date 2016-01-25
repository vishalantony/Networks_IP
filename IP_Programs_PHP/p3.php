<html>
<body>
<?php
if(isset($_POST) && $_POST['greeting'] == "Enter") {
	$_POST['username'] = (empty($_POST['username']))?"Anonymous":$_POST['username'];
	$webmaster = 'vishal';
	$hour = date("H");
	$greeting = "Good Morning";
	if($hour >= 12 and $hour < 16)
		$greeting = "Good Afternoon";
	else if($hour >= 16 and $hour < 20)
		$greeting = "Good Evening";
	else if(($hour >= 20 and $hour <= 23) or ($hour >= 0 and $hour <= 3))
		$greeting = "Good Night";
?>
<h2><?php echo $greeting.' '.$_POST['username']; ?>!</h2><hr>
<p>
	Nice to see you here!<br>
	Do visit again!
	<pre>Current server time: <?php echo date("r"); ?></pre>
</p>
<?php

$output = array();
exec("who | grep $webmaster", $output);
if(empty($output)) {
	echo "<br>Webmaster $webmaster not logged in<br>";
}
else
	echo "<br>webmaster $webmaster logged in<br>";

}
else {
?>
<form action="p3.php" method="post">
<label>Enter Name:</label>
<input type="text" name="username">
<input type="submit" value="Enter" name="greeting">
</form>
<?php 
}
?>
</body>
</html>
