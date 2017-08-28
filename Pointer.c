int main(){
  int a = 10;
  int *aPtr = &a;
  printf("%d %d\n", a, aPtr);
  aPtr++;
  printf("%d\n", aPtr);
  aPtr--;
  printf("%d\n", *aPtr);
}
