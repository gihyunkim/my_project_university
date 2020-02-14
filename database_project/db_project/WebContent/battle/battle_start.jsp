<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("utf-8");
	String heroes[] = request.getParameterValues("heroes");
	String army = request.getParameter("army");
	Db_project db = Db_project.getInstance();
	Monster_table mt = new Monster_table();
	double total_status[] = db.getBattledHeroAttack(heroes, army);
	mt = db.army_applied_comp(army);


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
		text-align:center;
		margin:auto;
	}


</style>
</head>
<body>
	<h1>배틀 시뮬레이션</h1>
	<%if((total_status[0]>mt.getArmy_total_defense())&&
			(mt.getArmy_total_attack()>total_status[1])){ %> <!-- 전멸 -->
	<div><a href='../main.jsp'><img src='../image/death_all.png' width="500" height="300" ></a><br><br></div>
		<h1>모두 전멸하였습니다....</h1>
	<%} else if((total_status[0]<mt.getArmy_total_defense())&&
	(mt.getArmy_total_attack()<total_status[1])){%>	<!-- 무승부 -->
	<div><a href='../main.jsp'><img src='../image/death_all.png' width="500" height="300" ></a><br><br></div>
		<h1>무승부입니다...!</h1>
	<%}else if(total_status[0]>mt.getArmy_total_defense()){%>
	<div><a href='../main.jsp'><img src='../image/hero_win2.png' width="500" height="300" ></a><br><br></div>
		<h1>용사들이 승리하였습니다!!!</h1>
	<%}else if(mt.getArmy_total_attack()>total_status[1]){%>
	<div><a href='../main.jsp'><img src='../image/hero_die.jpg' width="500" height="300" ></a><br><br></div>
		<h1>용사들이 마물군단에게 당했습니다....!</h1>
	<%}else{ %>
		<h1>오류발생!!</h1>
	<%} %>
	
	<table border=1 cellpadding=3 cellspacing=0>
		<tr>
			<td colspan="4">시뮬레이션 결과</td>
		</tr>
		<tr>
			<td>용사들 총 공격력</td>
			<td>용사들 총 방어력</td>
			<td>마물 군단 총 공격력</td>
			<td>마물 군단 총 방어력</td>
		</tr>
		<tr>
			<td><%=Math.round(total_status[0]*1000.0)/1000.0 %></td>
			<td><%=Math.round(total_status[1]*1000.0)/1000.0 %></td>
			<td><%=Math.round(mt.getArmy_total_attack()*1000.0)/1000.0 %></td>
			<td><%=Math.round(mt.getArmy_total_defense()*1000.0)/1000.0 %></td>
		</tr>
	</table>
</body>
</html>