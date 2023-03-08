#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 27

int sudoku[9][9] = {
    {6, 2, 4, 5, 3, 9, 1, 8, 7},
    {5, 1, 9, 7, 2, 8, 6, 3, 4},
    {8, 3, 7, 6, 1, 4, 2, 9, 5},
    {1, 4, 3, 8, 6, 5, 7, 2, 9},
    {9, 5, 8, 2, 4, 7, 3, 6, 1},
    {7, 6, 2, 3, 9, 1, 4, 5, 8},
    {3, 7, 1, 9, 5, 6, 8, 4, 2},
    {4, 9, 6, 1, 8, 2, 5, 7, 3},
    {2, 8, 5, 4, 7, 3, 9, 1, 6}
};

typedef struct {
    int row;
    int col;
} Parameters;

int is_valid[3][9] = {0};

void* check_subgrid(void* arg) {
    Parameters* parameters = (Parameters*) arg;
    int row_start = parameters->row;
    int col_start = parameters->col;

    int used[9] = {0};
    int i, j;

    for (i = row_start; i < row_start + 3; i++) {
        for (j = col_start; j < col_start + 3; j++) {
            int val = sudoku[i][j];
            if (val < 1 || val > 9 || used[val - 1]) {
                pthread_exit(NULL);
            }
            used[val - 1] = 1;
        }
    }

    is_valid[0][row_start + col_start / 3] = 1;
    pthread_exit(NULL);
}

void* check_row(void* arg) {
    int row = *(int*) arg;
    int used[9] = {0};
    int i;
    for (i = 0; i < 9; i++) {
        int val = sudoku[row][i];
        if (val < 1 || val > 9 || used[val - 1]) {
            pthread_exit(NULL);
        }
        used[val - 1] = 1;
    }
    is_valid[1][row] = 1;
    pthread_exit(NULL);
}

void* check_col(void* arg) {
    int col = *(int*) arg;
    int used[9] = {0};
    int i;
    for (i = 0; i < 9; i++) {
        int val = sudoku[i][col];
        if (val < 1 || val > 9 || used[val - 1]) {
            pthread_exit(NULL);
        }
        used[val - 1] = 1;
    }
    is_valid[2][col] = 1;
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int i, j, k;
    k = 0;
    for (i = 0; i < 9; i += 3) {
		for (j = 0; j < 9; j += 3) {
			Parameters* parameters = malloc(sizeof(Parameters));
			parameters->row = i;
			parameters->col = j;
			pthread_create(&threads[k], NULL, check_subgrid, parameters);
			k++;
		}
	}
  int row_nums[9];
  int col_nums[9];
  for (i = 0; i < 9; i++) {
      row_nums[i] = i;
      col_nums[i] = i;
      pthread_create(&threads[k], NULL, check_row, &row_nums[i]);
      k++;
      pthread_create(&threads[k], NULL, check_col, &col_nums[i]);
      k++;
  }

  for (i = 0; i < NUM_THREADS; i++) {
      pthread_join(threads[i], NULL);
  }

  int valid = 1;
  for (i = 0; i < 3; i++) {
      for (j = 0; j < 9; j++) {
          if (!is_valid[i][j]) {
              valid = 0;
              break;
          }
      }
      if (!valid) {
          break;
      }
  }

  if (valid) {
      printf("Sudoku is valid.\n");
  } else {
      printf("Sudoku is not valid.\n");
  }

  return 0;
}
