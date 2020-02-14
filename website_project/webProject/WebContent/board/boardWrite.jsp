<%@page import="java.io.File"%>
<%@page import="com.oreilly.servlet.multipart.DefaultFileRenamePolicy"%>
<%@page import="java.io.IOException"%>
<%@page import="java.util.Enumeration"%>
<%@page import="com.oreilly.servlet.MultipartRequest"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
<%@page import="board.dao.BoardDAO, board.bean.BoardDTO"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">

 <%
//Request
request.setCharacterEncoding("UTF-8");

String filename="첨부파일없음";
String original="";
String savedPath = "D:/ITProject/webProject/WebContent/board/fileStorage";
String stringType = "utf-8";
String title = "";
String content ="";
boolean check = false;
int maxSize = 10*1024*1024;	//10MB


try{
		MultipartRequest multi = null;
		
		multi = new MultipartRequest(request, savedPath, maxSize, stringType, 
				new DefaultFileRenamePolicy());
		Enumeration params = multi.getParameterNames();
		
		while(params.hasMoreElements()){
			String dataname = (String)params.nextElement();
			String value = multi.getParameter(dataname);
			out.println(dataname + "=" +value+"<br>");
		}
		
		Enumeration files = multi.getFileNames();
		while(files.hasMoreElements()){
				String paramname = (String)files.nextElement();
				filename = multi.getFilesystemName(paramname);
				
				original = multi.getOriginalFileName(paramname);
				String type = multi.getContentType(paramname);
				
				File f = multi.getFile(paramname);
				out.println("파라미터 이름 : "+paramname+"<br>");
				out.println("실제 파일 이름 : "+original+"<br>");
				out.println("저장된 파일 이름 : "+filename+"<br>");
				out.println("파일 타입 : "+type+"<br>");
				if(f!=null){
					out.println("크기:"+f.length()+"바이트");
					out.println("<br>");
					check=true;
				}
				title = multi.getParameter("title");
				content = multi.getParameter("content");

					
		}
}catch(IOException ioe){
	System.out.println(ioe);
}catch(Exception ex){
	System.out.println(ex);
}

if(check==false){
	filename="파일없음";
	original="파일없음";
}
String id=(String)session.getAttribute("memId");
String name=(String)session.getAttribute("memName");
BoardDTO dto = new BoardDTO();
dto.setId(id);
dto.setName(name);
dto.setOriginalFile(original);
dto.setFilename(filename);
dto.setTitle(title);
dto.setContent(content);

//DB
BoardDAO dao = BoardDAO.getInstance();
dao.boardWrite(dto);

%> 

<script type="text/javascript">
window.onload=function(){
	alert("글이 작성되었습니다!!");
	location.href="boardList.jsp?pg=1";
}


</script>


<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>


</head>
<body>
</body>
</html>