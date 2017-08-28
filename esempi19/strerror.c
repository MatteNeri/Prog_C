#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
  int a = printf("prima\n");
  char *s = strerror(E2BIG);
  printf("dopo\n""%s\n%p\n", s, s);
  /* printf("%s\n%p\n", s, s); */
  /* free(s); //BANG! */
}
