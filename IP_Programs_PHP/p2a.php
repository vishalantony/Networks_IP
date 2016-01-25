<html>
<body>
<?php
if(isset($_POST) && $_POST['greeting'] == "Enter") {
	$_POST['username'] = (empty($_POST['username']))?"Anonymous":$_POST['username'];
?>
<h2>Greetings <?php echo $_POST['username']; ?>!</h2><hr>
<p>
	Nice to see you here!<br>
	Do visit again!
	<pre>Current server time: <?php echo date("r"); ?></pre>
</p>
<?php
}
else {
?>
<form action="p2a.php" method="post">
<label>Enter Name:</label>
<input type="text" name="username">
<input type="submit" value="Enter" name="greeting">
</form>
<?php 
}
?>
</body>
</html>
