#include <stdio.h>

int main() {

  FILE *file;
  char buffer[20];
  file = fopen("aoc1.txt", "r");
  int sum = 0;
  while (fgets(buffer, sizeof(buffer), file)) {
    int value = 0;
    sscanf(buffer, "%d", &value);
    int fuel = (value / 3) - 2;
    sum += fuel;
  }
  printf("sum %d",sum);
}