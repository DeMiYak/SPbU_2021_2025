<!doctype html>
<html lang=ru>
    <head><title>QuizMachine</title>
    <link rel=stylesheet href=Chapter6.css>
</head>
<body>
    <p>Опросник</p>
<?php
include("Addition/QuizBuilder.php");
include("Addition/takeQuiz.php");
include("Addition/editQuiz.php");
include("Addition/showLog.php");
include("Addition/gradeQuiz.php");
include("Addition/writeQuiz.php");

function getFiles(){
    global $dirPtr, $theFiles;
    chdir(".");
    $dirPtr = openDir(".");
    $currentFile = readDir($dirPtr);
    while($currentFile !== false){
        $theFiles[] = $currentFile;
        $currentFile = readDir($dirPtr);
    }
}

function showTest(){
    global $theFiles;
    print <<<HERE
    <form action=Addition/takeQuiz.php method=post>
    <table align=center border=3 cellpadding=2 width=40%>
    <tr>
    <td colspan=2>
    <p>Начать опрос</p></td></tr>
    <tr><td>Пароль опроса</td>
    <td><input type=password name=password/>
    </td></tr>
    <tr><td>Опрос</td>
    <td><select name=takeFile>
    HERE;
    $testFiles = preg_grep("/html$/", $theFiles);
    foreach($testFiles as $myFile){
        $fileBase = substr($myFile, 0, strlen($myFile) - 5);
        print("<option value=$fileBase>$fileBase</option>\n");
    }

    print <<<HERE
    </select>
    </td>
    </tr>
    <tr>
    <td colspan=2>
    <input type=submit value=Начать>
    </td>
    </tr>
    </table>
    </form>
    HERE;
}

function showEdit(){
    global $theFiles;
    $testFiles = preg_grep("/mas$/", $theFiles);
    print <<<HERE
    <form action=Addition/editQuiz.php method=post>
    <table align=center border=3 cellpadding=2 width=40%>
    <tr>
    <td colspan=2>
    <p>Изменить опрос</p></td></tr>
    <tr><td>Пароль администратора</td>
    <td><input type=password name=password value=""/>
    </td></tr>
    <tr><td>Опрос</td>
    <td><select name=editFile>
    <option value=new>Новый опрос</option>
    HERE;
    foreach($testFiles as $myFile){
        $fileBase = substr($myFile, 0, strlen($myFile)-4);
        print "<option value=$myFile>$fileBase</option>\n";
    }
    print <<<HERE
    </select></td></tr>
    <tr><td colspan=2><input type=submit value=Начать>
    </td></tr></table></form>
    HERE;
}

function showLog(){
    global $theFiles;
    print <<<HERE
    <form action=Addition/showLog.php method=post>
    <table align=center border=3 cellpadding=2 width=40%>
    <tr>
    <td colspan=2>
    <p>Показать список изменений</p></td></tr>
    <tr><td>Пароль администратора</td>
    <td><input type=password name=password value=""/>
    </td></tr>
    <tr><td>Опрос</td>
    <td><select name=logFile>
    HERE;

    $logFiles = preg_grep("/log$/", $theFiles);
    foreach($logFiles as $myFile){
        $fileBase = substr($myFile, 0, strlen($myFile)-4);
        print "<option value=$myFile>$fileBase</option>\n";
    }
    print <<<HERE
    </select></td></tr>
    <tr><td colspan=2><input type=submit value=Начать>
    </td></tr></table></form>
    HERE;
}

getFiles();
showTest();
showEdit();
showLog();
?>
</body>
</html>