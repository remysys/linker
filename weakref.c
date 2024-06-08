__attribute__((weak)) void foo();

int main()
{
  // foo();
  if (foo) foo();
  return 0;
}
