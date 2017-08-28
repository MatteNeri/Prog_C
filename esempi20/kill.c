#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main( int argc, char **argv )
{
  kill( atoi(argv[1]), atoi(argv[2]) );

  return EXIT_SUCCESS;
}
