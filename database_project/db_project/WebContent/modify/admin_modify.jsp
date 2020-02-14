<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="member.*" %>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");
	String id = request.getParameter("id");
	Db_project db =Db_project.getInstance();
	String admin[] = db.getAdminInfo(id);

%>
<html>
<head>
<meta charset="utf-8">
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
<form name="adminModifyForm" method="post" action="admin_modify_db.jsp">
<div><a href='modify.jsp'><img src='../image/hero.jpg' width="300" height="100" ></a><br><br></div>
<%if(admin[0]!=null) {%>
	<h3>수정할 관리자 정보를 입력하시오.</h3>
	<input type="hidden" name="old_id" value=<%=admin[0] %>>
	<table border="1" cellpadding="3" cellspacing="0">
		<tr>
			<td>id</td>
			<td><input type="text" name="id" size="5" value=<%=admin[0] %>></td>
		</tr>

		<tr>
			<td>pwd</td>
			<td><input type="password" name="pwd" size="30"></td>
		</tr>
		
		<tr>
			<td colspan="2" align="center">
				<input type="submit" value="관리자  수정">
				<input type="reset" value="다시작성">
			</td>
		</tr>
	</table>
<%}else{%>
	<h3>존재하지 않는 관리자 id입니다</h3>
	<%} %>
</body>
</html>