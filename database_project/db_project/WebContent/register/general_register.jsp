<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");

	Db_project db = Db_project.getInstance();
	General_table gt = new General_table();
	
	int check1 = 0;	// 장군 등록 성공 여부 체크
	int check2 = 0; // 지휘 등록 성공 여부 체크
	int age=0;
	double army_attack_comp=0, army_defense_comp=0, army_loco_comp=0,army_moral_comp=0;
	String new_general = request.getParameter("new_general");
	String age_buff = request.getParameter("age");
	if(age_buff!="")
		age = Integer.parseInt(age_buff);
	String army_attack_comp_buff = request.getParameter("army_attack_comp");
	if(army_attack_comp_buff!="")
		army_attack_comp = Double.parseDouble(army_attack_comp_buff);
	String army_defense_comp_buff = request.getParameter("army_defense_comp");
	if(army_defense_comp_buff!="")
		army_defense_comp = Double.parseDouble(army_defense_comp_buff);
	String army_loco_comp_buff = request.getParameter("army_loco_comp");
	if(army_loco_comp_buff!="")
		army_loco_comp = Double.parseDouble(army_loco_comp_buff);
	String army_moral_comp_buff = request.getParameter("army_moral_comp");
	if(army_moral_comp_buff!="")
		army_moral_comp = Double.parseDouble(army_moral_comp_buff);
	String army = request.getParameter("army");
	if(army.equals("없음")){
		army = null;
	}
	String rival = request.getParameter("rival");
	//한번에 저장하기
	if(rival.equals("없음")){
		rival = null;
	}
	gt.setGeneral_name(new_general);
	gt.setAge(age);
	gt.setArmy_attack_comp(army_attack_comp);
	gt.setArmy_defense_comp(army_defense_comp);
	gt.setArmy_loco_comp(army_loco_comp);
	gt.setArmy_moral_comp(army_moral_comp);
	gt.setRival(rival);
	check1 = db.RegisterGeneral(gt);
	
	if(army!=null){	//마물장군은 지휘하는 몬스터 군단이 없을 수 있음
		check2=db.setCommandMonster(army, new_general);
	}

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
		<%if(army!=null && check2!=1){ %>
			<div><h1>마물 장군 등록에는 성공하였으나 지휘 등록은 실패하였습니다...!</h1></div>
		<%} %>
	<h1>새로운 마물 장군 등록에 성공하였습니다!! </h1>
	<div><a href="../main.jsp">홈으로</a></div>
	<%}else{ %>
	<h1>등록에 실패하였습니다. </h1>
	<div><a href="general_form.jsp">마물장군 재등록</a></div>
	<div><a href="../main.jsp">홈으로</a></div>
	<%} %>
</body>
</html>