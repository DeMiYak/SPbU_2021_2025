<!doctype html>
<html lang="ru">

<head>
    <title>Игрок 1</title>
    <link rel="stylesheet" href="Chapter4.css">
</head>

<body> 
    <table width="100%" height="100%">
    <tr><td align="center">
    <form method="post" action="player1.php">
    <?php  
        extract($_POST);
       if($comp == "Начать игру с компьютером"){
            $singlePlayerMode = 1;
            print "Вы начали игру с компьютером <br>";
        }else{
            $singlePlayerMode = 0;
            print "Вы начали игру вдвоём <br>";
        }
        print <<<DD
        leftE $leftE <br>
        rightE $rightE <br>
        comp $comp <br>
        singlePlayerMode $singlePlayerMode <br>
        DD;
        $singlePlayerMode;
        $attempt = 0;
        if($leftE >= $rightE)
        {
            print "Ошибка: неправильные границы.";
        } else{
            print "Угадайте число от $leftE до $rightE";
        }

        function Turns()
        {
            if($exitTurns){$exitTurns = false;};
            while(!$exitTurns)
            {
                playerGuess();
                compGuess();
            }
        }

        function playerGuess()
        {
            global $exitTurns;
            print "<br><br>Попробуйте отгадать число, заданное компьютером";
            $compGenerated = rand(0, 100);

        }
        $exitTurns = false;

    ?>
    <br><br>Введите число в диапазоне от <?php print "$leftE до $rightE" ?>: <input type="text" name="number" size="16"></input>
    <br>Число попыток: <?php print "$attempt"?> 
    <br><br><hr class="short"><hr class="wide"><hr class="short"><br>
    <input type="submit" value="Подтвердить выбор"></input>
    </form>
    </td></th>
    </table>
</body>

</html>