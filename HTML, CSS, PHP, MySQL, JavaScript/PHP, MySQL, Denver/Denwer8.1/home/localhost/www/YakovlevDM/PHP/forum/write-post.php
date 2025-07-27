<html>
<head>
<title>Просмотр</title>
</head>
<body>
<?

function buildHT($text){

    $data = explode("\n", $text);

    $ht_data = "";
    foreach ($data as $line) {
        $ht_data .= $line . "<br>";
    }

    return $ht_data;
}

$title = $_REQUEST['title'];
$author = $_REQUEST['author'];
$text = $_REQUEST['text'];
$id = $_REQUEST['id'];
$action = $_REQUEST['action'];

$conn = new mysqli("mysql", "server", "server", "forum");
if (!$conn -> connect_errno) {

    if ($action == "update") {

        $ht_data = buildHT($text);
        if ($id == "new") {
            $result = $conn -> query("INSERT INTO posts (title, author, text) VALUES ('$title', '$author', '$ht_data')");
        } else {
            $result = $conn -> query("UPDATE posts SET title='$title', text='$ht_data' WHERE id=$id");
        }
        
        if (is_null($result)) {
            echo "<script type='text/javascript'>alert('Не удалось изменить сообщение, попробуйте ещё раз');";
            echo " history.back()</script>";
        }

        print
        <<<HERE
        <h3>$title</h3>
        <div style='padding: 5px;'>$ht_data</div>
        <br>Автор:  $author<br>
        <br><br>
        <a href="main-page.php">На главную</a>
        HERE;

    } else {

        $conn -> query("DELETE FROM posts WHERE id=$id");
        $conn -> close();
        echo "<script type='text/javascript'>window.location.href = 'main-page.php'</script>";

    }

    $conn -> close();

} else {
    echo "<script type='text/javascript'>alert('Не удалось изменить сообщение, попробуйте ещё раз');";
    echo " history.back()</script>";
}

?>
</body>