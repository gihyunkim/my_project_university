#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXK 4 //2d
#define halfK 2 //d
#pragma warning (disable:4996)

typedef struct idxnode *type_ptr_idxnode; //indexnode 의 포인터
typedef struct datanode *type_ptr_datanode;

typedef struct _rec {	//레코드구조체
	char wstr[100];
	char pos[10];
	int numpos;
}type_rec;

//인덱스 노드 ( B-TREE로 구성됨 )
typedef struct idxnode {
	char key[100][100];
	type_ptr_idxnode idx_ptr[MAXK + 1];
	type_ptr_datanode data_ptr[MAXK + 1];
	int fill_cnt;
}idxnode;

//데이터 노드
typedef struct datanode {
	type_rec rec[MAXK];
	type_ptr_datanode data_ptr;
	int fill_cnt;
}datanode;

//빅노드 ( 일반 노드보다 레코드 수와 노드포인터수가 1개 더 많은 노드 )(인덱스 노드용 )
typedef struct idx_bignode {
	type_ptr_idxnode idx_ptr[MAXK + 2];
	type_ptr_datanode data_ptr[MAXK + 2];
	char key[MAXK + 1][100];
}idx_bignode;

//빅노드(데이터 노드용)
typedef struct data_bignode {

	type_rec rec[MAXK + 1];
}data_bignode;

//일반 노드보다 두 배 더 큰 노드(인덱스노드용)
typedef struct idx_two_bignode {
	type_ptr_idxnode idx_ptr[2 * MAXK + 1];
	type_ptr_datanode data_ptr[2 * MAXK + 1];
	char key[2 * MAXK][100];
}idx_two_bignode;

//일반 노드보다 두 배 더 큰 노드(데이터노드용)
typedef struct data_two_bignode {

	type_rec rec[2 * MAXK];
}data_two_bignode;

//root노드를 가리키는 포인터
type_ptr_idxnode root = NULL;

int b_plus_tree_insertion(type_rec in_rec, type_ptr_idxnode *root);

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

		b_plus_tree_insertion(one_record, &root);//B_+TREE 삽입

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


int b_plus_tree_insertion(type_rec in_rec, type_ptr_idxnode *root) {

	//**node앞에 idx가 붙어있으면 인덱스노드용 data가 붙어있으면 데이터 노드용이다

	char key[100];
	int i, j, k, m;
	int top = -1;
	int check = 0;
	type_rec* recptr = &in_rec;
	type_ptr_idxnode rnew;	//새 root용 노드
	type_ptr_idxnode stack[50];	//부모 보관용
	type_ptr_idxnode root_idx;	//루트포인터
	type_ptr_idxnode curr_idx;	//현재 인덱스 노드
	type_ptr_idxnode new_idx;
	type_ptr_idxnode P;	//보관용 포인터
	idx_bignode binode;	//index_bignode( 보통 indexnode보다 레코드와 포인터수가 하나씩 더 많은 노드 )

	type_ptr_datanode new_data;	//꽉 찼을 시의 새 노드
	type_ptr_datanode curr_data;

	data_bignode bdnode;//data_bignode( 보통 datanode보다 레코드와 포인터수가 하나씩 더 많은 노드 )

	type_ptr_idxnode n;
	type_ptr_datanode nd;

	if (!*root) {	//ROOT가 NULL인 경우 ( 초기상황)

		n = (type_ptr_idxnode)malloc(sizeof(idxnode));	//인덱스노드를 하나 만든 후
		strcpy(n->key[0], recptr->wstr);
		n->idx_ptr[0] = n->idx_ptr[1] = NULL;
		n->fill_cnt = 1;
		*root = n;	//루트가 가리키게 함

		nd = (type_ptr_datanode)malloc(sizeof(datanode));	//데이터노드를 하나 생성 후
		nd->rec[0] = in_rec;
		nd->fill_cnt = 1;
		root_idx = *root;

		root_idx->data_ptr[0] = nd;	//루트 인덱스노드의 포인터[0]가 가리키게 함
		root_idx->data_ptr[1] = NULL;	//루트 인덱스노드의 포인터[1] = NULL로 초기화

		return 0;
	}

	root_idx = *root;
	curr_idx = root_idx;
	strcpy(key, recptr->wstr);//키 값 복사

	if (root_idx->data_ptr[1] == NULL) {	//Root가 Null이 아닌 경우의 초반부 삽입

		curr_data = root_idx->data_ptr[0];

		if (curr_data->fill_cnt < MAXK) {	//데이터 노드에 빈자리가 있다면
			for (i = 0; i < curr_data->fill_cnt; i++) {
				if (strcmp(key, curr_data->rec[i].wstr) == 0) {
					return -1;
				}
				if (strcmp(key, curr_data->rec[i].wstr) < 0) {//입력데이터가 curr의 데이터들보다 작다면
					for (j = curr_data->fill_cnt - 1; j >= i; j--) {//오른쪽으로 한칸씩 push
						curr_data->rec[j + 1] = curr_data->rec[j];
					}
					//입력데이터 적합한 자리에 넣기
					curr_data->rec[i] = in_rec;
					curr_data->fill_cnt++;
					return 1;
				}

			}
			if (i == curr_data->fill_cnt) {//curr의 데이터들보다 크다면
				curr_data->rec[i] = in_rec;	//마지막 자리에 넣기
				curr_data->fill_cnt++;
				strcpy(root_idx->key[0], in_rec.wstr);
				return 1;
			}
		}
		else {	//빈자리가 없을 경우
			strcpy(key, in_rec.wstr);
			for (k = 0; k < MAXK; k++) {	//key값보다 작은값들 찾기
				if (strcmp(key, curr_data->rec[k].wstr) < 0) //다 찾았으면 break
					break;
			}

			for (m = 0; m < k; m++) {	//key값보다 작은값들 bnode에 먼저 넣기
				bdnode.rec[m] = curr_data->rec[m];
			}

			//그 다음, 입력 데이터 넣기
			bdnode.rec[m] = in_rec;
			m++;

			//나머지 bnode에 넣기
			for (; m < MAXK + 1; m++) {
				bdnode.rec[m] = curr_data->rec[m - 1];
			}

			for (i = 0; i < halfK + 1; i++) {	//왼쪽 반을 curr에 넣어준다(중간레코드 포함)
				curr_data->rec[i] = bdnode.rec[i];
			}
			curr_data->fill_cnt = halfK + 1;

			for (; i < MAXK; i++) {	//curr의 나머지 데이터 삭제
				type_ptr_datanode *buff = &curr_data->rec[i];
				*buff = NULL;
				curr_data->rec[i].numpos = 0;
				buff = &curr_data->rec[i].pos;
				*buff = NULL;
			}

			//new노드 생성 후 오른쪽 반 데이터 넣기
			new_data = (type_ptr_datanode)malloc(sizeof(datanode));

			for (i = 0; i < halfK; i++) {
				new_data->rec[i] = bdnode.rec[i + halfK + 1];
			}
			new_data->fill_cnt = halfK;

			strcpy(root_idx->key[0], bdnode.rec[halfK].wstr);	//중간레코드를 루트 인덱스노드의 KEY값에 넣음
			root_idx->data_ptr[1] = new_data;	//새로 만든 노드를 인덱스 노드의 data_ptr[1]에 넣음
			curr_data->data_ptr = new_data;		//두 데이타 노드끼리 연결
			new_data->data_ptr = NULL;		//새로 만든 노드의 link는 NULL
		}

	}
	else if (root_idx->data_ptr[1] != NULL) {	//정상삽입의 경우(초기 상황이 아닌 경우)

		while (1) {	//데이터가 들어갈 데이타노드를 찾는다

			for (i = 0; i < curr_idx->fill_cnt; i++) {

				if (strcmp(key, curr_idx->key[i]) == 0) {
					return -1;
				}
				if (strcmp(key, curr_idx->key[i]) < 0) {//입력데이터가 curr의 어떤 데이터보다 작다면
					P = curr_idx->idx_ptr[i];	//그 데이터의 왼쪽 자식포인터를 P에 넣음
					break;
				}
			}

			if (i == curr_idx->fill_cnt) {//curr의 제일 큰 데이터보다 크다면
				P = curr_idx->idx_ptr[i];	//그 데이터의 오른쪽 자식 포인터를 P에 넣음
			}

			if (curr_idx->data_ptr[0] != NULL) {	//데이터 노드 바로 위의 인덱스 노드를 찾음
				P = NULL;
			}
			if (P) {	//자식이 존재
				top++;
				stack[top] = curr_idx;
				curr_idx = P;
				continue;
			}
			else //데이타노드의 바로 위 index노드에서 데이타노드를 찾음( i가 데이터노드를 가리키는 인덱스 값을 가지고 있음)
			{
				curr_data = curr_idx->data_ptr[i];	//데이타노드를 가리키는 포인터를 curr_data에 옮겨줌

				break;

			}

		}

		while (1) {	//curr_data는 현재 도달한 데이타 

			if (curr_data->fill_cnt != MAXK) {	//데이터 노드가 다 차지 않았을 경우

				for (i = 0; i < curr_data->fill_cnt; i++) {

					if (strcmp(key, curr_data->rec[i].wstr) == 0) {
						return -1;
					}
					if (strcmp(key, curr_data->rec[i].wstr) < 0) {//입력데이터가 데이터 노드의 데이터들보다 작다면
						for (j = curr_data->fill_cnt - 1; j >= i; j--) {//오른쪽으로 한칸씩 push
							curr_data->rec[j + 1] = curr_data->rec[j];
						}
						//입력데이터 적합한 자리에 넣기
						curr_data->rec[i] = in_rec;
						curr_data->fill_cnt++;
						return 0;
					}
				}
				if (i == curr_data->fill_cnt) {//데이터 노드의 데이터들보다 크다면
					curr_data->rec[i] = in_rec;	//마지막 자리에 넣기
					curr_data->fill_cnt++;
					return 0;
				}
			}
			else {	//데이터노드가 다 찼을 경우

				type_ptr_datanode ptr_new_data;
				char mid_key[100];	//빅노드에서 중간레코드의 key

				for (i = 0; i < curr_data->fill_cnt; i++) {//중복검사
					if (strcmp(key, curr_data->rec[i].wstr) == 0) {
						return -1;
					}
				}

				for (k = 0; k < MAXK; k++) {	//key값보다 작은값들 찾기
					if (strcmp(key, curr_data->rec[k].wstr) < 0) //다 찾았으면 break
						break;
				}

				for (m = 0; m < k; m++) {	//key값보다 작은값들 bnode에 먼저 넣기
					bdnode.rec[m] = curr_data->rec[m];
				}

				//그 다음, 입력 데이터 넣기
				bdnode.rec[m] = in_rec;
				m++;

				//나머지 bnode에 넣기
				for (; m < MAXK + 1; m++) {
					bdnode.rec[m] = curr_data->rec[m - 1];
				}

				for (i = 0; i < halfK + 1; i++) {	//왼쪽 반을 현재 데이터노드에 넣어준다(중간레코드 포함)
					curr_data->rec[i] = bdnode.rec[i];
				}
				curr_data->fill_cnt = halfK + 1;

				for (; i < MAXK; i++) {	//현재 데이터노드의 나머지 데이터 삭제
					type_ptr_datanode *buff = &curr_data->rec[i];
					*buff = NULL;
					curr_data->rec[i].numpos = 0;
					buff = &curr_data->rec[i].pos;
					*buff = NULL;
				}

				//new데이터 노드 생성 후 오른쪽 반 데이터 넣기
				new_data = (type_ptr_datanode)malloc(sizeof(datanode));

				for (i = 0; i < halfK; i++) {
					new_data->rec[i] = bdnode.rec[i + halfK + 1];
				}
				new_data->fill_cnt = halfK;
				new_data->data_ptr = curr_data->data_ptr;
				curr_data->data_ptr = new_data;

				strcpy(mid_key, bdnode.rec[halfK].wstr);
				ptr_new_data = new_data;

				//현재 여기서 curr_idx는 현재 mid_key값과 ptr_new_data를 넣을 인덱스 노드이다.

				if (curr_idx->fill_cnt < MAXK) {//curr_idx 노드에 빈 자리가 있는 경우
					int x;
					for (x = 0; x < curr_idx->fill_cnt; x++) {
						if (strcmp(mid_key, curr_idx->key[x]) < 0) {
							for (j = curr_idx->fill_cnt - 1; j >= x; j--) {//오른쪽으로 한칸씩 push
								strcpy(curr_idx->key[j + 1], curr_idx->key[j]);
								curr_idx->data_ptr[j + 2] = curr_idx->data_ptr[j + 1];
							}
							//입력데이터 적합한 자리에 넣기
							strcpy(curr_idx->key[x], mid_key);
							curr_idx->data_ptr[x + 1] = ptr_new_data;
							curr_idx->fill_cnt++;
							return 1;


						}
					}
					if (x == curr_idx->fill_cnt) {//curr의 데이터들보다 크다면
						strcpy(curr_idx->key[x], mid_key);	//마지막 자리에 넣기
						curr_idx->data_ptr[x + 1] = ptr_new_data;
						curr_idx->fill_cnt++;
						return 1;
					}


				}
				else {//빈 자리가 없는 경우

					for (k = 0; k < MAXK; k++) {	//key값보다 작은값들 찾기
						if (strcmp(mid_key, curr_idx->key[k]) < 0) //다 찾았으면 break
							break;
					}

					binode.data_ptr[0] = curr_idx->data_ptr[0];

					for (m = 0; m < k; m++) {	//key값보다 작은값들 bnode에 먼저 넣기
						binode.data_ptr[m + 1] = curr_idx->data_ptr[m + 1];
						strcpy(binode.key[m], curr_idx->key[m]);
					}

					//그 다음, 입력 데이터 넣기
					binode.data_ptr[m + 1] = ptr_new_data;
					strcpy(binode.key[m], mid_key);
					m++;

					//나머지 bnode에 넣기
					for (; m < MAXK + 1; m++) {
						binode.data_ptr[m + 1] = curr_idx->data_ptr[m];
						strcpy(binode.key[m], curr_idx->key[m - 1]);
					}

					for (i = 0; i < halfK; i++) {	//왼쪽 반을 curr에 넣어준다(  중간key미포함)
						curr_idx->data_ptr[i] = binode.data_ptr[i];
						strcpy(curr_idx->key[i], binode.key[i]);
					}
					curr_idx->fill_cnt = halfK;
					curr_idx->data_ptr[i] = binode.data_ptr[i];

					for (; i < MAXK; i++) {	//curr의 나머지 데이터 삭제
						curr_idx->data_ptr[i + 1] = NULL;
						type_ptr_idxnode *buff = &curr_idx->key[i];
						*buff = NULL;
					}

					//new노드 생성 후 오른쪽 반 데이터 넣기
					new_idx = (type_ptr_idxnode)malloc(sizeof(idxnode));


					for (i = 0; i < halfK; i++) {

						new_idx->data_ptr[i] = binode.data_ptr[i + halfK + 1];
						strcpy(new_idx->key[i], binode.key[i + halfK + 1]);
					}
					new_idx->data_ptr[i] = binode.data_ptr[i + halfK + 1];
					new_idx->fill_cnt = halfK;


					//가운데 데이터
					P = new_idx;
					strcpy(mid_key, binode.key[halfK]);

					if (top >= 0) {//부모 노드가 존재한다면
						int x;
						curr_idx = stack[top];
						top--;
						while (1) {
							if (curr_idx->fill_cnt != MAXK) {	//부모 인덱스 노드가 다 차지 않았을 경우
								for (x = 0; x < curr_idx->fill_cnt; x++) {
									if (strcmp(mid_key, curr_idx->key[x]) < 0) {
										for (j = curr_idx->fill_cnt - 1; j >= x; j--) {//오른쪽으로 한칸씩 push
											strcpy(curr_idx->key[j + 1], curr_idx->key[j]);
											curr_idx->idx_ptr[j + 2] = curr_idx->idx_ptr[j + 1];
										}
										//입력데이터 적합한 자리에 넣기
										strcpy(curr_idx->key[x], mid_key);
										curr_idx->data_ptr[0] = NULL;
										curr_idx->idx_ptr[x + 1] = P;
										curr_idx->fill_cnt++;
										return 1;


									}
								}
								if (x == curr_idx->fill_cnt) {//curr의 데이터들보다 크다면
									strcpy(curr_idx->key[x], mid_key);	//마지막 자리에 넣기
									curr_idx->data_ptr[0] = NULL;
									curr_idx->idx_ptr[x + 1] = P;
									curr_idx->fill_cnt++;
									return 1;
								}

							}

							else {//다 찼을 경우
								for (k = 0; k < MAXK; k++) {	//key값보다 작은값들 찾기
									if (strcmp(mid_key, curr_idx->key[k]) < 0) //다 찾았으면 break
										break;
								}

								strcpy(binode.key[0], curr_idx->idx_ptr[0]);
								binode.idx_ptr[0] = curr_idx->idx_ptr[0];
								for (m = 0; m < k; m++) {	//key값보다 작은값들 bnode에 먼저 넣기
									binode.idx_ptr[m + 1] = curr_idx->idx_ptr[m + 1];
									strcpy(binode.key[m], curr_idx->key[m]);
								}

								//그 다음, 입력 데이터 넣기
								binode.idx_ptr[m + 1] = P;
								strcpy(binode.key[m], mid_key);
								m++;

								//나머지 bnode에 넣기
								for (; m < MAXK + 1; m++) {
									binode.idx_ptr[m + 1] = curr_idx->idx_ptr[m];
									strcpy(binode.key[m], curr_idx->key[m - 1]);
								}

								for (i = 0; i < halfK; i++) {	//왼쪽 반을 curr에 넣어준다
									curr_idx->idx_ptr[i] = binode.idx_ptr[i];
									strcpy(curr_idx->key[i], binode.key[i]);
								}
								curr_idx->fill_cnt = halfK;
								curr_idx->idx_ptr[i] = binode.idx_ptr[i];

								for (; i < MAXK; i++) {	//curr의 나머지 데이터 삭제
									curr_idx->idx_ptr[i + 1] = NULL;
									type_ptr_idxnode *buff = &curr_idx->key[i];
									*buff = NULL;
								}

								//new노드 생성 후 오른쪽 반 데이터 넣기
								new_idx = (type_ptr_idxnode)malloc(sizeof(idxnode));


								for (i = 0; i < halfK; i++) {

									new_idx->idx_ptr[i] = binode.idx_ptr[i + halfK + 1];
									strcpy(new_idx->key[i], binode.key[i + halfK + 1]);
								}
								new_idx->data_ptr[0] = NULL;
								new_idx->idx_ptr[i] = binode.idx_ptr[i + halfK + 1];
								new_idx->fill_cnt = halfK;

								//가운데 데이터
								P = new_idx;
								strcpy(mid_key, binode.key[halfK]);

								if (top >= 0) {//부모 노드가 존재한다면
									curr_idx = stack[top];
									top--;
									continue;
								}
								else {//부모 노드가 존재하지 않는다면
									rnew = (type_ptr_idxnode)malloc(sizeof(idxnode));
									rnew->idx_ptr[0] = curr_idx;
									strcpy(rnew->key[0], mid_key);
									rnew->idx_ptr[1] = P;
									rnew->fill_cnt = 1;
									rnew->data_ptr[0] = NULL;
									*root = rnew;	//부모 노드가 존재하지 않는다면 이 새 노드가 루트가 됨
									return 1;
								}
							}
						}
					}
					else {//부모 노드가 존재하지 않는다면
						rnew = (type_ptr_idxnode)malloc(sizeof(idxnode));
						rnew->idx_ptr[0] = curr_idx;
						strcpy(rnew->key[0], mid_key);
						rnew->idx_ptr[1] = P;
						rnew->fill_cnt = 1;
						rnew->data_ptr[0] = NULL;
						*root = rnew;	//부모 노드가 존재하지 않는다면 이 새 노드가 루트가 됨
						return 0;
					}

				}

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

int b_plus_tree_insertion_test(type_rec in_rec, type_ptr_idxnode *root) {


	//**node앞에 idx가 붙어있으면 인덱스노드용 data가 붙어있으면 데이터 노드용이다

	char key[100];
	int i, j, k, m;
	int top = -1;
	int split = 0;//split한 횟수
	int check = 0;
	type_rec* recptr = &in_rec;
	type_ptr_idxnode rnew;	//새 root용 노드
	type_ptr_idxnode stack[50];	//부모 보관용
	type_ptr_idxnode root_idx;	//루트포인터
	type_ptr_idxnode curr_idx;	//현재 인덱스 노드
	type_ptr_idxnode new_idx;
	type_ptr_idxnode P;	//보관용 포인터
	idx_bignode binode;	//index_bignode( 보통 indexnode보다 레코드와 포인터수가 하나씩 더 많은 노드 )

	type_ptr_datanode new_data;	//꽉 찼을 시의 새 노드
	type_ptr_datanode curr_data;

	data_bignode bdnode;//data_bignode( 보통 datanode보다 레코드와 포인터수가 하나씩 더 많은 노드 )

	type_ptr_idxnode n;
	type_ptr_datanode nd;

	if (!*root) {	//ROOT가 NULL인 경우 ( 초기상황)

		n = (type_ptr_idxnode)malloc(sizeof(idxnode));	//인덱스노드를 하나 만든 후
		strcpy(n->key[0], recptr->wstr);
		n->idx_ptr[0] = n->idx_ptr[1] = NULL;
		n->fill_cnt = 1;
		*root = n;	//루트가 가리키게 함

		nd = (type_ptr_datanode)malloc(sizeof(datanode));	//데이터노드를 하나 생성 후
		nd->rec[0] = in_rec;
		nd->fill_cnt = 1;
		root_idx = *root;

		root_idx->data_ptr[0] = nd;	//루트 인덱스노드의 포인터[0]가 가리키게 함
		root_idx->data_ptr[1] = NULL;	//루트 인덱스노드의 포인터[1] = NULL로 초기화

		return split;
	}

	root_idx = *root;
	curr_idx = root_idx;
	strcpy(key, recptr->wstr);//키 값 복사

	if (root_idx->data_ptr[1] == NULL) {	//Root가 Null이 아닌 경우의 초반부 삽입

		curr_data = root_idx->data_ptr[0];

		if (curr_data->fill_cnt < MAXK) {	//데이터 노드에 빈자리가 있다면
			for (i = 0; i < curr_data->fill_cnt; i++) {
				if (strcmp(key, curr_data->rec[i].wstr) == 0) {
					return -1;
				}
				if (strcmp(key, curr_data->rec[i].wstr) < 0) {//입력데이터가 curr의 데이터들보다 작다면
					for (j = curr_data->fill_cnt - 1; j >= i; j--) {//오른쪽으로 한칸씩 push
						curr_data->rec[j + 1] = curr_data->rec[j];
					}
					//입력데이터 적합한 자리에 넣기
					curr_data->rec[i] = in_rec;
					curr_data->fill_cnt++;
					return split;
				}

			}
			if (i == curr_data->fill_cnt) {//curr의 데이터들보다 크다면
				curr_data->rec[i] = in_rec;	//마지막 자리에 넣기
				curr_data->fill_cnt++;
				strcpy(root_idx->key[0], in_rec.wstr);
				return split;
			}
		}
		else {	//빈자리가 없을 경우
			split++;
			strcpy(key, in_rec.wstr);
			for (k = 0; k < MAXK; k++) {	//key값보다 작은값들 찾기
				if (strcmp(key, curr_data->rec[k].wstr) < 0) //다 찾았으면 break
					break;
			}

			for (m = 0; m < k; m++) {	//key값보다 작은값들 bnode에 먼저 넣기
				bdnode.rec[m] = curr_data->rec[m];
			}

			//그 다음, 입력 데이터 넣기
			bdnode.rec[m] = in_rec;
			m++;

			//나머지 bnode에 넣기
			for (; m < MAXK + 1; m++) {
				bdnode.rec[m] = curr_data->rec[m - 1];
			}

			for (i = 0; i < halfK + 1; i++) {	//왼쪽 반을 curr에 넣어준다(중간레코드 포함)
				curr_data->rec[i] = bdnode.rec[i];
			}
			curr_data->fill_cnt = halfK + 1;

			for (; i < MAXK; i++) {	//curr의 나머지 데이터 삭제
				type_ptr_datanode *buff = &curr_data->rec[i];
				*buff = NULL;
				curr_data->rec[i].numpos = 0;
				buff = &curr_data->rec[i].pos;
				*buff = NULL;
			}

			//new노드 생성 후 오른쪽 반 데이터 넣기
			new_data = (type_ptr_datanode)malloc(sizeof(datanode));

			for (i = 0; i < halfK; i++) {
				new_data->rec[i] = bdnode.rec[i + halfK + 1];
			}
			new_data->fill_cnt = halfK;

			strcpy(root_idx->key[0], bdnode.rec[halfK].wstr);	//중간레코드를 루트 인덱스노드의 KEY값에 넣음
			root_idx->data_ptr[1] = new_data;	//새로 만든 노드를 인덱스 노드의 data_ptr[1]에 넣음
			curr_data->data_ptr = new_data;		//두 데이타 노드끼리 연결
			new_data->data_ptr = NULL;		//새로 만든 노드의 link는 NULL
		}

	}
	else if (root_idx->data_ptr[1] != NULL) {	//정상삽입의 경우(초기 상황이 아닌 경우)

		while (1) {	//데이터가 들어갈 데이타노드를 찾는다

			for (i = 0; i < curr_idx->fill_cnt; i++) {

				if (strcmp(key, curr_idx->key[i]) == 0) {
					return -1;
				}
				if (strcmp(key, curr_idx->key[i]) < 0) {//입력데이터가 curr의 어떤 데이터보다 작다면
					P = curr_idx->idx_ptr[i];	//그 데이터의 왼쪽 자식포인터를 P에 넣음
					break;
				}
			}

			if (i == curr_idx->fill_cnt) {//curr의 제일 큰 데이터보다 크다면
				P = curr_idx->idx_ptr[i];	//그 데이터의 오른쪽 자식 포인터를 P에 넣음
			}

			if (curr_idx->data_ptr[0] != NULL) {	//데이터 노드 바로 위의 인덱스 노드를 찾음
				P = NULL;
			}
			if (P) {	//자식이 존재
				top++;
				stack[top] = curr_idx;
				curr_idx = P;
				continue;
			}
			else //데이타노드의 바로 위 index노드에서 데이타노드를 찾음( i가 데이터노드를 가리키는 인덱스 값을 가지고 있음)
			{
				curr_data = curr_idx->data_ptr[i];	//데이타노드를 가리키는 포인터를 curr_data에 옮겨줌

				break;

			}

		}

		while (1) {	//curr_data는 현재 도달한 데이타 

			if (curr_data->fill_cnt != MAXK) {	//데이터 노드가 다 차지 않았을 경우

				for (i = 0; i < curr_data->fill_cnt; i++) {

					if (strcmp(key, curr_data->rec[i].wstr) == 0) {
						return -1;
					}
					if (strcmp(key, curr_data->rec[i].wstr) < 0) {//입력데이터가 데이터 노드의 데이터들보다 작다면
						for (j = curr_data->fill_cnt - 1; j >= i; j--) {//오른쪽으로 한칸씩 push
							curr_data->rec[j + 1] = curr_data->rec[j];
						}
						//입력데이터 적합한 자리에 넣기
						curr_data->rec[i] = in_rec;
						curr_data->fill_cnt++;
						return split;
					}
				}
				if (i == curr_data->fill_cnt) {//데이터 노드의 데이터들보다 크다면
					curr_data->rec[i] = in_rec;	//마지막 자리에 넣기
					curr_data->fill_cnt++;
					return split;
				}
			}
			else {	//데이터노드가 다 찼을 경우
				split++;
				type_ptr_datanode ptr_new_data;
				char mid_key[100];	//빅노드에서 중간레코드의 key

				for (i = 0; i < curr_data->fill_cnt; i++) {//중복검사
					if (strcmp(key, curr_data->rec[i].wstr) == 0) {
						return -1;
					}
				}

				for (k = 0; k < MAXK; k++) {	//key값보다 작은값들 찾기
					if (strcmp(key, curr_data->rec[k].wstr) < 0) //다 찾았으면 break
						break;
				}

				for (m = 0; m < k; m++) {	//key값보다 작은값들 bnode에 먼저 넣기
					bdnode.rec[m] = curr_data->rec[m];
				}

				//그 다음, 입력 데이터 넣기
				bdnode.rec[m] = in_rec;
				m++;

				//나머지 bnode에 넣기
				for (; m < MAXK + 1; m++) {
					bdnode.rec[m] = curr_data->rec[m - 1];
				}

				for (i = 0; i < halfK + 1; i++) {	//왼쪽 반을 현재 데이터노드에 넣어준다(중간레코드 포함)
					curr_data->rec[i] = bdnode.rec[i];
				}
				curr_data->fill_cnt = halfK + 1;

				for (; i < MAXK; i++) {	//현재 데이터노드의 나머지 데이터 삭제
					type_ptr_datanode *buff = &curr_data->rec[i];
					*buff = NULL;
					curr_data->rec[i].numpos = 0;
					buff = &curr_data->rec[i].pos;
					*buff = NULL;
				}

				//new데이터 노드 생성 후 오른쪽 반 데이터 넣기
				new_data = (type_ptr_datanode)malloc(sizeof(datanode));

				for (i = 0; i < halfK; i++) {
					new_data->rec[i] = bdnode.rec[i + halfK + 1];
				}
				new_data->fill_cnt = halfK;
				curr_data->data_ptr = new_data;

				strcpy(mid_key, bdnode.rec[halfK].wstr);
				ptr_new_data = new_data;

				//현재 여기서 curr_idx는 현재 mid_key값과 ptr_new_data를 넣을 인덱스 노드이다.

				if (curr_idx->fill_cnt < MAXK) {//curr_idx 노드에 빈 자리가 있는 경우
					int x;
					for (x = 0; x < curr_idx->fill_cnt; x++) {
						if (strcmp(mid_key, curr_idx->key[x]) < 0) {
							for (j = curr_idx->fill_cnt - 1; j >= x; j--) {//오른쪽으로 한칸씩 push
								strcpy(curr_idx->key[j + 1], curr_idx->key[j]);
								curr_idx->data_ptr[j + 2] = curr_idx->data_ptr[j + 1];
							}
							//입력데이터 적합한 자리에 넣기
							strcpy(curr_idx->key[x], mid_key);
							curr_idx->data_ptr[x + 1] = ptr_new_data;
							curr_idx->fill_cnt++;
							return split;


						}
					}
					if (x == curr_idx->fill_cnt) {//curr의 데이터들보다 크다면
						strcpy(curr_idx->key[x], mid_key);	//마지막 자리에 넣기
						curr_idx->data_ptr[x + 1] = ptr_new_data;
						curr_idx->fill_cnt++;
						return split;
					}


				}
				else {//빈 자리가 없는 경우
					split++;
					for (k = 0; k < MAXK; k++) {	//key값보다 작은값들 찾기
						if (strcmp(mid_key, curr_idx->key[k]) < 0) //다 찾았으면 break
							break;
					}

					binode.data_ptr[0] = curr_idx->data_ptr[0];

					for (m = 0; m < k; m++) {	//key값보다 작은값들 bnode에 먼저 넣기
						binode.data_ptr[m + 1] = curr_idx->data_ptr[m + 1];
						strcpy(binode.key[m], curr_idx->key[m]);
					}

					//그 다음, 입력 데이터 넣기
					binode.data_ptr[m + 1] = ptr_new_data;
					strcpy(binode.key[m], mid_key);
					m++;

					//나머지 bnode에 넣기
					for (; m < MAXK + 1; m++) {
						binode.data_ptr[m + 1] = curr_idx->data_ptr[m];
						strcpy(binode.key[m], curr_idx->key[m - 1]);
					}

					for (i = 0; i < halfK; i++) {	//왼쪽 반을 curr에 넣어준다(  중간key미포함)
						curr_idx->data_ptr[i] = binode.data_ptr[i];
						strcpy(curr_idx->key[i], binode.key[i]);
					}
					curr_idx->fill_cnt = halfK;
					curr_idx->data_ptr[i] = binode.data_ptr[i];

					for (; i < MAXK; i++) {	//curr의 나머지 데이터 삭제
						curr_idx->data_ptr[i + 1] = NULL;
						type_ptr_idxnode *buff = &curr_idx->key[i];
						*buff = NULL;
					}

					//new노드 생성 후 오른쪽 반 데이터 넣기
					new_idx = (type_ptr_idxnode)malloc(sizeof(idxnode));


					for (i = 0; i < halfK; i++) {

						new_idx->data_ptr[i] = binode.data_ptr[i + halfK + 1];
						strcpy(new_idx->key[i], binode.key[i + halfK + 1]);
					}
					new_idx->data_ptr[i] = binode.data_ptr[i + halfK + 1];
					new_idx->fill_cnt = halfK;


					//가운데 데이터
					P = new_idx;
					strcpy(mid_key, binode.key[halfK]);

					if (top >= 0) {//부모 노드가 존재한다면
						int x;
						curr_idx = stack[top];
						top--;
						while (1) {
							if (curr_idx->fill_cnt != MAXK) {	//부모 인덱스 노드가 다 차지 않았을 경우
								for (x = 0; x < curr_idx->fill_cnt; x++) {
									if (strcmp(mid_key, curr_idx->key[x]) < 0) {
										for (j = curr_idx->fill_cnt - 1; j >= x; j--) {//오른쪽으로 한칸씩 push
											strcpy(curr_idx->key[j + 1], curr_idx->key[j]);
											curr_idx->idx_ptr[j + 2] = curr_idx->idx_ptr[j + 1];
										}
										//입력데이터 적합한 자리에 넣기
										strcpy(curr_idx->key[x], mid_key);
										curr_idx->data_ptr[0] = NULL;
										curr_idx->idx_ptr[x + 1] = P;
										curr_idx->fill_cnt++;
										return split;


									}
								}
								if (x == curr_idx->fill_cnt) {//curr의 데이터들보다 크다면
									strcpy(curr_idx->key[x], mid_key);	//마지막 자리에 넣기
									curr_idx->data_ptr[0] = NULL;
									curr_idx->idx_ptr[x + 1] = P;
									curr_idx->fill_cnt++;
									return split;
								}

							}

							else {//다 찼을 경우
								split++;
								for (k = 0; k < MAXK; k++) {	//key값보다 작은값들 찾기
									if (strcmp(mid_key, curr_idx->key[k]) < 0) //다 찾았으면 break
										break;
								}

								strcpy(binode.key[0], curr_idx->idx_ptr[0]);
								binode.idx_ptr[0] = curr_idx->idx_ptr[0];
								for (m = 0; m < k; m++) {	//key값보다 작은값들 bnode에 먼저 넣기
									binode.idx_ptr[m + 1] = curr_idx->idx_ptr[m + 1];
									strcpy(binode.key[m], curr_idx->key[m]);
								}

								//그 다음, 입력 데이터 넣기
								binode.idx_ptr[m + 1] = P;
								strcpy(binode.key[m], mid_key);
								m++;

								//나머지 bnode에 넣기
								for (; m < MAXK + 1; m++) {
									binode.idx_ptr[m + 1] = curr_idx->idx_ptr[m];
									strcpy(binode.key[m], curr_idx->key[m - 1]);
								}

								for (i = 0; i < halfK; i++) {	//왼쪽 반을 curr에 넣어준다
									curr_idx->idx_ptr[i] = binode.idx_ptr[i];
									strcpy(curr_idx->key[i], binode.key[i]);
								}
								curr_idx->fill_cnt = halfK;
								curr_idx->idx_ptr[i] = binode.idx_ptr[i];

								for (; i < MAXK; i++) {	//curr의 나머지 데이터 삭제
									curr_idx->idx_ptr[i + 1] = NULL;
									type_ptr_idxnode *buff = &curr_idx->key[i];
									*buff = NULL;
								}

								//new노드 생성 후 오른쪽 반 데이터 넣기
								new_idx = (type_ptr_idxnode)malloc(sizeof(idxnode));


								for (i = 0; i < halfK; i++) {

									new_idx->idx_ptr[i] = binode.idx_ptr[i + halfK + 1];
									strcpy(new_idx->key[i], binode.key[i + halfK + 1]);
								}
								new_idx->data_ptr[0] = NULL;
								new_idx->idx_ptr[i] = binode.idx_ptr[i + halfK + 1];
								new_idx->fill_cnt = halfK;

								//가운데 데이터
								P = new_idx;
								strcpy(mid_key, binode.key[halfK]);

								if (top >= 0) {//부모 노드가 존재한다면
									curr_idx = stack[top];
									top--;
									continue;
								}
								else {//부모 노드가 존재하지 않는다면
									rnew = (type_ptr_idxnode)malloc(sizeof(idxnode));
									rnew->idx_ptr[0] = curr_idx;
									strcpy(rnew->key[0], mid_key);
									rnew->idx_ptr[1] = P;
									rnew->fill_cnt = 1;
									rnew->data_ptr[0] = NULL;
									*root = rnew;	//부모 노드가 존재하지 않는다면 이 새 노드가 루트가 됨
									return split;
								}
							}
						}
					}
					else {//부모 노드가 존재하지 않는다면
						rnew = (type_ptr_idxnode)malloc(sizeof(idxnode));
						rnew->idx_ptr[0] = curr_idx;
						strcpy(rnew->key[0], mid_key);
						rnew->idx_ptr[1] = P;
						rnew->fill_cnt = 1;
						rnew->data_ptr[0] = NULL;
						*root = rnew;	//부모 노드가 존재하지 않는다면 이 새 노드가 루트가 됨
						return split;
					}

				}

			}
		}
	}
}

int B_plus_tree_Search(char word[100], type_ptr_idxnode root) {	//root노드의 level을 0이라하고 그 아래부터 1씩 증가

	char key[100];
	int i;
	int top = -1;
	int level = 0;
	int check_have_data = 0;	//찾는 데이터가 있는지 확인하는 변수 ( 1이면 있고 0이면 없음 )
	type_ptr_idxnode stack[50];	//부모 보관용
	type_ptr_idxnode curr_idx;	//현재 노드
	type_ptr_datanode curr_data;
	type_ptr_idxnode P;	//보관용 포인터
	strcpy(key, word);//키 값 복사
	curr_idx = root;


	while (1) {	//데이터가 들어갈 데이타노드를 찾는다

		for (i = 0; i < curr_idx->fill_cnt; i++) {

			if (strcmp(key, curr_idx->key[i]) <= 0) {//입력데이터가 curr의 어떤 데이터보다 작다면
				P = curr_idx->idx_ptr[i];	//그 데이터의 왼쪽 자식포인터를 P에 넣음
				break;
			}
		}

		if (i == curr_idx->fill_cnt) {//curr의 제일 큰 데이터보다 크다면
			P = curr_idx->idx_ptr[i];	//그 데이터의 오른쪽 자식 포인터를 P에 넣음
		}

		if (curr_idx->data_ptr[0] != NULL) {	//데이터 노드 바로 위의 인덱스 노드를 찾음
			P = NULL;
		}
		if (P) {	//자식이 존재
			top++;
			level = top + 1;
			stack[top] = curr_idx;
			curr_idx = P;
			continue;
		}
		else //데이타노드의 바로 위 index노드에서 데이타노드를 찾음( i가 데이터노드를 가리키는 인덱스 값을 가지고 있음)
		{
			curr_data = curr_idx->data_ptr[i];	//데이타노드를 가리키는 포인터를 curr_data에 옮겨줌

			break;

		}

	}

	for (int j = 0; j < curr_data->fill_cnt; j++) {
		if (strcmp(key, curr_data->rec[j].wstr) == 0) {
			printf("해당 이름은 LEVEL %d에 있는 레코드 내 %d번째에 있습니다.\n", level, j + 1);
			return 0;
		}
	}
	printf("찾는 변수가 존재하지않습니다...\n");
	return -1;


}

int B_plus_tree_Deletion(char word[100], type_ptr_idxnode *root) {

	char key[100];

	int i, j, k, m;
	int top = -1;
	int retri = 0;	//재분배 횟수
	int merge = 0;	//합병 횟수
	int middle = 0; //bignode의 총 레코드 수의 반
	int parent_index;
	int exist_data = 0;	//1이면 존재 0이면 존재하지 않음

	type_ptr_idxnode stack[50];	//부모 보관용

	type_ptr_idxnode curr_idx;	//현재 노드
	type_ptr_datanode curr_data;

	type_ptr_idxnode parent_idx;	//balancing에서 sibling 여부를 알기위한 부모노드
	type_ptr_datanode parent_data;

	type_ptr_idxnode left_sibling_idx;	//왼쪽 형제
	type_ptr_datanode left_sibling_data;

	type_ptr_idxnode right_sibling_idx;	//오른쪽 형제
	type_ptr_datanode right_sibling_data;

	type_ptr_idxnode P;	//보관용 포인터
	type_ptr_idxnode * ptr;	//노드 이중 포인터

	idx_two_bignode tibnode;
	data_two_bignode tdbnode;

	if (!*root) {
		printf("데이터가 하나도 존재하지 않습니다....\n");
		return 1;
	}

	curr_idx = *root;

	strcpy(key, word);

	while (1) {	//삭제할 데이터가 있는 데이타노드를 찾는다

		for (i = 0; i < curr_idx->fill_cnt; i++) {
			if (strcmp(key, curr_idx->key[i]) <= 0) {//입력데이터가 curr의 어떤 데이터보다 작다면
				P = curr_idx->idx_ptr[i];	//그 데이터의 왼쪽 자식포인터를 P에 넣음
				break;
			}
		}

		if (i == curr_idx->fill_cnt) {//curr의 제일 큰 데이터보다 크다면
			P = curr_idx->idx_ptr[i];	//그 데이터의 오른쪽 자식 포인터를 P에 넣음
		}

		if (P) {	//자식이 존재
			top++;
			stack[top] = curr_idx;
			curr_idx = P;
			continue;
		}
		else //데이타노드의 바로 위 index노드에서 데이타노드를 찾음( i가 데이터노드를 가리키는 인덱스 값을 가지고 있음)
		{
			curr_data = curr_idx->data_ptr[i];	//데이타노드를 가리키는 포인터를 curr_data에 옮겨줌
			parent_index = i;
			break;

		}
	}

	for (int j = 0; j < curr_data->fill_cnt; j++) {
		if (strcmp(key, curr_data->rec[j].wstr) == 0) {
			//레코드 삭제
			ptr = &curr_data->rec[j].wstr;
			*ptr = NULL;
			curr_data->rec[j].numpos = 0;
			ptr = &curr_data->rec[j].pos;
			*ptr = NULL;
			curr_data->fill_cnt--;
			exist_data = 1;
			break;
		}
	}

	if (exist_data == 0) {

		printf("삭제하려는 값이 존재하지않습니다...\n");
		return;
	}
	for (j = 0; j < curr_data->fill_cnt; j++) {
		curr_data->rec[j] = curr_data->rec[j + 1];
	}

	if (top == -1) {//현재 노드가 root노드라면
		ptr = &curr_data->rec[0];
		if (!*ptr) {//루트노드의 레코드가 존재하지않는다면
			free(curr_data);
			free(curr_idx);
		}
		else {//루트노드의 레코드가 존재							
			printf("삭제에 성공하였습니다!! 재분배는 %d번, 합병은 %d번하였습니다\n", retri, merge);
			return 0;
		}
	}

	while (1) {
		if (curr_data->fill_cnt < halfK) {	//노드가 balancing에 어긋남

											//부모로 올라가 오른쪽 형제나 왼쪽 형제가 있는지 확인 (오른쪽 형제를 선호)

			parent_idx = curr_idx;//parent_idx가 현재 부모 노드( 즉 바로 위 인덱스 노드) 임


								  //parentindex가 parent(curr_idx)에서의 curr_data노드를 가르키는 포인터 인덱스 
			if (parent_index != 0) {
				left_sibling_data = parent_idx->data_ptr[parent_index - 1];
			}
			if (parent_index != MAXK) {
				right_sibling_data = parent_idx->data_ptr[parent_index + 1];
			}

			if (right_sibling_data&&right_sibling_data->fill_cnt > halfK) {	//오른쪽 형제에게 빌려옴 ( 재분배가 가능 )

				for (k = 0; k < curr_data->fill_cnt; k++) {
					tdbnode.rec[k] = curr_data->rec[k];
				}

				for (m = 0; m < right_sibling_data->fill_cnt; k++, m++) {
					tdbnode.rec[k] = right_sibling_data->rec[m];
				}

				//k에 two_bignode 총 레코드 수가 들어있음

				middle = k / 2;
				//two_bignode에서 middle번째 레코드를 기준으로 왼쪽을 curr에 넣는다.
				for (i = 0; i <= middle; i++) {
					curr_data->rec[i] = tdbnode.rec[i];
				}
				curr_data->fill_cnt = middle + 1;

				//parent에다가 가운데 값인 halfK번째 레코드 값을 넣는다.
				strcpy(parent_idx->key[parent_index], tdbnode.rec[halfK].wstr);

				//오른쪽 자식에 나머지 two_bignode값들을 넣는다.
				for (m = 0; i < k; m++, i++) {

					right_sibling_data->rec[m] = tdbnode.rec[i];
				}
				right_sibling_idx->fill_cnt = k - (middle + 1);	//two_bignode의 총 레코드 수에서 curr에 넣은 반과 parent에 넣은 값을 제외한 나머지 수

				retri++;

				printf("삭제에 성공하였습니다!! 재분배는 %d번, 합병은 %d번하였습니다\n", retri, merge);
				return 0;
			}

			else if (left_sibling_data&&left_sibling_data->fill_cnt > halfK) {	//왼쪽 형제에게 빌려옴 ( 재분배가 가능 )


																				//tbnode에 먼저 왼쪽 자식노드의 값을 넣는다
				for (k = 0; k < left_sibling_data->fill_cnt; k++) {
					tdbnode.rec[k] = left_sibling_data->rec[k];
				}

				//그 다음, curr의 값들을 two_bignode에 넣는다
				for (m = 0; m < curr_data->fill_cnt; k++, m++) {
					tdbnode.rec[k] = curr_data->rec[m];
				}

				//k에 two_bignode 총 레코드 수가 들어있음
				middle = k / 2;

				//two_bignode에서 middle번째 레코드를 기준으로 왼쪽을 curr에 넣는다. 		
				for (i = 0; i <= middle; i++) {
					left_sibling_data->rec[i] = tdbnode.rec[i];
				}
				left_sibling_data->fill_cnt = middle + 1;

				//parent에다가 가운데 값인 middle번째 레코드 값을 넣는다.
				strcpy(parent_idx->key[parent_index], tdbnode.rec[middle].wstr);

				//curr에 나머지 two_bignode값들을 넣는다.
				for (m = 0; i < k; m++, i++) {
					curr_data->rec[m] = tdbnode.rec[i];
				}
				curr_data->fill_cnt = k - (middle + 1);	//two_bignode의 총 레코드 수에서 왼쪽 형제에 넣은 반과 parent에 넣은 값을 제외한 나머지 수

				retri++;

				printf("삭제에 성공하였습니다!! 재분배는 %d번, 합병은 %d번하였습니다\n", retri, merge);

				return 0;
			}

			else {	//합병을 해야한다. ( 재분배가 불가능 )

				int next_data = curr_data->fill_cnt;	//curr의 들어가있는 레코드 다음에 넣을 인덱스

				if (right_sibling_data) {	//오른쪽 형제가 있다면

											//오른쪽 형제의 값들을 curr에 나머지 부분에 넣는다.
					for (i = 0; i < right_sibling_data->fill_cnt; next_data++, i++) {
						curr_data->rec[next_data] = right_sibling_data->rec[i];
					}

					//오른쪽 형제 노드 해제
					free(right_sibling_data);

					//parent에서 curr와 오른쪽 형제 사이에 있던 레코드를 기준으로 왼쪽으로 한칸씩 shift
					for (; j + 1 < parent_idx->fill_cnt; j++) {
						parent_idx->data_ptr[j + 1] = parent_idx->data_ptr[j + 2];
						strcpy(parent_idx->key[j], parent_idx->key[j + 1]);
					}

					curr_data->data_ptr = parent_idx->data_ptr[parent_index + 1];

					//한칸 씩 옮겼다면 마지막으로 옮긴 레코드의 원래 위치 레코드와 포인터 초기화
					ptr = &parent_idx->key[j];
					*ptr = NULL;

					parent_idx->data_ptr[j + 1] = NULL;

					parent_idx->fill_cnt--;

					curr_idx = parent_idx;	//curr에 부모 포인터를 넣고 다시 반복

					merge++;

					//이번에는 인덱스 노드가 밸런싱이 맞는지를 봐야함
					while (1) {
						if (curr_idx->fill_cnt < halfK) {	//노드가 balancing에 어긋남

															//부모로 올라가 오른쪽 형제나 왼쪽 형제가 있는지 확인 (오른쪽 형제를 선호)
							parent_idx = stack[top];
							top--;

							for (j = 0; j < parent_idx->fill_cnt; j++) {
								if (parent_idx->idx_ptr[j] == curr_idx) {
									break;
								}
							}

							//j가 parent에서의 curr노드 포인터

							if (j != 0) {
								left_sibling_idx = parent_idx->idx_ptr[j - 1];
							}
							if (j != MAXK) {
								right_sibling_idx = parent_idx->idx_ptr[j + 1];
							}

							if (right_sibling_idx&&right_sibling_idx->fill_cnt > halfK) {	//오른쪽 형제에게 빌려옴 ( 재분배가 가능 )

																							//tbnode에 먼저 curr값을 넣는다
								tibnode.idx_ptr[0] = curr_idx->idx_ptr[0];
								for (k = 0; k < curr_idx->fill_cnt; k++) {
									tibnode.idx_ptr[k + 1] = curr_idx->idx_ptr[k + 1];
									strcpy(tibnode.key[k], curr_idx->key[k]);
								}

								//그 다음, curr와 오른쪽 형제 사이의 부모의 레코드 값을 넣는다.
								strcpy(tibnode.key[k], parent_idx->key[j]);
								k++;

								tibnode.idx_ptr[k] = right_sibling_idx->idx_ptr[0];
								for (m = 0; m < right_sibling_idx->fill_cnt; k++, m++) {
									tibnode.idx_ptr[k + 1] = right_sibling_idx->idx_ptr[m + 1];
									strcpy(tibnode.key[k], right_sibling_idx->key[m]);
								}

								//k에 two_bignode 총 레코드 수가 들어있음

								middle = k / 2;
								//two_bignode에서 middle번째 레코드를 기준으로 왼쪽을 curr에 넣는다.
								for (i = 0; i < middle; i++) {
									curr_idx->idx_ptr[i] = tibnode.idx_ptr[i];
									strcpy(curr_idx->key[i], tibnode.key[i]);
								}
								curr_idx->idx_ptr[i] = tibnode.idx_ptr[i];
								curr_idx->fill_cnt = middle;

								//parent에다가 가운데 값인 halfK번째 레코드 값을 넣는다.
								strcpy(parent_idx->key[j], tibnode.key[halfK]);
								i++;

								//오른쪽 자식에 나머지 two_bignode값들을 넣는다.
								for (m = 0; i < k; m++, i++) {
									right_sibling_idx->idx_ptr[m] = tibnode.idx_ptr[i];
									strcpy(right_sibling_idx->key[m], tibnode.key[i]);
								}
								right_sibling_idx->idx_ptr[m] = tibnode.idx_ptr[i];
								right_sibling_idx->fill_cnt = k - (middle + 1);	//two_bignode의 총 레코드 수에서 curr에 넣은 반과 parent에 넣은 값을 제외한 나머지 수

								retri++;

								printf("삭제에 성공하였습니다!! 재분배는 %d번, 합병은 %d번하였습니다\n", retri, merge);
								return 0;
							}
							else if (left_sibling_idx&&left_sibling_idx->fill_cnt > halfK) {	//왼쪽 형제에게 빌려옴 ( 재분배가 가능 )


																								//tbnode에 먼저 왼쪽 자식노드의 값을 넣는다
								tibnode.idx_ptr[0] = left_sibling_idx->idx_ptr[0];
								for (k = 0; k < left_sibling_idx->fill_cnt; k++) {
									tibnode.idx_ptr[k + 1] = left_sibling_idx->idx_ptr[k + 1];
									strcpy(tibnode.key[k], left_sibling_idx->key[k]);
								}

								strcpy(tibnode.key[k], parent_idx->key[j - 1]);	//그 다음, curr와 왼쪽 형제 사이의 부모의 레코드 값을 넣는다.
								k++;

								//그 다음, curr의 값들을 two_bignode에 넣는다
								tibnode.idx_ptr[k] = curr_idx->idx_ptr[0];
								for (m = 0; m < curr_idx->fill_cnt; k++, m++) {
									tibnode.idx_ptr[k + 1] = curr_idx->idx_ptr[m + 1];
									strcpy(tibnode.key[k], curr_idx->key[m]);
								}

								//k에 two_bignode 총 레코드 수가 들어있음
								middle = k / 2;

								//two_bignode에서 middle번째 레코드를 기준으로 왼쪽을 curr에 넣는다. 		
								for (i = 0; i < middle; i++) {
									left_sibling_idx->idx_ptr[i] = tibnode.idx_ptr[i];
									strcpy(left_sibling_idx->key[i], tibnode.key[i]);
								}
								left_sibling_idx->idx_ptr[i] = tibnode.idx_ptr[i];
								left_sibling_idx->fill_cnt = middle;

								//parent에다가 가운데 값인 middle번째 레코드 값을 넣는다.
								strcpy(parent_idx->key[j], tibnode.key[middle]);

								i++;

								//curr에 나머지 two_bignode값들을 넣는다.
								for (m = 0; i < k; m++, i++) {
									curr_idx->idx_ptr[m] = tibnode.idx_ptr[i];
									strcpy(curr_idx->key[m], tibnode.key[i]);
								}
								curr_idx->idx_ptr[m] = tibnode.idx_ptr[i];
								curr_idx->fill_cnt = k - (middle + 1);	//two_bignode의 총 레코드 수에서 왼쪽 형제에 넣은 반과 parent에 넣은 값을 제외한 나머지 수

								retri++;

								printf("삭제에 성공하였습니다!! 재분배는 %d번, 합병은 %d번하였습니다\n", retri, merge);

								return 0;
							}
							else {	//합병을 해야한다. ( 재분배가 불가능 )

								int next = curr_idx->fill_cnt;	//curr의 들어가있는 레코드 다음에 넣을 인덱스

								if (right_sibling_idx) {	//오른쪽 형제가 있다면

															//curr와 오른쪽 형제 포인터 사이에 있는 레코드를 넣는다
									strcpy(curr_idx->key[next], parent_idx->key[j]);
									next++;

									//그 다음, 오른쪽 형제의 값들을 curr에 나머지 부분에 넣는다.
									curr_idx->idx_ptr[next] = right_sibling_idx->idx_ptr[0];
									for (i = 0; i < right_sibling_idx->fill_cnt; next++, i++) {
										strcpy(curr_idx->key[next], right_sibling_idx->key[i]);
									}

									//오른쪽 형제 노드 해제
									free(right_sibling_idx);

									//parent에서 curr와 오른쪽 형제 사이에 있던 레코드를 기준으로 왼쪽으로 한칸씩 shift
									for (; j + 1 < parent_idx->fill_cnt; j++) {
										strcpy(parent_idx->key[j], parent_idx->key[j + 1]);
										parent_idx->idx_ptr[j + 1] = parent_idx->idx_ptr[j + 2];
									}

									//한칸 씩 옮겼다면 마지막으로 옮긴 레코드의 원래 위치 레코드와 포인터 초기화
									ptr = &parent_idx->key[j];
									*ptr = NULL;
									parent_idx->idx_ptr[j + 1] = NULL;
									parent_idx->fill_cnt--;

									curr_idx = parent_idx;	//curr에 부모 포인터를 넣고 다시 반복
									merge++;
									continue;

								}
								else {//왼쪽 형제와 합병
									  //curr의 값들을 왼쪽 형제의 레코드들과 curr와 왼쪽 형제 사이의 parent 레코드까지 합친 수만큼 오른쪽으로 shift
									for (i = 0; i < curr_idx->fill_cnt; i++) {
										curr_idx->idx_ptr[i + (left_sibling_idx->fill_cnt + 1)] = curr_idx->idx_ptr[i];
										strcpy(curr_idx->key[i + (left_sibling_idx->fill_cnt + 1)], curr_idx->key[i]);
									}
									curr_idx->idx_ptr[i + (left_sibling_idx->fill_cnt + 1)] = curr_idx->idx_ptr[i];

									//그 다음, curr와 왼쪽 형제 사이의 parent레코드를 옮겨진 curr의 값들 왼쪽에 넣는다.
									strcpy(curr_idx->key[left_sibling_idx->fill_cnt], parent_idx->key[j - 1]);

									//그리고 왼쪽 형제의 값들을 curr에 처음부터 넣는다.
									for (i = 0; i < left_sibling_idx->fill_cnt; i++) {
										curr_idx->idx_ptr[i] = left_sibling_idx->idx_ptr[i];
										strcpy(curr_idx->key[i], left_sibling_idx->key[i]);
									}
									curr_idx->idx_ptr[i] = left_sibling_idx->idx_ptr[i];

									free(left_sibling_idx);	//왼쪽 형제노드 해제

															//parent에서 curr와 왼쪽 형제 사이에 있던 레코드를 기준으로 왼쪽으로 한칸씩 shift
									for (; j < parent_idx->fill_cnt; j++) {
										strcpy(parent_idx->key[j - 1], parent_idx->key[j]);
										parent_idx->idx_ptr[j - 1] = parent_idx->idx_ptr[j];
									}
									parent_idx->idx_ptr[j - 1] = parent_idx->idx_ptr[j];

									//한칸 씩 옮겼다면 마지막으로 옮긴 레코드의 원래 위치 레코드와 포인터 초기화
									ptr = &parent_idx->key[j - 1];
									*ptr = NULL;
									parent_idx->idx_ptr[j] = NULL;
									parent_idx->fill_cnt--;

									curr_idx = parent_idx;  //curr에 부모 포인터를 넣고 다시 반복
									merge++;
									continue;
								}

							}
						}
					}

				}
				else {//왼쪽 형제와 합병
					  //curr의 값들을 왼쪽 형제의 레코드들과 curr와 왼쪽 형제 사이의 parent 레코드까지 합친 수만큼 오른쪽으로 shift
					for (i = 0; i < curr_data->fill_cnt; i++) {
						curr_data->rec[i + (left_sibling_data->fill_cnt + 1)] = curr_data->rec[i];
					}

					//그리고 왼쪽 형제의 값들을 curr에 처음부터 넣는다.
					for (i = 0; i < left_sibling_data->fill_cnt; i++) {
						curr_data->rec[i] = left_sibling_data->rec[i];
					}

					free(left_sibling_data);	//왼쪽 형제노드 해제

												//parent에서 curr와 왼쪽 형제 사이에 있던 레코드를 기준으로 왼쪽으로 한칸씩 shift
					for (; j < parent_idx->fill_cnt; j++) {
						strcpy(parent_idx->key[j - 1], parent_idx->key[j]);
						parent_idx->data_ptr[j - 1] = parent_idx->data_ptr[j];
					}
					parent_idx->data_ptr[j - 1] = parent_idx->data_ptr[j];

					//한칸 씩 옮겼다면 마지막으로 옮긴 레코드의 원래 위치 레코드와 포인터 초기화
					ptr = &parent_idx->key[j - 1];
					*ptr = NULL;
					parent_idx->data_ptr[j] = NULL;
					parent_idx->fill_cnt--;

					curr_idx = parent_idx;  //curr에 부모 포인터를 넣고 다시 반복
					merge++;

					//이제 인덱스 노드가 밸런스가 맞는지 확인해야 함
					while (1) {
						if (curr_idx->fill_cnt < halfK) {	//노드가 balancing에 어긋남

															//부모로 올라가 오른쪽 형제나 왼쪽 형제가 있는지 확인 (오른쪽 형제를 선호)
							parent_idx = stack[top];
							top--;

							for (j = 0; j < parent_idx->fill_cnt; j++) {
								if (parent_idx->idx_ptr[j] == curr_idx) {
									break;
								}
							}

							//j가 parent에서의 curr노드 포인터

							if (j != 0) {
								left_sibling_idx = parent_idx->idx_ptr[j - 1];
							}
							if (j != MAXK) {
								right_sibling_idx = parent_idx->idx_ptr[j + 1];
							}

							if (right_sibling_idx&&right_sibling_idx->fill_cnt > halfK) {	//오른쪽 형제에게 빌려옴 ( 재분배가 가능 )

																							//tbnode에 먼저 curr값을 넣는다
								tibnode.idx_ptr[0] = curr_idx->idx_ptr[0];
								for (k = 0; k < curr_idx->fill_cnt; k++) {
									tibnode.idx_ptr[k + 1] = curr_idx->idx_ptr[k + 1];
									strcpy(tibnode.key[k], curr_idx->key[k]);
								}

								//그 다음, curr와 오른쪽 형제 사이의 부모의 레코드 값을 넣는다.
								strcpy(tibnode.key[k], parent_idx->key[j]);
								k++;

								tibnode.idx_ptr[k] = right_sibling_idx->idx_ptr[0];
								for (m = 0; m < right_sibling_idx->fill_cnt; k++, m++) {
									tibnode.idx_ptr[k + 1] = right_sibling_idx->idx_ptr[m + 1];
									strcpy(tibnode.key[k], right_sibling_idx->key[m]);
								}

								//k에 two_bignode 총 레코드 수가 들어있음

								middle = k / 2;
								//two_bignode에서 middle번째 레코드를 기준으로 왼쪽을 curr에 넣는다.
								for (i = 0; i < middle; i++) {
									curr_idx->idx_ptr[i] = tibnode.idx_ptr[i];
									strcpy(curr_idx->key[i], tibnode.key[i]);
								}
								curr_idx->idx_ptr[i] = tibnode.idx_ptr[i];
								curr_idx->fill_cnt = middle;

								//parent에다가 가운데 값인 halfK번째 레코드 값을 넣는다.
								strcpy(parent_idx->key[j], tibnode.key[halfK]);
								i++;

								//오른쪽 자식에 나머지 two_bignode값들을 넣는다.
								for (m = 0; i < k; m++, i++) {
									right_sibling_idx->idx_ptr[m] = tibnode.idx_ptr[i];
									strcpy(right_sibling_idx->key[m], tibnode.key[i]);
								}
								right_sibling_idx->idx_ptr[m] = tibnode.idx_ptr[i];
								right_sibling_idx->fill_cnt = k - (middle + 1);	//two_bignode의 총 레코드 수에서 curr에 넣은 반과 parent에 넣은 값을 제외한 나머지 수

								retri++;

								printf("삭제에 성공하였습니다!! 재분배는 %d번, 합병은 %d번하였습니다\n", retri, merge);
								return 0;
							}
							else if (left_sibling_idx&&left_sibling_idx->fill_cnt > halfK) {	//왼쪽 형제에게 빌려옴 ( 재분배가 가능 )


																								//tbnode에 먼저 왼쪽 자식노드의 값을 넣는다
								tibnode.idx_ptr[0] = left_sibling_idx->idx_ptr[0];
								for (k = 0; k < left_sibling_idx->fill_cnt; k++) {
									tibnode.idx_ptr[k + 1] = left_sibling_idx->idx_ptr[k + 1];
									strcpy(tibnode.key[k], left_sibling_idx->key[k]);
								}

								strcpy(tibnode.key[k], parent_idx->key[j - 1]);	//그 다음, curr와 왼쪽 형제 사이의 부모의 레코드 값을 넣는다.
								k++;

								//그 다음, curr의 값들을 two_bignode에 넣는다
								tibnode.idx_ptr[k] = curr_idx->idx_ptr[0];
								for (m = 0; m < curr_idx->fill_cnt; k++, m++) {
									tibnode.idx_ptr[k + 1] = curr_idx->idx_ptr[m + 1];
									strcpy(tibnode.key[k], curr_idx->key[m]);
								}

								//k에 two_bignode 총 레코드 수가 들어있음
								middle = k / 2;

								//two_bignode에서 middle번째 레코드를 기준으로 왼쪽을 curr에 넣는다. 		
								for (i = 0; i < middle; i++) {
									left_sibling_idx->idx_ptr[i] = tibnode.idx_ptr[i];
									strcpy(left_sibling_idx->key[i], tibnode.key[i]);
								}
								left_sibling_idx->idx_ptr[i] = tibnode.idx_ptr[i];
								left_sibling_idx->fill_cnt = middle;

								//parent에다가 가운데 값인 middle번째 레코드 값을 넣는다.
								strcpy(parent_idx->key[j], tibnode.key[middle]);

								i++;

								//curr에 나머지 two_bignode값들을 넣는다.
								for (m = 0; i < k; m++, i++) {
									curr_idx->idx_ptr[m] = tibnode.idx_ptr[i];
									strcpy(curr_idx->key[m], tibnode.key[i]);
								}
								curr_idx->idx_ptr[m] = tibnode.idx_ptr[i];
								curr_idx->fill_cnt = k - (middle + 1);	//two_bignode의 총 레코드 수에서 왼쪽 형제에 넣은 반과 parent에 넣은 값을 제외한 나머지 수

								retri++;

								printf("삭제에 성공하였습니다!! 재분배는 %d번, 합병은 %d번하였습니다\n", retri, merge);

								return 0;
							}
							else {	//합병을 해야한다. ( 재분배가 불가능 )

								int next = curr_idx->fill_cnt;	//curr의 들어가있는 레코드 다음에 넣을 인덱스

								if (right_sibling_idx) {	//오른쪽 형제가 있다면

															//curr와 오른쪽 형제 포인터 사이에 있는 레코드를 넣는다
									strcpy(curr_idx->key[next], parent_idx->key[j]);
									next++;

									//그 다음, 오른쪽 형제의 값들을 curr에 나머지 부분에 넣는다.
									curr_idx->idx_ptr[next] = right_sibling_idx->idx_ptr[0];
									for (i = 0; i < right_sibling_idx->fill_cnt; next++, i++) {
										strcpy(curr_idx->key[next], right_sibling_idx->key[i]);
									}

									//오른쪽 형제 노드 해제
									free(right_sibling_idx);

									//parent에서 curr와 오른쪽 형제 사이에 있던 레코드를 기준으로 왼쪽으로 한칸씩 shift
									for (; j + 1 < parent_idx->fill_cnt; j++) {
										strcpy(parent_idx->key[j], parent_idx->key[j + 1]);
										parent_idx->idx_ptr[j + 1] = parent_idx->idx_ptr[j + 2];
									}

									//한칸 씩 옮겼다면 마지막으로 옮긴 레코드의 원래 위치 레코드와 포인터 초기화
									ptr = &parent_idx->key[j];
									*ptr = NULL;
									parent_idx->idx_ptr[j + 1] = NULL;
									parent_idx->fill_cnt--;

									curr_idx = parent_idx;	//curr에 부모 포인터를 넣고 다시 반복
									merge++;
									continue;

								}
								else {//왼쪽 형제와 합병
									  //curr의 값들을 왼쪽 형제의 레코드들과 curr와 왼쪽 형제 사이의 parent 레코드까지 합친 수만큼 오른쪽으로 shift
									for (i = 0; i < curr_idx->fill_cnt; i++) {
										curr_idx->idx_ptr[i + (left_sibling_idx->fill_cnt + 1)] = curr_idx->idx_ptr[i];
										strcpy(curr_idx->key[i + (left_sibling_idx->fill_cnt + 1)], curr_idx->key[i]);
									}
									curr_idx->idx_ptr[i + (left_sibling_idx->fill_cnt + 1)] = curr_idx->idx_ptr[i];

									//그 다음, curr와 왼쪽 형제 사이의 parent레코드를 옮겨진 curr의 값들 왼쪽에 넣는다.
									strcpy(curr_idx->key[left_sibling_idx->fill_cnt], parent_idx->key[j - 1]);

									//그리고 왼쪽 형제의 값들을 curr에 처음부터 넣는다.
									for (i = 0; i < left_sibling_idx->fill_cnt; i++) {
										curr_idx->idx_ptr[i] = left_sibling_idx->idx_ptr[i];
										strcpy(curr_idx->key[i], left_sibling_idx->key[i]);
									}
									curr_idx->idx_ptr[i] = left_sibling_idx->idx_ptr[i];

									free(left_sibling_idx);	//왼쪽 형제노드 해제

															//parent에서 curr와 왼쪽 형제 사이에 있던 레코드를 기준으로 왼쪽으로 한칸씩 shift
									for (; j < parent_idx->fill_cnt; j++) {
										strcpy(parent_idx->key[j - 1], parent_idx->key[j]);
										parent_idx->idx_ptr[j - 1] = parent_idx->idx_ptr[j];
									}
									parent_idx->idx_ptr[j - 1] = parent_idx->idx_ptr[j];

									//한칸 씩 옮겼다면 마지막으로 옮긴 레코드의 원래 위치 레코드와 포인터 초기화
									ptr = &parent_idx->key[j - 1];
									*ptr = NULL;
									parent_idx->idx_ptr[j] = NULL;
									parent_idx->fill_cnt--;

									curr_idx = parent_idx;  //curr에 부모 포인터를 넣고 다시 반복
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
			}
		}
	}
}



int B_plus_tree_Sequential_print(type_ptr_idxnode root) {

	FILE * fp = fopen("SeqData.txt", "w");
	int i = 0;
	int j = 0;
	int on[100];	//부모의 i 저장용( 부모가 어느 자식까지 확인했는지 체크 )
	int top = -1;	//현재 노드의 level root가 -1 자식으로 내려갈 수록 1씩 +

	type_ptr_idxnode stack[50];	//부모 보관용
	type_ptr_idxnode idx_curr;	//현재 노드
	type_ptr_idxnode P;	//보관용 포인터
	type_ptr_datanode data_curr;	//현재 노드
	if (!root) {
		printf("데이터가 하나도 존재하지 않습니다....\n");
		return 1;
	}

	idx_curr = root;

	while (idx_curr->idx_ptr[0]) {
		idx_curr = idx_curr->idx_ptr[0];
	}
	data_curr = idx_curr->data_ptr[0];
	while (1) {
		for (i = 0; i < data_curr->fill_cnt; i++) {
			fprintf(fp, "%s %s %d\n", data_curr->rec[i].wstr, data_curr->rec[i].pos, data_curr->rec[i].numpos);
		}
		if (data_curr->data_ptr) {
			data_curr = data_curr->data_ptr;
			continue;
		}
		else
			break;

	}
	printf("출력완료했습니다\n");
	fclose(fp);


}

int B_plus_tree_range_search(char data1[100], char data2[100], type_ptr_idxnode root) {
	char key1[100];//data1을 담을 키
	char key2[100];//data2를 담을 키
	char key_buff[100];//두 데이터 크기에 따른 둘 중 하나의 키 값을 넣어둘 버퍼
	int check_who=0;	//1이면 data1이크고 2이면 data2가 큼
	int i;
	int find = 0;//data2를 찾았으면 1 아니면 0
	int top = -1;
	int level = 0;
	int check_word1=0;//data1이 b+tree내에 있었는지 확인
	int check_word2=0;//data2가 b+tree내에 있었는지 확인
	int check_have_data = 0;	//찾는 데이터가 있는지 확인하는 변수 ( 1이면 있고 0이면 없음 )
	FILE * fp = fopen("amongData.txt", "w");
	type_ptr_idxnode stack[50];	//부모 보관용
	type_ptr_idxnode curr_idx;	//현재 노드
	type_ptr_datanode curr_data;
	type_ptr_datanode curr_data_word1;
	type_ptr_datanode curr_data_word2;
	type_ptr_idxnode P;	//보관용 포인터
	strcpy(key1, data1);//키 값 복사
	curr_idx = root;

	if (!root) {
		printf("데이터가 하나도 존재하지 않습니다....\n");
		return 1;
	}
	while (1) {	//첫번째 word가 있는 데이타노드를 찾는다

		for (i = 0; i < curr_idx->fill_cnt; i++) {

			if (strcmp(key1, curr_idx->key[i]) <= 0) {//입력데이터가 curr의 어떤 데이터보다 작다면
				if (strcmp(key1, curr_idx->key[i]) == 0)
					check_word1 = 1;
				P = curr_idx->idx_ptr[i];	//그 데이터의 왼쪽 자식포인터를 P에 넣음
				break;
			}
		}

		if (i == curr_idx->fill_cnt) {//curr의 제일 큰 데이터보다 크다면
			P = curr_idx->idx_ptr[i];	//그 데이터의 오른쪽 자식 포인터를 P에 넣음
		}

		if (curr_idx->data_ptr[0] != NULL) {	//데이터 노드 바로 위의 인덱스 노드를 찾음
			P = NULL;
		}
		if (P) {	//자식이 존재
			top++;
			level = top + 1;
			stack[top] = curr_idx;
			curr_idx = P;
			continue;
		}
		else //word1이 있는 데이타노드를 찾음( i가 데이터노드를 가리키는 인덱스 값을 가지고 있음)
		{
			curr_data_word1 = curr_idx->data_ptr[i];	//데이타노드를 가리키는 포인터를 curr_data_word1에 옮겨줌

			break;

		}

	}

	for (int j = 0; j < curr_data_word1->fill_cnt; j++) {
		if (strcmp(key1, curr_data_word1->rec[j].wstr) == 0) {
			check_have_data = 1;
			break;
		}
	}
	if (check_have_data == 0) {
		printf("찾는 변수가 존재하지않습니다...\n");
		return -1;
	}


	check_have_data = 0;	//초기화
	strcpy(key2, data2);//키 값 복사
	curr_idx = root;


	while (1) {//두번째 word가 있는 데이타노드를 찾는다

		for (i = 0; i < curr_idx->fill_cnt; i++) {

			if (strcmp(key2, curr_idx->key[i]) <= 0) {//입력데이터가 curr의 어떤 데이터보다 작다면
				if (strcmp(key2, curr_idx->key[i]) == 0)
					check_word2 = 1;
				P = curr_idx->idx_ptr[i];	//그 데이터의 왼쪽 자식포인터를 P에 넣음
				break;
			}
		}

		if (i == curr_idx->fill_cnt) {//curr의 제일 큰 데이터보다 크다면
			P = curr_idx->idx_ptr[i];	//그 데이터의 오른쪽 자식 포인터를 P에 넣음
		}

		if (curr_idx->data_ptr[0] != NULL) {	//데이터 노드 바로 위의 인덱스 노드를 찾음
			P = NULL;
		}
		if (P) {	//자식이 존재
			top++;
			level = top + 1;
			stack[top] = curr_idx;
			curr_idx = P;
			continue;
		}
		else //word2가 있는 데이타노드를 찾음( i가 데이터노드를 가리키는 인덱스 값을 가지고 있음)
		{
			curr_data_word2 = curr_idx->data_ptr[i];	//데이타노드를 가리키는 포인터를 curr_data_word2에 옮겨줌
			break;
		}

	}

	for (int j = 0; j < curr_data_word2->fill_cnt; j++) {
		if (strcmp(key2, curr_data_word2->rec[j].wstr) == 0) {
			check_have_data = 1;
			break;
		}
	}
	if (check_have_data == 0) {
		printf("찾는 변수가 존재하지않습니다...\n");
		return -1;
	}
	//여기 까지 왔다면 현재 두 단어가 다 존재한다는 뜻이고 curr_data_word1과 curr_data_word2는 현재 두 단어가 있는 데이터 노드를 가르키고 있음
	if (strcmp(data1, data2)>0) {//data1이 더 크다면
		curr_data = curr_data_word2;
		
		check_who = 1;	
	}
	else if (strcmp(data1, data2) < 0) {//data2가 더 크다면
		curr_data = curr_data_word1;
		check_who = 2;
	}
	else {//둘이 같은 단어라면
		printf("같은 단어를 고르셨습니다..\n");
		return -1;
	}
	int j;
	if (check_who == 1) {
		strcpy(key_buff, key2);
	}
	else if (check_who == 2) {
		strcpy(key_buff, key1);
	}
	else {
		printf("오류발생!\n");
		return -1;
	}
		
	for (j = 0; j < curr_data->fill_cnt; j++) {
		if (strcmp(key_buff, curr_data->rec[j].wstr) == 0) {
			break;
		}
	}
	for (; j < curr_data->fill_cnt; j++) {//처음 data1(data2)이 있는 노드에서 data1(data2)부터 그 노드의 마지막 단어까지 화일에 출력함
		if (check_who == 1) {//b+tree에 없는 데이타면 출력하지 않음
			if (check_word1 != 1)
				j++;
		}
		else if (check_who == 2) {
			if (check_word2 != 1)
				j++;
		}
		else {
			printf("오류발생!\n");
			return -1;
		}
		fprintf(fp, "%s %s %d\n", curr_data->rec[j].wstr, curr_data->rec[j].pos, curr_data->rec[j].numpos);
	}

	if (check_who == 1) {
		strcpy(key_buff, key1);
	}
	else if (check_who == 2) {
		strcpy(key_buff, key2);
	}
	else {
		printf("오류발생!\n");
		return -1;
	}

	while (curr_data->data_ptr) {
		curr_data = curr_data->data_ptr;
		for (int k = 0; k < curr_data->fill_cnt; k++) {
			if (strcmp(key_buff, curr_data->rec[k].wstr) == 0) {//현재 여기서 key_buff는 두 데이터중 큰 데이터의 값임 (그 데이터까지 왔다면 그것까지 출력하고 나감)
				if (check_who == 2) {
					if (check_word1 == 1)
						fprintf(fp, "%s %s %d\n", curr_data->rec[k].wstr, curr_data->rec[k].pos, curr_data->rec[k].numpos);
				}
				else if (check_who == 1) {
					if (check_word2 == 1)
						fprintf(fp, "%s %s %d\n", curr_data->rec[k].wstr, curr_data->rec[k].pos, curr_data->rec[k].numpos);
				}
				else {
					printf("오류발생!\n");
					return -1;
				}
				
				find = 1;
				break;
			}
			fprintf(fp, "%s %s %d\n", curr_data->rec[k].wstr, curr_data->rec[k].pos, curr_data->rec[k].numpos);
		}
		if (find == 1)
			break;
	}

	printf("출력완료했습니다\n");
	fclose(fp);
	return 0;




}
int main() {
	char text[30];
	char ins[30];	//명령어 변수
	char data1[100];	//데이터 변수1
	char data2[100];	//변수2
	int split = 0;
	int check = 0;	//명령어와 데이터 변수끼리 자르기 위한 체크 변수
	int success = 1;	//에러 여부	( 성공 = 0 에러 = 1)
	type_rec in_rec;
	while (success == 1) {	//실패면 반복, 성공이면 빠져나감
		printf("입력 텍스트 화일명은?");
		scanf("%s", text);
		getchar();
		success = putdatast(text);
	}
	while (1) {
		check = 0;//초기화
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
					data1[j] = getchar();

					if (data1[j] == '\n') {
						data1[j] = '\0';
						check = 1;
						break;
					}
					if (data1[j] == ' ') {
						data1[j] = '\0';
						for (int k = 0;; k++) {
							data2[k] = getchar();

							if (data2[k] == '\n') {
								check = 1;
								data2[k] = '\0';
								break;
							}
						}
						if (check == 1)
							break;
					}
				}
				if (check == 1)
					break;
			}
		}



		if (strcmp(ins, "i") == 0) {	//insertion
			in_rec = makeRec(data1);
			split = b_plus_tree_insertion_test(in_rec, &root);

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
			B_plus_tree_Search(data1, root);
		}
		else if (strcmp(ins, "delete") == 0) {	//deletion( 삭제는 완성하지 못했습니다. 죄송합니다.)
			B_plus_tree_Deletion(data1, &root);
		}
		else if (strcmp(ins, "seqprint") == 0) {	//printout
			B_plus_tree_Sequential_print(root);
		}
		else if (strcmp(ins, "rquery") == 0) {
			B_plus_tree_range_search(data1, data2, root);

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
