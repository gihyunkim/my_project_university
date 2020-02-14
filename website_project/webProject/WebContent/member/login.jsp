<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.dao.MemberDAO"%>
<%@page import="java.net.URLEncoder"%>
<%
request.setCharacterEncoding("UTF-8");
String id = request.getParameter("id");
String pwd = request.getParameter("pwd");

MemberDAO dao = MemberDAO.getInstance();
String encrypted_pwd = dao.encryptPwd(pwd);
String name = dao.login(id,encrypted_pwd);

if(name==null) {
	response.sendRedirect("loginFail.jsp");
}else {
//쿠키
session.setAttribute("memName", name);
session.setAttribute("memId", id);
response.sendRedirect("loginOk.jsp");

} 
%>
