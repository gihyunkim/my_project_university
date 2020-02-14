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
<div><a href='../main.jsp'><img src='../image/hero.jpg' width="400" height="200" ></a><br><br></div>
<form name="admin_delete" method="post" action="admin_delete.jsp">
<div><b>관리자 정보 삭제</b>&nbsp;&nbsp;&nbsp;<input type="text" name="id"  size=30 placeholder="삭제할 관리자 id입력">&nbsp;
<input type="submit" value="삭제"></div>
</form>
<br>
<form name="hero_delete" method="post" action="hero_delete.jsp">
<div><b>용사 정보 삭제</b>&nbsp;&nbsp;&nbsp;<input type="text" name="hero_id"  size=30 placeholder="삭제할 용사  id입력">&nbsp;
<input type="submit" value="삭제"></div>
</form>
<br>
<form name="skill_delete" method="post" action="skill_delete.jsp">
<div><b>스킬 정보 삭제</b>&nbsp;&nbsp;&nbsp;<input type="text" name="skill_id" size=30 placeholder="삭제할 스킬 이름입력">&nbsp;
<input type="submit" value="삭제"></div>
</form>
<br>
<form name="species_delete" method="post" action="species_delete.jsp">
<div><b>종족 정보 삭제</b>&nbsp;&nbsp;&nbsp;<input type="text" name="species_name" size=30 placeholder="삭제할 종족 이름입력">&nbsp;
<input type="submit" value="삭제"></div>
</form>
<br>
<form name="item_delete" method="post" action="item_delete.jsp">
<div><b>아이템 정보 삭제</b>&nbsp;&nbsp;&nbsp;<input type="text" name="item_id" size=30 placeholder="삭제할 아이템 이름입력">&nbsp;
<input type="submit" value="삭제"></div>
</form>
<br>
<form name="army_delete" method="post" action="army_delete.jsp">
<div><b>마물군단 정보 삭제</b>&nbsp;&nbsp;<input type="text" name="army_name" size=30 placeholder="삭제할 마물군단 이름입력">&nbsp;
<input type="submit" value="삭제"></div>
</form>
<br>
<form name="general_delete" method="post" action="general_delete.jsp">
<div><b>마물장군 정보 삭제</b>&nbsp;&nbsp;<input type="text" name="general_name" size=30 placeholder="삭제할 마물장군 이름입력">&nbsp;
<input type="submit" value="삭제"></div>
</form>
<br>




</body>
</html>