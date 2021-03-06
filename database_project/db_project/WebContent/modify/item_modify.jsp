<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.*"%>
<!DOCTYPE html>
<%
	request.setCharacterEncoding("UTF-8");
	String item_id = request.getParameter("item_id");
	Db_project db = Db_project.getInstance();
	Item_table it = new Item_table();
	it = db.getItemInfo(item_id);
	String heroes[] = db.getAllHeroes();	//부여 가능한 용사들 (모든 용사) * 중복이 가능하므로
	int total_count_heroes = db.CntAllHeroes();	
%>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
<style>
	h3, div{
		text-align:center;
	}
	table{
		margin:auto
	}
</style>
</head>
<body>
	<form name="itemModifyForm" method="post" action="item_modify_db.jsp">
	<div><a href='modify.jsp'><img src='../image/hero.jpg' width="300" height="100" ></a><br><br></div>
	<%if(it.getItem_id()!=null){ %>
	<h3>수정할 아이템의 정보를 입력하시오.</h3>
	<table border="1" cellpadding="3" cellspacing="0">
		<input type="hidden" name="old_item" value=<%=it.getItem_id() %>>
		<tr>
			<td>아이템명</td>
			<td><input type="text" name="new_item" size="30" value=<%=it.getItem_id() %>></td>
		</tr>
		
		<tr>
			<td>부여 할 용사</td>
			<td>
			<select name="hero_id">
				<option value="없음">없음
				<%for(int i=0;i<total_count_heroes;i++){%>
					<option value=<%=heroes[i]%>><%=heroes[i]%>
				<%}%>
			</select>
			</td>
		</tr>
		
		<tr>
			<td>타입</td>
			<td>
			<select name="type">
		 	    <option value="longsword">longsword
				<option value="dagar">dagger
				<option value="spear">spear
				<option value="axe">axe
				<option value="bow">bow
				<option value="globe">globe
				<option value="staff">staff
				<option value="accessory">accessory
			</select>
			</td>
		</tr>
		<tr>
			<td>공격력 증가량</td>
			<td><input type="text" name="attack_p_up" size="5" value=<%=it.getAttack_p_up() %> ></td>
		</tr>
		<tr>
			<td>방어력 증가량</td>
			<td><input type="text" name="defend_p_up" size="5" value=<%=it.getDefend_p_up() %> ></td>
		</tr>
		<tr>
			<td>힘 증가량</td>
			<td><input type="text" name="str_up" size="5" value=<%=it.getStr_up() %> ></td>
		</tr>
		<tr>
			<td>지능 증가량</td>
			<td><input type="text" name="int_up" size="5" value=<%=it.getInt_up() %> ></td>
		</tr>
		<tr>
			<td colspan="2" align="center">
				<input type="submit" value="아이템수정">
				<input type="reset" value="다시작성">
			</td>
		</tr>
	</table>
	<%}else{ %>
		<h3>존재하지 않는 아이템명입니다.</h3>
	<%} %>

</body>
</html>