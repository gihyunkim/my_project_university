<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>Insert title here</title>
<style>
	h1, div{
		text-align:center;
	}
</style>
</head>
<body>
<h1>정보 수정</h1>
<div><a href='../main.jsp'><img src='../image/hero.jpg' width="400" height="200" ></a><br><br></div>
<form name="admin_modify" method="post" action="admin_modify.jsp">
<div><b>관리자 정보 수정</b>&nbsp;&nbsp;&nbsp;<input type="text" name="id"  size=30 placeholder="수정할 관리자  id입력">&nbsp;
<input type="submit" value="수정"></div>
</form>
<br>
<form name="hero_modify" method="post" action="hero_modify.jsp">
<div><b>용사 정보 수정</b>&nbsp;&nbsp;&nbsp;<input type="text" name="hero_id"  size=30 placeholder="수정할 용사  id입력">&nbsp;
<input type="submit" value="수정"></div>
</form>
<br>
<form name="skill_modify" method="post" action="skill_modify.jsp">
<div><b>스킬 정보 수정</b>&nbsp;&nbsp;&nbsp;<input type="text" name="skill_id" size=30 placeholder="수정할 스킬 이름입력">&nbsp;
<input type="submit" value="수정"></div>
</form>
<br>
<form name="species_modify" method="post" action="species_modify.jsp">
<div><b>종족 정보 수정</b>&nbsp;&nbsp;&nbsp;<input type="text" name="species_name" size=30 placeholder="수정할 종족 이름입력">&nbsp;
<input type="submit" value="수정"></div>
</form>
<br>
<form name="item_modify" method="post" action="item_modify.jsp">
<div><b>아이템 정보 수정</b>&nbsp;&nbsp;&nbsp;<input type="text" name="item_id" size=30 placeholder="수정할 아이템 이름입력">&nbsp;
<input type="submit" value="수정"></div>
</form>
<br>
<form name="monster_modify" method="post" action="army_modify.jsp">
<div><b>마물군단 정보 수정</b>&nbsp;&nbsp;<input type="text" name="army_name" size=30 placeholder="수정할 마물군단 이름입력">&nbsp;
<input type="submit" value="수정"></div>
</form>
<br>
<form name="general_modify" method="post" action="general_modify.jsp">
<div><b>마물장군 정보 수정</b>&nbsp;&nbsp;<input type="text" name="general_name" size=30 placeholder="수정할 마물장군 이름입력">&nbsp;
<input type="submit" value="수정"></div>
</form>
<br>




</body>
</html>