#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compute(int code[]) {
  int pc = 0;
  while (1) {
    switch (code[pc]) {
    case 1: {
      ++pc;
      int value1 = code[code[pc]];
      ++pc;
      int value2 = code[code[pc]];
      int result = value1 + value2;
      code[code[++pc]] = result;
      break;
    }

    case 2: {
      ++pc;
      int value1 = code[code[pc]];
      ++pc;
      int value2 = code[code[pc]];
      int result = value1 * value2;
      code[code[++pc]] = result;
      break;
    }

    case 99: {
      return code[0];
      break;
    }

    default:
      exit(-1);
    }
    // increment pc
    ++pc;
  }
}

int main() {
  FILE *input = fopen("aoc2.txt", "r");
  char buffer[1000] = {"\0"};

  if (!fgets(buffer, sizeof(buffer), input)) {
    exit(-1);
  }
  int codes[1000] = {0};
  char *token = strtok(buffer, ",");
  int i = 0;
  while (token) {
    sscanf(token, "%d", &codes[i]);
    ++i;
    token = strtok(NULL, ",");
  }
  int copy[1000];
  memcpy(copy, codes, sizeof(codes));

  // update position 1 and 2
  const int noun = 1;
  const int verb = 2;
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 100; j++) {
      codes[noun] = i;
      codes[verb] = j;
      if (compute(codes) == 19690720) {
        printf("noun*100 + verb = %d\n", (codes[noun] * 100) + codes[verb]);
        return 0;
      } else {
        memcpy(codes, copy, sizeof(codes));
      }
    }
  }
}