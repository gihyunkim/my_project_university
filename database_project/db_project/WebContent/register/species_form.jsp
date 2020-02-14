<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");

	Db_project db = Db_project.getInstance();
	
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
<div><a href='register.jsp'><img src='../image/hero.jpg' width="300" height="100" ></a></div>
	<form name="speciesForm" method="post" action="species_register.jsp">
	<h3>등록할 종족의 정보를 입력하시오.</h3>
	<table border="1" cellpadding="3" cellspacing="0">
	
		<tr>
			<td>종족명</td>
			<td><input type="text" name="new_species" size="30" ></td>
		</tr>
		
		<tr>
			<td>공격력 보정치</td>
			<td><input type="text" name="attack_p_comp" size="5" ></td>
		</tr>
		<tr>
			<td>방어력 보정치</td>
			<td><input type="text" name="defend_p_comp" size="5" ></td>
		</tr>
		<tr>
			<td>체력 보정치</td>
			<td><input type="text" name="hp_comp" size="5" ></td>
		</tr>
		<tr>
			<td>마력 보정치</td>
			<td><input type="text" name="mp_comp" size="5" ></td>
		</tr>
		<tr>
			<td>힘 보정치</td>
			<td><input type="text" name="str_comp" size="5" ></td>
		</tr>
		<tr>
			<td>지능 보정치</td>
			<td><input type="text" name="int_comp" size="5" ></td>
		</tr>
		<tr>
			<td colspan="2" align="center">
				<input type="submit" value="종족 등록">
				<input type="reset" value="다시작성">
			</td>
		</tr>
	</table>

</body>
</html>