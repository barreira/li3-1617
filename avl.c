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

// Funções auxilares

int maior(int a, int b) {
	return (a > b) ? a : b;
}

int heightAvl(PAGE p) {
	if (p == NULL) return 0;
	return p->height;
}

PAGE updateHeight(PAGE a, PAGE b) {
	a->height = maior(heightAvl(a->left), heightAvl(a->right)) + 1;
	b->height = maior(heightAvl(b->left), heightAvl(b->right)) + 1;
	return b;
}

PAGE rotateRight(PAGE p) {
	PAGE aux;
	aux = p->left;
	p->left = aux->right;
	aux->right = p;
	aux = updateHeight(p, aux);
	return aux;	
}

PAGE rotateLeft(PAGE p) {
	PAGE aux;
	aux = p->right;
	p->right = aux->left;
	aux->left = p;
	aux = updateHeight(p, aux);
	return aux;
}

// Inits

ARTICLE initArticle() {
	return NULL;
}

REVISION initRevision() {
	return NULL;
}

CONTRIBUTION initContribution() {
	return NULL;
}

PAGE initPage() {
	return NULL;
}

AVL initAvl() {
	AVL a = malloc(sizeof(struct avl));
	a->page = initPage();
	a->total = 0;
	return a;
}

PAGE initStructs(PAGE p, char* title, char* a_id, char* r_id, char* timestamp, char* text, char* c_id, char* name, int backup) {
	p = malloc(sizeof(struct page));
	p->a = malloc(sizeof(struct article));
	p->r[0] = malloc(sizeof(struct revision));
	p->c[0] = malloc(sizeof(struct contribution));
	p->appears = malloc(BACKUPS * sizeof(int));
	p->height = 0;
	p->left = NULL;
	p->right = NULL;
	p->a->title = malloc(A_TITLE * sizeof(char));
	p->a->id = malloc(A_ID * sizeof(char));
	p->r[0]->id = malloc(R_ID * sizeof(char));
	p->r[0]->timestamp = malloc(R_TIME * sizeof(char));
	p->r[0]->text = malloc(R_TEXT * sizeof(char));
	p->c[0]->id = malloc(C_ID * sizeof(char));
	p->c[0]->name = malloc(C_NAME * sizeof(char));	
	return p;
}

// Inserts

REVISION getRevision(PAGE p) {
	int i = 0;

	while (p->r[i] != NULL) i++;

	i--;
	return p->r[i];
}

int getLastRevison(PAGE p) {
	int i;

	while (p->r[i] != NULL) i++;

	return i;
}

REVISION insertRevision(PAGE p, char* id, char* timestamp, char* text) {

	return ;
}

CONTRIBUTION insertContribution(PAGE p, char* id, char* name) {

	return ;
}

PAGE insertPage(PAGE p, char* title, char* a_id, char* r_id, char* timestamp, char* text, char* c_id, char* name, int backup) {
	if (p == NULL) {
		p = initStructs(p, title, a_id, r_id, timestamp, text, c_id, name, backup);
		strcpy(p->a->title, title);
		strcpy(p->a->id, a_id);
		strcpy(p->r[0]->id, r_id);
		strcpy(p->r[0]->timestamp, timestamp);
		strcpy(p->r[0]->text, text);
		strcpy(p->c[0]->id, c_id);
		strcpy(p->c[0]->name, name);
	} 
	else {
		if (p->a->id == a_id) { /* tem de ser strcmp */
			int rev = getRevision(p)->id;
			
			if (rev == r_id) p->appears[backup-1] = 1;
			
			else {
				int lr = getLastRevison(PAGE p);
				p->r[lr] = insertRevision(p, r_id, timestamp, text);
				p->c[lr] = insertContribution(p, c_id, name);
			}
		}
		else if (p->a->id > a_id) p->left = insertPage(p->left, title, a_id, text, r_id, timestamp, c_id, name);
		else if (p->a->id < a_id) p->right = insertPage(p->right, title, a_id, text, r_id, timestamp, c_id, name);

		if (p->a->id > a_id || p->a->id < a_id) {
			hl = heightAvl(p->left);
			hr = heightAvl(p->right);

			p->height = maior(hl, hr) + 1;

			bal = hl - hr;

			if (bal > 1) bal = RIGHTBAL;
			if (bal < -1) bal = LEFTBAL;

			switch (bal) {
				case RIGHTBAL:
					if (a_id < p->left->a->id) return rotateRight(p);
					else if (a_id > p->left->a->id) {
						p->left = rotateLeft(p->left);
						return rotateRight(p);
					}
					break;

				case LEFTBAL:
					if (a_id > p->right->a->id) return rotateLeft(p);
					else if (a_id < p->right->a->id) {
						p->right = rotateRight(p->right);
						return rotateLeft(p);
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

