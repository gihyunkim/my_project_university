<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="member.*" %>
<!DOCTYPE html>
<%
	Db_project db = Db_project.getInstance();
	double status[] =db.totalArmyStatus();
	status[0] = Math.round(status[0]*1000.0)/1000.0;
	status[1] = Math.round(status[1]*1000.0)/1000.0;
	int total_army_cnt = db.CntTotalNumOfMonsters();
	int command_cnt = db.CntCommand();
	String general[] = db.current_command_general();
	String army[] = db.current_command_army();
	
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
	<h3><b>한 군단의 최종 공격력 = 보정된 총 공격력 + 6*보정된 이동력 </b></h3>
	<h3><b>한 군단의 최종 방어력 = 보정된 총 방어력 + 5*보정된 사기</b></h3>
	<br>
	<table border="1" cellpadding="3" cellspacing="0">
		<tr>
			<td colspan=3>현재 마물군단 상황</td>
		</tr>
		<tr>
			<td>총 수</td>
			<td>총 공격력</td>
			<td>총 방어력</td>
		</tr>
		<tr>
			<td><%=total_army_cnt %></td>
			<td><%=status[0] %></td>
			<td><%=status[1] %></td>
		</tr>
	</table>
	<br>
	<table border="1" cellpadding="3" cellspacing="0">
		<tr>
			<td colspan=<%=command_cnt %>>현재 지휘 상황</td>
		</tr>
		<tr>
			<%for(int i=0;i<command_cnt;i++){ %>
				<td><a href='../search/general_info.jsp?general_name=<%=general[i]%>'><%=general[i] %></a></td>
			<%} %>
		</tr>
		<tr>
			<%for(int j=0;j<command_cnt;j++){ %>
				<td><a href='../search/monster_info.jsp?army_name=<%=army[j]%>'><%=army[j]%></a></td>
			<%} %>
		</tr>
	</table>
</body>
</html>