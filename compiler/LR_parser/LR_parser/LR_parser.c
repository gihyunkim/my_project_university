#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MaxSymbols 200	//number of symbols should smaller than this
#define MaxRules 100	//number of rules should be smaller than this
#define MaxNumberOfStates 200	//maximum number of state

#define URT 48     // �ν��� �� ���� ��ū�� ��Ÿ���� ��ū ��ȣ. ���� ��ū ��ȣ�� ?? �� �����־�� ��.
#define EOF_TOK 48	//EOF Token

typedef struct tkt { // �ϳ��� ��ū�� ��Ÿ���� ����ü.
	int kind;  // kind : ��ū�� ������ ��Ÿ��, �� ��ū ��ȣ�� ����.
	char sub_kind[3];  // relop ��ū�� ��� �ٽ� �����ϴµ� �̿��.
						 // NUM ��ū�� ���� ��������("in") �Ǽ�������("do") ����.
	int sub_data; // ID ��ū�� �ɺ����̺�Ʈ�� ��ȣ, ���� ���� ���� ������.
	double rnum;  // �Ǽ��� ��� 
	char str[20]; // ��ū�� �����ϴ� ��Ʈ��.  // �Ƹ��� �� �ʵ�� �̿���� �ʴ� �� ����.
} tokentype;

typedef struct ssym {
	int kind; // 0 if terminal; 1 if nonterminal; -1 if dummy symbol indicating the end mark.
	int no; // the unique index of a symbol.
	char str[10];	//�ɺ��� string
} sym;  // definition symbols 

typedef struct orule {
	sym leftside;
	sym rightside[10];
	int rleng;	//RHS�� �ɺ��� ����
}onerule;

typedef char oneword[50];

//keyword table
//ù��° keyword "if"�� token index�� 31,
// �ٸ� Ű������ token index�� �� ������ �̿��Ͽ� ����
char keywords[17][50] =
{ "if", "else" ,"while","do","for", "include","define",
  "typedef","struct","int","char","float","double","void",
	"return" , "case", "then" };

int total_keywords = 17; //keyword�� ��

int Idx_First_keyword = 31; //ù Ű������ token index


//symobol table
typedef struct symtbl { oneword idstr; int attribute; }sym_ent;
//�ɺ����̺��� �� ��Ʈ�� ����
sym_ent symtbl[500];
int total_ids = 0;	//�ɺ����̺��� ������ ���� ��Ʈ�� ��ȣ

typedef struct typeitemnode *ty_ptr_item_node;
typedef struct typeitemnode {
	int RuleNum;
	int DotNum;
	ty_ptr_item_node link;
}type_item;

//state node : Goto graph ���� ����� state node ����ü
typedef struct statenode* state_node_ptr;
typedef struct statenode {
	int id;	//�ڽ��� ID
	int	item_cnt;	//�����ϰ� �ִ� Item���� ��
	ty_ptr_item_node	item_start;	//�����ϰ� �ִ� Item_list�� �����ּ�
	state_node_ptr	next;	//���� state���� arc
}state_node;

//Arc_node : Item list���� ����� ����ü
typedef struct itemnode * Arc_node_ptr;
typedef struct itemnode {
	int	from_state;	//���ȣ
	int to_state;	//����ġ
	sym	gram_sym;	//���� �ɺ�
	Arc_node_ptr link;
}Arc_node;

//goto set
typedef struct gotoset* goto_set_ptr;
typedef struct gotoset {
	Arc_node_ptr Arc_list;
	state_node_ptr State_Node_List;
}goto_set;

typedef struct cell_action_tbl {
	char Kind;	//s, r, a, e �� �� ����
	int num;	//s�̸� ������Ʈ ��ȣ, r�̸� �� ��ȣ�� ��Ÿ��.
}ty_Cell_Action_Table;

//definition Parse Tree node. ���� �����ɺ��� ����. �׷���, �� ���� LR STACK���� ����.
//�׷��� LR stack���� state��ȣ�� ���� ��. 
//�׷��� node�� �����ɺ��� state�� �ִ� 2���� �뵵�� �����
typedef struct nodetype* Ty_Node_Ptr;
typedef struct nodetype {
	int state;	//-1�̸� grammar symbol, 0�̻��̸� state�� ������ ��
	sym nodesym;	//�ܸ� ��ȣ�� ��ܸ� ��ȣ�� ����
	int child_cnt;	//�ڽ��� ��
	Ty_Node_Ptr children[10];	//�ڽ��� ������
	int rule_no_used;	//�� ��带 ����µ� ���� ���ȣ
}nodeT;

//////////////Global Variables///////////////////////

int MaxTerminal;	//$�� �����ϴ� ������ �͹̳��� ���� ����
int MaxNonTerminal;	//������ nonterminal�� ���� ����
sym Nonterminals_list[MaxSymbols];
sym Terminals_list[MaxSymbols];

int totalNumberOfRules;	//������ rule�� ���� ����
onerule rules[MaxRules]; //rule table

int FirstTable[MaxSymbols][MaxSymbols];	//���� ����: MaxNonterminal x (MaxTerminals+2)
										//2 is for epsilon and done flag
int FollowTable[MaxSymbols][MaxSymbols]; //���� ����: MaxNonterminal x (MaxTerminals+1)
										//1 is for done flag
goto_set_ptr	States_And_Arcs = NULL;	//go-to graph�� ������
int Number_Of_States = 0;	//goto graph�� state ���� ��
int NumberOfArcs = 0;	//arcs�� ���� ��
ty_Cell_Action_Table Action_Table[MaxNumberOfStates][MaxSymbols];
//���� ���Ǵ� column�� ���� MaxTerminal
int Goto_Table[MaxNumberOfStates][MaxSymbols];	//���� ���Ǵ� columns�� ���� MaxNonTerminal
Ty_Node_Ptr Stack[1000];	//LR parsing stack�� ����
int Top = -1; //stack�� top

Ty_Node_Ptr Root = NULL;	//parse tree�� ��Ʈ ����� ������
int bar[100];

FILE *fps;	//source program file�� ���� ������


//�Լ� �����
sym get_next_token();
tokentype lexan();
int iswhitespace(char c);
int lookup_keyword_tbl(char *str);
int lookup_symtbl(char *str);
ty_ptr_item_node closure(ty_ptr_item_node IS);
int CheckExistItem(ty_ptr_item_node cs_list, ty_ptr_item_node s_val);
ty_ptr_item_node GoTo(ty_ptr_item_node IS, sym sym_val);
void makeGotoGraph(ty_ptr_item_node IS_0);
state_node_ptr Add_A_State_Node(state_node_ptr State_Node_List_Header, ty_ptr_item_node To_list);
void Add_An_Arc(Arc_node_ptr *Arc_List_Header, int from_num, int to_num, sym Symbol);
int is_same_two_itemlists(ty_ptr_item_node list1, ty_ptr_item_node list2);
state_node_ptr makeStateNode(void);
Arc_node_ptr makeArcNode(void);
int itemListCounter(ty_ptr_item_node IS);
int deleteTyPtrItemNode(ty_ptr_item_node item_list);
void printGotoGraph(goto_set_ptr gsp);
int findToStateNodeId(Arc_node_ptr arc_list, int from_id, sym symbal);
void fitemListPrint(ty_ptr_item_node IS, FILE *fpw);
void Make_Action_Table();
void print_Action_Table(void);
void Clear_Action_Table(void);
void Make_Goto_Table();
void Clear_Goto_Table(void);
void print_Goto_Table(void);
void push_state(Ty_Node_Ptr Stack[], int State);
void push_symbol(Ty_Node_Ptr Stack[], Ty_Node_Ptr NodeToPush);
Ty_Node_Ptr pop();
Ty_Node_Ptr Parsing(FILE * fps);
void print_parse_tree(FILE * fout, Ty_Node_Ptr curr, int standard, int first, int child);
int Compute_first_of_one_nonterminal(sym);
int Compute_first_of_any_string(sym alpha[], int first_result[]);
int Compute_follow_of_one_nonterminal(int);
void read_grammar(char* fileName);
int lookUp_nonterminal(char* str);
int lookUp_terminal(char* str);
ty_ptr_item_node getLastItem(ty_ptr_item_node cs_list);;

//���� token�� source file���� get
sym get_next_token() {
	sym token;
	tokentype a_tok;	//lexical analyzer���� ������� token
	a_tok = lexan();
	token.kind = 0;
	if (a_tok.kind == EOF_TOK) {
		token.no = MaxTerminal - 1;
		strcpy(token.str, Terminals_list[MaxTerminal - 1].str);
	}
	else {
		token.no = a_tok.kind;
		strcpy(token.str, a_tok.str);
	}
	return token;
}

tokentype lexan() {
	int state = 0;
	char c;
	char buf[50];
	int bp = 0; // bp is buffer pointer(���� ���� ��ġ).
	int upper_n; // number ��ū���� �Ҽ��� �� �κ� �� ���� �κ��� ������.
	double fraction; // number ��ū���� �Ҽ��� �Ʒ� �κ��� ������.
	tokentype token;
	int idx, FCNT, sign, Enum;

	while (1) {
		switch (state) {
		case 0: // �ʱ� ����. �� ��ū�� ù ���ڿ� ���� �۾� ���� �� ���� ���� ������.
			c = fgetc(fps);  // fgetc can be called even if fps is after the end of file.
							  // calling it again still returns EOF(-1) w/o invoking error.
			if (iswhitespace(c)) state = 0;  // this is white space.
			else if (isalpha(c)) { buf[bp] = c; bp++; buf[bp] = '\0'; state = 28; }
			else if (isdigit(c)) { buf[bp] = c; bp++; buf[bp] = '\0'; upper_n = c - '0'; state = 1; }
			else if (c == '<') state = 2;
			else if (c == '>') state = 32;
			else if (c == '=') state = 35;
			else if (c == '!') state = 38;
			else if (c == '+') state = 3;
			else if (c == '-') state = 4;
			else if (c == '*') state = 52;
			else if (c == '/') state = 8;
			else if (c == '\\') state = 53;
			else if (c == '%') state = 54;
			else if (c == '.') state = 55;
			else if (c == ',') state = 56;
			else if (c == '(') state = 57;
			else if (c == ')') state = 58;
			else if (c == '{') state = 59;
			else if (c == '}') state = 60;
			else if (c == '[') state = 61;
			else if (c == ']') state = 62;
			else if (c == ':') state = 63;
			else if (c == ';') state = 64;
			else if (c == '"') state = 65;
			else if (c == '\'') state = 66;
			else if (c == '#') state = 67;
			else if (c == '|') state = 68;
			else if (c == '&') state = 5;
			else if (c == EOF) state = 71;
			else {
				token.kind = URT; // �ν��� �� ���� ��ū���� ��Ÿ��.
				return token;
			}
			break;
		case 1: // NUM ��ū�� �Ҽ��� �� ���ڿ��� �޾� ���̴� ����.
			c = fgetc(fps);
			if (isdigit(c)) { buf[bp] = c; bp++; buf[bp] = '\0'; upper_n = 10 * upper_n + c - '0'; state = 1; }
			else if (c == '.') { buf[bp] = c; bp++; buf[bp] = '\0'; fraction = 0; FCNT = 0; state = 9; } // �Ҽ����� �������Ƿ� �Ǽ��� ó���ϴ� ���·� ��.
			else if (c == 'E') { buf[bp] = c; bp++; buf[bp] = '\0'; fraction = 0; state = 16; }  // E �� �ִ� exponent ó���η� ��.
			else state = 14;
			break;
		case 2: // ���� < �� ���� ���� ó���� ����ϴ� ����.
			c = fgetc(fps);
			if (c == '=') state = 30;
			else state = 31;
			break;
		case 3: // ���� + �� ���� ���� ó���� ����ϴ� ����.
			c = fgetc(fps);
			if (c == '+') state = 47;
			else if (c == '=') state = 45;
			else state = 46;
			break;
		case 4: // ���� - �� ���� ���� ó���� ����ϴ� ����.
			c = fgetc(fps);
			if (c == '-') state = 48;
			else if (c == '=') state = 49;
			else if (c == '>') state = 51;
			else state = 50;
			break;
		case 5: // ���� + �� ���� ���� ó���� ����ϴ� ����.
			c = fgetc(fps);
			if (c == '&') state = 6;
			else state = 7;
			break;
		case 6:
			token.kind = 2; strcpy(token.sub_kind, "");		 strcpy(token.str, "&&");
			return token;
		case 7: // ��ū & �� �������ִ� ����.
			ungetc(c, fps);
			token.kind = 13;
			return token;
		case 8:
			c = fgetc(fps);
			if (c == '/') state = 74;
			else if (c == '*') state = 75;
			else if (c == EOF) state = 73;
			else state = 72;
			break;
		case 9: // �Ǽ��� �Ҽ��� ���ϸ� �޾� ���̴� ����
			c = fgetc(fps);
			if (isdigit(c)) {
				buf[bp] = c; bp++; buf[bp] = '\0';
				FCNT++; fraction = fraction + (c - '0') / pow(10.0, FCNT); state = 23;
			}
			else if (c == 'E') { buf[bp] = c; bp++; buf[bp] = '\0'; state = 16; }
			else if (c == EOF)  state = 26;
			else if (iswhitespace(c)) state = 24;
			else state = 25;
			break;
		case 14: // ���� ���� ��ū�� �����ϴ� ����.
			ungetc(c, fps);
			token.kind = 1; strcpy(token.sub_kind, "in"); // ���� ������ ��Ÿ��.
			token.sub_data = upper_n;
			strcpy(token.str, buf);
			return token;
		case 16:
			c = fgetc(fps);
			if (c == '+') { buf[bp] = c; bp++; buf[bp] = '\0'; sign = 1; state = 17; }
			else if (c == '-') { buf[bp] = c; bp++; buf[bp] = '\0'; sign = -1; state = 17; }
			else if (isdigit(c)) { buf[bp] = c; bp++; buf[bp] = '\0'; sign = 1; Enum = c - '0'; state = 18; }
			else  state = 25; // error! 		 
			break;
		case 17:
			c = fgetc(fps);
			if (isdigit(c)) { buf[bp] = c; bp++; buf[bp] = '\0'; Enum = c - '0'; state = 18; }
			else state = 25; // error!
			break;
		case 18:
			c = fgetc(fps);
			if (isdigit(c)) { buf[bp] = c; bp++;  buf[bp] = '\0'; Enum = Enum * 10 + c - '0'; state = 18; }
			else state = 19;
			break;
		case 19:
			ungetc(c, fps);
			token.kind = 1; strcpy(token.sub_kind, "do"); // �Ǽ��� ��Ÿ��.
			token.rnum = (upper_n + fraction) * pow(10.0, sign*Enum);
			strcpy(token.str, buf);
			return token;
		case 20:
			strcpy(token.str, buf);
			idx = lookup_keyword_tbl(buf); // -1 if not exist.
			if (idx >= 0) { token.kind = Idx_First_keyword + idx; return token; }  // Note: first keyword has token index 30.
			// reaches here if it is not a keyword.
			idx = lookup_symtbl(buf); // -1 if not exist.
			if (idx >= 0) { token.kind = 0; token.sub_data = idx; return token; }
			// reaches here if it is not in symbol table.
			strcpy(symtbl[total_ids].idstr, buf); total_ids++;
			token.kind = 0; // ID ��ū���� ��Ÿ��.
			token.sub_data = total_ids - 1; // �� ID �� ��� �ִ� �ɺ����̺� ��Ʈ�� ��ȣ.
			return token;
		case 23:
			c = fgetc(fps);
			if (isdigit(c)) {
				buf[bp] = c; bp++; buf[bp] = '\0';
				FCNT++; fraction = fraction + (c - '0') / pow(10.0, FCNT); state = 23;
			}
			else if (c == 'E') { buf[bp] = c; bp++; buf[bp] = '\0'; state = 16; }
			else state = 24;
			break;
		case 24:
			ungetc(c, fps);
			token.kind = 1; strcpy(token.sub_kind, "do"); // �Ǽ��� ��Ÿ��.
			token.rnum = upper_n + fraction;
			strcpy(token.str, buf);
			return token;
		case 25:
			token.kind = -1;
			return token;
		case 26:  // do not call ungetc.
			token.kind = 1; strcpy(token.sub_kind, "do"); // �Ǽ��� ��Ÿ��.
			token.rnum = upper_n + fraction;
			strcpy(token.str, buf);
			return token;
		case 28:
			c = fgetc(fps);
			if (isalpha(c) || isdigit(c) || c == '_') { buf[bp] = c; bp++; buf[bp] = '\0'; state = 28; }
			else if (c == EOF) state = 20;
			else	 state = 29;
			break;
		case 29: // id �� keyword 
			ungetc(c, fps);
			strcpy(token.str, buf);
			idx = lookup_keyword_tbl(buf); // -1 if not exist.
			if (idx >= 0) { token.kind = Idx_First_keyword + idx; return token; }  // Note: first keyword has token index 30.
			// reaches here if it is not a keyword.
			idx = lookup_symtbl(buf); // -1 if not exist.
			if (idx >= 0) { token.kind = 0; token.sub_data = idx; return token; }
			// reaches here if it is not in symbol table.
			strcpy(symtbl[total_ids].idstr, buf); total_ids++;
			token.kind = 0; // ID ��ū���� ��Ÿ��.
			token.sub_data = total_ids - 1; // �� ID �� ��� �ִ� �ɺ����̺� ��Ʈ�� ��ȣ.
			return token;
		case 30:
			token.kind = 2; strcpy(token.sub_kind, "LE"); strcpy(token.str, "<=");
			return token;
		case 31:
			ungetc(c, fps);
			token.kind = 2; strcpy(token.sub_kind, "LT"); strcpy(token.str, "<");
			return token;
		case 32:
			c = fgetc(fps);
			if (c == '=') state = 33;
			else state = 34;
			break;
		case 33:
			token.kind = 2; strcpy(token.sub_kind, "GE");	strcpy(token.str, ">=");
			return token;
		case 34:
			ungetc(c, fps);
			token.kind = 2; strcpy(token.sub_kind, "GT"); strcpy(token.str, ">");
			return token;
		case 35: // ���� = �� ���� ���� ó���� ����ϴ� ����.
			c = fgetc(fps);
			if (c == '=') state = 36;
			else state = 37;
			break;
		case 36: // ��ū == �� ���� ó���� �����ϴ� ����.
			token.kind = 2; strcpy(token.sub_kind, "EQ");	strcpy(token.str, "==");
			return token;
		case 37: // ��ū > �� ���� ó���� �����ϴ� ����.
			ungetc(c, fps);
			token.kind = 8; strcpy(token.str, "=");
			return token;
		case 38:
			c = fgetc(fps);
			if (c == '=') state = 39;
			else state = 40;
			break;
		case 39:
			token.kind = 2; strcpy(token.sub_kind, "NE");	 strcpy(token.str, "!=");
			return token;
		case 40:
			ungetc(c, fps);
			token.kind = 10;  strcpy(token.str, "!"); // NOT		
			return token;
		case 45:
			token.kind = 16; 		 strcpy(token.str, "+=");
			return token;
		case 46:
			ungetc(c, fps);
			token.kind = 3;  strcpy(token.str, "+");
			return token;
		case 47:
			token.kind = 14;		 strcpy(token.str, "++");
			return token;
		case 48:
			token.kind = 15;		 strcpy(token.str, "--");
			return token;
		case 49:
			ungetc(c, fps);
			token.kind = 17;  strcpy(token.str, "-=");
			return token;
		case 50:
			ungetc(c, fps);
			token.kind = 4;		 strcpy(token.str, "-");
			return token;
		case 51:
			token.kind = 9;		 strcpy(token.str, "->");
			return token;
		case 52:
			token.kind = 5;		 strcpy(token.str, "*");
			return token;
		case 53:
			token.kind = 30;		 strcpy(token.str, "\\");
			return token;
		case 54:
			token.kind = 7;		 strcpy(token.str, "%");
			return token;
		case 55:
			token.kind = 11;		 strcpy(token.str, ".");
			return token;
		case 56:
			token.kind = 12;		 strcpy(token.str, ",");
			return token;
		case 57:
			token.kind = 18;		 strcpy(token.str, "(");
			return token;
		case 58:
			token.kind = 19;		 strcpy(token.str, ")");
			return token;
		case 59:
			token.kind = 20;		 strcpy(token.str, "{");
			return token;
		case 60:
			token.kind = 21;		 strcpy(token.str, "}");
			return token;
		case 61:
			token.kind = 22;		 strcpy(token.str, "[");
			return token;
		case 62:
			token.kind = 23;		 strcpy(token.str, "]");
			return token;
		case 63:
			token.kind = 24;		 strcpy(token.str, ":");
			return token;
		case 64:
			token.kind = 25;		 strcpy(token.str, ";");
			return token;
		case 65:
			token.kind = 26;		 strcpy(token.str, "\"");
			return token;
		case 66:
			token.kind = 27;		 strcpy(token.str, "'");
			return token;
		case 67:
			token.kind = 28;		 strcpy(token.str, "#");
			return token;
		case 68:
			c = fgetc(fps);
			if (c == '|') 	state = 69;
			else 	 state = 70;
			break;
		case 69:
			token.kind = 2;	strcpy(token.sub_kind, "OR");	 strcpy(token.str, "||");
			return token;
		case 70:
			ungetc(c, fps);
			token.kind = 29;	 strcpy(token.str, "|");
			return token;
		case 71:
			token.kind = EOF_TOK; strcpy(token.str, "EOF");
			return token;
		case 72:
			ungetc(c, fps);
			token.kind = 6; strcpy(token.str, "/");
			return token;
		case 73:
			token.kind = 6; strcpy(token.str, "/");
			return token;
		case 74:
			c = fgetc(fps);
			if (c == '\n') state = 0;
			else if (c == EOF) state = 71;
			else state = 74;
			break;
		case 75:
			c = fgetc(fps);
			if (c == '*') state = 76;
			else if (c == EOF) state = 71;
			else state = 75;
			break;
		case 76:
			c = fgetc(fps);
			if (c == '/') state = 0;
			else if (c == EOF) state = 71;
			else state = 75;
			break;
		default: printf("Unrecognizable token! Stop generating tokens.\n");
			token.kind = URT; strcpy(token.str, "URT");
			return token;
		} // switch
	} //while
}

int iswhitespace(char c) {
	if (c == ' ' || c == '\n' || c == '\t')
		return 1;
	else
		return 0;
}

int lookup_keyword_tbl(char *str) {
	int i;
	for (i = 0; i < total_keywords; i++)
		if (strcmp(keywords[i], str) == 0)
			return i;
	return -1;

}

int lookup_symtbl(char *str) {
	int i;
	for (i = 0; i < total_ids; i++)
		if (strcmp(symtbl[i].idstr, str) == 0)
			return i;
	return -1;
}

ty_ptr_item_node closure(ty_ptr_item_node IS) {
	ty_ptr_item_node new_cs = NULL;
	ty_ptr_item_node curr = NULL;
	ty_ptr_item_node cursor = NULL;

	sym	SymAfterDot;

	int r_num, d_num;
	int i_0 = 0;

	//initialize
	r_num = d_num = 0;

	//������ cuur�� IS�� ù ��带 ����Ű�� �Ѵ�.
	curr = IS;

	//Core Routine
	while (curr) {
		//curr ����� rule ��ȣ
		r_num = curr->RuleNum;
		d_num = curr->DotNum;

		//SymAfterDot : type.sym { int kind / int no} : 
		if (d_num >= rules[r_num].rleng) { // ex) TE'��
			curr = curr->link;
			continue;
		}
		else
			SymAfterDot = rules[r_num].rightside[d_num];

		//����
		//�ܸ���ȣ�̸� �����ϰ� �Ѿ��.
		if (!SymAfterDot.kind) {
			curr = curr->link;
			continue;
		}

		for (i_0 = 0; i_0 < totalNumberOfRules; i_0++) {
			//�� i_0�� ���� �ɺ��� symAfterDot�� �ƴϸ� continue
			if (rules[i_0].leftside.no != SymAfterDot.no)
				continue;

			//item node �ϳ��� �����.
			new_cs = (ty_ptr_item_node)malloc(sizeof(type_item));

			//rule ��ȣ r, dot number =0 �� ���⿡ �ִ´�.
			new_cs->RuleNum= i_0;
			new_cs->DotNum = 0;
			new_cs->link = NULL;

			//new_cs�� �̹� �����ϸ� continue
			if (CheckExistItem(IS, new_cs)) {
				free(new_cs);
				continue;
			}

			//NewItemNodePtr�� IS�� �� �ڿ� ���δ�.
			cursor = getLastItem(IS);
			cursor->link = new_cs;
		}//for : i_0
		curr = curr->link;
	}//while : curr

	return IS;
}//closure()

int CheckExistItem(ty_ptr_item_node cs_list, ty_ptr_item_node s_val) {
	ty_ptr_item_node cursor = cs_list;

	while (cursor) {
		if (cursor->RuleNum == s_val->RuleNum && cursor->DotNum == s_val->DotNum)
			return 1;
		cursor = cursor->link;
	}//while : cursor
	
	return 0;
}	//CheckExistItem()

ty_ptr_item_node GoTo(ty_ptr_item_node IS, sym sym_val) {
	int r_num, d_num;
	sym symAfterDot;
	ty_ptr_item_node cursor = NULL;
	ty_ptr_item_node New_Item = NULL;
	ty_ptr_item_node Go_To_Result_List = NULL;
	ty_ptr_item_node i_cursor = NULL;
	ty_ptr_item_node temp_item = NULL;

	cursor = IS;
	while (cursor) {
		r_num = cursor->RuleNum;
		d_num = cursor->DotNum;

		//SymAfterDot : type.sym{ int kind / int no}
		if (d_num >= rules[r_num].rleng) {
			cursor = cursor->link;
			continue;	//ignore this item since dot is at the end
		}
		symAfterDot = rules[r_num].rightside[d_num];

		//�� ������ �ɺ��� goto �� �ɺ��� �ٸ��� ���� ���������� �Ѿ� ��.
		if (!(symAfterDot.kind == sym_val.kind&&symAfterDot.no == sym_val.no)) {
			cursor = cursor->link;
			continue;
		}

		New_Item = (ty_ptr_item_node)malloc(sizeof(type_item));
		New_Item->RuleNum = r_num;
		New_Item->DotNum = d_num + 1;
		New_Item->link = NULL;

		//New_item�� �̹� �����ϸ� �� �������� �����Ѵ�.
		if (CheckExistItem(Go_To_Result_List, New_Item)) {
			free(New_Item);
			cursor = cursor->link;
			continue;
		}//if : CheckExistItem()

		//NewItemNodePtr �� Go_To_Result_List�� �� �ڿ� ���δ�.
		if (Go_To_Result_List == NULL) {
			Go_To_Result_List = New_Item;
		}
		else {
			temp_item = getLastItem(Go_To_Result_List);
			temp_item->link = New_Item;	//black
		}	//if
		
		cursor = cursor->link;
	}	//while : cursor
	if (Go_To_Result_List)
		return closure(Go_To_Result_List);
	else
		return NULL;
} //GoTo()

//make Goto Graph. ó�� ����� state list�� arc list�� ������� ������ ���� ������ ��Ʈ�� ��.
void makeGotoGraph(ty_ptr_item_node IS_0) {
	int i_0, i_1, i_max;
	sym sym_temp;
	goto_set_ptr result = NULL;
	state_node_ptr	State_Node_List_Header = NULL; //State List�� ���
	state_node_ptr state_cursor = NULL;	//���� �۾� ���� state node�� ������
	state_node_ptr To_state_node = NULL;//state list�� �� ������ state node�� ������
	Arc_node_ptr Arc_List_Header = NULL;
	ty_ptr_item_node To_item_list = NULL;

	//state 0 �� �� state list�� �ֵ��� ��
	State_Node_List_Header = makeStateNode();
	State_Node_List_Header->id = 0;
	State_Node_List_Header->item_cnt = itemListCounter(IS_0);
	State_Node_List_Header->item_start = IS_0;
	State_Node_List_Header->next = NULL;
	Number_Of_States = 1;
	state_cursor = State_Node_List_Header;

	while (state_cursor) {
		//�ܸ���ȣ, ��ܸ���ȣ
		for (i_0 = 0; i_0 < 2; i_0++) {//i_0 =0�̸� �ܸ���ȣ, i_0=1�̸� ��ܸ���ȣ�� ���� ó��
			//i_max�� �� ��찡 ���� �� ��ȣ�� ��
			i_max = i_0 ? MaxNonTerminal : MaxTerminal - 1;
			for (i_1 = 0; i_1 < i_max; i_1++) {//i_1�� �ܸ�, ��ܸ� �� ��쿡�� ��ȣ�� ��ȣ
				//���� �ɺ� �ϳ��� ����
				sym_temp.kind = i_0;
				sym_temp.no = i_1;
				//���� state���� �����ɺ� sym_temp�� ���� goto�� ������ ����Ʈ�� �˾� ��
				To_item_list = GoTo(state_cursor->item_start, sym_temp);	//goto �� �Ͽ� ����� �˾� ��

				if (To_item_list) {//goto result is not empty
					//goto�� ������ ����Ʈ�� ���� state�� ��ϵǾ� ���� ������ �� state�� �����
					To_state_node = Add_A_State_Node(State_Node_List_Header, To_item_list);

					//�˾Ƴ� ��ũ�� ���Ͽ� �̰��� �̹� �����ϴ� ��ũ�� �ƴϸ� ���ο� ��ũ�� �߰�
					Add_An_Arc(&Arc_List_Header, state_cursor->id, To_state_node->id, sym_temp);//black
				}//if : To_Item_List
			}//for : i_1 : ��� ��ȣ�� ���Ͽ� goto ����
		}//for : i_0 : �ܸ���ȣ -> ��ܸ� ��ȣ
		state_cursor = state_cursor->next; //black
	}//while : state_cursor
	//�� �Լ��� ����� �����ϱ� ���� ���� ����ü�� ��Ʈ
	States_And_Arcs = (goto_set_ptr)malloc(sizeof(goto_set));
	States_And_Arcs->State_Node_List = State_Node_List_Header;
	States_And_Arcs->Arc_list = Arc_List_Header;
}// : makeGotoGraph()

//��� state�� item list�� �ٸ� �� new item�� new state�ν� �߰�
state_node_ptr Add_A_State_Node(state_node_ptr State_Node_List_Header, ty_ptr_item_node To_list) {
	int Number_Of_Items = 0; //���ο� item list�� item ����
	state_node_ptr cursor = State_Node_List_Header;
	state_node_ptr last_cursor = NULL;
	state_node_ptr new_state_node = NULL;

	Number_Of_Items = itemListCounter(To_list);

	//state list ���� ����� ���Ͽ� list �߰� ���θ� �����մϴ�.
	while (cursor) {
		//item ������ ���� ������ Ȯ����.
		if (cursor->item_cnt != Number_Of_Items) {//cursor�� ����Ű�� state�� item list�� item ���� �ٸ���
			last_cursor = cursor;
			cursor =cursor->next;//black
			continue;
		}// if: state node�� item list�� �����ϰ� �ִ� item�� ������ ��ġ ���� ������ Ȯ������ �ʾƵ� ����
		
		int is_same = is_same_two_itemlists(cursor->item_start, To_list);	//���� ������ 1
		if (is_same) { //cursor�� state�� itemlist�� to_list�� ������ ��Ȳ
			deleteTyPtrItemNode(To_list);//To_list�� �ִ� item ��� free
			return cursor;	//������ ������ �Ǹ�� �� state node�� ������ ��ȯ
		}
		//�� ������ ����Ʈ�� �ٸ� ������ �Ǹ�Ǿ����Ƿ� ���� state node�� Ŀ���� �ű�
		last_cursor = cursor;
		cursor = cursor->next;
	}//while

	//state node list ��ü�� ���ص� ���� item list�� ���� state node�� �߰ߵ��� ����
	//���� ���ο� state node�� ����� To_list�� ���̰� �� ��带 state node list�� �� �ڿ� �߰�
	new_state_node = makeStateNode();
	//�������� Number_Of_States�� ũ�⸦ ����
	Number_Of_States++;

	//state list �� ���ο� state node�� ����
	new_state_node->item_cnt = Number_Of_Items;
	new_state_node->item_start = To_list;
	new_state_node->id = last_cursor->id + 1;
	new_state_node->next = NULL;
	last_cursor->next = new_state_node; 

	return new_state_node;
}	//ADD_A_State_node()

//arc list�� ���ٸ�, arc�� �߰�
void Add_An_Arc(Arc_node_ptr *Arc_List_Header, int from_num, int to_num, sym Symbol) {
	Arc_node_ptr Arc_cursor, Arc_last = NULL;
	Arc_node_ptr Arc_new = NULL;
	int same_arc_exists = 0;

	Arc_new = makeArcNode();

	Arc_new->from_state = from_num;
	Arc_new->to_state = to_num;
	Arc_new->gram_sym = Symbol;
	Arc_new->link = NULL;

	if (*Arc_List_Header == NULL) {
		*Arc_List_Header = Arc_new; //�� ó�� ��ũ�� �޾� ��
		NumberOfArcs++;
		return;
	}

	Arc_cursor = *Arc_List_Header;

	while (Arc_cursor) {
		if (Arc_cursor->from_state == from_num && Arc_cursor->to_state == to_num
			&& Arc_cursor->gram_sym.kind == Symbol.kind && Arc_cursor->gram_sym.no == Symbol.no) {
			same_arc_exists = 1;
			break;
		}
		else {
			Arc_last = Arc_cursor;
			Arc_cursor = Arc_cursor->link;
		}
	}//while
	if (!same_arc_exists) {
		Arc_last->link = Arc_new;	//���ο� ��ũ�� �Ŵ޾� �ش�.
		NumberOfArcs++;
	}
	else
		free(Arc_new);
//Add_An_Arc()
}

//�־��� two list�� ���ٸ� 1, �ƴ϶�� 0
int is_same_two_itemlists(ty_ptr_item_node list1, ty_ptr_item_node list2) {
	int l1, l2;
	l1 = itemListCounter(list1);
	l2 = itemListCounter(list2);
	ty_ptr_item_node p1 = list1, p2;
	if (l1 != l2)
		return 0;
	while (p1) {
		//p1�� list2�� �����ϴ��� Ȯ��
		p2 = list2; //list2���� �� item�� ������
		int p1_exists_in_list2 = 0;	//�ʱ⿡�� �������� �ʴ´ٰ� ����

		while(p2){ //p2�� �̿��� list2�� ��ĳ�������ν� list2���� p1�� ã�´�
			if (p1->RuleNum == p2->RuleNum && p1->DotNum == p2->DotNum) {
				p1_exists_in_list2 = 1;	//p1�� ã����
				break;
			}
			p2 = p2->link;
		}//while
		if(!p1_exists_in_list2)
			return 0;// list1�� item�� list2�� �������� �ʱ� ������ �� �� list���� �ٸ���.
		p1 = p1->link;
	}//while
	return 1;
}//is_same_two_itemlists

state_node_ptr makeStateNode(void) {
	state_node_ptr cursor;

	cursor = (state_node_ptr)malloc(sizeof(state_node));

	cursor->id = -1;
	cursor->item_cnt = 0;
	cursor->item_start = NULL;
	cursor->next = NULL;

	return cursor;
}//makeStateNode()

Arc_node_ptr makeArcNode(void) {
	Arc_node_ptr cursor;

	cursor = (Arc_node_ptr)malloc(sizeof(Arc_node));

	cursor->from_state = -1;
	cursor->to_state = -1;
	cursor->gram_sym.kind = -1;
	cursor->gram_sym.no = -1;
	cursor->link = NULL;

	return cursor;
}//makeArcNode()

int itemListCounter(ty_ptr_item_node IS) {
	int cnt = 0;
	ty_ptr_item_node cursor = IS;

	while (cursor) {
		cnt++;
		cursor = cursor->link;
	}
	return cnt;
}

//item_list�� ��� ������ ����
int deleteTyPtrItemNode(ty_ptr_item_node item_list) {
	ty_ptr_item_node item_next = NULL;
	ty_ptr_item_node item_cursor = item_list->link;

	while (item_cursor) {
		item_next = item_cursor->link;
		free(item_cursor);
		item_cursor = item_next;
	}
	free(item_list);
	return 0;

}

void printGotoGraph(goto_set_ptr gsp) {
	state_node_ptr State_Node_List_Header = gsp->State_Node_List;
	Arc_node_ptr item_list = gsp->Arc_list;
	char str[10];
	FILE *fpw;
	fpw = fopen("goto_graph.txt", "w");

	while (State_Node_List_Header) {
		fprintf(fpw, "ID[%2d] (%3d) : ", State_Node_List_Header->id, State_Node_List_Header->item_cnt);
		fitemListPrint(State_Node_List_Header->item_start, fpw);
		State_Node_List_Header = State_Node_List_Header->next;
	}
	printf("\nTotal number of states = %d\n", Number_Of_States);
	fprintf(fpw, "Total number of states = %d\n", Number_Of_States);

	fprintf(fpw, "\nGoto arcs:\nFrom	to	Symbol\n");
	while (item_list) {
		fprintf(fpw, "%4d %4d	", item_list->from_state, item_list->to_state);
		if (item_list->gram_sym.kind == 0)
			strcpy(str, Terminals_list[item_list->gram_sym.no].str);
		else
			strcpy(str, Nonterminals_list[item_list->gram_sym.no].str);
		fprintf(fpw, "%s \n", str);

		item_list = item_list->link;
	}
	printf("Total number of arcs = %d\n", NumberOfArcs);
	fprintf(fpw, "Total number of arcs = %d\n", NumberOfArcs);
	fclose(fpw);
}

//grammar symbol symbal�� ������ from_id state������ arc�� �ִ� state�� ã�ƶ�
int findToStateNodeId(Arc_node_ptr arc_list, int from_id, sym symbal) {
	Arc_node_ptr cursor = arc_list;

	while (cursor) {
		if (cursor->from_state == from_id && cursor->gram_sym.kind == symbal.kind
			&&cursor->gram_sym.no == symbal.no)
			return cursor->to_state;
		cursor = cursor->link;
	}

	return -1;
}

//���Ϸ� item list�� �����۵��� print
void fitemListPrint(ty_ptr_item_node IS, FILE *fpw) {
	int i_0;
	int r_num, d_num;

	ty_ptr_item_node cursor = IS;

	while (cursor) {
		r_num = cursor->RuleNum;
		d_num = cursor->DotNum;

		fprintf(fpw, "%s -> ", Nonterminals_list[rules[r_num].leftside.no].str);
		for (i_0 = 0; i_0 < rules[r_num].rleng; i_0++) {
			if (i_0 == d_num)
				fprintf(fpw, ". ");
			fprintf(fpw, "%s ", rules[r_num].rightside[i_0].kind ?
				Nonterminals_list[rules[r_num].rightside[i_0].no].str :
				Terminals_list[rules[r_num].rightside[i_0].no].str);
		}
		if (i_0 == d_num)
			fprintf(fpw, ".");
		if (!rules[r_num].rleng)
			fprintf(fpw, "��");
		fprintf(fpw, "	");
		cursor = cursor->link;
	}
	fprintf(fpw, "\n");
}

void Make_Action_Table() {
	//�������� ����
	int to_state_id = -1;
	int i_0 = 0;
	state_node_ptr state_cursor = States_And_Arcs->State_Node_List;
	ty_ptr_item_node item_cursor = NULL;
	sym symbol;

	//initialize table
	Clear_Action_Table();
	while (state_cursor) {
		item_cursor = state_cursor->item_start;
		
		while (item_cursor) {
			symbol = rules[item_cursor->RuleNum].rightside[item_cursor->DotNum];
			if (rules[item_cursor->RuleNum].rleng > item_cursor->DotNum) {//��Ʈ ������ �ɺ��� ������
				if (!symbol.kind) {//�׸��� �װ��� �ܸ���ȣ��� shift
					to_state_id = findToStateNodeId(States_And_Arcs->Arc_list, state_cursor->id, symbol);
					//shift �� �� state��ȣ �˾ƿ�

					if (to_state_id == -1) { // to state�� ����
						printf("Logic error at Make_Action (1) \n");
						getchar();
					}

					if (Action_Table[state_cursor->id][symbol.no].Kind == 'e') {//�ʱ�ȭ�� ��� �ִ� ��. shift actino�� �ִ´�
						Action_Table[state_cursor->id][symbol.no].Kind = 's';
						Action_Table[state_cursor->id][symbol.no].num = to_state_id;
					}
					else {//���� �̹� ����ִ�.
						if (Action_Table[state_cursor->id][symbol.no].Kind == 's'
							&& Action_Table[state_cursor->id][symbol.no].num == to_state_id) {
							//�� ���� �ٽ� ���� �ʰ� �׳� �Ѿ. ������ �ƴ�.
						}
						else {	//���� ���� �ٸ� ������ �̹� ����. LR0�� �ƴϴ�"��� ����
							printf("Make_Action_Table�� ���߰� ��Ȳ�߻�1\n");
							getchar();
						}
					}
				}//if(!symbol_kind)
			}
			else {
				if (item_cursor->RuleNum == 0) {	//Augmented rule ( S' -> S)�� ���
					if (Action_Table[state_cursor->id][MaxTerminal - 1].Kind == 'e') {//��� ������ accept �׼� �־���
						Action_Table[state_cursor->id][MaxTerminal - 1].Kind = 'a';//Action[state][$]�� 'a'�� ����
					}
					else {
						printf("Make_Action_Table�� ���߰� ��Ȳ�߻�2\n");
						getchar();
					}
				}else{//��Ʈ�� �������� �������̹Ƿ� �̿� ���� reduction �۾��� ����
					for (i_0 = 0; i_0 < MaxTerminal; i_0++) {
						if (FollowTable[rules[item_cursor->RuleNum].leftside.no][i_0]) { //���� ���� ��ܸ���ȣ�� ��� follow �ɺ�
							if (Action_Table[state_cursor->id][i_0].Kind == 'e') {//���� ��� ������, reduction�� �ִ´�
								Action_Table[state_cursor->id][i_0].Kind = 'r';
								Action_Table[state_cursor->id][i_0].num = item_cursor->RuleNum;
							}
							else {	//�̹� ä���� ������
								if (Action_Table[state_cursor->id][i_0].Kind == 'r'
									&&Action_Table[state_cursor->id][i_0].num == item_cursor->RuleNum) {
									//���� ���� ������ ������ �����Ƿ� ������ �ƴϰ� ����
								}
								else {
									printf("Make_Action_Table�� ���߰� ��Ȳ�߻�3\n");
									getchar();
								}
							}
						}//if: FollowTable[rules[item_cursor->RuleNum].
					}//for : i_0
				}//else
			}//else (rules[item_cursor->RuleNum].rleng ==

			item_cursor = item_cursor->link;
		}//while

		//���� state_node�� �̵�
		state_cursor = state_cursor->next;
	}//while : state_cursor
}//make_action_table()

void print_Action_Table(void) {
	int i_0, i_1;
	FILE * file_ptr = NULL;
	
	file_ptr = fopen("action_table.txt", "w");

	fprintf(file_ptr, "\t");
	for (i_0 = 0; i_0 < MaxTerminal; i_0++) 
		fprintf(file_ptr, "%2s\t", Terminals_list[i_0].str);
	fprintf(file_ptr, "\n");

	for (i_0 = 0; i_0 < Number_Of_States; i_0++) {
		fprintf(file_ptr, "%3d\t", i_0);
		for (i_1 = 0; i_1 < MaxTerminal; i_1++) {
			fprintf(file_ptr, "%c", Action_Table[i_0][i_1].Kind);
			if (Action_Table[i_0][i_1].Kind == 's' || Action_Table[i_0][i_1].Kind == 'r')
				fprintf(file_ptr, "%2d\t", Action_Table[i_0][i_1].num);
			else
				fprintf(file_ptr, "\t");
		}//for : i_1
		fprintf(file_ptr, "\n");
	}//for : i_0

	fclose(file_ptr);
	
}

void Clear_Action_Table(void) {
	int i_0, i_1;

	for (i_0 = 0; i_0 < Number_Of_States; i_0++) {
		for (i_1 = 0; i_1 < MaxTerminal; i_1++) {
			Action_Table[i_0][i_1].Kind = 'e';
			Action_Table[i_0][i_1].num = 0;
		}
	}
}

void Make_Goto_Table() {
	int to_state_id = -1;
	int i_0 = 0;
	state_node_ptr state_cursor = States_And_Arcs->State_Node_List;
	ty_ptr_item_node item_cursor = NULL;
	sym symbol;

	Clear_Goto_Table();
	while (state_cursor) {
		item_cursor = state_cursor->item_start;
		while (item_cursor) {
			symbol = rules[item_cursor->RuleNum].rightside[item_cursor->DotNum];

			if(rules[item_cursor->RuleNum].rleng > item_cursor->DotNum ) { //dot ������ grammar symbol�� ����
				if (symbol.kind) {	//symbol�� nonterminal
					to_state_id = findToStateNodeId(States_And_Arcs->Arc_list, state_cursor->id, symbol); //state ã��
					if (to_state_id == -1) {
						item_cursor = item_cursor->link;
						continue;
					}
				Goto_Table[state_cursor->id][symbol.no] = to_state_id;
				}	
			}
			item_cursor = item_cursor->link;
		}

		//���� state_node�� �̵��մϴ�.
		state_cursor = state_cursor->next;
	}
}

void Clear_Goto_Table(void) {
	int i_0, i_1;

	for (i_0 = 0; i_0 < MaxNumberOfStates; i_0++) {
		for (i_1 = 0; i_1 < MaxNonTerminal; i_1++) {
			Goto_Table[i_0][i_1] = -1;
		}
	}
}

void print_Goto_Table(void) {
	int i_0, i_1;
	FILE* file_ptr = NULL;

	file_ptr = fopen("goto_table.txt", "w");

	fprintf(file_ptr, "\t");
	for (i_0 = 0; i_0 < MaxNonTerminal; i_0++) {
		fprintf(file_ptr, "%3s\t", Nonterminals_list[i_0].str);
	}
	fprintf(file_ptr, "\n");

	for (i_0 = 0; i_0 < Number_Of_States; i_0++) {
		fprintf(file_ptr, "%3d\t", i_0);
		for (i_1 = 0; i_1 < MaxNonTerminal; i_1++) {
			if (Goto_Table[i_0][i_1] != -1)
				fprintf(file_ptr, "%3d\t", Goto_Table[i_0][i_1]);
			else
				fprintf(file_ptr, " -1\t");
		}
		fprintf(file_ptr, "\n");
	}
	fclose(file_ptr);
}

//LR stack�� state�� ��Ÿ���� ������带 ����� ���� �����͸� ����. 2nd parameter�� ���� state��ȣ��
void push_state(Ty_Node_Ptr Stack[], int State) {
	Ty_Node_Ptr NewNode;

	//state�� ���� ��带 ����� �̸� ���ÿ� �־��ش�.
	NewNode = (Ty_Node_Ptr)malloc(sizeof(struct nodetype));
	NewNode->state = State;	//���Ⱑ �� NewNode->state�� 0�̻��̸� state�� ��Ÿ��
	Top++;
	Stack[Top] = NewNode;
}

//LR stack�� �����ɺ� ����� �����͸� ����. ȣ��ÿ� �����ɺ��� ������ ��带 �غ��Ͽ� ���� �����͸� 2nd parameter�� ����
void push_symbol(Ty_Node_Ptr Stack[], Ty_Node_Ptr NodeToPush) {
	Top++;
	Stack[Top] = NodeToPush;
}

//LR stack���� �����͸� ����
Ty_Node_Ptr pop() {
	Ty_Node_Ptr rptr;
	if (Top < 0) {
		printf("Pop error. Empty stack\n");
		getchar();
	}
	rptr = Stack[Top];
	Top--;
	return rptr;
}

Ty_Node_Ptr Parsing(FILE * fps) {
	int i, kind, TempState, Finished = 0, State, RuleNo, RuleLeng;
	kind = 0;	//state�� push �� ���� ����
	sym NextToken;	//lexical analyzer���� ���� �ִ� ��ū ������
	Ty_Node_Ptr Root, NewNode, TempNode;
	//���ÿ� �� ó���� state 0 �� �־� ����
	push_state(Stack, 0);	//psuh a state 0 to LR stack
	NextToken = get_next_token(fps);	//ù ��ū�� �о�´�.
	do {
		State = Stack[Top]->state;
		switch (Action_Table[State][NextToken.no].Kind) {
			case 's':
				//���� ��ū�� �ش��ϴ� �ܸ���ȣ�� �������� shift�� ���� �ɺ� �غ�.
				NewNode = (Ty_Node_Ptr)malloc(sizeof(struct nodetype));
				NewNode->state = -1;	//�����ɺ��� ����Ǿ� ������ ��Ÿ��.
				NewNode->nodesym = NextToken;//�ܸ� ��ȣ�� ��� �Ľ�Ʈ�� ��忡 ��ū �� ��ü�� ������
				NewNode->child_cnt = 0; NewNode->children[0] = NULL;
				push_symbol(Stack, NewNode);//���� ��ū�� �ش��ϴ� �ܸ���ȣ�� ���ÿ� shift��
				//action table ���� ������ state�� Ǫ���ؾ���
				TempState = Action_Table[State][NextToken.no].num;
				push_state(Stack, TempState);
				NextToken = get_next_token(fps);	//���� ��ū�� �о� ���´�.
				break;
			case 'r':
				//���� LHS ��ܸ���ȣ�� �ش��ϴ� ��� �غ�.
				NewNode = (Ty_Node_Ptr)malloc(sizeof(struct nodetype));
				NewNode->state = -1;//�����ɺ� ������� ǥ��
				RuleNo = Action_Table[State][NextToken.no].num;
				NewNode->nodesym = rules[RuleNo].leftside;
				//���ÿ��� ��带 ������ �ڽ��� �غ�
				RuleLeng = rules[RuleNo].rleng;
				for (i = 0; i < RuleLeng; i++) {
					TempNode = pop();	//state�� �ϳ� ����
					TempNode = pop();	//���� �ɺ��� �ϳ� ����.
					NewNode->children[RuleLeng - 1 - i] = TempNode;	//���� ���� �� ��忡 �ڽ����� �Ŵ޾� ��
				}
				NewNode->child_cnt = RuleLeng;
				NewNode->rule_no_used = RuleNo;
				State = Stack[Top]->state;	//���� ���� ������ 2�� ��ŭ�� ���Ҹ� ������ �� �� ������ ž�� state 
				TempState = Goto_Table[State][NewNode->nodesym.no];	//��ܸ���ȣ�� goto �� state�� �����´�.
				push_symbol(Stack, NewNode);//������� ���� ���� ��ܸ� ��ȣ�� �ش��ϴ� ��带 ���ÿ� ����
				push_state(Stack, TempState);// goto�� state�� ����
				break;
			case 'a':
				Root = Stack[1];	//������ starting nonterminal�� �ڽĳ��� ��
				return Root;
				break;
			case 'e':
				printf("Error: Parser is attempting to access an error cell. \n");
				getchar();
		}
	} while (1);
}

//file�� parse tree�� print
void print_parse_tree(FILE * fout, Ty_Node_Ptr curr, int standard, int first, int child) {
	int i, j, n = 0;
	if (first != 0) {
		for (i = 0; i < standard - 2; i++) {
			if (i % 8 == 5) {
				n++;
				if (bar[n])
					fprintf(fout, "|");
				else
					fprintf(fout, " ");
			}
			else {
				fprintf(fout, " ");
			}
		}
		if (standard != 0)
			fprintf(fout, "--");
	}

	fprintf(fout, "%3s", curr->nodesym.str);
	if (first == child)
		bar[standard / 8] = 0;
	if (curr->nodesym.kind == 0)
		fprintf(fout, "\n");
	else
		fprintf(fout, "-----");

	for (j = 0; j < curr->child_cnt; j++) {
		bar[standard / 8 + 1] = 1;
		print_parse_tree(fout, curr->children[j], standard + 8, j, curr->child_cnt - 1);
	}
	return;
}

void read_grammar(char* fileName) {
	FILE* fp;
	char line[500];
	char symstr[10];
	char* ret = "hi";
	int i, k, n_sym, n_rule, i_leftSymbol, i_rightSymbol, i_right, synkind;
	fp = fopen(fileName, "r");
	if (!fp) {
		printf("File open error of grammar file\n");
		getchar();
	}

	//ignore
	ret = fgets(line, 500, fp);
	ret = fgets(line, 500, fp);

	//nonterminal
	ret = fgets(line, 500, fp);

	i = 0; n_sym = 0;

	do {
		while (line[i] == ' ' || line[i] == '\t') i++;
		if (line[i] == '\n')break;
		k = 0;
		while (line[i] != ' ' && line[i] != '\t' && line[i] != '\n') {
			symstr[k] = line[i]; i++; k++;
		}
		symstr[k] = '\0';
		strcpy(Nonterminals_list[n_sym].str, symstr);
		Nonterminals_list[n_sym].kind = 1;
		Nonterminals_list[n_sym].no = n_sym;
		n_sym++;
	} while (1);
	MaxNonTerminal = n_sym;

	//terminal
	i = 0; n_sym = 0;
	ret = fgets(line, 500, fp);
	do {
		while (line[i] == ' ' || line[i] == '\t')i++;
		if (line[i] == '\n')break;
		k = 0;
		while (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		{
			symstr[k] = line[i]; i++; k++;
		}
		symstr[k] = '\0';
		strcpy(Terminals_list[n_sym].str, symstr);
		Terminals_list[n_sym].kind = 0;
		Terminals_list[n_sym].no = n_sym;
		n_sym++;
	} while (1);
	MaxTerminal = n_sym;

	n_rule = 0;

	do {//reading rules
		ret = fgets(line, 500, fp);
		if (!ret)
			break;
		i = 0;
		if (strlen(line) < 1)
			continue;
		else {//if line has only white space
			while (line[i] == ' ' || line[i] == '\t') i++; //skip spaces
			if (!isalpha(line[i]))
				continue;
		}

		//left symbol
		while (line[i] == ' ' || line[i] == '\t') i++;
		k = 0;
		while (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
		{
			symstr[k] = line[i]; i++; k++;
		}
		symstr[k] = '\0';
		i_leftSymbol = lookUp_nonterminal(symstr);
		if (i_leftSymbol < 0) {
			printf("Wrong left symbol of a rule.\n");
			getchar();
		}

		rules[n_rule].leftside.kind = 1; rules[n_rule].leftside.no = i_leftSymbol;
		strcpy(rules[n_rule].leftside.str, symstr);


		while (line[i] != '>') i++;
		i++;
		while (line[i] == ' ' || line[i] == '\t')i++;

		//right side
		i_right = 0;
		do {
			k = 0;
			while (i < strlen(line) && (line[i] != ' '
				&& line[i] != '\t' && line[i] != '\n'))
			{
				symstr[k] = line[i]; i++; k++;
			}
			symstr[k] = '\0';
			if (strcmp(symstr, "epsilon") == 0) {
				rules[n_rule].rleng = 0;
				break;
			}

			if (isupper(symstr[0])) {//this is nonterminal
				synkind = 1;
				i_rightSymbol = lookUp_nonterminal(symstr);
			}
			else {	//this is terminal
				synkind = 0;
				i_rightSymbol = lookUp_terminal(symstr);
			}
			if (i_rightSymbol < -1) {
				printf("Wrong right symbol of a rule.\n");
				getchar();
			}

			rules[n_rule].rightside[i_right].kind = synkind;
			rules[n_rule].rightside[i_right].no = i_rightSymbol;
			strcpy(rules[n_rule].rightside[i_right].str, symstr);

			i_right++;

			while (line[i] == ' ' || line[i] == '\t')i++;
			if (i >= strlen(line) || line[i] == '\n')
				break;
		} while (1);

		rules[n_rule].rleng = i_right;
		n_rule++;
	} while (1);
	totalNumberOfRules = n_rule;
	printf("Total number of rules = %d\n", totalNumberOfRules);
}

int Compute_first_of_one_nonterminal(sym X) {
	int i, j, k, CR = -1;
	int Yi_has_epsilon;
	int first_result[MaxSymbols]
;

	for (i = 0; i < MaxTerminal + 2; i++) first_result[i] = 0; //initialize

Next_Rule:
	CR++;
	if (CR >= totalNumberOfRules) {	//all x-rules have been processed
		for (k = 0; k < MaxTerminal + 1; k++)
			if (first_result[k] == 1)
				FirstTable[X.no][k] = 1;
		FirstTable[X.no][MaxTerminal + 1] = 1;
		return 1;
	}

	if (!(rules[CR].leftside.kind == 1 && rules[CR].leftside.no == X.no))
		goto Next_Rule;

	if (rules[CR].rleng == 0) {//epsilon
		first_result[MaxTerminal] = 1;
		goto Next_Rule;
	}

	i = 0;

Next_Element:
	if (rules[CR].rightside[i].kind == 0) {
		first_result[rules[CR].rightside[i].no] = 1;
		goto Next_Rule;
	}

	Yi_has_epsilon = 0;
	if (rules[CR].rightside[i].no != X.no) {
		if (FirstTable[rules[CR].rightside[i].no][MaxTerminal + 1] != 1)
			Compute_first_of_one_nonterminal(rules[CR].rightside[i]);

		for (k = 0; k < MaxTerminal; k++)
			if (FirstTable[rules[CR].rightside[i].no][k] == 1)
				first_result[k] = 1;
		if (FirstTable[rules[CR].rightside[i].no][MaxTerminal] == 1)
			Yi_has_epsilon = 1;
	}
	else {
		if (first_result[MaxTerminal] == 1)
			Yi_has_epsilon = 1;
	}

	if (Yi_has_epsilon == 0)
		goto Next_Rule;

	if (i == rules[CR].rleng - 1) {
		first_result[MaxTerminal] = 1;
		goto Next_Rule;
	}
	else {
		i++;
		goto Next_Element;
	}

}

// This function computes the follow of a nonterminal with index idx_NT.
int Compute_follow_of_one_nonterminal(int idx_NT) {
	int i, j, k, m;
	int first_result[MaxSymbols]; // one row of First table.
	sym SymString[10];

	for (i = 0; i < totalNumberOfRules; i++) {
		for (j = 0; j < rules[i].rleng; j++)
		{    //  the symbol of index j of the RHS of rule i is to be processed in this iteration
			if (rules[i].rightside[j].kind == 0 || rules[i].rightside[j].no != idx_NT) continue; // skip this symbol j.
			// Now, position j has a nonterminal which is equal to idx_NT.
			if (j < rules[i].rleng - 1) {  // there are symbols after position j in RHS of rule i.
				m = 0;
				for (k = j + 1; k < rules[i].rleng; k++, m++) SymString[m] = rules[i].rightside[k];
				SymString[m].kind = -1;  // end of string marker.
				Compute_first_of_any_string(SymString, first_result); // Compute the first of the string after position j of rule i.
				for (k = 0; k < MaxTerminal; k++) // Copy the first symbols of the remaining string to the Follow of idx_NT.
					if (first_result[k] == 1) {
						FollowTable[idx_NT][k] = 1;
					}
			}

			if (j == rules[i].rleng - 1 || first_result[MaxTerminal] == 1) // j is last symbol or first result has epsilon
			{
				if (rules[i].leftside.no == idx_NT) continue; // No need of adding the follow of the left side symbol
				if (FollowTable[rules[i].leftside.no][MaxTerminal] == 0) // We need follow of the left side sym of rule i.
					Compute_follow_of_one_nonterminal(rules[i].leftside.no);
				for (k = 0; k < MaxTerminal; k++) // add follow of left side symbol to follow of idx_NT.
					if (FollowTable[rules[i].leftside.no][k] == 1) {
						FollowTable[idx_NT][k] = 1;
					}
			}
		} // end of for j=0.
	} // end of for i
	FollowTable[idx_NT][MaxTerminal] = 1;  // put the completion mark for this nonterminal.
	return 1;
} // end of function Compute_follow_of_one_nonterminal.
int Compute_first_of_any_string(sym alpha[], int first_result[]) {
	int i, k;
	for (i = 0; i < MaxTerminal + 2; i++)
		first_result[i] = 0; // initialize the first result of alpha

	// Let alpha be Y0 Y1 ... Yn-1
	i = 0;
	do {
		if (alpha[i].kind == 0) {  // Yi is terminal
			first_result[alpha[i].no] = 1;
			break;
		}
		else if (alpha[i].kind == 1) { // Yi is nonterminal
			for (k = 0; k < MaxTerminal; k++)	 // copy first of Yi to first of alpha
				if (FirstTable[alpha[i].no][k] == 1) first_result[k] = 1;
			if (FirstTable[alpha[i].no][MaxTerminal] == 0)
				break; // first of Yi does not have epsilon.	
			else
				i = i + 1; // move to next Yi.
		}
		else if (alpha[i].kind == -1) {  // end of string mark.
			first_result[MaxTerminal] = 1; // if control reach here, all Yi's have epsilon in its first. Thus alpha has epsilon as first.
			break;
		}
	} while (1);
	return 1; // the first of alpha is passed thru parameter first_result.
} // end of function Compute_first_of_any_string
int lookUp_nonterminal(char* str) {
	int i;
	for (i = 0; i < MaxTerminal; i++)
		if (strcmp(str, Nonterminals_list[i].str) == 0)
			return i;
	return -1;
}

int lookUp_terminal(char* str) {
	int i;
	for (i = 0; i < MaxTerminal; i++)
		if (strcmp(str, Terminals_list[i].str) == 0)
			return i;
	return -1;
}

ty_ptr_item_node getLastItem(ty_ptr_item_node cs_list) {

	ty_ptr_item_node curr;
	curr = cs_list->link;
	while (curr) {
		if (!curr->link) {
			return curr;
		}
		curr = curr->link;
	}

}
void main() {
	int i, j;
	sym a_nonterminal = { 1, 0 };

	read_grammar("Grammar_data.txt");
	//non_terminal_list�� terminal_list, rule table�� �������

	strcpy(Terminals_list[MaxTerminal].str, "Epsilon");

	//initialize Fisrt and Follow tables
	for (i = 0; i < MaxNonTerminal; i++) {
		for (j = 0; j < MaxTerminal; j++) {
			FirstTable[i][j] = 0;
			FollowTable[i][j] = 0;
		}
		FirstTable[i][MaxTerminal + 1] = 0;
	}

	//compute first of all nonterminals
	for (i = 0; i < MaxNonTerminal; i++) {
		if (FirstTable[i][MaxTerminal + 1] == 0) {
			a_nonterminal.no = i;
			Compute_first_of_one_nonterminal(a_nonterminal);
		}
	}

	FollowTable[0][MaxTerminal - 1] = 1;
	for (i = 0; i < MaxNonTerminal; i++) {
		if (FollowTable[i][MaxTerminal] == 0)
			Compute_follow_of_one_nonterminal(i);
	}

	for (i = 0; i < MaxNonTerminal; i++) {
		printf("First(%s): ", Nonterminals_list[i].str);
		for (j = 0; j < MaxTerminal; j++) {
			if (FirstTable[i][j] == 1)
				printf("%s  ", Terminals_list[j].str);
		}
		if (FirstTable[i][MaxTerminal] == 1)
			printf("epsilon");
		printf("\n");
	}

	printf("\n");
	for (i = 0; i < MaxNonTerminal; i++) {
		printf("Follow(%s): ", Nonterminals_list[i].str);
		for (j = 0; j < MaxTerminal; j++) {
			if (FollowTable[i][j] == 1)
				printf("%s  ", Terminals_list[j].str);
		}
		printf("\n");
	}

	ty_ptr_item_node ItemSet0, tptr;

	tptr = (ty_ptr_item_node)malloc(sizeof(type_item));
	tptr->RuleNum = 0;
	tptr->DotNum = 0;
	tptr->link = NULL;

	ItemSet0 = closure(tptr);

	makeGotoGraph(ItemSet0);
	printGotoGraph(States_And_Arcs);
	Make_Action_Table();
	print_Action_Table();
	Make_Goto_Table();
	print_Goto_Table();

	fps = fopen("source.txt", "r");
	Root = Parsing(fps);
	fclose(fps);

	FILE *fpo;
	fpo = fopen("output.txt", "w");
	print_parse_tree(fpo, Root, 0, 0, 0);
	fclose(fpo);

	printf("Program terminates.\n");
}