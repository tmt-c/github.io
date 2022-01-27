<%@ page language="java" contentType="text/html; charset=UTF-8"
 pageEncoding="UTF-8"%>
<%@ page import="db.Book, java.util.List" %>
<%
List<Book> bookList = (List<Book>)request.getAttribute("list");
%>
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
<h1><a href="BookServlet">書籍DB</a></h1>

<hr>
<h3>並び替え</h3>
<form action="BookServlet" method="POST">
<input type="radio" name="item" value="ID" checked="checked">ID
<input type="radio" name="item" value="発行年">発行年
<input type="radio" name="item" value="価格">価格
<input type="radio" name="item" value="評価">評価
<br>
<input type="radio" name="order" value="asc" checked="checked">昇順
<input type="radio" name="order" value="desc">降順
<br>
<input type="submit" name="submit" value="並び替え">
<hr>
<h3>条件を指定</h3>
電子対応<br>
<input type="radio" name="search_d" value="なし">なし
<input type="radio" name="search_d" value="あり">あり
<br>ジャンル<br>
<select name="search_g">
<option value="アクション">アクション
<option value="絵本">絵本
<option value="攻略">攻略
<option value="推理">推理
<option value="歴史">歴史
<option value="SF">SF
</select>
<br><input type="submit" name="submit" value="検索">

<hr>
<h3>登録する</h3>
書籍名<input type="text" name="newtitle">
著者名<input type="text" name="newname"><br>
発行年<input type="text" name="newdate">
ジャンル
<select name="newgenre">
<option value="アクション">アクション
<option value="絵本">絵本
<option value="攻略">攻略
<option value="推理">推理
<option value="歴史">歴史
<option value="SF">SF
</select><br>
価格<input type="text" name="newprice">
評価<select name="newpoint">
<option>5<option>4<option>3<option>2<option>1
</select>
電子対応<select name="newdenshi">
<option>あり<option>なし
</select><br>
<input type="submit" name="submit" value="登録">

<hr>
<h3>削除する</h3>
削除するデータのID
<input type="text" name="deleteid">
<input type="submit" name="submit" value="削除">
</form>

<hr>
<% if (bookList != null) { %>
書籍情報
<table border="1">
<tr><th>ID</th><th>書籍名</th><th>著者名</th><th>発行年</th><th>ジャンル</th><th>価格</th><th>評価</th><th>電子対応</th></tr>
<% for (Book book: bookList) { %>
<tr>
<td><%=book.getId() %></td>
<td><%=book.getTitle() %></td>
<td><%=book.getName() %></td>
<td><%=book.getDate() %></td>
<td><%=book.getGenre() %></td>
<td><%=book.getPrice() %></td>
<td><%=book.getPoint() %></td>
<td><%=book.getDenshi() %></td>
</tr>
<% } %>
</table>
<% } %>
</body>
</html>