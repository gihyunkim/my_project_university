#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning (disable:4996)
#define MAXK 4 //2d
#define halfK 2 //d

//입력 데이터 저장 구조체

typedef struct _rec {
	char wstr[100];
	char pos[10];
	int numpos;
}type_rec;

typedef struct node *nodeptr;

//노드
typedef struct node {
	nodeptr ptr[MAXK + 1];
	type_rec record[MAXK];
	int fill_cnt;
}node;

//빅노드 ( 일반 노드보다 레코드 수와 노드포인터수가 1개 더 많은 노드 )
typedef struct bignode {
	nodeptr ptr[MAXK + 2];
	type_rec record[MAXK + 1];
}bignode;

//일반 노드보다 두 배 더 큰 노드
typedef struct two_bignode {
	nodeptr ptr[2*MAXK + 1];
	type_rec record[2*MAXK];
}two_bignode;

//root노드를 가리키는 포인터
nodeptr root = NULL;

int b_tree_insertion(type_rec in_rec, nodeptr *root);

int putdatast(char text[30]) {//데이타를 구조체에 입력

	char buffer[200];	//단어열을 담기위한 임시배열
	int wordnum = 0;	//품사의 총 갯수
	int check = 0;		//파일이 비어있지않았다는 여부 확인 변수( 1이면 비어있지 않은 파일 )
	char *get_err = NULL; //fgets에러점검용
	FILE * fp = fopen(text, "r+");
	type_rec one_record;
	type_rec* recptr = &one_record;

	if (!fp) {
		printf("파일이 제대로 열리지않았습니다...\n");
		return 1;
	}

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

		for (; !(isspace(buffer[i])); i++) {	//처음 문자열 넘김

		}

		for (; isspace(buffer[i]); i++) {	//스페이스 넘김

		}

		for (; !(isspace(buffer[i])); i++) {	//두번째 문자열도 넘김

		}

		for (; isspace(buffer[i]); i++) {	//스페이스 넘김

		}

		for (j = 0; !(isspace(buffer[i])); i++, j++) {	//세번째 문자열(본 문자열)을 구조체 문자에 넣는다
			recptr->wstr[j] = buffer[i];
			word_length++;
		}

		recptr->wstr[j] = '\0';	//문자열 완성

		//-----------------------------pos------------------------------------

		for (; !(isupper(buffer[i])); i++) {	//품사열이 나올 때까지 스킵

												//품사열이 없을 경우
			if (buffer[i] == '\n') {
				strcpy(recptr->pos, "  ");
				break;
			}
			if (buffer[i] == '\0') {
				strcpy(recptr->pos, "  ");
				break;
			}
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

		b_tree_insertion(one_record, &root);

		//---------------------------------------------------------------------
		for (int n = 0; n < word_length; n++) {//구조체 초기화
			recptr->wstr[n] = ' ';
		}

		for (int n = 0; n < wordnum; n++) {
			recptr->pos[n] = ' ';
		}
		recptr->numpos = 0;
		//--------------------------------------------------------------------

		if (buffer[i] == '\0') {//파일이 끝났다면
			break;
		}
	}
	fclose(fp);
}


int b_tree_insertion(type_rec in_rec, nodeptr *root) {

	char key[100];
	int i, j, k, m;
	int top = -1;
	type_rec* recptr = &in_rec;

	nodeptr rnew;	//새 root용 노드
	nodeptr new;	//꽉 찼을 시의 새 노드
	nodeptr stack[50];	//부모 보관용
	nodeptr curr;	//현재 노드
	nodeptr P;	//보관용 포인터
	bignode bnode;	//bignode( 보통 node보다 레코드와 포인터수가 하나씩 더 많은 노드 )

	nodeptr n;

	if (!*root) {
		n = (nodeptr)malloc(sizeof(node));
		n->record[0] = in_rec;
		n->ptr[0] = n->ptr[1] = NULL;
		n->fill_cnt = 1;
		*root = n;
		return 0;
	}

	curr = *root;

	while (1) {	//데이터가 들어갈 leaf노드를 찾는다

		strcpy(key, recptr->wstr);

		for (i = 0; i < curr->fill_cnt; i++) {
			if (strcmp(key, curr->record[i].wstr) < 0) {//입력데이터가 curr의 어떤 데이터보다 작다면
				P = curr->ptr[i];	//그 데이터의 왼쪽 자식포인터를 P에 넣음
				break;
			}
			else if (strcmp(key, curr->record[i].wstr) == 0) {	//중복이라면
				return 1;
			}
		}

		if (i == curr->fill_cnt) {//curr의 제일 큰 데이터보다 크다면
			P = curr->ptr[i];	//그 데이터의 오른쪽 자식 포인터를 P에 넣음
		}

		if (P) {	//자식이 존재
			top++;
			stack[top] = curr;
			curr = P;
			continue;
		}
		else
		{
			break;//자식이 존재 하지 않음
		}

	}

	while (1) {

		strcpy(key, recptr->wstr);

		if (curr->fill_cnt != MAXK) {	//curr가 다 차지 않았을 경우

			for (i = 0; i < curr->fill_cnt; i++) {
				if (strcmp(key, curr->record[i].wstr) < 0) {//입력데이터가 curr의 데이터들보다 작다면
					for (j = curr->fill_cnt - 1; j >= i; j--) {//오른쪽으로 한칸씩 push
						curr->record[j + 1] = curr->record[j];
						curr->ptr[j + 2] = curr->ptr[j + 1];
					}
					//입력데이터 적합한 자리에 넣기
					curr->record[i] = in_rec;
					curr->ptr[i + 1] = P;
					curr->fill_cnt++;
					return 1;
				}
			}
			if (i == curr->fill_cnt) {//curr의 데이터들보다 크다면
				curr->record[i] = in_rec;	//마지막 자리에 넣기
				curr->ptr[i + 1] = P;
				curr->fill_cnt++;
				return 1;
			}
		}
		else {	//curr가 다 찼을 경우

			for (k = 0; k < MAXK; k++) {	//key값보다 작은값들 찾기
				if (strcmp(key, curr->record[k].wstr) < 0) //다 찾았으면 break
					break;
			}

			bnode.ptr[0] = curr->ptr[0];

			for (m = 0; m < k; m++) {	//key값보다 작은값들 bnode에 먼저 넣기
				bnode.ptr[m + 1] = curr->ptr[m + 1];
				bnode.record[m] = curr->record[m];
			}

			//그 다음, 입력 데이터 넣기
			bnode.ptr[m + 1] = P;
			bnode.record[m] = in_rec;
			m++;

			//나머지 bnode에 넣기
			for (; m < MAXK + 1; m++) {
				bnode.ptr[m + 1] = curr->ptr[m];
				bnode.record[m] = curr->record[m - 1];
			}

			for (i = 0; i < halfK; i++) {	//왼쪽 반을 curr에 넣어준다
				curr->ptr[i] = bnode.ptr[i];
				curr->record[i] = bnode.record[i];
			}
			curr->fill_cnt = halfK;
			curr->ptr[i] = bnode.ptr[i];

			for (; i < MAXK; i++) {	//curr의 나머지 데이터 삭제
				curr->ptr[i + 1] = NULL;
				nodeptr *buff = &curr->record[i];
				*buff = NULL;
				curr->record[i].numpos = 0;
				buff = &curr->record[i].pos;
				*buff = NULL;

			}

			//new노드 생성 후 오른쪽 반 데이터 넣기
			new = (nodeptr)malloc(sizeof(node));


			for (i = 0; i < halfK; i++) {

				new->ptr[i] = bnode.ptr[i + halfK + 1];
				new->record[i] = bnode.record[i + halfK + 1];
			}
			new->ptr[i] = bnode.ptr[i + halfK + 1];
			new->fill_cnt = halfK;

			//가운데 데이터
			P = new;
			in_rec = bnode.record[halfK];

			if (top >= 0) {//부모 노드가 존재한다면
				curr = stack[top];
				top--;
				continue;
			}
			else {//부모 노드가 존재하지 않는다면
				rnew = (nodeptr)malloc(sizeof(node));
				rnew->ptr[0] = curr;
				rnew->record[0] = in_rec;
				rnew->ptr[1] = P;
				rnew->fill_cnt = 1;
				*root = rnew;	//부모 노드가 존재하지 않는다면 이 새 노드가 루트가 됨
				return 1;
			}
		}
	}
}

type_rec makeRec(char word[100]) {
	type_rec in_rec;

	strcpy(in_rec.wstr, word);
	in_rec.numpos = 0;
	strcpy(in_rec.pos, "AA");
	
	return in_rec;

}

int B_tree_Insertion_in_test(type_rec in_rec, nodeptr * root) {	//record를 삽입하는 함수 (성공이면 split횟수 리턴, 실패면 -1 리턴)
	char key[100];
	int i, j, k, m;
	int top = -1;
	int split = 0;	//split 횟수
	type_rec* recptr = &in_rec;

	nodeptr rnew;	//새 root용 노드
	nodeptr new;	//꽉 찼을 시의 새 노드
	nodeptr stack[50];	//부모 보관용
	nodeptr curr;	//현재 노드
	nodeptr P;	//보관용 포인터
	bignode bnode;	//bignode( 보통 node보다 레코드와 포인터수가 하나씩 더 많은 노드 )
	nodeptr n;

	if (!*root) {
		n = (nodeptr)malloc(sizeof(node));
		n->record[0] = in_rec;
		n->ptr[0] = n->ptr[1] = NULL;
		n->fill_cnt = 1;
		*root = n;
		return split;
	}

	curr = *root;

	while (1) {	//데이터가 들어갈 leaf노드를 찾는다

		strcpy(key, recptr->wstr);

		for (i = 0; i < curr->fill_cnt; i++) {
			if (strcmp(key, curr->record[i].wstr) < 0) {//입력데이터가 curr의 어떤 데이터보다 작다면
				P = curr->ptr[i];	//그 데이터의 왼쪽 자식포인터를 P에 넣음
				break;
			}
			else if (strcmp(key, curr->record[i].wstr) == 0) {	//중복이라면 실패
				return -1;
			}
		}

		if (i == curr->fill_cnt) {//curr의 제일 큰 데이터보다 크다면
			P = curr->ptr[i];	//그 데이터의 오른쪽 자식 포인터를 P에 넣음
		}

		if (P) {	//자식이 존재
			top++;
			stack[top] = curr;
			curr = P;
			continue;
		}
		else
		{
			break;//자식이 존재 하지 않음
		}

	}

	while (1) {

		strcpy(key, recptr->wstr);

		if (curr->fill_cnt != MAXK) {	//curr가 다 차지 않았을 경우

			for (i = 0; i < curr->fill_cnt; i++) {
				if (strcmp(key, curr->record[i].wstr) < 0) {//입력데이터가 curr의 데이터들보다 작다면
					for (j = curr->fill_cnt - 1; j >= i; j--) {//오른쪽으로 한칸씩 push
						curr->record[j + 1] = curr->record[j];
						curr->ptr[j + 2] = curr->ptr[j + 1];
					}
					//입력데이터 적합한 자리에 넣기
					curr->record[i] = in_rec;
					curr->ptr[i + 1] = P;
					curr->fill_cnt++;
					return split;
				}
			}
			if (i == curr->fill_cnt) {//curr의 데이터들보다 크다면
				curr->record[i] = in_rec;	//마지막 자리에 넣기
				curr->ptr[i + 1] = P;
				curr->fill_cnt++;
				return split;
			}
		}
		else {	//curr가 다 찼을 경우

			for (k = 0; k < MAXK; k++) {	//key값보다 작은값들 찾기
				if (strcmp(key, curr->record[k].wstr) < 0) //다 찾았으면 break
					break;
			}

			bnode.ptr[0] = curr->ptr[0];

			for (m = 0; m < k; m++) {	//key값보다 작은값들 bnode에 먼저 넣기
				bnode.ptr[m + 1] = curr->ptr[m + 1];
				bnode.record[m] = curr->record[m];
			}

			//그 다음, 입력 데이터 넣기
			bnode.ptr[m + 1] = NULL;
			bnode.record[m] = in_rec;
			m++;

			//나머지 bnode에 넣기
			for (; m < MAXK + 1; m++) {
				bnode.ptr[m + 1] = curr->ptr[m];
				bnode.record[m] = curr->record[m - 1];
			}

			for (i = 0; i < halfK; i++) {	//왼쪽 반을 curr에 넣어준다
				curr->ptr[i] = bnode.ptr[i];
				curr->record[i] = bnode.record[i];
			}
			curr->fill_cnt = halfK;
			curr->ptr[i] = bnode.ptr[i];

			for (; i < MAXK; i++) {	//curr의 나머지 데이터 초기화

				nodeptr *buff = &curr->record[i];

				curr->ptr[i + 1] = NULL;
				*buff = NULL;
				curr->record[i].numpos = 0;
				buff = &curr->record[i].pos;
				*buff = NULL;

			}

			//new노드 생성 후 오른쪽 반 데이터 넣기
			new = (nodeptr)malloc(sizeof(node));


			for (i = 0; i < halfK; i++) {

				new->ptr[i] = bnode.ptr[i + halfK + 1];
				new->record[i] = bnode.record[i + halfK + 1];
			}
			new->ptr[i] = bnode.ptr[i + halfK + 1];
			new->fill_cnt = halfK;

			//가운데 데이터
			P = new;
			in_rec = bnode.record[halfK];

			split++;

			if (top >= 0) {//부모 노드가 존재한다면
				curr = stack[top];
				top--;
				continue;
			}
			else {//부모 노드가 존재하지 않는다면
				rnew = (nodeptr)malloc(sizeof(node));
				rnew->ptr[0] = curr;
				rnew->record[0] = in_rec;
				rnew->ptr[1] = P;
				rnew->fill_cnt = 1;
				*root = rnew;	//부모 노드가 존재하지 않는다면 이 새 노드가 루트가 됨
				return split;
			}
		}
	}


}

int B_tree_Search(char word[100], nodeptr root) {	//root노드의 level을 0이라하고 그 아래부터 1씩 증가

	char key[100];
	int i;
	int top = -1;
	int level = 0;

	nodeptr stack[50];	//부모 보관용
	nodeptr curr;	//현재 노드
	nodeptr P;	//보관용 포인터

	curr = root;

	while (1) {	

		strcpy(key, word);

		for (i = 0; i < curr->fill_cnt; i++) {
			if (strcmp(key, curr->record[i].wstr) < 0) {//입력데이터가 curr의 어떤 데이터보다 작다면
				P = curr->ptr[i];	//그 데이터의 왼쪽 자식포인터를 P에 넣음
				break;
			}
			else if (strcmp(key, curr->record[i].wstr) == 0) {	//찾았다면
				printf("해당 이름은 LEVEL %d에 있는 레코드 내 %d번째에 있습니다.\n", level, i + 1);
				return 0;
			}
		}

		if (i == curr->fill_cnt) {//curr의 제일 큰 데이터보다 크다면
			P = curr->ptr[i];	//그 데이터의 오른쪽 자식 포인터를 P에 넣음
		}

		if (P) {	//자식이 존재
			top++;
			level = top + 1;
			stack[top] = curr;
			curr = P;
			continue;
		}
		else
		{
			break;//자식이 존재 하지 않음
		}

	}
	printf("해당 이름을 찾을 수가 없습니다.\n");
	return -1;

}

int B_tree_Deletion(char word[100], nodeptr *root) {

	char key[100];

	int i, j, k, m;
	int top = -1;
	int retri=0;	//재분배 횟수
	int merge=0;	//합병 횟수
	int middle = 0; //bignode의 총 레코드 수의 반

	nodeptr stack[50];	//부모 보관용
	nodeptr curr;	//현재 노드
	nodeptr succ; //successor 탐색용
	nodeptr parent;	//balancing에서 sibling 여부를 알기위한 부모노드
	nodeptr left_sibling;	//왼쪽 형제
	nodeptr right_sibling;	//오른쪽 형제
	nodeptr P;	//보관용 포인터
	nodeptr * ptr;	//노드 이중 포인터

	two_bignode tbnode;

	if (!*root) {
		printf("데이터가 하나도 존재하지 않습니다....\n");
		return 1;
	}

	curr = *root;

	strcpy(key, word);

	while (1) {	//삭제할 데이터가 있는 노드를 탐색

		for (i = 0; i < curr->fill_cnt; i++) {
			if (strcmp(key, curr->record[i].wstr) < 0) {//삭제할 문자열이 curr노드의 어떤 값보다 작다면
				P = curr->ptr[i];	//그 데이터의 왼쪽 자식포인터를 P에 넣음
				break;
			}
			else if (strcmp(key, curr->record[i].wstr) == 0) {	//삭제할 데이터가 있는 노드 찾음

				//오른쪽 자식 포인터를 successor 탐색 포인터에 넣음
				succ = curr->ptr[i + 1];

				//successor 탐색
				if (succ) {	//만약 자식 노드가 존재한다면 삭제할 레코드의 오른쪽 자식으로 내려감
					top++;
					stack[top] = curr;

					while (succ->ptr[0]) {	//leaf노드가 나올 때 까지 왼쪽 자식으로 계속 내려감
						P = succ->ptr[0];
						top++;
						stack[top] = succ;
						succ = P;
					}

					//나온 leaf 노드의 제일 첫 레코드가 successor이다.
					//successor와 삭제할 값을 서로 교환해주는 작업

					curr->record[i] = succ->record[0];	//successor를 원래 지울 레코드에 대체

					//삭제할 레코드가 있는 위치로 이동 ( successor가 있던 노드 )
					curr = succ;
					
					//레코드 삭제
					ptr = &curr->record[0].wstr;
					*ptr = NULL;
					curr->record[0].numpos = 0;
					ptr = &curr->record[0].pos;
					*ptr = NULL;
					curr->fill_cnt--;

					//그 오른쪽 포인터 삭제
					curr->ptr[1] = NULL;

					for (j = 0; j < curr->fill_cnt; j++) {
						curr->record[j] = curr->record[j + 1];
						curr->ptr[j + 1] = curr->ptr[j + 2];
					}


					if (top==-1) {//현재 노드가 root노드라면
						ptr = &curr->record[0];
						if (!*ptr) {//루트노드의 레코드가 존재하지않는다면
							free(curr);
						}
						else {//루트노드의 레코드가 존재							
							printf("삭제에 성공하였습니다!! 재분배는 %d번, 합병은 %d번하였습니다\n", retri, merge);
							return 0;
						}
					}

					while (1) {
						if (curr->fill_cnt < halfK) {	//노드가 balancing에 어긋남
							
							//부모로 올라가 오른쪽 형제나 왼쪽 형제가 있는지 확인 (오른쪽 형제를 선호)
							parent = stack[top];
							top--;

							for (j = 0; j < parent->fill_cnt; j++) {
								if (parent->ptr[j] == curr) {
									break;
								}
							}

							//j가 parent에서의 curr노드 포인터

							if (j != 0) {
								left_sibling = parent->ptr[j - 1];						
							}
							if (j != MAXK) {
								right_sibling = parent->ptr[j + 1];
							}
							 
							if (right_sibling&&right_sibling->fill_cnt > halfK) {	//오른쪽 형제에게 빌려옴 ( 재분배가 가능 )

								//tbnode에 먼저 curr값을 넣는다
								tbnode.ptr[0] = curr->ptr[0];
								for (k = 0; k < curr->fill_cnt; k++) {
									tbnode.ptr[k + 1] = curr->ptr[k + 1];
									tbnode.record[k] = curr->record[k];
								}
								
								//그 다음, curr와 오른쪽 형제 사이의 부모의 레코드 값을 넣는다.
								tbnode.record[k] = parent->record[j];	
								k++;

								tbnode.ptr[k] = right_sibling->ptr[0];
								for (m=0; m < right_sibling->fill_cnt; k++, m++) {
									tbnode.ptr[k + 1] = right_sibling->ptr[m + 1];
									tbnode.record[k] = right_sibling->record[m];
								}

								//k에 two_bignode 총 레코드 수가 들어있음

								middle = k / 2;
								//two_bignode에서 middle번째 레코드를 기준으로 왼쪽을 curr에 넣는다.
								for (i = 0; i < middle; i++) {
									curr->ptr[i] = tbnode.ptr[i];
									curr->record[i] = tbnode.record[i];
								}
								curr->ptr[i] = tbnode.ptr[i];
								curr->fill_cnt = middle;
								
								//parent에다가 가운데 값인 halfK번째 레코드 값을 넣는다.
								parent->record[j] = tbnode.record[halfK];
								i++;

								//오른쪽 자식에 나머지 two_bignode값들을 넣는다.
								for (m=0; i < k; m++,i++) {
									right_sibling->ptr[m] = tbnode.ptr[i];
									right_sibling->record[m] = tbnode.record[i];
								}
								right_sibling->ptr[m] = tbnode.ptr[i];
								right_sibling->fill_cnt = k - (middle + 1);	//two_bignode의 총 레코드 수에서 curr에 넣은 반과 parent에 넣은 값을 제외한 나머지 수

								retri++;

								printf("삭제에 성공하였습니다!! 재분배는 %d번, 합병은 %d번하였습니다\n", retri, merge);
								return 0;
							}
							else if (left_sibling&&left_sibling->fill_cnt > halfK) {	//왼쪽 형제에게 빌려옴 ( 재분배가 가능 )
							

								//tbnode에 먼저 왼쪽 자식노드의 값을 넣는다
								tbnode.ptr[0] = left_sibling->ptr[0];
								for (k = 0; k < left_sibling->fill_cnt; k++) {
									tbnode.ptr[k + 1] = left_sibling->ptr[k + 1];
									tbnode.record[k] = left_sibling->record[k];
								}

								tbnode.record[k] = parent->record[j-1];	//그 다음, curr와 왼쪽 형제 사이의 부모의 레코드 값을 넣는다.
								k++;								

								//그 다음, curr의 값들을 two_bignode에 넣는다
								tbnode.ptr[k] = curr->ptr[0];
								for (m = 0; m < curr->fill_cnt; k++, m++) {
									tbnode.ptr[k + 1] = curr->ptr[m + 1];
									tbnode.record[k] = curr->record[m];
								}

								//k에 two_bignode 총 레코드 수가 들어있음
								middle = k / 2;
								
								//two_bignode에서 middle번째 레코드를 기준으로 왼쪽을 curr에 넣는다. 		
								for (i = 0; i < middle; i++) {
									left_sibling->ptr[i] = tbnode.ptr[i];
									left_sibling->record[i] = tbnode.record[i];
								}
								left_sibling->ptr[i] = tbnode.ptr[i];
								left_sibling->fill_cnt = middle;

								//parent에다가 가운데 값인 middle번째 레코드 값을 넣는다.
								parent->record[j] = tbnode.record[middle];

								i++;

								//curr에 나머지 two_bignode값들을 넣는다.
								for (m = 0; i < k; m++, i++) {
									curr->ptr[m] = tbnode.ptr[i];
									curr->record[m] = tbnode.record[i];
								}
								curr->ptr[m] = tbnode.ptr[i];
								curr->fill_cnt = k - (middle + 1);	//two_bignode의 총 레코드 수에서 왼쪽 형제에 넣은 반과 parent에 넣은 값을 제외한 나머지 수
							
								retri++;

								printf("삭제에 성공하였습니다!! 재분배는 %d번, 합병은 %d번하였습니다\n", retri, merge);

								return 0;
							}
							else {	//합병을 해야한다. ( 재분배가 불가능 )

								int next = curr->fill_cnt;	//curr의 들어가있는 레코드 다음에 넣을 인덱스

								if (right_sibling) {	//오른쪽 형제가 있다면
									
									//curr와 오른쪽 형제 포인터 사이에 있는 레코드를 넣는다
									curr->record[next] = parent->record[j];
									next++;

									//그 다음, 오른쪽 형제의 값들을 curr에 나머지 부분에 넣는다.
									curr->ptr[next] = right_sibling->ptr[0];
									for (i=0; i < right_sibling->fill_cnt; next++,i++) {
										curr->record[next] = right_sibling->record[i];
									}

									//오른쪽 형제 노드 해제
									free(right_sibling);
									
									//parent에서 curr와 오른쪽 형제 사이에 있던 레코드를 기준으로 왼쪽으로 한칸씩 shift
									for (; j + 1 < parent->fill_cnt; j++) {
										parent->record[j] = parent->record[j + 1];
										parent->ptr[j + 1] = parent->ptr[j + 2];
									}
									
									//한칸 씩 옮겼다면 마지막으로 옮긴 레코드의 원래 위치 레코드와 포인터 초기화
									ptr = &parent->record[j].wstr;
									*ptr = NULL;
									ptr = &parent->record[j].pos;
									*ptr = NULL;
									parent->record[j].numpos = 0;
									parent->ptr[j + 1] = NULL;

									parent->fill_cnt--;

									curr = parent;	//curr에 부모 포인터를 넣고 다시 반복
									top--;
									merge++;
									continue;
									
								}else {//왼쪽 형제와 합병
									//curr의 값들을 왼쪽 형제의 레코드들과 curr와 왼쪽 형제 사이의 parent 레코드까지 합친 수만큼 오른쪽으로 shift
									for (i = 0; i < curr->fill_cnt; i++) {
										curr->ptr[i + (left_sibling->fill_cnt + 1)] = curr->ptr[i];	
										curr->record[i + (left_sibling->fill_cnt + 1)] = curr->record[i];
									}
									curr->ptr[i + (left_sibling->fill_cnt + 1)] = curr->ptr[i];
									
									//그 다음, curr와 왼쪽 형제 사이의 parent레코드를 옮겨진 curr의 값들 왼쪽에 넣는다.
									curr->record[left_sibling->fill_cnt] = parent->record[j - 1];

									//그리고 왼쪽 형제의 값들을 curr에 처음부터 넣는다.
									for (i = 0; i < left_sibling->fill_cnt; i++) {
										curr->ptr[i] = left_sibling->ptr[i];
										curr->record[i] = left_sibling->record[i];
									}
									curr->ptr[i] = left_sibling->ptr[i];
									
									free(left_sibling);	//왼쪽 형제노드 해제

									//parent에서 curr와 왼쪽 형제 사이에 있던 레코드를 기준으로 왼쪽으로 한칸씩 shift
									for (; j  < parent->fill_cnt; j++) {
										parent->record[j - 1] = parent->record[j];
										parent->ptr[j - 1] = parent->ptr[j];
									}
									parent->ptr[j - 1] = parent->ptr[j];

									//한칸 씩 옮겼다면 마지막으로 옮긴 레코드의 원래 위치 레코드와 포인터 초기화
									ptr = &parent->record[j-1].wstr;
									*ptr = NULL;
									ptr = &parent->record[j-1].pos;
									*ptr = NULL;
									parent->record[j-1].numpos = 0;
									parent->ptr[j] = NULL;

									parent->fill_cnt--;

									curr = parent;  //curr에 부모 포인터를 넣고 다시 반복
									top--;
									merge++;
									continue;
								}
								
							}

						}
						else {	//balancing이 맞음

							printf("삭제에 성공하였습니다!! 재분배는 %d번, 합병은 %d번하였습니다\n", retri, merge);
							return 0;
						}
					}
				}
				else {	//현재 노드가 leaf노드 이므로 바로 삭제한다.
					ptr = &curr->record[i].wstr;
					*ptr = NULL;
					curr->record[i].numpos = 0;
					ptr = &curr->record[i].pos;
					*ptr = NULL;
					curr->fill_cnt--;
					printf("삭제에 성공하였습니다!! 재분배는 %d번, 합병은 %d번하였습니다\n", retri, merge);
					return 0;
				}
				
				

			}
		}

		if (i == curr->fill_cnt) {//curr의 제일 큰 데이터보다 크다면
			P = curr->ptr[i];	//그 데이터의 오른쪽 자식 포인터를 P에 넣음
		}

		if (P) {	//자식이 존재
			top++;
			stack[top] = curr;
			curr = P;
			continue;
		}
		else
		{
			printf("삭제하려는 값이 존재하지않습니다...\n");
			return 1;//삭제할 값이 존재하지않음
		}
	}
}


int B_tree_Sequential_print(nodeptr root) {

	FILE * fp = fopen("SeqData.txt", "w");
	int i = 0;
	int j = 0;
	int on[100];	//부모의 i 저장용( 부모가 어느 자식까지 확인했는지 체크 )
	int top = -1;	//현재 노드의 level root가 -1 자식으로 내려갈 수록 1씩 +

	nodeptr stack[50];	//부모 보관용
	nodeptr curr;	//현재 노드
	nodeptr P;	//보관용 포인터

	if (!root) {
		printf("데이터가 하나도 존재하지 않습니다....\n");
		return 1;
	}

	curr = root;

	while (1) {

		if (i > curr->fill_cnt) {	//현재 노드의 모든 데이터를 print했으면

			if (top >= 0) {//부모가 존재
				//부모로 올라간 후, on[top] ++
				curr = stack[top];
				on[top]++;
				i = on[top];
				top--;

				if ((i - 1) < curr->fill_cnt)	//레코드가 존재한다면 출력
					fprintf(fp, "%s %s %d\n", curr->record[i - 1].wstr, curr->record[i - 1].pos, curr->record[i - 1].numpos);

				continue;
			}
			else {	//루트노드라는 의미
				printf("SeqData.txt 파일에 출력 완료하였습니다.\n");
				return 1;
			}

		}
		else     //다음 자식 체크
			P = curr->ptr[i];

		if (i < curr->fill_cnt && !P) {	//어떤 레코드의 왼쪽 자식이 존재하지 않을 때
			for (; i < curr->fill_cnt; i++) {
				fprintf(fp, "%s %s %d\n", curr->record[i].wstr, curr->record[i].pos, curr->record[i].numpos);
			}
			i++;
			continue;
		}
		else if (i == curr->fill_cnt && !P) {	//맨우측 레코드는 존재하는데 그 우측 자식이 존재하지 않을 때
			i++;
			continue;
		}

		if (P) {	//자식이 존재

			//스택에 현재 노드를 저장 후 자식으로 내려감
			top++;
			on[top] = i;
			i = 0;
			stack[top] = curr;
			curr = P;
			continue;
		}
		else
		{
			//자식이 아예 없는 노드의 경우, 순차적으로 모두 출력
			for (j = 0; j < curr->fill_cnt; j++) {
				fprintf(fp, "%s %s %d\n", curr->record[j].wstr, curr->record[j].pos, curr->record[j].numpos);
			}

			if (top >= 0) {//부모가 존재
				curr = stack[top];
				on[top]++;
				i = on[top];
				top--;

				if ((i - 1) < curr->fill_cnt)
					fprintf(fp, "%s %s %d\n", curr->record[i - 1].wstr, curr->record[i - 1].pos, curr->record[i - 1].numpos);

				continue;
			}
			else {	//출력 끝
				printf("SeqData.txt 파일에 출력 완료하였습니다.\n");
				return 1;
			}

		}
	}


	fclose(fp);


}


int main() {
	char text[30];
	char ins[30];	//명령어 변수
	char data[100];	//데이터 변수
	int split = 0;
	int success = 1;	//에러 여부	( 성공 = 0 에러 = 1)
	type_rec in_rec;
	while (success == 1) {	//실패면 반복, 성공이면 빠져나감
		printf("입력 텍스트 화일명은?");
		scanf("%s", text);
		getchar();
		success = putdatast(text);
	}
	while (1) {
		printf("Command? ");

		for (int i = 0;; i++) {	//명령어 변수 받기
			ins[i] = getchar();
			if (ins[i] == '\n') {
				ins[i] = '\0';
				break;
			}
			if (ins[i] == ' ') {	//데이터 변수가 필요하다면 데이터 변수 받기
				ins[i] = '\0';
				for (int j = 0;; j++) {
					data[j] = getchar();

					if (data[j] == '\n') {
						data[j] = '\0';
						break;
					}
				}
				break;
			}
		}



		if (strcmp(ins, "i") == 0) {	//insertion
			in_rec = makeRec(data);
			split = B_tree_Insertion_in_test(in_rec, &root);

			if (split == -1) {
				printf("중복입니다!! 입력에 실패하였습니다\n");
				continue;
			}
			else {
				printf("삽입해 성공하였습니다!! split 횟수는 %d번 입니다.\n", split);
				continue;
			}
		}
		else if (strcmp(ins, "retrieve") == 0) {	//search
			B_tree_Search(data, root);
		}
		else if (strcmp(ins, "delete") == 0) {	//deletion
			B_tree_Deletion(data, &root);
		}
		else if (strcmp(ins, "seqprint") == 0) {	//printout
			B_tree_Sequential_print(root);
		}
		else if (strcmp(ins, "exit") == 0) {
			printf("프로그램을 종료합니다....");
			return 0;
		}
		else {
			printf("잘못된 명령어 입니다.\n");
		}
	}

}