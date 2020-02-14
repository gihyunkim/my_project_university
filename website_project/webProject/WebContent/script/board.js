function checkBoardWrite(){
	if(document.forms[0].title.value=="")alert("제목을 입력해주세요");
	else if(document.forms[0].content.value=="")alert("내용을 입력해주세요");
	else
		document.forms[0].submit();
}

//function checkBoardModify(){
//	if(document.boardModifyForm.title.value=="")alert("제목을 입력해주세요");
//	else if(document.boardModifyForm.content.value=="")alert("내용을 입력해주세요");
//	else
//		document.boardModifyForm.submit();
//}