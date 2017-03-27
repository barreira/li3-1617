#include <stdio.h>

#include "interface.h"

int main() {
	AVL a = init();

	char* sp[] = {"snapshot_dec16"};

	load(a, 1, sp);

	return 0;
}