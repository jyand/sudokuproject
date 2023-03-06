#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <wait.h>

void *CheckBoard(void *param) {
}

void *CheckColumns(void *param) {
}

void *PrintBoard(void *param) {
}

int main(int argc, char **argv) {
        int opt = atoi([1]) ;
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
        //TODO: open file
        pthread_t t ;
        pthread_create(&t, NULL, CheckBoard, NULL) ;
        pthread_join(t, NULL) ;
}
