#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct state
{
	enum{Q0, Q1, Q2, Q3, Q4, D} label;
	struct state *on_a;
	struct state *on_b;
	enum{NO, YES} isFinal;
} state;

state *q0 = NULL;

createTransitionDiagram()
{
	q0 = malloc(sizeof(state));
	state *q1 = malloc(sizeof(state));
	state *q2 = malloc(sizeof(state));
	state *q3 = malloc(sizeof(state));
	state *q4 = malloc(sizeof(state));
	state *d = malloc(sizeof(state));
	
	q0->label = Q0;
	q0->on_a = q1;
	q0->on_b = q3;
	q0->isFinal = NO;
	
	q1->label = Q1;
	q1->on_a = q2;
	q1->on_b = q2;
	q1->isFinal = YES;
	
	q2->label = Q2;
	q2->on_a = q1;
	q2->on_b = d;
	q2->isFinal = YES;
	
	q3->label = Q3;
	q3->on_a = q4;
	q3->on_b = q4;
	q3->isFinal = YES;
	
	q4->label = Q4;
	q4->on_a = d;
	q4->on_b = q3;
	q4->isFinal = YES;
	
	d->label = D;
	d->on_a = d;
	d->on_b = d;
	d->isFinal = NO;
	
}

verify(char *s)
{
	int i;
	state *current = malloc(sizeof(state));
	current = q0;
	char st[3];
	
	for (i = 0; i < strlen(s); i += 1) {
	
		//Printing configuration
		switch(current->label) {
			case 0: strcpy(st, "Q0"); break;
			case 1: strcpy(st, "Q1"); break;
			case 2: strcpy(st, "Q2"); break;
			case 3: strcpy(st, "Q3"); break;
			case 4: strcpy(st, "Q4"); break;
			case 5: strcpy(st, "D"); break;
			default: perror("Switch"); exit(-1);
		}
		printf("(%s, %s)\n", st, s+i);
		
		if(*(s+i) == 'a') {
			current = current->on_a;
		} else if(*(s+i) == 'b') {
			current = current->on_b;
		} else {
			perror("Invalid string");
			exit(-1);
		}
			
	}
	
	//Printing configuration
	switch(current->label) {
		case 0: strcpy(st, "Q0"); break;
		case 1: strcpy(st, "Q1"); break;
		case 2: strcpy(st, "Q2"); break;
		case 3: strcpy(st, "Q3"); break;
		case 4: strcpy(st, "Q4"); break;
		case 5: strcpy(st, "D"); break;
		default: perror("Switch"); exit(-1);
	}
	printf("(%s, %s)\n", st, "e");
		
	if (current->isFinal == YES) {
		printf("Accepted\n");
	} else if (current->isFinal == NO) {
		printf("Rejected\n");
	}
}

int main (int argc, char *argv[])
{
	if(argc != 2) {
		printf("Usage: \n./a.out \"Input String\"\n");
		exit(-1);
	}
	
	createTransitionDiagram();
	
	verify(argv[1]);
	
	return 0;
}
