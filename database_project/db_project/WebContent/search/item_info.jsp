<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");
	String item_id = request.getParameter("item_id");	//item id
	Db_project db = Db_project.getInstance();
	Item_table it = db.getItemInfo(item_id);
%>
<html>
<head>
<meta charset="UTF-8">
<title>Insert title here</title>
<style>
	div, h1{
		text-align:center;
	}
	table{
		margin:auto;
	}

</style>
</head>
<body>
	<h1>아이템 정보</h1>
<div><a href='./search.jsp'><img src='../image/hero.jpg' width="300" height="200" ></a><br><br></div>	
	<table border="1" cellpadding="3" cellspacing="0">
		<tr>
			<td colspan=7 align="center">아이템</td>
		</tr>
		<tr align="center">
			<td>아이템명</td>
			<td>타입</td>
			<td>공격력 증가치</td>
			<td>방어력 증가치</td>
			<td>힘 증가치</td>
			<td>지능 증가치</td>
			<td>사용중인 용사</td>
		</tr>
		<tr align="center">
			<td><%=it.getItem_id() %></td>
			<td><%=it.getType() %></td>
			<td><%=it.getAttack_p_up() %></td>
			<td><%=it.getDefend_p_up() %></td>
			<td><%=it.getStr_up() %></td>
			<td><%=it.getInt_up() %></td>
			<%if(it.getHero_id()!=null) {%>
			<td><a href='hero_info.jsp?hero_id=<%=it.getHero_id() %>'><%=it.getHero_id() %></a></td>
			<%}else{ %>
				<td>없음</td>
			<%} %>
		</tr>
	</table>

	
</body>
</html>