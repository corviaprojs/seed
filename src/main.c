#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <threads.h>
#include <time.h>


#include "symbols.h"
#include "settings.h"

typedef struct {
    int crsize; // the create size
    int sf;     // the full size
    int *map;   // the ptr of the map
} Map;


typedef struct {
    int food;
    int water;
    int *veins; 
} Org;


Map newMap(int size) {
    static Map newMap;

    newMap.crsize = size;
    newMap.sf = size*size;
    newMap.map = malloc(sizeof(int)*newMap.sf);

    for (int ifill = 0; ifill < newMap.sf; ifill++) {
        newMap.map[ifill] = 0;
    }

    return newMap;
}

Org org() {
    static Org org;
    org.water = 1; org.food = 1;
    org.veins = malloc(sizeof(int)*MAX_ORG_SIZE);
    for (int iVf = 0; iVf < MAX_ORG_SIZE; iVf++) org.veins[iVf] = 0;

    return org;
}


// free the 'map->map'
void initFree(Map *map) {
    if (map->map != NULL) {
        free(map->map);
        map->map = NULL; 
    }
}

// draw map
void drawMap(Map *map) {
    for (int i = 0; i < map->sf; i++) {

        // new line every 'map->crsize' like: 8
        if (i != 0 && i % map->crsize == 0) printf("\n");

        int mapNow = map->map[i];

        if (OLD_MAP_PRINT == 1)
            printf(" %d ", mapNow);
        else
            printf(" %c ", charachters[mapNow]);
    }
}

void genOrg(Map *map) {
    int orgPos = rand() % map->sf;
    map->map[orgPos] = 9;
}

// resources generating
void genRes(Map *map) {
    for (int i = 0; i < (rand() % map->crsize); i++)
    {
        int waterPos = rand() % map->sf;
        map->map[waterPos] = 1;
    }


    for (int i = 0; i < (rand() % map->crsize); i++)
    {
        int foodPos = rand() % map->sf;
        map->map[foodPos] = 2;
    }
}

// base init
void initBase(Map *map) {
    genRes(map); // the resources


    genOrg(map); // the org pos gen
}

// get the orgPos head
int getOrgPos(Map *map) {
    int iOrgFind = 0;

    for (iOrgFind = 0; iOrgFind < map->sf; iOrgFind++) {
        int nwM = map->map[iOrgFind];
        if (nwM == 9) {break;}
    }

    return iOrgFind;
}


int genRMove() {
    return rand() % 3;
}

void seedAI(Map *map, Org *org) {
    // while (1) {
    for (int i = 0; i < 100; i++) {
        printf("\nW: %d F:%d\n", org->water, org->food);

        int move = genRMove();

        // forward
        // TODO: make movement and learn how Neural Networks work.




        drawMap(map);
    }
}


int main() {
    srand(time(NULL));

    Map test1 = newMap(8);

    initBase(&test1);

    Org theorg = org();

    seedAI(&test1, &theorg);

    initFree(&test1);
    printf("\n"); return 0;
}