-<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<%@ page import="java.util.Vector, poll.plBean.PollListBean" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<jsp:useBean id="dao" class="poll.dao.PollMgr"/>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html lang="en" ng-app>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<script type="text/javascript" src="../script/jquery.min.js"></script>
<link rel="stylesheet" href="../css/board.css">
<link rel="stylesheet" href="../css/bootstrap.min.css">
<script type="text/javascript" src="../script/bootstrap.min.js"></script>
<script type="text/javascript" src="../script/angular.min.js"></script>
<title>Insert title here</title>
</head>
<body>
<div class="page-header">
		<h2><img src="../image/site_name.jpg" width="189" height="57" style="cursor:pointer"
onclick="location.href='../main/index.jsp'"> <small>Experience Site</small></h2>
	<div class="clearfix">
		<div class="pull-right"> 
			<c:if test="${sessionScope.memId!=null }">
				<a href='../member/logout.jsp'>로그아웃</a>&nbsp;
				<a href='../board/boardWriteForm.jsp'>글쓰기</a>&nbsp;&nbsp;
			</c:if>
			<c:if test="${memId==null }">
				<a href='../member/loginForm.jsp'>로그인</a>&nbsp;
				<a href='/webProject/member/writeForm.jsp'>회원가입</a>&nbsp;&nbsp;		
			</c:if>
		</div>
		</div>
	</div>
	
	<nav class="navbar navbar-default" role="navigation">
		<div class="navbar-header">
       	 	<button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".nav-toggle">
            	<span class="sr-only">Toggle navigation</span>
            	<span class="icon-bar"></span>
            	<span class="icon-bar"></span>
            	<span class="icon-bar"></span>
        	</button>	
        	
		</div>
		
		<div class="collapse navbar-collapse nav-toggle">
        	<ul class="nav navbar-nav">
          	  <li class="dropdown">
          	  <a href='#' class="dropdown-toggle" data-toggle="dropdown">소통의방<b class="caret"></b></a>
          	  <ul class="dropdown-menu">
          	  	<li> <a href="#">공지</a></li>
          	  	<li> <a href="../board/boardList.jsp?pg=1&checkFile=0">자유게시판</a></li>
          	    <li> <a href="#">게임게시판</a></li>
          	    <li> <a href="#">코인게시판</a></li>
          	    <li> <a href="#">쇼핑게시판</a></li>
          	  </ul>
          	  </li>
          	  <li ><a href='../board/boardChard.jsp'>비트코인 차트</a></li>
          	  <li ><a href='../polling/pollList.jsp?'>투표 프로그램</a></li>
       		</ul>
        <form class="navbar-form navbar-right" role="search">
        <div class="form-group">
            <input type="text" class="form-control" placeholder="Search">
        </div>
        <button type="submit" class="btn btn-default">검색</button>
        </form>
    </div>
    </nav>
    
    <div class="container">
	<div align="center">
	<br/>
	<h2>투표 프로그램</h2>
	<hr width="60%"/>
	
	<jsp:include page="pollForm.jsp"/>
	<hr width="60%"/>
	<table>
		<tr>
			<td>
				<table width="500" border="1">
					<tr>
						<td align="center"><b>번호</b></td>
						<td><b>제목</b></td>
						<td><b>시작일~종료일</b></td>
					</tr>
<% 
	Vector<PollListBean> vlist = dao.getAllList();

	int count = vlist.size();
	for(int i=0; i<vlist.size();i++){
		PollListBean plBean = vlist.get(i);
		int num = plBean.getNum();
		String question = plBean.getQuestion();
		String sdate = plBean.getSdate();
		String edate = plBean.getEdate();
		out.println("<tr><td align='center'>"+count+"</td>");
		out.println("<td align='center'><a href='pollList.jsp?num="+num+"'>"+question+"</a></td>");
		out.println("<td>"+sdate+" ~ "+edate+"</td></tr>");
		count -= 1;
	}
%>
</table>
</td>
</tr>
<tr>
<td align="right"> <a href="pollInsert.jsp">설문 작성하기</a></td>
</tr>
</table>
</div>
</div>
</body>
</html>