<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="board.dao.BoardDAO, board.bean.BoardDTO"%>
<%
request.setCharacterEncoding("UTF-8");
int pg = Integer.parseInt(request.getParameter("pg"));
int seq= Integer.parseInt(request.getParameter("seq"));
String title = request.getParameter("title");
String content = request.getParameter("content");

BoardDTO dto = new BoardDTO();

dto.setSeq(seq);
dto.setTitle(title);
dto.setContent(content);

BoardDAO dao = BoardDAO.getInstance();
dao.modifyForm(dto);

request.setAttribute("pg", pg);
request.setAttribute("seq", seq);

RequestDispatcher dispatcher = request.getRequestDispatcher("boardModifyView.jsp");
dispatcher.forward(request, response);

%>
