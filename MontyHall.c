#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int arg, char *argv[]) {
    if (arg != 2) {
        printf("Usage: %s <number_of_simulations>\n", argv[0]);
        return 1;
    }

    int simul = atoi(argv[1]);
    int stay_win = 0;
    int switch_win = 0;
    srand(time(NULL));

    for (int i = 0; i < simul; i++) {
        int prize = rand() % 3;    
        int choice = rand() % 3;   

        int opened;
        do {
            opened = rand() % 3;
        } while (opened == prize || opened == choice);

        int switched = 3 - choice - opened;
        if (choice == prize)
            stay_win++;
        if (switched == prize)
            switch_win++;
    }

    printf("Simulations: %d\n", simul);
    printf("Stay win rate:   %.2f%%\n", 100.0 * stay_win / simul);
    printf("Switch win rate: %.2f%%\n", 100.0 * switch_win / simul);

    return 0;
}

