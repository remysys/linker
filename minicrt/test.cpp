#include "iostream.h"
#include "cstring.h"

using namespace std;

string global_str("global string");

int main(int argc, char* argv[]) {

  // test malloc and stdio
  
  int i;
  FILE* fp;
  char **v = (char **)malloc(argc * sizeof(char *));
  
  for(i = 0; i < argc; ++i) {
    v[i] = (char *)malloc(strlen(argv[i]) + 1);
    strcpy(v[i], argv[i]);
  }

  
  fp = fopen("test.txt", "w");
  for(i = 0; i < argc; ++i) {
    int len = strlen(v[i]);
    fwrite(&len, 1, sizeof(int), fp);
    fwrite(v[i], 1, len, fp);
  }
  fclose(fp);

  fp = fopen("test.txt", "r");
  for(i = 0; i < argc; ++i) {
    int len;
    char* buf;
    fread(&len, 1, sizeof(int), fp);
    buf = (char *)malloc(len + 1);
    fread(buf, 1, len, fp);
    buf[len] = '\0';
    printf("%d %s\n", len, buf);
    free(buf);
    free(v[i]);
  }

  fclose(fp);
  
  // test printf 
  int num = 15;
  const char *str = "world";
  printf("num = %d num = 0x%x\n", num, num);
  printf("hello %s\n", str);

  // test global object construct and destruct
  cout << global_str << endl;
  

  return 0;
}