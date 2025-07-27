<!DOCTYPE html>
<html lang=ru>

<head>
    <link rel=stylesheet href=../Chapter6.css>
    <title>Режим работы</title>
    <meta charset ="UTF-8">
</head>

<body>
    <h1>Пожалуйста, выберите режим работы с гостевой книгой.</h1>
    <form method=get action=guestbook.php>
        <table align=center border=4 cellpadding=5>
            <tr>
                <td>
                    <input type="submit" name="mode" value="Гость" />
                </td>
                <td>
                    <input type="submit" name="mode" value="Пользователь" />
                </td>
                <td>
                    <input type="submit" name="mode" value="Администратор" />
                </td>
            </tr>
        </table>
        <input type=hidden name=name value='' />
        <input type=hidden name=text value='' />
    </form>
</body>

</html>