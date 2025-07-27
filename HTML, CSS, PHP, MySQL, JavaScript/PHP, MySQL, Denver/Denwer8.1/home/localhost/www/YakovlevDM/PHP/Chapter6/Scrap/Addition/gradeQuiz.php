<!doctype html>
<html lang=ru>
    <head><title>GradeQuiz</title>
    <link rel=stylesheet href=Chapter6.css>
</head>
<body>
    <?php
    include("writeQuiz.php");
    print <<<HERE
    <html>
    <head>
    <title>Результат для $quizName: $student</title>
    </head>
    <body>
    <h1>Результат для $quizName: $student</h1>
    HERE;

    $fileBase = str_replace(" ", "_", $quizName);
    $masFile = $fileBase . ".mas";
    $msfp = fopen($masFile, "r");

    $logFile = $fileBase . ".log";

    $quizName = fgets($msfp);
    $quizEmail = fgets($msfp);
    $quizPwd = fgets($msfp);
    
    $numCorrect = 0;
    $questionNumber = 1;
    while(!feof($msfp)){
        $currentProblem = fgets($msfp);
        list($question, 
        $answerA,
        $answerB,
        $answerC, 
        $answerD, 
        $correct) 
        = explode(":", $currentProblem);
        $key[$questionNumber++] = $correct; // ???
    }
    fclose($msfp);
    for($questionNumber = 1; $questionNumber <= count($quest); $questionNumber++){
        $guess = $quest[$questionNumber];
        $correct = $key[$questionNumber];
        $correct = rtrim($correct);
        if($guess == $correct){
            $numCorrect++;
            print "Ответ №$questionNumber правильный<br>\n";
        } else {
            print "<font color=red>Ответ №$questionNumber неправильный</font><br>\n";
        }
    }
    print "Итого: $numCorrect из ". count($quest). " вопросов отвечены правильно";
    $percentage = ($numCorrect/count($quest))*100;
    print "В процентах: $percentage<br>\n";
    $today = date("F, Y g:i a")
    ?>
</body>
</html>