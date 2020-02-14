<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<jsp:useBean id="dao" class="poll.dao.PollMgr"/>
<% 
request.setCharacterEncoding("utf-8");
int num = Integer.parseInt(request.getParameter("num"));
String [] itemnum = request.getParameterValues("itemnum");
boolean flag = dao.updatePoll(num, itemnum);
String msg = "poll is not able to be registered!!";
if(flag){
	msg = "poll is registered!!";
}
%>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<script>
	alert("<%=msg%>");
	location.href="pollList.jsp?num=<%=num%>";
</script>

<title>Insert title here</title>
</head>
<body>

</body>
</html>