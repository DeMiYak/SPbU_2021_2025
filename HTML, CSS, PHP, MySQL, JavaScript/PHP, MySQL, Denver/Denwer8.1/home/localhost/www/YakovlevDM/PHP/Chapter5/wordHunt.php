<!doctype html>
<html lang=ru>

<head>
    <title>Кроссворд</title>
    <link rel=stylesheet href=Chapter5.css>
</head>

<body>

    <?php

    include("functions.php");

    extract($_REQUEST);
    extract($_POST);

    if ($wordList == NULL) {
        $word = array(
            "ДОМ",
            "ШИМПАНЗЕ",
            "ЯНТАРЬ",
            "СОЛОНИНА",
            "ГИРЛЯНДА"
        );
        $boardData = array(
            "width" => 10,
            "height" => 10,
            "name" => "Шаблонный кроссворд",
        );
    } else {
        $boardData = array(
            "width" => $width,
            "height" => $height,
            "name" => $name,
        );
        if (parseList()) {
            $legalBoard = false;
            while (!$legalBoard) {
                clearBoard();
                $legalBoard = fillBoard();
            }
            $key = $board;
            // var_dump($key);
            $keyPuzzle = makeBoard($key);

            addFoils();
            $puzzle = makeBoard($board);

            printPuzzle();
        }
    }
    ?>
</body>

</html>