#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define tbl_Size 37533		//hash-table�� ũ��
#pragma warning (disable:4996)

typedef struct element {	//�����͸� ���� ����ü
	char name[100];	//ȸ���
	int monincome;	//�������� ������ �����
	int link;		//���� ��ũ�� �� �� ��ũ ����
	int HA;			//HomeAddress�� ���� ����
}type_record;

type_record hash_table[tbl_Size];	//�ؽ����̺� ����

long R = tbl_Size;	//�� ���̺��� ���� ã�� ���� �� R���� ( ����ִ� ���� ���� �ε����� ����Ű�� �ִ� )

int rec_count = 0;	//record move Ƚ��( ������ �� �߻��� ���ڵ尣 �̵� Ƚ�� )

void setDummy() {	//table�� Dummy record ����

	for (int i = 0; i < tbl_Size; i++) {
		hash_table[i].name[0] = '-';	//�̸��� key���̹Ƿ� ���� ó�� �ε��� 0�� -�� ���̷� �� �־����
	}

}
int checkEmpty();	//�ؽ����̺� �� �� ���ڵ带 ã�� ��ȯ�ϴ� �Լ�
int hash(char recname[]);	//�ؽ��Լ� ( ���ڿ��� ���ڷ� �ٲ� ��ȯ���ִ� �ؽ� )

void setStruct() {

	FILE* fp = fopen("Companies_Korean.txt", "r");
	char *get_err = NULL;
	type_record element;
	int empty;			//�� ���ڵ��� �ּҸ� �޴� ����
	int override = 0;	//1�̸� �ߺ�
	int hash_num;	//���Ͽ��� �о�� �������� �ؽ��Լ���
	int curr_num;	//��ũ�� �̾������� ���� ���� �ּҸ� �˷��ִ� ����
	int check = 0; // ���� ����ִ��� Ȯ�� ���� 1�� ���� ���� 0�̸� ���� ����
	int i = 0;
	int end = 0;	//������ �������� üũ ���� 0�̸� false 1�̸� true

	srand(time(NULL));		//�������� ����ø��� �ٲ��ִ� �Լ�
	setDummy();				//���̰� �Է� �Լ�

	if (!fp) {	//������ ���� ���� ����
		printf("�������� �ʴ� �����Դϴ�...\n");
		return;
	}
	while (1) {

		get_err = fgets(element.name, sizeof(element.name), fp);	//���Ͽ��� �� ���� �о��

		if (!get_err) {	
			if (check == 1) {	//������ ������ ������ ��
				return;
			}
			//������ ������ ���� ��� ( ó���� get_err�� NULL�� ��� )
			printf("������ ���� �����Դϴ�.");
			return;
		}
		for (int j = 0; j < strlen(element.name); j++) {	//fgets���� �о�� �� \n�� �����ֱ� ����
			if (element.name[j] == '\n') {		//������ \n�� \0�� �ٲ��־� ���ڿ��� ����
				element.name[j] = '\0';
			}
		}

		element.monincome = 10000000 + rand() % 90000001;	//���� õ��~1��
		hash_num = hash(element.name);	//�ؽ��Լ����� �ؽð��� ��ȯ���� hash_num�� �Է�
		curr_num = hash_num;	//������ �ּҰ� ������ �ؽð�

		if (hash_table[hash_num].name[0] == '-') {	//HA�� hash_num�� �����Ͱ� �̰� ó���̶��
			for (int j = 0; j < strlen(element.name); j++) {	//������ ���� �����ϱ� ����
				if (element.name[j] == '\0') {//���� �� �����Ͱ� ������ �� �����Ͷ��
					end = 1;
				}
				hash_table[hash_num].name[j] = element.name[j];	//�ؽ����̺� ���ڵ� ���� �־���
			}
			hash_table[hash_num].monincome = element.monincome;
			hash_table[hash_num].HA = hash_num;
		}
		else {//ó���� �ƴ� ���

			while (1) {	//link�� ���� HA�� hash_num�� �ּҸ� ã�ư�
				if (strcmp(hash_table[curr_num].name, element.name) == 0) {	//�ߺ��Ǵ� ���� ���� ��
					override = 1;	
					break;
				}
				if (!hash_table[curr_num].link)	//link�� ���ٸ� break
					break;
				curr_num = hash_table[curr_num].link;	//�ִٸ� �� link�� Ÿ�� ��
			}
			if (override == 1) {	//�ߺ��̶�� ������ ���� �����͸� �޾ƿ´�
				i++;
				continue;
			}
			empty = checkEmpty();	//�� ���� �ִ����� ã�´�

			for (int j = 0; j < strlen(element.name); j++) {	
				if (element.name[j] == '\0') {	//���� �� �����Ͱ� ������ �� �����Ͷ��
					end = 1;
				}
				hash_table[empty].name[j] = element.name[j];	//�� �ؽ����̺� ���ڵ� ���� �־���
			}
			hash_table[empty].monincome = element.monincome;
			hash_table[empty].HA = hash_num;
			hash_table[curr_num].link = empty;
		}

		if (end == 1) {	//������ ������ �����Ϳ��ٸ� �ݺ����� ����
			break;
		}

		i++;

		check = 1;	//�����Ͱ� �� ���� �־����� Ȯ��

	}

	fclose(fp);

}
int searchData(char data[30], int choose);	//Ž�� �Լ� choose�� 0�̸� �׳� Ž�� 1�̸� getprobe �Լ�
void insertData(char data[30]) {	//�����͸� �޾� �����ϴ� �Լ�
	int hash_num;	//�� �������� �ؽ� ���� ���� ����
	int empty;		//�� ���̺� �ּҸ� ���� ����
	int curr_num;	//��ũ�� �̾������� ���� ���� �ּҸ� �˷��ִ� ����
	hash_num = hash(data);	//�ؽ��Լ��� �ؽð��� ��ȯ����
	curr_num = hash_num;	

	if (hash_table[hash_num].name[0] == '-') {	//HA�� hash_num�� �����Ͱ� �̰� ó���̶��
		strcpy(hash_table[hash_num].name, data);	//�����͸� �� �ؽ����̺� ����
		hash_table[hash_num].monincome = 10000000 + rand() % 90000001;
		printf("Success in insertion. Position = %d\n", hash_num);
	}
	else {	//ó���� �ƴ� ���
		while (1) {	//link�� ���� HA�� hash_num�� �ּҸ� ã�ư�
			if (strcmp(hash_table[curr_num].name, data) == 0) {	//�ߺ��Ǵ� �����Ͷ�� ����
				printf("�̹� ��ϵ� ȸ���Դϴ�....\n");
				return;
			}
			if (!hash_table[curr_num].link)	//link�� ���ٸ�
				break;
			curr_num = hash_table[curr_num].link;	//�ִٸ� link�� Ÿ�� ��
		}

		empty = checkEmpty();	//�ؽ����̺� �� ���ڵ带 ã�� �ּҹ�ȯ
		//�� ���ڵ忡 �����͸� �־���
		strcpy(hash_table[empty].name, data);
		hash_table[empty].monincome = 10000000 + rand() % 90000001;
		hash_table[curr_num].link = empty;
		printf("Success in insertion. Position = %d\n", empty);
	}


	return;

}

int searchData(char data[30], int choose) {	//choose�� 0�̸� �׳� search ���, 1�̸� �� probe����� �� ���
	int hash_num;
	int probe = 1;	//probe���� ( �� ���� ��ġ���� ���縦 �����Ͽ��ĸ� ��� ���� )
	int curr_num; //���� ��ġ
	hash_num = hash(data);
	curr_num = hash_num;

	if (hash_table[hash_num].name[0] == '-') {	//���̺��� ����ִٸ�
		printf("�����Ͱ� ���������ʽ��ϴ�...\n");
		return -1;
	}
	else {
		while (1) {
			if (strcmp(data, hash_table[curr_num].name) == 0) {	//����Ÿ�� ã�Ҵٸ� �������� ��� �� probe �� ����
				if (choose == 0) {	//�� probe���ÿ��� �����������
					printf("Position = %d, probe = %d\n", curr_num, probe);
				}
				return probe;
			}
			else {
				if (hash_table[curr_num].link) {//link�� �ִٸ� link�� Ÿ��
					curr_num = hash_table[curr_num].link;
					probe++;	//probe �� 1 ����
				}
				else {//�����͸� ã�� ����
					printf("�����Ͱ� ���������ʽ��ϴ�...\n");
					return -1;
				}
			}
		}
	}
}

int del_start(int curr_num, int choose);	//HA�� �ڽ��� �ּ��� ���ڵ带 ���� ���� �Լ� 
											//( �� Ư�� HA���� ���� ���ڵ� �� ó�� ���ڵ� )
int del_middle(int s, int p, int choose);	//Ư�� HA���� ���� ���ڵ� �� �߰��� �ִ� ���ڵ带 ���� ���� �Լ�

int delete(char data[30], int choose) {	//choose �� 0�̸� �׳� delete 1�̸� �ϰ�����
	int hash_num;
	int curr_num;
	int previous;		//�������� ��ġ�� ���� ����
	int success = 0;	//data�� ���� �̸��� ã�Ҵ��� ���� 1�̸� ���� 0�̸� ����

	rec_count = 0;	//move Ƚ�� �ʱ�ȭ
	hash_num = hash(data);
	curr_num = hash_num;

	if (strcmp(hash_table[hash_num].name, data)==0) {	//������ �����Ͱ� HA=hash_num�� ���ڵ�� �� ù ���ڵ忡 �ִٸ�
		rec_count = del_start(hash_num,choose);	//del_start�Լ��� �θ��� ���� �� moveȽ���� ���Ϲ���
		return rec_count;
	}
	else {

		while (hash_table[curr_num].link) {	//link�� �����Ѵٸ�
			previous = curr_num;	//�����ڸ� �����ص�
			curr_num = hash_table[curr_num].link;
			if (strcmp(hash_table[curr_num].name, data) == 0) {	//������ ���ڵ带 ã�Ҵٸ�
				success = 1;	
				break;
			}	
		}

		if (success == 1) {	//���ڵ带 ã���� �� 
			rec_count = del_middle(curr_num, previous,choose);	//del_middle�Լ� ȣ���� ���� �� moveȽ�� ���Ϲ���
			return rec_count;
		}
		else {	//������ �����Ͱ� �ִ� ���ڵ尡 ���ٸ�
			printf("�����͸� ã�µ� �����Ͽ����ϴ�\n");
			return 0;
		}
	}
		
}

int del_start(int s, int choose) {	//s�� �������ϴ� ���ڵ尡 �ִ� ��ġ
	int previous;		//linkŸ�� �Ѿ �� �����ڸ� ������� ����
	int previous_last;	//�� ���� ����� �����ڸ� �˱����� ����
	int curr_num = s;
	int last_num;		//Ư�� HA�� ���� �� ���� ���ڵ带 ������� ����
	int found = 0; // HA�� s�� ��尡 s��ġ�� link�� ����Ű�� ��忡������ �� �ִ� �� Ȯ�� 1�̸� ���� 0�̸� ����
	int rec_count = 0;	//record move Ƚ��

	previous = curr_num;	

	//s���ķ� HA=s�� ���ڵ尡 �����ϴ��� ����
	while (hash_table[curr_num].link) {	//link�� �������� �ʴ� ���ڵ尡 ���� �� ���� �ݺ�
		previous = curr_num;	//������ ����
		curr_num = hash_table[curr_num].link;				
		if (hash_table[curr_num].HA == s) {	//HomeAdrress�� s�� ���� ���� ���ڵ带 ã������ ������
			previous_last = previous;	//HomeAddress�� s�� ���ڵ带 ã�� ������ �� �����ڸ� ����
			found = 1;
			last_num = curr_num;	//HomeAddress�� s�� ���ڵ带 ã�� ������ �� �ּҸ� last_num�� ����
		}
	}
	if (found == 1) {	//HomeAddress�� s�� ���ڵ尡 �ִٸ� 
		//�� ���� ���� ���ڵ带 s�� ��ġ�� ���ڵ忡 ����
		strcpy(hash_table[s].name, hash_table[last_num].name);
		hash_table[s].monincome = hash_table[last_num].monincome;
		rec_count++;
		//last_num�� �ִ� �ڸ��� �� �����ڸ� �Ű������� del_middle ȣ��
		del_middle(last_num, previous_last, choose);
		
	}
	else {	//ü���� �Ʒ���ġ S�� �̿��ϴ� ��尡 ���� ( s�� ü���� ������ ���ڵ� �� �� )
		//s�� ���ڵ� ���� ����� ���̰��� �־���
		strcpy(hash_table[s].name, "-");
		hash_table[s].monincome = NULL;
		hash_table[s].HA = NULL;
		hash_table[s].link = NULL;
		hash_table[previous].link = NULL;	//�������� link�� ������

		if (R < s) { //R�� s���� ���� ��ġ�� ���� ��
			R = s + 1;	//���� ��ĭ�� ã�� �� s���� ���� ��
		}
		if (choose == 0) {	//�ϰ����������� ������� �ʰ� �ϱ� ����
			printf("Position of the deleted record = %d, Relocation �� = %d\n", s, rec_count);
		}
		return rec_count;
	}
}

int del_middle(int s, int p, int choose) {	//s�� �������� ���ڵ尡 �ִ� ��ġ, p�� �� ������
	int curr_num = s;
	int found = 0; //��ġ s�� link�� ����Ű�� ��忡�� ����� HA�� s�� ��尡 �� �ִ��� ã�� ���� 1�̸� ã��
	int last_num;
	int locations[100];	//s���� �� ���� ���ڵ��� �ּҵ��� ������� �迭
	int previous; //������
	int previous_last;	//�߰��� ������ ����� ������
	int Included = 0;	//HA�� ���� locations�� ���ԵǴ��� �ȵǴ��� 1�̸� ����
	int i;

	while (hash_table[curr_num].link) {	//link�� ���� ���ڵ尡 ���� �� ���� �ݺ�
		curr_num = hash_table[curr_num].link;
		if (hash_table[curr_num].HA == s) {	//HA�� s�� ���ڵ� �� ���� ���� ���ڵ带 ã��
			found = 1;
			last_num = curr_num;
		}
	}
	curr_num = s;
	last_num = -1;	//last_num �ʱ�ȭ ����

	if (found == 1) {	//HA�� s�� ���ڵ带 ã�Ҵٸ�
		for (i = 0; hash_table[curr_num].name[0]!='-'; i++) {	//�� ���ڵ尡 ������ ������ ����
			locations[i] = curr_num;	//�� ��ġ�� locations �迭�� ����
			if (!hash_table[curr_num].link)		//ü���� ������ ���ڵ�� break
				break;
			curr_num = hash_table[curr_num].link;	//link�� �ִٸ� ���� ���ڵ�� �Ѿ
		}
		curr_num = s;
		while (hash_table[curr_num].link) {	//ü���� �� ���ڵ尡 ���ö����� �ݺ�
			Included = 0;	// included ���� �ʱ�ȭ
			previous = curr_num;
			curr_num = hash_table[curr_num].link;
			for (int j = 0; j < i; j++) {	//s ���ķ� locations���� �ִ� �ּҵ��� HA�� ���� ���ڵ尡 �ִ�����
				if (hash_table[curr_num].HA == locations[j]) {	//HA�� locations�� �ִ� �迭�� ���Եȴٸ�
					Included = 1;
					break;
				}
			}
			if (Included == 1) {//���Եȴٸ� �ƹ� ���� ���� ����

			}
			else {	//���Ծȵȴٸ� �����ڿ� ��ġ�� ����
				previous_last = previous;
				last_num = curr_num;
			}
		}
		if (last_num == -1) {	//s������ ��� ���ڵ尡 ���Եȴٸ�
			hash_table[p].link = NULL;	//ü���� �и���
			del_start(s,choose);	//�� �� s��ġ������ del_start�� ȣ��
		}
		else {	//���ԾȵǴ� ���ڵ尡 �ִٸ�
			//�� ���ڵ�� s��ġ�� �͵� �ٸ� ���ڵ忡 ������ ��ġ�� �����Ƿ�
			//s��ġ�� ���� �� last_num��ġ���� �� �����ڸ� �Ű��������ϴ� del_middle ȣ��
			strcpy(hash_table[s].name, hash_table[last_num].name);
			hash_table[s].HA = hash_table[last_num].HA;
			hash_table[s].monincome = hash_table[last_num].monincome;
			rec_count++;
			del_middle(last_num, previous_last, choose);	
		}


	}
	else {//HA�� s�� ���ڵ尡 ���ٸ� 
		//�� �������� link�� s��ġ�� link�� �־��ְ�
		//s��ġ ���ڵ带 ����� ���̰��� �־���
		hash_table[p].link = hash_table[s].link;
		strcpy(hash_table[s].name, "-");
		hash_table[s].link = NULL;
		hash_table[s].monincome = NULL;
		hash_table[s].HA = NULL;
		if (R < s) {
			R = s + 1;
		}
		if (choose == 0) {	//�ϰ������� ���� ������� �ʰ� �ϱ� ����
			printf("Position of the deleted record = %d, Relocation �� = %d\n", s, rec_count);
		}
		return rec_count;
	}


}

int checkEmpty() {	//�� ���ڵ带 ã�� �Լ�
	while (R >= 0) {
		R--;
		
		if (hash_table[R].name[0] == '-')	//���ڵ带 ã�Ҵٸ� �� ��ġ�� ����
			return R;
		
	}
	//R�� 0���� �۴ٸ� 
	printf("���̺��� �� �� �ֽ��ϴ�!!\n");
	return -1;
}

int hash(char recname[]) {	//�ؽ��Լ�
	unsigned char u;
	int HA, j, leng, halfleng;
	long sum = 0;
	int A[100];

	leng = strlen(recname);
	for (j = 0; j < leng; j++) {
		u = recname[j];
		A[j] = u;
	}
	halfleng = leng / 2;
	for (j = 0; j < halfleng; j++) {
		sum = sum + (A[j] + A[leng - 1 - j] * A[(leng - 1) / 2]);
	}
	if (leng % 2 == 1)
		sum = sum + A[halfleng] * A[halfleng + 1] * A[(leng - 1) / 2];
	HA = sum % tbl_Size;
	return HA;
}

void delBundle() {	//3������ �����͸� ������ ó���������� �о� �ϰ� �����ϴ� �Լ�
	FILE* fp = fopen("Companies_Korean.txt", "r");
	char *get_err = NULL;
	char buffer[100];	//�����͸� ���� ���۹迭
	int check = 0;	//�����Ͱ� ���� �������� �˱� ���� ����
	int count = 30000;	//�ݺ� ī����
	int total_move=0;	//3������ ���� �� �Ͼ �� moveȽ���� ���� ����

	if (!fp) {	//������ ���ٸ�
		printf("�������� �ʴ� �����Դϴ�...\n");
		return;
	}
	for(int i =0; i<count;i++) {	//3���� �ݺ�

		get_err = fgets(buffer, sizeof(buffer), fp);

		if (!get_err) {
			if (check == 1) {
				break;
			}
			//������ ������ ���� ��� ( ó���� get_err�� NULL�� ��� )
			printf("������ ���� �����Դϴ�.\n");
			return;
		}
		
		for (int j = 0; j < strlen(buffer); j++) {	
			
			if (buffer[j] == '\n') {
				buffer[j] = '\0';
			}
		}
		
		total_move += delete(buffer,1);	//delete �Լ��� ȣ���ϰ� move Ƚ���� ���Ϲ޾� total_move�� ������
		check = 1;
	}

	printf("�ϰ������� �����Ͽ����ϴ�. Total Relocation = %d\n", total_move);
	fclose(fp);
}


void getProbe() {	//ȭ���� ó������ �ϳ��� �о� ��� ���κ� ���� ����ϴ� ���� ���� �Լ�
	FILE* fp = fopen("Companies_Korean.txt", "r");
	char *get_err = NULL;
	char buffer[100];
	int check = 0;
	int end = 0;	//������ ���������� ���� 1�̸� ��
	int total_probe = 0;	//�� probe Ƚ��
	double average_probe;	//��� probe
	int num_names=0;		//�� ���� �������� ��

	if (!fp) {
		printf("�������� �ʴ� �����Դϴ�...\n");
		return;
	}
	while(1){

		get_err = fgets(buffer, sizeof(buffer), fp);

		if (!get_err) {
			if (check == 1) {	//������ ������ ������ ��
				break;
			}
			//������ ������ ���� ��� ( ó���� get_err�� NULL�� ��� )
			printf("������ ���� �����Դϴ�.\n");
			return;
		}
		for (int j = 0; j < strlen(buffer); j++) {
			if (buffer[j] == '\0')	//���� �����Ͱ� ������ �� �����Ͷ�� 
				end = 1;
			if (buffer[j] == '\n') {
				buffer[j] = '\0';
			}
		}
		total_probe += searchData(buffer, 1);//search�Լ��� ȣ���ϰ� probeȽ���� ���Ϲ޾� total_probe�� ������
		if (end == 1)
			break;
		check = 1;
		num_names++;	
	}
	average_probe = (double)total_probe / num_names;	//��� ���κ� ���

	printf("Total_probe = %d   Num_names = %d   Average_probe = %.2lf\n", total_probe, num_names, average_probe);

	fclose(fp);
}

int main() {
	char ins[20];
	char data[20];
	setStruct();

	while (1) {
		data[0] = '-';	//data�� ó���� ���̷� ����� ���� i r d��ɾ���� �����͸� �� �Է����� ��, t v e ��ɾ�� �����͸� �Է����� �� ������ ��������

		printf("����� �Է����ּ���. ( i : ����, r : Ž��, d : ����, t : �ϰ�����, v : ���� Ž��, e : ���� ) : ");

		for (int i = 0;i<sizeof(ins); i++) {	//��ɾ� ���� �ޱ�	
			ins[i] = getchar();
			if (ins[i] == '\n') {
				ins[i] = '\0';
				break;
			}
			if (ins[i] == ' ') {	//������ ������ �ʿ��ϴٸ� ������ ���� �ޱ�
				ins[i] = '\0';
				for (int j = 0; j < sizeof(data); j++) {
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
			if (data[0] == '-') {
				printf("�߸��� �Է��Դϴ�. i��ɾ�� �����Ͱ� �� �ʿ��մϴ�\n");
				continue;
			}
			else {
				insertData(data);
			}
		}
		else if (strcmp(ins, "r") == 0) {	//search
			if (data[0] == '-') {
				printf("�߸��� �Է��Դϴ�. r��ɾ�� �����Ͱ� �� �ʿ��մϴ�\n");
				continue;
			}
			else {
				searchData(data, 0);
			}
		}
		else if (strcmp(ins, "d") == 0) {	//deletion
			if (data[0] == '-') {
				printf("�߸��� �Է��Դϴ�. d��ɾ�� �����Ͱ� �� �ʿ��մϴ�\n");
				continue;
			}
			else {
				delete(data, 0);
			}
		}
		else if (strcmp(ins, "t") == 0) {	//�ϰ�����
			if (data[0]=='-') {
				delBundle();
			}
			else {
				printf("�߸��� �Է��Դϴ�. t��ɾ�� �����͸� �Է��� �� �����ϴ�\n");
				continue;
			}
			
		}
		else if (strcmp(ins, "v") == 0) {	//probe ���ϱ�
			if (data[0]=='-') {
				getProbe();
				
			}
			else {
				printf("�߸��� �Է��Դϴ�. v��ɾ�� �����͸� �Է��� �� �����ϴ�\n");
				continue;
			}
			
		}
		else if (strcmp(ins, "e") == 0) {	//���α׷� ����
			if (data[0]=='-') {
				printf("���α׷��� �����մϴ�....\n");
				return 0;			
			}
			else {
				printf("�߸��� �Է��Դϴ�. e��ɾ�� �����͸� �Է��� �� �����ϴ�\n");
				continue;
			}
			
		}
		else {	//�߸��� ��ɾ �Է����� ��
			printf("�߸��� ��ɾ� �Դϴ�.\n");	
		}
	}

}