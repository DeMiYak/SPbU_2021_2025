<?php
function save_mess()
{
    if ($_GET['name'] && $_GET["text"]) {
        $str = $_GET['name'] . '|' . $_GET['text'] . '|' . date('Y-m-d H:i:s') . "\n***\n";
        // записываем все в файл gb.txt с помощью функции file_put_contents
        file_put_contents('gb.txt', $str, FILE_APPEND);
    }
}
function get_mess()
{
    // возвращаем результат работы функции file_get_contents
    return file_get_contents('gb.txt');
}
function array_mess($messages)
{
    $messages = explode("\n***\n", $messages);
    array_pop($messages); // убираем последний элемент массива
    return array_reverse($messages); // переварачиваем массив
}
function get_format_message($message)
{
    return explode('|', $message);
}
function print_arr($arr)
{
    echo '<pre>' . print_r($arr, true) . '</pre>';
}

?>