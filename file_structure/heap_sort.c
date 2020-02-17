#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#pragma warning (disable:4996)

typedef struct {
	char word[100];//�ܾ ù �ܾ�
	int wordidx;   //�ܾ� ���� ������ ù ����
	char pos[10];  //ǰ�翭 �� ù ǰ��
	int numpos;    //ǰ�翭�� ǰ���� �� ����
}arec;

arec rectype;			//����ü ���� ����
arec *recptr = &rectype;//����ü�� ���� ������ ����

unsigned putdatast(FILE* fp, FILE*fpbin) {//����Ÿ�� ����ü�� �Է�

	char buffer[200];	//�ܾ�� ������� �ӽù迭
	char chgint[10];	//���ڿ� ���ڸ� int������ �ٲ��ֱ� ���� �迭
	int total_line = 0; //�� �� ��
	int wordnum = 0;	//ǰ���� �� ����
	int check = 0;		//������ ��������ʾҴٴ� ���� Ȯ�� ����( 1�̸� ������� ���� ���� )
	char *get_err = NULL; //fgets�������˿�


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

		for (; !(isspace(buffer[i])); i++) {	//ó�� ���ڸ� ����ü ���ڿ� �ִ´�
			recptr->word[i] = buffer[i];
			word_length++;
		}

		recptr->word[i] = '\0';	//���ڿ� �ϼ�

		//--------------------------------wordidx----------------------------------


		for (; !(isdigit(buffer[i])); i++) {	//�ܾ������� ���� �� ���� ��ŵ

		}
		for (j = 0; buffer[i] != ' '; j++, i++) {	//�ܾ������� ���� ù ���� �Է�
			chgint[j] = buffer[i];

		}
		chgint[j] = '\0';//���ڿ� �ϼ�

		recptr->wordidx = atoi(chgint);	//���ڹ��ڿ� int������ ����

		//-----------------------------pos------------------------------------

		for (; !(isupper(buffer[i])); i++) {	//ǰ�翭�� ���� ������ ��ŵ

			//ǰ�翭�� ���� ���
			if (buffer[i] == '\n')
				break;
			if (buffer[i] == '\0')
				break;
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

		total_line++;

		fwrite(recptr, sizeof(rectype), 1, fpbin);	//bin���Ͽ� ����ü ����Ÿ �Է�


		//---------------------------------------------------------------------
		for (int n = 0; n < word_length; n++) {//����ü �ʱ�ȭ
			recptr->word[n] = ' ';
		}

		recptr->wordidx = 0;

		for (int n = 0; n < wordnum; n++) {
			recptr->pos[n] = ' ';
		}
		recptr->numpos = 0;
		//--------------------------------------------------------------------

		if (buffer[i] == '\0') {//������ �����ٸ�
			break;
		}



	}
	return total_line;
}

int SortBin(int total_line);//bin������ ����Ÿ�� heap sorting�ϴ� �Լ�

int makebin(char text[]) {//bin���� ����

	FILE *fp, *fpbin;
	int total_line = 0;

	fp = fopen(text, "r");	//������ ���� open

	fpbin = fopen("all_words_occurred.bin", "w+b");	//bin���� ����

	if (!fp) {
		printf("������ ����� �������ʾҽ��ϴ�...");
		return 0;
	}
	if (!fpbin) {
		printf("������ ����� �������ʾҽ��ϴ�...");
		return 0;
	}

	total_line = putdatast(fp, fpbin);//������ ������ ������ ����ü�� �־� bin���� ����

	fclose(fpbin);
	fclose(fp);
	

	return total_line;
}

void FirstSort(FILE* fpbin, int total_line);	//�ʱ� �� ����(Max heap)
void SWAP(FILE * fpbin, int now, int pa);		//����Ÿ SWAP
void MakeHeap(FILE *fpbin, int n);				//�� ����
void BinaryToText(int total_line);				//bin����->text����

int SortBin(int total_line) {//�� ����

	int orgin = total_line;	//�� �� �� ���� ����

	FILE *fpbin;

	fpbin = fopen("all_words_occurred.bin", "r+b");		//binary���� open

	if (!fpbin) {
		printf("������ ����� �������ʾҽ��ϴ�...");
		return 0;
	}

	FirstSort(fpbin, total_line);		//�ʱ� �� ����

	//�� ����
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

void FirstSort(FILE* fpbin, int total_line) {//�ʱ� �� ���� �Լ�

	int now;
	int pa = 0;	//parent
	int i;
	char now_key[100];	//now�� word
	char pa_key[100];	//parent�� word

	for (i = 1; i < total_line; i++) {

		now = i;

		while (now > 0)//now�� ���� ��Ʈ�� �ƴ϶��
		{
			pa = ((now - 1) / 2);

			//now�� word��
			fseek(fpbin, sizeof(rectype)*now, SEEK_SET);
			fread(recptr, sizeof(rectype), 1, fpbin);
			strcpy(now_key, recptr->word);

			//parent�� word��
			fseek(fpbin, sizeof(rectype)*pa, SEEK_SET);
			fread(recptr, sizeof(rectype), 1, fpbin);
			strcpy(pa_key, recptr->word);

			if (strcmp(now_key, pa_key) > 0) {//�θ𺸴� ũ�ٸ�

				SWAP(fpbin, now, pa);//�θ�� ��ȯ

				now = pa;//�ε����� �θ�� ����

			}
			else
			{//�ڸ��� ���� ���

				break;

			}

		}
	}

}

int FindMaxIndex(FILE* fpbin, int n, int now);	//now, left child, right child �� �ִ밪 ���� �Լ�

void MakeHeap(FILE* fpbin, int n) {	//�ִ� �� ����
	
	int now = 0;
	int mp = 0;
	int left = 2 * now + 1;		//left child

	while (left < n)	//���� �ڽ��� ������
	{
		mp = FindMaxIndex(fpbin, n, now);	//now, left child, right�� �ִ밪

		if (mp == now) {//�ڸ��� ã�� ��
			break;
		}

		SWAP(fpbin, mp, now);

		now = mp;	//mp�� now���� ����

		left = 2 * now + 1;

	}
}

int FindMaxIndex(FILE* fpbin, int n, int now) {

	int lc = 2 * now + 1;	//���� �ڽ�
	int rc = 2 * now + 2;	//������ �ڽ�
	char now_key[100];	//now�� word
	char lc_key[100];	//left child�� word
	char rc_key[100];	//right child�� word

	//now�� key��
	fseek(fpbin, sizeof(rectype)*now, SEEK_SET);
	fread(recptr, sizeof(rectype), 1, fpbin);
	strcpy(now_key, recptr->word);

	//left child�� key��
	fseek(fpbin, sizeof(rectype)*lc, SEEK_SET);
	fread(recptr, sizeof(rectype), 1, fpbin);
	strcpy(lc_key, recptr->word);

	//right child�� key��
	fseek(fpbin, sizeof(rectype)*rc, SEEK_SET);
	fread(recptr, sizeof(rectype), 1, fpbin);
	strcpy(rc_key, recptr->word);

	if (rc >= n) //������ �ڽ��� ���� ��
	{
		if (strcmp(lc_key, now_key) > 0) {//���� �ڽ��� �� Ŭ ��
			return lc;
		}
		//now�� �� ũ�ٸ�
		return now;
	}

	if (strcmp(rc_key, lc_key) > 0) //right child > left child �� ��
	{

		if (strcmp(rc_key, now_key) > 0)	//right child�� now ���� ũ�ٸ�
		{
			return rc;
		}
		else   //now�� right child���� ũ�ٸ�
			return now;
	

	}
	if (strcmp(lc_key, now_key) > 0) //left child�� now���� ũ�ٸ�
	{
		return lc;
	}
	else    //now�� left child���� ũ�ٸ�
		return now;

}
void SWAP(FILE * fpbin, int a, int b) {

	arec buff;	//�ӽ� ���� ����ü ����
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



int NoOverlapped(FILE* fpbin, int n, char key[]);	//�ߺ� ���� �Լ�

void BinaryToText(int total_line) {		//bin����-> text����

	FILE * fptext;
	FILE * fpbin;
	int check=0;//�ߺ����� ����
	char key[100];
	int fpf_error = 0;	//fprintf error �˻� ����

	fptext = fopen("words.txt", "w");
	fpbin = fopen("all_words_occurred.bin", "r+b");

	if (!fpbin) {
		printf("���̳ʸ� ������ ����� �������ʾҽ��ϴ�...");
		return;
	}

	if (!fptext) {
		printf("�ؽ�Ʈ ������ ����� �������ʾҽ��ϴ�...");
		return;
	}

	for (int i = 0; i < total_line; i++)	//bin���Ͽ��� �� �پ� �о� text���Ͽ� �Է�
	{
		fseek(fpbin, sizeof(rectype)*i, SEEK_SET);
		fread(recptr, sizeof(rectype), 1, fpbin);
		strcpy(key, recptr->word);
		check = NoOverlapped(fpbin, i, key);//�ܾ� �ߺ� ���� Ȯ��

		if (check == 0) //�ܾ �ߺ���
		{
			i++;	//�� �ٷ� �� ����Ÿ

			for (; i < total_line; i++) {	//�� �ڿ� �� �ߺ��Ǵ��� Ȯ��

				fseek(fpbin, sizeof(rectype)*i, SEEK_SET);
				fread(recptr, sizeof(rectype), 1, fpbin);

				if (strcmp(key, recptr->word) == 0)	//�ߺ��̶�� �Ѿ
				{

				}
				else //�� �� ����Ÿ�� �ߺ��� �ƴ϶��
				{   
					check = 1;
					break;
				}
			}
		}


		if (check == 1) //�ߺ������ʴ´�
		{
			//�ߺ� �˻�� ���� ���� �����͸� �ٽ� �ٲ��ش�
			fseek(fpbin, sizeof(rectype)*i, SEEK_SET);
			fread(recptr, sizeof(rectype), 1, fpbin);

			//words.txt ���Ͽ� �Է�
			fpf_error = fprintf(fptext, "%s %d %s %d\n", recptr->word, recptr->wordidx, recptr->pos, recptr->numpos);

			if (fpf_error == -1)	//fprintf ����
			{
				printf("�Է¿� ���� ������ �߻��Ͽ����ϴ�....");
				return;
			}
		}
	

	}

	fclose(fpbin);
	fclose(fptext);
	

}

int NoOverlapped(FILE* fpbin, int n, char key[]) {

	if (n != 0)	//���� ù ����Ÿ�� �ƴ϶�� 
	{

		fseek(fpbin, sizeof(rectype)*(n - 1), SEEK_SET);	//�� �� ����Ÿ �˻�
		fread(recptr, sizeof(rectype), 1, fpbin);

		if (strcmp(key, recptr->word) == 0) {
			return 0;//�ܾ �ߺ���
		}
	}
	return 1;//�ܾ �ߺ���������

}



int main(void) {
	char text[30];
	int total_line = 0;
	printf("�Է� �ؽ�Ʈ ȭ�ϸ���?");
	scanf("%s", text);
	total_line = makebin(text);//�����͸� �̾� bin���Ͽ� �Է�
	total_line = SortBin(total_line);//bin���� ������ heap sorting
	BinaryToText(total_line);//sorting�� bin���� ������ text���Ϸ� �ű�

	return 0;


}