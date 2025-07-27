<!doctype html>
<html lang=ru>
    <head><title>QuizBuilder</title>
    <link rel=stylesheet href=Chapter6.css>
</head>
<body>
    <?php
    include_once("QuizMachine.php");
    include("takeQuiz.php");
    include("writeQuiz.php");
    extract($_POST);

    if($password == "JamShoot"){
        print <<<HERE
        <font color=red size=+4>
        Неправильный пароль
        </font>
        HERE;
    } else {
        if($editFile == "new"){
            $quizName = "sample test";
            $quizEmail = "root@localhost";
            $quizData = "q:a:b:c:d:correct";
            $quizPwd = "php";
        } else {
            $fp = fopen($editFile, "r");
            $quizName = fgets($fp);
            $quizEmail = fgets($fp);
            $quizPwd = fgets($fp);
            while(!feof($fp)){
                $quizData .= fgets($fp); // ???
            }
            fclose($fp);
        }
    }
    print <<<HERE
    <form action = "writeQuiz.php" method=post>

    <table border=1>
    <tr>
    <th>Наименование опроса</th>
    <td><input type=text name=quizName value=$quizName/>
    </td>
    </tr>
    <tr><th>Инструктор электронной почты</th>
    <td><input type=text name=quizEmail value=$quizEmail/>
    </td></tr>
    <tr><th>Пароль</th>
    <td><input type=text name=quizPwd value=$quizPwd/>
    </td></tr>
    <tr>
    <td rowspan=1 colspan=2>
    <textarea name=quizData rows=20 cols=60>
    $quizData</textarea>
    </td></tr>
    <tr>
    <td colspan=2><center>
    <input type=submit value="Сделать опрос">
    </center></td>
    </tr>
    </table>
    </form>
    HERE;
    ?>
</body>
</html>