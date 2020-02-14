<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");

	Db_project db = Db_project.getInstance();
	Monster_table mt = new Monster_table();
	
	int check1 = 0;	//등록 성공 여부 체크
	int check2 = 0; //지휘 등록 성공 체크
	int num_monster=0, total_attack=0, total_defense=0,locomotive=0, moral=0;
	String new_army = request.getParameter("new_army");
	String num_monster_buff = request.getParameter("num_monster");
	String total_attack_buff = request.getParameter("total_attack");
	String total_defense_buff = request.getParameter("total_defense");
	String locomotive_buff = request.getParameter("locomotive");
	String moral_buff = request.getParameter("moral");
	String general_name = request.getParameter("general_name");
	if(num_monster_buff!="")
		num_monster = Integer.parseInt(num_monster_buff);
	if(total_attack_buff!="")
		total_attack = Integer.parseInt(total_attack_buff);
	if(total_defense_buff!="")
		total_defense = Integer.parseInt(total_defense_buff);
	if(locomotive_buff!="")
		locomotive = Integer.parseInt(locomotive_buff);
	if(moral_buff!="")
		moral = Integer.parseInt(moral_buff);

	
	//한번에 저장하기
	mt.setArmy_name(new_army);
	mt.setNum_monster(num_monster);
	mt.setTotal_attack(total_attack);
	mt.setTotal_defense(total_defense);
	mt.setLocomotive(locomotive);
	mt.setMoral(moral);
	
	
	check1 = db.RegisterMonster(mt);
	check2 = db.setCommandMonster(new_army, general_name);
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
	<%if(check1==1){ %>
		<%if(check2!=1){%>
			<h1>지휘 등록에는 실패하였습니다!!...command 쪽을 다시 한번 살펴주시기 바랍니다.</h1>
		<%} %>
	<h1>새로운 군단 등록에 성공하였습니다!! </h1>
	<div><a href="../main.jsp">홈으로</a></div>
	<%}else{ %>
	<h1>등록에 실패하였습니다. </h1>
	<div><a href="hero_form.jsp">마물군단 재등록</a></div>
	<div><a href="../main.jsp">홈으로</a></div>
	<%} %>
</body>
</html>