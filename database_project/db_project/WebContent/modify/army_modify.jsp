<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");
	String army_name = request.getParameter("army_name");
	Db_project db = Db_project.getInstance();
	Monster_table mt = new Monster_table();
	mt = db.getMonsterInfo(army_name);
	String generals[] = db.getAllGeneral();
	int total_count = db.CntAllGeneral();
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
	<form name="monsterModifyForm" method="post" action="army_modify_db.jsp">
	<div><a href='modify.jsp'><img src='../image/hero.jpg' width="300" height="100" ></a><br><br></div>
	<%if(mt.getArmy_name()!=null){ %>
	<h3>수정할 마물군단의 정보를 입력하시오.</h3>
	<table border="1" cellpadding="3" cellspacing="0">
		<input type="hidden" name="army_name" value=<%=mt.getArmy_name() %>>
		<tr>
			<td>소속 몬스터 수</td>
			<td><input type="text" name="num_monster" size="5" value=<%=mt.getNum_monster() %>></td>
		</tr>
		<tr>
			<td>지휘 할 장군</td>
			<td>
			<select name="general_name">
				<%for(int i=0;i<total_count;i++){%>
					<option value=<%=generals[i]%>><%=generals[i]%>
				<%}%>
			</select>
			</td>
		</tr>
		<tr>
			<td>총 공격력</td>
			<td><input type="text" name="total_attack" size="5" value=<%=mt.getTotal_attack() %> ></td>
		</tr>
		<tr>
			<td>총 방어력</td>
			<td><input type="text" name="total_defense" size="5" value=<%=mt.getTotal_defense() %> ></td>
		</tr>
		<tr>
			<td>이동력</td>
			<td><input type="text" name="locomotive" size="5" value=<%=mt.getLocomotive() %>></td>
		</tr>
		<tr>
			<td>사기</td>
			<td><input type="text" name="moral" size="5" value=<%=mt.getMoral() %>></td>
		</tr>
		
		<tr>
			<td colspan="2" align="center">
				<input type="submit" value="마물군단  수정">
				<input type="reset" value="다시작성">
			</td>
		</tr>
	</table>
	<%}else{ %>
		<h3>존재하지 않는 마물 군단명입니다.</h3>
	<%} %>
</body>
</html>