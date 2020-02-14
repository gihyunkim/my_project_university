<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");

	Db_project db = Db_project.getInstance();
	String skill_id = request.getParameter("skill_id");
	Skill_table st = new Skill_table();
	st = db.getSkillInfo(skill_id);
	String heroes[] = db.getHeroes();	//부여 가능한 용사들
	int total_count_heroes = db.CntHeroes();
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
	<form name="skillModifyForm" method="post" action="skill_modify_db.jsp">
	<div><a href='modify.jsp'><img src='../image/hero.jpg' width="300" height="100" ></a><br><br></div>
	<%if(st.getSkill_id()!=null){ %>
	<h3>수정할 스킬의 정보를 입력하시오.</h3>
	<table border="1" cellpadding="3" cellspacing="0">
		<input type="hidden" name="old_owner" value=<%=st.getHero_id() %>>
		<input type="hidden" name="old_skill" value=<%=st.getSkill_id() %>>
		<tr>
			<td>스킬명</td>
			<td><input type="text" name="new_skill" size="30" value=<%=st.getSkill_id() %> ></td>
		</tr>
		
		<tr>
			<td>부여 할 용사</td>
			<td>
			<select name="hero_id">
				<%for(int i=0;i<total_count_heroes;i++){%>
					<option value=<%=heroes[i]%>><%=heroes[i]%>
				<%}%>
			</select>
			</td>
		</tr>
		
		<tr>
			<td>체력 증가량</td>
			<td><input type="text" name="hp_up" size="5" value=<%=st.getHp_up() %>></td>
		</tr>
		<tr>
			<td>마력 증가량</td>
			<td><input type="text" name="mp_up" size="5" value=<%=st.getMp_up() %> ></td>
		</tr>
		
		<tr>
			<td colspan="2" align="center">
				<input type="submit" value="스킬수정">
				<input type="reset" value="다시작성">
			</td>
		</tr>
	</table>
	<%}else{ %>
		<h3>존재하지 않는 스킬명입니다</h3>
	<%} %>

</body>
</html>