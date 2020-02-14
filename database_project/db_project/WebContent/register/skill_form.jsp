<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");

	Db_project db = Db_project.getInstance();
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
<div><a href='register.jsp'><img src='../image/hero.jpg' width="300" height="100" ></a></div>
	<form name="skillForm" method="post" action="skill_register.jsp">
	<h3>등록할 스킬의 정보를 입력하시오.</h3>
	<table border="1" cellpadding="3" cellspacing="0">
	
		<tr>
			<td>스킬명</td>
			<td><input type="text" name="new_skill" size="30" ></td>
		</tr>
		
		<tr>
			<td>부여 할 용사</td>
			<td>
			<select name="hero_id">
				<option value="없음">없음
				<%for(int i=0;i<total_count_heroes;i++){%>
					<option value=<%=heroes[i]%>><%=heroes[i]%>
				<%}%>
			</select>
			</td>
		</tr>
		
		<tr>
			<td>체력 증가량</td>
			<td><input type="text" name="hp_up" size="5" ></td>
		</tr>
		<tr>
			<td>마력 증가량</td>
			<td><input type="text" name="mp_up" size="5" ></td>
		</tr>
		
		<tr>
			<td colspan="2" align="center">
				<input type="submit" value="스킬등록">
				<input type="reset" value="다시작성">
			</td>
		</tr>
	</table>

</body>
</html>