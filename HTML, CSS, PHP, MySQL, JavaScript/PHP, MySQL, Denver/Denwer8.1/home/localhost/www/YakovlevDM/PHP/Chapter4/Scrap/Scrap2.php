<form method="post" action="player2.php">
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
        $attempt = 1;
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