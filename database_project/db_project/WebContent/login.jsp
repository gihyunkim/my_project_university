<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.Db_project"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");
	String id = request.getParameter("id");
	String pwd = request.getParameter("pwd");
	Db_project db = Db_project.getInstance();
	pwd = db.encryptPwd(pwd);
	String aid = db.check_login(id, pwd);
	
	
	if(aid!=null){
		session.setAttribute("memId", id);
	}
%>

<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
<style>
	div{
		text-align: center;
	}


</style>
</head>
<body>
<%if(aid==null) {%>
잘못된 아이디 또는 비밀번호 입니다.
<a href="loginForm.jsp">돌아가기</a>
<%}else{%>
<div><h1>로그인에 성공하였습니다!!</h1></div>
<div><a href="main.jsp">홈으로</a></div>
<%} %>

</body>
</html>