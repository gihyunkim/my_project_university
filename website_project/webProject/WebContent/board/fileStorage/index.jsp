<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib  prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html lang="en" ng-app>
<head>

<title>Insert title here</title>
<script type="text/javascript" src="../script/jquery.min.js"></script>
<link rel="stylesheet" href="../css/board.css">
<link rel="stylesheet" href="../css/bootstrap.min.css">
<script type="text/javascript" src="../script/angular.min.js"></script>
</head>
<body>
	<div class="page-header">
		<h2><img src="../image/site_name.jpg" width="189" height="57" style="cursor:pointer"
onclick="location.href='../main/index.jsp'"> <small>Experience Site</small></h2>
	<div class="clearfix">
		<div class="pull-right">
			<c:if test="${sessionScope.memId!=null }">
				<a href='../member/logout.jsp'>로그아웃</a>&nbsp;
				<a href='../board/boardWriteForm.jsp'>글쓰기</a>
			</c:if>
			<c:if test="${memId==null }">
				<a href='../member/loginForm.jsp'>로그인</a>&nbsp;
				<a href='/webProject/member/writeForm.jsp'>회원가입</a>

			</c:if>
		</div>
		</div>
	</div>

	<nav class="navbar navbar-default" role="navigation">
		<div class="navbar-header">
       	 	<button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#nav-toggle">
            	<span class="sr-only">Toggle navigation</span>
            	<span class="icon-bar"></span>
            	<span class="icon-bar"></span>
            	<span class="icon-bar"></span>
        	</button>

		</div>

		<div class="collapse navbar-collapse" id="nav-toggle">
        	<ul class="nav navbar-nav">
          	  <li class="active"><a href='../board/boardList.jsp?pg=1'>목록</a></li>
       		</ul>
        <form class="navbar-form navbar-right" role="search">
            <input type="text" class="form-control" placeholder="Search">
        </form>
    </div>
</body>
</html>



<%-- <%if(session.getAttribute("memId")!=null){ %> --%>
<!-- <a href='../member/logout.jsp'>로그아웃</a><br/> -->
<!-- <a href='../board/boardWriteForm.jsp'>글쓰기</a><br/> -->
<!-- <a href=''>목록</a><br/> -->
<%-- <%} else if(session.getAttribute("memId")==null){%> --%>
<!-- <a href='/miniproject/member/writeForm.jsp'>회원가입</a><br/> -->
<!-- <a href='../member/loginForm.jsp'>로그인</a><br/> -->
<!-- <a href='../board/boardList.jsp?pg=1'>목록</a><br/> -->
<%-- <%} %> --%>
