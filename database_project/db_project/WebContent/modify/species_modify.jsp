<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");
	String species_name = request.getParameter("species_name");
	Db_project db = Db_project.getInstance();
	Species_table spt = new Species_table();
	spt = db.getSpeciesInfo(species_name);
	
%>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
<style>
	h3, div{
		text-align:center;
	}
	table{
		margin:auto
	}
</style>
</head>
<body>
	<form name="speciesModifyForm" method="post" action="species_modify_db.jsp">
	<div><a href='modify.jsp'><img src='../image/hero.jpg' width="300" height="100" ></a><br><br></div>
	<%if(spt.getSpecies_name()!=null){ %>
	<h3>수정할 종족의 정보를 입력하시오.</h3>
	<table border="1" cellpadding="3" cellspacing="0">
	<input type="hidden" name="species_name" value=<%=spt.getSpecies_name() %>>
		
		<tr>
			<td>공격력 보정치</td>
			<td><input type="text" name="attack_p_comp" size="5" value=<%=spt.getAttack_p_comp() %>></td>
		</tr>
		<tr>
			<td>방어력 보정치</td>
			<td><input type="text" name="defend_p_comp" size="5" value=<%=spt.getDefend_p_comp() %>></td>
		</tr>
		<tr>
			<td>체력 보정치</td>
			<td><input type="text" name="hp_comp" size="5" value=<%=spt.getHp_comp() %> ></td>
		</tr>
		<tr>
			<td>마력 보정치</td>
			<td><input type="text" name="mp_comp" size="5" value=<%=spt.getMp_comp() %>></td>
		</tr>
		<tr>
			<td>힘 보정치</td>
			<td><input type="text" name="str_comp" size="5"  value=<%=spt.getStr_comp() %>></td>
		</tr>
		<tr>
			<td>지능 보정치</td>
			<td><input type="text" name="int_comp" size="5" value=<%=spt.getInt_comp() %>></td>
		</tr>
		<tr>
			<td colspan="2" align="center">
				<input type="submit" value="종족 수정">
				<input type="reset" value="다시작성">
			</td>
		</tr>
	</table>
	<%}else{ %>
		<h3>존재하지 않는 종족명입니다.</h3>
	<%} %>

</body>
</html>