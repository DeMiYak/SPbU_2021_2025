<?php
    /* function addWordToFile($wordFile, $word)
    {
        $file = fopen($wordFile, 'a');
        fwrite($file, "\n".$word);
        foreach($wordFile as $word){print "$word<br>";};
        fclose($file);
    } */


    
/*
    Function Name: fetchWordArray()
    Parameters: None
    Return values: Returns an array of characters.
*/
    function fetchWordArray($wordFile)
    {
        $file = fopen($wordFile,'r');
           if ($file)
        {
            $random_line = null;
            $line = null;
            $count = 0;
            while (($line = fgets($file)) !== false) 
            {
                $count++;
                if(rand() % $count == 0) 
                {
                      $random_line = trim($line);
                }
        }
        if (!feof($file)) 
        {
            fclose($file);
            return null;
        }else 
        {
            fclose($file);
        }
    }
        $answer = preg_split('//u', $random_line, -1, PREG_SPLIT_NO_EMPTY);
        return $answer;
    }

/*
    Function Name: hideCharacters()
    Parameters: Word whose characters are to be hidden.
    Return values: Returns a string of characters.
*/
    function hideCharacters($answer)
    {
        $noOfHiddenChars = floor((sizeof($answer)/2) + 1);
        $count = 0;
        $hidden = $answer;
        while ($count < $noOfHiddenChars )
        {
            $rand_element = rand(0,sizeof($answer)-2);
            if( $hidden[$rand_element] != '_' )
            {
                $hidden = str_replace($hidden[$rand_element],'_',$hidden,$replace_count);
                $count = $count + $replace_count;
            }
        }
        return $hidden;
    }
/*
    Function Name: checkAndReplace()
    Parameters: UserInput, Hidden string and the answer.
    Return values: Returns a character array.
*/
    function checkAndReplace($userInput, $hidden, $answer)
    {
        $i = 0;
        $wrongGuess = true;
        while($i < count($answer))
        {
            if ($answer[$i] == $userInput)
            {
                $hidden[$i] = $userInput;
                $wrongGuess = false;
            }
            $i = $i + 1;
        }
        if (!$wrongGuess) $_SESSION['attempts'] = $_SESSION['attempts'] - 1;
        return $hidden;
    }
    
    
/*
    Function Name: checkGameOver()
    Parameters: Maximum attempts, no. of attempts made by user, Hidden string and the answer.
    Return values: Returns a character array.
*/
    function checkGameOver($MAX_ATTEMPTS,$userAttempts, $answer, $hidden)
    {
        if ($userAttempts >= $MAX_ATTEMPTS)
            {
                echo "Конец игры. Правильное слово:  ";
                foreach ($answer as $letter) echo $letter;
                echo '<br><form action = "" method = "post"><input type = "submit" name' . 
                  ' = "newWord" value = "Try another Word"/></form><br>';
                die();
            }
            if ($hidden == $answer)
            {
                echo "Конец игры. Вы угадали слово:  ";
                foreach ($answer as $letter) echo $letter;
                echo '<br><form action = "" method = "post"><input ' . 
                  'type = "submit" name = "newWord" value = "Try another Word"/></form><br>';
                die();
            }
    }
?>