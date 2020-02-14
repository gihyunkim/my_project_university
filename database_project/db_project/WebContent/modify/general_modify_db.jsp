<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");

	Db_project db = Db_project.getInstance();
	General_table gt = new General_table();
	
	int check1 = 0;	// 장군 등록 성공 여부 체크
	int check2 = 0; // 지휘 중복 여부
	String command_army[];
	
	String general_name = request.getParameter("general_name");
	String age_buff = request.getParameter("age");
	int age = Integer.parseInt(age_buff);
	String army_attack_comp_buff = request.getParameter("army_attack_comp");
	double army_attack_comp = Double.parseDouble(army_attack_comp_buff);
	String army_defense_comp_buff = request.getParameter("army_defense_comp");
	double army_defense_comp = Double.parseDouble(army_defense_comp_buff);
	String army_loco_comp_buff = request.getParameter("army_loco_comp");
	double army_loco_comp = Double.parseDouble(army_loco_comp_buff);
	String army_moral_comp_buff = request.getParameter("army_moral_comp");
	double army_moral_comp = Double.parseDouble(army_moral_comp_buff);
	String army = request.getParameter("army");
	if(army.equals("없음")){
		army = null;
	}
	String rival = request.getParameter("rival");
	//한번에 저장하기
	if(rival.equals("없음")){
		rival = null;
	}
	gt.setGeneral_name(general_name);
	gt.setAge(age);
	gt.setArmy_attack_comp(army_attack_comp);
	gt.setArmy_defense_comp(army_defense_comp);
	gt.setArmy_loco_comp(army_loco_comp);
	gt.setArmy_moral_comp(army_moral_comp);
	gt.setRival(rival);
	
	command_army = db.getCommandArmy(general_name);
	
	for(int i=0;i<100;i++){
		if(command_army[i]==null)
			break;
		if(command_army[i].equals(army)){
			check2=1;
		}
	}
	check1 = db.modifyGeneral(gt,army,check2);
	
%>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
	<%if(check1==1){ %>
	마물 장군 수정에 성공하였습니다!! 
	<a href="../main.jsp">홈으로</a>
	<%}else{ %>
	등록에 실패하였습니다. 
	<a href="modify.jsp">마물장군 재수정</a>
	<a href="../main.jsp">홈으로</a>
	<%} %>
</body>
</html>