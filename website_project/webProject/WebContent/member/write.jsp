<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8" import="member.dao.MemberDAO"  %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<%@ page import="member.bean.MemberDTO" %>

<%-- import 2번 쓰면 안된다.--%>

<%--   콤마(,)쓰고 또 쓰던가 <% %>를 하나더 만들면된다. --%>

<% 
MemberDAO dao = MemberDAO.getInstance();

request.setCharacterEncoding("UTF-8");//한글 처리

String name = request.getParameter("name");//이름

String id = request.getParameter("id");//아이디

String pwd = request.getParameter("pwd");//비밀번호

String encrypted_pwd = dao.encryptPwd(pwd);

String gender = request.getParameter("gender");//성별

String email1 = request.getParameter("email1");
String email2 = request.getParameter("email2");
String email=email1+"@"+email2;	//이메일

String tel1 = request.getParameter("tel1");
String tel2 = request.getParameter("tel2");
String tel3 = request.getParameter("tel3");
String phone = tel1+"-"+tel2+"-"+tel3; //핸드폰 번호

String zipcode = request.getParameter("zipcode");
String addr1 = request.getParameter("addr1");
String addr2 = request.getParameter("addr2");
String address = addr1+" "+addr2+" : "+zipcode; // 주소

//현재 가지고 있는 데이터를 DTO에 한곳에 모으기

MemberDTO dto = new MemberDTO();
dto.setName(name);
dto.setId(id);
dto.setPwd(encrypted_pwd);
dto.setGender(gender);
dto.setEmail1(email1);
dto.setEmail2(email2);
dto.setTel1(tel1);
dto.setTel2(tel2);
dto.setTel3(tel3);
dto.setZipcode(zipcode);
dto.setAddr1(addr1);
dto.setAddr2(addr2);
//DB

int su = dao.write(dto);//호출

%> 

<!-- jsp에서 자동으로 미리 만들어져있기때문에 request등등 9가지는 그냥 써도됨 -->

<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>
<body>
<%if(su==1){ %>
화원가입 성공
<input type="button" value="로그인" onclick="javascript:location.href='loginForm.jsp'">

<%}else{ %>
회원가입 실패
<input type="button" value="뒤로" onclick="javascript:history().go(-1)">
<%} %>


</body>

</html>

