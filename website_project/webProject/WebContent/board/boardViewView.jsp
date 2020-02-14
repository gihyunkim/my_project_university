<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<%
String test = (String)session.getAttribute("checkHit");
out.println(test);
%>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
<h2><img src="../image/site_name.jpg" width="189" height="57" style="cursor:pointer"
onclick="location.href='../main/index.jsp'"> <small>Experience Site</small></h2>
<div class= container>
<table class="table table-bordered table-striped table-hover" border="1">
<tr>
	<td colspan="3" align="center" ><h2>${dto.title}</h2></td>
</tr>

<tr >
	<td width="200" align="center">글번호 : ${dto.seq }</td>
	<td width="150" align="center">작성자 : ${dto.id }</td>
	<td width="200" align="center">조회수 : ${dto.hit }</td>
</tr>
<tr>
	<td>첨부파일 : <a href="fileDown.jsp?file_name=${dto.filename}">${dto.originalFile }</a></td>
</tr>
<tr>
	<td colspan="3" height="200" valign="top"><pre>${dto.content }</pre></td>
</tr>


</table>

<input type="button" value="글목록" onclick="javascript:location.href='boardList.jsp?pg=${pg}'">
<c:if test="${sessionScope.memId == dto.id}">
<input type="button" value="글수정" onclick="javascript:location.href='boardModifyForm.jsp?seq=${dto.seq}&pg=${pg }'">
<input type="button" value="글삭제" onclick="javascript:location.href='boardDelete.jsp?seq=${dto.seq}'">
</c:if>
</div>
</body>
</html>