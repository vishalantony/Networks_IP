<html>
<body>
<?php
if(isset($_POST) && $_POST['search'] == "Search") {
?>
<table>
	<tr><th>NAME</th><th>Author</th><th>ISBN</th></tr>
<?php
$db = mysql_connect('localhost', 'root', 'root') or die();
mysql_select_db('student', $db) or die();
$query = 'SELECT * from book where name like "%'.mysql_real_escape_string($_POST['name'], $db).'%";';
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
<form action="p9.php" method="post">
<P>Search book:</P>

<label>title:</label><input type="text" name="name"><br>
<input type="submit" value="Search" name="search">
</form>
<?php 
}
?>
</body>
</html>
