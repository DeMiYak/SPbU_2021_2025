<!doctype html>
<html lang='ru'>

<head>
    <title>Глава 4: Циклы и массивы. Покер и кости</title>
    <link rel="stylesheet" href="Chapter4.css">
</head>

<body>
    Игра "Угадай число друга".
    <br>
    Отгадайте загаданное число друга в указанном диапазоне целых чисел.
    <br>
    <form method="post" action="player1.php">
    <table width="100%" height="50%">
        <tr><td align="center">
        Введите левую границу: <input type="text" name="leftE" size="6" value="0"></input><br>
        Введите правую границу: <input type="text" name="rightE" size="6" value ="100"></input> 
             </td></tr>
</table>
<input type="submit" name="comp" value="Начать игру с компьютером"></input><input type="submit" name="comp" value="Начать игру с игроком"></input>
</form>
</form>
</body>

</html>