<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");

	Db_project db = Db_project.getInstance();
	Species_table spt = new Species_table();
	
	int check = 0;	//등록 성공 여부 체크
	double attack_p_comp=0, defend_p_comp=0, hp_comp=0, mp_comp=0, str_comp=0, int_comp=0;
	String new_species = request.getParameter("new_species");
	String attack_p_comp_buff = request.getParameter("attack_p_comp");
	if(attack_p_comp_buff!="")
		attack_p_comp = Double.parseDouble(attack_p_comp_buff);
	String defend_p_comp_buff = request.getParameter("defend_p_comp");
	if(defend_p_comp_buff!="")
		defend_p_comp = Double.parseDouble(defend_p_comp_buff);
	String hp_comp_buff = request.getParameter("hp_comp");
	if(hp_comp_buff!="")
		hp_comp = Double.parseDouble(hp_comp_buff);
	String mp_comp_buff = request.getParameter("mp_comp");
	if(mp_comp_buff!="")
		mp_comp = Double.parseDouble(mp_comp_buff);
	String str_comp_buff = request.getParameter("str_comp");
	if(str_comp_buff!="")
		str_comp = Double.parseDouble(str_comp_buff);
	String int_comp_buff = request.getParameter("int_comp");
	if(int_comp_buff!="")
		int_comp = Double.parseDouble(int_comp_buff);

	
	//한번에 저장하기
	spt.setSpecies_name(new_species);
	spt.setAttack_p_comp(attack_p_comp);
	spt.setDefend_p_comp(defend_p_comp);
	spt.setHp_comp(hp_comp);
	spt.setMp_comp(mp_comp);
	spt.setStr_comp(str_comp);
	spt.setInt_comp(int_comp);
	
	check = db.RegisterSpecies(spt);

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
	<h1>새로운 종족 등록에 성공하였습니다!! </h1>
	<div><a href="../main.jsp">홈으로</a></div>
	<%}else{ %>
	<h1>등록에 실패하였습니다. </h1>
	<div><a href="hero_form.jsp">종족 재등록</a></div>
	<div><a href="../main.jsp">홈으로</a></div>
	<%} %>
</body>
</html>