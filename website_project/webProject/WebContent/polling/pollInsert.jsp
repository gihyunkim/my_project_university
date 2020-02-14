<%@ page language="java" contentType="text/html; charset=utf-8"
    pageEncoding="utf-8"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8">
<title>Insert title here</title>
</head>
<body>
	
	<div align="center">
	<br />
	<h2>투표프로그램</h2>
	<hr width="60%" />
	<form method="post" action="pollInsertProc.jsp">
	<input type="hidden"  name='active' value=1>
	<table border="1" width="500">
	<tr>
	<td><b>질문</b></td>
	<td colspan="2"><input type="text" name="question" size="30"></td>
	</tr>
	<tr>
	<td rowspan="10"> <b>항목</b></td>
	<%
	for(int i = 1;i<=4;i++){
	out.println("<td>" +(i*2-1)
	+": <input type='text' name='item'></td>");
	out.println("<td>" +(i*2) + ":<input type='text' name='item'></td>");
	out.println("</tr>");
	if(i==9){
	out.println("");
	}else{
	out.println("<tr>");
	}
	}%>
	
	<tr>
	<td>시작일</td>
	<td colspan="2"><select name="sdateY">
	
	<option value="2018">2018</option></select>년<select name="sdateM">
	<%
	for(int i = 1; i<=12;i++){
	out.println("<option value='"+i+"'>"+i);
	}
	%>
	</select>월<select name="sdateD">
	
	<%
	for(int i=1;i<=31;i++){
		out.println("<option value='"+i+"'>"+i);
	}
	
	%></select>일</td>
	</tr>
	<tr>
	<td>종료일</td>
	<td colspan=2> <select name ="edateY"><%
	for(int i=2019;i<=2022;i++){
	out.println("<option value='"+i+"'>"+i);
	}
	%></select>년<select name="edateM">
	<%
	for(int i=1;i<=12;i++){
	out.println("<option value='"+i+"'>"+i);
	}
	%>
	</select>월<select name="edateD">
	<%
	for(int i =1; i<=31;i++){
	out.println("<option value='"+i+"'>"+i);
	}%></select>일</td>
	</tr>
	<tr>
	<td>이중답변</td>
	<td colspan=2><input type="radio" name="type" value="1" checked>
	yes<input type="radio" name="type" value="0">no
	</td>
	</tr>
	<tr>
	<td colspan=3><input type="submit" value="작성하기">
	<input type="reset" value="다시쓰기"><input type="button" value="리스트"
	onClick="javascript:location.href='pollList.jsp'">
	</td>
</tr>

</table>
</form>
	</div>
</body>
</html>