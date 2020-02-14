<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");

	Db_project db = Db_project.getInstance();
	Species_table spt = new Species_table();
	
	int check = 0;	//등록 성공 여부 체크
	
	String species_name = request.getParameter("species_name");
	String attack_p_comp_buff = request.getParameter("attack_p_comp");
	double attack_p_comp = Double.parseDouble(attack_p_comp_buff);
	String defend_p_comp_buff = request.getParameter("defend_p_comp");
	double defend_p_comp = Double.parseDouble(defend_p_comp_buff);
	String hp_comp_buff = request.getParameter("hp_comp");
	double hp_comp = Double.parseDouble(hp_comp_buff);
	String mp_comp_buff = request.getParameter("mp_comp");
	double mp_comp = Double.parseDouble(mp_comp_buff);
	String str_comp_buff = request.getParameter("str_comp");
	double str_comp = Double.parseDouble(str_comp_buff);
	String int_comp_buff = request.getParameter("int_comp");
	double int_comp = Double.parseDouble(int_comp_buff);

	
	//한번에 저장하기
	spt.setSpecies_name(species_name);
	spt.setAttack_p_comp(attack_p_comp);
	spt.setDefend_p_comp(defend_p_comp);
	spt.setHp_comp(hp_comp);
	spt.setMp_comp(mp_comp);
	spt.setStr_comp(str_comp);
	spt.setInt_comp(int_comp);
	
	check = db.modifySpecies(spt);

%>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
	<%if(check==1){ %>
	 종족 수정 성공하였습니다!! 
	<a href="../main.jsp">홈으로</a>
	<%}else{ %>
	수정에 실패하였습니다. 
	<a href="modify.jsp">종족 재수정</a>
	<a href="../main.jsp">홈으로</a>
	<%} %>
</body>
</html>