#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void compute(int code[]) {
  int pc = 0;
  while (1) {
    switch (code[pc]) {
    case 1: {
      ++pc;
      int value1 = code[code[pc]];
      ++pc;
      int value2 = code[code[pc]];
      int result = value1 + value2;
      ++pc;
      code[code[pc]] = result;
      break;
    }

    case 2: {
      ++pc;
      int value1 = code[code[pc]];
      ++pc;
      int value2 = code[code[pc]];
      int result = value1 * value2;
      ++pc;
      code[code[pc]] = result;
      break;
    }

    case 99: {
      return;
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
  // update position 1 and 12
  codes[1] = 12;
  codes[2] = 2;
  compute(codes);
  printf("Value: %d\n", codes[0]);
}