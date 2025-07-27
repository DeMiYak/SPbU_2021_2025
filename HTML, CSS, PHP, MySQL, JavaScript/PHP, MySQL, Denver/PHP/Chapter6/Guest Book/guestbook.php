<?php
header("Content-type: text/html; charset=utf-8");
error_reporting(-1);

require_once 'funcs.php'; // подключаем файл funcs.php

// принятие данных из формы
// если у нас не пуст массив $_POST, то вызовем некую функцию: save_mess
 
?>


<!doctype html>
<html Lang="en">
<html>
<head>
<link rel=stylesheet href=../Chapter6.css>
<meta charset ="UTF-8">
<title>Гостевая книга</title>
</head>
<body>
<?php
/* var_dump($_GET);
print $_GET['mode']; */
save_mess(); // Пользовательская функция

$messages = get_mess();
$messages = array_mess($messages);
/* print_arr ($messages); */
?>
<!-- Возвращаемся в меню выбора режима работы -->
<button onclick="document.location='mode.php'">Вернуться к выбору режима работы</button>
<?php if($_GET['mode']=="Гость"){ ?>
<!-- Создаём форму -->
<form action = "guestbook.php" method = "get">
<input type=submit name=mode value="Регистрация гостя"/>
<?php } else if ($_GET['mode']=="Пользователь") {?>
<!-- Создаём форму -->
<form action = "guestbook.php" method = "get">
<p>
<!-- Название поля -->
<label for ="name"> Имя:</label>
<!-- Поле для ввода имени -->
<input type ="text" name ="name" id ="name">
</p>
<p>
<!-- Название поля -->
<label for ="text"> Текст:</label>
<!-- Поле для ввода текста -->
<textarea name = "text" id ="text" ></textarea>
</p>

<!-- Кнопка -->
<button type="submit"> Написать </button>
<input type=hidden name=mode value="Пользователь">
</form>

<?php } else { ?>
<!-- Создаём форму -->
<form action = "guestbook.php" method = "get">
<input type=submit name=register value="Администратор"/>
</form>
<?php } ?>
<hr class=wide>
<br><br>
<?php if (! empty ($messages)): ?>
<!-- проходим по массиву $messages в цикле и выводим наши сообшения -->
<?php foreach ($messages as $message) : ?>
<!-- возвращает, разбитую в массив строку -->
<?php $message = get_format_message($message); //print_r($message) ?>
<!-- выводим полученные наши данные -->
<div class= "messages">
<hr class=wide>
<p> Автор: <?= $message[0] ?> | Дата: <?= $message[2] ?> </p>
<div> <?= nl2br ( htmlspecialchars ($message[1]) ) ?> </div>
<hr class=wide>
</div>
<?php endforeach; ?>
<?php endif; ?>
</body>
</html>