<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");
	String hero_id = request.getParameter("hero_id");
	Db_project db = Db_project.getInstance();
	Hero_table ht1 = db.getHeroInfo(hero_id);
	Hero_table ht2 = db.applied_comp(hero_id);

%>
<html>
<head>
<meta charset=UTF-8>
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
	<h1>용사 정보</h1>
<div><a href='./search.jsp'><img src='../image/hero.jpg' width="300" height="200" ></a><br><br></div>	
	<table border="1" cellpadding="3" cellspacing="0">
		<tr>
			<td colspan=4 align="center">용사</td>
		</tr>
		<tr align="center">
			<td>이름</td>
			<td>나이</td>
			<td>출생지</td>
			<td>종족</td>
		</tr>
		<tr align="center">
			<td><%=ht1.getName() %></td>
			<td><%=ht1.getAge() %></td>
			<td><%=ht1.getHometown() %></td>
			<td><a href='species_info.jsp?species_name=<%=ht1.getSpecies() %>'><%=ht1.getSpecies() %></a></td>
		</tr>
	</table>

	<table border="1" cellpadding="3" cellspacing="0">
		<tr>
			<td colspan=6 align="center"> status </td>
		</tr>
		<tr align="center">
			<td>공격력</td>
			<td>방어력</td>
			<td>체력</td>
			<td>마력</td>
			<td>힘</td>
			<td>지능</td>
		</tr>
		<tr align="center">	
			<td><%=ht1.getAttack_p() %></td>
			<td><%=ht1.getDefend_p() %></td>
			<td><%=ht1.getHp() %></td>
			<td><%=ht1.getMp() %></td>
			<td><%=ht1.getStr()%></td>
			<td><%=ht1.getIntel() %></td>
		</tr>
	</table>
	
	<table border="1" cellpadding="3" cellspacing="0">
		<tr>
			<td colspan=6 align="center">보정된 status</td>
		</tr>
		<tr align="center">
			<td><a href='showCompAttack.jsp?hero_id=<%=hero_id%>'>보정된 공격력</a></td>
			<td><a href='showCompDefense.jsp?hero_id=<%=hero_id %>'>보정된 방어력</a></td>
			<td><a href='showCompHp.jsp?hero_id=<%=hero_id %>'>보정된 체력</a></td>
			<td><a href='showCompMp.jsp?hero_id=<%=hero_id %>'>보정된 마력</a></td>
			<td><a href='showCompStr.jsp?hero_id=<%=hero_id %>'>보정된  힘</a></td>
			<td><a href='showCompInt.jsp?hero_id=<%=hero_id %>'>보정된 지능</a></td>
		</tr>
		<tr align="center">
			<td><%=ht2.getTotal_attack() %></td>
			<td><%=ht2.getTotal_defense() %></td>
			<td><%=ht2.getTotal_hp() %></td>
			<td><%=ht2.getTotal_mp() %></td>
			<td><%=ht2.getTotal_str() %></td>
			<td><%=ht2.getTotal_int() %></td>
		</tr>
	</table>
</body>
</html>