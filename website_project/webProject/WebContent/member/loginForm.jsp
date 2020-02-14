<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<script type="text/javascript">
function checkLogin(){
	if(document.loginForm.id.value=="")
		alert("아이디를 입력해주세요...");
	else if(document.loginForm.pwd.value=="")
		alert("비밀번호를 입력해주세요...");
	else
		document.loginForm.submit();
}


</script>
<title>Insert title here</title>
</head>
<body>
<h2><img src="../image/site_name.jpg" width="189" height="57" style="cursor:pointer"
onclick="location.href='../main/index.jsp'"> <small>Experience Site</small></h2>
<h3>로그인</h3>
<form name="loginForm" method="post" action="login.jsp">
	<table border="1" cellpadding="3" cellspacing="0">
		
		<tr>
		<td>아이디</td>
		<td><input type="text" name="id" size="10"></td>
		</tr>
		
		<tr>
		<td>비밀번호</td>
		<td><input type="password" name="pwd" size="30"></td>
		</tr>
		
		<tr >
		<td colspan="2" align="center">
		<input type="button" onclick="javascript:checkLogin()" value="로그인">
		<input type="button" value="회원가입" onclick="javascript:location.href='writeForm.jsp'">
		</td>
		</tr>

	</table>
	</form>
</body>
</html>