/**
 * @file tree_app.c
 *
 * @author Samah A. SHAYYA
 *
 * @brief This file contains code for the tree app.
 */

#include <stdio.h>
#include <stdlib.h>     // For exit
#include <signal.h>

#include "helpers.h"

/**
 * Global variables. Note that it is mandatory to have at least root declared
 * globally to allow interrupt signal handler to delete the list entirely
 * before exiting the program. This essential to avoid memory leakage.
 *
 * Regarding recursive being global as well is to decide which delete method
 * should be used.
*/
Node *root = NULL;
bool recursive = false;

/**
 * @brief Handles interrupt signal (Ctrl + C) by deleting entire tree prior to
 *        exiting and thus avoiding memory leak.
 *
 * @param sigNum The signal number.
*/
void sigInterruptHandler(int sigNum) {
    puts("Received interrupt signal: preparing to exit the program...");

    // Deleting entire tree
    deleteAll(&root);

    puts("Deleted entire tree, and now exiting...");
    exit(0);
}

/**
 * TESTING CHALLENGE FOR THE LEARNER:
 *
 * This is the main function. It is important to note that this app testing is
 * left as an exercise for the learner.
 *
 * Here are few points to consider. This being a console app, testing is
 * different than individual functions. One approach would be to make the
 * main function as app function in such a way that it can tested as we do
 * with a normal function.
 *
 * However, we can still test as it is by redirecting stdin and stdout. If your
 * app executable is "app", then redirection can be done as below:
 *
 * On Unix-like systems: ./app < input.txt > output.txt
 *
 * On Windows systems:  type input.txt | my_app > output.txt
 *
 * You can also add this as test in to CMakeLists.txt in which you compare
 * output.txt with expected_output.txt.
 *
 */
int main() {
    /**
     * Setting an upper limit on operations that can be done to avoid the
     * unrecommended indefinite while loop. Set the limit as you see adequate.
     * Note for const declarations, we use all capital letters to distinguish
     * them from non-constant variables.
     */
    const unsigned int LIMIT = 20;

    unsigned int i = 0;

    OPERATION_TYPE operationType;

    // Setting interrupt signal handler
    signal(SIGINT, sigInterruptHandler);

    // Welcoming
    displayWelcomeMessage(LIMIT);

    // Identifying if approach should be recursive or not (i.e., iterative)
    recursive = shouldUseRecursiveApproach();

    do {
        // Increment counter;
        ++i;

        // Display the current list contents
        displayTree(root);

        /**
         * Identifying operation requested by the user.
         */
        operationType = getOperationType();

        // Performing requested operation
        performTreeOperation(&root, operationType, recursive);

    } while (i < LIMIT); // It allows limited number of operations

    puts("Reached the number of operations limit. The program will exit.");

    // Delete entire tree
    deleteAll(&root);

    puts("Press any key to exit...");
    getchar();

    return 0;
}
