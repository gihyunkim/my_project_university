#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define tbl_Size 37533		//hash-table의 크기
#pragma warning (disable:4996)

typedef struct element {	//데이터를 담을 구조체
	char name[100];	//회사명
	int monincome;	//랜덤으로 정해진 매출액
	int link;		//서로 링크할 때 쓸 링크 변수
	int HA;			//HomeAddress를 넣을 변수
}type_record;

type_record hash_table[tbl_Size];	//해시테이블 선언

long R = tbl_Size;	//빈 테이블을 빨리 찾기 위해 쓸 R변수 ( 비어있는 제일 뒤의 인덱스를 가리키고 있다 )

int rec_count = 0;	//record move 횟수( 삭제할 때 발생한 레코드간 이동 횟수 )

void setDummy() {	//table의 Dummy record 저장

	for (int i = 0; i < tbl_Size; i++) {
		hash_table[i].name[0] = '-';	//이름이 key값이므로 제일 처음 인덱스 0에 -를 더미로 다 넣어놓음
	}

}
int checkEmpty();	//해시테이블 내 빈 레코드를 찾아 반환하는 함수
int hash(char recname[]);	//해시함수 ( 문자열을 숫자로 바꿔 반환해주는 해시 )

void setStruct() {

	FILE* fp = fopen("Companies_Korean.txt", "r");
	char *get_err = NULL;
	type_record element;
	int empty;			//빈 레코드의 주소를 받는 변수
	int override = 0;	//1이면 중복
	int hash_num;	//파일에서 읽어온 데이터의 해시함수값
	int curr_num;	//링크로 이어져있을 시의 현재 주소를 알려주는 변수
	int check = 0; // 내용 비어있는지 확인 여부 1면 내용 있음 0이면 내용 없음
	int i = 0;
	int end = 0;	//파일이 끝났는지 체크 변수 0이면 false 1이면 true

	srand(time(NULL));		//랜덤값을 실행시마다 바꿔주는 함수
	setDummy();				//더미값 입력 함수

	if (!fp) {	//파일이 없을 때의 에러
		printf("존재하지 않는 파일입니다...\n");
		return;
	}
	while (1) {

		get_err = fgets(element.name, sizeof(element.name), fp);	//파일에서 한 줄을 읽어옴

		if (!get_err) {	
			if (check == 1) {	//파일의 내용이 끝났을 때
				return;
			}
			//파일의 내용이 없는 경우 ( 처음에 get_err가 NULL일 경우 )
			printf("내용이 없는 파일입니다.");
			return;
		}
		for (int j = 0; j < strlen(element.name); j++) {	//fgets에서 읽어올 시 \n을 없애주기 위함
			if (element.name[j] == '\n') {		//마지막 \n을 \0로 바꿔주어 문자열로 만듬
				element.name[j] = '\0';
			}
		}

		element.monincome = 10000000 + rand() % 90000001;	//범위 천만~1억
		hash_num = hash(element.name);	//해시함수에서 해시값을 반환시켜 hash_num에 입력
		curr_num = hash_num;	//현재의 주소가 가지는 해시값

		if (hash_table[hash_num].name[0] == '-') {	//HA가 hash_num인 데이터가 이게 처음이라면
			for (int j = 0; j < strlen(element.name); j++) {	//파일의 끝을 구별하기 위함
				if (element.name[j] == '\0') {//만약 이 데이터가 파일의 끝 데이터라면
					end = 1;
				}
				hash_table[hash_num].name[j] = element.name[j];	//해시테이블에 레코드 값을 넣어줌
			}
			hash_table[hash_num].monincome = element.monincome;
			hash_table[hash_num].HA = hash_num;
		}
		else {//처음이 아닌 경우

			while (1) {	//link가 없는 HA가 hash_num인 주소를 찾아감
				if (strcmp(hash_table[curr_num].name, element.name) == 0) {	//중복되는 값이 있을 시
					override = 1;	
					break;
				}
				if (!hash_table[curr_num].link)	//link가 없다면 break
					break;
				curr_num = hash_table[curr_num].link;	//있다면 그 link를 타고 감
			}
			if (override == 1) {	//중복이라면 버리고 다음 데이터를 받아온다
				i++;
				continue;
			}
			empty = checkEmpty();	//빈 곳이 있는지를 찾는다

			for (int j = 0; j < strlen(element.name); j++) {	
				if (element.name[j] == '\0') {	//만약 이 데이터가 파일의 끝 데이터라면
					end = 1;
				}
				hash_table[empty].name[j] = element.name[j];	//빈 해시테이블에 레코드 값을 넣어줌
			}
			hash_table[empty].monincome = element.monincome;
			hash_table[empty].HA = hash_num;
			hash_table[curr_num].link = empty;
		}

		if (end == 1) {	//파일의 마지막 데이터였다면 반복문을 끝냄
			break;
		}

		i++;

		check = 1;	//데이터가 한 개라도 있었는지 확인

	}

	fclose(fp);

}
int searchData(char data[30], int choose);	//탐색 함수 choose가 0이면 그냥 탐색 1이면 getprobe 함수
void insertData(char data[30]) {	//데이터를 받아 삽입하는 함수
	int hash_num;	//그 데이터의 해시 값을 받을 변수
	int empty;		//빈 테이블 주소를 받을 변수
	int curr_num;	//링크로 이어져있을 시의 현재 주소를 알려주는 변수
	hash_num = hash(data);	//해시함수로 해시값을 반환받음
	curr_num = hash_num;	

	if (hash_table[hash_num].name[0] == '-') {	//HA가 hash_num인 데이터가 이게 처음이라면
		strcpy(hash_table[hash_num].name, data);	//데이터를 그 해시테이블에 넣음
		hash_table[hash_num].monincome = 10000000 + rand() % 90000001;
		printf("Success in insertion. Position = %d\n", hash_num);
	}
	else {	//처음이 아닌 경우
		while (1) {	//link가 없는 HA가 hash_num인 주소를 찾아감
			if (strcmp(hash_table[curr_num].name, data) == 0) {	//중복되는 데이터라면 리턴
				printf("이미 등록된 회사입니다....\n");
				return;
			}
			if (!hash_table[curr_num].link)	//link가 없다면
				break;
			curr_num = hash_table[curr_num].link;	//있다면 link를 타고 감
		}

		empty = checkEmpty();	//해시테이블 내 빈레코드를 찾아 주소반환
		//빈 레코드에 데이터를 넣어줌
		strcpy(hash_table[empty].name, data);
		hash_table[empty].monincome = 10000000 + rand() % 90000001;
		hash_table[curr_num].link = empty;
		printf("Success in insertion. Position = %d\n", empty);
	}


	return;

}

int searchData(char data[30], int choose) {	//choose가 0이면 그냥 search 명령, 1이면 총 probe계산할 때 사용
	int hash_num;
	int probe = 1;	//probe변수 ( 몇 곳의 위치에서 조사를 시행하였냐를 담는 변수 )
	int curr_num; //현재 위치
	hash_num = hash(data);
	curr_num = hash_num;

	if (hash_table[hash_num].name[0] == '-') {	//테이블이 비어있다면
		printf("데이터가 존재하지않습니다...\n");
		return -1;
	}
	else {
		while (1) {
			if (strcmp(data, hash_table[curr_num].name) == 0) {	//데이타를 찾았다면 성공문장 출력 후 probe 수 리턴
				if (choose == 0) {	//총 probe계산시에는 출력하지않음
					printf("Position = %d, probe = %d\n", curr_num, probe);
				}
				return probe;
			}
			else {
				if (hash_table[curr_num].link) {//link가 있다면 link를 타고감
					curr_num = hash_table[curr_num].link;
					probe++;	//probe 수 1 증가
				}
				else {//데이터를 찾지 못함
					printf("데이터가 존재하지않습니다...\n");
					return -1;
				}
			}
		}
	}
}

int del_start(int curr_num, int choose);	//HA가 자신의 주소인 레코드를 지울 때의 함수 
											//( 즉 특정 HA값을 갖는 레코드 중 처음 레코드 )
int del_middle(int s, int p, int choose);	//특정 HA값을 갖는 레코드 중 중간에 있는 레코드를 지울 때의 함수

int delete(char data[30], int choose) {	//choose 가 0이면 그냥 delete 1이면 일괄삭제
	int hash_num;
	int curr_num;
	int previous;		//선행자의 위치를 담을 변수
	int success = 0;	//data와 같은 이름을 찾았는지 여부 1이면 성공 0이면 실패

	rec_count = 0;	//move 횟수 초기화
	hash_num = hash(data);
	curr_num = hash_num;

	if (strcmp(hash_table[hash_num].name, data)==0) {	//삭제할 데이터가 HA=hash_num인 레코드들 중 첫 레코드에 있다면
		rec_count = del_start(hash_num,choose);	//del_start함수를 부르고 삭제 중 move횟수를 리턴받음
		return rec_count;
	}
	else {

		while (hash_table[curr_num].link) {	//link가 존재한다면
			previous = curr_num;	//선행자를 저장해둠
			curr_num = hash_table[curr_num].link;
			if (strcmp(hash_table[curr_num].name, data) == 0) {	//삭제할 레코드를 찾았다면
				success = 1;	
				break;
			}	
		}

		if (success == 1) {	//레코드를 찾았을 시 
			rec_count = del_middle(curr_num, previous,choose);	//del_middle함수 호출해 삭제 중 move횟수 리턴받음
			return rec_count;
		}
		else {	//삭제할 데이터가 있는 레코드가 없다면
			printf("데이터를 찾는데 실패하였습니다\n");
			return 0;
		}
	}
		
}

int del_start(int s, int choose) {	//s는 지워야하는 레코드가 있는 위치
	int previous;		//link타고 넘어갈 때 선행자를 담기위한 변수
	int previous_last;	//맨 나중 노드의 선행자를 알기위한 변수
	int curr_num = s;
	int last_num;		//특정 HA를 갖는 맨 나중 레코드를 담기위한 변수
	int found = 0; // HA가 s인 노드가 s위치의 link가 가리키는 노드에서부터 더 있는 지 확인 1이면 있음 0이면 없음
	int rec_count = 0;	//record move 횟수

	previous = curr_num;	

	//s이후로 HA=s인 레코드가 존재하는지 여부
	while (hash_table[curr_num].link) {	//link가 존재하지 않는 레코드가 나올 때 까지 반복
		previous = curr_num;	//선행자 저장
		curr_num = hash_table[curr_num].link;				
		if (hash_table[curr_num].HA == s) {	//HomeAdrress가 s인 제일 나중 레코드를 찾기위한 가정문
			previous_last = previous;	//HomeAddress가 s인 레코드를 찾을 때마다 그 선행자를 저장
			found = 1;
			last_num = curr_num;	//HomeAddress가 s인 레코드를 찾을 때마다 그 주소를 last_num에 저장
		}
	}
	if (found == 1) {	//HomeAddress가 s인 레코드가 있다면 
		//그 제일 나중 레코드를 s의 위치의 레코드에 복사
		strcpy(hash_table[s].name, hash_table[last_num].name);
		hash_table[s].monincome = hash_table[last_num].monincome;
		rec_count++;
		//last_num이 있던 자리와 그 선행자를 매개변수로 del_middle 호출
		del_middle(last_num, previous_last, choose);
		
	}
	else {	//체인의 아래위치 S를 이용하는 노드가 없다 ( s가 체인의 마지막 레코드 일 시 )
		//s의 레코드 값을 지우고 더미값을 넣어줌
		strcpy(hash_table[s].name, "-");
		hash_table[s].monincome = NULL;
		hash_table[s].HA = NULL;
		hash_table[s].link = NULL;
		hash_table[previous].link = NULL;	//선행자의 link도 지워줌

		if (R < s) { //R이 s보다 낮은 위치에 있을 시
			R = s + 1;	//다음 빈칸을 찾을 때 s부터 보게 함
		}
		if (choose == 0) {	//일괄삭제에서는 출력하지 않게 하기 위함
			printf("Position of the deleted record = %d, Relocation 수 = %d\n", s, rec_count);
		}
		return rec_count;
	}
}

int del_middle(int s, int p, int choose) {	//s는 지워야할 레코드가 있는 위치, p는 그 선행자
	int curr_num = s;
	int found = 0; //위치 s의 link가 가리키는 노드에서 출발해 HA가 s인 노드가 더 있는지 찾는 변수 1이면 찾음
	int last_num;
	int locations[100];	//s포함 그 이후 레코드의 주소들을 담기위한 배열
	int previous; //선행자
	int previous_last;	//발견한 마지막 노드의 선행자
	int Included = 0;	//HA가 집합 locations에 포함되는지 안되는지 1이면 포함
	int i;

	while (hash_table[curr_num].link) {	//link가 없는 레코드가 나올 때 까지 반복
		curr_num = hash_table[curr_num].link;
		if (hash_table[curr_num].HA == s) {	//HA가 s인 레코드 중 제일 나중 레코드를 찾음
			found = 1;
			last_num = curr_num;
		}
	}
	curr_num = s;
	last_num = -1;	//last_num 초기화 해줌

	if (found == 1) {	//HA가 s인 레코드를 찾았다면
		for (i = 0; hash_table[curr_num].name[0]!='-'; i++) {	//빈 레코드가 나오기 전까지 돌림
			locations[i] = curr_num;	//그 위치를 locations 배열에 넣음
			if (!hash_table[curr_num].link)		//체인의 마지막 레코드면 break
				break;
			curr_num = hash_table[curr_num].link;	//link가 있다면 다음 레코드로 넘어감
		}
		curr_num = s;
		while (hash_table[curr_num].link) {	//체인의 끝 레코드가 나올때까지 반복
			Included = 0;	// included 변수 초기화
			previous = curr_num;
			curr_num = hash_table[curr_num].link;
			for (int j = 0; j < i; j++) {	//s 이후로 locations내에 있는 주소들을 HA로 갖는 레코드가 있는지봄
				if (hash_table[curr_num].HA == locations[j]) {	//HA가 locations에 있는 배열에 포함된다면
					Included = 1;
					break;
				}
			}
			if (Included == 1) {//포함된다면 아무 동작 하지 않음

			}
			else {	//포함안된다면 선행자와 위치를 저장
				previous_last = previous;
				last_num = curr_num;
			}
		}
		if (last_num == -1) {	//s이후의 모든 레코드가 포함된다면
			hash_table[p].link = NULL;	//체인을 분리함
			del_start(s,choose);	//그 후 s위치에서의 del_start를 호출
		}
		else {	//포함안되는 레코드가 있다면
			//그 레코드는 s위치에 와도 다른 레코드에 영향을 끼치지 않으므로
			//s위치에 복사 후 last_num위치에서 그 선행자를 매개변수로하는 del_middle 호출
			strcpy(hash_table[s].name, hash_table[last_num].name);
			hash_table[s].HA = hash_table[last_num].HA;
			hash_table[s].monincome = hash_table[last_num].monincome;
			rec_count++;
			del_middle(last_num, previous_last, choose);	
		}


	}
	else {//HA가 s인 레코드가 없다면 
		//그 선행자의 link를 s위치의 link에 넣어주고
		//s위치 레코드를 지우고 더미값을 넣어줌
		hash_table[p].link = hash_table[s].link;
		strcpy(hash_table[s].name, "-");
		hash_table[s].link = NULL;
		hash_table[s].monincome = NULL;
		hash_table[s].HA = NULL;
		if (R < s) {
			R = s + 1;
		}
		if (choose == 0) {	//일괄삭제일 때는 출력하지 않게 하기 위함
			printf("Position of the deleted record = %d, Relocation 수 = %d\n", s, rec_count);
		}
		return rec_count;
	}


}

int checkEmpty() {	//빈 레코드를 찾는 함수
	while (R >= 0) {
		R--;
		
		if (hash_table[R].name[0] == '-')	//빈레코드를 찾았다면 그 위치를 리턴
			return R;
		
	}
	//R이 0보다 작다면 
	printf("테이블이 꽉 차 있습니다!!\n");
	return -1;
}

int hash(char recname[]) {	//해시함수
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

void delBundle() {	//3만개의 데이터를 파일의 처음에서부터 읽어 일괄 삭제하는 함수
	FILE* fp = fopen("Companies_Korean.txt", "r");
	char *get_err = NULL;
	char buffer[100];	//데이터를 담을 버퍼배열
	int check = 0;	//데이터가 없는 파일인지 알기 위한 변수
	int count = 30000;	//반복 카운터
	int total_move=0;	//3만번의 삭제 중 일어난 총 move횟수를 담을 변수

	if (!fp) {	//파일이 없다면
		printf("존재하지 않는 파일입니다...\n");
		return;
	}
	for(int i =0; i<count;i++) {	//3만번 반복

		get_err = fgets(buffer, sizeof(buffer), fp);

		if (!get_err) {
			if (check == 1) {
				break;
			}
			//파일의 내용이 없는 경우 ( 처음에 get_err가 NULL일 경우 )
			printf("내용이 없는 파일입니다.\n");
			return;
		}
		
		for (int j = 0; j < strlen(buffer); j++) {	
			
			if (buffer[j] == '\n') {
				buffer[j] = '\0';
			}
		}
		
		total_move += delete(buffer,1);	//delete 함수를 호출하고 move 횟수를 리턴받아 total_move에 더해줌
		check = 1;
	}

	printf("일괄삭제에 성공하였습니다. Total Relocation = %d\n", total_move);
	fclose(fp);
}


void getProbe() {	//화일의 처음부터 하나씩 읽어 평균 프로브 수를 출력하는 성능 측정 함수
	FILE* fp = fopen("Companies_Korean.txt", "r");
	char *get_err = NULL;
	char buffer[100];
	int check = 0;
	int end = 0;	//파일이 끝났는지의 여부 1이면 끝
	int total_probe = 0;	//총 probe 횟수
	double average_probe;	//평균 probe
	int num_names=0;		//총 읽은 데이터의 수

	if (!fp) {
		printf("존재하지 않는 파일입니다...\n");
		return;
	}
	while(1){

		get_err = fgets(buffer, sizeof(buffer), fp);

		if (!get_err) {
			if (check == 1) {	//파일의 내용이 끝났을 때
				break;
			}
			//파일의 내용이 없는 경우 ( 처음에 get_err가 NULL일 경우 )
			printf("내용이 없는 파일입니다.\n");
			return;
		}
		for (int j = 0; j < strlen(buffer); j++) {
			if (buffer[j] == '\0')	//읽은 데이터가 파일의 끝 데이터라면 
				end = 1;
			if (buffer[j] == '\n') {
				buffer[j] = '\0';
			}
		}
		total_probe += searchData(buffer, 1);//search함수를 호출하고 probe횟수를 리턴받아 total_probe에 더해줌
		if (end == 1)
			break;
		check = 1;
		num_names++;	
	}
	average_probe = (double)total_probe / num_names;	//평균 프로브 계산

	printf("Total_probe = %d   Num_names = %d   Average_probe = %.2lf\n", total_probe, num_names, average_probe);

	fclose(fp);
}

int main() {
	char ins[20];
	char data[20];
	setStruct();

	while (1) {
		data[0] = '-';	//data의 처음을 더미로 만들어 놓음 i r d명령어에서는 데이터를 안 입력했을 시, t v e 명령어에서 데이터를 입력했을 시 에러를 내기위함

		printf("명령을 입력해주세요. ( i : 삽입, r : 탐색, d : 삭제, t : 일괄삭제, v : 파일 탐색, e : 종료 ) : ");

		for (int i = 0;i<sizeof(ins); i++) {	//명령어 변수 받기	
			ins[i] = getchar();
			if (ins[i] == '\n') {
				ins[i] = '\0';
				break;
			}
			if (ins[i] == ' ') {	//데이터 변수가 필요하다면 데이터 변수 받기
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
				printf("잘못된 입력입니다. i명령어는 데이터가 꼭 필요합니다\n");
				continue;
			}
			else {
				insertData(data);
			}
		}
		else if (strcmp(ins, "r") == 0) {	//search
			if (data[0] == '-') {
				printf("잘못된 입력입니다. r명령어는 데이터가 꼭 필요합니다\n");
				continue;
			}
			else {
				searchData(data, 0);
			}
		}
		else if (strcmp(ins, "d") == 0) {	//deletion
			if (data[0] == '-') {
				printf("잘못된 입력입니다. d명령어는 데이터가 꼭 필요합니다\n");
				continue;
			}
			else {
				delete(data, 0);
			}
		}
		else if (strcmp(ins, "t") == 0) {	//일괄삭제
			if (data[0]=='-') {
				delBundle();
			}
			else {
				printf("잘못된 입력입니다. t명령어에는 데이터를 입력할 수 없습니다\n");
				continue;
			}
			
		}
		else if (strcmp(ins, "v") == 0) {	//probe 구하기
			if (data[0]=='-') {
				getProbe();
				
			}
			else {
				printf("잘못된 입력입니다. v명령어에는 데이터를 입력할 수 없습니다\n");
				continue;
			}
			
		}
		else if (strcmp(ins, "e") == 0) {	//프로그램 종료
			if (data[0]=='-') {
				printf("프로그램을 종료합니다....\n");
				return 0;			
			}
			else {
				printf("잘못된 입력입니다. e명령어에는 데이터를 입력할 수 없습니다\n");
				continue;
			}
			
		}
		else {	//잘못된 명령어를 입력했을 시
			printf("잘못된 명령어 입니다.\n");	
		}
	}

}