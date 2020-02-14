<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<!DOCTYPE html>
<%
	String memId= (String)session.getAttribute("memId");

%>
<html>
<head>
<meta charset="utf-8">
<title>용사 정보 입력</title>
<style>
	h1, b, div{
		text-align:center;
	}
</style>
</head>
<body>
<h1>게임 정보</h1>
<div><a href='../main.jsp'><img src='../image/hero.jpg' width="300" height="100" ></a><br><br></div>
<%if(memId!=null){ %>
<form name="admin_info" method="post" action="admin_search.jsp">
<div><b>관리자 정보</b>&nbsp;&nbsp;<input type="text" name="id"  size=30 placeholder="관리자  id입력">&nbsp;<input type="submit" value="검색"></div>
</form>
<br>
<%} %>
<form name="hero_info" method="post" action="heroes_table.jsp">
<div><b>용사 정보</b>&nbsp;&nbsp;<input type="text" name="hero_id"  size=30 placeholder="용사  id입력">&nbsp;
<input type="submit" value="검색"></div>
</form>
<br>
<form name="skill_info" method="post" action="skills_table.jsp">
<div><b>스킬 정보</b>&nbsp;&nbsp;<input type="text" name="skill_id" size=30 placeholder="스킬 이름입력">&nbsp;
<input type="submit" value="검색"></div>
</form>
<br>
<form name="species_info" method="post" action="species_table.jsp">
<div><b>종족 정보</b>&nbsp;&nbsp;<input type="text" name="species_name" size=30 placeholder="종족 이름입력">&nbsp;
<input type="submit" value="검색"></div>
</form>
<br>
<form name="item_info" method="post" action="items_table.jsp">
<div><b>아이템 정보</b>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="text" name="item_id" size=30 placeholder="아이템 이름입력">&nbsp;
<input type="submit" value="검색"></div>
</form>
<br>
<form name="monster_info" method="post" action="monsters_table.jsp">
<div><b>마물군단 정보</b>&nbsp;&nbsp;<input type="text" name="army_name" size=30 placeholder="마물군단 이름입력">&nbsp;
<input type="submit" value="검색"></div>
</form>
<br>
<form name="general_info" method="post" action="generals_table.jsp">
<div><b>마물장군 정보</b>&nbsp;&nbsp;<input type="text" name="general_name" size=30 placeholder="마물장군 이름입력">&nbsp;
<input type="submit" value="검색"></div>
</form>
<br>


</body>
</html>