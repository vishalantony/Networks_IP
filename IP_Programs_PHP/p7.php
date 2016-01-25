<html>
<body>
<?php
if(isset($_POST) && $_POST['details'] == "Get Details") {
?>
<table>
	<tr><th>NAME</th><th>Author</th><th>ISBN</th></tr>
<?php
$db = mysql_connect('localhost', 'root', 'root') or die("Can't connect");
mysql_select_db("student", $db) or die("can't select db");
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
<form action="p7.php" method="post">
<label>Click to see book details:</label>
<input type="submit" value="Get Details" name="details">
</form>
<?php 
}
?>
</body>
</html>
