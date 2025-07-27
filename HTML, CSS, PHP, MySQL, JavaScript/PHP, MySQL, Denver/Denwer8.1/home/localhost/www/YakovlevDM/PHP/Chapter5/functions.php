<?php
function parseList()
{
    global $word, $wordList, $boardData;
    $itWorked = TRUE;
    /* var_dump($wordList); */
    $wordList = mb_strtoupper($wordList, "utf-8");
    /* var_dump($wordList); */
    /* print $wordList; */
    $word = preg_split("/\n/u", $wordList, -1, PREG_SPLIT_NO_EMPTY);
    
    /* var_dump($word);
    foreach ($word as $currentWord) {
        print "<table border=0 align=center>";
        print <<<TEXT
        <tr>
        <td>$currentWord</tr>
        </tr>
        TEXT;
        print '</table>';
    } */
    foreach ($word as $currentWord) {
        $currentWord = rtrim($currentWord);
        var_dump($currentWord);
        if ((strlen($currentWord)/2 > $boardData["width"]) && (strlen($currentWord)/2 > $boardData["height"])) {
            print "$currentWord - слишком длинное слово для кроссворда<br>";
            $itWorked = false;
        }

    }
    /* print "<table border=0 align=center>";
    foreach($boardData as $index => $value){
        print <<<HERE
        <tr><td>$index</td>
        <td>$value</td></tr>
        HERE;
    }
    print "</table>"; */
    /* foreach($word as $theWord)
    {
        $theWord = rtrim($theWord);
        print "$theWord: ".strlen($theWord)/2 ."<br>";
    } */
     return $itWorked;
}

function clearBoard()
{
    global $board, $boardData;
    for ($row = 0; $row < $boardData["height"]; $row++) {
        for ($col = 0; $col < $boardData["width"]; $col++) {
            $board[$row][$col] = ".";
        }
    }
}

function fillBoard()
{
    global $word;
    $direction = array("E", "W", "S", "N");
    $itWorked = true;
    $counter = 0;
    $keepGoing = true;
    while ($keepGoing) {
        $dir = rand(0, 3);
        $result = addWord($word[$counter], $direction[$dir]);
        if ($result == false) {
            $keepGoing = false;
            $itWorked = false;
        }
        $counter++;
        if ($counter >= count($word)) {
            $keepGoing = false;
        }
    }
    return $itWorked;
}

function addWord($theWord, $dir)
{
    global $board, $boardData;

    $theWord = rtrim($theWord);
/*     var_dump($theWord); */
    $wordLength = strlen($theWord)/2;/* 
    print "wordLength: $wordLength"; */
    $theWord = preg_split("//u", $theWord, -1);
    /* var_dump($theWord); */

    $itWorked = true;
    switch ($dir) {
        case "E":
            $newCol = rand(0, $boardData["width"] - 1 - $wordLength);
            $newRow = rand(0, $boardData["height"] - 1);
            for ($i = 1; $i < $wordLength+1; $i++) {
                $boardLetter = $board[$newRow][$newCol + $i - 1];
                $wordLetter = $theWord[$i];
                /* var_dump($wordLetter); */
                if (($boardLetter == $wordLetter) || ($boardLetter == ".")) {
                    $board[$newRow][$newCol + $i - 1] = $wordLetter;
                } else {
                    $itWorked = false;
                }
            }
            break;
        case "W":
            $newCol = rand($wordLength+1, $boardData["width"] - 1);
            $newRow = rand(0, $boardData["height"] - 1);
            for ($i = 1; $i < $wordLength+1; $i++) {
                $boardLetter = $board[$newRow][$newCol - $i];
                $wordLetter = $theWord[$i];
                if (($boardLetter == $wordLetter) || ($boardLetter == ".")) {
                    $board[$newRow][$newCol - $i] = $wordLetter;
                } else {
                    $itWorked = false;
                }
            }
            break;
        case "S":
            $newCol = rand(0, $boardData["width"] - 1);
            $newRow = rand(0, $boardData["height"] - 1 - $wordLength+1);
            for ($i = 1; $i < $wordLength+1; $i++) {
                $boardLetter = $board[$newRow + $i - 1][$newCol];
                $wordLetter = $theWord[$i];
                if (($boardLetter == $wordLetter) || ($boardLetter == ".")) {
                    $board[$newRow + $i - 1][$newCol] = $wordLetter;
                } else {
                    $itWorked = false;
                }
            }
            break;
        case "N":
            $newCol = rand(0, $boardData["width"] - 1);
            $newRow = rand($wordLength+1, $boardData["height"] - 1);
            for ($i = 1; $i < $wordLength+1; $i++) {
                $boardLetter = $board[$newRow - $i][$newCol];
                $wordLetter = $theWord[$i];
                if (($boardLetter == $wordLetter) || ($boardLetter == ".")) {
                    $board[$newRow - $i][$newCol] = $wordLetter;
                } else {
                    $itWorked = false;
                }
            }
            break;
    }
    return $itWorked;
}

function makeBoard($theBoard)
{
    global $boardData;
    $puzzle = "<table border=0 align=center>";

    for ($row = 0; $row < $boardData["height"]; $row++) {
        $puzzle .= "<tr>";
        for ($col = 0; $col < $boardData["width"]; $col++) {
            $puzzle .= "<td width=15>" . $theBoard[$row][$col] . "</td>";
        }
        $puzzle .= "</tr>\n";
    }
    $puzzle .= "</table>";
    return $puzzle;
}

function addFoils()
{ // Заполняет поле случайными буквами
    global $board, $boardData;
    for ($row = 0; $row < $boardData["height"]; $row++) {
        for ($col = 0; $col < $boardData["width"]; $col++) {
            if ($board[$row][$col] == ".") {
                $newLetter = rand(192, 223);
                $cyrillic = iconv("windows-1251//IGNORE", "UTF-8//IGNORE", chr($newLetter));
                $board[$row][$col] = $cyrillic;
            }
        }
    }
}

function printPuzzle()
{ // Печатает кроссворд
    global $puzzle, $word, $keyPuzzle, $boardData;
    print "<h1>" . $boardData["name"] . "</h1>";
    print <<<TEXT
    <center>
    $puzzle
    <h3>Список слов</h3>
    <table border=0>
    TEXT;
    foreach ($word as $theWord) {
        print "<tr><td>$theWord</td></tr>\n";
    }
    print "</table></center>\n";
    $puzzleName = $boardData["name"];
    print <<<HERE
    <br><br><br><br><br><br><br><br>
    <form action="wordHuntKey.php"
    method="post">
    <input type=hidden name=key
    value=$keyPuzzle>
    <input type=hidden name=puzzleName
    value=$puzzleName>
    <input type=submit value="Показать ключ ответов">
    </form>
    HERE;
}
?>