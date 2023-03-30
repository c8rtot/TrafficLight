/* TrafficLight Simulator - all text, all the time! */

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
int changeDelay = 200;

/* more globals - replace buttons from Arduino code */

int westButton = true;
int eastButton = false;

int flipCoin() {
    return rand() % 2;
}

void delay (int dTime) {
    for(int a=0; a<10; a++) {
       printf(".\t");
       Sleep(dTime);
    }
    printf("\n");
}

int main () {
    srand(time(NULL));
    int coinflip;
    /* random number to determine traffic direction */
    printf("Welcome to the Traffic Simulator\n");

    do {
        coinflip = flipCoin();
        if (coinflip) {
            westButton = true;
            eastButton = false;
        } else {
            eastButton = true;
            westButton = false;
        }
        if(westButton) {
            printf("West button was pushed\n");
            if(!trafficWest) {
                printf("Waiting for traffic to clear\n");
                trafficWest = true;
                delay(flowTime);
                printf("East - turning off green\n");
                printf("East - turning on yellow\n");
                delay(changeDelay);
                printf("East red light is on\n");
                delay(changeDelay);
                printf("Yellow light west blinking\n");
                delay(yellowBlinkTime);
                printf("\nWest green light is on\n");
            } /* end inner if */
        } /* end outer if */

        if(eastButton) {
            printf("East button was pushed\n");
            if(trafficWest) {
                printf("Waiting for traffic to clear\n");
                trafficWest = false;
                delay(flowTime);
                printf("West - turning off green\n");
                printf("West - turning on yellow\n");
                delay(changeDelay);
                printf("West red light is on\n");
                delay(changeDelay);
                printf("Yellow light east blinking\n");
                delay(yellowBlinkTime);
                printf("\nEast green light is on\n");
            } /* end inner if */
        }
        system("pause");
    } while(1);
    printf("Goodbye\n");
    /* end main */
    return 0;
}
