<!doctype html>
<html lang=ru>

<head>
    <title>Глава 5: Улучшенная обработка массивов и строк</title>
    <link rel=stylesheet href=Chapter5.css>
</head>

<body>
    <p>Создатель кроссвордов</p>
    <form action="wordHunt.php" method="post">
        <p>Название кроссворда</p>
        <input type=text name='name'>
        <br>
        Высота: <input type=text name=height value=10 size=6>
        <br>
        Ширина: <input type=text name=width value=10 size=6>
        <hr class=short>
        <hr class=wide>
        <hr class=short>
        <p>Список слов</p>
        <textarea rows=10 cols=60 name=wordList></textarea>
        <br><br>
        Пожалуйста, вводите только одно слово в каждой строке, без пробелов
        <br>
        <input type=submit value="Создать кроссворд" />
    </form>
</body>

</html>