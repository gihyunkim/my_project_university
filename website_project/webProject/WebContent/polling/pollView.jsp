<%@page import="poll.plBean.PollListBean"%>
<%@page import="poll.piBean.PollItemBean"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<%@ page import="java.util.*" %>
<jsp:useBean id="dao" class="poll.dao.PollMgr"/>
<%
request.setCharacterEncoding("utf-8");
int num= 0;
if(request.getParameter("num")!=null){
	num=Integer.parseInt(request.getParameter("num"));
}
int sum = dao.sumCount(num);
Vector<PollItemBean> vlist = dao.getView(num);
PollListBean plBean = dao.getList(num);
String question = plBean.getQuestion();
Random r = new Random();

%>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
<div align="center">
<table border="1" width="400">
<tr>
<td colspan="4"><b>Q:<%=question %></b></td>
</tr>
<tr>
	<td colspan="3"><b>총 투표자:<%=sum %>명</b></td>
	<td width="40">count</td>
</tr>
<%
for(int i=0;i< vlist.size();i++){
	PollItemBean piBean = vlist.get(i);
	String[] item = piBean.getItem();
	int rgb = r.nextInt(255*255*255);
	String rgbt = Integer.toHexString(rgb);
	String hRGB = "#" +rgbt;
	int count = piBean.getCount();
	int ratio = (new Double (Math.ceil((double) count/sum*100))).intValue();
%>
	<tr>
	<td width="20" align="center"><%=i+1%></td>
	<td width="120"><%=item[0] %></td>
			<td>
				<table width="<%=ratio %>" height="15">
					<tr>
						<td bgcolor="<%=hRGB %>"></td>
					</tr>
				</table>
			</td>
			<td width="40"><%=count%></td>
	</tr>
<%
}
%>
</table>	
<p />	
</div>
</body>
</html>