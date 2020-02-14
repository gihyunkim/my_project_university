<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");

	Db_project db = Db_project.getInstance();
	Hero_table ht = new Hero_table();
	
	int check = 0;	//수정 성공 여부 체크
	
	String id = request.getParameter("id");
	String pwd = request.getParameter("pwd");
	String name = request.getParameter("name");
	String age_buff = request.getParameter("age");
	int age = Integer.parseInt(age_buff);
	String hometown = request.getParameter("hometown");
	String species = request.getParameter("species");
	String attack_p_buff = request.getParameter("attack_p");
	int attack_p = Integer.parseInt(attack_p_buff);
	String defend_p_buff = request.getParameter("defend_p");
	int defend_p = Integer.parseInt(defend_p_buff);
	String hp_buff = request.getParameter("hp");
	int hp = Integer.parseInt(hp_buff);
	String mp_buff = request.getParameter("mp");
	int mp = Integer.parseInt(mp_buff);
	String str_buff = request.getParameter("str");
	int str = Integer.parseInt(str_buff);
	String int_buff = request.getParameter("int");
	int intel = Integer.parseInt(int_buff);
	
	//한번에 저장하기
	ht.setId(id);
	ht.setPwd(pwd);
	ht.setName(name);
	ht.setAge(age);
	ht.setHometown(hometown);
	ht.setSpecies(species);
	ht.setAttack_p(attack_p);
	ht.setDefend_p(defend_p);
	ht.setHp(hp);
	ht.setMp(mp);
	ht.setStr(str);
	ht.setIntel(intel);

	check = db.modifyHero(ht);
	
%>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
	<%if(check==1){ %>
	용사 수정에 성공하였습니다!! 
	<a href="../main.jsp">홈으로</a>
	<%}else{ %>
	수정에 실패하였습니다. 
	<a href="modify.jsp">영웅 재수정</a>
	<a href="../main.jsp">홈으로</a>
	<%} %>
</body>
</html>