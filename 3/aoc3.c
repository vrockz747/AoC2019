#include "../uthash.h"
#include <stdio.h>
#include <string.h>

typedef struct {
  int x;
  int y;
} point;
typedef struct {
  point cord;
  char value;
  UT_hash_handle hh;
} map;

map *mmap = NULL;
int sum = 0;

void update_map(point current, char marker) {
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
    }
  } else {
    // mark the cords
    out = (map *)malloc(sizeof(map));
    out->cord = current;
    out->value = marker;
    HASH_ADD(hh, mmap, cord, sizeof(point), out);
  }
}

void trace_path(int x, int y, char marker, int offset, point *prev_point) {
  for (int i = 0; i < offset; i++) {
    prev_point->x += x;
    prev_point->y += y;
    update_map(*prev_point, marker);
  }
}

void update_grid(int offset, char dir, char marker, point *prev_point) {
  // get dir and add cords to mmap
  switch (dir) {
  case 'L':
    trace_path(-1, 0, marker, offset, prev_point);
    break;
  case 'R':
    trace_path(1, 0, marker, offset, prev_point);
    break;
  case 'U':
    trace_path(0, 1, marker, offset, prev_point);
    break;
  case 'D':
    trace_path(0, -1, marker, offset, prev_point);
    break;
  }
}

int main() {
  FILE *file = fopen("input.txt", "r");
  char buffer[2000];

  int marker = 0;
  while (fgets(buffer, sizeof(buffer), file)) {
    char *token = strtok(buffer, ",");
    point prev_point = {0, 0};
    while (token) {
      int offset;
      char dir;
      sscanf(token, "%c%d", &dir, &offset);
      update_grid(offset, dir, 'A' + marker, &prev_point);
      token = strtok(NULL, ",");
    }
    marker++;
  }
  printf("SUM: %d\n", sum);
}