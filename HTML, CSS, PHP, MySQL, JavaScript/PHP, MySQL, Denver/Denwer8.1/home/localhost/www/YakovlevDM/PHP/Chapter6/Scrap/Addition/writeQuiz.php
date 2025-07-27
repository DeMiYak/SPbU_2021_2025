<!doctype html>
<html lang=ru>
    <head><title>WriteQuiz</title>
    <link rel=stylesheet href=Chapter6.css>
</head>
<body>
    <?php
    $fileBase = str_replace(" ", "_", $quizName);
    $htmlFile = $fileBase . ".html";
    $masFile = $fileBase . ".mas";
    $htfp = fopen($htmlFile, "w");
    $htData = buildHTML();
    fputs($htfp, $htData);
    fclose($htfp);

    $msfp = fopen($masFile, "w");
    $msData = buildMas();
    fputs($msfp, $msData);
    fclose($msfp);

    print <<<HERE
    <pre>
    $msData
    </pre>
    HERE;

    function buildMas(){
        global $quizName, $quizEmail, $quizPwd, $quizData;
        $msData = $quizName . "\n";
        $msData .= $quizEmail . "\n";
        $msData .= $quizPwd . "\n";
        $msData .= $quizData;
        return $msData;
    }

    function buildHTML(){
        global $quizName, $quizData;
        $htData = <<<HERE
        <html>
        <head>
        <title>$quizName</title>
        </head>
        <body>
        HERE;

        $problems = str_split($quizData);
        $htData .= <<<HERE
        <center>
        <h1>$quizName</h1>
        </center>
        <form action=gradeQuiz.php method=post>
        Имя <input type=text name=student />
        <ol>
        HERE;
        $questionNumber = 1;
        foreach($problems as $currentProblem){
            list($question, 
            $answerA, 
            $answerB, 
            $answerC, 
            $answerD, 
            $correct) 
            = explode(":", $currentProblem);
            $htData .= <<<HERE
            <li>
            $question
            <ol type=A>
            <li><input type=radio name=quest[$questionNumber] value=A>
            $answerA
            </li>
            <li><input type=radio name=quest[$questionNumber] value=B>
            $answerB
            </li>
            <li><input type=radio name=quest[$questionNumber] value=C>
            $answerC
            </li>
            <li><input type=radio name=quest[$questionNumber] value=D>
            $answerD
            </li>
            </ol>
            </li>
            HERE;
            $questionNumber++;
        }
        $htData .= <<<HERE
        </ol>
        <input type=hidden name=quizName value=$quizName/>
        <input type=submit value="Отправить форму"/>
        </form>
        HERE;
        print $htData;
        return $htData;
    }
    ?>
</body>
</html>