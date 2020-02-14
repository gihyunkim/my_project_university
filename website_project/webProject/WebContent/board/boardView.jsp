<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="board.dao.BoardDAO,board.bean.BoardDTO" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<%

int pg=Integer.parseInt(request.getParameter("pg"));
int seq=Integer.parseInt(request.getParameter("seq"));

BoardDAO dao = BoardDAO.getInstance();
BoardDTO dto=dao.boardView(seq);

dao.hitUpdate(seq);

request.setAttribute("dto", dto);
request.setAttribute("pg", pg);


RequestDispatcher dispatch = request.getRequestDispatcher("boardViewView.jsp");
dispatch.forward(request, response);

%>