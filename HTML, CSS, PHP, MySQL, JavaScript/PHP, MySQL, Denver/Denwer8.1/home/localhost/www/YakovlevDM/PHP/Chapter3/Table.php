<!doctype html>
<html>

<head>
    <title>Таблица для главы 3</title>
    <link rel="stylesheet" href="Chapter3.css">
</head>

<?php
    /*
    $roll = rand(1, 6);
    if($roll == 1){
        // Пример игнорирования лишних пробелов и символа каретки.
        print "<h2>That's     \n an ace!</h2>";
    } else{
        print"Not an ace...<br>";
    }
    print "You rolled a $roll\$";
    function verse1($s){

    }
    function verse2($s){
        return $s;
    }
    */
    function makeTable(){
        global $bc, $tb, $ta, $cs, $cp, $tw, $if, $caVal, $ca, $bco, $bs, $pc, $ttc, $ff, $ifVal, $fileType;
        $temp = "<body style='background-color:$pc;'><table cellpadding='$cp' cellspacing='$cs' border='$tb' align='$ta' style='font-family:$ff;width:$tw%;border-color:$bco;border-style:$bs;color:$ttc;background-color:$bc;'>";
        for($i = 0; $i <= 1; $i++){
            $temp .= "<tr>";
            for($j=0; $j<=1; $j++){
                if($j + 2*$i == $caVal){
                    $temp .= "<td align='$ca'>";
                }else {$temp .="<td>";};
                if($j + 2*$i == $ifVal){
                    $temp .= match($fileType){
                        'jpg', 'gif', 'png' => '<img src='.$if.'>',
                        'html' => '<iframe src='.$if.'></iframe>',
                        'txt' => '<iframe src='.$if.'></iframe>',
                        'mp3' => '<audio controls loop>
                        <source src='.$if.' type="audio/mpeg">
                        Ваш браузер не поддерживает тип аудиофайла.
                        </audio>',
                    };
                }
                $temp .= "</td>";
            }
            $temp .= "</tr>";
        }
        $temp .= "</table></body>";
        return $temp;
    };
    /* $dp = opendir($dirName);
    chdir($dirName);

    $theFiles = array();
    $currentFile = readDir($dp);
    while($currentFile !== false)
    {
        $theFiles[] = $currentFile;
        $currentFile = readDir($dp);
    }
    var_dump($theFiles);
    $filesInUse = preg_grep("/txt$|mp3$|png$|html$|jpg$|gif$/", $theFiles);
    var_dump($filesInUse); */

    $bc = $_POST["bc"];
    if($bc == ""){$bc = "#2b2b2b";};
    $tb = $_POST["tb"];
    if($tb == ""){$tb = 1;};
    $ta = $_POST["ta"];
    $cs = $_POST["cs"];
    if($cs == "") {$cs = 1;};
    $cp = $_POST["cp"];
    if($cp == "") {$cp = 1;};
    $tw = $_POST["tw"];
    if($tw == "") {$tw = "100";};
    /* $if = $_POST["if"];
    if($if == ""){$if = <<<H
        Here is some text to fill up the void. 
        Here is some text to fill up the void.
        Here is some text to fill up the void.
        Here is some text to fill up the void.
        Here is some text to fill up the void.
        H;}; */
        $caVal = $_POST["caVal"];
    $ca = $_POST["ca"];
    $bco = $_POST["bco"];
    $bs = $_POST["bs"];
    $pc = $_POST["pc"];
    $ttc = $_POST["ttc"];
    $ff = $_POST["ff"];
    $if = $_POST["if"];
    $ifVal = $_POST["ifVal"];

    $fileType = substr($if, strpos($if, ".")+1);
    /* print "$fileType<br>"; */
    /* $if = str_replace(" ", "\ ", $if); */
    /* $temp = explode('\ ', $if);
    $if = $temp[0]; */
    print <<<H
    bc  $bc<br>
    ta  $ta<br>
    cs  $cs<br>
    cp  $cp<br>
    tw  $tw<br>
    caVal   $caVal<br>
    ca  $ca<br>
    bco $bco<br>
    bs $bs<br>
    pc $pc<br>
    ttc $ttc<br>
    if $if <br>
    ff $ff <br>
    ifVal $ifVal <br>
    H;
    $preset = "";
    $preset = makeTable($preset);
    print $preset;
    ?>

</html>