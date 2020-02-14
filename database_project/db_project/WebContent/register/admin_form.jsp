<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
<style>
	h3, div{
		text-align:center;
	}
	table{
		margin:auto
	}
</style>
</head>
<body>
	<form name="adminForm" method="post" action="admin_register.jsp">
	<h3>등록할 관리자 정보를 입력하시오.</h3>
	<div><a href='register.jsp'><img src='../image/hero.jpg' width="300" height="100" ></a><br><br></div>
	<table border="1" cellpadding="3" cellspacing="0">
	
		<tr>
			<td>id</td>
			<td><input type="text" name="id" size="30" ></td>
		</tr>
		
		<tr>
			<td>password</td>
			<td><input type="password" name="pwd" size="30" ></td>
		</tr>
		
		<tr>
			<td colspan="2" align="center">
				<input type="submit" value="관리자 등록">
				<input type="reset" value="다시작성">
			</td>
		</tr>
	</table>

</body>
</html>