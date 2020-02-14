<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<script type="text/javascript" src="../script/board.js"></script>
<body>
<h2><img src="../image/site_name.jpg" width="189" height="57" style="cursor:pointer"
onclick="location.href='../main/index.jsp'"> <small>Experience Site</small></h2>
<form name=boardModifyForm method="post" action="boardModify.jsp">

<input type="hidden" name="seq"	value="${seq }">
<input type="hidden" name="pg"	value="${pg }">

<table class="table table-bordered table-striped table-hover" border="1" cellspacing="0" cellpadding="3">

<tr>
<td>제목</td>
<td>
<input type="text" name="title" size="50" value="${dto.title }">
</td>
</tr>

<tr>
<td>내용</td>
<td>
<textarea name="content" cols="50" rows="15">${dto.content }</textarea>
</td>
</tr>

<tr>
<td colspan="2" align="center">
<input type="button" value="글수정" onclick="javascript:checkBoardWrite();">
<input type="reset" value="다시작성">
</td>
</tr>
</table>
</body>
</html>