<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");
	String old_id = request.getParameter("old_id");
	int check=0;
	String id = request.getParameter("id");
	String pwd = request.getParameter("pwd");
	Db_project db =Db_project.getInstance();
	pwd = db.encryptPwd(pwd);
	check = db.modifyAdmin(old_id, id, pwd);
	

%>
<html>
<head>
<meta charset="utf-8">
<title>Insert title here</title>
</head>
<body>
	<%if(check==1){ %>
		관리자 수정에 성공하였습니다.
		<a href='../main.jsp'>홈으로</a>
	<%}else{ %>
		관리자 수정에 실패하였습니다.
		<a href='../main.jsp'>홈으로</a>
	<%} %>

</body>
</html>