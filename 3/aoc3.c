#include "../uthash.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  int x;
  int y;
} point;
typedef struct {
  point cord;
  char value;
  int steps;
  UT_hash_handle hh;
} map;

// understand the TIME COMP
map *mmap = NULL;
int sum = 0;
int sum_steps = INT_MAX;

void update_map(point current, char marker, int *steps) {
  map *out = NULL;
  HASH_FIND(hh, mmap, &current, sizeof(current), out);
  if (out) {
    // check with marker
    if (out->value != marker) {
      // if marker different make it X and store x + y sum
      out->value = 'X';
      int temp = abs(current.x) + abs(current.y);
      if (temp < sum || sum == 0) {
        sum = temp;
      }
      int local = (out->steps + (++(*steps)));
      printf("%d\n",local);

      if(sum_steps > local){
        sum_steps = local;
      }
    }else{
      (*steps)++;
    }
  } else {
    // mark the cords
    out = (map *)malloc(sizeof(map));
    out->steps = ++(*steps);
    out->cord = current;
    out->value = marker;
    HASH_ADD(hh, mmap, cord, sizeof(point), out);
  }
}

void trace_path(int x, int y, char marker, int offset, point *prev_point, int *steps) {
  for (int i = 0; i < offset; i++) {
    prev_point->x += x;
    prev_point->y += y;
    update_map(*prev_point, marker, steps);
  }
}

void update_grid(int offset, char dir, char marker, point *prev_point, int *steps) {
  // get dir and add cords to mmap
  switch (dir) {
  case 'L':
    trace_path(-1, 0, marker, offset, prev_point, steps);
    break;
  case 'R':
    trace_path(1, 0, marker, offset, prev_point, steps);
    break;
  case 'U':
    trace_path(0, 1, marker, offset, prev_point, steps);
    break;
  case 'D':
    trace_path(0, -1, marker, offset, prev_point, steps);
    break;
  }
}

int main() {
  FILE *file = fopen("input.txt", "r");
  char buffer[2000];

  int marker = 0;
  int steps = 0;
  while (fgets(buffer, sizeof(buffer), file)) {
    char *token = strtok(buffer, ",");
    point prev_point = {0, 0};
    while (token) {
      int offset;
      char dir;
      sscanf(token, "%c%d", &dir, &offset);
      update_grid(offset, dir, 'A' + marker, &prev_point, &steps);
      token = strtok(NULL, ",");
    }
    steps = 0;
    marker++;
  }
  printf("SUM: %d\n", sum);
    printf("STEPS: %d\n", sum_steps);

}