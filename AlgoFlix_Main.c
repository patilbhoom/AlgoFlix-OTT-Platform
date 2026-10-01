
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<ctype.h>
#include"AlgoFlix.h"   

int main() 
{
	printf("\nMAX defined on command line is %d\n",MAX);
    char choice, subchoice, title[100], ch; //for display by letter
    BSTNODE *root = NULL;

    root = buildBST(); // build BST once at start to perform search


    do {
		printf("\n\n==============================\n");
		printf("           ALGOFLIX         \n");
		printf("==============================\n");
        printf("\nMAIN MENU\n");
        printf("W - Watchlist\n");
        printf("C - Continue Watching\n");
        printf("L - Latest Releases\n");
        printf("S - Search\n");
        printf("D - Display All Movies\n");
        printf("P - Display All Series\n");
		printf("F - Display All by first letter\n");
        printf("Q - Quit\n");

        printf("\nEnter your choice: ");
        scanf(" %c", &choice);
        choice = toupper(choice);

        switch (choice) {

        //----------------WATCHLIST---------------------
        case 'W':
            do {
				printf("\n\n==============================\n");
				printf("           ALGOFLIX         \n");
				printf("==============================\n");
                printf("\nWATCHLIST MENU\n");
                printf("A - Add to Watchlist\n");
                printf("R - Remove from Watchlist\n");
                printf("D - Display Watchlist\n");
                printf("S - Search in Watchlist\n");
                //printf("C - Count Watchlist\n");
                printf("B - Back to Main Menu\n");
                printf("\nEnter choice: ");
                scanf(" %c", &subchoice);
                subchoice = toupper(subchoice);

                switch (subchoice) {
                case 'A':
					displayMovies();
					displaySeries();

                    printf("\nEnter title to add: ");
                    scanf(" %[^\n]", title);
                    addToWatchlist(title);
                    break;

                case 'R':
                    printf("\nEnter title to remove: ");
                    scanf(" %[^\n]", title);
                    removeFromWatchlist(title);
                    break;

                case 'D':
                    displayWatchlist();
                    break;

                case 'S':
                    printf("\nEnter title to search: ");
                    scanf(" %[^\n]", title);
                    searchInWatchlist(title);
                    break;

                case 'B':
                    break;

                default:
                    printf("\nInvalid option.\n");
					break;
                }

            } while (subchoice != 'B');
            break;

        // ---------------- CONTINUE WATCHING ----------------
        case 'C':
            do {
				printf("\n\n==============================\n");
				printf("           ALGOFLIX         \n");
				printf("==============================\n");
                printf("\nCONTINUE WATCHING MENU\n");
                printf("A - Add to CW\n");
                printf("R - Remove from CW \n");
                printf("D - Display CW\n");
                //printf("C - Count Continue Watching\n");
                printf("B - Back to Main Menu\n");
                printf("\nEnter choice: ");
                scanf(" %c", &subchoice);
                subchoice = toupper(subchoice);

                switch (subchoice) {
                case 'A':
		
					displayMovies();
					displaySeries();

                    printf("\nEnter title to add: ");
                    scanf(" %[^\n]", title);
                    enqueueCW(title);
                    break;

                case 'R':
                    dequeueCW();
                    break;

                case 'D':
                    displayContinueWatching();
                    break;

                case 'B':
                    break;

                default:
                    printf("\nInvalid option.\n");
					break;
                }

            } while (subchoice != 'B');
            break;

        // ---------------- LATEST RELEASES ----------------
        case 'L':
            do {
				printf("\n\n==============================\n");
				printf("           ALGOFLIX         \n");
				printf("==============================\n");
                printf("\nLATEST RELEASES\n");
                printf("A - Add to Latest Releases\n");
                printf("D - Delete from Latest Release\n");
                printf("P - Peek Latest Release\n");
                printf("S - Display Latest Releases\n");
                printf("B - Back to Main Menu\n");
                printf("\nEnter choice: ");
                scanf(" %c", &subchoice);
                subchoice = toupper(subchoice);

                switch (subchoice) {
                case 'A': {
					
					displayMovies();
					displaySeries();

                    printf("\nEnter title to add: ");
                    scanf(" %[^\n]", title);
                    insertPQ(title);
					break;
                }

                case 'D':
                    deleteMaxPQ();
                    break;

                case 'P': {
                    peekPQ();
					break;
                }

                case 'S':
                    displayPQ();
                    break;

                case 'B':
                    break;

                default:
                    printf("\nInvalid option.\n");
					break;
                }

            } while (subchoice != 'B');
            break;

        // ---------------- SEARCH ----------------
        case 'S': {		
            printf("\nEnter title to search in database: ");
            scanf(" %[^\n]", title);
            BSTNODE *res = searchBST(root, title);
            if (res == NULL)
                printf("\n'%s' not found in ALGOFLIX database.\n", title);
            else {
                if (res->data->type == 1) {
                    MOVIE m = res->data->data.movie;
                    printf("\n[Movie] %s (%d) | %s | Views: %d\n", m.title, m.releaseYear, m.genre, m.views);
                } else {
                    SERIES s = res->data->data.series;
                    printf("\n[Series] %s (%d) | %s | Views: %d\n", s.title, s.releaseYear, s.genre, s.views);
                }
            }
            break;
        }

        // ---------------- DISPLAY MOVIES ----------------
        case 'D':
			printf("\n\n==============================\n");
			printf("           ALGOFLIX         \n");
			printf("==============================\n");
            displayMovies();
            break;

        // ---------------- DISPLAY SERIES ----------------
        case 'P':
			printf("\n\n==============================\n");
			printf("           ALGOFLIX         \n");
			printf("==============================\n");
            displaySeries();
            break;

		//--------------------DISPLAY BY LETTER  -----------------
		case 'F':
			printf("\n\n==============================\n");
			printf("           ALGOFLIX         \n");
			printf("==============================\n");
			
			printf("\nEnter first letter: ");
			scanf(" %c", &ch);
			displayContentByLetter(ch);
			break;
	
			
        // ---------------- QUIT ----------------
        case 'Q':
            printf("\nExiting ALGOFLIX... Goodbye!\n");
			freeWatchlist();
			freeContinueWatching();
			freeBST(root);
            break;

        default:
            printf("Invalid Main Menu option.\n");
			break;
        }

    } while (choice != 'Q');

    return 0;
}





