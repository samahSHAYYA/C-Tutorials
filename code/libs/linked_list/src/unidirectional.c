/**
 * @file unidirectional.c
 *
 * @author Samah A. SHAYYA
 *
 * @brief This file contains the implementation of the functions associated with
 *        unidirectional linked lists, embracing both unordered and ordered
 *        versions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list/unidirectional.h"
#include "linked_list/common.h"

// Task 1: Data Structure Declaration and Textual Description
void displayUniList(UniNode *root) {
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

char *uniListToString(UniNode *root) {
    /**
     * We use initialize function with string literals to assure we have
     * malloc-ed strings that can be free-d.
     */
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
bool addUniNode(UniNode **root, int value) {
    bool added = false;
    UniNode *newItemPtr;

    if (root) {
        // Assured non-null value of root
        if(*root) {
            // Non-empty list: move forward until you reach last node
            while (*root) {
                root = &(*root)->next;
            }
        }

        /**
         * We allocate to newItemPtr to assure we do not break existing list
         * if allcoation fails returning NULL. If it was directly assigned to
         * *root, the list is no more accessible and we would have memory leak.
         */
        newItemPtr = malloc(sizeof(UniNode));
        if(newItemPtr) {
            // Allocation was successful
            *root = newItemPtr;
            (*root)->value = value;
            (*root)->next = NULL;
            added = true;
        }
    }

    return added;
}

bool addUniNodeRecursively(UniNode **root, int value) {
    bool added = false;
    UniNode *newItemPtr;

    if (root) {
        // Assured non-null value of root
        if(*root) {
            // Move forward until you reach last node
            added = addUniNodeRecursively(&(*root)->next, value);
        }
        else {
            newItemPtr = malloc(sizeof(UniNode));
            if(newItemPtr) {
                *root = newItemPtr;
                (*root)->value = value;
                (*root)->next = NULL;
                added = true;
            }
        }
    }

    return added;
}

// Task 3: Read / Find Operations
UniNode *findUniNode(UniNode *root, int value) {
    UniNode *itemPtr = NULL;

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

UniNode *findUniNodeRecursively(UniNode *root, int value) {
    UniNode *itemPtr = NULL;

    if(root) {
        if(root->value == value) {
            itemPtr = root;
        } else {
            itemPtr = findUniNodeRecursively(root->next, value);
        }
    }

    return itemPtr;
}

// Task 4: Update Operation
bool updateUniNode(UniNode *root, int originalValue, int newValue) {
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

bool updateUniNodeRecursively(UniNode *root, int originalValue, int newValue) {
    bool updated = false;

    if(root) {
        if(root->value == originalValue) {
            root->value = newValue;
            updated = true;
        }
        else {
           updated = updateUniNodeRecursively(root->next, originalValue, newValue);
        }
    }

    return updated;
}

// Task 5: Delete Operation
bool deleteUniNode(UniNode **root, int value) {
    bool deleted = false;
    UniNode *itemPtr;

    if(root) {
        while(*root) {
            if ((*root)->value == value) {
                itemPtr = *root;
                *root = (*root)->next;
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

bool deleteUniNodeRecursively(UniNode **root, int value) {
    bool deleted = false;
    UniNode *itemPtr;

    if(root && *root) {
        if((*root)->value == value) {
            itemPtr = *root;
            *root = (*root)->next;
            free(itemPtr);
            deleted = true;
        }
        else {
            deleted = deleteUniNodeRecursively(&(*root)->next, value);
        }
    }

    return deleted;
}

// Task 6: Delete Entire List
void deleteEntireUniList(UniNode **root) {
    UniNode *itemPtr;
    if(root) {
        while(*root) {
            itemPtr = *root;
            *root = (*root)->next;
            free(itemPtr);
        }
    }
}

void deleteEntireUniListRecursively(UniNode **root) {
    UniNode *itemPtr;
    if(root) {
        if(*root) {
            itemPtr = *root;
            *root = (*root)->next;
            free(itemPtr);
            deleteEntireUniListRecursively(root);
        }
    }
}

// Task 7: Getting List Length / UniNodes Count
size_t getUniNodesCount(UniNode *root) {
    size_t count = 0;
    while(root) {
        count += 1;
        root = root->next;
    }

    return count;
}

size_t getUniNodesCountRecursively(UniNode *root) {
    size_t count = 0;

    if(root) {
        count += 1 + getUniNodesCountRecursively(root->next);
    }

    return count;
}

// Task 8: Ordered Unidirectional List
bool addOrderedUniNode(UniNode **root, int value) {
    /**
     * We assume the current unidirectional list is ordered and duplicates are
     * allowed.
     */
    bool added = false;
    UniNode *itemPtr, *newItemPtr;

    if(root) {
        while(*root && (*root)->value < value) {
            root = &(*root)->next;
        }

        itemPtr = *root;
        newItemPtr = malloc(sizeof(UniNode));
        if(newItemPtr) {
            *root = newItemPtr;
            (*root)->value = value;
            (*root)->next = itemPtr;
            added = true;
        }
    }

    return added;
}

bool addOrderedUniNodeRecursively(UniNode **root, int value) {
    bool added = false;
    UniNode *itemPtr, *newItemPtr;

    if(root) {
        if(!(*root) || (*root)->value >= value) {
            itemPtr = *root;
            newItemPtr = malloc(sizeof(UniNode));
            if(newItemPtr) {
                *root = newItemPtr;
                (*root)->value = value;
                (*root)->next = itemPtr;
                added = true;
            }
        }
        else {
            added = addOrderedUniNodeRecursively(&(*root)->next, value);
        }
    }

    return added;
}

UniNode *findOrderedUniNode(UniNode *root, int value) {
    // We assume ordered unidirectional list
    UniNode *itemPtr = NULL;

    while(root && root->value < value) {
        root = root->next;
    }

    if(root && root->value == value) {
        itemPtr = root;
    }

    return itemPtr;
}

UniNode *findOrderedUniNodeRecusrively(UniNode *root, int value) {
    UniNode *itemPtr = NULL;

    if(root) {
        if(root->value == value) {
            itemPtr = root;
        }
        else {
            if(root->value < value) {
                itemPtr = findOrderedUniNodeRecusrively(root->next, value);
            }
            // Else it does not exist as the values starting from current root
            // node are greater than the searched value
        }
    }

    return itemPtr;
}

bool deleteOrderedUniNode(UniNode **root, int value) {
    // We assume ordered unidirectional list
    bool deleted = false;
    UniNode *itemPtr;

    if(root) {
        while(*root && (*root)->value < value) {
            root = &(*root)->next;
        }

        if(*root && (*root)->value == value) {
            itemPtr = *root;
            *root = (*root)->next;
            free(itemPtr);
            deleted = true;
        }
    }

    return deleted;
}

bool deleteOrderedUniNodeRecursively(UniNode **root, int value) {
    bool deleted = false;
    UniNode *itemPtr;

    if(root && *root) {
        if((*root)->value == value) {
            itemPtr = *root;
            *root = (*root)->next;
            free(itemPtr);
            deleted = true;
        }
        else {
            if((*root)->value < value) {
                deleted = deleteOrderedUniNodeRecursively(&(*root)->next, value);
            }
        }
    }

    return deleted;
}
