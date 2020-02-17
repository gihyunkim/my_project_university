#include <stdio.h>
#define MaxTerminal			13 
#define MaxNonterminal		6


typedef struct ssym {
	int kind; // 0 if terminal; 1 if nonterminal; -1 if dummy symbol indicating the end mark.
	int no; // the unique index of a symbol.
} sym;  // definition symbols 

// Rules are represented as follows
typedef struct orule {  // rule 한 개의 정
	sym leftside;
	sym rightside[10];
	int  rleng;  // RHS 의 심볼의 수.  0 is given if righthand side is epsilon.
} onerule;
typedef struct twoints {
	int cr;
	int elm;
} element_stack;

int Compute_first_of_one_nonterminal(sym);
int Compute_follow_of_one_nonterminal(int);
int Compute_first_of_any_string(sym[], int[]);

/****GRAMMAR ***********************************************************************************************************/
// Terminals:
//  id	 num  :=	;	+	  -	   *	/	(	)	{	}	$
//   0    1    2    3    4    5    6	7	8	9	10	11	12
//
// Nonterminals:
//   L	  S	   A	E	 T	  F
//   0    1    2    3    4	  5
//

char Names_of_nonterminals[MaxNonterminal][10] = { "L","S","A","E","T","F" };
char Names_of_terminals[MaxTerminal][10] = { "id", "num", ":=", ";", "+", "-", "*","/","(",")","{","}","$" };

#define MaxNumberOfRules	14  
onerule rules[MaxNumberOfRules] = {
	{ { 1, 0 },		{ { 1, 2 }, { 1, 1 } },	 2 },	// L -> A S    	rule0

	{ { 1, 1 },		{},						 0 },	// S -> epsilon    rule1

	{ { 1, 1 },		{ { 1, 2 },	{ 1, 1 } },	 2 },	// S -> A S 	rule2

	{ { 1, 2 },		{ { 0, 0 }, { 0, 2 }, { 1, 3 }, { 0, 3} },	4 },	// A -> id := E ;	    rule3

	{ { 1, 2 },		{ { 0, 10 }, { 1, 1 }, { 0, 11 } },	3 },		// A -> { S } 	rule4

	{ { 1, 3 },		{ { 1, 4 } } ,	1 },	// E -> T		rule5

	{ { 1, 3 },		{ { 1, 3 }, { 0, 4 }, { 1, 4 } },	3 },	// E -> E + T       rule6

	{ { 1, 3 },		{ { 1, 3 }, { 0, 5 }, { 1, 4 } },	3 },// E -> E - T   rule7

	{ { 1, 4 },		{ { 1, 5 } }, 1}, // T -> F		rule 8

	{ { 1, 4 },		{ { 1, 4 }, { 0 , 6 }, { 1, 5 } }, 3}, // T -> T * F		rule 9

	{ { 1, 4 },		{ { 1, 4 }, { 0 , 7 }, { 1, 5 } }, 3}, // T -> T / F		rule 10

	{ { 1, 5 },		{ { 0, 8 }, { 1, 3 }, { 0, 9 } }, 3 }, // F -> ( E )		rule 11

	{ { 1, 5 },		{ { 0, 0 } }, 1}, // F -> id	rule 12

	{ { 1, 5 },		{ { 0, 1 } }, 1}, // F -> num	rule 13



};
/****GRAMMAR ***********************************************************************************************************/

int FirstTable[MaxNonterminal][MaxTerminal + 2]; // +2 was done for epsilon and done-mark.
int FollowTable[MaxNonterminal][MaxTerminal + 1]; // +1 was done for done-mark.

int main()
{
	int i, j;
	sym a_nonterminal = { 1, 0 };
	int first_result[MaxTerminal + 2];
	sym symstring1[5] = { {1,1}, {1,3},   {-1, 0} };   //  S E

	// initialze First and Follow tables.
	for (i = 0; i < MaxNonterminal; i++) {
		for (j = 0; j < MaxTerminal + 1; j++) {
			FirstTable[i][j] = 0;
			FollowTable[i][j] = 0;
		}
		FirstTable[i][MaxTerminal + 1] = 0;
	}

	// Compute first of all nonterminals
	for (i = 0; i < MaxNonterminal; i++)
		if (FirstTable[i][MaxTerminal + 1] == 0) {  // first compute is done only when it's not done yet.
			a_nonterminal.no = i;
			Compute_first_of_one_nonterminal(a_nonterminal);
		}

	//print first table
	for (int m = 0; m < MaxNonterminal; m++) {
		printf("first of %s :", Names_of_nonterminals[m]);
		for (int n = 0; n < MaxTerminal + 1; n++) {
			if (FirstTable[m][n] == 1) {
				if (n == MaxTerminal) {
					printf("    ep");
				}
				else
					printf("    %s", Names_of_terminals[n]);
			}
		}
		printf("\n");
	}

	// Compute follow of all nonterminals
	FollowTable[0][MaxTerminal - 1] = 1; // make $ to be a follow symbol of the starting nonterminal.
	for (i = 0; i < MaxNonterminal; i++) {
		if (FollowTable[i][MaxTerminal] == 0) // if follow of nonterminal i was not done, compute it.
			Compute_follow_of_one_nonterminal(i);

	}

	//print follow table
	for (int m = 0; m < MaxNonterminal; m++) {
		printf("follow of %s :", Names_of_nonterminals[m]);
		for (int n = 0; n < MaxTerminal + 1; n++) {
			if (FollowTable[m][n] == 1) {
				printf("    %s", Names_of_terminals[n]);
			}
		}
		printf("\n");
	}

	// Experiment 1: compute first of the string  E' F  in symstring1 
	Compute_first_of_any_string(symstring1, first_result);
	// Print out the result of the first computation.
	printf("first of string  SE :  ");
	for (i = 0; i < MaxTerminal + 1; i++) {
		if (first_result[i] == 1)
			printf("%s   ", Names_of_terminals[i]);
	}
	printf("\n");
	getchar();

} // main.

// alpha is an arbitrary string of terminals or nonterminals. A dummy symbol with kind = -1 must be place at the end.
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

int Compute_first_of_one_nonterminal(sym X) {
	int i, j, k, CR = -1;
	element_stack es;
	element_stack Stack[100];
	int top = -1;

	int first_result[MaxTerminal + 2];  // this is used for storing the processing result of symbol X.

	for (i = 0; i < MaxTerminal + 2; i++) first_result[i] = 0; // initialize.

Next_Rule:
	CR++;
	if (CR >= MaxNumberOfRules) goto Process_Stop_Points;  // all X-rules were tried.
	if (!(rules[CR].leftside.kind == 1 && rules[CR].leftside.no == X.no)) // find a X-rule.
		goto Next_Rule;
	if (rules[CR].rleng == 0) { // this is epsilon rule
		first_result[MaxTerminal] = 1;  // add epsilon to the first of X.
		goto Next_Rule;
	}
	i = 0;

Next_Element:
	if (!(rules[CR].rightside[i].kind == 1 && rules[CR].rightside[i].no == X.no)) { // Yi differs from X
		if (rules[CR].rightside[i].kind == 0) {  // Yi is terminal
			first_result[rules[CR].rightside[i].no] = 1; // add Yi as first of X
			goto Next_Rule;
		}
		else {  // Yi is nonterminal
			if (FirstTable[rules[CR].rightside[i].no][MaxTerminal + 1] != 1) // first compute for Yi was not done.
				Compute_first_of_one_nonterminal(rules[CR].rightside[i]); // first computation for Yi is executed.
			for (k = 0; k < MaxTerminal; k++) // copy except epsilon.
				if (FirstTable[rules[CR].rightside[i].no][k] == 1)
					first_result[k] = 1;
			if (FirstTable[rules[CR].rightside[i].no][MaxTerminal] == 0) // epsilon is not in first of Yi?
				goto Next_Rule;
			if (i == rules[CR].rleng - 1) { // Yi is the last element of RHS.
				first_result[MaxTerminal] = 1;  // add epsilon to first of X.
				goto Next_Rule;
			}
			i++; goto Next_Element; // Yi was not the last one. So move to the next element.
		}
	}
	else { // Yi is X. So case 1 has occurred.
		es.cr = CR; es.elm = i;
		top++; Stack[top] = es;    //  push ( es ) ; // store the stopping point to the stack.
		goto Next_Rule;
	}

Process_Stop_Points:
	if (top < 0) { // Stack is empty. So, save the first result of X and terminate the function.
		for (k = 0; k < MaxTerminal + 1; k++)
			if (first_result[k] == 1)
				FirstTable[X.no][k] = 1;
		FirstTable[X.no][MaxTerminal + 1] = 1;  // place a done mark for this nonterminal.
		return 1;
	}

	CR = Stack[top].cr; j = Stack[top].elm; top--; // pop stack.

Process_X:
	if (first_result[MaxTerminal] == 0) // no epsilon in first of X yet.
		goto Process_Stop_Points;

Next_Sym:
	if (j == rules[CR].rleng - 1) { first_result[MaxTerminal] = 1; goto Process_Stop_Points; }
	j++;
	if (rules[CR].rightside[j].kind == 1 && rules[CR].rightside[j].no == X.no) goto Process_X;

	// Yj is not X.
	if (rules[CR].rightside[j].kind == 0) {  // Yj is terminal
		first_result[rules[CR].rightside[j].no] = 1; // add Yj as first of X
		goto Process_Stop_Points;
	}
	else {  // Yj is nonterminal
		if (FirstTable[rules[CR].rightside[j].no][MaxTerminal + 1] != 1) // first compute for Yj was not done.
			Compute_first_of_one_nonterminal(rules[CR].rightside[j]); // first computation for Yi is executed.
		for (k = 0; k < MaxTerminal; k++) // copy except epsilon.
			if (FirstTable[rules[CR].rightside[j].no][k] == 1)
				first_result[k] = 1;
		if (FirstTable[rules[CR].rightside[j].no][MaxTerminal] == 1) // epsilon is in first of Yj?
			goto Next_Sym;
		else
			goto Process_Stop_Points;
	}
} // end of function First_Compute_One_Symbol

// This function computes the follow of a nonterminal with index idx_NT.
int Compute_follow_of_one_nonterminal(int idx_NT) {
	int i, j, k, m;
	int first_result[MaxTerminal + 2]; // one row of First table.
	sym SymString[10];

	for (i = 0; i < MaxNumberOfRules; i++) {
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

