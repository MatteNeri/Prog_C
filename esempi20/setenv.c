#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
  lanciarlo in due modi:

  ./setenv

  e

  key1=val2 key2=val0 ./setenv
 */

int main() {
  setenv("key1", "val1", 0);
  putenv("key2=val2");
  setenv("key2", "val3", 1);
  putenv("key3=val3");
  setenv("key3", "val4", 1);
  putenv("key4=val4");
  system("echo $key1 $key2 $key3 $key4"); /* si poteva fare con getenv... */
}
