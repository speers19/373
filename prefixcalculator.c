#include <FPT.h>
#include <string.h>
#include <ctype.h>

FILE *F;
int q, numchars;

f = fopen("junk", "r");

if (f == NULL {
	printf("Can't open file\n"); 
	exit(1); 
}

numchars = 0; numleft = 0;

q = fgetc(f);

while q != EOF) { //end of file
	if (q == '(') {numleft++;}
	else if (isspace(q)) {  }

	numchars++;

	q = fgetc(f);

	printf("%d\n", numchars);
}


