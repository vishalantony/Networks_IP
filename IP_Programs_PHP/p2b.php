<html>
<body>
<?php

if(isset($_POST) && $_POST['acc'] == "click") {
	$myfile = fopen('faccess', "r") or die("1. cannot open file");
fscanf($myfile, "%d", $access);
fclose($myfile);
$access++;
$myfile = fopen('faccess', "w") or die("2. cannot open file");
fprintf($myfile, "%d", $access);
fclose($myfile);
?>
<h2>Hello!</h2><hr>
<p>
	This page has been accessed <?php echo $access;?> times.
</p>
<?php
}
else {
?>
<form action="p2b.php" method="post">
<label>Number of accesses:</label>
<input type="submit" value="click" name="acc">
</form>
<?php 
}
?>
</body>
</html>
