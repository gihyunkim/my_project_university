<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="member.*" %>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");
	String general_name = request.getParameter("general_name");
	int check = 0;
	Db_project db = Db_project.getInstance();
	check = db.delete_general(general_name);

%>
<html>
<head>
<meta charset="utf-8">
<title>Insert title here</title>
<style>
	h3, div{
		text-align:center;
	}
</style>
</head>
<body>
<div><a href='delete.jsp'><img src='../image/hero.jpg' width="400" height="200" ></a><br><br></div>
	<%if(check==1) {%>
	<h3>마물장군 삭제에 성공하였습니다</h3>
	<div><a href='../main.jsp'>홈으로</a></div>
	<%}else {%>
	<h3>마물장군 삭제에 실패하였습니다...</h3>
	<div><a href='../main.jsp'>홈으로</a></div>
	<%} %>
</body>
</html>