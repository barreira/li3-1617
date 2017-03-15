#include <stdlib.h>
#include <string.h>

#include "avl.h"

#define BACKUPS 3

#define A_TITLE 30
#define A_ID    5
#define R_TEXT  1024
#define R_ID    10
#define R_TIME  20
#define C_ID    10
#define C_NAME  15

#define LEFTBAL 1;
#define RIGHTBAL 2;

struct article {
	char* title;
	char* id;
};

struct revision {
	char* id;
	char* timestamp;
	char* text;
};

struct contribution {
	char* id;
	char* name;
};

struct page {
	ARTICLE a;
	REVISION* r;     // array de revisões
	CONTRIBUTION* c; // array de contribuições
	int appears[BACKUPS];
	int height;
	struct page *left, *right;
};

struct avl {
	int total;
	PAGE page;
};


// Inits

ARTICLE initArticle() {
	ARTICLE a = malloc(sizeof(struct article));
	a->title = malloc(A_TITLE * sizeof(char));
	a->id = malloc(A_ID * sizeof(char));
	return a;
}

REVISION initRevision() {
	REVISION r = malloc(sizeof(struct revision));
	r->id = malloc(R_ID * sizeof(char));
	r->timestamp = malloc(R_TIME * sizeof(char));
	r->text = malloc(R_TEXT * sizeof(char));
	return r;
}

CONTRIBUTION initContribution() {
	CONTRIBUTION c = malloc(sizeof(struct contribution));
	c->id = malloc(C_ID * sizeof(char));
	c->name = malloc(C_NAME * sizeof(char));
	return c;
}

PAGE initPage() {
	int i;
	PAGE p = malloc(sizeof(struct page));
	p->a = initArticle();
	p->r[0] = initRevision();
	p->c[0] = initContribution();
	//p->height = 0;
	appears = malloc(BACKUPS * sizeof(int))
	for (i = 0; i < BACKUPS; i++) appears[i] = 0;
	p->left = NULL;
	p->right = NULL;
	return p;
}

AVL initAvl() {
	AVL a = malloc(sizeof(struct avl));
	a->page = initPage();
	a->total = 0;
	return a;
}

// Inserts

REVISION getRevision(PAGE p) {
	int i = 0;

	while (p->r[i] != NULL) i++;

	i--;
	return p->r[i];
}

PAGE insertPage(PAGE p, char* title, char* a_id, char* r_id, char* timestamp, char* text, char* c_id, char* name, int backup) {
	int ls, rs, bal, HL, HR, cp;

	if (p == NULL) {
		p = initPage();
		strcpy(p->a->title, title);
		strcpy(p->a->title, a_id);
		strcpy(p->a->text, text);
		strcpy(p->r[0]->id, r_id);
		strcpy(p->r[0]->timestamp, timestamp);
		strcpy(p->c[0]->id, c_id);
		strcpy(p->c[0]->name, name);
		p->height = 0;
	} 
	else {
		if (p->a->id == a_id) {
			int rev = getRevision(p)->id;
			if (rev == r_id) {
				p->appears[backup-1] = 1;
			} 
			else {
				insertRevision(p, r_id, timestamp);
				insertContributor(c_id, name);
			}
		}
		else if (p->a->id > a_id) p->left = insert(p->left, title, a_id, text, r_id, timestamp, c_id, name);
		else if (p->a->id < a_id) p->right = insert(p->right, title, a_id, text, r_id, timestamp, c_id, name);
		
		if (p->a->id > a_id || p->a->id < a_id) {
			HL = heightAvl(p->left);
			HR = heightAvl(p->right);

			p->height = maior(HL,HR) + 1;

			bal = HL - HR;

			if (bal > 1) bal = RIGHTBAL;
			if (bal < -1) bal = LEFTBAL;

			switch (bal) {

				case RIGHTBAL: if ((ls=strcmp(line,estrutura->left->code)) < 0)
							return rotateRight(estrutura);
						else if (ls>0){
							estrutura->left =  rotateLeft(estrutura->left);
							return rotateRight(estrutura);
						}
						break;

				case LEFTBAL:
					if ((rs = strcmp(line,estrutura->right->code)) > 0) return rotateLeft(p);
					else if (rs < 0){
						estrutura->right = rotateRight(estrutura->right);
						return rotateLeft(estrutura);
					}	
					break;
			}
		}
	}
	return p;
}

AVL insertAvl(AVL a, char* title, char* a_id, char* r_id, char* timestamp, char* text, char* c_id, char* name, int backup) {
	if (a == NULL) a = initAvl();

	a->page = insertPage(a->page, title, a_id, r_id, timestamp, text, c_id, name, backup);
	(a->total)++;

	return a;
} 

