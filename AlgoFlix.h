
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>

#ifndef MAX   // false → skip
#define MAX 100
#endif

//Structures:

typedef struct Movie { int id; char title[50]; char genre[30]; int duration; int releaseYear; int views; } MOVIE; 

typedef struct Series { int id; char title[50]; char genre[30]; int seasons; int episodes; int ep_duration; int releaseYear; int views; } SERIES; 

typedef struct Node {
    union {
        MOVIE movie;
        SERIES series;
    } data;
    int type; //to indicate 1 = Movie, 2 = Series
    struct Node *next;
} NODE;

// BST Node
typedef struct BSTNode {
    NODE* data; // pointer to movie/series node
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNODE;

//Function declarations:

NODE* createNode(char title[]);
void addToWatchlist(char title[]);
void removeFromWatchlist(char title[]);
void searchInWatchlist(char title[]);
void displayWatchlist();

void enqueueCW(char title[]);
void dequeueCW();
void displayContinueWatching();
int isEmptyCW();

void insertPQ(char title[]);           
void deleteMaxPQ();                 
void peekPQ();                      
void heapify(int index);            
void displayPQ();                   

BSTNODE* createBSTNode(NODE *n);
BSTNODE* insertBST(BSTNODE *root, NODE *newNode);
BSTNODE* searchBST(BSTNODE *root, char title[]);
//void inorderBST(BSTNODE *root);
BSTNODE* buildBST();

//Display All movies and series
void displayMovies();
void displaySeries();

//Display by Letter
void displayContentByLetter(char ch);

// Memory cleanup functions
void freeWatchlist();
void freeContinueWatching();

void freeBST(BSTNODE *root);

