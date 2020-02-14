<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");
	String general_name = request.getParameter("general_name");
	Db_project db = Db_project.getInstance();
	
	General_table gt = new General_table();
	gt = db.getGeneralInfo(general_name);
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
	<form name="generalModifyForm" method="post" action="general_modify_db.jsp">
	<div><a href='modify.jsp'><img src='../image/hero.jpg' width="300" height="100" ></a><br><br></div>
	<%if(gt.getGeneral_name()!=null){ %>
	<h3>수정할 마물장군의 정보를 입력하시오.</h3>
	<input type=hidden name=general_name value=<%=gt.getGeneral_name() %>>
	<table border="1" cellpadding="3" cellspacing="0">
		<tr>
			<td>나이</td>
			<td><input type="text" name="age" size="5" value=<%=gt.getAge() %>></td>
		</tr>
		<tr>
			<td>공격력 보정치</td>
			<td><input type="text" name="army_attack_comp" size="5" value=<%=gt.getArmy_attack_comp() %>></td>
		</tr>
		<tr>
			<td>방어력 보정치</td>
			<td><input type="text" name="army_defense_comp" size="5" value=<%=gt.getArmy_defense_comp() %>></td>
		</tr>
		<tr>
			<td>이동력 보정치</td>
			<td><input type="text" name="army_loco_comp" size="5" value=<%=gt.getArmy_loco_comp() %>></td>
		</tr>
		<tr>
			<td>사기 보정치</td>
			<td><input type="text" name="army_moral_comp" size="5" value=<%=gt.getArmy_moral_comp() %>></td>
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
				<input type="submit" value="장군 수정">
				<input type="reset" value="다시작성">
			</td>
		</tr>
	</table>
	<%}else{ %>
		<h3>존재하지 않는 마물 장군명입니다.</h3>
	<%} %>

</body>
</html>