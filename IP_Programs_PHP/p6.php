<html>
<body>
<?php
if(isset($_POST) && $_POST['insert'] == "Insert") {
?>
<table>
	<tr><th>NAME</th><th>REGISTER NUMBER</th></tr>
<?php
$db = mysql_connect('localhost', 'root', 'root') or die();
mysql_select_db('student', $db) or die();
$query = 'insert into students values ("'.mysql_real_escape_string($_POST['name'], $db).'", 
"'.mysql_real_escape_string($_POST['regno'], $db).'");';	
mysql_query($query, $db) or die();
$query = 'SELECT * from students;';
$result = mysql_query($query, $db) or die("Can't select");
while($row = mysql_fetch_assoc($result)) {
	echo '<tr>';
	echo '<td>'.$row['name'].'</td>';
	echo '<td>'.$row['ID'].'</td>';
	echo '</tr>'."\n";
}
echo '</table>';
}
else {
?>
<form action="p6.php" method="post">
<P>Enter student details:</P>

<label>Name:</label><input type="text" name="name"><br>
<label>Reg No:</label><input type="text" name="regno"><br>
<input type="submit" value="Insert" name="insert">
</form>
<?php 
}
?>
</body>
</html>
