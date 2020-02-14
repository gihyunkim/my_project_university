<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");
	String skill_id = request.getParameter("skill_id");	//skill name
	Db_project db = Db_project.getInstance();
	Skill_table st = db.getSkillInfo(skill_id);
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
	<h1>스킬 정보</h1>
<div><a href='./search.jsp'><img src='../image/hero.jpg' width="300" height="200" ></a><br><br></div>	
	<table border="1" cellpadding="3" cellspacing="0">
		<tr>
			<td colspan=4 align="center">스킬</td>
		</tr>
		<tr align="center">
			<td>스킬명</td>
			<td>체력 증가치</td>
			<td>마력 증가치</td>
			<td>사용중인 용사</td>
		</tr>
		<tr align="center">
			<td><%=st.getSkill_id() %></td>
			<td><%=st.getHp_up() %></td>
			<td><%=st.getMp_up() %></td>
			<%if(st.getHero_id()!=null){ %>
				<td><a href='hero_info.jsp?hero_id=<%=st.getHero_id() %>'><%=st.getHero_id() %></a></td>
			<%} else{%>
				<td>없음</td>
			<%} %>
		</tr>
	</table>

	
</body>
</html>