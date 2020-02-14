<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>

<%
/* Cookie[] cookies = request.getCookies();
if(cookies!=null){
	for(int i=0;i<cookies.length;i++){
		if(cookies[i].getName().equals("memName")){
			cookies[i].setMaxAge(0);//쿠키삭제
			response.addCookie(cookies[i]);//클라이언트에게 보내기
		}else if(cookies[i].getName().equals("memId")){
			cookies[i].setMaxAge(0);
			response.addCookie(cookies[i]);
	}
	}
} */

session.removeAttribute("memName");
session.removeAttribute("memId");

session.invalidate();//모든 세션 없애기



%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
<script type="text/javascript">
window.onload=function(){
	alert("로그아웃되었습니다.");
	location.href='../main/index.jsp';
}


</script>
</head>
<body>

</body>
</html>