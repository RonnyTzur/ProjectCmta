//
// Project menu
//

#include <stdio.h>
#include <stdlib.h>
#include "../Game.h"
#include "../Position.h"
#include "../greedyCheapPath/GreedyCheapPath.h"
#include "../streamIo/StreamIo.h"
#include "Menu.h"

void showMenu() {

    Position* source = createEmptyPos();
    Position* destination = createEmptyPos();

    Board c;
    Board board =
            {
                    {'1', '5', '6', '7'},
                    {'4', '4', '8', '0'},
                    {'4', '4', '8', '0'},
                    {'2', '3', '4', '5'}
            };

	const char *menuOptions[] = { 
								  "Load a board from file", 
								  "Enter a source position and destination", 
								  "Find a greedy cheap path between the source and destination",
								  "Create a tree of all possible paths starting from source position",
								  "Find all sorted path prices starting from source",
								  "Find the cheapest path between source and destination",
								  "Exit"
								};
	unsigned int input;
	char file_name[SIZE];


    // print menu with enumeration
	for (int i = 0; i < 7; ++i) {
		printf("%d.\t%s\n", i + 1, menuOptions[i]);
	}

    // menu
    printf("\nEnter new command: \n");
    scanf("%d", &input);

    while(input != 7){

        switch (input)
        {
            case 1: // load board from binary file
                printf("Enter File Path:\n");
                scanf("%s",&file_name);
                readFile(file_name,&board,"rb");
                break;

            case 2: // scan source and dest positions
                scanPositions(source, destination);
                break;

            case 3: 
            case 4: 
            case 5:
            case 6: // Check if there is excisting positions and then end then execute the correct gateways
                if (*source[0] == NULL || *destination[0] == NULL) {
                    printf("You forgot to enter positions\n");
                    scanPositions(source, destination);
                }

                switch (input)
                {
                    case 3:  // execute greedyCheapPath1 function
						greedyCheapPath(board, source, destination);
						break;
                    case 4:  // execute findAllPossiblePaths
						break;
                    case 5:  // execute findAllPathSortedPrices
                        break;
                    case 6:
                        break;
                }

				break;
            default:
                printf("\n%d is unknown input please try again..\n\n", input);
                showMenu(source, destination, board);
				return;
        }
        printf("Enter new command: \n");
        scanf("%d", &input);
    }

    printf("Bye Bye ...");
}

void scanXY(char *x, char *y) {
    while (TRUE) {
        printf("Enter X position, number:\n");
        scanf(" %c", x);
        printf("Enter Y position, Capital letter:\n");
        scanf(" %c", y);

		toUpperChar(y);

		if ( isNumberInBoard(*x) && isCapLetterInBoard(*y) ) {
        break;
        } // coordinates are valid !
        else{
            printf("\nWrong Positions ! \n");
        }
    }

}

void scanPositions(Position *source, Position *destination) {

	printf("Enter source position: \n");
	scanXY(&(*source)[0], &(*source)[1]);
	printf("Enter target position: \n");
	scanXY(&(*destination)[0], &(*destination)[1]);
}
