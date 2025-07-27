<!doctype html>
<html>

<head>
    <title>Ключи к кроссворду</title>
    <link rel=stylesheet href=Chapter5.css>
</head>

<body>
    <?php
    extract($_REQUEST);
    extract($_POST);

    print <<<HERE
    <h1>$puzzleName. Ключи к кроссворду</h1>
    $key
    HERE;
    ?>

    <?php
    print <<<TEXT
    <table border=1 cellpadding=3 cellspacing=4 align=center>
    <tr>
    <th>Индекс</th>
    <th>Значение</th>
    </tr>
    TEXT;
    foreach ($_REQUEST as $index => $value) {
        print <<<TEXT
    <tr>
    <td>$index</td>
    <td>$value</td>
    </tr>
    TEXT;
    }
    print '</table>';
    ?>
</body>

</html>