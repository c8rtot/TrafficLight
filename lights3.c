/* TrafficLight Simulator - all text, all the time! */
/* version 3: add functions */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define true 1
#define false 0

/* global variables (oh my!) */
int trafficWest = true; /* traffic from west has green light */
int yellowBlinkTime = 50; /* time for yellow light to stay on */
int flowTime = 1000; /* test values - will be lengthened for production code */
int changeDelay = 20;
int pedFlowTime = 3000;
char east = 'E';
char west = 'W';
char ped = 'P';

/* more globals - replace buttons from Arduino code */

int westButton = true;
int eastButton = false;
int pedButton = false;

/* random function to determine which button was pressed -
   original name was reference to 2 options (east & west)
   for traffic, but pedestrians add a 3rd option. So code
   changed but function name still the same */
int flipCoin() {
    return rand() % 3;
}

void delay (int dTime) {
    for(int a=0; a<10; a++) {
       printf(".\t");
       Sleep(dTime);
    }
    printf("\n");
}

void stopTraffic (char direction){
     if(direction == 'E') {
        printf("EAST - turning off green\n");
        printf("EAST - turning on yellow\n");
        delay(changeDelay);
        printf("EAST red light is on\n");
        delay(changeDelay);
     }

     if (direction == 'W'){
        printf("WEST - turning off green\n");
        printf("WEST - turning on yellow\n");
        delay(changeDelay);
        printf("WEST red light is on\n");
        delay(changeDelay);
    }
}

void startTraffic(char direction) {
    if(direction == 'W') {
        printf("Yellow light WEST blinking\n");
        delay(yellowBlinkTime);
        printf("\nWEST green light is on\n");
    }
    if(direction == 'E') {
       printf("Yellow light EAST blinking\n");
       delay(yellowBlinkTime);
       printf("\nEAST green light is on\n");
    }

}

void pedestrian() {
        printf("PEDESTRIANS ON BRIDGE!\n");
        stopTraffic('W');
        stopTraffic('E');
        printf("Pedestrian walk light is ON\n");
        delay(pedFlowTime);
        printf("Pedestrian walk light is OFF\n");
        pedButton=false;
}

void waitForIt() {
    printf("Waiting for traffic to clear\n");
    delay(flowTime);
}

int main () {
    srand(time(NULL));
    int coinflip;    /* random number to determine traffic direction */

    printf("Welcome to the Traffic Simulator\n");
    do {
        coinflip = flipCoin();
        if (coinflip == 0) {  // traffic from west
            westButton = true;
            eastButton = false;
            pedButton = false;
        } else if (coinflip == 1) { // traffic from east
            eastButton = true;
            westButton = false;
            pedButton = false;
        } else { // pedestrians
            westButton = false;
            eastButton = false;
            pedButton = true;
        }
        if(westButton) {
            printf("West button was pushed\n");
            waitForIt();
            if(!trafficWest) {
                trafficWest = true;
                stopTraffic('E');
            } /* end inner if */
            startTraffic('W');
        } /* end outer if */

        if(eastButton) {
            printf("East button was pushed\n");
            waitForIt();
            if(trafficWest) {
                trafficWest = false;
                stopTraffic('W');
            } /* end inner if */
            startTraffic('E');
        }
        if(pedButton) {
            waitForIt();
            pedestrian();
        }
        system("pause");
    } while(1);
    printf("Goodbye\n");
    /* end main */
    return 0;
}
