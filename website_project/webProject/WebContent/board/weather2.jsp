<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
<script type="text/javascript" src="../script/jquery.min.js"></script>
<link rel="stylesheet" href="../css/board.css">
<link rel="stylesheet" href="../css/bootstrap.min.css">
<script type="text/javascript" src="../script/bootstrap.min.js"></script>
<script type="text/javascript" src="../script/angular.min.js"></script>
<script type="text/javascript">
	window.onload = function() {
		document.getElementById("btnOk").onclick = function() {
			startXHR(); //function startXHR로 이동
		}
	}

	var xhr;
	function createXHR() {
		if (window.ActiveXObject) {
			xhr = new ActiveXObject("Msxml2.XMLHTTP");
		} else {
			xhr = new XMLHttpRequest(); // xhr을 얻음
		}
	}

	function startXHR() {
		createXHR();

		xhr.open("get", "weather2.xml", true); //weather.xml 호출
		xhr.onreadystatechange = function() {

			if (xhr.readyState == 4) {
				if (xhr.status == 200) {
					process();
				}
			}
		}
		xhr.send(null);
	}

	function process() { // xml 업데이트 시점 불러오기
		var data = xhr.responseXML;

		var weatherNode = data.getElementsByTagName("weather")[0];
		var strDate = weatherNode.getAttribute("year") + "년 "
				+ weatherNode.getAttribute("month") + "월 "
				+ weatherNode.getAttribute("day") + "일 "
				+ weatherNode.getAttribute("hour") + "시";

		document.getElementById("disp").innerHTML = strDate; // disp 레이어에 집어넣음

		var localNode = data.getElementsByTagName("local");
		//날씨 출력방법1 - HTML DOM을 쓰는 방식
		for (var i = 0; i < localNode.length; i++) {
			var row = document.createElement("tr"); // tr 생성
			var col1 = document.createElement("td"); // td 생성
			var col2 = document.createElement("td"); // td 생성
			var loc = localNode[i].childNodes[0].nodeValue;
			var ta = localNode[i].getAttribute("ta"); 
			col1.appendChild(document.createTextNode(loc)); //appendchild로 넣음
			col2.appendChild(document.createTextNode(ta)); //appendchild로 넣음
			row.appendChild(col1);
			row.appendChild(col2);
			document.getElementById("myTbody").appendChild(row); // 테이블을 만들어서 row에 appendchild로 넣음
		}

		//날씨 출력방법1 - innerHTML을 쓴 방식
		var ss = "<table>";
		for (var i = 0; i < localNode.length; i++) {
			ss += "<tr>";
			ss += "<td>" + localNode[i].childNodes[0].nodeValue + "</td>";
			ss += "<td>" + localNode[i].getAttribute("ta") + "</td>";
			ss += "</tr>";
		}
		ss += "</table>";
		document.getElementById("disp2").innerHTML = ss;
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
          	  	<li> <a href="../board/boardList.jsp?pg=1&checkFile=0">자유게시판</a></li>
          	    <li> <a href="#">게임게시판</a></li>
          	    <li> <a href="#">코인게시판</a></li>
          	    <li> <a href="#">쇼핑게시판</a></li>
          	  </ul>
          	  </li>
          	  <li ><a href='../board/boardChard.jsp'>비트코인 차트</a></li>
          	  <li ><a href='../polling/pollList.jsp'>투표 프로그램</a></li>
          	  <li ><a href='../board/ajax1_ex.html'>오늘의 날씨</a></li>
       		</ul>
        <form class="navbar-form navbar-right" role="search">
        <div class="form-group">
            <input type="text" class="form-control" placeholder="Search">
        </div>
        <button type="submit" class="btn btn-default">검색</button>
        </form>
    </div>
    </nav>
	<input type="button" value="온도 확인" id="btnOk"> <!-- 온도 확인 버튼 -->
	<div id="disp"></div> <!-- disp 레이어 - HTML DOM을 쓰기 위함 -->

	<table id="myTable"> <!-- 표 지정 -->
		<tbody id="myTbody"></tbody>
	</table>

	<hr>
</body>
</html>