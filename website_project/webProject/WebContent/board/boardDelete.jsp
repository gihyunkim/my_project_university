<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<jsp:useBean id="dao" class="board.dao.BoardDAO" />

<%
int seq= Integer.parseInt(request.getParameter("seq"));

dao.boardDelete(seq);

response.sendRedirect("boardDeleteView.jsp");


%>