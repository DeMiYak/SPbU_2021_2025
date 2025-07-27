<!doctype html>
<html lang=ru>
    <head><title>TakeQuiz</title>
    <link rel=stylesheet href=Chapter6.css>
</head>
<body>
    <?php
    $masterFile = $takeFile . ".mas";
    $fp = fopen($masterFile, "r");
    $dummy = fgets($fp);
    $dummy = fgets($fp);
    $magicWord = fgets($fp);
    $magicWord = rtrim($magicWord);
    fclose($fp);
    
    if($password == $magicWord){
        $htmlFile = $takeFile . ".html";
        readFile($htmlFile);
    } else {
        print <<<HERE
        <font color=red size=+3>
        Неправильный пароль.<br>
        Чтобы принять участие в опросе, вам нужен пароль
        </font>
        HERE;
    }
    ?>
</body>
</html>