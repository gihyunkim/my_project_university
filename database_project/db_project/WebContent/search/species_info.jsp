<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");
	String species_name = request.getParameter("species_name");	//skill name
	Db_project db = Db_project.getInstance();
	Species_table spt = db.getSpeciesInfo(species_name);
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
	<h1>종족 정보</h1>
<div><a href='./search.jsp'><img src='../image/hero.jpg' width="300" height="200" ></a><br><br></div>	
	<table border="1" cellpadding="3" cellspacing="0">
		<tr>
			<td colspan=7 align="center">종족</td>
		</tr>
		<tr align="center">
			<td>종족명</td>
			<td>공격력 보정치</td>
			<td>방어력 보정치</td>
			<td>체력 보정치</td>
			<td>마력 보정치</td>
			<td>힘 보정치</td>
			<td>지능 보정치</td>
		</tr>
		<tr align="center">
			<td><%=spt.getSpecies_name() %></td>
			<td><%=spt.getAttack_p_comp() %></td>
			<td><%=spt.getDefend_p_comp() %></td>
			<td><%=spt.getHp_comp() %></td>
			<td><%=spt.getMp_comp() %></td>
			<td><%=spt.getStr_comp() %></td>
			<td><%=spt.getInt_comp() %></td>
		</tr>
	</table>

	
</body>
</html>