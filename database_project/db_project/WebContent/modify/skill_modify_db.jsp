<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");

	Db_project db = Db_project.getInstance();
	Skill_table st = new Skill_table();
	
	int check = 0;	//등록 성공 여부 체크
	String old_skill = request.getParameter("old_skill");
	String new_skill = request.getParameter("new_skill");
	String hero_id = request.getParameter("hero_id");
	String old_owner = request.getParameter("old_owner");
	if(hero_id==null){
		hero_id = old_owner;
	}
	String hp_up_buff = request.getParameter("hp_up");
	int hp_up = Integer.parseInt(hp_up_buff);
	String mp_up_buff = request.getParameter("mp_up");
	int mp_up = Integer.parseInt(mp_up_buff);
	
	//한번에 저장하기
	
	st.setSkill_id(new_skill);
	st.setHero_id(hero_id);
	st.setHp_up(hp_up);
	st.setMp_up(mp_up);
	
	check = db.modifySkill(st, old_skill);

%>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
</head>
<body>
	<%if(check==1){ %>
	스킬 수정에 성공하였습니다!! 
	<a href="../main.jsp">홈으로</a>
	<%}else{ %>
	수정에 실패하였습니다. 
	<a href="modify.jsp">스킬 재수정</a>
	<a href="../main.jsp">홈으로</a>
	<%} %>
</body>
</html>