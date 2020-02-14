<%@page import="poll.plBean.PollListBean"%>
<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<%@ page import= "java.util.Vector" %>
<jsp:useBean id="dao" class="poll.dao.PollMgr"/>
<%
	int num = 0;
	if(!(request.getParameter("num")==null || request.getParameter("num").equals(""))){
		num = Integer.parseInt(request.getParameter("num"));
	}
	out.println(num);
	PollListBean plBean = dao.getList(num);
	Vector <String> vlist = dao.getItem(num);
	
	String question = plBean.getQuestion();
	int type = plBean.getType();
	int active = plBean.getActive();

%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>Insert title here</title>
</head>
<body>
<form method="post" action="pollFormProc.jsp">
<input type="hidden" name="num" value="<%=num %>">
<table border="1" width="300">
<tr><tr><td colspan=2>Q : <%=question%></td>
</tr>
<tr>
<td colspan="2">
<%
for(int i=0; i<vlist.size();i++){
String itemList = vlist.get(i);
if(type==1){
	out.println("<input type=checkbox name='itemnum' value='"+i+"'>");
	}else{
	out.println("<input type=radio name='itemnum' value='"+i+"'>");
	}
	out.println(itemList+"<br>");
}
	%></td>
	</tr>
	<tr>
	<td>
	<%
	if(active==1){
		out.println("<input type='submit' value='투표'>");
		}else{
		out.println("투표");
	}
		%></td>
		<td>
		<input type="button" value="결과" onclick="javascript:window.open(
		'pollView.jsp?num=<%=num %>','PollView', 'width=500, height=350')">
		</td>
		</table>
		
		</form>


</body>
</html>