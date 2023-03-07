#include <fcntl.h>
#include <pthread.h>
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

void *CheckBoard(void *param) {
}

void *CheckColumns(void *param) {
}

void *PrintBoard(void *param) {
}

int main(int argc, char **argv) {
        /*int opt = atoi([1]) ;
        switch(opt) {
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
        pthread_join(t, NULL) ;
        */

        struct sudoku_t *puzzle = ReadSudoku("input.txt") ;
        for (int j = 0 ; j < LENGTH ; ++j) {
                for (int i = 0 ; i < LENGTH ; ++i) {
                        printf("%d ", puzzle->board[i][j]) ;
                }
                printf("\n") ;
        }
}
