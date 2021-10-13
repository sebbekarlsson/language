#include <utils.hpp>
#include <stdio.h>

char* copy_str(char* s) {
  int length = strlen(s);
  char* copied = (char*)calloc(length + 1, sizeof(char));
  memccpy(copied, s, sizeof(char), length);
  return copied;
}

char* get_file_contents(const char* filepath) {
  char* contents = 0;
  long length = 0;
  FILE* f = fopen(filepath, "rb");
  if (!f) {
    printf("Could not open file %s\n", filepath);
    return 0;
  }

  fseek(f, 0, SEEK_END);
  length = ftell(f);
  fseek(f, 0, SEEK_SET);
  contents = (char*)calloc(length + 1, sizeof(char));
  fread(contents, sizeof(char), length, f);
  fclose(f);
  return contents;
}
