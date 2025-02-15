#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW_LEN 40000
#define COL_LEN 40000
typedef struct {
  int x;
  int y;
} point;

void set_mark(char *current, char set) {
  if (*current == set) {
    return;
  }
  if (*current != 0) {
    // cross
    *current = 'X';
  }
}

void trace_path_x(int num, point *p_point, char grid[][ROW_LEN], char mark) {
  if (p_point->x + num >= ROW_LEN) {
    printf("pointx%d num%d\n", p_point->x, num);
    printf("Row OOB\n");
    exit(-1);
  }

  if (num < 0) {
    for (int i = -1; i >= num; i--) {
      set_mark(&grid[p_point->y][p_point->x + i], mark);
    }
  } else {
    for (int i = 1; i <= num; i++) {
      set_mark(&grid[p_point->y][p_point->x + i], mark);
    }
  }
  p_point->x += num;
}

void trace_path_y(int num, point *p_point, char grid[][ROW_LEN], char mark) {
  if (p_point->y + num >= COL_LEN) {
    printf("pointx%d num%d\n", p_point->y, num);

    printf("COL OOB\n");
    exit(-1);
  }
  if (num < 0) {
    for (int i = -1; i >= num; i--) {
      set_mark(&grid[p_point->y + i][p_point->x], mark);
    }
  } else {
    for (int i = 1; i <= num; i++) {
      set_mark(&grid[p_point->y + i][p_point->x], mark);
    }
  }

  p_point->y += num;
}

void update_grid(char grid[][ROW_LEN], char direction, int num, char mark) {
  static point prev_point = {COL_LEN / 2, ROW_LEN / 2};
  switch (direction) {
  case 'L': {
    trace_path_x(num * (-1), &prev_point, grid, mark);

  } break;

  case 'R': {
    trace_path_x(num, &prev_point, grid, mark);

  } break;

  case 'U': {
    trace_path_y(num, &prev_point, grid, mark);

  } break;

  case 'D': {
    trace_path_y(num * (-1), &prev_point, grid, mark);

  } break;

  default:
    break;
  }
}

int main() {
  FILE *file = fopen("input.txt", "r");
  char buffer[2000];
  static char grid[COL_LEN][ROW_LEN] = {0};
  while (fgets(buffer, sizeof(buffer), file)) {
    int mark = 0;
    char *token = strtok(buffer, ",");
    // write to grid
    while (token) {
      char dir;
      int num;
      sscanf(token, "%c%d", &dir, &num);
      update_grid(grid, dir, num, 'A' + mark);
      token = strtok(NULL, ",");
    }
    // update mark
    ++mark;
  }

  for (int i = ROW_LEN/2; i < ROW_LEN; i++) {
    for (int j = ROW_LEN/2; j < ROW_LEN; j++) {
      printf("%c", grid[i][j]);
    }
    printf("\n");
  }
}