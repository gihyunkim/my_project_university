<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");

	Db_project db = Db_project.getInstance();
	Hero_table ht = new Hero_table();
	
	int check = 0;	//등록 성공 여부 체크
	int age=0,attack_p=0, defend_p=0, hp=0,mp=0,str=0,intel=0;
	String id = request.getParameter("id");
	String pwd = request.getParameter("pwd");
	String name = request.getParameter("name");
	String age_buff = request.getParameter("age");
	if(age_buff!="")
		age = Integer.parseInt(age_buff);
	String hometown = request.getParameter("hometown");
	String species = request.getParameter("species");
	String attack_p_buff = request.getParameter("attack_p");
	if(attack_p_buff!="")
		attack_p = Integer.parseInt(attack_p_buff);
	String defend_p_buff = request.getParameter("defend_p");
	if(defend_p_buff!="")
		defend_p = Integer.parseInt(defend_p_buff);
	String hp_buff = request.getParameter("hp");
	if(hp_buff!="")
		hp = Integer.parseInt(hp_buff);
	String mp_buff = request.getParameter("mp");
	if(mp_buff!="")
		mp = Integer.parseInt(mp_buff);
	String str_buff = request.getParameter("str");
	if(str_buff!="")
		str = Integer.parseInt(str_buff);
	String int_buff = request.getParameter("int");
	if(int_buff!="")
		intel = Integer.parseInt(int_buff);
	
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
	
	check = db.RegisterHero(ht);

%>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
<style>
	h1, div{
		text-align:center;
	}
</style>
</head>
<body>
<div><a href='register.jsp'><img src='../image/hero.jpg' width="300" height="200" ></a><br><br></div>
	<%if(check==1){ %>
	<h1>새로운 용사 등록에 성공하였습니다!! </h1>
	<div><a href="../main.jsp">홈으로</a></div>
	<%}else{ %>
	<h1>등록에 실패하였습니다. </h1>
	<div><a href="hero_form.jsp">영웅 재등록</a></div>
	<div><a href="../main.jsp">홈으로</a></div>
	<%} %>
</body>
</html>