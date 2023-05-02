/**
 * @file bst.c
 *
 * @author Samah A. SHAYYA
 *
 * @brief This file contains the implementation of the functions associated
 *        with binary search tree (BST).
 */

#include <stdio.h>
#include <string.h>

#include "tree/bst.h"
#include "tree/common.h"

BSTNode **getBSTLevelNodesWithPrefeed(BSTNode *root,
                                      size_t height,
                                      size_t level,
                                      BSTNode **previousLevelNodes) {
    size_t numLevelNodes = 1 << level;              // 2^level
    BSTNode **nodes = NULL;

    if(root && (level < height)) {
        if(level == 0) {
            // Discard previousLevelNodes
            nodes = calloc(numLevelNodes, sizeof(BSTNode));

            if(nodes) {
                // Allocation was successful
                nodes[0] = root;
            }
        }
        else {
            /**
             * We are expecting that previousLevelNodes has proper size as
             * there is no built-in mechanism to determine its size.
             *
             * Expected size is 2^(level - 1).
             */
            nodes = calloc(numLevelNodes, sizeof(BSTNode));
            if(nodes) {
                // Allocation was successful
                size_t index = 0;
                for(size_t i = 0; i < (1<<(level - 1)); ++i) {
                    if(previousLevelNodes[i]) {
                        nodes[index++] = previousLevelNodes[i]->left;
                        nodes[index++] = previousLevelNodes[i]->right;
                    }
                    else {
                        index += 2;
                    }
                }
            }
        }
    }

    return nodes;
}

BSTNode **getBSTLevelNodes(BSTNode *root, size_t height, size_t level) {
    size_t numLevelNodes = 1 << level;              // 2^level
    BSTNode **nodes = NULL;

    if(root && (level < height)) {
        nodes = calloc(numLevelNodes, sizeof(BSTNode*));

        if(nodes) {
            // Allocation was successful
            nodes[0] = root;

            size_t currentLevel = 0;

            /**
             * Current level number of values and current nodes' offset within
             * nodes.
             */
            size_t currentNumValues = 1 << currentLevel;
            size_t currentOffset = numLevelNodes;

            while(currentLevel < level) {
                // This holds the current node to expand
                BSTNode *node;

                // This is the next level offset
                size_t nextOffset = currentOffset / 2;

                for (size_t i = 0; i < currentNumValues; i++)
                {
                    /**
                     * This is the current node that needs to be expanded into
                     * its left and right children, regardless of being NULL or
                     * not.
                     */
                    node = nodes[i * currentOffset];

                    if(node) {
                        nodes[currentOffset * i] = node->left;
                        nodes[currentOffset * i + nextOffset] = node->right;
                    }
                }

                currentLevel++;
                currentNumValues = 1 << currentLevel;
                currentOffset = nextOffset;
            }
        }
    }

    return nodes;
}

/**
 * @brief Returns a string representation of the given level in a binary search
 *        tree (BST). This helper function is statically typed to limit its
 *        scope to this file only.
 *
 * @param root Pointer to the root node of the BST.
 *
 * @param height The height of the binary search tree.
 *
 * @param maxNumberOfDigits The maximum number of digits that will be used to
 *                          represent a value in the BST.
 *
 * @param level The level of the BST for which the string representation is
 *              generated. It is zero-based index. It should be less than or
 *              equal to (height - 1).
 *
 * @return A char * pointer to the dynamically allocated string representing
 *         the level.
 *
 * @note The returned string must be freed by the caller using `free()` to
 *       avoid memory leaks.
 *
 * @attention The values of height and level are assumed to be valid.
 */
static char *getLevelStr(BSTNode *root,
                         size_t height,
                         size_t maxNumberOfDigits,
                         size_t level) {
    char *str = NULL;
    size_t numValues = 1 << level;          // 2 ^ level
    size_t padding, interSpacing;
    BSTNode **nodes = NULL, **prevNodes = NULL;
    bool ok;

    ok = setPaddingAndInterSpacing(height, level, &padding, &interSpacing);

    if(ok) {
        for(size_t i = 0; i <= level; ++i) {
            nodes = getBSTLevelNodesWithPrefeed(root, height, i, prevNodes);

            if(prevNodes) {
                /**
                 * Freeing previous nodes as no more needed and if not NULL,
                 * which is the case for i = 0.
                 */
                free(prevNodes);
            }

            prevNodes = nodes;
        }

        size_t numChars;

        // Number of total blocks including spaces and node values
        numChars = padding + interSpacing * (numValues - 1) + numValues;

        // Multiply by maxNumberOfDigits to get number of characters
        numChars *= maxNumberOfDigits;

        // Adding one to consider null character '\0'
        numChars += 1;

        str = malloc(numChars * sizeof(char));
    }

    if(str && nodes) {
        // Adding left padding
        sprintf(str, "%*s", (int) (padding * maxNumberOfDigits), "");

        // Adding values and interspaces
        for (size_t i = 0; i < numValues - 1; ++i) {
            // Adding nodes[i] value
            if(nodes[i]) {
                // nodes[i] is not NULL
                sprintf(str + strlen(str),
                        "%*d",
                        (int) maxNumberOfDigits,
                        nodes[i]->value);
            }
            else {
                // nodes[i] is NULL
                sprintf(str + strlen(str), "%*s", (int) maxNumberOfDigits, "");
            }

            // Adding interspace
            sprintf(str + strlen(str),
                    "%*s",
                    (int) (interSpacing * maxNumberOfDigits),
                    "");
        }

        // Adding last value
        if(nodes[numValues - 1]) {
            // Last value is not NULL
            sprintf(str + strlen(str),
                    "%*d",
                    (int) maxNumberOfDigits,
                    nodes[numValues -1]->value);
        }
        else {
            // Last value is NULL
            sprintf(str + strlen(str), "%*s", (int) maxNumberOfDigits, "");
        }
    }

    if(nodes) {
        // Freeing nodes as no more used
        free(nodes);
    }

    return str;
}

void displayBST(BSTNode *root) {
    size_t size = getBSTCount(root);
    size_t height = getBSTHeight(root);

    if(root) {
        int minValue, maxValue;
        minBST(root, &minValue);
        maxBST(root, &maxValue);
        size_t numDigits = getMaxNumberOfDigitsNeeded(minValue, maxValue);

        printf("\nBST (size = %zu, height = %zu):\n", size, height);
        char *str;

        for(size_t level = 0; level < height; ++level) {
            str = getLevelStr(root, height, numDigits, level);
            puts(str); // Automatically moves to a new line
            free(str); // Being no more needed avoiding memory leak
        }
    }
    else {
        printf("\nBST (size = 0, height = 0): Empty.\n");
    }
}

/**
 * @brief Performs an in-order traversal of a Binary Search Tree (BST) and
 *        populates a sorted array.
 *
 * @param root Pointer to the root node of the BST.
 *
 * @param sortedArray Pointer to the sorted array where the values will be
 *                    stored.
 *
 * @param indexPtr Pointer to the current start index in the sorted array.
 *
 * @note This is an internal function and is not meant to be called directly.
 *       That's why it is statically typed assuring scope limitation to this
 *       file only.
 */
static void traverseBST(BSTNode *root, int *sortedArray, size_t *indexPtr) {
    if(root) {
        if(root->left) {
            traverseBST(root->left, sortedArray, indexPtr);
        }

        sortedArray[(*indexPtr)++] = root->value;

        if(root->right) {
            traverseBST(root->right, sortedArray, indexPtr);
        }
    }
}

char *bstToStr(BSTNode *root) {
    char *str = NULL;

    if(root) {
        size_t size = getBSTCount(root);
        int *sortedValues = malloc(size * sizeof(int));
        size_t startIndex = 0;

        if(sortedValues)
        {   // Allocation was successful and we can fill sortedValues
            traverseBST(root, sortedValues, &startIndex);

            int minValue, maxValue, numDigits;
            minBST(root, &minValue);
            maxBST(root, &maxValue);
            numDigits = getMaxNumberOfDigitsNeeded(minValue, maxValue);

            /**
             * Because we are going to represent as follows:
             * 1 - Case of single element: < 122 >
             * 2 - Case of two or more elements: < 1 | 2 | 55 >
             * We assume numDigits per each eleemnt but later we use realloc
             * to shrink memory as needed.
             */
            size_t numChars = size * numDigits + 3 * (size - 1) + 5;

            str = malloc(numChars * sizeof(char));
            if(str) {
                // Allocation was successful
                sprintf(str, "< ");
                for(size_t i = 0; i < size - 1; ++i) {
                    sprintf(str + strlen(str), "%d | ", sortedValues[i]);
                }

                // Adding last element
                sprintf(str + strlen(str), "%d >", sortedValues[size - 1]);

                /**
                 * Reducing allocated memory block to exactly fit string
                 * length (note that memory needed is sting length + 1
                 * to accommodate '\0' character). This should not fail as we
                 * are shrinking the allocated memory not enlarging it, and
                 * therefore it is not necessary to checkif str is not NULL.
                 */
                str = realloc(str, (strlen(str) + 1) * sizeof(char));
            }
        }
    }
    else {
        size_t numChars = snprintf(NULL, 0, "< >");
        str = malloc((numChars + 1) * sizeof(char));
        memcpy(str, "< >", numChars + 1);
    }

    return str;
}

bool addBSTNode(BSTNode **root, int value) {
    /**
     * Note that left child has inferior or equal value and right child has a
     * superior value. Note also that duplicates are allowed.
     */

    bool added = false;

    if(root) {
        while(*root) {
            if(value <= (*root)->value) {
                root = &(*root)->left;
            }
            else {
                root = &(*root)->right;
            }
        }

        // Reached here means *root is NULL
        *root = malloc(sizeof(BSTNode));
        if(*root) {
            // Allocation was successful
            (*root)->value = value;
            (*root)->left = (*root)->right = NULL;
            added = true;
        }
    }

    return added;
}

bool addBSTNodeRecursively(BSTNode **root, int value) {
    bool added = false;

    if(root) {
        if(!(*root)) {
            // *root is NULL
            *root = malloc(sizeof(BSTNode));
            (*root)->value = value;
            (*root)->left = (*root)->right = NULL;
            added = true;
        }
        else {
            if(value <= (*root)->value) {
                added = addBSTNodeRecursively(&(*root)->left, value);
            }
            else {
                added = addBSTNodeRecursively(&(*root)->right, value);
            }
        }
    }

    return added;
}

BSTNode *findBSTNode(BSTNode *root, int value) {
    // As duplicates are allowed, the function stops at first occurrence
    BSTNode *itemPtr = NULL;

    while(root) {
        if(value == root->value) {
            itemPtr = root;
            break;
        }
        else {
            root = value < root->value? root->left : root->right;
        }
    }

    return itemPtr;
}

BSTNode *findBSTNodeRecursively(BSTNode *root, int value) {
    BSTNode *itemPtr = NULL;

    if(!root || root->value == value) {
        itemPtr = root;
    }
    else {
        if(value < root->value) {
            itemPtr = findBSTNodeRecursively(root->left, value);
        }
        else {
            itemPtr = findBSTNodeRecursively(root->right, value);
        }
    }

    return itemPtr;
}

/**
 * @brief This is a helper function used by deleteBSTNode and
 *        deleteBSTNodeRecursively in case of deleting a BST node with no
 *        children. It is statically typed to limit its scope to this file only.
 *
 * @param node Pointer to the pointer of the BST node to be deleted.
*/
static void deleteBSTNodeWithNoChildren(BSTNode **node) {
    /**
     * Here we did not check for node and *node as we assume that the input is
     * properly validated prior to calling.
     */
    free(*node);
    *node = NULL;
}

/**
 * @brief This is a helper function used by deleteBSTNode and
 *        deleteBSTNodeRecursively in case of deleting a BST node with single
 *        child. It is statically typed to limit its scope to this file only.
 *
 * @param node Pointer to the pointer of the BST node to be deleted.
 */
static void deleteBSTNodeWithSingleChild(BSTNode **node) {
    /**
     * Here we did not check for node and *node as we assume that the input is
     * properly validated prior to calling.
     */
    BSTNode *itemPtr = *node;

    if((*node)->left) {
        *node = (*node)->left;
    }
    else {
        *node = (*node)->right;
    }

    free(itemPtr);
}

/**
 * @brief This is a helper function used by deleteBSTNode and
 *        deleteBSTNodeRecursively in case of deleting a BST node with two
 *        children. It is statically typed to limit its scope to this file only.
 *
 * @param node Pointer to the pointer of the BST node to be deleted.
 */
static void deleteBSTNodeWithTwoChildren(BSTNode **node) {
    /**
     * Here we did not check for node and *node as we assume that the input is
     * properly validated prior to calling.
     *
     * How to deal with having left and right children nodes being not NULL?
     *
     * One way is to find the leftmost child in the right subtree, which will
     * be less than all the subtree elements. So we can move it up so it points
     * to initial (*root)->left and modified (*root)->right (after removing
     * the leftmost node and replacing the left pointer in the parent to the
     * right subtree of the removed leftmost element).
     *
     * Another way, would be to find the right most child in the left subtree.
     * It will be greater than all the subtree elements and less than the
     * initial right subtree elements. We can then work in a similar approach
     * as the abovementioned one.
     *
     * In the following, we will stick to the first approach.
     */
    BSTNode *itemPtr = *node;
    BSTNode *successor = (*node)->right;

    while(successor->left && successor->left->left) {
        /**
         * Move one step to the left assuring we have access to left child
         * and its parent.
         */
        successor = successor->left;
    }

    /**
     * Reached here means no more left child, i.e.,:
     *      successor->left == NULL or successor->left->left == NULL.
     */
    if(successor->left) {
        *node = successor->left;
        successor->left = successor->left->right;
        (*node)->right = itemPtr->right;
    }
    else {
        /**
         * Meaning succesor is the same as itemPtr->right (i.e. (*node)->right)
         * Note that here we do not have to update (*node)->right.
         */
        *node = successor;
    }

    /**
     * In all cases, we need to update (*node)->left to initial left child of
     * itemPtr.
     */
    (*node)->left = itemPtr->left;

    free(itemPtr);
}

bool deleteBSTNode(BSTNode **root, int value) {
    bool deleted = false;

    if(root) {
        while(*root) {
            if((*root)->value == value) {
                if((*root)->left == NULL && (*root)->right == NULL) {
                    // The node to be deleted has no children
                    deleteBSTNodeWithNoChildren(root);
                }
                else {
                    // At least one child is not NULL
                    if((*root)->left == NULL || (*root)->right == NULL) {
                        // One and only one of the child nodes exist
                        deleteBSTNodeWithSingleChild(root);
                    }
                    else {
                        // Having left and right children nodes
                        deleteBSTNodeWithTwoChildren(root);
                    }
                }

                deleted = true;
                break;
            }
            else {
                root = value < (*root)->value? &(*root)->left : &(*root)->right;
            }
        }
    }

    return deleted;
}

bool deleteBSTNodeRecursively(BSTNode **root, int value) {
    bool deleted = false;

    if(root) {
        if(*root) {
            if((*root)->value == value) {
                if((*root)->left == NULL && (*root)->right == NULL) {
                    deleteBSTNodeWithNoChildren(root);
                }
                else {
                    // At least one child is not NULL
                    if((*root)->left == NULL || (*root)->right == NULL) {
                        deleteBSTNodeWithSingleChild(root);
                    }
                    else {
                        deleteBSTNodeWithTwoChildren(root);
                    }
                }

            }
            else {
                if(value < (*root)->value) {
                    // Traverse the left subtree
                    deleted = deleteBSTNodeRecursively(&(*root)->left, value);
                }
                else {
                    // Traverse the right subtree
                    deleted = deleteBSTNodeRecursively(&(*root)->right, value);
                }
            }
        }
    }

    return deleted;
}

void deleteEntireBST(BSTNode **root) {
    /**
     * It will directly utilize recursion as iterative approach requires usage
     * of Stack structure, which makes it memory intensive and rather more
     * complex.
     */

    if(root && *root) {
        // Delete left subtree
        deleteEntireBST(&(*root)->left);

        // Delete right subtree
        deleteEntireBST(&(*root)->right);

        // Delete this node
        free(*root);
        *root = NULL;
    }
}

size_t getBSTCount(BSTNode *root) {
    // We'll use recursive approach as iterative approach is less efficient
    size_t count = 0;

    if(root) {
        count = 1 + getBSTCount(root->left) + getBSTCount(root->right);
    }

    return count;
}

size_t getBSTHeight(BSTNode *root) {
    // We'll use recursive approach here being more efficient and simpler
    size_t height = 0;

    if(root) {
        size_t  leftHeight = getBSTHeight(root->left);
        size_t rightHeight = getBSTHeight(root->right);

        // The paranthesis around ?: expression is needed to function properly.
        height = 1 + (leftHeight >= rightHeight ? leftHeight : rightHeight);
    }

    return height;
}

bool maxBST(BSTNode *root, int *maxValuePtr) {
    bool maxFound = false;

    if(root) {
        while(root->right) {
            // Traverse to reach the rightmost node being the largest
            root = root->right;
        }

        // Reached rightmost node
        if(maxValuePtr) {
            // Assure we have valid pointer so that we can write maxValue
            *maxValuePtr = root->value;
            maxFound = true;
        }
    }

    return maxFound;
}

bool minBST(BSTNode *root, int *minValuePtr) {
    bool minFound = false;

    if(root) {
        while(root->left) {
            // Traverse to reach the leftmost node being the smallest
            root = root->left;
        }

        // Reached leftmost node
        if(minValuePtr) {
            // Assure we have valid pointer so that we can write maxValue
            *minValuePtr = root->value;
            minFound = true;
        }
    }

    return minFound;
}

int *getBSTAsSortedArray(BSTNode *root) {
    int *sortedArray = NULL;

    if(root) {
        // Getting items' count
        size_t count = getBSTCount(root);

        // Setting start index to zero
        size_t index = 0;

        // Allocating the sortedArray required memory
        sortedArray = malloc(count * sizeof(int));

        if(sortedArray) {
            // Allocation was successful
            traverseBST(root, sortedArray, &index);
        }
    }

    return sortedArray;
}
