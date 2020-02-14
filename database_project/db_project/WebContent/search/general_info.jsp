<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("utf-8");
	String general_name = request.getParameter("general_name");	//general name
	Db_project db = Db_project.getInstance();
	General_table gt = db.getGeneralInfo(general_name);
	

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
	<h1>몬스터 장군 정보</h1>
<div><a href='./search.jsp'><img src='../image/hero.jpg' width="300" height="200" ></a><br><br></div>	
	<table border="1" cellpadding="3" cellspacing="0">
		<tr>
			<td colspan=7 align="center">몬스터 장군</td>
		</tr>
		<tr align="center">
			<td>장군명</td>
			<td>나이</td>
			<td>공격력 보정치</td>
			<td>방어력 보정치</td>
			<td>이동력 보정치</td>
			<td>사기 보정치</td>
			<td>천적</td>
		</tr>
		<tr align="center">
			<td><%=gt.getGeneral_name() %></td>
			<td><%=gt.getAge() %></td>
			<td><%=gt.getArmy_attack_comp() %></td>
			<td><%=gt.getArmy_defense_comp() %></td>
			<td><%=gt.getArmy_moral_comp()%></td>
			<td><%=gt.getArmy_loco_comp() %></td>
			<td><a href='species_info.jsp?species_name=<%=gt.getRival()%>'><%=gt.getRival() %></a></td>
		</tr>
	</table>

	
</body>
</html>