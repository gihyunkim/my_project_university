#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning (disable:4996)

typedef struct {
	char word[100];//단어열 첫 단어
	int wordidx;   //단어 관려 정보중 첫 정수
	char pos[10];  //품사열 중 첫 품사
	int numpos;    //품사열의 품사의 총 갯수
}arec;

arec rectype;			//구조체 전역 변수
arec *recptr = &rectype;//구조체의 전역 포인터 변수

unsigned putdatast(FILE* fp, FILE*fpbin) {//데이타를 구조체에 입력

	char buffer[200];	//단어열을 담기위한 임시배열
	char chgint[10];	//문자열 숫자를 int형으로 바꿔주기 위한 배열
	int total_line = 0; //총 줄 수
	int wordnum = 0;	//품사의 총 갯수
	int check = 0;		//파일이 비어있지않았다는 여부 확인 변수( 1이면 비어있지 않은 파일 )
	char *get_err = NULL; //fgets에러점검용


	while (1) {

		int i = 0;
		int j = 0;
		int k = 0;
		int word_length = 0;	//word의 길이
		wordnum = 0;


		
		get_err = fgets(buffer, sizeof(buffer), fp);	//한 줄을 wordlist에서 읽어온다

		if (!get_err) 
		{	
			if (check == 1) {//빈 파일이 아니라, 개행 후에 파일이 끝날 시
				break;
			}
			printf("데이터가 없습니다");	//빈 파일
			break;
		}
		else if (strcmp(get_err, "\n") == 0) //빈칸이 있다면 넘긴다
		{
			continue;
		}


		check = 1;	//파일이 비어있지 않다
		//--------------------------------word----------------------------------

		for (; !(isspace(buffer[i])); i++) {	//처음 문자를 구조체 문자에 넣는다
			recptr->word[i] = buffer[i];
			word_length++;
		}

		recptr->word[i] = '\0';	//문자열 완성

		//--------------------------------wordidx----------------------------------


		for (; !(isdigit(buffer[i])); i++) {	//단어정보가 나올 때 까지 스킵

		}
		for (j = 0; buffer[i] != ' '; j++, i++) {	//단어정보중 제일 첫 숫자 입력
			chgint[j] = buffer[i];

		}
		chgint[j] = '\0';//문자열 완성

		recptr->wordidx = atoi(chgint);	//숫자문자열 int형으로 변형

		//-----------------------------pos------------------------------------

		for (; !(isupper(buffer[i])); i++) {	//품사열이 나올 때까지 스킵

			//품사열이 없을 경우
			if (buffer[i] == '\n')
				break;
			if (buffer[i] == '\0')
				break;
		}

		if (buffer[i] != '\n' && buffer[i] != '\0') {	//품사열이 있을 경우

			for (k = 0; buffer[i] != ' '; i++, k++) {	//처음 품사열를 구조체 문자에 넣는다

				if (buffer[i] == '\n')	//마지막 품사열일 경우
					break;
				if (buffer[i] == '\0')	//파일 끝 마지막 품사열일 경우
					break;

				recptr->pos[k] = buffer[i];

			}

			recptr->pos[k] = '\0';//문자열 완성

			wordnum++;

			//-----------------------------numpos------------------------------------

			while (buffer[i] != '\n') {//문장이 끝날때까지의 품사들 갯수

				if (buffer[i] == '\0')//파일이 끝났으면
					break;

				for (; !(isupper(buffer[i])); i++) {//품사열이 나올 때까지 스킵

					//품사열 뒤에 다른 기호가 올 경우
					if (buffer[i] == '\n')
						break;
					if (buffer[i] == '\0')
						break;
				}

				//품사열의 갯수 +1
				wordnum++;

				//품사열 
				for (; buffer[i] != ' '; i++) {

					//품사열이 더이상 없다면
					if (buffer[i] == '\n')
						break;
					if (buffer[i] == '\0')
						break;
				}

			}
		}

		recptr->numpos = wordnum;

		total_line++;

		fwrite(recptr, sizeof(rectype), 1, fpbin);	//bin파일에 구조체 데이타 입력


		//---------------------------------------------------------------------
		for (int n = 0; n < word_length; n++) {//구조체 초기화
			recptr->word[n] = ' ';
		}

		recptr->wordidx = 0;

		for (int n = 0; n < wordnum; n++) {
			recptr->pos[n] = ' ';
		}
		recptr->numpos = 0;
		//--------------------------------------------------------------------

		if (buffer[i] == '\0') {//파일이 끝났다면
			break;
		}



	}
	return total_line;
}

int SortBin(int total_line);//bin파일의 데이타를 heap sorting하는 함수

int makebin(char text[]) {//bin파일 생성

	FILE *fp, *fpbin;
	int total_line = 0;

	fp = fopen(text, "r");	//선택한 파일 open

	fpbin = fopen("all_words_occurred.bin", "w+b");	//bin파일 생성

	if (!fp) {
		printf("파일이 제대로 열리지않았습니다...");
		return 0;
	}
	if (!fpbin) {
		printf("파일이 제대로 열리지않았습니다...");
		return 0;
	}

	total_line = putdatast(fp, fpbin);//선택한 파일의 내용을 구조체에 넣어 bin파일 생성

	fclose(fpbin);
	fclose(fp);
	

	return total_line;
}

void FirstSort(FILE* fpbin, int total_line);	//초기 힙 생성(Max heap)
void SWAP(FILE * fpbin, int now, int pa);		//데이타 SWAP
void MakeHeap(FILE *fpbin, int n);				//힙 정렬
void BinaryToText(int total_line);				//bin파일->text파일

int SortBin(int total_line) {//힙 정렬

	int orgin = total_line;	//총 줄 수 보관 변수

	FILE *fpbin;

	fpbin = fopen("all_words_occurred.bin", "r+b");		//binary파일 open

	if (!fpbin) {
		printf("파일이 제대로 열리지않았습니다...");
		return 0;
	}

	FirstSort(fpbin, total_line);		//초기 힙 생성

	//힙 정렬
	total_line--;
	SWAP(fpbin, 0, total_line);

	while (total_line > 1) {

		MakeHeap(fpbin, total_line);
		total_line--;
		SWAP(fpbin, 0, total_line);

	}

	fclose(fpbin);

	return orgin;

}

void FirstSort(FILE* fpbin, int total_line) {//초기 힙 생성 함수

	int now;
	int pa = 0;	//parent
	int i;
	char now_key[100];	//now의 word
	char pa_key[100];	//parent의 word

	for (i = 1; i < total_line; i++) {

		now = i;

		while (now > 0)//now가 힙의 루트가 아니라면
		{
			pa = ((now - 1) / 2);

			//now의 word값
			fseek(fpbin, sizeof(rectype)*now, SEEK_SET);
			fread(recptr, sizeof(rectype), 1, fpbin);
			strcpy(now_key, recptr->word);

			//parent의 word값
			fseek(fpbin, sizeof(rectype)*pa, SEEK_SET);
			fread(recptr, sizeof(rectype), 1, fpbin);
			strcpy(pa_key, recptr->word);

			if (strcmp(now_key, pa_key) > 0) {//부모보다 크다면

				SWAP(fpbin, now, pa);//부모와 교환

				now = pa;//인덱스를 부모로 설정

			}
			else
			{//자리가 맞을 경우

				break;

			}

		}
	}

}

int FindMaxIndex(FILE* fpbin, int n, int now);	//now, left child, right child 중 최대값 리턴 함수

void MakeHeap(FILE* fpbin, int n) {	//최대 힙 정렬
	
	int now = 0;
	int mp = 0;
	int left = 2 * now + 1;		//left child

	while (left < n)	//왼쪽 자식이 있으면
	{
		mp = FindMaxIndex(fpbin, n, now);	//now, left child, right중 최대값

		if (mp == now) {//자리를 찾은 것
			break;
		}

		SWAP(fpbin, mp, now);

		now = mp;	//mp를 now값의 저장

		left = 2 * now + 1;

	}
}

int FindMaxIndex(FILE* fpbin, int n, int now) {

	int lc = 2 * now + 1;	//왼쪽 자식
	int rc = 2 * now + 2;	//오른쪽 자식
	char now_key[100];	//now의 word
	char lc_key[100];	//left child의 word
	char rc_key[100];	//right child의 word

	//now의 key값
	fseek(fpbin, sizeof(rectype)*now, SEEK_SET);
	fread(recptr, sizeof(rectype), 1, fpbin);
	strcpy(now_key, recptr->word);

	//left child의 key값
	fseek(fpbin, sizeof(rectype)*lc, SEEK_SET);
	fread(recptr, sizeof(rectype), 1, fpbin);
	strcpy(lc_key, recptr->word);

	//right child의 key값
	fseek(fpbin, sizeof(rectype)*rc, SEEK_SET);
	fread(recptr, sizeof(rectype), 1, fpbin);
	strcpy(rc_key, recptr->word);

	if (rc >= n) //오른쪽 자식이 없을 때
	{
		if (strcmp(lc_key, now_key) > 0) {//왼쪽 자식이 더 클 때
			return lc;
		}
		//now가 더 크다면
		return now;
	}

	if (strcmp(rc_key, lc_key) > 0) //right child > left child 일 때
	{

		if (strcmp(rc_key, now_key) > 0)	//right child가 now 보다 크다면
		{
			return rc;
		}
		else   //now가 right child보다 크다면
			return now;
	

	}
	if (strcmp(lc_key, now_key) > 0) //left child가 now보다 크다면
	{
		return lc;
	}
	else    //now가 left child보다 크다면
		return now;

}
void SWAP(FILE * fpbin, int a, int b) {

	arec buff;	//임시 저장 구조체 변수
	arec *buff_ptr = &buff;

	fseek(fpbin, sizeof(rectype)*a, SEEK_SET);//buff <- now
	fread(buff_ptr, sizeof(buff), 1, fpbin);

	fseek(fpbin, sizeof(rectype)*b, SEEK_SET);//now <- parent
	fread(recptr, sizeof(rectype), 1, fpbin);
	fseek(fpbin, sizeof(rectype)*a, SEEK_SET);
	fwrite(recptr, sizeof(rectype), 1, fpbin);

	fseek(fpbin, sizeof(rectype)*b, SEEK_SET);//parent <- buff
	fwrite(buff_ptr, sizeof(buff), 1, fpbin);

}



int NoOverlapped(FILE* fpbin, int n, char key[]);	//중복 제거 함수

void BinaryToText(int total_line) {		//bin파일-> text파일

	FILE * fptext;
	FILE * fpbin;
	int check=0;//중복여부 변수
	char key[100];
	int fpf_error = 0;	//fprintf error 검사 변수

	fptext = fopen("words.txt", "w");
	fpbin = fopen("all_words_occurred.bin", "r+b");

	if (!fpbin) {
		printf("바이너리 파일이 제대로 열리지않았습니다...");
		return;
	}

	if (!fptext) {
		printf("텍스트 파일이 제대로 열리지않았습니다...");
		return;
	}

	for (int i = 0; i < total_line; i++)	//bin파일에서 한 줄씩 읽어 text파일에 입력
	{
		fseek(fpbin, sizeof(rectype)*i, SEEK_SET);
		fread(recptr, sizeof(rectype), 1, fpbin);
		strcpy(key, recptr->word);
		check = NoOverlapped(fpbin, i, key);//단어 중복 여부 확인

		if (check == 0) //단어가 중복됨
		{
			i++;	//그 바로 뒤 데이타

			for (; i < total_line; i++) {	//그 뒤에 또 중복되는지 확인

				fseek(fpbin, sizeof(rectype)*i, SEEK_SET);
				fread(recptr, sizeof(rectype), 1, fpbin);

				if (strcmp(key, recptr->word) == 0)	//중복이라면 넘어감
				{

				}
				else //그 뒤 데이타가 중복이 아니라면
				{   
					check = 1;
					break;
				}
			}
		}


		if (check == 1) //중복되지않는다
		{
			//중복 검사로 인해 변한 포인터를 다시 바꿔준다
			fseek(fpbin, sizeof(rectype)*i, SEEK_SET);
			fread(recptr, sizeof(rectype), 1, fpbin);

			//words.txt 파일에 입력
			fpf_error = fprintf(fptext, "%s %d %s %d\n", recptr->word, recptr->wordidx, recptr->pos, recptr->numpos);

			if (fpf_error == -1)	//fprintf 오류
			{
				printf("입력에 대해 오류가 발생하였습니다....");
				return;
			}
		}
	

	}

	fclose(fpbin);
	fclose(fptext);
	

}

int NoOverlapped(FILE* fpbin, int n, char key[]) {

	if (n != 0)	//제일 첫 데이타가 아니라면 
	{

		fseek(fpbin, sizeof(rectype)*(n - 1), SEEK_SET);	//그 전 데이타 검색
		fread(recptr, sizeof(rectype), 1, fpbin);

		if (strcmp(key, recptr->word) == 0) {
			return 0;//단어가 중복됨
		}
	}
	return 1;//단어가 중복되지않음

}



int main(void) {
	char text[30];
	int total_line = 0;
	printf("입력 텍스트 화일명은?");
	scanf("%s", text);
	total_line = makebin(text);//데이터를 뽑아 bin파일에 입력
	total_line = SortBin(total_line);//bin파일 내에서 heap sorting
	BinaryToText(total_line);//sorting한 bin파일 내용을 text파일로 옮김

	return 0;


}