<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");
	String army_name = request.getParameter("army_name");	//skill name
	Db_project db = Db_project.getInstance();
	Monster_table mt = db.getMonsterInfo(army_name);
	Monster_table mt2 = db.army_applied_comp(army_name);
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
	<h1>몬스터 군단 정보</h1>
<div><a href='./search.jsp'><img src='../image/hero.jpg' width="300" height="200" ></a><br><br></div>	
	<table border="1" cellpadding="3" cellspacing="0">
		<tr>
			<td colspan=6 align="center">몬스터 군단</td>
		</tr>
		<tr align="center">
			<td>군단명</td>
			<td>총 병력</td>
			<td>총 공격력</td>
			<td>총 방어력</td>
			<td>이동력</td>
			<td>사기</td>
		</tr>
		<tr align="center">
			<td><%=mt.getArmy_name() %></td>
			<td><%=mt.getNum_monster() %></td>
			<td><%=mt.getTotal_attack() %></td>
			<td><%=mt.getTotal_defense() %></td>
			<td><%=mt.getLocomotive()%></td>
			<td><%=mt.getMoral() %></td>
		</tr>
	</table>
	
	<table border="1" cellpadding="3" cellspacing="0">
		<tr>
			<td colspan=4 align="center">보정된 status</td>
		</tr>
		<tr align="center">
			<td>보정된 총 공격력</td>
			<td>보정된 총 방어력</td>
			<td>보정된 이동력</td>
			<td>보정된 사기</td>
		</tr>
		<tr align="center">
			<td><%=mt2.getArmy_total_attack() %></td>
			<td><%=mt2.getArmy_total_defense() %></td>
			<td><%=mt2.getArmy_total_loco()%></td>
			<td><%=mt2.getArmy_total_moral() %></td>
		</tr>
	</table>

	
</body>
</html>