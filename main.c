#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NbTests 100000000
#define NbDoors 3
#define Car 1
#define Goat 2

void initializeDoors(unsigned short doors[NbDoors]) {
    for (int i = 0; i < NbDoors; i++) {
        doors[i] = Goat;
    }
    int randomDoor = rand() % NbDoors;
    doors[randomDoor] = Car;
}

int chooseDoors(unsigned short doors[NbDoors]) {
    return rand() % NbDoors;
}

int openDoor(unsigned short doors[NbDoors], int forbiddenDoor) {
    if (doors[forbiddenDoor] == Car) {
        int randomDoor = rand() % (NbDoors - 1);
        return (forbiddenDoor + 1 + randomDoor) % NbDoors;
    } else {
        for (int i=0; i < NbDoors; i++) {
            if ((i != forbiddenDoor) && (doors[i] == Goat)) {
                return i;
            }
        }
    }
    return -1;
}

void showResult(int nbGoals) {
    printf("Nombre de tentatives gagnantes : %f\n", ((float)nbGoals / NbTests * 100));
}

int main() {
    unsigned short doors[NbDoors];
    int nbGoals = 0;
    srand( time( NULL ) ); // On mélange le random

    // Joueur qui change pas d'avis
    for (int i = 0; i < NbTests; i++) {
        initializeDoors(doors);
        int chosenDoor = chooseDoors(doors);
        int openedDoor = openDoor(doors, chosenDoor);
        if (doors[chosenDoor] == Car) {
            nbGoals++;
        }
    }
    showResult(nbGoals);

    // Joueur qui change d'avis
    nbGoals = 0;
    for (int i = 0; i < NbTests; i++) {
        initializeDoors(doors);
        int chosenDoor = chooseDoors(doors);
        int openedDoor = openDoor(doors, chosenDoor);
        chosenDoor = NbDoors - chosenDoor - openedDoor;
        if (doors[chosenDoor] == Car) {
            nbGoals++;
        }
    }
    showResult(nbGoals);
    return 0;
}
