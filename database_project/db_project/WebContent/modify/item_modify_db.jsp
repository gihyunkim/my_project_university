<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");

	Db_project db = Db_project.getInstance();
	Item_table it = new Item_table();
	
	int check = 0;	//등록 성공 여부 체크
	
	String old_item = request.getParameter("old_item");
	String new_item = request.getParameter("new_item");
	String hero_id = request.getParameter("hero_id");
	if(hero_id.equals("없음")){
		hero_id = null;
	}
	String type = request.getParameter("type");
	String attack_p_up_buff = request.getParameter("attack_p_up");
	int attack_p_up = Integer.parseInt(attack_p_up_buff);
	String defend_p_up_buff = request.getParameter("defend_p_up");
	int defend_p_up = Integer.parseInt(defend_p_up_buff);
	String str_up_buff = request.getParameter("str_up");
	int str_up = Integer.parseInt(str_up_buff);
	String int_up_buff = request.getParameter("int_up");
	int int_up = Integer.parseInt(int_up_buff);
	
	//한번에 저장하기
	it.setItem_id(new_item);
	it.setHero_id(hero_id);
	it.setType(type);
	it.setAttack_p_up(attack_p_up);
	it.setDefend_p_up(defend_p_up);
	it.setStr_up(str_up);
	it.setInt_up(int_up);
	
	check = db.modifyItem(it,old_item);

%>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
	<%if(check==1){ %>
	아이템 수정에 성공하였습니다!! 
	<a href="../main.jsp">홈으로</a>
	<%}else{ %>
	수정에 실패하였습니다. 
	<a href="modify.jsp">아이템 재수정</a>
	<a href="../main.jsp">홈으로</a>
	<%} %>
</body>
</html>