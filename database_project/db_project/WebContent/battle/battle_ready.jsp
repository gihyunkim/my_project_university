<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="member.*"%>
<!DOCTYPE html>
<%
	Db_project db = Db_project.getInstance();
	String heroes[] = db.getAllHeroes();
	int count_hero = db.CntAllHeroes();
	String army[] = db.getAllMonster();
	int count_army = db.CntAllMonsters();
%>
<html>
<head>
<meta charset="utf-8">
<title>Insert title here</title>
<style>
	div, h3{
		text-align: center;
	}
	table{
		text-align:center;
		margin:auto;
	}

</style>
</head>
<body>
<form name=battle method=post action="battle_start.jsp">
<div><a href='../main.jsp'><img src='../image/hero.jpg' width="500" height="300" ></a><br><br></div>
	<%if((count_hero!=0) | (count_army!=0)){ %>
	<table border="1" cellpadding="3" cellspacing="0">
		<tr>
			<td>출격할 용사 선택</td>
		</tr>
		<tr>
			<td>
				<%for(int i=0;i<count_hero;i++){ %>
					<input type="checkbox" name="heroes" value=<%=heroes[i] %>><%=heroes[i] %>
				<%} %>
			</td>
		</tr>
		<tr>
			<td>섬멸할 마물 선택</td>
		</tr>
		<tr>
			<td>
				<select name="army">
				<%for(int i=0;i<count_army;i++){ %>
					<option value=<%=army[i] %>><%=army[i] %>
				<%} %>
				</select>
			</td>
		</tr>
		
		<tr>
			<td><input type=submit 	value="배틀시작"></td>
		</tr>
	</table>
	<%}else{ %>
		<h1>출격할 용사 또는 섬멸할 마물이 없습니다.</h1>
		<div><a href='../main.jsp'>홈으로</a></div>
	<%} %>
	</form>
</body>
</html>