<%@page import="java.util.Date" %>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
<style>
		h3{
			text-align:center;
		}
		table, div{
			margin:auto;
			text-align:center;
		}
</style>
</head>
<body>
<h3>로그인</h3>
<form name="loginForm" method="post" action="login.jsp">
	<div><a href='main.jsp'><img src='./image/hero.jpg' width="500" height="300" ></a><br><br></div>
	<table border="1" cellpadding ="3" cellspacing="0">
		<tr>
		<td>아이디</td>
		<td><input type="text" name="id" size="30"></td>
		</tr>
		
		<tr>
		<td>비밀번호</td>
		<td><input type="password" name="pwd" size="30"></td>
		</tr>
		
		<tr>
		<td colspan="2" align="center">
		<input type="submit" value="로그인">
		<input type="reset" value="다시입력">
		
		</td>
		</tr>
	</table>
	
</form>

</body>
</html>