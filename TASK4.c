#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Required for memset

// --- Structure and Global Variables ---

// Structure to define a book slot on the shelf
typedef struct {
    int id;
    int popularity;
    int lastAccessedTime; // Tracks recency for LRU eviction.
} Book;
int i;
int q;
// Global variables managed by main()
Book* shelf;          // Pointer to the dynamically allocated shelf array
int capacity;         // Maximum number of books the shelf can hold
int currentSize = 0;    // Number of books currently on the shelf
int timeCounter = 0;    // Global counter updated with every operation

// --- Helper Function: Find a Book's Index ---
// Returns the index of the book, or -1 if not found.
int findBook(int targetID) {
    for ( i = 0; i < currentSize; i++) {
        // Search up to the number of valid books
        if (shelf[i].id == targetID) { 
            return i; 
        }
    }
    return -1;
}

// --- Operation 1: ADD x y ---
void ADD(int x, int y) {
    // 1. Increment time for recency tracking
    timeCounter++; 
    int index = findBook(x); // Check if the book already exists

    if (index != -1) {
        // Scenario 1: Book Exists (Update Score and Recency)
        shelf[index].popularity = y;
        shelf[index].lastAccessedTime = timeCounter;
        return;
    }

    // Scenario 2: Shelf NOT Full (Add to next available slot)
    if (currentSize < capacity) {
        shelf[currentSize].id = x;
        shelf[currentSize].popularity = y;
        shelf[currentSize].lastAccessedTime = timeCounter;
        currentSize++;
        return;
    }

    // Scenario 3: Shelf IS Full (LRU Eviction)
    if (currentSize == capacity) {
        int lruIndex = 0;
        int oldestTime = shelf[0].lastAccessedTime;

        // Find the index of the Least Recently Used (LRU) book
        for ( i = 1; i < capacity; i++) {
            // The smallest time stamp is the oldest book
            if (shelf[i].lastAccessedTime < oldestTime) {
                oldestTime = shelf[i].lastAccessedTime;
                lruIndex = i; // Save the index to overwrite
            }
        }

        // Overwrite the LRU book's slot with the new book data
        shelf[lruIndex].id = x;
        shelf[lruIndex].popularity = y;
        shelf[lruIndex].lastAccessedTime = timeCounter;
    }
}

// --- Operation 2: ACCESS x ---
int ACCESS(int x) {
    // 1. Find the book
    int index = findBook(x);

    if (index != -1) {
        // 2. Increment time and update recency (Crucial for LRU)
        timeCounter++; 
        shelf[index].lastAccessedTime = timeCounter; 
        
        // 3. Return the popularity score
        return shelf[index].popularity;
    } else {
        // 4. Book not found
        return -1; // Sentinel value for "not found"
    }
}

// --- Main Execution ---
int main(){
    int Q;
	printf("Enter Capacity and number of operation:\n"); // Number of operations
    
    // Read Capacity (C) and Number of Operations (Q)
    if (scanf("%d %d", &capacity, &Q) != 2) return 1;

    // Dynamically allocate memory for the shelf array
    shelf = (Book*)malloc(capacity * sizeof(Book));
    if (shelf == NULL) return 1;

    

    char operation[5];
    int id, score;
    

    // Loop through the total number of operations (Q)
    for(q = 0; q < Q; q++) {
    	printf("Enter ADD or ACCESSS for book:");
        if (scanf("%s", operation) != 1) break; 

        if (operation[0] == 'A' && operation[1] == 'D') {
		 printf("ENTER ID and Score of book:");
            if (scanf("%d %d", &id, &score) == 2) {
                ADD(id, score);
            }
            
        } else if (operation[0] == 'A' && operation[1] == 'C') { // ACCESS x
            
			printf("ENTER ID of book :");
			if(scanf("%d", &id) == 1) {
                printf("%d\n", ACCESS(id));
            }
        }
    }

    // Clean up allocated memory before exiting
    free(shelf); 
    return 0;
}
