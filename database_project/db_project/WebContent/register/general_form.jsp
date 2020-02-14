<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");

	Db_project db = Db_project.getInstance();
	
	String [] rival= db.getAllSpecies();	//라이벌 = 모든 종족 중 하나
	int total_count_rival = db.CntAllSpecies();
	String [] army = db.getAllMonster();	//지휘할 몬스터
	int total_count_monster = db.CntAllMonsters();
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
	<form name="generalForm" method="post" action="general_register.jsp">
	<h3>등록할 마물장군의 정보를 입력하시오.</h3>
	<table border="1" cellpadding="3" cellspacing="0">
	
		<tr>
			<td>장군명</td>
			<td><input type="text" name="new_general" size="30" ></td>
		</tr>
		
		<tr>
			<td>나이</td>
			<td><input type="text" name="age" size="5" ></td>
		</tr>
		<tr>
			<td>공격력 보정치</td>
			<td><input type="text" name="army_attack_comp" size="5" ></td>
		</tr>
		<tr>
			<td>방어력 보정치</td>
			<td><input type="text" name="army_defense_comp" size="5" ></td>
		</tr>
		<tr>
			<td>이동력 보정치</td>
			<td><input type="text" name="army_loco_comp" size="5" ></td>
		</tr>
		<tr>
			<td>사기 보정치</td>
			<td><input type="text" name="army_moral_comp" size="5" ></td>
		</tr>
		
		<tr>
			<td>지휘할 군단</td>
			<td>
			<select name="army">
				<option value='없음'>없음
				<%for(int i=0;i<total_count_monster;i++){%>
					<option value=<%=army[i]%>><%=army[i]%>
				<%}%>
			</select>
			</td>
		</tr>
		
		<tr>
			<td>천적</td>
			<td>
			<select name="rival">
				<option value='없음'>없음
				<%for(int i=0;i<total_count_rival;i++){%>
					<option value=<%=rival[i]%>><%=rival[i]%>
				<%}%>
			</select>
			</td>
		</tr>
		
		
		
		<tr>
			<td colspan="2" align="center">
				<input type="submit" value="장군 등록">
				<input type="reset" value="다시작성">
			</td>
		</tr>
	</table>

</body>
</html>