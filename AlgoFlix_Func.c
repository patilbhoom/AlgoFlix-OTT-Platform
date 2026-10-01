
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include"AlgoFlix.h"
#include<ctype.h>

//Arrays:

static const MOVIE movie_arr[] = {
    {101, "Dune: Part Two", "Sci-Fi", 155, 2024, 950},
    {102, "Oppenheimer", "Drama", 180, 2023, 880},
    {103, "Inside Out 2", "Animation", 110, 2024, 720},
    {104, "The Batman", "Action", 176, 2022, 845},
    {105, "Barbie", "Comedy", 114, 2023, 810},
    {106, "John Wick 4", "Action", 169, 2023, 870},
    {107, "Mission Impossible: Dead Reckoning", "Action", 164, 2023, 790},
    {108, "Top Gun: Maverick", "Action", 131, 2022, 940},
    {109, "The Marvels", "Superhero", 105, 2023, 580},
    {110, "Spider-Man: Across the Spider-Verse", "Animation", 140, 2023, 960},
    {111, "Extraction 2", "Action", 122, 2023, 820},
    {112, "Red Notice", "Comedy", 118, 2021, 730},
    {113, "Glass Onion", "Mystery", 139, 2022, 710},
    {114, "The Gray Man", "Action", 128, 2022, 680},
    {115, "Knives Out", "Mystery", 130, 2019, 750},
    {116, "Tenet", "Sci-Fi", 150, 2020, 770},
    {117, "Joker", "Drama", 122, 2019, 910},
    {118, "Interstellar", "Sci-Fi", 169, 2014, 980},
    {119, "The Martian", "Sci-Fi", 144, 2015, 860},
    {120, "Arrival", "Sci-Fi", 116, 2016, 820}
};
static int movieCount = sizeof(movie_arr) / sizeof(movie_arr[0]);

static const SERIES series_arr[] = {
    {201, "Stranger Things", "Sci-Fi", 4, 34, 50, 2016, 960},
    {202, "Money Heist", "Thriller", 5, 41, 45, 2017, 890},
    {203, "The Boys", "Superhero", 4, 32, 55, 2019, 880},
    {204, "Loki", "Superhero", 2, 12, 52, 2021, 840},
    {205, "The Witcher", "Fantasy", 3, 24, 58, 2019, 850},
    {206, "Breaking Bad", "Crime", 5, 62, 47, 2008, 970},
    {207, "Better Call Saul", "Crime", 6, 63, 46, 2015, 910},
    {208, "The Crown", "Drama", 6, 60, 55, 2016, 730},
    {209, "Peaky Blinders", "Drama", 6, 36, 58, 2013, 900},
    {210, "The Office", "Comedy", 9, 201, 22, 2005, 850},
    {211, "Friends", "Comedy", 10, 236, 23, 1994, 980},
    {212, "The Family Man", "Action", 3, 24, 45, 2019, 750},
    {213, "Mirzapur", "Crime", 3, 28, 48, 2018, 870},
    {214, "Paatal Lok", "Thriller", 1, 9, 50, 2020, 730},
    {215, "Made in Heaven", "Drama", 2, 16, 50, 2019, 710},
    {216, "Squid Game", "Thriller", 1, 9, 55, 2021, 990},
    {217, "Dark", "Sci-Fi", 3, 26, 50, 2017, 940},
    {218, "Wednesday", "Comedy", 1, 8, 49, 2022, 880},
    {219, "House of the Dragon", "Fantasy", 2, 18, 58, 2022, 860},
    {220, "The Mandalorian", "Action", 3, 24, 40, 2019, 820}
};
static int seriesCount = sizeof(series_arr) / sizeof(series_arr[0]);

//Function definitions:

//WATCHLIST

static NODE *watchHead = NULL; // static Head pointer for Watchlist

//Create Node (searches in movie_arr or series_arr)
NODE* createNode(char title[]) {
    NODE *newNode = (NODE*)malloc(sizeof(NODE));
	if(!newNode){
		printf("Memory not allocated\n");
		return NULL;
	}
    newNode->next = NULL;

    // Search in movies
    for (int i = 0; i < movieCount; i++) {
        
        if (strcasecmp(movie_arr[i].title, title) == 0) {
            newNode->data.movie = movie_arr[i];
            newNode->type = 1;
            return newNode;
        }
    }

    // Search in series
    for (int i = 0; i < seriesCount; i++) {
  
        if (strcasecmp(series_arr[i].title, title) == 0) {
            newNode->data.series = series_arr[i];
            newNode->type = 2;
            return newNode;
        }
    }

    free(newNode);
    return NULL; // Not found
}

//Add to Watchlist
void addToWatchlist(char title[]) {
	// check if already in watchlist
	NODE *check = watchHead;
	while (check != NULL) {
		if ((check->type == 1 && strcasecmp(check->data.movie.title, title) == 0) ||
			(check->type == 2 && strcasecmp(check->data.series.title, title) == 0)) {
			printf("'%s' is already in Watchlist.\n", title);
			return;
		}
		check = check->next;
	}

	
    NODE *newNode = createNode(title);
    if (newNode == NULL) {
        printf("'%s' not found in dataset.\n", title);
        return;
    }

    if (watchHead == NULL) {
        watchHead = newNode;
        printf("'%s' added to Watchlist.\n", title);
        return;
    }

    NODE *temp = watchHead;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
    printf("'%s' added to Watchlist.\n", title);
}

//Remove from Watchlist
void removeFromWatchlist(char title[]) {
    if (watchHead == NULL) {
        printf("Watchlist is empty.\n");
        return;
    }

	
    NODE *temp = watchHead, *prev = NULL;

    // Check first node
    if ((temp->type == 1 && strcasecmp(temp->data.movie.title, title) == 0) ||
        (temp->type == 2 && strcasecmp(temp->data.series.title, title) == 0)) {

		//Ask confirmation before unlinking
		char ch;
		printf("Are you sure you want to delete '%s' from Watchlist? (y/n): ", title);
		scanf(" %c", &ch);
		
		if (ch != 'y' && ch != 'Y') {
			printf("Deletion cancelled.\n");
			return;
		}
		
        watchHead = temp->next;
        free(temp);
        printf("'%s' removed from Watchlist.\n", title);
        return;
    }

    // Traverse
    while (temp != NULL) {
        if ((temp->type == 1 && strcasecmp(temp->data.movie.title, title) == 0) ||
            (temp->type == 2 && strcasecmp(temp->data.series.title, title) == 0)) {

			//Ask confirmation before unlinking
			char ch;
			printf("Are you sure you want to delete '%s' from Watchlist? (y/n): ", title);
			scanf(" %c", &ch);
			
			if (ch != 'y' && ch != 'Y') {
				printf("Deletion cancelled.\n");
				return;
			}

			prev->next = temp->next;
            free(temp);
            printf("'%s' removed from Watchlist.\n", title);
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("'%s' not found in Watchlist.\n", title);
}

//Search in Watchlist
void searchInWatchlist(char title[]) {
    NODE *temp = watchHead;
    int pos = 1;

    while (temp != NULL) {
        if ((temp->type == 1 && strcasecmp(temp->data.movie.title, title) == 0) ||
            (temp->type == 2 && strcasecmp(temp->data.series.title, title) == 0)) {
            printf("'%s' found at position %d in Watchlist.\n", title, pos);
            return;
        }
        temp = temp->next;
        pos++;
    }

    printf("'%s' not found in Watchlist.\n", title);
}

//Display Watchlist
void displayWatchlist() {
    if (watchHead == NULL) {
        printf("Watchlist is empty.\n");
        return;
    }

    NODE *temp = watchHead;
    printf("\n----- WATCHLIST -----\n\n");
    while (temp != NULL) {
        if (temp->type == 1) {
            printf("[MOVIE] %s (%d) |  Genre: %s | Duration: %d min | Views: %d\n",
                   temp->data.movie.title, temp->data.movie.releaseYear,
                   temp->data.movie.genre, temp->data.movie.duration,
                   temp->data.movie.views);
        } else if (temp->type == 2) {
            printf("[SERIES] %s (%d) |  Genre: %s | Seasons: %d | Episodes: %d | Views: %d\n",
                   temp->data.series.title, temp->data.series.releaseYear,
                   temp->data.series.genre, temp->data.series.seasons,
                   temp->data.series.episodes, temp->data.series.views);
        }
        temp = temp->next;
    }
    printf("\n---------------------\n");
}


//CONTINUE WATCHING


static NODE *frontCW = NULL; //static ptrs
static NODE *rearCW = NULL;

//Enqueue (Add to Continue Watching Queue)
void enqueueCW(char title[]) {
	// check if already in Continue Watching
	NODE *check = frontCW;
	while (check != NULL) {
		if ((check->type == 1 && strcasecmp(check->data.movie.title, title) == 0) ||
			(check->type == 2 && strcasecmp(check->data.series.title, title) == 0)) {
			printf("'%s' is already in Continue Watching.\n", title);
			return;
		}
		check = check->next;
	}

	
    NODE *newNode = createNode(title);  // use existing createNode
    if (newNode == NULL) {
        printf("'%s' not found in dataset.\n", title);
        return;
    }

    if (rearCW == NULL) {
        // First element
        frontCW = rearCW = newNode;
    } else {
        rearCW->next = newNode;
        rearCW = newNode;
    }

    printf("'%s' added to Continue Watching.\n", title);
}

//Dequeue (Remove first element)
void dequeueCW() {
    if (frontCW == NULL) {
        printf("Continue Watching queue is empty.\n");
        return;
    }

    NODE *temp = frontCW;
    char title[50];

    if (temp->type == 1)
        strcpy(title, temp->data.movie.title);
    else
        strcpy(title, temp->data.series.title);

	//Ask Confirmation
    char ch;
    printf("Are you sure you want to remove '%s' from Continue Watching? (y/n): ", title);
    scanf(" %c", &ch);
    if (ch != 'y' && ch != 'Y') {
        printf("Deletion cancelled.\n");
        return;
    }
	
    frontCW = frontCW->next;

    if (frontCW == NULL) // if queue became empty
        rearCW = NULL;

    free(temp);
    printf("'%s' removed from Continue Watching.\n", title);
}

//Display Continue Watching Queue
void displayContinueWatching() {
    if (frontCW == NULL) {
        printf("Continue Watching is empty.\n");
        return;
    }

    NODE *temp = frontCW;
    printf("\n ---- CONTINUE WATCHING ----\n\n");
    while (temp != NULL) {
        if (temp->type == 1) {
            printf("[MOVIE] %s (%d) |   Genre: %s | Duration: %d min | Views: %d\n",
                   temp->data.movie.title, temp->data.movie.releaseYear,
                   temp->data.movie.genre, temp->data.movie.duration,
                   temp->data.movie.views);
        } else if (temp->type == 2) {
            printf("[SERIES] %s (%d) |   Genre: %s | Seasons: %d | Episodes: %d | Views: %d\n",
                   temp->data.series.title, temp->data.series.releaseYear,
                   temp->data.series.genre, temp->data.series.seasons,
                   temp->data.series.episodes, temp->data.series.views);
        }
        temp = temp->next;
    }
    printf("\n----------------------------\n");
}

//Check if Continue Watching is empty
int isEmptyCW() {
    return (frontCW == NULL);
}

//LATEST RELEASES

static NODE heap[MAX]; //static Heap array
static int heapSize = 0;

//HELPER
int getReleaseYear(NODE n) {
    return (n.type == 1) ? n.data.movie.releaseYear : n.data.series.releaseYear;
}

//INSERT
void insertPQ(char title[]) {
    if (heapSize == MAX) {
        printf("\nHeap is full!\n");
        return;
    }
	
	// check if already in heap (Latest Releases)
	for (int i = 0; i < heapSize; i++) {
		if ((heap[i].type == 1 && strcasecmp(heap[i].data.movie.title, title) == 0) ||
			(heap[i].type == 2 && strcasecmp(heap[i].data.series.title, title) == 0)) {
			printf("\n'%s' is already in Latest Releases.\n", title);
			return;
		}
	}

	NODE* ret = createNode(title);
	NODE item;
	if(ret != NULL){
		item = *ret;
		free(ret);
	}
	else{
		printf("\n'%s' not found in dataset.\n", title);
		return;
	}

    int c = heapSize;
    int p = (c - 1) / 2;

    // Move up while parent < new element (Max Heap by releaseYear)
    while (c > 0 && getReleaseYear(heap[p]) < getReleaseYear(item)) {
        heap[c] = heap[p];
        c = p;
        p = (c - 1) / 2;
    }

    heap[c] = item;
    heapSize++;
    printf("\nInserted: %s (%d)\n",
           item.type == 1 ? item.data.movie.title : item.data.series.title,
           getReleaseYear(item));
}

//HEAPIFY DOWN
void heapify(int index) {
    int p = index;
    int c = 2 * p + 1;
    NODE temp = heap[p];

    while (c < heapSize) {
        // Pick larger child
        if (c + 1 < heapSize && getReleaseYear(heap[c + 1]) > getReleaseYear(heap[c]))
            c++;

        if (getReleaseYear(temp) >= getReleaseYear(heap[c]))
            break;

        heap[p] = heap[c];
        p = c;
        c = 2 * p + 1;
    }

    heap[p] = temp;
}

//DELETE MAX
void deleteMaxPQ() {
    if (heapSize == 0) {
        printf("\nHeap is empty!\n");
        return;
    }

	//Ask Confirmation
    char ch;
    printf("Are you sure you want to delete '%s' (%d) from Latest Releases? (y/n): ", heap[0].type == 1 ? heap[0].data.movie.title : heap[0].data.series.title,
           getReleaseYear(heap[0]));
    scanf(" %c", &ch);
    if (ch != 'y' && ch != 'Y') {
        printf("Deletion cancelled.\n");
        return;
    }
	
    NODE maxItem = heap[0];
    heap[0] = heap[heapSize - 1];
    heapSize--;

    if (heapSize > 0)
        heapify(0);

    printf("\nDeleted: %s (%d)\n",
           maxItem.type == 1 ? maxItem.data.movie.title : maxItem.data.series.title,
           getReleaseYear(maxItem));
}

//PEEK
void peekPQ() {
    if (heapSize == 0) {
        printf("\nLatest Releases is empty!\n");
        return;
    }
    if(heap[0].type == 1){
		printf("\nLatest Movie: %s (%d)\n", heap[0].data.movie.title, heap[0].data.movie.releaseYear);
	}
    else
		printf("\nLatest Series: %s (%d)\n", heap[0].data.series.title, heap[0].data.series.releaseYear);
}

//DISPLAY
//HEAP SORT
void displayPQ() {
    if (heapSize == 0) {
        printf("\nNo latest releases in heap.\n");
        return;
    }

    NODE temp[MAX];

    // copy global heap to temp
    for (int i = 0; i < heapSize; i++)
        temp[i] = heap[i];

    int n = heapSize;

    // Heap sort (Max heap → ascending order)
    for (int i = n - 1; i > 0; i--) {

        // Step 1: swap root with last (max goes to end)
        NODE t = temp[0];
        temp[0] = temp[i];
        temp[i] = t;

        // Step 2: sift-down from root to restore heap
        int p = 0;          // parent index
        int size = i;       // heap size reduces each loop

        while (1) {
            int left = 2 * p + 1;
            int right = 2 * p + 2;
            int large = p;

            // choose larger of left child / parent
            if (left < size && getReleaseYear(temp[left]) > getReleaseYear(temp[large]))
                large = left;

            // choose larger of right child / current largest
            if (right < size && getReleaseYear(temp[right]) > getReleaseYear(temp[large]))
                large = right;

            // if parent is largest, heap is fixed
            if (large == p)
                break;

            // swap parent with larger child
            NODE tt = temp[p];
            temp[p] = temp[large];
            temp[large] = tt;

            // move down
            p = large;
        }
    }

    // Now temp[] is in ascending order → print reverse for "latest first"
    printf("\nLatest Releases:\n");
    for (int i = n - 1; i >= 0; i--) {
        if (temp[i].type == 1)
            printf("Movie: %-30s | Year: %d | Genre: %s | Duration: %d min | Views: %d\n",
                   temp[i].data.movie.title, temp[i].data.movie.releaseYear,
                   temp[i].data.movie.genre, temp[i].data.movie.duration, temp[i].data.movie.views);
        else
            printf("Series: %-29s | Year: %d | Genre: %s | Seasons: %d | Episodes: %d | Views: %d\n",
                   temp[i].data.series.title, temp[i].data.series.releaseYear,
                   temp[i].data.series.genre, temp[i].data.series.seasons,
                   temp[i].data.series.episodes, temp[i].data.series.views);
    }
}


//SEARCH

//Create BST Node
BSTNODE* createBSTNode(NODE* data) {
    BSTNODE* newNode = (BSTNODE*)malloc(sizeof(BSTNODE));
	if(!newNode){
		printf("Memory is not alloctaed\n");
		return NULL;
	}
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

//insert 
BSTNODE* insertBST(BSTNODE* root, NODE* data) {
    char title[50];
    if (data->type == 1)
        strcpy(title, data->data.movie.title);
    else
        strcpy(title, data->data.series.title);

    // Base case: create a node only when root is NULL
    if (root == NULL) {
        BSTNODE *newNode = createBSTNode(data);
        if (newNode == NULL) {
            printf("Unable to insert Node\n");
            return NULL;
        }
        return newNode;
    }

    char rootTitle[50];
    if (root->data->type == 1)
        strcpy(rootTitle, root->data->data.movie.title);
    else
        strcpy(rootTitle, root->data->data.series.title);

    if (strcasecmp(title, rootTitle) < 0)
        root->left = insertBST(root->left, data);
    else if (strcasecmp(title, rootTitle) > 0)
        root->right = insertBST(root->right, data);
    else
        printf("Duplicate title '%s' ignored.\n", title);

    return root;
}

//Build BST
BSTNODE* buildBST() {
    BSTNODE* root = NULL;
    NODE* temp;

    // Insert Movies
    for (int i = 0; i < movieCount; i++) {
        temp = (NODE*)malloc(sizeof(NODE));
		if (!temp) {
		    printf("Memory not allocated for movie node\n");
		    return root;
		}

        temp->data.movie = movie_arr[i];
        temp->type = 1;
        temp->next = NULL;
        root = insertBST(root, temp);
    }

    // Insert Series
    for (int i = 0; i < seriesCount; i++) {
        temp = (NODE*)malloc(sizeof(NODE));
		if (!temp) {
		    printf("Memory not allocated for series node\n");
		    return root;
		}

        temp->data.series = series_arr[i];
        temp->type = 2;
        temp->next = NULL;
        root = insertBST(root, temp);
    }

    return root;
}

/*
//Inorder traversal
void inorderBST(BSTNODE* root) {
    if (root == NULL) return;

    inorderBST(root->left);

    if (root->data->type == 1) {
        MOVIE m = root->data->data.movie;
        printf("[Movie] %s (%d) | %s | Views: %d\n", m.title, m.releaseYear, m.genre, m.views);
    } else {
        SERIES s = root->data->data.series;
        printf("[Series] %s (%d) | %s | Views: %d\n", s.title, s.releaseYear, s.genre, s.views);
    }

    inorderBST(root->right);
}
*/

//Search by Title
BSTNODE* searchBST(BSTNODE* root, char title[]) {
    if (root == NULL) return NULL;

    char rootTitle[50];
    if (root->data->type == 1)
        strcpy(rootTitle, root->data->data.movie.title);
    else
        strcpy(rootTitle, root->data->data.series.title);

    int cmp = strcasecmp(title, rootTitle);
	
	//Base condition
    if (cmp == 0) return root;
	
    else if (cmp < 0) return searchBST(root->left, title);
    else return searchBST(root->right, title);
}

//DISPLAY ALL Movies and Series
void displayMovies()
{
	if(movieCount == 0){
		printf("There are NO Movies in Dataset\n");
		return;
	}
	printf("\nMOVIES:\n\n");
	for (int i = 0; i < movieCount; i++){
		printf("%-35s | %-15s | %d\n", movie_arr[i].title, movie_arr[i].genre, movie_arr[i].releaseYear);
	}
}

void displaySeries()
{
	if(seriesCount == 0){
		printf("There are NO Series in Dataset\n");
		return;
	}
    printf("\nSERIES:\n\n");	
	for (int i = 0; i < seriesCount; i++){
		printf("%-35s | %-15s | %d\n", series_arr[i].title, series_arr[i].genre, series_arr[i].releaseYear);
	}
}


//MEMORY Freeing functions

// Free Watchlist (Singly Linked List)
void freeWatchlist() {
    NODE *temp;
    while (watchHead != NULL) {
        temp = watchHead;
        watchHead = watchHead->next;
        free(temp);
    }
}

// Free Continue Watching Queue
void freeContinueWatching() {
    NODE *temp;
    while (frontCW != NULL) {
        temp = frontCW;
        frontCW = frontCW->next;
        free(temp);
    }
    rearCW = NULL;
}

// Free BST
//using post-order traversal
void freeBST(BSTNODE *root) {
    if (root == NULL) return;
	
    freeBST(root->left);
	
    freeBST(root->right);
	
    if (root->data != NULL){
		free(root->data);
	}
    free(root);
}


//DISPLAY BY LETTER
void displayContentByLetter(char ch) {
    ch = tolower(ch);
    int foundMovie = 0, foundSeries = 0;

    printf("\n------------------------------\n");
    printf("Results for '%c'\n", ch);
    printf("------------------------------\n\n");

    // --- MOVIES ---
    printf("MOVIES starting with '%c':\n\n", ch);

    for (int i = 0; i < movieCount; i++) {
        if (tolower(movie_arr[i].title[0]) == ch) {
            printf("%-35s | %-15s | %d\n",
                   movie_arr[i].title,
                   movie_arr[i].genre,
                   movie_arr[i].releaseYear);
            foundMovie = 1;
        }
    }

    if (!foundMovie)
        printf("No movies found starting with '%c'.\n", ch);

    

    // --- SERIES ---
    printf("\nSERIES starting with '%c':\n\n", ch);

    for (int i = 0; i < seriesCount; i++) {
        if (tolower(series_arr[i].title[0]) == ch) {
            printf("%-35s | %-15s | %d\n",
                   series_arr[i].title,
                   series_arr[i].genre,
                   series_arr[i].releaseYear);
            foundSeries = 1;
        }
    }

    if (!foundSeries)
        printf("No series found starting with '%c'.\n", ch);

}
















