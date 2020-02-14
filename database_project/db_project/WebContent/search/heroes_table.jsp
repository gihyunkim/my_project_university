<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");
	String hero_id = request.getParameter("hero_id");
	Db_project db = Db_project.getInstance(); 
	String heroes[] = db.getHeroTable(hero_id);
	int total_cnt = db.getHeroCnt(hero_id);
	
%>
<html>
<head>
<meta charset="UTF-8">
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
<h1> 용사 검색 리스트</h1>
<div><a href='./search.jsp'><img src='../image/hero.jpg' width="300" height="200" ></a><br><br></div>
	<%if(total_cnt!=0){ %>
	<table border="1" cellpadding="3" cellspacing="0">
	<tr>
		<td>용사 id</td>
	</tr>
	<%for(int i=0;i<total_cnt;i++){ %>
		<tr align="center">
			<td><a href='hero_info.jsp?hero_id=<%=heroes[i] %>'><%=heroes[i] %></a>	</td>
		</tr>
	<%} %>
	</table>
	<%}else{ %>
		<h1>존재하지 않는 용사 id 입니다.</h1>
		<div><a href='search.jsp'>뒤로</a></div>
	<%} %>
</body>
</html>