<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html lang="en" ng-app>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<script type="text/javascript" src="../script/jquery.min.js"></script>
<link rel="stylesheet" href="../css/board.css">
<link rel="stylesheet" href="../css/bootstrap.min.css">
<script type="text/javascript" src="../script/bootstrap.min.js"></script>
<script type="text/javascript" src="../script/angular.min.js"></script>

<title>Insert title here</title>

<script type="text/javascript">

function isLogin(seq){
	
	if('${memId}'==''){
		alert("로그인을 해주세요!!");
		location.href="../member/loginForm.jsp";
	}
	else
		location.href='boardView.jsp?seq='+seq+'&pg=${pg}&count=0';
	
	
}

</script>

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
          	  	<li class="active"> <a href="../board/boardList.jsp?pg=1&checkFile=0">자유게시판</a></li>
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
    
	<c:if test="${requestScope.list!=null }">


		<table class="table table-bordered table-striped table-hover" border="1">
			<tr class=active>
				<th align="center" width="100">글번호</th>
				<th align="center" width="300">제목</th>
				<th align="center" width="300">파일첨부</th>
				<th align="center" width="100">작성자</th>
				<th align="center" width="100">조회수</th>
				<th align="center" width="100">작성일</th>
			</tr>

			<c:forEach var="dto" items="${list }">
				<tr>
					<td align="center">${dto.getSeq()}</td>
					<td align="center"><a href='#' onclick="isLogin(${dto.seq})" >${dto.title }</a></td>
					<!-- 문자인 경우는 ' '싱글 다운표 쳐준다 -->
					<td align="center">${dto.originalFile}</td>
					<td align="center">${dto.id }</td>
					<td align="center">${dto.hit }</td>
					<td align="center">${dto.logtime }</td>
				</tr>
			</c:forEach>
		</table>
</c:if>
		<div style="text-align:center;width:600px;">
			<c:if test="${startPage!=1 }">
				[<a href="boardList.jsp?pg=${startPage-1}" >이전</a>]
			</c:if>
			<c:forEach var="i" begin="${startPage}" end="${endPage}" step="1">
			
				<c:if test="${i==pg}">
					[<a href="boardList.jsp?pg=${i}" class="currentPaging">${i }</a>]
				</c:if>
				<c:if test="${i!=pg}">
					[<a href="boardList.jsp?pg=${i}" id="paging">${i}</a>]
				</c:if>
			</c:forEach>
			
			<c:if test="${endPage<totalPg }">
				[<a href="boardList.jsp?pg=${endPage+1}" >다음</a>]
			</c:if>
			
		</div>
</body>
</html>