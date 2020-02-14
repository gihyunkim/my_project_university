<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");

	Db_project db = Db_project.getInstance();
	Monster_table mt = new Monster_table();
	
	int check1 = 0;	//등록 성공 여부 체크
	int check2=0;	//지휘관 중복 여부
	String army_name = request.getParameter("army_name");
	String num_monster_buff = request.getParameter("num_monster");
	String total_attack_buff = request.getParameter("total_attack");
	String total_defense_buff = request.getParameter("total_defense");
	String locomotive_buff = request.getParameter("locomotive");
	String moral_buff = request.getParameter("moral");
	String general_name = request.getParameter("general_name");
	int num_monster = Integer.parseInt(num_monster_buff);
	int total_attack = Integer.parseInt(total_attack_buff);
	int total_defense = Integer.parseInt(total_defense_buff);
	int locomotive = Integer.parseInt(locomotive_buff);
	int moral = Integer.parseInt(moral_buff);
	String command_general[] = db.getCommandGeneral(army_name);
	//한번에 저장하기
	mt.setArmy_name(army_name);
	mt.setNum_monster(num_monster);
	mt.setTotal_attack(total_attack);
	mt.setTotal_defense(total_defense);
	mt.setLocomotive(locomotive);
	mt.setMoral(moral);
	
	for(int i=0;i<100;i++){
		if(command_general[i]==null)	//두 관계 간 명령 체제 존재안함
			break;
		if(command_general[i].equals(general_name)){//존재
			check2=1;
		}
	}
	
	check1 = db.modifyArmy(mt,general_name,check2);

%>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
	<%if(check1==1){ %>
	군단 수정에 성공하였습니다!! 
	<a href="../main.jsp">홈으로</a>
	<%}else{ %>
	수정에 실패하였습니다. 
	<a href="modify.jsp">마물군단 재수정</a>
	<a href="../main.jsp">홈으로</a>
	<%} %>
</body>
</html>