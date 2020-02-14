<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html lang="en" ng-app>
<head>
   <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
   <title>Insert title here</title>
   <script src="https://code.jquery.com/jquery-3.1.1.min.js"></script>
   <script src="https://code.highcharts.com/stock/highstock.js"></script>
   <script src="https://code.highcharts.com/stock/modules/exporting.js"></script>
   <script type="text/javascript" src="../script/jquery.min.js"></script>
<link rel="stylesheet" href="../css/board.css">
<link rel="stylesheet" href="../css/bootstrap.min.css">
<script type="text/javascript" src="../script/bootstrap.min.js"></script>
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
   <div id="container" style="height: 400px; min-width: 310px"></div>
      <script>
         function draw3(){
            var chartdata = [];
            $.getJSON('https://poloniex.com/public?command=returnChartData&currencyPair=BTC_ETH&start=1455699200&end=9999999999&period=14400', function (data) {
               $.each(data, function(i, item){
                  chartdata.push([item.date*1000, item.open, item.high, item.low, item.close]);
               });
            }).done(function(){
               Highcharts.stockChart('container',{
                  title: {
                     text: 'ETH/BTC'
                  },
                  rangeSelector: {
                     buttons: [
                        {type: 'hour',count: 1,text: '1h'}, 
                        {type: 'day',count: 1,text: '1d'}, 
                        {type: 'all',count: 1,text: 'All'}
                     ],
                     selected: 2,
                     inputEnabled: true
                  },
                  plotOptions: {
                     candlestick: {
                        downColor: 'blue',
                        upColor: 'red'
                     }
                  },
                  series: [{
                     name: 'ETH/BTC',
                     type: 'candlestick',
                     data: chartdata,
                     tooltip: {
                        valueDecimals: 8
                     }
                  }]
               });
            });
         }
         draw3();
      </script>
   </body>
</html>