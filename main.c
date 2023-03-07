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

void *CheckColumns(void *param) {
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
        }*/


        pthread_t t ;
        pthread_create(&t, NULL, CheckBoard, NULL) ;
        pthread_join(t, NULL) ;

        return 0 ;

}
