<!-- 

    ? Как вставлять текстовые файлы, ссылки, изображения, 
    ? загрузочные файлы в таблицу через параметры

 -->





<!doctype html>
<html lang="ru">

<head>
    <title>Глава 3: Управляем работой программы с помощью условий и функций</title>
    <link rel="stylesheet" href="Chapter3.css">
</head>

<body>
    Web-дизайн, глава 3: шаблон для пользовательской страницы с большим числом параметров для ввода значений
    пользователя:
    <ul>
        <li> на странице должна быть таблица с ячейками 2х2,
        </li>
        <li> возможности изменения параметров фона страницы,

        </li>
        <li> размещения таблицы, параметров таблицы, параметров ячейки, вставки в ячейку текстового файла, ссылки,
            изображения, загрузочного файла (с возможностью запуска программы) и другие,
        </li>

    </ul>

    <hr class="short">
    <hr class="wide">
    <hr class="short">

    <form method="post" action="Table.php">
        <table cellspacing='4' cellpadding='3' border='4' align='center' style="size:fit-content;">
            <tr>
                <th>Background Color</th>
                <th>Table Border</th>
                <th>Table Alignment</th>
            </tr>
            <tr>
                <td>
                    <select name="bc" size="1" style="color:purple;">
                        <option value="purple">purple</option>
                        <option value="red">red</option>
                        <option value="green">green</option>
                        <option value="hotpink">hotpink</option>
                        <option value="crimson">crimson</option>
                        <option value="thisle">thisle</option>
                        <option value="chartreuse">chartreuse</option>
                        <option value="chocolate">chocolate</option>
                        <option value="cyan">cyan</option>
                        <option value="blue">blue</option>
                        <option value="aquamarine">aquamarine</option>
                        <option value="darksalmon">darksalmon</option>
                        <option value="fuchsia">fuchsia</option>
                        <option value="firebrick">firebrick</option>
                        <option value="white">white</option>
                        <option value="black">black</option>
                        <option value="#2b2b2b" selected>mine shaft</option>
                        <option value="gray">gray</option>
                    </select>
                </td>
                <td><input name="tb" type="text" size="12" style="color:purple;background-color:orange;"></input></td>
                <td>
                    <select name="ta" size="1" style="color:purple;">
                        <option value="left">left</option>
                        <option value="center" selected>center</option>
                        <option value="right">right</option>
                        <option value="justify">justify</option>
                    </select>
                </td>
            </tr>
            <tr>
                <th>CellSpacing</th>
                <th>CellPadding</th>
                <th>Table Width (%)</th>
            </tr>
            <tr>
                <td><input name="cs" type="text" size="12" style="color:purple;background-color:orange;"></input></td>
                <td><input name="cp" type="text" size="12" style="color:purple;"></input></td>
                <td><input name="tw" type="text" size="12" style="color:purple;background-color:orange;"></input></td>
            </tr>
            <tr>
                <th>font-family</th>
                <th>Insert a file</th>
                <th>Cell Alignment</th>
            </tr>
            <tr>
                <td><select name="ff" size="1" style="color:purple;">
                        <option value="Times New Roman" selected>Times New Roman</option>
                        <option value="monospace">monospace</option>
                        <option value="sans-serif">sans-serif</option>
                        <option value="Arial">Arial</option>
                        <option value="fantasy">fantasy</option>
                        <option value="cursive">cursive</option>
                        <option value="Haettenschweiler">Haettenschweiler</option>
                        <option value="Impact">Impact</option>
                        <option value="Franklin Gothic Medium">Franklin Gothic Medium</option>
                    </select>
                    <!-- font-family: 'Courier New', Courier, monospace ;
    font-family: 'Franklin Gothic Medium', 'Arial Narrow', Arial, sans-serif;
    font-family: 'Times New Roman', Times, serif;
    font-family:fantasy;
    font-family:cursive;
    font-family:Impact, Haettenschweiler, 'Arial Narrow Bold', sans-serif   -->
                </td>
                <td>Position: <select name="ifVal" size="1" style="color:purple;">
                        <option value="0" selected>1x1</option>
                        <option value="1">1x2</option>
                        <option value="2">2x1</option>
                        <option value="3">2x2</option>
                    </select>
                    <br><select name="if" size="6" style="color:purple;background-color:orange;">
                        <option value="Hyperlinks\Task1.html" selected>Hyperlinks\Task1.html</option>
                        <option value="Hyperlinks\Task2.html">Hyperlinks\Task2.html</option>
                        <option value="Hyperlinks\Task3.html">Hyperlinks\Task3.html</option>
                        <option value="Hyperlinks\Task4.html">Hyperlinks\Task4.html</option>
                        <option value="Hyperlinks\Task5.html">Hyperlinks\Task5.html</option>
                        <option value="Hyperlinks\Task6.html">Hyperlinks\Task6.html</option>
                        <option value="Hyperlinks\Task7.html">Hyperlinks\Task7.html</option>
                        <option value="Hyperlinks\Tasks.html">Hyperlinks\Tasks.html</option>
                        <option value="Imagery\Fleur-de-lis.png">Imagery\Fleur-de-lis.png</option>
                        <option value="Imagery\fontenblo.jpg">Imagery\fontenblo.jpg</option>
                        <option value="Imagery\Jumping-Spyro.gif">Imagery\Jumping Spyro.gif</option>
                        <option value="Imagery\NOTRDAM.gif">Imagery\NOTRDAM.gif</option>
                        <option value="Imagery\NOTRDAM1.gif">Imagery\NOTRDAM1.gif</option>
                        <option value="Imagery\Windows_XP_Wallpaper.jpg">Imagery\Windows XP Wallpaper.jpg</option>
                        <option value="Imagery\Space.jpg">Imagery\Space.jpg</option>
                        <option value="Music\Freddy-Fazbear-s-Pizzeria-Simulator-OST-Extended-Just-Add-Water.mp3">
                            Music\Freddy-Fazbear-s-Pizzeria-Simulator-OST-Extended-Just-Add-Water.mp3</option>
                        <option value="Music\Victoria-2-Soundtrack-Handel-This.mp3">
                            Music\Victoria-2-Soundtrack-Handel-This.mp3</option>
                        <option value="TextFiles\охрана-здоровья-и-среды.txt">TextFiles\охрана здоровья и среды.txt
                        </option>
                        <option value="TextFiles\зубцы-и-амбразуры.txt">TextFiles\зубцы и амбразуры.txt</option>
                        <option value="TextFiles\ворота.txt">TextFiles\ворота.txt</option>
                    </select>
                </td>
                <td>Position: <select name="caVal" size="1" style="color:purple;">
                        <option value="0" selected>1x1</option>
                        <option value="1">1x2</option>
                        <option value="2">2x1</option>
                        <option value="3">2x2</option>
                    </select>
                    <br>
                    Alignment:<select name="ca" size="1" style="color:purple;">
                        <option value="left">left</option>
                        <option value="center" selected>center</option>
                        <option value="right">right</option>
                        <option value="justify">justify</option>
                    </select>
                </td>
            </tr>
            <tr>
                <th>Border Color</th>
                <th>Border Style</th>
                <th>Page Color</th>
            </tr>
            <tr>
                <td>
                    <select name="bco" size="1" style="color:purple;">
                        <option value="purple">purple</option>
                        <option value="red">red</option>
                        <option value="green">green</option>
                        <option value="hotpink">hotpink</option>
                        <option value="crimson">crimson</option>
                        <option value="thisle">thisle</option>
                        <option value="chartreuse">chartreuse</option>
                        <option value="chocolate">chocolate</option>
                        <option value="cyan">cyan</option>
                        <option value="blue">blue</option>
                        <option value="aquamarine">aquamarine</option>
                        <option value="darksalmon">darksalmon</option>
                        <option value="fuchsia">fuchsia</option>
                        <option value="firebrick" selected>firebrick</option>
                        <option value="white">white</option>
                        <option value="black">black</option>
                        <option value="#2b2b2b">mine shaft</option>
                        <option value="gray">gray</option>
                    </select>
                </td>
                <td>

                    <!--  border-style:dashed dotted double;
    border-style:groove outset ridge solid; -->
                    <select name="bs" size="1" style="color:purple;">
                        <option value="dashed">dashed</option>
                        <option value="dotted">dotted</option>
                        <option value="double">double</option>
                        <option value="groove">groove</option>
                        <option value="outset">outset</option>
                        <option value="ridge">ridge</option>
                        <option value="solid" selected>solid</option>
                    </select>
                </td>
                <td>
                    <select name="pc" size="1" style="color:purple;">
                        <option value="purple">purple</option>
                        <option value="red">red</option>
                        <option value="green">green</option>
                        <option value="hotpink">hotpink</option>
                        <option value="crimson">crimson</option>
                        <option value="thisle">thisle</option>
                        <option value="chartreuse">chartreuse</option>
                        <option value="chocolate">chocolate</option>
                        <option value="cyan">cyan</option>
                        <option value="blue">blue</option>
                        <option value="aquamarine">aquamarine</option>
                        <option value="darksalmon">darksalmon</option>
                        <option value="fuchsia">fuchsia</option>
                        <option value="firebrick">firebrick</option>
                        <option value="white">white</option>
                        <option value="black">black</option>
                        <option value="#2b2b2b" selected>mine shaft</option>
                        <option value="gray">gray</option>
                    </select>
                </td>
            </tr>
            <tr>
                <th colspan="3">Table Text Color</th>
            </tr>
            <tr>
                <td colspan="3">
                    <select name="ttc" size="1" style="color:purple;">
                        <option value="purple">purple</option>
                        <option value="red">red</option>
                        <option value="green">green</option>
                        <option value="hotpink">hotpink</option>
                        <option value="crimson">crimson</option>
                        <option value="thisle">thisle</option>
                        <option value="chartreuse">chartreuse</option>
                        <option value="chocolate">chocolate</option>
                        <option value="cyan">cyan</option>
                        <option value="blue">blue</option>
                        <option value="aquamarine">aquamarine</option>
                        <option value="darksalmon">darksalmon</option>
                        <option value="fuchsia">fuchsia</option>
                        <option value="firebrick">firebrick</option>
                        <option value="white">white</option>
                        <option value="black">black</option>
                        <option value="#cccccc" selected>gris de perle</option>
                        <option value="gray">gray</option>
                    </select>
                </td>
            </tr>
            <tr>
                <td colspan='3' align='center'><input type="submit" value="Изменить данные"></input></td>
        </table>
    </form>
    <!-- <form method="post" action="Chapter3.php"> -->

    <hr class="short">
    <hr class="wide">
    <hr class="short">
</body>

</html>