<?

function showPosts(){

    $conn = new mysqli("mysql", "server", "server", "forum");
    if (!$conn -> connect_errno && !is_null($result = $conn -> query("SELECT * FROM posts ORDER BY id DESC"))) {
        
        $row = $result -> fetch_all();

        foreach($row as $post) {
                
            echo "<div style='left-margin: 30px; padding: 5px; bottom-margin: 10px; width: 50%; height: 300px; border-style: solid; border-width: 1px; float: left;'>";
            echo "<h3>" . $post[1] . "</h3>";
            echo "<div style='padding: 5px;'>" . $post[3] . "</div>";
            echo "<br>Автор: " . $post[2] . "<br>";
            echo "</div>";

        }
        $conn -> close();
    }

}

function showUserRegistration() {

    print 
    <<<HERE
    <form action = "add-user.php" method = "post">
        <table border = 1 width = 400>
            <tr>
                <td colspan = 2>
                    <center>
                    <h3>Регистрация пользователя</h3>
                    </center>
                </td>
            </tr>
            <tr>
                <td>Логин</td>
                <td>
                    <input type = "text" name = "user" value = "">
                </td>
            </tr>
            <tr>
                <td>Пароль</td>
                <td>
                    <input type = "password" name = "password" value = "">
                </td>
            </tr>
            <tr>
                <td colspan = 2>
                    <center>
                    <input type = "hidden" name = "mode" value = "add">
                    <input type = "submit" value = "Зарегистрироваться">
                    </center>
                </td>
            </tr>
        </table>
    </form>
    </div>
    HERE;
}

function showEdit(){
    
    print 
    <<<HERE
    <div style="float: right; position: relative; top: 0%; left: -10%;">
    <form action = "edit-post.php" method = "post">
        <table border = 1 width = 400>
            <tr>
                <td colspan = 2>
                    <center>
                    <h3>Создать или изменить сообщение</h3>
                    </center>
                </td>
            </tr>
            <tr>
                <td>Логин</td>
                <td>
                    <input type = "text" name = "user" value = "">
                </td>
            </tr>
            <tr>
                <td>Пароль</td>
                <td>
                    <input type = "password" name = "password" value = "">
                </td>
            </tr>
            <tr>
                <td>Сообщение</td>
                <td>
                    <select name = "post_id">
                    <option value = "new">Новое сообщение</option>
    HERE;

    $conn = new mysqli("mysql", "server", "server", "forum");
    if (!$conn -> connect_errno && !is_null($result = $conn -> query("SELECT * FROM posts ORDER BY id DESC"))) {
        $posts = $result -> fetch_all();
        foreach ($posts as $post){
            $id = $post[0];
            $title = str_replace(' ', '_', $post[1]);
            print " <option value = $id>$title ($id)</option>\n";
        }
        $conn -> close();
    }
    print 
    <<<HERE
                    </select>
                </td>
            </tr>
            <tr>
                <td colspan = 2>
                    <center>
                    <input type = "submit" value = "Создать / Изменить">
                    </center>
                </td>
            </tr>
        </table>
    </form>
    <br>
    HERE;
}

?>