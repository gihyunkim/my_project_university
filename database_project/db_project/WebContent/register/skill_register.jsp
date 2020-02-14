<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");

	Db_project db = Db_project.getInstance();
	Skill_table st = new Skill_table();
	
	int check = 0;	//등록 성공 여부 체크
	int hp_up=0, mp_up=0;
	String new_skill = request.getParameter("new_skill");
	String hero_id = request.getParameter("hero_id");
	if(hero_id.equals("없음")){
		hero_id = null;
	}
	String hp_up_buff = request.getParameter("hp_up");
	if(hp_up_buff!="")
		hp_up = Integer.parseInt(hp_up_buff);
	String mp_up_buff = request.getParameter("mp_up");
	if(mp_up_buff!="")
		mp_up = Integer.parseInt(mp_up_buff);
	
	//한번에 저장하기
	
	st.setSkill_id(new_skill);
	st.setHero_id(hero_id);
	st.setHp_up(hp_up);
	st.setMp_up(mp_up);
	
	check = db.RegisterSkill(st);

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
	<h1>새로운 스킬 등록에 성공하였습니다!! </h1>
	<div><a href="../main.jsp">홈으로</a></div>
	<%}else{ %>
	<h1>등록에 실패하였습니다. </h1>
	<div><a href="hero_form.jsp">스킬 재등록</a></div>
	<div><a href="../main.jsp">홈으로</a></div>
	<%} %>
</body>
</html>