/**
 * @file helpers.c
 *
 * @author Samah A. SHAYYA
 *
 * @brief This file contains data structure and other useful helper functions
 *        that can be used within a general linked list app.
 */

#include <stdio.h>

#include "helpers.h"

/**
 * REMARK:
 *
 * In all the functions, where scanf is used, it is good practice to validate
 * that it captured the correct number of variables by checking scanf return
 * value.
 *
 * EXAMPLE:
 *
 *      while(scanf("%d %d", &v1, &v2) != 2) {do ...};
 *      In such a case, allow only a limited number of retrials instead of
 *      indefinite loop.
 */


/**
 *  @brief It gets rid of any remaining unconsumed characters passed by the
 *         user to stdin. Note that fflush(stdin) is not recommended as its
 *         behaviour is undefined (some compilers such as visual studio would
 *         allow it).
 */
void clearAnyRemainingChars() {
    char c;
    while((c = getchar()) != '\n' && c != EOF);
}

void displayWelcomeMessage(const unsigned int limit){
    puts("Welcome to Linked List Console Application!");
    puts("NB: You can exit application at any time by pressing: Ctrl + C!");
    printf("    Note also that up to %u operations are allowed!\n\n", limit);
};

LIST_TYPE getListType()
{
    LIST_TYPE listType = UNORDERED;

    printf("\nPlease choose the list ordering type [for ordered press 1 and ");
    printf("any other character for unordered]: ");

    if(getchar() == '1') {
        /**
         * We flush any extra characters passed by user in order not impact
         * future prompts by using clearAnyRemainingChars() function.
         */
        clearAnyRemainingChars();

        listType = ORDERED;
    }

    return listType;
}

bool shouldUseRecursiveApproach() {
    bool useRecursive = false;

    puts("Should recursive approach be used [y/n]?");
    printf("Enter y/Y for yes, and any other charcater for no: ");

    char c = getchar();
    if(c == 'y' || c == 'Y') {
        useRecursive = true;
    }

    clearAnyRemainingChars();

    return useRecursive;
}

void displayCurrentList(Node *root, bool recursive) {
    size_t size = recursive? getCountRec(root) : getCountIter(root);

    // We use %zu in printf string format for proper display of size_t value
    printf("Current list (size = %zu): ", size);

    // Note that displayList will create a new line before and after
    displayList(root);
    puts("");
}

OPERATION_TYPE getOperationType(bool excludeUpdate) {
    OPERATION_TYPE operationType;
    int choice;

    puts("What operation you want to do next?");
    puts("0 -> Add value (default for undefined input)");
    puts("1 -> Find value");
    puts("2 -> Delete value");
    puts("3 -> Delete entire list");

    if (!excludeUpdate) {
        puts("4 -> Update an existing value");
    }

    printf("Enter your choice: ");
    scanf("%d", &choice);
    clearAnyRemainingChars();

    /**
     * Note that we can cast choice directly into OPERATION_TYPE but this is
     * not recommended for two reasons. First,it is the underlying type of enum
     * although it is probably int. Second, suppose that for some reason or
     * another, OPERATION_TYPE enumerated values where changed to start from
     * non-zero value. Thus, it is always good to work as below for safety.
     */
    switch(choice)
    {
        case 1:
            operationType = FIND;
            break;

        case 2:
            operationType = DELETE;
            break;

        case 3:
            operationType = DELETE_ALL;
            break;

        case 4:
            if(!excludeUpdate) {
                operationType = UPDATE;
                break;
            } // else fall back to default

        default:
            // default operation which is adding a value
            operationType = ADD;
    }

    return operationType;
}

void performListOperation(Node **root,
                          LIST_TYPE listType,
                          OPERATION_TYPE operationType,
                          bool recursive) {
    /**
     * Note that root is assumed different than NULL. However, *root might be
     * NULL in case of empty list. We also assume that if listType == ORDERED,
     * then operationType is different than UPDATE.
     */

    int value;

    switch(operationType)
    {
        case ADD:
            printf("Enter integer value to add: ");
            scanf("%d", &value);
            clearAnyRemainingChars();

            bool added;
            if(recursive) {
                if (listType == UNORDERED) {
                    added = addRec(root, value);
                }
                else {
                    added = addOrderedRec(root, value);
                }
            }
            else {
                if(listType == UNORDERED) {
                    added = addIter(root, value);
                }
                else {
                    added = addOrderedIter(root, value);
                }
            }

            if(added) {
                printf("The value = %d was added successfully!\n", value);
            }
            else {
                printf("The value = %d was not added!\n", value);
            }

            break;

        case FIND:
            printf("Enter integer value to find: ");
            scanf("%d", &value);
            clearAnyRemainingChars();

            Node *itemPtr;
            if(recursive) {
                if(listType == UNORDERED) {
                    itemPtr = findRec(*root, value);
                }
                else {
                    itemPtr = findOrderedRec(*root, value);
                }
            }
            else {
                if(listType == UNORDERED) {
                    itemPtr = findIter(*root, value);
                }
                else {
                    itemPtr = findOrderedIter(*root, value);
                }
            }

            if(itemPtr) {
                printf("The value = %d was found at adddress %p!\n",
                       value,
                       itemPtr);
            }
            else {
                // NULL pointer
                printf("The value = %d was not found!\n", value);
            }

            break;

        case DELETE:
            printf("Enter integer value to delete: ");
            scanf("%d", &value);
            clearAnyRemainingChars();

            bool deleted;
            if(recursive) {
                if(listType == UNORDERED) {
                    deleted = deleteRec(root, value);
                }
                else {
                    deleted = deleteOrderedRec(root, value);
                }
            }
            else {
                if(listType == UNORDERED) {
                    deleted = deleteIter(root, value);
                }
                else {
                    deleted = deleteOrderedIter(root, value);
                }
            }

            if(deleted) {
                printf("The value = %d was deleted successfully!\n", value);
            }
            else {
                printf("The value = %d was not deleted!\n", value);
            }

            break;

        case DELETE_ALL:
            printf("The list is being entirely deleted...");

            if(recursive) {
                deleteAllRec(root);
            }
            else {
                deleteAllIter(root);
            }

            puts("The entire list has been deleted!");

            break;

        case UPDATE:
            // This is possible only in case of unordered list
            printf("Enter integer value to update: ");
            scanf("%d", &value);
            clearAnyRemainingChars();

            int newValue;
            printf("Enter the new integer value to set: ");
            scanf("%d", &newValue);
            clearAnyRemainingChars();

            bool updated;
            if(recursive) {
                updated = updateRec(*root, value, newValue);
            }
            else {
                updated = updateIter(*root, value, newValue);
            }

            if(added) {
                printf("The value = %d was updated to %d successfully!\n",
                       value,
                       newValue);
            }
            else {
                printf("The value = %d was not updated to %d!\n",
                       value,
                       newValue);
            }

            break;
    }
}
