<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("utf-8");
	String general_name = request.getParameter("general_name");
	Db_project db = Db_project.getInstance(); 
	String generals[] = db.getGeneralsTable(general_name);
	int total_cnt = db.getGeneralsCnt(general_name);
	
%>
<html>
<head>
<meta charset="utf-8">
<title>Insert title here</title>
<style>
	div, h1{
		text-align:center;
	}
	table{
		margin:auto;
	}

</style>
</head>
<body>
<h1> 군단 장군 검색 리스트</h1>
<div><a href='./search.jsp'><img src='../image/hero.jpg' width="300" height="200" ></a><br><br></div>
	<%if(total_cnt!=0){ %>
	<table border="1" cellpadding="3" cellspacing="0">
	<tr>
		<td>군단 장군 이름</td>
	</tr>
	<%for(int i=0;i<total_cnt;i++){ %>
		<tr align="center">
			<td><a href='../search/general_info.jsp?general_name=<%=generals[i]%>'><%=generals[i] %></a>	</td>
		</tr>
	<%} %>
	</table>
	<%}else{ %>
	<h1>존재하지 않는 군단 장군 이름입니다.</h1>
	<div><a href='search.jsp'>뒤로</a></div>
	<%} %>
</body>
</html>