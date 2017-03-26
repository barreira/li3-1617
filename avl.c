#include <stdlib.h>
#include <string.h>

#include "avl.h"

#define SIZE_A_ID       5
#define SIZE_R_ID       10
#define SIZE_TIMESTAMP  20
#define SIZE_TEXT       1024
#define SIZE_TITLE      30
#define SIZE_C_ID       10
#define SIZE_NAME       15


// Definição das estruturas

struct contribution {
	char* id;
	char* name;
};

struct revision {
	char* id;
	char* timestamp;
	char* title;
	char* text;
	CONTRIBUTION c;
};

struct page {
	char* article_id;
	REVISION* rev;
	int height;
	struct page *left, *right;
};

// Funções auxiliares

int greater(int a, int b) {
	return (a > b) ? a : b;
}

int getHeight(PAGE p) {
	return (p) ? p->height : 0;
}

int getNumRevisions(PAGE p) {
	int i;
	for (i = 0; p->rev[i]; i++);
	return i;
}

PAGE updateHeight(PAGE a, PAGE b){
	a->height = greater(getHeight(a->left), getHeight(a->right)) + 1;
	b->height = greater(getHeight(b->left), getHeight(b->right)) + 1;
	return b;
}

PAGE rotateRight(PAGE p) {
	PAGE tmp;

	tmp = p->left;
	p->left = tmp->right;
	tmp->right = p;
	tmp = updateHeight(p, tmp);

	return tmp;
}

PAGE rotateLeft(PAGE p) {
	PAGE tmp;

	tmp = p->right;
	p->right = tmp->left;
	tmp->left = p;
	tmp = updateHeight(p, tmp);

	return tmp;
}

// Inicialização das estruturas

PAGE initPage() {
	return NULL;
}

// Inserções nas estruturas

PAGE insertPage(PAGE p, char* a_id, char* r_id, char* timestamp, char* title, char* text, char* c_id, char* name) {
	if (!p) {
		p = malloc(sizeof(struct page));
		p->article_id = malloc(SIZE_A_ID);
		p->rev[0] = malloc(sizeof(struct revision)); /* é necessária esta linha? */
		p->rev[0]->id = malloc(SIZE_R_ID);
		p->rev[0]->timestamp = malloc(SIZE_TIMESTAMP);
		p->rev[0]->title = malloc(SIZE_TITLE);
		p->rev[0]->text = malloc(SIZE_TEXT);
		p->rev[0]->c = malloc(sizeof(struct contribution)); /* é necessária esta linha? */
		p->rev[0]->c->id = malloc(SIZE_C_ID);
		p->rev[0]->c->name = malloc(SIZE_NAME);
		p->height = 0;
		p->left = NULL;
		p->right = NULL;

		strcpy(p->article_id, a_id);
		strcpy(p->rev[0]->id, r_id);
		strcpy(p->rev[0]->timestamp, timestamp);
		strcpy(p->rev[0]->title, title);
		strcpy(p->rev[0]->text, text);
		strcpy(p->rev[0]->c->id, c_id);
		strcpy(p->rev[0]->c->name, name);
	}

	else {
		int cmp = strcmp(p->article_id, a_id);

		if (cmp > 0) {
			p->left = insertPage(p->left, a_id, r_id, timestamp, title, text, c_id, name);
		}

		else if (cmp < 0) {
			p->right = insertPage(p->right, a_id, r_id, timestamp, title, text, c_id, name);
		}

		else {
			int nr = getNumRevisions(p);
			nr++;
			p->rev[nr] = malloc(sizeof(struct revision)); /* é necessária esta linha? */
			p->rev[nr]->id = malloc(SIZE_R_ID);
			p->rev[nr]->timestamp = malloc(SIZE_TIMESTAMP);
			p->rev[nr]->title = malloc(SIZE_TITLE);
			p->rev[nr]->text = malloc(SIZE_TEXT);
			p->rev[nr]->c = malloc(sizeof(struct contribution)); /* é necessária esta linha? */
			p->rev[nr]->c->id = malloc(SIZE_C_ID);
			p->rev[nr]->c->name = malloc(SIZE_NAME);

			strcpy(p->rev[nr]->id, r_id);
			strcpy(p->rev[nr]->timestamp, timestamp);
			strcpy(p->rev[nr]->title, title);
			strcpy(p->rev[nr]->text, text);
			strcpy(p->rev[nr]->c->id, c_id);
			strcpy(p->rev[nr]->c->name, name);
		}
		
		if (cmp) {
			int hl = getHeight(p->left);
			int hr = getHeight(p->right);
			p->height = greater(hl, hr) + 1;

			int bal = hl-hr;

			if (bal > 1) { /* right bal */
				int lcmp = strcmp(a_id, p->left->article_id);

				if (lcmp < 0) {
					return rotateRight(p);
				}
				
				else if (lcmp > 0) {
					p->left = rotateLeft(p->left);
					return rotateRight(p);
				}
			}

			else if (bal < -1) { /* left bal */
				int rcmp = strcmp(a_id, p->right->article_id);

				if (rcmp > 0) {
					return rotateLeft(p);
				}

				else if (rcmp < 0) {
					p->right = rotateRight(p->right);
					return rotateLeft(p);
				}
			}
		}
	}

	return p;
}

AVL insert(AVL a, char* a_id, char* r_id, char* timestamp, char* title, char* text, char* c_id, char* name) {
	if (!a) {
		a = initAvl();
	}

	a->page = insertPage(a->page, a_id, r_id, timestamp, title, text, c_id, name);
	(a->total)++;

	return a;
}

// Testar existência de uma page numa AVL

int existsPage(PAGE p, char* a_id) {
	int res = 0;
	int cmp = strcmp(p->article_id, a_id);

	if (cmp == 0) {
		return 1;
	}
	else if (cmp > 0 && p->left) {
		res = existsPage(p->left, a_id);
	}
	else if (p->right) {
		res = existsPage(p->right, a_id);
	}

	return res;
}

int exists(AVL a, char* a_id) {
	int res = existsPage(a->page, a_id);
	return res;
}

// Total de pages numa AVL

int totalPages(AVL a) {
	return (a) ? a->total : 0;
}