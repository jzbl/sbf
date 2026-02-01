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

int build_bracket_map(int len, int *map) {
  int stack[MEMSIZE];
  int sp = 0;
  int i;

  for (i = 0; i < len; i++) {
    if (src[i] == BF_LOOPS) {
      if (sp >= MEMSIZE) {
        printf("Bracket stack overflow.\n");
        return -1;
      }
      stack[sp++] = i;
    } else if (src[i] == BF_LOOPE) {
      if (sp == 0) {
        printf("Unmatched closing bracket at %d.\n", i);
        return -1;
      }
      sp--;
      map[i] = stack[sp];
      map[stack[sp]] = i;
    }
  }

  if (sp != 0) {
    printf("Unmatched opening bracket at %d.\n", stack[sp - 1]);
    return -1;
  }

  return 0;
}

int interpret(int *bracket_map) {
  int ip = 0;
  int dp = 0;

  while (ip < srclen) {
    switch (src[ip]) {
      case BF_RIGHT:
        ++dp;
        break;
      case BF_LEFT:
        --dp;
        break;
      case BF_INC:
        ++mem[dp];
        break;
      case BF_DEC:
        --mem[dp];
        break;
      case BF_OUT:
        putchar(mem[dp]);
        break;
      case BF_IN:
        mem[dp] = (int)getchar();
        break;
      case BF_LOOPS:
        if (mem[dp] == 0)
          ip = bracket_map[ip];
        break;
      case BF_LOOPE:
        if (mem[dp] != 0)
          ip = bracket_map[ip];
        break;
      default:
        break;
    }
    ip++;
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
      int bracket_map[MEMSIZE];
      int i;
      /* int i = 0; */
      while ( ( buf = fgetc(srcfile) ) != EOF ) {
        src[c] = buf;
        c++;
      }
      srclen = c;
      for (i = 0; i < MEMSIZE; i++)
        mem[i] = 0;
      /* for (i = 0; i < c; i++)
        printf("%c", src[i]); */
      if (build_bracket_map(srclen, bracket_map) != 0) {
        fclose(srcfile);
        return 1;
      }
      interpret(bracket_map);
      printf("\n");
    }
  }
	return 0;
}
