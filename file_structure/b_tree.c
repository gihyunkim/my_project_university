#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning (disable:4996)
#define MAXK 4 //2d
#define halfK 2 //d

//�Է� ������ ���� ����ü

typedef struct _rec {
	char wstr[100];
	char pos[10];
	int numpos;
}type_rec;

typedef struct node *nodeptr;

//���
typedef struct node {
	nodeptr ptr[MAXK + 1];
	type_rec record[MAXK];
	int fill_cnt;
}node;

//���� ( �Ϲ� ��庸�� ���ڵ� ���� ��������ͼ��� 1�� �� ���� ��� )
typedef struct bignode {
	nodeptr ptr[MAXK + 2];
	type_rec record[MAXK + 1];
}bignode;

//�Ϲ� ��庸�� �� �� �� ū ���
typedef struct two_bignode {
	nodeptr ptr[2*MAXK + 1];
	type_rec record[2*MAXK];
}two_bignode;

//root��带 ����Ű�� ������
nodeptr root = NULL;

int b_tree_insertion(type_rec in_rec, nodeptr *root);

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

		b_tree_insertion(one_record, &root);

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


int b_tree_insertion(type_rec in_rec, nodeptr *root) {

	char key[100];
	int i, j, k, m;
	int top = -1;
	type_rec* recptr = &in_rec;

	nodeptr rnew;	//�� root�� ���
	nodeptr new;	//�� á�� ���� �� ���
	nodeptr stack[50];	//�θ� ������
	nodeptr curr;	//���� ���
	nodeptr P;	//������ ������
	bignode bnode;	//bignode( ���� node���� ���ڵ�� �����ͼ��� �ϳ��� �� ���� ��� )

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

	while (1) {	//�����Ͱ� �� leaf��带 ã�´�

		strcpy(key, recptr->wstr);

		for (i = 0; i < curr->fill_cnt; i++) {
			if (strcmp(key, curr->record[i].wstr) < 0) {//�Էµ����Ͱ� curr�� � �����ͺ��� �۴ٸ�
				P = curr->ptr[i];	//�� �������� ���� �ڽ������͸� P�� ����
				break;
			}
			else if (strcmp(key, curr->record[i].wstr) == 0) {	//�ߺ��̶��
				return 1;
			}
		}

		if (i == curr->fill_cnt) {//curr�� ���� ū �����ͺ��� ũ�ٸ�
			P = curr->ptr[i];	//�� �������� ������ �ڽ� �����͸� P�� ����
		}

		if (P) {	//�ڽ��� ����
			top++;
			stack[top] = curr;
			curr = P;
			continue;
		}
		else
		{
			break;//�ڽ��� ���� ���� ����
		}

	}

	while (1) {

		strcpy(key, recptr->wstr);

		if (curr->fill_cnt != MAXK) {	//curr�� �� ���� �ʾ��� ���

			for (i = 0; i < curr->fill_cnt; i++) {
				if (strcmp(key, curr->record[i].wstr) < 0) {//�Էµ����Ͱ� curr�� �����͵麸�� �۴ٸ�
					for (j = curr->fill_cnt - 1; j >= i; j--) {//���������� ��ĭ�� push
						curr->record[j + 1] = curr->record[j];
						curr->ptr[j + 2] = curr->ptr[j + 1];
					}
					//�Էµ����� ������ �ڸ��� �ֱ�
					curr->record[i] = in_rec;
					curr->ptr[i + 1] = P;
					curr->fill_cnt++;
					return 1;
				}
			}
			if (i == curr->fill_cnt) {//curr�� �����͵麸�� ũ�ٸ�
				curr->record[i] = in_rec;	//������ �ڸ��� �ֱ�
				curr->ptr[i + 1] = P;
				curr->fill_cnt++;
				return 1;
			}
		}
		else {	//curr�� �� á�� ���

			for (k = 0; k < MAXK; k++) {	//key������ �������� ã��
				if (strcmp(key, curr->record[k].wstr) < 0) //�� ã������ break
					break;
			}

			bnode.ptr[0] = curr->ptr[0];

			for (m = 0; m < k; m++) {	//key������ �������� bnode�� ���� �ֱ�
				bnode.ptr[m + 1] = curr->ptr[m + 1];
				bnode.record[m] = curr->record[m];
			}

			//�� ����, �Է� ������ �ֱ�
			bnode.ptr[m + 1] = P;
			bnode.record[m] = in_rec;
			m++;

			//������ bnode�� �ֱ�
			for (; m < MAXK + 1; m++) {
				bnode.ptr[m + 1] = curr->ptr[m];
				bnode.record[m] = curr->record[m - 1];
			}

			for (i = 0; i < halfK; i++) {	//���� ���� curr�� �־��ش�
				curr->ptr[i] = bnode.ptr[i];
				curr->record[i] = bnode.record[i];
			}
			curr->fill_cnt = halfK;
			curr->ptr[i] = bnode.ptr[i];

			for (; i < MAXK; i++) {	//curr�� ������ ������ ����
				curr->ptr[i + 1] = NULL;
				nodeptr *buff = &curr->record[i];
				*buff = NULL;
				curr->record[i].numpos = 0;
				buff = &curr->record[i].pos;
				*buff = NULL;

			}

			//new��� ���� �� ������ �� ������ �ֱ�
			new = (nodeptr)malloc(sizeof(node));


			for (i = 0; i < halfK; i++) {

				new->ptr[i] = bnode.ptr[i + halfK + 1];
				new->record[i] = bnode.record[i + halfK + 1];
			}
			new->ptr[i] = bnode.ptr[i + halfK + 1];
			new->fill_cnt = halfK;

			//��� ������
			P = new;
			in_rec = bnode.record[halfK];

			if (top >= 0) {//�θ� ��尡 �����Ѵٸ�
				curr = stack[top];
				top--;
				continue;
			}
			else {//�θ� ��尡 �������� �ʴ´ٸ�
				rnew = (nodeptr)malloc(sizeof(node));
				rnew->ptr[0] = curr;
				rnew->record[0] = in_rec;
				rnew->ptr[1] = P;
				rnew->fill_cnt = 1;
				*root = rnew;	//�θ� ��尡 �������� �ʴ´ٸ� �� �� ��尡 ��Ʈ�� ��
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

int B_tree_Insertion_in_test(type_rec in_rec, nodeptr * root) {	//record�� �����ϴ� �Լ� (�����̸� splitȽ�� ����, ���и� -1 ����)
	char key[100];
	int i, j, k, m;
	int top = -1;
	int split = 0;	//split Ƚ��
	type_rec* recptr = &in_rec;

	nodeptr rnew;	//�� root�� ���
	nodeptr new;	//�� á�� ���� �� ���
	nodeptr stack[50];	//�θ� ������
	nodeptr curr;	//���� ���
	nodeptr P;	//������ ������
	bignode bnode;	//bignode( ���� node���� ���ڵ�� �����ͼ��� �ϳ��� �� ���� ��� )
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

	while (1) {	//�����Ͱ� �� leaf��带 ã�´�

		strcpy(key, recptr->wstr);

		for (i = 0; i < curr->fill_cnt; i++) {
			if (strcmp(key, curr->record[i].wstr) < 0) {//�Էµ����Ͱ� curr�� � �����ͺ��� �۴ٸ�
				P = curr->ptr[i];	//�� �������� ���� �ڽ������͸� P�� ����
				break;
			}
			else if (strcmp(key, curr->record[i].wstr) == 0) {	//�ߺ��̶�� ����
				return -1;
			}
		}

		if (i == curr->fill_cnt) {//curr�� ���� ū �����ͺ��� ũ�ٸ�
			P = curr->ptr[i];	//�� �������� ������ �ڽ� �����͸� P�� ����
		}

		if (P) {	//�ڽ��� ����
			top++;
			stack[top] = curr;
			curr = P;
			continue;
		}
		else
		{
			break;//�ڽ��� ���� ���� ����
		}

	}

	while (1) {

		strcpy(key, recptr->wstr);

		if (curr->fill_cnt != MAXK) {	//curr�� �� ���� �ʾ��� ���

			for (i = 0; i < curr->fill_cnt; i++) {
				if (strcmp(key, curr->record[i].wstr) < 0) {//�Էµ����Ͱ� curr�� �����͵麸�� �۴ٸ�
					for (j = curr->fill_cnt - 1; j >= i; j--) {//���������� ��ĭ�� push
						curr->record[j + 1] = curr->record[j];
						curr->ptr[j + 2] = curr->ptr[j + 1];
					}
					//�Էµ����� ������ �ڸ��� �ֱ�
					curr->record[i] = in_rec;
					curr->ptr[i + 1] = P;
					curr->fill_cnt++;
					return split;
				}
			}
			if (i == curr->fill_cnt) {//curr�� �����͵麸�� ũ�ٸ�
				curr->record[i] = in_rec;	//������ �ڸ��� �ֱ�
				curr->ptr[i + 1] = P;
				curr->fill_cnt++;
				return split;
			}
		}
		else {	//curr�� �� á�� ���

			for (k = 0; k < MAXK; k++) {	//key������ �������� ã��
				if (strcmp(key, curr->record[k].wstr) < 0) //�� ã������ break
					break;
			}

			bnode.ptr[0] = curr->ptr[0];

			for (m = 0; m < k; m++) {	//key������ �������� bnode�� ���� �ֱ�
				bnode.ptr[m + 1] = curr->ptr[m + 1];
				bnode.record[m] = curr->record[m];
			}

			//�� ����, �Է� ������ �ֱ�
			bnode.ptr[m + 1] = NULL;
			bnode.record[m] = in_rec;
			m++;

			//������ bnode�� �ֱ�
			for (; m < MAXK + 1; m++) {
				bnode.ptr[m + 1] = curr->ptr[m];
				bnode.record[m] = curr->record[m - 1];
			}

			for (i = 0; i < halfK; i++) {	//���� ���� curr�� �־��ش�
				curr->ptr[i] = bnode.ptr[i];
				curr->record[i] = bnode.record[i];
			}
			curr->fill_cnt = halfK;
			curr->ptr[i] = bnode.ptr[i];

			for (; i < MAXK; i++) {	//curr�� ������ ������ �ʱ�ȭ

				nodeptr *buff = &curr->record[i];

				curr->ptr[i + 1] = NULL;
				*buff = NULL;
				curr->record[i].numpos = 0;
				buff = &curr->record[i].pos;
				*buff = NULL;

			}

			//new��� ���� �� ������ �� ������ �ֱ�
			new = (nodeptr)malloc(sizeof(node));


			for (i = 0; i < halfK; i++) {

				new->ptr[i] = bnode.ptr[i + halfK + 1];
				new->record[i] = bnode.record[i + halfK + 1];
			}
			new->ptr[i] = bnode.ptr[i + halfK + 1];
			new->fill_cnt = halfK;

			//��� ������
			P = new;
			in_rec = bnode.record[halfK];

			split++;

			if (top >= 0) {//�θ� ��尡 �����Ѵٸ�
				curr = stack[top];
				top--;
				continue;
			}
			else {//�θ� ��尡 �������� �ʴ´ٸ�
				rnew = (nodeptr)malloc(sizeof(node));
				rnew->ptr[0] = curr;
				rnew->record[0] = in_rec;
				rnew->ptr[1] = P;
				rnew->fill_cnt = 1;
				*root = rnew;	//�θ� ��尡 �������� �ʴ´ٸ� �� �� ��尡 ��Ʈ�� ��
				return split;
			}
		}
	}


}

int B_tree_Search(char word[100], nodeptr root) {	//root����� level�� 0�̶��ϰ� �� �Ʒ����� 1�� ����

	char key[100];
	int i;
	int top = -1;
	int level = 0;

	nodeptr stack[50];	//�θ� ������
	nodeptr curr;	//���� ���
	nodeptr P;	//������ ������

	curr = root;

	while (1) {	

		strcpy(key, word);

		for (i = 0; i < curr->fill_cnt; i++) {
			if (strcmp(key, curr->record[i].wstr) < 0) {//�Էµ����Ͱ� curr�� � �����ͺ��� �۴ٸ�
				P = curr->ptr[i];	//�� �������� ���� �ڽ������͸� P�� ����
				break;
			}
			else if (strcmp(key, curr->record[i].wstr) == 0) {	//ã�Ҵٸ�
				printf("�ش� �̸��� LEVEL %d�� �ִ� ���ڵ� �� %d��°�� �ֽ��ϴ�.\n", level, i + 1);
				return 0;
			}
		}

		if (i == curr->fill_cnt) {//curr�� ���� ū �����ͺ��� ũ�ٸ�
			P = curr->ptr[i];	//�� �������� ������ �ڽ� �����͸� P�� ����
		}

		if (P) {	//�ڽ��� ����
			top++;
			level = top + 1;
			stack[top] = curr;
			curr = P;
			continue;
		}
		else
		{
			break;//�ڽ��� ���� ���� ����
		}

	}
	printf("�ش� �̸��� ã�� ���� �����ϴ�.\n");
	return -1;

}

int B_tree_Deletion(char word[100], nodeptr *root) {

	char key[100];

	int i, j, k, m;
	int top = -1;
	int retri=0;	//��й� Ƚ��
	int merge=0;	//�պ� Ƚ��
	int middle = 0; //bignode�� �� ���ڵ� ���� ��

	nodeptr stack[50];	//�θ� ������
	nodeptr curr;	//���� ���
	nodeptr succ; //successor Ž����
	nodeptr parent;	//balancing���� sibling ���θ� �˱����� �θ���
	nodeptr left_sibling;	//���� ����
	nodeptr right_sibling;	//������ ����
	nodeptr P;	//������ ������
	nodeptr * ptr;	//��� ���� ������

	two_bignode tbnode;

	if (!*root) {
		printf("�����Ͱ� �ϳ��� �������� �ʽ��ϴ�....\n");
		return 1;
	}

	curr = *root;

	strcpy(key, word);

	while (1) {	//������ �����Ͱ� �ִ� ��带 Ž��

		for (i = 0; i < curr->fill_cnt; i++) {
			if (strcmp(key, curr->record[i].wstr) < 0) {//������ ���ڿ��� curr����� � ������ �۴ٸ�
				P = curr->ptr[i];	//�� �������� ���� �ڽ������͸� P�� ����
				break;
			}
			else if (strcmp(key, curr->record[i].wstr) == 0) {	//������ �����Ͱ� �ִ� ��� ã��

				//������ �ڽ� �����͸� successor Ž�� �����Ϳ� ����
				succ = curr->ptr[i + 1];

				//successor Ž��
				if (succ) {	//���� �ڽ� ��尡 �����Ѵٸ� ������ ���ڵ��� ������ �ڽ����� ������
					top++;
					stack[top] = curr;

					while (succ->ptr[0]) {	//leaf��尡 ���� �� ���� ���� �ڽ����� ��� ������
						P = succ->ptr[0];
						top++;
						stack[top] = succ;
						succ = P;
					}

					//���� leaf ����� ���� ù ���ڵ尡 successor�̴�.
					//successor�� ������ ���� ���� ��ȯ���ִ� �۾�

					curr->record[i] = succ->record[0];	//successor�� ���� ���� ���ڵ忡 ��ü

					//������ ���ڵ尡 �ִ� ��ġ�� �̵� ( successor�� �ִ� ��� )
					curr = succ;
					
					//���ڵ� ����
					ptr = &curr->record[0].wstr;
					*ptr = NULL;
					curr->record[0].numpos = 0;
					ptr = &curr->record[0].pos;
					*ptr = NULL;
					curr->fill_cnt--;

					//�� ������ ������ ����
					curr->ptr[1] = NULL;

					for (j = 0; j < curr->fill_cnt; j++) {
						curr->record[j] = curr->record[j + 1];
						curr->ptr[j + 1] = curr->ptr[j + 2];
					}


					if (top==-1) {//���� ��尡 root�����
						ptr = &curr->record[0];
						if (!*ptr) {//��Ʈ����� ���ڵ尡 ���������ʴ´ٸ�
							free(curr);
						}
						else {//��Ʈ����� ���ڵ尡 ����							
							printf("������ �����Ͽ����ϴ�!! ��й�� %d��, �պ��� %d���Ͽ����ϴ�\n", retri, merge);
							return 0;
						}
					}

					while (1) {
						if (curr->fill_cnt < halfK) {	//��尡 balancing�� ��߳�
							
							//�θ�� �ö� ������ ������ ���� ������ �ִ��� Ȯ�� (������ ������ ��ȣ)
							parent = stack[top];
							top--;

							for (j = 0; j < parent->fill_cnt; j++) {
								if (parent->ptr[j] == curr) {
									break;
								}
							}

							//j�� parent������ curr��� ������

							if (j != 0) {
								left_sibling = parent->ptr[j - 1];						
							}
							if (j != MAXK) {
								right_sibling = parent->ptr[j + 1];
							}
							 
							if (right_sibling&&right_sibling->fill_cnt > halfK) {	//������ �������� ������ ( ��й谡 ���� )

								//tbnode�� ���� curr���� �ִ´�
								tbnode.ptr[0] = curr->ptr[0];
								for (k = 0; k < curr->fill_cnt; k++) {
									tbnode.ptr[k + 1] = curr->ptr[k + 1];
									tbnode.record[k] = curr->record[k];
								}
								
								//�� ����, curr�� ������ ���� ������ �θ��� ���ڵ� ���� �ִ´�.
								tbnode.record[k] = parent->record[j];	
								k++;

								tbnode.ptr[k] = right_sibling->ptr[0];
								for (m=0; m < right_sibling->fill_cnt; k++, m++) {
									tbnode.ptr[k + 1] = right_sibling->ptr[m + 1];
									tbnode.record[k] = right_sibling->record[m];
								}

								//k�� two_bignode �� ���ڵ� ���� �������

								middle = k / 2;
								//two_bignode���� middle��° ���ڵ带 �������� ������ curr�� �ִ´�.
								for (i = 0; i < middle; i++) {
									curr->ptr[i] = tbnode.ptr[i];
									curr->record[i] = tbnode.record[i];
								}
								curr->ptr[i] = tbnode.ptr[i];
								curr->fill_cnt = middle;
								
								//parent���ٰ� ��� ���� halfK��° ���ڵ� ���� �ִ´�.
								parent->record[j] = tbnode.record[halfK];
								i++;

								//������ �ڽĿ� ������ two_bignode������ �ִ´�.
								for (m=0; i < k; m++,i++) {
									right_sibling->ptr[m] = tbnode.ptr[i];
									right_sibling->record[m] = tbnode.record[i];
								}
								right_sibling->ptr[m] = tbnode.ptr[i];
								right_sibling->fill_cnt = k - (middle + 1);	//two_bignode�� �� ���ڵ� ������ curr�� ���� �ݰ� parent�� ���� ���� ������ ������ ��

								retri++;

								printf("������ �����Ͽ����ϴ�!! ��й�� %d��, �պ��� %d���Ͽ����ϴ�\n", retri, merge);
								return 0;
							}
							else if (left_sibling&&left_sibling->fill_cnt > halfK) {	//���� �������� ������ ( ��й谡 ���� )
							

								//tbnode�� ���� ���� �ڽĳ���� ���� �ִ´�
								tbnode.ptr[0] = left_sibling->ptr[0];
								for (k = 0; k < left_sibling->fill_cnt; k++) {
									tbnode.ptr[k + 1] = left_sibling->ptr[k + 1];
									tbnode.record[k] = left_sibling->record[k];
								}

								tbnode.record[k] = parent->record[j-1];	//�� ����, curr�� ���� ���� ������ �θ��� ���ڵ� ���� �ִ´�.
								k++;								

								//�� ����, curr�� ������ two_bignode�� �ִ´�
								tbnode.ptr[k] = curr->ptr[0];
								for (m = 0; m < curr->fill_cnt; k++, m++) {
									tbnode.ptr[k + 1] = curr->ptr[m + 1];
									tbnode.record[k] = curr->record[m];
								}

								//k�� two_bignode �� ���ڵ� ���� �������
								middle = k / 2;
								
								//two_bignode���� middle��° ���ڵ带 �������� ������ curr�� �ִ´�. 		
								for (i = 0; i < middle; i++) {
									left_sibling->ptr[i] = tbnode.ptr[i];
									left_sibling->record[i] = tbnode.record[i];
								}
								left_sibling->ptr[i] = tbnode.ptr[i];
								left_sibling->fill_cnt = middle;

								//parent���ٰ� ��� ���� middle��° ���ڵ� ���� �ִ´�.
								parent->record[j] = tbnode.record[middle];

								i++;

								//curr�� ������ two_bignode������ �ִ´�.
								for (m = 0; i < k; m++, i++) {
									curr->ptr[m] = tbnode.ptr[i];
									curr->record[m] = tbnode.record[i];
								}
								curr->ptr[m] = tbnode.ptr[i];
								curr->fill_cnt = k - (middle + 1);	//two_bignode�� �� ���ڵ� ������ ���� ������ ���� �ݰ� parent�� ���� ���� ������ ������ ��
							
								retri++;

								printf("������ �����Ͽ����ϴ�!! ��й�� %d��, �պ��� %d���Ͽ����ϴ�\n", retri, merge);

								return 0;
							}
							else {	//�պ��� �ؾ��Ѵ�. ( ��й谡 �Ұ��� )

								int next = curr->fill_cnt;	//curr�� ���ִ� ���ڵ� ������ ���� �ε���

								if (right_sibling) {	//������ ������ �ִٸ�
									
									//curr�� ������ ���� ������ ���̿� �ִ� ���ڵ带 �ִ´�
									curr->record[next] = parent->record[j];
									next++;

									//�� ����, ������ ������ ������ curr�� ������ �κп� �ִ´�.
									curr->ptr[next] = right_sibling->ptr[0];
									for (i=0; i < right_sibling->fill_cnt; next++,i++) {
										curr->record[next] = right_sibling->record[i];
									}

									//������ ���� ��� ����
									free(right_sibling);
									
									//parent���� curr�� ������ ���� ���̿� �ִ� ���ڵ带 �������� �������� ��ĭ�� shift
									for (; j + 1 < parent->fill_cnt; j++) {
										parent->record[j] = parent->record[j + 1];
										parent->ptr[j + 1] = parent->ptr[j + 2];
									}
									
									//��ĭ �� �Ű�ٸ� ���������� �ű� ���ڵ��� ���� ��ġ ���ڵ�� ������ �ʱ�ȭ
									ptr = &parent->record[j].wstr;
									*ptr = NULL;
									ptr = &parent->record[j].pos;
									*ptr = NULL;
									parent->record[j].numpos = 0;
									parent->ptr[j + 1] = NULL;

									parent->fill_cnt--;

									curr = parent;	//curr�� �θ� �����͸� �ְ� �ٽ� �ݺ�
									top--;
									merge++;
									continue;
									
								}else {//���� ������ �պ�
									//curr�� ������ ���� ������ ���ڵ��� curr�� ���� ���� ������ parent ���ڵ���� ��ģ ����ŭ ���������� shift
									for (i = 0; i < curr->fill_cnt; i++) {
										curr->ptr[i + (left_sibling->fill_cnt + 1)] = curr->ptr[i];	
										curr->record[i + (left_sibling->fill_cnt + 1)] = curr->record[i];
									}
									curr->ptr[i + (left_sibling->fill_cnt + 1)] = curr->ptr[i];
									
									//�� ����, curr�� ���� ���� ������ parent���ڵ带 �Ű��� curr�� ���� ���ʿ� �ִ´�.
									curr->record[left_sibling->fill_cnt] = parent->record[j - 1];

									//�׸��� ���� ������ ������ curr�� ó������ �ִ´�.
									for (i = 0; i < left_sibling->fill_cnt; i++) {
										curr->ptr[i] = left_sibling->ptr[i];
										curr->record[i] = left_sibling->record[i];
									}
									curr->ptr[i] = left_sibling->ptr[i];
									
									free(left_sibling);	//���� ������� ����

									//parent���� curr�� ���� ���� ���̿� �ִ� ���ڵ带 �������� �������� ��ĭ�� shift
									for (; j  < parent->fill_cnt; j++) {
										parent->record[j - 1] = parent->record[j];
										parent->ptr[j - 1] = parent->ptr[j];
									}
									parent->ptr[j - 1] = parent->ptr[j];

									//��ĭ �� �Ű�ٸ� ���������� �ű� ���ڵ��� ���� ��ġ ���ڵ�� ������ �ʱ�ȭ
									ptr = &parent->record[j-1].wstr;
									*ptr = NULL;
									ptr = &parent->record[j-1].pos;
									*ptr = NULL;
									parent->record[j-1].numpos = 0;
									parent->ptr[j] = NULL;

									parent->fill_cnt--;

									curr = parent;  //curr�� �θ� �����͸� �ְ� �ٽ� �ݺ�
									top--;
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
				else {	//���� ��尡 leaf��� �̹Ƿ� �ٷ� �����Ѵ�.
					ptr = &curr->record[i].wstr;
					*ptr = NULL;
					curr->record[i].numpos = 0;
					ptr = &curr->record[i].pos;
					*ptr = NULL;
					curr->fill_cnt--;
					printf("������ �����Ͽ����ϴ�!! ��й�� %d��, �պ��� %d���Ͽ����ϴ�\n", retri, merge);
					return 0;
				}
				
				

			}
		}

		if (i == curr->fill_cnt) {//curr�� ���� ū �����ͺ��� ũ�ٸ�
			P = curr->ptr[i];	//�� �������� ������ �ڽ� �����͸� P�� ����
		}

		if (P) {	//�ڽ��� ����
			top++;
			stack[top] = curr;
			curr = P;
			continue;
		}
		else
		{
			printf("�����Ϸ��� ���� ���������ʽ��ϴ�...\n");
			return 1;//������ ���� ������������
		}
	}
}


int B_tree_Sequential_print(nodeptr root) {

	FILE * fp = fopen("SeqData.txt", "w");
	int i = 0;
	int j = 0;
	int on[100];	//�θ��� i �����( �θ� ��� �ڽı��� Ȯ���ߴ��� üũ )
	int top = -1;	//���� ����� level root�� -1 �ڽ����� ������ ���� 1�� +

	nodeptr stack[50];	//�θ� ������
	nodeptr curr;	//���� ���
	nodeptr P;	//������ ������

	if (!root) {
		printf("�����Ͱ� �ϳ��� �������� �ʽ��ϴ�....\n");
		return 1;
	}

	curr = root;

	while (1) {

		if (i > curr->fill_cnt) {	//���� ����� ��� �����͸� print������

			if (top >= 0) {//�θ� ����
				//�θ�� �ö� ��, on[top] ++
				curr = stack[top];
				on[top]++;
				i = on[top];
				top--;

				if ((i - 1) < curr->fill_cnt)	//���ڵ尡 �����Ѵٸ� ���
					fprintf(fp, "%s %s %d\n", curr->record[i - 1].wstr, curr->record[i - 1].pos, curr->record[i - 1].numpos);

				continue;
			}
			else {	//��Ʈ����� �ǹ�
				printf("SeqData.txt ���Ͽ� ��� �Ϸ��Ͽ����ϴ�.\n");
				return 1;
			}

		}
		else     //���� �ڽ� üũ
			P = curr->ptr[i];

		if (i < curr->fill_cnt && !P) {	//� ���ڵ��� ���� �ڽ��� �������� ���� ��
			for (; i < curr->fill_cnt; i++) {
				fprintf(fp, "%s %s %d\n", curr->record[i].wstr, curr->record[i].pos, curr->record[i].numpos);
			}
			i++;
			continue;
		}
		else if (i == curr->fill_cnt && !P) {	//�ǿ��� ���ڵ�� �����ϴµ� �� ���� �ڽ��� �������� ���� ��
			i++;
			continue;
		}

		if (P) {	//�ڽ��� ����

			//���ÿ� ���� ��带 ���� �� �ڽ����� ������
			top++;
			on[top] = i;
			i = 0;
			stack[top] = curr;
			curr = P;
			continue;
		}
		else
		{
			//�ڽ��� �ƿ� ���� ����� ���, ���������� ��� ���
			for (j = 0; j < curr->fill_cnt; j++) {
				fprintf(fp, "%s %s %d\n", curr->record[j].wstr, curr->record[j].pos, curr->record[j].numpos);
			}

			if (top >= 0) {//�θ� ����
				curr = stack[top];
				on[top]++;
				i = on[top];
				top--;

				if ((i - 1) < curr->fill_cnt)
					fprintf(fp, "%s %s %d\n", curr->record[i - 1].wstr, curr->record[i - 1].pos, curr->record[i - 1].numpos);

				continue;
			}
			else {	//��� ��
				printf("SeqData.txt ���Ͽ� ��� �Ϸ��Ͽ����ϴ�.\n");
				return 1;
			}

		}
	}


	fclose(fp);


}


int main() {
	char text[30];
	char ins[30];	//��ɾ� ����
	char data[100];	//������ ����
	int split = 0;
	int success = 1;	//���� ����	( ���� = 0 ���� = 1)
	type_rec in_rec;
	while (success == 1) {	//���и� �ݺ�, �����̸� ��������
		printf("�Է� �ؽ�Ʈ ȭ�ϸ���?");
		scanf("%s", text);
		getchar();
		success = putdatast(text);
	}
	while (1) {
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
				printf("�ߺ��Դϴ�!! �Է¿� �����Ͽ����ϴ�\n");
				continue;
			}
			else {
				printf("������ �����Ͽ����ϴ�!! split Ƚ���� %d�� �Դϴ�.\n", split);
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
			printf("���α׷��� �����մϴ�....");
			return 0;
		}
		else {
			printf("�߸��� ��ɾ� �Դϴ�.\n");
		}
	}

}