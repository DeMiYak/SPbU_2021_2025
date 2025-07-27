<?php session_start();?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html lang="ru" xmlns="http://www.w3.org/1999/xhtml">
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Hangman</title>
<link rel="stylesheet" href="Chapter4.css">
</head>

<body>
<?php

    include 'Chapter4Config.php';

    include 'Chapter4Functions.php';

    if (isset($_POST['newWord'])) unset($_SESSION['answer']);

    if (!isset($_SESSION['answer']))

    {

        $_SESSION['attempts'] = 0;

        $answer = fetchWordArray($WORDLISTFILE);

        $_SESSION['answer'] = $answer;

        $_SESSION['hidden'] = hideCharacters($answer);

        echo 'Попыток осталось: '.($MAX_ATTEMPTS - $_SESSION['attempts']).'<br>';
    }else
    {
        if (isset ($_POST['userInput']))
        {
            $userInput = $_POST['userInput'];
            $_SESSION['hidden'] = checkAndReplace(strtolower($userInput), $_SESSION['hidden'], $_SESSION['answer']);
            checkGameOver($MAX_ATTEMPTS,$_SESSION['attempts'], $_SESSION['answer'],$_SESSION['hidden']);
        }
        $_SESSION['attempts'] = $_SESSION['attempts'] + 1;
        echo 'Попыток осталось: '.($MAX_ATTEMPTS - $_SESSION['attempts'])."<br>";
    }
    $hidden = $_SESSION['hidden'];
    foreach ($hidden as $char) echo $char."  ";
?>
<script type="application/javascript">
    function validateInput()
    {
    var x=document.forms["inputForm"]["userInput"].value;
    if (x=="" || x==" ")
      {
          alert("Please enter a character.");
          return false;
      }
    if (!isNaN(x))
    {
        alert("Please enter a character.");
        return false;
    }
}
</script>
<form name = "inputForm" action = "" method = "post">
Буква: <input name = "userInput" type = "text" size="1" maxlength="1"  />
<input type = "submit"  value = "Проверить" onclick="return validateInput()"/>
<input type = "submit" name = "newWord" value = "Новое слово"/><br>
<!-- Слово: <input name = "word" type = "text" size="16" onblur="$_SESSION['word'] = document.forms['inputForm']['word'].value; print $_SESSION['word'];"/>
<input type = "submit" name = "createWord" value = "Создать слово" onclick="return addWordToFile($WORDLISTFILE, $_SESSION['word']);"/>
 -->
</form>
</body>
</html>