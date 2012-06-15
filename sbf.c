#include <stdio.h>

#define MEMSIZE 1024*4

FILE *srcfile;
char src[MEMSIZE];
char mem[MEMSIZE];
char *ip = mem;

void interpret() {
  
}

int main(int argc, char *argv[] ) {
  if (argc != 2) {
    printf("Usage: %s sourcefile\n", argv[0]);
  }
  else {
    srcfile = fopen(argv[1], "r");
    if (srcfile == 0) {
      printf("Couldn't open the source file.\n");
    }
    else {
      int c = 0;
      int buf;
      int i = 0;
      while ( ( buf = fgetc(srcfile) ) != EOF ) {
        src[c] = buf;
        c++;
      }
      for (i = 0; i < c; i++)
        printf("%c", src[i]);
    }
  }
	return 0;
}

