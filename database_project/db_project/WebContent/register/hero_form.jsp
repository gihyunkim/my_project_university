<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");

	Db_project db = Db_project.getInstance();
	String species[] = db.getAllSpecies();
	int total_count = db.CntAllSpecies();
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
	<form name="heroForm" method="post" action="hero_register.jsp">
	<h3>등록할 용사의 정보를 입력하시오.</h3>
	<table border="1" cellpadding="3" cellspacing="0">
	
		<tr>			
			<td>아이디</td>
			<td><input type="text" name="id" size="30" ></td>
		</tr>
		
		<tr>			
			<td>비밀번호</td>
			<td><input type="password" name="pwd" size="30" ></td>
		</tr>
		
		<tr>			
			<td>이름</td>
			<td><input type="text" name="name" size="5" placeholder="이름입력"></td>
		</tr>
		
		<tr>
			<td>나이</td>
			<td><input type="text" name="age" size="5" ></td>
		</tr>
		
		<tr>
			<td>출생지</td>
			<td>
			<select name="hometown">
				<option value="treon">treon
				<option value="swamp of hell">swamp of hell
				<option value="elf's forest">elf's forest
				<option value="giant island">giant island
				<option value="darkness of fort">darkness of fort
			</select>
			</td>
		</tr>
		
		<tr>
			<td>종족</td>
			<td>
			<select name="species">
				<%for(int i=0;i<total_count;i++){%>
					<option value=<%=species[i]%>><%=species[i]%>
				<%}%>
			</select>
			</td>
		</tr>
		<tr>
			<td>공격력</td>
			<td><input type="text" name="attack_p" size="5" ></td>
		</tr>
		<tr>
			<td>방어력</td>
			<td><input type="text" name="defend_p" size="5" ></td>
		</tr>
		<tr>
			<td>체력</td>
			<td><input type="text" name="hp" size="5" ></td>
		</tr>
		<tr>
			<td>마력</td>
			<td><input type="text" name="mp" size="5" ></td>
		</tr>
		<tr>
			<td>힘</td>
			<td><input type="text" name="str" size="5" ></td>
		</tr>
		<tr>
			<td>지능</td>
			<td><input type="text" name="int" size="5" ></td>
		</tr>
		<tr>
			<td colspan="2" align="center">
				<input type="submit"  value="등록">
				<input type="reset" value="다시작성">
			</td>
		</tr>
	</table>

</body>
</html>