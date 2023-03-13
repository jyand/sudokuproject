#include <fcntl.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>

#define LENGTH 9

struct sudoku_t {
        int board[LENGTH][LENGTH] ;
} ;

struct Parameters {
        int row ;
        int col ;
} ;

int is_valid[3][9] = {0} ;

int g_sudoku[9][9] ;

struct sudoku_t *ReadSudoku(const char *fname) {
        FILE *f = fopen(fname, "r") ;
        struct sudoku_t *s = (struct sudoku_t*)malloc(sizeof(struct sudoku_t)) ;
        for (int j = 0 ; j < LENGTH ; ++j) {
                for (int i = 0 ; i < LENGTH ; ++i) {
                        int temp = fscanf(f, "%1d", &s->board[i][j]) ;
                }
        }
        return s ;
}

void PrintBoard(const struct sudoku_t *s) {
        for (int j = 0 ; j < LENGTH ; ++j) {
                for (int i = 0 ; i < LENGTH ; ++i) {
                        printf("%d ", s->board[i][j]) ;
                }
                printf("\n") ;
        }
}

/* If there are no duplicates in a set of 9 cells, that set MUST contain digits 1 through 9  */
bool CheckDuplicates(int *vector) {
        bool valid = true ;
        for (int j = 0 ; j < LENGTH ; ++j) {
                for (int k = j + 1 ; k < LENGTH ; ++k) {
                        if (vector[j] == vector[k]) {
                                valid = false ;
                        }
                }
        }
        return valid ;
}

void *CheckBoard(void *param) {
        struct sudoku_t *puzzle = ReadSudoku("input.txt") ;
        for (int i = 0 ; i < LENGTH ; ++i) {
                if (CheckDuplicates(puzzle->board[i]) == false) {
                        printf("invalid\n") ;
                        break ;
                }
        }

}

void *CheckSubgrid(void *param) {
        struct Parameters *p = (struct parameters*)param ;
        int row_start = p->row ;
        int col_start = p->col ;
        int used[9] = {0} ;
        for (int i = row_start ; i < row_start + 3 ; ++i) {
                for (int j = col_start ; j < col_start ; ++j) {
                        int val = g_sudoku[i][j] ;
                        if (val < 1 || val > 9 || used[val - 1]) {
                                pthread_exit(NULL) ;
                        }
                        used[val - 1] = 1 ;
                }
        }
        is_valid[0][row_start + col_start/3] = 1 ;
        pthread_exit(NULL) ;
}

void *CheckColumn(void *param) {
        int col = *(int*)param ;
        int used[9] = {0} ;
        for (int i = 0 ; i < 9 ; ++i) {
                int val = g_sudoku[i][col] ;
                if (val < 1 || val > 9 || used[val - 1]) {
                        pthread_exit(NULL) ;
                }
                used[val - 1] = 1 ;
        }
        is_valid[2][col] = 1 ;
        pthread_exit(NULL) ;
}

void *CheckRow(void *param) {
        int row = *(int*)param ;
        int used[9] = {0} ;
        for (int i = 0 ; i < 9 ; ++i) {
                int val = g_sudoku[row][i] ;
                if (val < 1 || val > 9 || used[val - 1]) {
                        pthread_exit(NULL) ;
                }
                used[val - 1] = 1 ;
        }
        is_valid[1][row] = 1 ;
        pthread_exit(NULL) ;
}

char *IsValid(int n_threads) {
        pthread_t threads[n_threads] ;
        int k = 0 ;
        for (int i = 0 ; i < 9 ; i +=3) {
                for (int j = 0 ; j < 9 ; j += 3) {
                        struct Parameters *p =  (struct Parameters*)malloc(sizeof(struct Parameters)) ;
                        p->row = i ;
                        p->col = j ;
                        pthread_create(&threads[k], NULL, CheckSubgrid, p) ;
                        ++k ;
                }
        }
        int row_nums[9] ;
        int col_nums[9] ;
        for (int i = 0 ; i < 9 ; ++i) {
                row_nums[i] = i ;
                col_nums[i] = i ;
                pthread_create(&threads[k], NULL, CheckRow, &row_nums[i]) ;
                pthread_create(&threads[k], NULL, CheckColumn, &col_nums[i]) ;
                ++k ;
        }
        for (int i = 0 ; i < n_threads ; ++i) {
                pthread_join(threads[i], NULL) ;
        }
        int valid = 1 ;
        for (int i = 0 ; i < 3 ; ++i) {
                for (int j = 0 ; j < 9 ; ++j) {
                        if (!is_valid[i][j]) {
                                valid = 0 ;
                                break ;
                        }
                }
                if (!valid) {
                        break ;
                }
        }
        if (valid) {
                return "Sudoku is valid.\n" ;
        } else {
                return "Sudoku is invalid.\n" ;
        }
}

int main(int argc, char **argv) {
        int opt = atoi(argv[1]) ;
        /*switch(opt) {
                case 2:
                        int num_threads = 27 ;
                break ;
                case 3:
                        int num_child_proc = 3 ;
                break ;
                default:
                        int num_threads = 1 ;
                break ;
        }


        pthread_t t ;
        pthread_create(&t, NULL, CheckBoard, NULL) ;
        pthread_join(t, NULL) ; */

        FILE *f = fopen("input.txt", "r") ;
        for (int j = 0 ; j < LENGTH ; ++j) {
                for (int i = 0 ; i < LENGTH ; ++i) {
                        int temp = fscanf(f, "%1d", &g_sudoku[i][j]) ;
                }
        }
        printf(IsValid(27)) ;

        return 0 ;

}
