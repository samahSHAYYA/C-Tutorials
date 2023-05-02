/**
 * @file bidirectional.c
 *
 * @author Samah A. SHAYYA
 *
 * @brief This file contains the implementation of the functions associated with
 *        bidirectional linked lists, embracing both unordered and ordered
 *        versions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list/bidirectional.h"
#include "linked_list/common.h"

// Task 1: Data Structure Declaration and Textual Description
void displayBiList(BiNode *root) {
    printf("\n< ");
    while(root) {
        if(root->next) {
            printf("%d | ", root->value);
        }
        else {
            printf("%d ", root->value);
        }

        root = root->next;
    }

    printf(">\n");
}

char *biListToString(BiNode *root) {
    // We use initialize function with string literals to assure we have
    // malloc-ed strings that can be free-d.
    char *str = NULL, *tmp_str, *item = NULL;
    size_t len;

    if (!root) {
        str = initialize("< >");
    }
    else {
        tmp_str = initialize("");
        do {
            if (root->next) {
                len = snprintf(NULL, 0, " %d |", root->value);
                item = malloc((len + 1) * sizeof(char));
                sprintf(item, " %d |", root->value);
            }
            else {
                len = snprintf(NULL, 0, " %d ", root->value);
                item = malloc((len + 1) * sizeof(char));
                sprintf(item, " %d ", root->value);
            }

            str = concatenate(tmp_str, item);
            freeCharPtrs(2, tmp_str, item);
            tmp_str = str;

            root = root->next;
        } while(root);

        str = concatenate("<", tmp_str);
        free(tmp_str);

        tmp_str = str;
        str = concatenate(tmp_str, ">");
        free(tmp_str);
    }

    return str;
}

// Task 2: Creation Operation
bool addBiNode(BiNode **root, int value) {
    bool added = false;
    BiNode *prevPtr = NULL, *newItemPtr;

    if (root) {
        // Assured non-null value of root
        if(*root) {
            // Non-empty list: move forward until you reach last node while
            // storing predecessor node address
            while (*root) {
                prevPtr = *root;
                root = &(*root)->next;
            }
        }

        /**
         * We allocate to newItemPtr to assure we do not break existing list
         * if allcoation fails returning NULL. If it was directly assigned to
         * *root, the list is no more accessible and we would have memory leak.
         */
        newItemPtr = (BiNode*)malloc(sizeof(BiNode));
        if(newItemPtr) {
            // Allocation was successful
            *root = newItemPtr;
            (*root)->value = value;
            (*root)->prev = prevPtr;
            (*root)->next = NULL;
            added = true;
        }
    }

    return added;
}

bool addBiNodeRecursively(BiNode **root, int value) {
    bool added = false;
    BiNode *prevPtr = NULL, *newItemPtr;

    if (root) {
        if(*root && (*root)->next) {
            // Move forward until you reach last node
            added = addBiNodeRecursively(&(*root)->next, value);
        }
        else {
            prevPtr = *root;
            if(*root) {
                // Then (*root)->next is NULL
                newItemPtr = malloc(sizeof(BiNode));
                (*root)->next = newItemPtr;
                root = &(*root)->next;
            }
            else {
                /**
                 * *root is NULL meaning an empty list (here no breakage would
                 * happen if malloc is used directly)
                 */
                *root = malloc(sizeof(BiNode));
            }

            if(*root) {
                // Sucessful allocation
                (*root)->value = value;
                (*root)->prev = prevPtr;
                (*root)->next = NULL;
                added = true;
            }
        }
    }

    return added;
}

// Task 3: Read / Find Operations
BiNode *findBiNode(BiNode *root, int value) {
    BiNode *itemPtr = NULL;

    while(root) {
        if(root->value == value) {
            itemPtr = root;
            break;
        } else {
            root = root->next;
        }
    }

    return itemPtr;
}

BiNode *findBiNodeRecursively(BiNode *root, int value) {
    BiNode *itemPtr = NULL;

    if(root) {
        if(root->value == value) {
            itemPtr = root;
        } else {
            itemPtr = findBiNodeRecursively(root->next, value);
        }
    }

    return itemPtr;
}

// Task 4: Update Operation
bool updateBiNode(BiNode *root, int originalValue, int newValue) {
    bool updated = false;

    while(root) {
        if(root->value == originalValue) {
            root->value = newValue;
            updated = true;
            break;
        }
        else {
            root = root->next;
        }
    }

    return updated;
}

bool updateBiNodeRecursively(BiNode *root, int originalValue, int newValue) {
    bool updated = false;

    if(root) {
        if(root->value == originalValue) {
            root->value = newValue;
            updated = true;
        }
        else {
           updated = updateBiNodeRecursively(root->next, originalValue, newValue);
        }
    }

    return updated;
}

// Task 5: Delete Operation
bool deleteBiNode(BiNode **root, int value) {
    bool deleted = false;
    BiNode *itemPtr;

    if(root) {
        while(*root) {
            if ((*root)->value == value) {
                itemPtr = *root;
                *root = (*root)->next;

                if(*root) {
                    // The new *root is not NULL
                    (*root)->prev = itemPtr->prev;
                }

                free(itemPtr);
                deleted = true;
            }
            else {
               root = &(*root)->next;
            }
        }
    }

    return deleted;
}

bool deleteBiNodeRecursively(BiNode **root, int value) {
    bool deleted = false;
    BiNode *itemPtr;

    if(root && *root) {
        if((*root)->value == value) {
            itemPtr = *root;
            *root = (*root)->next;

            if(*root) {
                // The new *root is not NULL
                (*root)->prev = itemPtr->prev;
            }

            free(itemPtr);
            deleted = true;
        }
        else {
            deleted = deleteBiNodeRecursively(&(*root)->next, value);
        }
    }

    return deleted;
}

// Task 6: Delete Entire List
void deleteEntireBiList(BiNode **root) {
    BiNode *itemPtr;
    if(root) {
        while(*root) {
            itemPtr = *root;
            *root = (*root)->next;
            free(itemPtr);
        }
    }
}

void deleteEntireBiListRecursively(BiNode **root) {
    BiNode *itemPtr;
    if(root) {
        if(*root) {
            itemPtr = *root;
            *root = (*root)->next;
            free(itemPtr);
            deleteEntireBiListRecursively(root);
        }
    }
}

// Task 7: Getting List Length / BiNodes Count
size_t getBiNodesCount(BiNode *root) {
    size_t count = 0;
    while(root) {
        count += 1;
        root = root->next;
    }

    return count;
}

size_t getBiNodesCountRecursively(BiNode *root) {
    size_t count = 0;

    if(root) {
        count += 1 + getBiNodesCountRecursively(root->next);
    }

    return count;
}

// Task 8: Ordered Bidirectional List
bool addOrderedBiNode(BiNode **root, int value) {
    // We assume the current bidirectional list is ordered and duplicates are
    // allowed.
    bool added = false;
    BiNode *prevPtr = NULL, *itemPtr, *newItemPtr;

    if(root) {
        while(*root && (*root)->value < value) {
            prevPtr = *root;
            root = &(*root)->next;
        }

        itemPtr = *root;
        newItemPtr = malloc(sizeof(BiNode));
        if(newItemPtr) {
            *root = newItemPtr;
            (*root)->value = value;
            (*root)->next = itemPtr;
            (*root)->prev = prevPtr;

            if(itemPtr) {
                // itemPtr is not NULL
                itemPtr->prev = *root;
            }

            added = true;
        }
    }

    return added;
}

bool addOrderedBiNodeRecursively(BiNode **root, int value) {
    // We assume the current bidirectional list is ordered and duplicates are
    // allowed.
    bool added = false;
    BiNode *itemPtr, *newItemPtr;

    if(root) {
        if(!(*root) || (!((*root)->next)) || ((*root)->value >= value)) {
            if(*root && ((*root)->value >= value)) {
                itemPtr = *root;
                newItemPtr = malloc(sizeof(BiNode));
                if(newItemPtr) {
                    *root = newItemPtr;
                    (*root)->value = value;
                    (*root)->next = itemPtr;
                    (*root)->prev = itemPtr->prev;
                    itemPtr->prev = *root;
                    added = true;
                }
            }
            else {
                /**
                 * Empty list or ((*root)->value < value and (*root)->next is
                 * NULL
                 */
                itemPtr = *root;
                if(*root) {
                    // Non-empty list and we need to add at the end
                    root = &(*root)->next;
                }

                newItemPtr = malloc(sizeof(BiNode));
                if(newItemPtr) {
                    *root = newItemPtr;
                    (*root)->value = value;
                    (*root)->next = NULL;
                    (*root)->prev = itemPtr;
                    added = true;
                }
            }
        }
        else {
            added = addOrderedBiNodeRecursively(&(*root)->next, value);
        }
    }

    return added;
}

BiNode *findOrderedBiNode(BiNode *root, int value) {
    //We assume ordered bidirectional list
    BiNode *itemPtr = NULL;

    while(root && root->value < value) {
        root = root->next;
    }

    if(root && root->value == value) {
        itemPtr = root;
    }

    return itemPtr;
}

BiNode *findOrderedBiNodeRecusrively(BiNode *root, int value) {
    //We assume ordered bidirectional list
    BiNode *itemPtr = NULL;

    if(root) {
        if(root->value == value) {
            itemPtr = root;
        }
        else {
            if(root->value < value) {
                itemPtr = findOrderedBiNodeRecusrively(root->next, value);
            }
            // Else it does not exist as the values starting from current root
            // node are greater than the searched value
        }
    }

    return itemPtr;
}

bool deleteOrderedBiNode(BiNode **root, int value) {
    // We assume ordered bidirectional list
    bool deleted = false;
    BiNode *itemPtr;

    if(root) {
        while(*root && (*root)->value < value) {
            root = &(*root)->next;
        }

        if(*root && (*root)->value == value) {
            itemPtr = *root;
            *root = (*root)->next;

            if(*root) {
                // The new *root is not NULL
                (*root)->prev = itemPtr->prev;
            }

            free(itemPtr);
            deleted = true;
        }
    }

    return deleted;
}

bool deleteOrderedBiNodeRecursively(BiNode **root, int value) {
    // We assume ordered bidirectional list
    bool deleted = false;
    BiNode *itemPtr;

    if(root && *root) {
        if((*root)->value == value) {
            itemPtr = *root;
            *root = (*root)->next;

            if(*root) {
                // The new *root is not NULL
                (*root)->prev = itemPtr->prev;
            }

            free(itemPtr);
            deleted = true;
        }
        else {
            if((*root)->value < value) {
                deleted = deleteOrderedBiNodeRecursively(&(*root)->next, value);
            }
        }
    }

    return deleted;
}
