<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>

<%@page import="board.bean.BoardDTO"%>
<%@page import="java.util.ArrayList"%>

<jsp:useBean id="dao" class="board.dao.BoardDAO">
</jsp:useBean>

<%
	int pg = Integer.parseInt(request.getParameter("pg"));
	int endNum = pg * 5;//끝 페이지
	int startNum = endNum - 4;//시작 페이지

	int totalAt = dao.countTotal();//total Article
	int totalPg = 0;//total Page
	if (totalAt % 5 == 0)
		totalPg = totalAt / 5;
	else
		totalPg = (totalAt / 5) + 1;
	
	//3개의 페이지블럭
	int startPage = (pg-1)/3*3+1;
	int endPage=startPage+2;
	if(endPage>totalPg){
		
		endPage=totalPg;
	}
	
	ArrayList<BoardDTO> list = dao.showList(startNum, endNum);
	
	
	request.setAttribute("list", list);
	request.setAttribute("totalPg", totalPg);
	request.setAttribute("pg",pg);
	request.setAttribute("startPage", startPage);
	request.setAttribute("endPage", endPage);
	
	
	RequestDispatcher dispatcher = request.getRequestDispatcher("boardListView.jsp");
	dispatcher.forward(request,response);
	

	
%>
