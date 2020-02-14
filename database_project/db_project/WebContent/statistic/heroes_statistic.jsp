<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="member.*" %>
<!DOCTYPE html>
<%
	Db_project db = Db_project.getInstance();
	double status[] =db.totalHeroStatus();
	status[0] = Math.round(status[0]*1000.0)/1000.0;
	status[1] = Math.round(status[1]*1000.0)/1000.0;
	int total_hero_cnt = db.CntAllHeroes();
	String species[] = db.getAllSpecies();
	int total_species_cnt = db.CntAllSpecies();
	int[] species_current = db.current_species();


%>
<html>
<head>
<meta charset="utf-8">
<title>Insert title here</title>
<style>
	div, table,h3{
		text-align:center;
	}
	table{
		margin:auto
	}
</style>
</head>
<body>
<div><a href='../main.jsp'><img src='../image/hero.jpg' width="300" height="200" ></a><br><br></div>
	<h3><b>한 용사의 최종 공격력 = 보정된 공격력 + 3*보정된 힘+4*보정된 지능+2*보정된 마력</b></h3>
	<h3><b>한 용사의 최종 방어력 = 보정된 체력 + 3*보정된 방어력</b></h3>
	<br>
	<table border="1" cellpadding="3" cellspacing="0">
		<tr>
			<td colspan=3>현재 용사 상황</td>
		</tr>
		<tr>
			<td>총 수</td>
			<td>총 공격력</td>
			<td>총 방어력</td>
		</tr>
		<tr>
			<td><%=total_hero_cnt %></td>
			<td><%=status[0] %></td>
			<td><%=status[1] %></td>
		</tr>
	</table>
	<br>
	<table border="1" cellpadding="3" cellspacing="0">
		<tr>
			<td colspan=<%=total_species_cnt %>>종족별 현황</td>
		</tr>
		<tr>
			<%for(int i=0;i<total_species_cnt;i++){ %>
				<td><%=species[i] %></td>
			<%} %>
		</tr>
		<tr>
			<%for(int i=0;i<total_species_cnt;i++){ %>
				<td><%=species_current[i] %>명</td>
			<%} %>
		</tr>
		
	</table>
</body>
</html>