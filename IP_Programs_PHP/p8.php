<html>
<body>
<?php
if(isset($_POST) && $_POST['insert'] == "Insert") {
?>
<table>
	<tr><th>NAME</th><th>Author</th><th>ISBN</th></tr>
<?php
$db = mysql_connect('localhost', 'root', 'root') or die();
mysql_select_db('student', $db) or die();
$query = 'insert into book values ("'.mysql_real_escape_string($_POST['name'], $db).'", 
"'.mysql_real_escape_string($_POST['author'], $db).'", '.mysql_real_escape_string($_POST['isbn'], $db).');';	
mysql_query($query, $db) or die();
$query = 'SELECT * from book;';
$result = mysql_query($query, $db) or die("Can't select");
while($row = mysql_fetch_assoc($result)) {
	echo '<tr>';
	echo '<td>'.$row['name'].'</td>';
	echo '<td>'.$row['author'].'</td>';
	echo '<td>'.$row['ISBN'].'</td>';
	echo '</tr>'."\n";
}
echo '</table>';
}
else {
?>
<form action="p8.php" method="post">
<P>Enter book details:</P>

<label>Name:</label><input type="text" name="name"><br>
<label>author:</label><input type="text" name="author"><br>
<label>ISBN:</label><input type="text" name="isbn"><br>
<input type="submit" value="Insert" name="insert">
</form>
<?php 
}
?>
</body>
</html>
