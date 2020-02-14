<%@page import="member.Db_project"%>
<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="UTF-8"%>
<!DOCTYPE html>
<%
	String memId= (String)session.getAttribute("memId");
%>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title>Insert title here</title>
	<style>
		h1, div
		{
			text-align:center;	
		}
	</style>
</head>
<body >
<h1 align="center">Heroes of Thunder</h1>
<div><a href='main.jsp'><img src='./image/hero.jpg' width="500" height="300" ></a><br><br></div>
	<%if(memId==null) {%>
		<div><a href='loginForm.jsp' text-align= center>로그인</a><br><br></div>
		<div><a href='./search/search.jsp'>게임 정보 검색</a></div>
		<div><a href='./statistic/statistic.jsp'>현재 데이터 통계</a></div>
		<div><a href='./battle/battle_ready.jsp'>배틀 시뮬레이션</a></div>
		
	<%}else{%>
		<div><%=memId %>님이 로그인 중입니다.<br><br></div>
		<div><a href='./search/search.jsp'>게임 정보 검색</a><br><br></div>
		<div><a href='./statistic/statistic.jsp'>현재 데이터 통계</a></div>
		<div><a href='./battle/battle_ready.jsp'>배틀 시뮬레이션</a></div>
		<div><a href='./register/register.jsp'>데이터 등록</a><br><br></div>
		<div><a href='./modify/modify.jsp'>데이터 수정</a><br><br></div>
		<div><a href='./delete/delete.jsp'>데이터 삭제</a><br><br></div>
		<div><a href='logout.jsp'>로그아웃</a></div>
	<%} %>
</body>
</html>