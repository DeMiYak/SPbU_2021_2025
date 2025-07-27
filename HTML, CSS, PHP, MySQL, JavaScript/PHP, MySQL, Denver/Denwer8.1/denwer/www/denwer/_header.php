<?php
$TITLE = preg_replace("/^[\s\d]+/", "", @$TITLE? $TITLE : @$_REQUEST["TITLE"]);
$USE_HEAD = @$USE_HEAD? $USE_HEAD : @$_REQUEST["USE_HEAD"];
$ISMAIN = @$ISMAIN? $ISMAIN : @$_REQUEST["ISMAIN"];
?>
<html>
<head>
  <title><?=strip_tags($TITLE)?></title>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  <style type="text/css">
  <!--
    html, body { padding: 0px; margin: 0px; }
    .menu { padding: 4px 10px 4px 10px; border-bottom: 3px double #999999; background: #FFFFFF; font-size: 85%; font-weight: bold; }
    p { text-align: justify }
    h1 { font-size: 150%; }
    h2 { font-size: 130%; }
  -->
  </style>
</head>

<body bgcolor="white" text="#000000" link="#00639C" alink="#ffaa00" vlink="#00437C">

<table width="100%" height="100%" cellpadding="0" cellspacing="0" border="0">
<tr valign="top">
  <td bgcolor="#DEDFDE" width="80%" style="border-right: 1px outset">
    <?if ($USE_HEAD) {?>
      <table class="menu" width="100%" cellpadding="0" cellspacing="0" border="0">
      <tr>
        <td>
          <a href="http://localhost">localhost</a>
          |
          <a href="http://localhost/Tools/">Утилиты</a>
          |
          <a href="http://localhost/Tests/">Тестирование</a>
        </td>
        <td align="right">
          <a href="https://seditio.org">CMS Seditio</a>
		   |
          <a href="https://seditio.org/contact">Пишите нам!</a>
        </td>
      </tr>
      </table>
    <?}?>
    <div style="width=100%; padding: 0px 10px 4px 10px">

      <h1 style="margin-top: 0.2em"><?=$TITLE?></h1>
