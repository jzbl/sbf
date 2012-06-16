#include <stdio.h>

#define MEMSIZE 30000
#define BF_RIGHT '>'
#define BF_LEFT '<'
#define BF_INC '+'
#define BF_DEC '-'
#define BF_OUT '.'
#define BF_IN ','
#define BF_LOOPS '[' 
#define BF_LOOPE ']'

FILE *srcfile;
int srclen = 0;
char src[MEMSIZE];
char mem[MEMSIZE];
char *ip = src;
char *dp = mem;

int interpret() {
  for (;;) { 
  switch (*ip) {
    case BF_RIGHT:
      ++dp;
      break;
    case BF_LEFT:
      --dp;
      break;
    case BF_INC:
      ++(*dp);
      break;
    case BF_DEC:
      --(*dp);
      break;
    case BF_OUT:
      putchar(*dp);
      break;
    case BF_IN:
      *dp=(int)getchar();
      break;
  }
  if (srclen == 0)
    break;
  else
    ip++;
    srclen--;
  }
  return 0;
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
      /* int i = 0; */
      while ( ( buf = fgetc(srcfile) ) != EOF ) {
        src[c] = buf;
        c++;
      }
      srclen = c;
      /* for (i = 0; i < c; i++)
        printf("%c", src[i]); */
      interpret();
      printf("\n");
    }
  }
	return 0;
}

