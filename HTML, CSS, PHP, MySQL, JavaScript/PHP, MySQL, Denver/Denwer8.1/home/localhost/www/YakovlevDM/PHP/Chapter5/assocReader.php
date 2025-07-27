<!doctype html>
<html>

<head>
    <link rel='stylesheet' href='Chapter5.css'>
</head>

<body>
    <?php
print <<<TEXT
<center>
<table border=1 cellpadding=3 cellspacing=4>
<tr>
<th>Индекс</th>
<th>Значение</th>
</tr>
TEXT;
foreach($_REQUEST as $index => $value)
{
    print <<<TEXT
    <tr>
    <td>$index</td>
    <td>$value</td>
    </tr>
    TEXT;
}
print '</table></center>';
?>
</body>

</html>