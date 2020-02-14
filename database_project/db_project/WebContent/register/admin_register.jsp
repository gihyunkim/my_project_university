<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<%
	request.setCharacterEncoding("UTF-8");
	Db_project db = Db_project.getInstance();
	String id = request.getParameter("id");
	int check=0;
	String pwd = request.getParameter("pwd");
	pwd = db.encryptPwd(pwd);
	check = db.RegisterAdmin(id, pwd);
%>
<html>
<head>
<meta charset="utf-8">
<title>Insert title here</title>
<style>
	h1, div{
		text-align:center;
	}
</style>
</head>
<body>
<div><a href='register.jsp'><img src='../image/hero.jpg' width="300" height="200" ></a><br><br></div>
	<%if(check==1) {%>
		<h1>관리자 등록에 성공하였습니다.</h1>
		<div><a href='../main.jsp'>홈으로</a></div>
	<%}else {%>
		<h1>관리자 등록에 실패하였습니다.</h1>
		<div><a href='../main.jsp'>홈으로</a></div>
	<%} %>
</body>
</html>