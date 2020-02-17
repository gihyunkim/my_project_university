#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXK 4 //2d
#define halfK 2 //d
#pragma warning (disable:4996)

typedef struct idxnode *type_ptr_idxnode; //indexnode �� ������
typedef struct datanode *type_ptr_datanode;

typedef struct _rec {	//���ڵ屸��ü
	char wstr[100];
	char pos[10];
	int numpos;
}type_rec;

//�ε��� ��� ( B-TREE�� ������ )
typedef struct idxnode {
	char key[100][100];
	type_ptr_idxnode idx_ptr[MAXK + 1];
	type_ptr_datanode data_ptr[MAXK + 1];
	int fill_cnt;
}idxnode;

//������ ���
typedef struct datanode {
	type_rec rec[MAXK];
	type_ptr_datanode data_ptr;
	int fill_cnt;
}datanode;

//���� ( �Ϲ� ��庸�� ���ڵ� ���� ��������ͼ��� 1�� �� ���� ��� )(�ε��� ���� )
typedef struct idx_bignode {
	type_ptr_idxnode idx_ptr[MAXK + 2];
	type_ptr_datanode data_ptr[MAXK + 2];
	char key[MAXK + 1][100];
}idx_bignode;

//����(������ ����)
typedef struct data_bignode {

	type_rec rec[MAXK + 1];
}data_bignode;

//�Ϲ� ��庸�� �� �� �� ū ���(�ε�������)
typedef struct idx_two_bignode {
	type_ptr_idxnode idx_ptr[2 * MAXK + 1];
	type_ptr_datanode data_ptr[2 * MAXK + 1];
	char key[2 * MAXK][100];
}idx_two_bignode;

//�Ϲ� ��庸�� �� �� �� ū ���(�����ͳ���)
typedef struct data_two_bignode {

	type_rec rec[2 * MAXK];
}data_two_bignode;

//root��带 ����Ű�� ������
type_ptr_idxnode root = NULL;

int b_plus_tree_insertion(type_rec in_rec, type_ptr_idxnode *root);

int putdatast(char text[30]) {//����Ÿ�� ����ü�� �Է�

	char buffer[200];	//�ܾ�� ������� �ӽù迭
	int wordnum = 0;	//ǰ���� �� ����
	int check = 0;		//������ ��������ʾҴٴ� ���� Ȯ�� ����( 1�̸� ������� ���� ���� )
	char *get_err = NULL; //fgets�������˿�
	FILE * fp = fopen(text, "r+");
	type_rec one_record;
	type_rec* recptr = &one_record;

	if (!fp) {
		printf("������ ����� �������ʾҽ��ϴ�...\n");
		return 1;
	}

	while (1) {

		int i = 0;
		int j = 0;
		int k = 0;
		int word_length = 0;	//word�� ����
		wordnum = 0;



		get_err = fgets(buffer, sizeof(buffer), fp);	//�� ���� wordlist���� �о�´�

		if (!get_err)
		{
			if (check == 1) {//�� ������ �ƴ϶�, ���� �Ŀ� ������ ���� ��
				break;
			}
			printf("�����Ͱ� �����ϴ�");	//�� ����
			break;
		}
		else if (strcmp(get_err, "\n") == 0) //��ĭ�� �ִٸ� �ѱ��
		{
			continue;
		}


		check = 1;	//������ ������� �ʴ�

					//--------------------------------word----------------------------------

		for (; !(isspace(buffer[i])); i++) {	//ó�� ���ڿ� �ѱ�

		}

		for (; isspace(buffer[i]); i++) {	//�����̽� �ѱ�

		}

		for (; !(isspace(buffer[i])); i++) {	//�ι�° ���ڿ��� �ѱ�

		}

		for (; isspace(buffer[i]); i++) {	//�����̽� �ѱ�

		}

		for (j = 0; !(isspace(buffer[i])); i++, j++) {	//����° ���ڿ�(�� ���ڿ�)�� ����ü ���ڿ� �ִ´�
			recptr->wstr[j] = buffer[i];
			word_length++;
		}

		recptr->wstr[j] = '\0';	//���ڿ� �ϼ�

								//-----------------------------pos------------------------------------

		for (; !(isupper(buffer[i])); i++) {	//ǰ�翭�� ���� ������ ��ŵ

												//ǰ�翭�� ���� ���
			if (buffer[i] == '\n') {
				strcpy(recptr->pos, "  ");
				break;
			}
			if (buffer[i] == '\0') {
				strcpy(recptr->pos, "  ");
				break;
			}
		}

		if (buffer[i] != '\n' && buffer[i] != '\0') {	//ǰ�翭�� ���� ���

			for (k = 0; buffer[i] != ' '; i++, k++) {	//ó�� ǰ�翭�� ����ü ���ڿ� �ִ´�

				if (buffer[i] == '\n')	//������ ǰ�翭�� ���
					break;
				if (buffer[i] == '\0')	//���� �� ������ ǰ�翭�� ���
					break;

				recptr->pos[k] = buffer[i];

			}

			recptr->pos[k] = '\0';//���ڿ� �ϼ�

			wordnum++;

			//-----------------------------numpos------------------------------------

			while (buffer[i] != '\n') {//������ ������������ ǰ��� ����

				if (buffer[i] == '\0')//������ ��������
					break;

				for (; !(isupper(buffer[i])); i++) {//ǰ�翭�� ���� ������ ��ŵ

													//ǰ�翭 �ڿ� �ٸ� ��ȣ�� �� ���
					if (buffer[i] == '\n')
						break;
					if (buffer[i] == '\0')
						break;
				}

				//ǰ�翭�� ���� +1
				wordnum++;

				//ǰ�翭 
				for (; buffer[i] != ' '; i++) {

					//ǰ�翭�� ���̻� ���ٸ�
					if (buffer[i] == '\n')
						break;
					if (buffer[i] == '\0')
						break;
				}

			}
		}

		recptr->numpos = wordnum;

		b_plus_tree_insertion(one_record, &root);//B_+TREE ����

		//---------------------------------------------------------------------
		for (int n = 0; n < word_length; n++) {//����ü �ʱ�ȭ
			recptr->wstr[n] = ' ';
		}

		for (int n = 0; n < wordnum; n++) {
			recptr->pos[n] = ' ';
		}
		recptr->numpos = 0;
		//--------------------------------------------------------------------

		if (buffer[i] == '\0') {//������ �����ٸ�
			break;
		}
	}
	fclose(fp);
}


int b_plus_tree_insertion(type_rec in_rec, type_ptr_idxnode *root) {

	//**node�տ� idx�� �پ������� �ε������� data�� �پ������� ������ �����̴�

	char key[100];
	int i, j, k, m;
	int top = -1;
	int check = 0;
	type_rec* recptr = &in_rec;
	type_ptr_idxnode rnew;	//�� root�� ���
	type_ptr_idxnode stack[50];	//�θ� ������
	type_ptr_idxnode root_idx;	//��Ʈ������
	type_ptr_idxnode curr_idx;	//���� �ε��� ���
	type_ptr_idxnode new_idx;
	type_ptr_idxnode P;	//������ ������
	idx_bignode binode;	//index_bignode( ���� indexnode���� ���ڵ�� �����ͼ��� �ϳ��� �� ���� ��� )

	type_ptr_datanode new_data;	//�� á�� ���� �� ���
	type_ptr_datanode curr_data;

	data_bignode bdnode;//data_bignode( ���� datanode���� ���ڵ�� �����ͼ��� �ϳ��� �� ���� ��� )

	type_ptr_idxnode n;
	type_ptr_datanode nd;

	if (!*root) {	//ROOT�� NULL�� ��� ( �ʱ��Ȳ)

		n = (type_ptr_idxnode)malloc(sizeof(idxnode));	//�ε�����带 �ϳ� ���� ��
		strcpy(n->key[0], recptr->wstr);
		n->idx_ptr[0] = n->idx_ptr[1] = NULL;
		n->fill_cnt = 1;
		*root = n;	//��Ʈ�� ����Ű�� ��

		nd = (type_ptr_datanode)malloc(sizeof(datanode));	//�����ͳ�带 �ϳ� ���� ��
		nd->rec[0] = in_rec;
		nd->fill_cnt = 1;
		root_idx = *root;

		root_idx->data_ptr[0] = nd;	//��Ʈ �ε�������� ������[0]�� ����Ű�� ��
		root_idx->data_ptr[1] = NULL;	//��Ʈ �ε�������� ������[1] = NULL�� �ʱ�ȭ

		return 0;
	}

	root_idx = *root;
	curr_idx = root_idx;
	strcpy(key, recptr->wstr);//Ű �� ����

	if (root_idx->data_ptr[1] == NULL) {	//Root�� Null�� �ƴ� ����� �ʹݺ� ����

		curr_data = root_idx->data_ptr[0];

		if (curr_data->fill_cnt < MAXK) {	//������ ��忡 ���ڸ��� �ִٸ�
			for (i = 0; i < curr_data->fill_cnt; i++) {
				if (strcmp(key, curr_data->rec[i].wstr) == 0) {
					return -1;
				}
				if (strcmp(key, curr_data->rec[i].wstr) < 0) {//�Էµ����Ͱ� curr�� �����͵麸�� �۴ٸ�
					for (j = curr_data->fill_cnt - 1; j >= i; j--) {//���������� ��ĭ�� push
						curr_data->rec[j + 1] = curr_data->rec[j];
					}
					//�Էµ����� ������ �ڸ��� �ֱ�
					curr_data->rec[i] = in_rec;
					curr_data->fill_cnt++;
					return 1;
				}

			}
			if (i == curr_data->fill_cnt) {//curr�� �����͵麸�� ũ�ٸ�
				curr_data->rec[i] = in_rec;	//������ �ڸ��� �ֱ�
				curr_data->fill_cnt++;
				strcpy(root_idx->key[0], in_rec.wstr);
				return 1;
			}
		}
		else {	//���ڸ��� ���� ���
			strcpy(key, in_rec.wstr);
			for (k = 0; k < MAXK; k++) {	//key������ �������� ã��
				if (strcmp(key, curr_data->rec[k].wstr) < 0) //�� ã������ break
					break;
			}

			for (m = 0; m < k; m++) {	//key������ �������� bnode�� ���� �ֱ�
				bdnode.rec[m] = curr_data->rec[m];
			}

			//�� ����, �Է� ������ �ֱ�
			bdnode.rec[m] = in_rec;
			m++;

			//������ bnode�� �ֱ�
			for (; m < MAXK + 1; m++) {
				bdnode.rec[m] = curr_data->rec[m - 1];
			}

			for (i = 0; i < halfK + 1; i++) {	//���� ���� curr�� �־��ش�(�߰����ڵ� ����)
				curr_data->rec[i] = bdnode.rec[i];
			}
			curr_data->fill_cnt = halfK + 1;

			for (; i < MAXK; i++) {	//curr�� ������ ������ ����
				type_ptr_datanode *buff = &curr_data->rec[i];
				*buff = NULL;
				curr_data->rec[i].numpos = 0;
				buff = &curr_data->rec[i].pos;
				*buff = NULL;
			}

			//new��� ���� �� ������ �� ������ �ֱ�
			new_data = (type_ptr_datanode)malloc(sizeof(datanode));

			for (i = 0; i < halfK; i++) {
				new_data->rec[i] = bdnode.rec[i + halfK + 1];
			}
			new_data->fill_cnt = halfK;

			strcpy(root_idx->key[0], bdnode.rec[halfK].wstr);	//�߰����ڵ带 ��Ʈ �ε�������� KEY���� ����
			root_idx->data_ptr[1] = new_data;	//���� ���� ��带 �ε��� ����� data_ptr[1]�� ����
			curr_data->data_ptr = new_data;		//�� ����Ÿ ��峢�� ����
			new_data->data_ptr = NULL;		//���� ���� ����� link�� NULL
		}

	}
	else if (root_idx->data_ptr[1] != NULL) {	//��������� ���(�ʱ� ��Ȳ�� �ƴ� ���)

		while (1) {	//�����Ͱ� �� ����Ÿ��带 ã�´�

			for (i = 0; i < curr_idx->fill_cnt; i++) {

				if (strcmp(key, curr_idx->key[i]) == 0) {
					return -1;
				}
				if (strcmp(key, curr_idx->key[i]) < 0) {//�Էµ����Ͱ� curr�� � �����ͺ��� �۴ٸ�
					P = curr_idx->idx_ptr[i];	//�� �������� ���� �ڽ������͸� P�� ����
					break;
				}
			}

			if (i == curr_idx->fill_cnt) {//curr�� ���� ū �����ͺ��� ũ�ٸ�
				P = curr_idx->idx_ptr[i];	//�� �������� ������ �ڽ� �����͸� P�� ����
			}

			if (curr_idx->data_ptr[0] != NULL) {	//������ ��� �ٷ� ���� �ε��� ��带 ã��
				P = NULL;
			}
			if (P) {	//�ڽ��� ����
				top++;
				stack[top] = curr_idx;
				curr_idx = P;
				continue;
			}
			else //����Ÿ����� �ٷ� �� index��忡�� ����Ÿ��带 ã��( i�� �����ͳ�带 ����Ű�� �ε��� ���� ������ ����)
			{
				curr_data = curr_idx->data_ptr[i];	//����Ÿ��带 ����Ű�� �����͸� curr_data�� �Ű���

				break;

			}

		}

		while (1) {	//curr_data�� ���� ������ ����Ÿ 

			if (curr_data->fill_cnt != MAXK) {	//������ ��尡 �� ���� �ʾ��� ���

				for (i = 0; i < curr_data->fill_cnt; i++) {

					if (strcmp(key, curr_data->rec[i].wstr) == 0) {
						return -1;
					}
					if (strcmp(key, curr_data->rec[i].wstr) < 0) {//�Էµ����Ͱ� ������ ����� �����͵麸�� �۴ٸ�
						for (j = curr_data->fill_cnt - 1; j >= i; j--) {//���������� ��ĭ�� push
							curr_data->rec[j + 1] = curr_data->rec[j];
						}
						//�Էµ����� ������ �ڸ��� �ֱ�
						curr_data->rec[i] = in_rec;
						curr_data->fill_cnt++;
						return 0;
					}
				}
				if (i == curr_data->fill_cnt) {//������ ����� �����͵麸�� ũ�ٸ�
					curr_data->rec[i] = in_rec;	//������ �ڸ��� �ֱ�
					curr_data->fill_cnt++;
					return 0;
				}
			}
			else {	//�����ͳ�尡 �� á�� ���

				type_ptr_datanode ptr_new_data;
				char mid_key[100];	//���忡�� �߰����ڵ��� key

				for (i = 0; i < curr_data->fill_cnt; i++) {//�ߺ��˻�
					if (strcmp(key, curr_data->rec[i].wstr) == 0) {
						return -1;
					}
				}

				for (k = 0; k < MAXK; k++) {	//key������ �������� ã��
					if (strcmp(key, curr_data->rec[k].wstr) < 0) //�� ã������ break
						break;
				}

				for (m = 0; m < k; m++) {	//key������ �������� bnode�� ���� �ֱ�
					bdnode.rec[m] = curr_data->rec[m];
				}

				//�� ����, �Է� ������ �ֱ�
				bdnode.rec[m] = in_rec;
				m++;

				//������ bnode�� �ֱ�
				for (; m < MAXK + 1; m++) {
					bdnode.rec[m] = curr_data->rec[m - 1];
				}

				for (i = 0; i < halfK + 1; i++) {	//���� ���� ���� �����ͳ�忡 �־��ش�(�߰����ڵ� ����)
					curr_data->rec[i] = bdnode.rec[i];
				}
				curr_data->fill_cnt = halfK + 1;

				for (; i < MAXK; i++) {	//���� �����ͳ���� ������ ������ ����
					type_ptr_datanode *buff = &curr_data->rec[i];
					*buff = NULL;
					curr_data->rec[i].numpos = 0;
					buff = &curr_data->rec[i].pos;
					*buff = NULL;
				}

				//new������ ��� ���� �� ������ �� ������ �ֱ�
				new_data = (type_ptr_datanode)malloc(sizeof(datanode));

				for (i = 0; i < halfK; i++) {
					new_data->rec[i] = bdnode.rec[i + halfK + 1];
				}
				new_data->fill_cnt = halfK;
				new_data->data_ptr = curr_data->data_ptr;
				curr_data->data_ptr = new_data;

				strcpy(mid_key, bdnode.rec[halfK].wstr);
				ptr_new_data = new_data;

				//���� ���⼭ curr_idx�� ���� mid_key���� ptr_new_data�� ���� �ε��� ����̴�.

				if (curr_idx->fill_cnt < MAXK) {//curr_idx ��忡 �� �ڸ��� �ִ� ���
					int x;
					for (x = 0; x < curr_idx->fill_cnt; x++) {
						if (strcmp(mid_key, curr_idx->key[x]) < 0) {
							for (j = curr_idx->fill_cnt - 1; j >= x; j--) {//���������� ��ĭ�� push
								strcpy(curr_idx->key[j + 1], curr_idx->key[j]);
								curr_idx->data_ptr[j + 2] = curr_idx->data_ptr[j + 1];
							}
							//�Էµ����� ������ �ڸ��� �ֱ�
							strcpy(curr_idx->key[x], mid_key);
							curr_idx->data_ptr[x + 1] = ptr_new_data;
							curr_idx->fill_cnt++;
							return 1;


						}
					}
					if (x == curr_idx->fill_cnt) {//curr�� �����͵麸�� ũ�ٸ�
						strcpy(curr_idx->key[x], mid_key);	//������ �ڸ��� �ֱ�
						curr_idx->data_ptr[x + 1] = ptr_new_data;
						curr_idx->fill_cnt++;
						return 1;
					}


				}
				else {//�� �ڸ��� ���� ���

					for (k = 0; k < MAXK; k++) {	//key������ �������� ã��
						if (strcmp(mid_key, curr_idx->key[k]) < 0) //�� ã������ break
							break;
					}

					binode.data_ptr[0] = curr_idx->data_ptr[0];

					for (m = 0; m < k; m++) {	//key������ �������� bnode�� ���� �ֱ�
						binode.data_ptr[m + 1] = curr_idx->data_ptr[m + 1];
						strcpy(binode.key[m], curr_idx->key[m]);
					}

					//�� ����, �Է� ������ �ֱ�
					binode.data_ptr[m + 1] = ptr_new_data;
					strcpy(binode.key[m], mid_key);
					m++;

					//������ bnode�� �ֱ�
					for (; m < MAXK + 1; m++) {
						binode.data_ptr[m + 1] = curr_idx->data_ptr[m];
						strcpy(binode.key[m], curr_idx->key[m - 1]);
					}

					for (i = 0; i < halfK; i++) {	//���� ���� curr�� �־��ش�(  �߰�key������)
						curr_idx->data_ptr[i] = binode.data_ptr[i];
						strcpy(curr_idx->key[i], binode.key[i]);
					}
					curr_idx->fill_cnt = halfK;
					curr_idx->data_ptr[i] = binode.data_ptr[i];

					for (; i < MAXK; i++) {	//curr�� ������ ������ ����
						curr_idx->data_ptr[i + 1] = NULL;
						type_ptr_idxnode *buff = &curr_idx->key[i];
						*buff = NULL;
					}

					//new��� ���� �� ������ �� ������ �ֱ�
					new_idx = (type_ptr_idxnode)malloc(sizeof(idxnode));


					for (i = 0; i < halfK; i++) {

						new_idx->data_ptr[i] = binode.data_ptr[i + halfK + 1];
						strcpy(new_idx->key[i], binode.key[i + halfK + 1]);
					}
					new_idx->data_ptr[i] = binode.data_ptr[i + halfK + 1];
					new_idx->fill_cnt = halfK;


					//��� ������
					P = new_idx;
					strcpy(mid_key, binode.key[halfK]);

					if (top >= 0) {//�θ� ��尡 �����Ѵٸ�
						int x;
						curr_idx = stack[top];
						top--;
						while (1) {
							if (curr_idx->fill_cnt != MAXK) {	//�θ� �ε��� ��尡 �� ���� �ʾ��� ���
								for (x = 0; x < curr_idx->fill_cnt; x++) {
									if (strcmp(mid_key, curr_idx->key[x]) < 0) {
										for (j = curr_idx->fill_cnt - 1; j >= x; j--) {//���������� ��ĭ�� push
											strcpy(curr_idx->key[j + 1], curr_idx->key[j]);
											curr_idx->idx_ptr[j + 2] = curr_idx->idx_ptr[j + 1];
										}
										//�Էµ����� ������ �ڸ��� �ֱ�
										strcpy(curr_idx->key[x], mid_key);
										curr_idx->data_ptr[0] = NULL;
										curr_idx->idx_ptr[x + 1] = P;
										curr_idx->fill_cnt++;
										return 1;


									}
								}
								if (x == curr_idx->fill_cnt) {//curr�� �����͵麸�� ũ�ٸ�
									strcpy(curr_idx->key[x], mid_key);	//������ �ڸ��� �ֱ�
									curr_idx->data_ptr[0] = NULL;
									curr_idx->idx_ptr[x + 1] = P;
									curr_idx->fill_cnt++;
									return 1;
								}

							}

							else {//�� á�� ���
								for (k = 0; k < MAXK; k++) {	//key������ �������� ã��
									if (strcmp(mid_key, curr_idx->key[k]) < 0) //�� ã������ break
										break;
								}

								strcpy(binode.key[0], curr_idx->idx_ptr[0]);
								binode.idx_ptr[0] = curr_idx->idx_ptr[0];
								for (m = 0; m < k; m++) {	//key������ �������� bnode�� ���� �ֱ�
									binode.idx_ptr[m + 1] = curr_idx->idx_ptr[m + 1];
									strcpy(binode.key[m], curr_idx->key[m]);
								}

								//�� ����, �Է� ������ �ֱ�
								binode.idx_ptr[m + 1] = P;
								strcpy(binode.key[m], mid_key);
								m++;

								//������ bnode�� �ֱ�
								for (; m < MAXK + 1; m++) {
									binode.idx_ptr[m + 1] = curr_idx->idx_ptr[m];
									strcpy(binode.key[m], curr_idx->key[m - 1]);
								}

								for (i = 0; i < halfK; i++) {	//���� ���� curr�� �־��ش�
									curr_idx->idx_ptr[i] = binode.idx_ptr[i];
									strcpy(curr_idx->key[i], binode.key[i]);
								}
								curr_idx->fill_cnt = halfK;
								curr_idx->idx_ptr[i] = binode.idx_ptr[i];

								for (; i < MAXK; i++) {	//curr�� ������ ������ ����
									curr_idx->idx_ptr[i + 1] = NULL;
									type_ptr_idxnode *buff = &curr_idx->key[i];
									*buff = NULL;
								}

								//new��� ���� �� ������ �� ������ �ֱ�
								new_idx = (type_ptr_idxnode)malloc(sizeof(idxnode));


								for (i = 0; i < halfK; i++) {

									new_idx->idx_ptr[i] = binode.idx_ptr[i + halfK + 1];
									strcpy(new_idx->key[i], binode.key[i + halfK + 1]);
								}
								new_idx->data_ptr[0] = NULL;
								new_idx->idx_ptr[i] = binode.idx_ptr[i + halfK + 1];
								new_idx->fill_cnt = halfK;

								//��� ������
								P = new_idx;
								strcpy(mid_key, binode.key[halfK]);

								if (top >= 0) {//�θ� ��尡 �����Ѵٸ�
									curr_idx = stack[top];
									top--;
									continue;
								}
								else {//�θ� ��尡 �������� �ʴ´ٸ�
									rnew = (type_ptr_idxnode)malloc(sizeof(idxnode));
									rnew->idx_ptr[0] = curr_idx;
									strcpy(rnew->key[0], mid_key);
									rnew->idx_ptr[1] = P;
									rnew->fill_cnt = 1;
									rnew->data_ptr[0] = NULL;
									*root = rnew;	//�θ� ��尡 �������� �ʴ´ٸ� �� �� ��尡 ��Ʈ�� ��
									return 1;
								}
							}
						}
					}
					else {//�θ� ��尡 �������� �ʴ´ٸ�
						rnew = (type_ptr_idxnode)malloc(sizeof(idxnode));
						rnew->idx_ptr[0] = curr_idx;
						strcpy(rnew->key[0], mid_key);
						rnew->idx_ptr[1] = P;
						rnew->fill_cnt = 1;
						rnew->data_ptr[0] = NULL;
						*root = rnew;	//�θ� ��尡 �������� �ʴ´ٸ� �� �� ��尡 ��Ʈ�� ��
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


	//**node�տ� idx�� �پ������� �ε������� data�� �پ������� ������ �����̴�

	char key[100];
	int i, j, k, m;
	int top = -1;
	int split = 0;//split�� Ƚ��
	int check = 0;
	type_rec* recptr = &in_rec;
	type_ptr_idxnode rnew;	//�� root�� ���
	type_ptr_idxnode stack[50];	//�θ� ������
	type_ptr_idxnode root_idx;	//��Ʈ������
	type_ptr_idxnode curr_idx;	//���� �ε��� ���
	type_ptr_idxnode new_idx;
	type_ptr_idxnode P;	//������ ������
	idx_bignode binode;	//index_bignode( ���� indexnode���� ���ڵ�� �����ͼ��� �ϳ��� �� ���� ��� )

	type_ptr_datanode new_data;	//�� á�� ���� �� ���
	type_ptr_datanode curr_data;

	data_bignode bdnode;//data_bignode( ���� datanode���� ���ڵ�� �����ͼ��� �ϳ��� �� ���� ��� )

	type_ptr_idxnode n;
	type_ptr_datanode nd;

	if (!*root) {	//ROOT�� NULL�� ��� ( �ʱ��Ȳ)

		n = (type_ptr_idxnode)malloc(sizeof(idxnode));	//�ε�����带 �ϳ� ���� ��
		strcpy(n->key[0], recptr->wstr);
		n->idx_ptr[0] = n->idx_ptr[1] = NULL;
		n->fill_cnt = 1;
		*root = n;	//��Ʈ�� ����Ű�� ��

		nd = (type_ptr_datanode)malloc(sizeof(datanode));	//�����ͳ�带 �ϳ� ���� ��
		nd->rec[0] = in_rec;
		nd->fill_cnt = 1;
		root_idx = *root;

		root_idx->data_ptr[0] = nd;	//��Ʈ �ε�������� ������[0]�� ����Ű�� ��
		root_idx->data_ptr[1] = NULL;	//��Ʈ �ε�������� ������[1] = NULL�� �ʱ�ȭ

		return split;
	}

	root_idx = *root;
	curr_idx = root_idx;
	strcpy(key, recptr->wstr);//Ű �� ����

	if (root_idx->data_ptr[1] == NULL) {	//Root�� Null�� �ƴ� ����� �ʹݺ� ����

		curr_data = root_idx->data_ptr[0];

		if (curr_data->fill_cnt < MAXK) {	//������ ��忡 ���ڸ��� �ִٸ�
			for (i = 0; i < curr_data->fill_cnt; i++) {
				if (strcmp(key, curr_data->rec[i].wstr) == 0) {
					return -1;
				}
				if (strcmp(key, curr_data->rec[i].wstr) < 0) {//�Էµ����Ͱ� curr�� �����͵麸�� �۴ٸ�
					for (j = curr_data->fill_cnt - 1; j >= i; j--) {//���������� ��ĭ�� push
						curr_data->rec[j + 1] = curr_data->rec[j];
					}
					//�Էµ����� ������ �ڸ��� �ֱ�
					curr_data->rec[i] = in_rec;
					curr_data->fill_cnt++;
					return split;
				}

			}
			if (i == curr_data->fill_cnt) {//curr�� �����͵麸�� ũ�ٸ�
				curr_data->rec[i] = in_rec;	//������ �ڸ��� �ֱ�
				curr_data->fill_cnt++;
				strcpy(root_idx->key[0], in_rec.wstr);
				return split;
			}
		}
		else {	//���ڸ��� ���� ���
			split++;
			strcpy(key, in_rec.wstr);
			for (k = 0; k < MAXK; k++) {	//key������ �������� ã��
				if (strcmp(key, curr_data->rec[k].wstr) < 0) //�� ã������ break
					break;
			}

			for (m = 0; m < k; m++) {	//key������ �������� bnode�� ���� �ֱ�
				bdnode.rec[m] = curr_data->rec[m];
			}

			//�� ����, �Է� ������ �ֱ�
			bdnode.rec[m] = in_rec;
			m++;

			//������ bnode�� �ֱ�
			for (; m < MAXK + 1; m++) {
				bdnode.rec[m] = curr_data->rec[m - 1];
			}

			for (i = 0; i < halfK + 1; i++) {	//���� ���� curr�� �־��ش�(�߰����ڵ� ����)
				curr_data->rec[i] = bdnode.rec[i];
			}
			curr_data->fill_cnt = halfK + 1;

			for (; i < MAXK; i++) {	//curr�� ������ ������ ����
				type_ptr_datanode *buff = &curr_data->rec[i];
				*buff = NULL;
				curr_data->rec[i].numpos = 0;
				buff = &curr_data->rec[i].pos;
				*buff = NULL;
			}

			//new��� ���� �� ������ �� ������ �ֱ�
			new_data = (type_ptr_datanode)malloc(sizeof(datanode));

			for (i = 0; i < halfK; i++) {
				new_data->rec[i] = bdnode.rec[i + halfK + 1];
			}
			new_data->fill_cnt = halfK;

			strcpy(root_idx->key[0], bdnode.rec[halfK].wstr);	//�߰����ڵ带 ��Ʈ �ε�������� KEY���� ����
			root_idx->data_ptr[1] = new_data;	//���� ���� ��带 �ε��� ����� data_ptr[1]�� ����
			curr_data->data_ptr = new_data;		//�� ����Ÿ ��峢�� ����
			new_data->data_ptr = NULL;		//���� ���� ����� link�� NULL
		}

	}
	else if (root_idx->data_ptr[1] != NULL) {	//��������� ���(�ʱ� ��Ȳ�� �ƴ� ���)

		while (1) {	//�����Ͱ� �� ����Ÿ��带 ã�´�

			for (i = 0; i < curr_idx->fill_cnt; i++) {

				if (strcmp(key, curr_idx->key[i]) == 0) {
					return -1;
				}
				if (strcmp(key, curr_idx->key[i]) < 0) {//�Էµ����Ͱ� curr�� � �����ͺ��� �۴ٸ�
					P = curr_idx->idx_ptr[i];	//�� �������� ���� �ڽ������͸� P�� ����
					break;
				}
			}

			if (i == curr_idx->fill_cnt) {//curr�� ���� ū �����ͺ��� ũ�ٸ�
				P = curr_idx->idx_ptr[i];	//�� �������� ������ �ڽ� �����͸� P�� ����
			}

			if (curr_idx->data_ptr[0] != NULL) {	//������ ��� �ٷ� ���� �ε��� ��带 ã��
				P = NULL;
			}
			if (P) {	//�ڽ��� ����
				top++;
				stack[top] = curr_idx;
				curr_idx = P;
				continue;
			}
			else //����Ÿ����� �ٷ� �� index��忡�� ����Ÿ��带 ã��( i�� �����ͳ�带 ����Ű�� �ε��� ���� ������ ����)
			{
				curr_data = curr_idx->data_ptr[i];	//����Ÿ��带 ����Ű�� �����͸� curr_data�� �Ű���

				break;

			}

		}

		while (1) {	//curr_data�� ���� ������ ����Ÿ 

			if (curr_data->fill_cnt != MAXK) {	//������ ��尡 �� ���� �ʾ��� ���

				for (i = 0; i < curr_data->fill_cnt; i++) {

					if (strcmp(key, curr_data->rec[i].wstr) == 0) {
						return -1;
					}
					if (strcmp(key, curr_data->rec[i].wstr) < 0) {//�Էµ����Ͱ� ������ ����� �����͵麸�� �۴ٸ�
						for (j = curr_data->fill_cnt - 1; j >= i; j--) {//���������� ��ĭ�� push
							curr_data->rec[j + 1] = curr_data->rec[j];
						}
						//�Էµ����� ������ �ڸ��� �ֱ�
						curr_data->rec[i] = in_rec;
						curr_data->fill_cnt++;
						return split;
					}
				}
				if (i == curr_data->fill_cnt) {//������ ����� �����͵麸�� ũ�ٸ�
					curr_data->rec[i] = in_rec;	//������ �ڸ��� �ֱ�
					curr_data->fill_cnt++;
					return split;
				}
			}
			else {	//�����ͳ�尡 �� á�� ���
				split++;
				type_ptr_datanode ptr_new_data;
				char mid_key[100];	//���忡�� �߰����ڵ��� key

				for (i = 0; i < curr_data->fill_cnt; i++) {//�ߺ��˻�
					if (strcmp(key, curr_data->rec[i].wstr) == 0) {
						return -1;
					}
				}

				for (k = 0; k < MAXK; k++) {	//key������ �������� ã��
					if (strcmp(key, curr_data->rec[k].wstr) < 0) //�� ã������ break
						break;
				}

				for (m = 0; m < k; m++) {	//key������ �������� bnode�� ���� �ֱ�
					bdnode.rec[m] = curr_data->rec[m];
				}

				//�� ����, �Է� ������ �ֱ�
				bdnode.rec[m] = in_rec;
				m++;

				//������ bnode�� �ֱ�
				for (; m < MAXK + 1; m++) {
					bdnode.rec[m] = curr_data->rec[m - 1];
				}

				for (i = 0; i < halfK + 1; i++) {	//���� ���� ���� �����ͳ�忡 �־��ش�(�߰����ڵ� ����)
					curr_data->rec[i] = bdnode.rec[i];
				}
				curr_data->fill_cnt = halfK + 1;

				for (; i < MAXK; i++) {	//���� �����ͳ���� ������ ������ ����
					type_ptr_datanode *buff = &curr_data->rec[i];
					*buff = NULL;
					curr_data->rec[i].numpos = 0;
					buff = &curr_data->rec[i].pos;
					*buff = NULL;
				}

				//new������ ��� ���� �� ������ �� ������ �ֱ�
				new_data = (type_ptr_datanode)malloc(sizeof(datanode));

				for (i = 0; i < halfK; i++) {
					new_data->rec[i] = bdnode.rec[i + halfK + 1];
				}
				new_data->fill_cnt = halfK;
				curr_data->data_ptr = new_data;

				strcpy(mid_key, bdnode.rec[halfK].wstr);
				ptr_new_data = new_data;

				//���� ���⼭ curr_idx�� ���� mid_key���� ptr_new_data�� ���� �ε��� ����̴�.

				if (curr_idx->fill_cnt < MAXK) {//curr_idx ��忡 �� �ڸ��� �ִ� ���
					int x;
					for (x = 0; x < curr_idx->fill_cnt; x++) {
						if (strcmp(mid_key, curr_idx->key[x]) < 0) {
							for (j = curr_idx->fill_cnt - 1; j >= x; j--) {//���������� ��ĭ�� push
								strcpy(curr_idx->key[j + 1], curr_idx->key[j]);
								curr_idx->data_ptr[j + 2] = curr_idx->data_ptr[j + 1];
							}
							//�Էµ����� ������ �ڸ��� �ֱ�
							strcpy(curr_idx->key[x], mid_key);
							curr_idx->data_ptr[x + 1] = ptr_new_data;
							curr_idx->fill_cnt++;
							return split;


						}
					}
					if (x == curr_idx->fill_cnt) {//curr�� �����͵麸�� ũ�ٸ�
						strcpy(curr_idx->key[x], mid_key);	//������ �ڸ��� �ֱ�
						curr_idx->data_ptr[x + 1] = ptr_new_data;
						curr_idx->fill_cnt++;
						return split;
					}


				}
				else {//�� �ڸ��� ���� ���
					split++;
					for (k = 0; k < MAXK; k++) {	//key������ �������� ã��
						if (strcmp(mid_key, curr_idx->key[k]) < 0) //�� ã������ break
							break;
					}

					binode.data_ptr[0] = curr_idx->data_ptr[0];

					for (m = 0; m < k; m++) {	//key������ �������� bnode�� ���� �ֱ�
						binode.data_ptr[m + 1] = curr_idx->data_ptr[m + 1];
						strcpy(binode.key[m], curr_idx->key[m]);
					}

					//�� ����, �Է� ������ �ֱ�
					binode.data_ptr[m + 1] = ptr_new_data;
					strcpy(binode.key[m], mid_key);
					m++;

					//������ bnode�� �ֱ�
					for (; m < MAXK + 1; m++) {
						binode.data_ptr[m + 1] = curr_idx->data_ptr[m];
						strcpy(binode.key[m], curr_idx->key[m - 1]);
					}

					for (i = 0; i < halfK; i++) {	//���� ���� curr�� �־��ش�(  �߰�key������)
						curr_idx->data_ptr[i] = binode.data_ptr[i];
						strcpy(curr_idx->key[i], binode.key[i]);
					}
					curr_idx->fill_cnt = halfK;
					curr_idx->data_ptr[i] = binode.data_ptr[i];

					for (; i < MAXK; i++) {	//curr�� ������ ������ ����
						curr_idx->data_ptr[i + 1] = NULL;
						type_ptr_idxnode *buff = &curr_idx->key[i];
						*buff = NULL;
					}

					//new��� ���� �� ������ �� ������ �ֱ�
					new_idx = (type_ptr_idxnode)malloc(sizeof(idxnode));


					for (i = 0; i < halfK; i++) {

						new_idx->data_ptr[i] = binode.data_ptr[i + halfK + 1];
						strcpy(new_idx->key[i], binode.key[i + halfK + 1]);
					}
					new_idx->data_ptr[i] = binode.data_ptr[i + halfK + 1];
					new_idx->fill_cnt = halfK;


					//��� ������
					P = new_idx;
					strcpy(mid_key, binode.key[halfK]);

					if (top >= 0) {//�θ� ��尡 �����Ѵٸ�
						int x;
						curr_idx = stack[top];
						top--;
						while (1) {
							if (curr_idx->fill_cnt != MAXK) {	//�θ� �ε��� ��尡 �� ���� �ʾ��� ���
								for (x = 0; x < curr_idx->fill_cnt; x++) {
									if (strcmp(mid_key, curr_idx->key[x]) < 0) {
										for (j = curr_idx->fill_cnt - 1; j >= x; j--) {//���������� ��ĭ�� push
											strcpy(curr_idx->key[j + 1], curr_idx->key[j]);
											curr_idx->idx_ptr[j + 2] = curr_idx->idx_ptr[j + 1];
										}
										//�Էµ����� ������ �ڸ��� �ֱ�
										strcpy(curr_idx->key[x], mid_key);
										curr_idx->data_ptr[0] = NULL;
										curr_idx->idx_ptr[x + 1] = P;
										curr_idx->fill_cnt++;
										return split;


									}
								}
								if (x == curr_idx->fill_cnt) {//curr�� �����͵麸�� ũ�ٸ�
									strcpy(curr_idx->key[x], mid_key);	//������ �ڸ��� �ֱ�
									curr_idx->data_ptr[0] = NULL;
									curr_idx->idx_ptr[x + 1] = P;
									curr_idx->fill_cnt++;
									return split;
								}

							}

							else {//�� á�� ���
								split++;
								for (k = 0; k < MAXK; k++) {	//key������ �������� ã��
									if (strcmp(mid_key, curr_idx->key[k]) < 0) //�� ã������ break
										break;
								}

								strcpy(binode.key[0], curr_idx->idx_ptr[0]);
								binode.idx_ptr[0] = curr_idx->idx_ptr[0];
								for (m = 0; m < k; m++) {	//key������ �������� bnode�� ���� �ֱ�
									binode.idx_ptr[m + 1] = curr_idx->idx_ptr[m + 1];
									strcpy(binode.key[m], curr_idx->key[m]);
								}

								//�� ����, �Է� ������ �ֱ�
								binode.idx_ptr[m + 1] = P;
								strcpy(binode.key[m], mid_key);
								m++;

								//������ bnode�� �ֱ�
								for (; m < MAXK + 1; m++) {
									binode.idx_ptr[m + 1] = curr_idx->idx_ptr[m];
									strcpy(binode.key[m], curr_idx->key[m - 1]);
								}

								for (i = 0; i < halfK; i++) {	//���� ���� curr�� �־��ش�
									curr_idx->idx_ptr[i] = binode.idx_ptr[i];
									strcpy(curr_idx->key[i], binode.key[i]);
								}
								curr_idx->fill_cnt = halfK;
								curr_idx->idx_ptr[i] = binode.idx_ptr[i];

								for (; i < MAXK; i++) {	//curr�� ������ ������ ����
									curr_idx->idx_ptr[i + 1] = NULL;
									type_ptr_idxnode *buff = &curr_idx->key[i];
									*buff = NULL;
								}

								//new��� ���� �� ������ �� ������ �ֱ�
								new_idx = (type_ptr_idxnode)malloc(sizeof(idxnode));


								for (i = 0; i < halfK; i++) {

									new_idx->idx_ptr[i] = binode.idx_ptr[i + halfK + 1];
									strcpy(new_idx->key[i], binode.key[i + halfK + 1]);
								}
								new_idx->data_ptr[0] = NULL;
								new_idx->idx_ptr[i] = binode.idx_ptr[i + halfK + 1];
								new_idx->fill_cnt = halfK;

								//��� ������
								P = new_idx;
								strcpy(mid_key, binode.key[halfK]);

								if (top >= 0) {//�θ� ��尡 �����Ѵٸ�
									curr_idx = stack[top];
									top--;
									continue;
								}
								else {//�θ� ��尡 �������� �ʴ´ٸ�
									rnew = (type_ptr_idxnode)malloc(sizeof(idxnode));
									rnew->idx_ptr[0] = curr_idx;
									strcpy(rnew->key[0], mid_key);
									rnew->idx_ptr[1] = P;
									rnew->fill_cnt = 1;
									rnew->data_ptr[0] = NULL;
									*root = rnew;	//�θ� ��尡 �������� �ʴ´ٸ� �� �� ��尡 ��Ʈ�� ��
									return split;
								}
							}
						}
					}
					else {//�θ� ��尡 �������� �ʴ´ٸ�
						rnew = (type_ptr_idxnode)malloc(sizeof(idxnode));
						rnew->idx_ptr[0] = curr_idx;
						strcpy(rnew->key[0], mid_key);
						rnew->idx_ptr[1] = P;
						rnew->fill_cnt = 1;
						rnew->data_ptr[0] = NULL;
						*root = rnew;	//�θ� ��尡 �������� �ʴ´ٸ� �� �� ��尡 ��Ʈ�� ��
						return split;
					}

				}

			}
		}
	}
}

int B_plus_tree_Search(char word[100], type_ptr_idxnode root) {	//root����� level�� 0�̶��ϰ� �� �Ʒ����� 1�� ����

	char key[100];
	int i;
	int top = -1;
	int level = 0;
	int check_have_data = 0;	//ã�� �����Ͱ� �ִ��� Ȯ���ϴ� ���� ( 1�̸� �ְ� 0�̸� ���� )
	type_ptr_idxnode stack[50];	//�θ� ������
	type_ptr_idxnode curr_idx;	//���� ���
	type_ptr_datanode curr_data;
	type_ptr_idxnode P;	//������ ������
	strcpy(key, word);//Ű �� ����
	curr_idx = root;


	while (1) {	//�����Ͱ� �� ����Ÿ��带 ã�´�

		for (i = 0; i < curr_idx->fill_cnt; i++) {

			if (strcmp(key, curr_idx->key[i]) <= 0) {//�Էµ����Ͱ� curr�� � �����ͺ��� �۴ٸ�
				P = curr_idx->idx_ptr[i];	//�� �������� ���� �ڽ������͸� P�� ����
				break;
			}
		}

		if (i == curr_idx->fill_cnt) {//curr�� ���� ū �����ͺ��� ũ�ٸ�
			P = curr_idx->idx_ptr[i];	//�� �������� ������ �ڽ� �����͸� P�� ����
		}

		if (curr_idx->data_ptr[0] != NULL) {	//������ ��� �ٷ� ���� �ε��� ��带 ã��
			P = NULL;
		}
		if (P) {	//�ڽ��� ����
			top++;
			level = top + 1;
			stack[top] = curr_idx;
			curr_idx = P;
			continue;
		}
		else //����Ÿ����� �ٷ� �� index��忡�� ����Ÿ��带 ã��( i�� �����ͳ�带 ����Ű�� �ε��� ���� ������ ����)
		{
			curr_data = curr_idx->data_ptr[i];	//����Ÿ��带 ����Ű�� �����͸� curr_data�� �Ű���

			break;

		}

	}

	for (int j = 0; j < curr_data->fill_cnt; j++) {
		if (strcmp(key, curr_data->rec[j].wstr) == 0) {
			printf("�ش� �̸��� LEVEL %d�� �ִ� ���ڵ� �� %d��°�� �ֽ��ϴ�.\n", level, j + 1);
			return 0;
		}
	}
	printf("ã�� ������ ���������ʽ��ϴ�...\n");
	return -1;


}

int B_plus_tree_Deletion(char word[100], type_ptr_idxnode *root) {

	char key[100];

	int i, j, k, m;
	int top = -1;
	int retri = 0;	//��й� Ƚ��
	int merge = 0;	//�պ� Ƚ��
	int middle = 0; //bignode�� �� ���ڵ� ���� ��
	int parent_index;
	int exist_data = 0;	//1�̸� ���� 0�̸� �������� ����

	type_ptr_idxnode stack[50];	//�θ� ������

	type_ptr_idxnode curr_idx;	//���� ���
	type_ptr_datanode curr_data;

	type_ptr_idxnode parent_idx;	//balancing���� sibling ���θ� �˱����� �θ���
	type_ptr_datanode parent_data;

	type_ptr_idxnode left_sibling_idx;	//���� ����
	type_ptr_datanode left_sibling_data;

	type_ptr_idxnode right_sibling_idx;	//������ ����
	type_ptr_datanode right_sibling_data;

	type_ptr_idxnode P;	//������ ������
	type_ptr_idxnode * ptr;	//��� ���� ������

	idx_two_bignode tibnode;
	data_two_bignode tdbnode;

	if (!*root) {
		printf("�����Ͱ� �ϳ��� �������� �ʽ��ϴ�....\n");
		return 1;
	}

	curr_idx = *root;

	strcpy(key, word);

	while (1) {	//������ �����Ͱ� �ִ� ����Ÿ��带 ã�´�

		for (i = 0; i < curr_idx->fill_cnt; i++) {
			if (strcmp(key, curr_idx->key[i]) <= 0) {//�Էµ����Ͱ� curr�� � �����ͺ��� �۴ٸ�
				P = curr_idx->idx_ptr[i];	//�� �������� ���� �ڽ������͸� P�� ����
				break;
			}
		}

		if (i == curr_idx->fill_cnt) {//curr�� ���� ū �����ͺ��� ũ�ٸ�
			P = curr_idx->idx_ptr[i];	//�� �������� ������ �ڽ� �����͸� P�� ����
		}

		if (P) {	//�ڽ��� ����
			top++;
			stack[top] = curr_idx;
			curr_idx = P;
			continue;
		}
		else //����Ÿ����� �ٷ� �� index��忡�� ����Ÿ��带 ã��( i�� �����ͳ�带 ����Ű�� �ε��� ���� ������ ����)
		{
			curr_data = curr_idx->data_ptr[i];	//����Ÿ��带 ����Ű�� �����͸� curr_data�� �Ű���
			parent_index = i;
			break;

		}
	}

	for (int j = 0; j < curr_data->fill_cnt; j++) {
		if (strcmp(key, curr_data->rec[j].wstr) == 0) {
			//���ڵ� ����
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

		printf("�����Ϸ��� ���� ���������ʽ��ϴ�...\n");
		return;
	}
	for (j = 0; j < curr_data->fill_cnt; j++) {
		curr_data->rec[j] = curr_data->rec[j + 1];
	}

	if (top == -1) {//���� ��尡 root�����
		ptr = &curr_data->rec[0];
		if (!*ptr) {//��Ʈ����� ���ڵ尡 ���������ʴ´ٸ�
			free(curr_data);
			free(curr_idx);
		}
		else {//��Ʈ����� ���ڵ尡 ����							
			printf("������ �����Ͽ����ϴ�!! ��й�� %d��, �պ��� %d���Ͽ����ϴ�\n", retri, merge);
			return 0;
		}
	}

	while (1) {
		if (curr_data->fill_cnt < halfK) {	//��尡 balancing�� ��߳�

											//�θ�� �ö� ������ ������ ���� ������ �ִ��� Ȯ�� (������ ������ ��ȣ)

			parent_idx = curr_idx;//parent_idx�� ���� �θ� ���( �� �ٷ� �� �ε��� ���) ��


								  //parentindex�� parent(curr_idx)������ curr_data��带 ����Ű�� ������ �ε��� 
			if (parent_index != 0) {
				left_sibling_data = parent_idx->data_ptr[parent_index - 1];
			}
			if (parent_index != MAXK) {
				right_sibling_data = parent_idx->data_ptr[parent_index + 1];
			}

			if (right_sibling_data&&right_sibling_data->fill_cnt > halfK) {	//������ �������� ������ ( ��й谡 ���� )

				for (k = 0; k < curr_data->fill_cnt; k++) {
					tdbnode.rec[k] = curr_data->rec[k];
				}

				for (m = 0; m < right_sibling_data->fill_cnt; k++, m++) {
					tdbnode.rec[k] = right_sibling_data->rec[m];
				}

				//k�� two_bignode �� ���ڵ� ���� �������

				middle = k / 2;
				//two_bignode���� middle��° ���ڵ带 �������� ������ curr�� �ִ´�.
				for (i = 0; i <= middle; i++) {
					curr_data->rec[i] = tdbnode.rec[i];
				}
				curr_data->fill_cnt = middle + 1;

				//parent���ٰ� ��� ���� halfK��° ���ڵ� ���� �ִ´�.
				strcpy(parent_idx->key[parent_index], tdbnode.rec[halfK].wstr);

				//������ �ڽĿ� ������ two_bignode������ �ִ´�.
				for (m = 0; i < k; m++, i++) {

					right_sibling_data->rec[m] = tdbnode.rec[i];
				}
				right_sibling_idx->fill_cnt = k - (middle + 1);	//two_bignode�� �� ���ڵ� ������ curr�� ���� �ݰ� parent�� ���� ���� ������ ������ ��

				retri++;

				printf("������ �����Ͽ����ϴ�!! ��й�� %d��, �պ��� %d���Ͽ����ϴ�\n", retri, merge);
				return 0;
			}

			else if (left_sibling_data&&left_sibling_data->fill_cnt > halfK) {	//���� �������� ������ ( ��й谡 ���� )


																				//tbnode�� ���� ���� �ڽĳ���� ���� �ִ´�
				for (k = 0; k < left_sibling_data->fill_cnt; k++) {
					tdbnode.rec[k] = left_sibling_data->rec[k];
				}

				//�� ����, curr�� ������ two_bignode�� �ִ´�
				for (m = 0; m < curr_data->fill_cnt; k++, m++) {
					tdbnode.rec[k] = curr_data->rec[m];
				}

				//k�� two_bignode �� ���ڵ� ���� �������
				middle = k / 2;

				//two_bignode���� middle��° ���ڵ带 �������� ������ curr�� �ִ´�. 		
				for (i = 0; i <= middle; i++) {
					left_sibling_data->rec[i] = tdbnode.rec[i];
				}
				left_sibling_data->fill_cnt = middle + 1;

				//parent���ٰ� ��� ���� middle��° ���ڵ� ���� �ִ´�.
				strcpy(parent_idx->key[parent_index], tdbnode.rec[middle].wstr);

				//curr�� ������ two_bignode������ �ִ´�.
				for (m = 0; i < k; m++, i++) {
					curr_data->rec[m] = tdbnode.rec[i];
				}
				curr_data->fill_cnt = k - (middle + 1);	//two_bignode�� �� ���ڵ� ������ ���� ������ ���� �ݰ� parent�� ���� ���� ������ ������ ��

				retri++;

				printf("������ �����Ͽ����ϴ�!! ��й�� %d��, �պ��� %d���Ͽ����ϴ�\n", retri, merge);

				return 0;
			}

			else {	//�պ��� �ؾ��Ѵ�. ( ��й谡 �Ұ��� )

				int next_data = curr_data->fill_cnt;	//curr�� ���ִ� ���ڵ� ������ ���� �ε���

				if (right_sibling_data) {	//������ ������ �ִٸ�

											//������ ������ ������ curr�� ������ �κп� �ִ´�.
					for (i = 0; i < right_sibling_data->fill_cnt; next_data++, i++) {
						curr_data->rec[next_data] = right_sibling_data->rec[i];
					}

					//������ ���� ��� ����
					free(right_sibling_data);

					//parent���� curr�� ������ ���� ���̿� �ִ� ���ڵ带 �������� �������� ��ĭ�� shift
					for (; j + 1 < parent_idx->fill_cnt; j++) {
						parent_idx->data_ptr[j + 1] = parent_idx->data_ptr[j + 2];
						strcpy(parent_idx->key[j], parent_idx->key[j + 1]);
					}

					curr_data->data_ptr = parent_idx->data_ptr[parent_index + 1];

					//��ĭ �� �Ű�ٸ� ���������� �ű� ���ڵ��� ���� ��ġ ���ڵ�� ������ �ʱ�ȭ
					ptr = &parent_idx->key[j];
					*ptr = NULL;

					parent_idx->data_ptr[j + 1] = NULL;

					parent_idx->fill_cnt--;

					curr_idx = parent_idx;	//curr�� �θ� �����͸� �ְ� �ٽ� �ݺ�

					merge++;

					//�̹����� �ε��� ��尡 �뷱���� �´����� ������
					while (1) {
						if (curr_idx->fill_cnt < halfK) {	//��尡 balancing�� ��߳�

															//�θ�� �ö� ������ ������ ���� ������ �ִ��� Ȯ�� (������ ������ ��ȣ)
							parent_idx = stack[top];
							top--;

							for (j = 0; j < parent_idx->fill_cnt; j++) {
								if (parent_idx->idx_ptr[j] == curr_idx) {
									break;
								}
							}

							//j�� parent������ curr��� ������

							if (j != 0) {
								left_sibling_idx = parent_idx->idx_ptr[j - 1];
							}
							if (j != MAXK) {
								right_sibling_idx = parent_idx->idx_ptr[j + 1];
							}

							if (right_sibling_idx&&right_sibling_idx->fill_cnt > halfK) {	//������ �������� ������ ( ��й谡 ���� )

																							//tbnode�� ���� curr���� �ִ´�
								tibnode.idx_ptr[0] = curr_idx->idx_ptr[0];
								for (k = 0; k < curr_idx->fill_cnt; k++) {
									tibnode.idx_ptr[k + 1] = curr_idx->idx_ptr[k + 1];
									strcpy(tibnode.key[k], curr_idx->key[k]);
								}

								//�� ����, curr�� ������ ���� ������ �θ��� ���ڵ� ���� �ִ´�.
								strcpy(tibnode.key[k], parent_idx->key[j]);
								k++;

								tibnode.idx_ptr[k] = right_sibling_idx->idx_ptr[0];
								for (m = 0; m < right_sibling_idx->fill_cnt; k++, m++) {
									tibnode.idx_ptr[k + 1] = right_sibling_idx->idx_ptr[m + 1];
									strcpy(tibnode.key[k], right_sibling_idx->key[m]);
								}

								//k�� two_bignode �� ���ڵ� ���� �������

								middle = k / 2;
								//two_bignode���� middle��° ���ڵ带 �������� ������ curr�� �ִ´�.
								for (i = 0; i < middle; i++) {
									curr_idx->idx_ptr[i] = tibnode.idx_ptr[i];
									strcpy(curr_idx->key[i], tibnode.key[i]);
								}
								curr_idx->idx_ptr[i] = tibnode.idx_ptr[i];
								curr_idx->fill_cnt = middle;

								//parent���ٰ� ��� ���� halfK��° ���ڵ� ���� �ִ´�.
								strcpy(parent_idx->key[j], tibnode.key[halfK]);
								i++;

								//������ �ڽĿ� ������ two_bignode������ �ִ´�.
								for (m = 0; i < k; m++, i++) {
									right_sibling_idx->idx_ptr[m] = tibnode.idx_ptr[i];
									strcpy(right_sibling_idx->key[m], tibnode.key[i]);
								}
								right_sibling_idx->idx_ptr[m] = tibnode.idx_ptr[i];
								right_sibling_idx->fill_cnt = k - (middle + 1);	//two_bignode�� �� ���ڵ� ������ curr�� ���� �ݰ� parent�� ���� ���� ������ ������ ��

								retri++;

								printf("������ �����Ͽ����ϴ�!! ��й�� %d��, �պ��� %d���Ͽ����ϴ�\n", retri, merge);
								return 0;
							}
							else if (left_sibling_idx&&left_sibling_idx->fill_cnt > halfK) {	//���� �������� ������ ( ��й谡 ���� )


																								//tbnode�� ���� ���� �ڽĳ���� ���� �ִ´�
								tibnode.idx_ptr[0] = left_sibling_idx->idx_ptr[0];
								for (k = 0; k < left_sibling_idx->fill_cnt; k++) {
									tibnode.idx_ptr[k + 1] = left_sibling_idx->idx_ptr[k + 1];
									strcpy(tibnode.key[k], left_sibling_idx->key[k]);
								}

								strcpy(tibnode.key[k], parent_idx->key[j - 1]);	//�� ����, curr�� ���� ���� ������ �θ��� ���ڵ� ���� �ִ´�.
								k++;

								//�� ����, curr�� ������ two_bignode�� �ִ´�
								tibnode.idx_ptr[k] = curr_idx->idx_ptr[0];
								for (m = 0; m < curr_idx->fill_cnt; k++, m++) {
									tibnode.idx_ptr[k + 1] = curr_idx->idx_ptr[m + 1];
									strcpy(tibnode.key[k], curr_idx->key[m]);
								}

								//k�� two_bignode �� ���ڵ� ���� �������
								middle = k / 2;

								//two_bignode���� middle��° ���ڵ带 �������� ������ curr�� �ִ´�. 		
								for (i = 0; i < middle; i++) {
									left_sibling_idx->idx_ptr[i] = tibnode.idx_ptr[i];
									strcpy(left_sibling_idx->key[i], tibnode.key[i]);
								}
								left_sibling_idx->idx_ptr[i] = tibnode.idx_ptr[i];
								left_sibling_idx->fill_cnt = middle;

								//parent���ٰ� ��� ���� middle��° ���ڵ� ���� �ִ´�.
								strcpy(parent_idx->key[j], tibnode.key[middle]);

								i++;

								//curr�� ������ two_bignode������ �ִ´�.
								for (m = 0; i < k; m++, i++) {
									curr_idx->idx_ptr[m] = tibnode.idx_ptr[i];
									strcpy(curr_idx->key[m], tibnode.key[i]);
								}
								curr_idx->idx_ptr[m] = tibnode.idx_ptr[i];
								curr_idx->fill_cnt = k - (middle + 1);	//two_bignode�� �� ���ڵ� ������ ���� ������ ���� �ݰ� parent�� ���� ���� ������ ������ ��

								retri++;

								printf("������ �����Ͽ����ϴ�!! ��й�� %d��, �պ��� %d���Ͽ����ϴ�\n", retri, merge);

								return 0;
							}
							else {	//�պ��� �ؾ��Ѵ�. ( ��й谡 �Ұ��� )

								int next = curr_idx->fill_cnt;	//curr�� ���ִ� ���ڵ� ������ ���� �ε���

								if (right_sibling_idx) {	//������ ������ �ִٸ�

															//curr�� ������ ���� ������ ���̿� �ִ� ���ڵ带 �ִ´�
									strcpy(curr_idx->key[next], parent_idx->key[j]);
									next++;

									//�� ����, ������ ������ ������ curr�� ������ �κп� �ִ´�.
									curr_idx->idx_ptr[next] = right_sibling_idx->idx_ptr[0];
									for (i = 0; i < right_sibling_idx->fill_cnt; next++, i++) {
										strcpy(curr_idx->key[next], right_sibling_idx->key[i]);
									}

									//������ ���� ��� ����
									free(right_sibling_idx);

									//parent���� curr�� ������ ���� ���̿� �ִ� ���ڵ带 �������� �������� ��ĭ�� shift
									for (; j + 1 < parent_idx->fill_cnt; j++) {
										strcpy(parent_idx->key[j], parent_idx->key[j + 1]);
										parent_idx->idx_ptr[j + 1] = parent_idx->idx_ptr[j + 2];
									}

									//��ĭ �� �Ű�ٸ� ���������� �ű� ���ڵ��� ���� ��ġ ���ڵ�� ������ �ʱ�ȭ
									ptr = &parent_idx->key[j];
									*ptr = NULL;
									parent_idx->idx_ptr[j + 1] = NULL;
									parent_idx->fill_cnt--;

									curr_idx = parent_idx;	//curr�� �θ� �����͸� �ְ� �ٽ� �ݺ�
									merge++;
									continue;

								}
								else {//���� ������ �պ�
									  //curr�� ������ ���� ������ ���ڵ��� curr�� ���� ���� ������ parent ���ڵ���� ��ģ ����ŭ ���������� shift
									for (i = 0; i < curr_idx->fill_cnt; i++) {
										curr_idx->idx_ptr[i + (left_sibling_idx->fill_cnt + 1)] = curr_idx->idx_ptr[i];
										strcpy(curr_idx->key[i + (left_sibling_idx->fill_cnt + 1)], curr_idx->key[i]);
									}
									curr_idx->idx_ptr[i + (left_sibling_idx->fill_cnt + 1)] = curr_idx->idx_ptr[i];

									//�� ����, curr�� ���� ���� ������ parent���ڵ带 �Ű��� curr�� ���� ���ʿ� �ִ´�.
									strcpy(curr_idx->key[left_sibling_idx->fill_cnt], parent_idx->key[j - 1]);

									//�׸��� ���� ������ ������ curr�� ó������ �ִ´�.
									for (i = 0; i < left_sibling_idx->fill_cnt; i++) {
										curr_idx->idx_ptr[i] = left_sibling_idx->idx_ptr[i];
										strcpy(curr_idx->key[i], left_sibling_idx->key[i]);
									}
									curr_idx->idx_ptr[i] = left_sibling_idx->idx_ptr[i];

									free(left_sibling_idx);	//���� ������� ����

															//parent���� curr�� ���� ���� ���̿� �ִ� ���ڵ带 �������� �������� ��ĭ�� shift
									for (; j < parent_idx->fill_cnt; j++) {
										strcpy(parent_idx->key[j - 1], parent_idx->key[j]);
										parent_idx->idx_ptr[j - 1] = parent_idx->idx_ptr[j];
									}
									parent_idx->idx_ptr[j - 1] = parent_idx->idx_ptr[j];

									//��ĭ �� �Ű�ٸ� ���������� �ű� ���ڵ��� ���� ��ġ ���ڵ�� ������ �ʱ�ȭ
									ptr = &parent_idx->key[j - 1];
									*ptr = NULL;
									parent_idx->idx_ptr[j] = NULL;
									parent_idx->fill_cnt--;

									curr_idx = parent_idx;  //curr�� �θ� �����͸� �ְ� �ٽ� �ݺ�
									merge++;
									continue;
								}

							}
						}
					}

				}
				else {//���� ������ �պ�
					  //curr�� ������ ���� ������ ���ڵ��� curr�� ���� ���� ������ parent ���ڵ���� ��ģ ����ŭ ���������� shift
					for (i = 0; i < curr_data->fill_cnt; i++) {
						curr_data->rec[i + (left_sibling_data->fill_cnt + 1)] = curr_data->rec[i];
					}

					//�׸��� ���� ������ ������ curr�� ó������ �ִ´�.
					for (i = 0; i < left_sibling_data->fill_cnt; i++) {
						curr_data->rec[i] = left_sibling_data->rec[i];
					}

					free(left_sibling_data);	//���� ������� ����

												//parent���� curr�� ���� ���� ���̿� �ִ� ���ڵ带 �������� �������� ��ĭ�� shift
					for (; j < parent_idx->fill_cnt; j++) {
						strcpy(parent_idx->key[j - 1], parent_idx->key[j]);
						parent_idx->data_ptr[j - 1] = parent_idx->data_ptr[j];
					}
					parent_idx->data_ptr[j - 1] = parent_idx->data_ptr[j];

					//��ĭ �� �Ű�ٸ� ���������� �ű� ���ڵ��� ���� ��ġ ���ڵ�� ������ �ʱ�ȭ
					ptr = &parent_idx->key[j - 1];
					*ptr = NULL;
					parent_idx->data_ptr[j] = NULL;
					parent_idx->fill_cnt--;

					curr_idx = parent_idx;  //curr�� �θ� �����͸� �ְ� �ٽ� �ݺ�
					merge++;

					//���� �ε��� ��尡 �뷱���� �´��� Ȯ���ؾ� ��
					while (1) {
						if (curr_idx->fill_cnt < halfK) {	//��尡 balancing�� ��߳�

															//�θ�� �ö� ������ ������ ���� ������ �ִ��� Ȯ�� (������ ������ ��ȣ)
							parent_idx = stack[top];
							top--;

							for (j = 0; j < parent_idx->fill_cnt; j++) {
								if (parent_idx->idx_ptr[j] == curr_idx) {
									break;
								}
							}

							//j�� parent������ curr��� ������

							if (j != 0) {
								left_sibling_idx = parent_idx->idx_ptr[j - 1];
							}
							if (j != MAXK) {
								right_sibling_idx = parent_idx->idx_ptr[j + 1];
							}

							if (right_sibling_idx&&right_sibling_idx->fill_cnt > halfK) {	//������ �������� ������ ( ��й谡 ���� )

																							//tbnode�� ���� curr���� �ִ´�
								tibnode.idx_ptr[0] = curr_idx->idx_ptr[0];
								for (k = 0; k < curr_idx->fill_cnt; k++) {
									tibnode.idx_ptr[k + 1] = curr_idx->idx_ptr[k + 1];
									strcpy(tibnode.key[k], curr_idx->key[k]);
								}

								//�� ����, curr�� ������ ���� ������ �θ��� ���ڵ� ���� �ִ´�.
								strcpy(tibnode.key[k], parent_idx->key[j]);
								k++;

								tibnode.idx_ptr[k] = right_sibling_idx->idx_ptr[0];
								for (m = 0; m < right_sibling_idx->fill_cnt; k++, m++) {
									tibnode.idx_ptr[k + 1] = right_sibling_idx->idx_ptr[m + 1];
									strcpy(tibnode.key[k], right_sibling_idx->key[m]);
								}

								//k�� two_bignode �� ���ڵ� ���� �������

								middle = k / 2;
								//two_bignode���� middle��° ���ڵ带 �������� ������ curr�� �ִ´�.
								for (i = 0; i < middle; i++) {
									curr_idx->idx_ptr[i] = tibnode.idx_ptr[i];
									strcpy(curr_idx->key[i], tibnode.key[i]);
								}
								curr_idx->idx_ptr[i] = tibnode.idx_ptr[i];
								curr_idx->fill_cnt = middle;

								//parent���ٰ� ��� ���� halfK��° ���ڵ� ���� �ִ´�.
								strcpy(parent_idx->key[j], tibnode.key[halfK]);
								i++;

								//������ �ڽĿ� ������ two_bignode������ �ִ´�.
								for (m = 0; i < k; m++, i++) {
									right_sibling_idx->idx_ptr[m] = tibnode.idx_ptr[i];
									strcpy(right_sibling_idx->key[m], tibnode.key[i]);
								}
								right_sibling_idx->idx_ptr[m] = tibnode.idx_ptr[i];
								right_sibling_idx->fill_cnt = k - (middle + 1);	//two_bignode�� �� ���ڵ� ������ curr�� ���� �ݰ� parent�� ���� ���� ������ ������ ��

								retri++;

								printf("������ �����Ͽ����ϴ�!! ��й�� %d��, �պ��� %d���Ͽ����ϴ�\n", retri, merge);
								return 0;
							}
							else if (left_sibling_idx&&left_sibling_idx->fill_cnt > halfK) {	//���� �������� ������ ( ��й谡 ���� )


																								//tbnode�� ���� ���� �ڽĳ���� ���� �ִ´�
								tibnode.idx_ptr[0] = left_sibling_idx->idx_ptr[0];
								for (k = 0; k < left_sibling_idx->fill_cnt; k++) {
									tibnode.idx_ptr[k + 1] = left_sibling_idx->idx_ptr[k + 1];
									strcpy(tibnode.key[k], left_sibling_idx->key[k]);
								}

								strcpy(tibnode.key[k], parent_idx->key[j - 1]);	//�� ����, curr�� ���� ���� ������ �θ��� ���ڵ� ���� �ִ´�.
								k++;

								//�� ����, curr�� ������ two_bignode�� �ִ´�
								tibnode.idx_ptr[k] = curr_idx->idx_ptr[0];
								for (m = 0; m < curr_idx->fill_cnt; k++, m++) {
									tibnode.idx_ptr[k + 1] = curr_idx->idx_ptr[m + 1];
									strcpy(tibnode.key[k], curr_idx->key[m]);
								}

								//k�� two_bignode �� ���ڵ� ���� �������
								middle = k / 2;

								//two_bignode���� middle��° ���ڵ带 �������� ������ curr�� �ִ´�. 		
								for (i = 0; i < middle; i++) {
									left_sibling_idx->idx_ptr[i] = tibnode.idx_ptr[i];
									strcpy(left_sibling_idx->key[i], tibnode.key[i]);
								}
								left_sibling_idx->idx_ptr[i] = tibnode.idx_ptr[i];
								left_sibling_idx->fill_cnt = middle;

								//parent���ٰ� ��� ���� middle��° ���ڵ� ���� �ִ´�.
								strcpy(parent_idx->key[j], tibnode.key[middle]);

								i++;

								//curr�� ������ two_bignode������ �ִ´�.
								for (m = 0; i < k; m++, i++) {
									curr_idx->idx_ptr[m] = tibnode.idx_ptr[i];
									strcpy(curr_idx->key[m], tibnode.key[i]);
								}
								curr_idx->idx_ptr[m] = tibnode.idx_ptr[i];
								curr_idx->fill_cnt = k - (middle + 1);	//two_bignode�� �� ���ڵ� ������ ���� ������ ���� �ݰ� parent�� ���� ���� ������ ������ ��

								retri++;

								printf("������ �����Ͽ����ϴ�!! ��й�� %d��, �պ��� %d���Ͽ����ϴ�\n", retri, merge);

								return 0;
							}
							else {	//�պ��� �ؾ��Ѵ�. ( ��й谡 �Ұ��� )

								int next = curr_idx->fill_cnt;	//curr�� ���ִ� ���ڵ� ������ ���� �ε���

								if (right_sibling_idx) {	//������ ������ �ִٸ�

															//curr�� ������ ���� ������ ���̿� �ִ� ���ڵ带 �ִ´�
									strcpy(curr_idx->key[next], parent_idx->key[j]);
									next++;

									//�� ����, ������ ������ ������ curr�� ������ �κп� �ִ´�.
									curr_idx->idx_ptr[next] = right_sibling_idx->idx_ptr[0];
									for (i = 0; i < right_sibling_idx->fill_cnt; next++, i++) {
										strcpy(curr_idx->key[next], right_sibling_idx->key[i]);
									}

									//������ ���� ��� ����
									free(right_sibling_idx);

									//parent���� curr�� ������ ���� ���̿� �ִ� ���ڵ带 �������� �������� ��ĭ�� shift
									for (; j + 1 < parent_idx->fill_cnt; j++) {
										strcpy(parent_idx->key[j], parent_idx->key[j + 1]);
										parent_idx->idx_ptr[j + 1] = parent_idx->idx_ptr[j + 2];
									}

									//��ĭ �� �Ű�ٸ� ���������� �ű� ���ڵ��� ���� ��ġ ���ڵ�� ������ �ʱ�ȭ
									ptr = &parent_idx->key[j];
									*ptr = NULL;
									parent_idx->idx_ptr[j + 1] = NULL;
									parent_idx->fill_cnt--;

									curr_idx = parent_idx;	//curr�� �θ� �����͸� �ְ� �ٽ� �ݺ�
									merge++;
									continue;

								}
								else {//���� ������ �պ�
									  //curr�� ������ ���� ������ ���ڵ��� curr�� ���� ���� ������ parent ���ڵ���� ��ģ ����ŭ ���������� shift
									for (i = 0; i < curr_idx->fill_cnt; i++) {
										curr_idx->idx_ptr[i + (left_sibling_idx->fill_cnt + 1)] = curr_idx->idx_ptr[i];
										strcpy(curr_idx->key[i + (left_sibling_idx->fill_cnt + 1)], curr_idx->key[i]);
									}
									curr_idx->idx_ptr[i + (left_sibling_idx->fill_cnt + 1)] = curr_idx->idx_ptr[i];

									//�� ����, curr�� ���� ���� ������ parent���ڵ带 �Ű��� curr�� ���� ���ʿ� �ִ´�.
									strcpy(curr_idx->key[left_sibling_idx->fill_cnt], parent_idx->key[j - 1]);

									//�׸��� ���� ������ ������ curr�� ó������ �ִ´�.
									for (i = 0; i < left_sibling_idx->fill_cnt; i++) {
										curr_idx->idx_ptr[i] = left_sibling_idx->idx_ptr[i];
										strcpy(curr_idx->key[i], left_sibling_idx->key[i]);
									}
									curr_idx->idx_ptr[i] = left_sibling_idx->idx_ptr[i];

									free(left_sibling_idx);	//���� ������� ����

															//parent���� curr�� ���� ���� ���̿� �ִ� ���ڵ带 �������� �������� ��ĭ�� shift
									for (; j < parent_idx->fill_cnt; j++) {
										strcpy(parent_idx->key[j - 1], parent_idx->key[j]);
										parent_idx->idx_ptr[j - 1] = parent_idx->idx_ptr[j];
									}
									parent_idx->idx_ptr[j - 1] = parent_idx->idx_ptr[j];

									//��ĭ �� �Ű�ٸ� ���������� �ű� ���ڵ��� ���� ��ġ ���ڵ�� ������ �ʱ�ȭ
									ptr = &parent_idx->key[j - 1];
									*ptr = NULL;
									parent_idx->idx_ptr[j] = NULL;
									parent_idx->fill_cnt--;

									curr_idx = parent_idx;  //curr�� �θ� �����͸� �ְ� �ٽ� �ݺ�
									merge++;
									continue;
								}

							}

						}
						else {	//balancing�� ����

							printf("������ �����Ͽ����ϴ�!! ��й�� %d��, �պ��� %d���Ͽ����ϴ�\n", retri, merge);
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
	int on[100];	//�θ��� i �����( �θ� ��� �ڽı��� Ȯ���ߴ��� üũ )
	int top = -1;	//���� ����� level root�� -1 �ڽ����� ������ ���� 1�� +

	type_ptr_idxnode stack[50];	//�θ� ������
	type_ptr_idxnode idx_curr;	//���� ���
	type_ptr_idxnode P;	//������ ������
	type_ptr_datanode data_curr;	//���� ���
	if (!root) {
		printf("�����Ͱ� �ϳ��� �������� �ʽ��ϴ�....\n");
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
	printf("��¿Ϸ��߽��ϴ�\n");
	fclose(fp);


}

int B_plus_tree_range_search(char data1[100], char data2[100], type_ptr_idxnode root) {
	char key1[100];//data1�� ���� Ű
	char key2[100];//data2�� ���� Ű
	char key_buff[100];//�� ������ ũ�⿡ ���� �� �� �ϳ��� Ű ���� �־�� ����
	int check_who=0;	//1�̸� data1��ũ�� 2�̸� data2�� ŭ
	int i;
	int find = 0;//data2�� ã������ 1 �ƴϸ� 0
	int top = -1;
	int level = 0;
	int check_word1=0;//data1�� b+tree���� �־����� Ȯ��
	int check_word2=0;//data2�� b+tree���� �־����� Ȯ��
	int check_have_data = 0;	//ã�� �����Ͱ� �ִ��� Ȯ���ϴ� ���� ( 1�̸� �ְ� 0�̸� ���� )
	FILE * fp = fopen("amongData.txt", "w");
	type_ptr_idxnode stack[50];	//�θ� ������
	type_ptr_idxnode curr_idx;	//���� ���
	type_ptr_datanode curr_data;
	type_ptr_datanode curr_data_word1;
	type_ptr_datanode curr_data_word2;
	type_ptr_idxnode P;	//������ ������
	strcpy(key1, data1);//Ű �� ����
	curr_idx = root;

	if (!root) {
		printf("�����Ͱ� �ϳ��� �������� �ʽ��ϴ�....\n");
		return 1;
	}
	while (1) {	//ù��° word�� �ִ� ����Ÿ��带 ã�´�

		for (i = 0; i < curr_idx->fill_cnt; i++) {

			if (strcmp(key1, curr_idx->key[i]) <= 0) {//�Էµ����Ͱ� curr�� � �����ͺ��� �۴ٸ�
				if (strcmp(key1, curr_idx->key[i]) == 0)
					check_word1 = 1;
				P = curr_idx->idx_ptr[i];	//�� �������� ���� �ڽ������͸� P�� ����
				break;
			}
		}

		if (i == curr_idx->fill_cnt) {//curr�� ���� ū �����ͺ��� ũ�ٸ�
			P = curr_idx->idx_ptr[i];	//�� �������� ������ �ڽ� �����͸� P�� ����
		}

		if (curr_idx->data_ptr[0] != NULL) {	//������ ��� �ٷ� ���� �ε��� ��带 ã��
			P = NULL;
		}
		if (P) {	//�ڽ��� ����
			top++;
			level = top + 1;
			stack[top] = curr_idx;
			curr_idx = P;
			continue;
		}
		else //word1�� �ִ� ����Ÿ��带 ã��( i�� �����ͳ�带 ����Ű�� �ε��� ���� ������ ����)
		{
			curr_data_word1 = curr_idx->data_ptr[i];	//����Ÿ��带 ����Ű�� �����͸� curr_data_word1�� �Ű���

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
		printf("ã�� ������ ���������ʽ��ϴ�...\n");
		return -1;
	}


	check_have_data = 0;	//�ʱ�ȭ
	strcpy(key2, data2);//Ű �� ����
	curr_idx = root;


	while (1) {//�ι�° word�� �ִ� ����Ÿ��带 ã�´�

		for (i = 0; i < curr_idx->fill_cnt; i++) {

			if (strcmp(key2, curr_idx->key[i]) <= 0) {//�Էµ����Ͱ� curr�� � �����ͺ��� �۴ٸ�
				if (strcmp(key2, curr_idx->key[i]) == 0)
					check_word2 = 1;
				P = curr_idx->idx_ptr[i];	//�� �������� ���� �ڽ������͸� P�� ����
				break;
			}
		}

		if (i == curr_idx->fill_cnt) {//curr�� ���� ū �����ͺ��� ũ�ٸ�
			P = curr_idx->idx_ptr[i];	//�� �������� ������ �ڽ� �����͸� P�� ����
		}

		if (curr_idx->data_ptr[0] != NULL) {	//������ ��� �ٷ� ���� �ε��� ��带 ã��
			P = NULL;
		}
		if (P) {	//�ڽ��� ����
			top++;
			level = top + 1;
			stack[top] = curr_idx;
			curr_idx = P;
			continue;
		}
		else //word2�� �ִ� ����Ÿ��带 ã��( i�� �����ͳ�带 ����Ű�� �ε��� ���� ������ ����)
		{
			curr_data_word2 = curr_idx->data_ptr[i];	//����Ÿ��带 ����Ű�� �����͸� curr_data_word2�� �Ű���
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
		printf("ã�� ������ ���������ʽ��ϴ�...\n");
		return -1;
	}
	//���� ���� �Դٸ� ���� �� �ܾ �� �����Ѵٴ� ���̰� curr_data_word1�� curr_data_word2�� ���� �� �ܾ �ִ� ������ ��带 ����Ű�� ����
	if (strcmp(data1, data2)>0) {//data1�� �� ũ�ٸ�
		curr_data = curr_data_word2;
		
		check_who = 1;	
	}
	else if (strcmp(data1, data2) < 0) {//data2�� �� ũ�ٸ�
		curr_data = curr_data_word1;
		check_who = 2;
	}
	else {//���� ���� �ܾ���
		printf("���� �ܾ ���̽��ϴ�..\n");
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
		printf("�����߻�!\n");
		return -1;
	}
		
	for (j = 0; j < curr_data->fill_cnt; j++) {
		if (strcmp(key_buff, curr_data->rec[j].wstr) == 0) {
			break;
		}
	}
	for (; j < curr_data->fill_cnt; j++) {//ó�� data1(data2)�� �ִ� ��忡�� data1(data2)���� �� ����� ������ �ܾ���� ȭ�Ͽ� �����
		if (check_who == 1) {//b+tree�� ���� ����Ÿ�� ������� ����
			if (check_word1 != 1)
				j++;
		}
		else if (check_who == 2) {
			if (check_word2 != 1)
				j++;
		}
		else {
			printf("�����߻�!\n");
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
		printf("�����߻�!\n");
		return -1;
	}

	while (curr_data->data_ptr) {
		curr_data = curr_data->data_ptr;
		for (int k = 0; k < curr_data->fill_cnt; k++) {
			if (strcmp(key_buff, curr_data->rec[k].wstr) == 0) {//���� ���⼭ key_buff�� �� �������� ū �������� ���� (�� �����ͱ��� �Դٸ� �װͱ��� ����ϰ� ����)
				if (check_who == 2) {
					if (check_word1 == 1)
						fprintf(fp, "%s %s %d\n", curr_data->rec[k].wstr, curr_data->rec[k].pos, curr_data->rec[k].numpos);
				}
				else if (check_who == 1) {
					if (check_word2 == 1)
						fprintf(fp, "%s %s %d\n", curr_data->rec[k].wstr, curr_data->rec[k].pos, curr_data->rec[k].numpos);
				}
				else {
					printf("�����߻�!\n");
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

	printf("��¿Ϸ��߽��ϴ�\n");
	fclose(fp);
	return 0;




}
int main() {
	char text[30];
	char ins[30];	//��ɾ� ����
	char data1[100];	//������ ����1
	char data2[100];	//����2
	int split = 0;
	int check = 0;	//��ɾ�� ������ �������� �ڸ��� ���� üũ ����
	int success = 1;	//���� ����	( ���� = 0 ���� = 1)
	type_rec in_rec;
	while (success == 1) {	//���и� �ݺ�, �����̸� ��������
		printf("�Է� �ؽ�Ʈ ȭ�ϸ���?");
		scanf("%s", text);
		getchar();
		success = putdatast(text);
	}
	while (1) {
		check = 0;//�ʱ�ȭ
		printf("Command? ");
		
		for (int i = 0;; i++) {	//��ɾ� ���� �ޱ�
			ins[i] = getchar();
			if (ins[i] == '\n') {
				ins[i] = '\0';
				break;
			}
			if (ins[i] == ' ') {	//������ ������ �ʿ��ϴٸ� ������ ���� �ޱ�
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
				printf("�ߺ��Դϴ�!! �Է¿� �����Ͽ����ϴ�\n");
				continue;
			}
			else {
				printf("������ �����Ͽ����ϴ�!! split Ƚ���� %d�� �Դϴ�.\n", split);
				continue;
			}
		}
		else if (strcmp(ins, "retrieve") == 0) {	//search
			B_plus_tree_Search(data1, root);
		}
		else if (strcmp(ins, "delete") == 0) {	//deletion( ������ �ϼ����� ���߽��ϴ�. �˼��մϴ�.)
			B_plus_tree_Deletion(data1, &root);
		}
		else if (strcmp(ins, "seqprint") == 0) {	//printout
			B_plus_tree_Sequential_print(root);
		}
		else if (strcmp(ins, "rquery") == 0) {
			B_plus_tree_range_search(data1, data2, root);

		}
		else if (strcmp(ins, "exit") == 0) {
			printf("���α׷��� �����մϴ�....");
			return 0;
		}
		else {
			printf("�߸��� ��ɾ� �Դϴ�.\n");
		}
	}

}
