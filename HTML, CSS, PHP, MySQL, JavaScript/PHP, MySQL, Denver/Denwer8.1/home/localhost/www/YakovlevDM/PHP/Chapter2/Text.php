<!doctype html>
<html lang="ru">

<head>
    <title>Морозко</title>
    <link rel="stylesheet" href="Chapter2.css">
</head>

<body>
    <h4> Морозко (Отрывок)</h4>
    <?php
    $anim1 =  $_POST["anim1"]; 
    $anim2 =  $_POST["anim2"];
    $anim3 =  $_POST["anim3"];
    $anim4 =  $_POST["anim4"];
    $anim5 = $_POST["anim5"];
    $action1 =  $_POST["action1"];
    $action2 =  $_POST["action2"];
    $bodypart =  $_POST["bodypart"];
    $stuff1 =  $_POST["stuff1"];
    $stuff2 =  $_POST["stuff2"];
    $stuff3 =  $_POST["stuff3"];
    $stuff4 = $_POST["stuff4"];
    $veget =  $_POST["veget"];
    $place1 =  $_POST["place1"];
    $place2 =  $_POST["place2"];
    $place3 =  $_POST["place3"];
    $place4 =  $_POST["place4"];
    $place5 =  $_POST["place5"];
    $mood =  $_POST["mood"];
        print <<<HR
        <p>
        Живало-бывало, – жил $anim1 да с другой $anim2. 
        У $anim1 была $anim3 и у $anim2 была $anim4. 
        
        Все знают, как за мачехой жить: перевернешься – $action1 
        и недовернешься – $action1. А родная $anim4 что ни $action2 
        – за все гладят по $bodypart: умница.
        <br>
        $anim3 и скотину поила-кормила, $stuff1 и $stuff3 в $place1 носила, $stuff4 топила, $place3 мела еще до свету… Ничем $anim2 не угодить – все не $veget, все $mood.

        $stuff2 хоть пошумит, да затихнет, а старая $anim2 расходится – не скоро уймется. Вот $anim2 и придумала $anim3 со свету сжить.
        <br>
        – Вези, вези её, старик, – говорит $anim2, – куда хочешь, чтобы мои глаза ее не видали! Вези ее в $place2, на трескучий $place5.
        <br>
        Старик затужил, заплакал, однако делать нечего, $anim2 не переспоришь. Запряг $anim5: – Садись, милая $anim3, в сани. Повез бездомную в $place2, свалил в сугроб под $place4 и уехал.
        </p>
        HR
        ?>
</body>

</html>