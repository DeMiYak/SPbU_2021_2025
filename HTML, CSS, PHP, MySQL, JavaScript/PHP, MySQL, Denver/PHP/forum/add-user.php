<?

$user = stripcslashes($_REQUEST['user']);
$password = password_hash(stripcslashes($_REQUEST['password']), PASSWORD_DEFAULT, []);
$mode = $_REQUEST['mode'];

if (strcmp($mode, "return") == 0) {
    echo "<script type='text/javascript'>window.location.href = 'main-page.php'</script>";
}

function isUserAlreadyExists($user, $users) {

    foreach ($users as $user_file) {
        if (strcmp($user_file[0], $user) == 0) {
            return true;
        }
    }
    return false;
}

$conn = new mysqli("mysql", "server", "server", "forum");
if (!$conn -> connect_errno && !is_null($users = $conn -> query("SELECT * FROM users"))) {

    $users = $users -> fetch_all();

    if (strcmp(trim($mode), "change") == 0 || !isUserAlreadyExists($user, $users)) {

        $upd = new mysqli("mysql", "server", "server", "forum");
        if (!$upd -> connect_errno) {
            
            $upd -> query("INSERT INTO users (login, pass, is_admin) VALUES ('$user', '$password', 0)");

            echo "<script type='text/javascript'>alert('Пользователь успешно зарегистрирован / изменён'); window.location.href = 'main-page.php'</script>";
            $upd -> close();
        }
    } else if (strcmp($user, "admin") !== 0) {
        print
        <<<HERE
        <html>
        <head>
        <title>Подтверждение</title>
        </head>
        <body>
        <script type='text/javascript'>
            function send() {
                document.getElementById("submit_button").click();
            }
        </script>
        <form action = "add-user.php" method = "post">
            <input type = "text" name = "user" value = "$user" hidden>
            <input type = "text" name = "password" value = "$password" hidden>
            <input type = "text" name = "mode" value = "return" hidden>
            Хотите ли вы сменить пароль для существующего пользователя « $user »?<br><br>
            <input type = "button" value = "Да" onclick="document.forms[0].elements['mode'].value = 'change'; send();">&nbsp;
            <input type = "button" value = "Нет" onclick="send();">
            <input type = "submit" id = "submit_button" hidden>
        </form>
        </body>
        </html>
        HERE;
    } else {
        echo "<script type='text/javascript'>alert('Вы не можете изменить профиль администратора'); window.location.href = 'main-page.php'</script>";
    }

    $conn -> close();

}

?>