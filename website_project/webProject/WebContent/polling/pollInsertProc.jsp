<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
    <%request.setCharacterEncoding("utf-8");%>
    <jsp:useBean id="dao" class="poll.dao.PollMgr"/>
    <jsp:useBean id="plBean" class="poll.plBean.PollListBean"/>
    <jsp:setProperty property="*" name="plBean"/>
    <jsp:useBean id="piBean" class="poll.piBean.PollItemBean"/>
    <jsp:setProperty property="*" name="piBean"/>
    <% 
    String sdate = request.getParameter("sdateY")+"-"+
    			   request.getParameter("sdateM")+"-"+
    			   request.getParameter("sdateD");
    String edate = request.getParameter("edateY")+"-"+
    			   request.getParameter("edateM")+"-"+
    			   request.getParameter("edateD");
    plBean.setSdate(sdate);
    plBean.setEdate(edate);

    boolean flag = dao.insertPoll(plBean, piBean);
    String msg = "failed to add polling";
    String url = "pollInsert.jsp";
    if(flag){
    	msg = "success to add polling";
    	url = "pollList.jsp";
    }
    %>

<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
<script>
alert("<%=msg%>");
location.href="<%=url%>";
</script>
</head>
<body>

</body>
</html>