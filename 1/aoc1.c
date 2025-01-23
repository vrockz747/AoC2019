#include <stdio.h>

int get_fuel(int value);

int main() {

  FILE *file;
  char buffer[20];
  file = fopen("aoc1.txt", "r");
  int sum = 0;
  while (fgets(buffer, sizeof(buffer), file)) {
    int value = 0;
    sscanf(buffer, "%d", &value);
    int fuel = get_fuel(value);
    sum += fuel;
  }
  printf("sum %d\n", sum);
}

int get_fuel(int value) {
  int result = 0;
  int temp = value;
  do {
    temp = (temp / 3) - 2;
    result = temp > 0 ? result + temp : result;
  } while (temp > 0);
  return result;
}
