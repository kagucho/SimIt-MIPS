void testing() {
  printf("Hi mom\n");
}

void test2() {
  printf("Wrong\n");
}

main(int argc, char *argv[])
{
  void (*test)();

  test = argc > 1 ? test2 : testing;
  (*test)();
}
