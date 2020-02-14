<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");

	Db_project db = Db_project.getInstance();
	Item_table it = new Item_table();
	
	int check = 0;	//등록 성공 여부 체크
	int attack_p_up=0, defend_p_up=0, str_up=0, int_up=0;
	String new_item = request.getParameter("new_item");
	String hero_id = request.getParameter("hero_id");
	if(hero_id.equals("없음")){
		hero_id = null;
	}
	String type = request.getParameter("type");
	String attack_p_up_buff = request.getParameter("attack_p_up");
	if(attack_p_up_buff!="")
		attack_p_up = Integer.parseInt(attack_p_up_buff);
	String defend_p_up_buff = request.getParameter("defend_p_up");
	if(defend_p_up_buff!="")
		defend_p_up = Integer.parseInt(defend_p_up_buff);
	String str_up_buff = request.getParameter("str_up");
	if(str_up_buff!="")
		str_up = Integer.parseInt(str_up_buff);
	String int_up_buff = request.getParameter("int_up");
	if(int_up_buff!="")
		int_up = Integer.parseInt(int_up_buff);
	
	//한번에 저장하기
	it.setItem_id(new_item);
	it.setHero_id(hero_id);
	it.setType(type);
	it.setAttack_p_up(attack_p_up);
	it.setDefend_p_up(defend_p_up);
	it.setStr_up(str_up);
	it.setInt_up(int_up);
	
	check = db.RegisterItem(it);

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
	<h1>새로운 아이템 등록에 성공하였습니다!! </h1>
	<div><a href="../main.jsp">홈으로</a></div>
	<%}else{ %>
	<h1>등록에 실패하였습니다. </h1>
	<div><a href="hero_form.jsp">아이템 재등록</a></div>
	<div><a href="../main.jsp">홈으로</a></div>
	<%} %>
</body>
</html>