/**
 * @file avl.c
 *
 * @author Samah A. SHAYYA
 *
 * @brief This file contains the implementation of the functions associated
 *        with AVL (balanced) tree.
 */

#include <stdio.h>
#include <string.h>

#include "tree/avl.h"
#include "tree/common.h"

AVLNode **getAVLLevelNodesWithPrefeed(AVLNode *root,
                                      size_t height,
                                      size_t level,
                                      AVLNode **previousLevelNodes) {
    size_t numLevelNodes = 1 << level;              // 2^level
    AVLNode **nodes = NULL;

    if(root && (level < height)) {
        if(level == 0) {
            // Discard previousLevelNodes
            nodes = calloc(numLevelNodes, sizeof(AVLNode));

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
            nodes = calloc(numLevelNodes, sizeof(AVLNode));
            if(nodes) {
                // Allocation was successful
                size_t index = 0;
                for(size_t i = 0; i < (1 << (level - 1)); ++i) {
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

AVLNode **getAVLLevelNodes(AVLNode *root, size_t height, size_t level) {
    size_t numLevelNodes = 1 << level;              // 2^level
    AVLNode **nodes = NULL;

    if(root && (level < height)) {
        nodes = calloc(numLevelNodes, sizeof(AVLNode*));

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
                AVLNode *node;

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
 * @brief Returns a string representation of the given level in an AVL tree.
 *        This helper function is statically typed to limit its scope to this
 *        file only.
 *
 * @param root Pointer to the root node of the AVL tree.
 *
 * @param height The height of the AVL tree.
 *
 * @param maxNumberOfDigits The maximum number of digits that will be used to
 *                          represent a value in the AVL tree.
 *
 * @param level The level of the AVL tree for which the string representation
 *              is generated. It is zero-based index. It should be less than or
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
static char *getLevelStr(AVLNode *root,
                         size_t height,
                         size_t maxNumberOfDigits,
                         size_t level) {
    char *str = NULL;
    size_t numValues = 1 << level;          // 2 ^ level
    size_t padding, interSpacing;
    AVLNode **nodes = NULL, **prevNodes = NULL;
    bool ok;

    ok = setPaddingAndInterSpacing(height, level, &padding, &interSpacing);

    if(ok) {
        for(size_t i = 0; i <= level; ++i) {
            nodes = getAVLLevelNodesWithPrefeed(root, height, i, prevNodes);

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

void displayAVLTree(AVLNode *root) {
    size_t size = getAVLCount(root);
    size_t height = getAVLHeight(root);

    if(root) {
        int minValue, maxValue;
        minAVL(root, &minValue);
        maxAVL(root, &maxValue);
        size_t numDigits = getMaxNumberOfDigitsNeeded(minValue, maxValue);

        printf("\nAVL Tree (size = %zu, height = %zu):\n", size, height);
        char *str;

        for(size_t level = 0; level < height; ++level) {
            str = getLevelStr(root, height, numDigits, level);
            puts(str); // Automatically moves to a new line
            free(str); // Being no more needed avoiding memory leak
        }
    }
    else {
        printf("\nAVL Tree (size = 0, height = 0): Empty.\n");
    }
}

/**
 * @brief Performs an in-order traversal of an AVL tree and populates a sorted
 *        array.
 *
 * @param root Pointer to the root node of the AVL tree.
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
static void traverseAVL(AVLNode *root, int *sortedArray, size_t *indexPtr) {
    if(root) {
        if(root->left) {
            traverseAVL(root->left, sortedArray, indexPtr);
        }

        sortedArray[(*indexPtr)++] = root->value;

        if(root->right) {
            traverseAVL(root->right, sortedArray, indexPtr);
        }
    }
}

char *avlTreeToStr(AVLNode *root) {
    char *str = NULL;

    if(root) {
        size_t size = getAVLCount(root);
        int *sortedValues = malloc(size * sizeof(int));
        size_t startIndex = 0;

        if(sortedValues)
        {   // Allocation was successful and we can fill sortedValues
            traverseAVL(root, sortedValues, &startIndex);

            int minValue, maxValue, numDigits;
            minAVL(root, &minValue);
            maxAVL(root, &maxValue);
            numDigits = getMaxNumberOfDigitsNeeded(minValue, maxValue);

            /**
             * Because we are going to represent as follows:
             * 1 - Case of single element: < 122 >
             * 2 - Case of two or more elements: < 1 | 2 | 55 >
             * We assume numDigits per each element but later we use realloc
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
                 * therefore it is not necessary to check if str is not NULL.
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

/**
 * @brief Updates the balance factors of an AVL tree.  The balance factor of a
 *        node is the height of its right subtree minus the height of its left
 *        one.
 *
 * @param root A pointer to a pointer to the root node of the AVL tree.
 *
 * @return A pointer to a pointer to the deepest imbalanced node if exists;
 *         otherwise NULL.
 */
static AVLNode **updateBalanceFactors(AVLNode **root) {
    AVLNode **imbalancedNode = NULL;

    if(root && *root) {
        (*root)->balanceFactor = getAVLHeight((*root)->right) -
                                 getAVLHeight((*root)->left);

        if(abs((*root)->balanceFactor) > 1) {
            imbalancedNode = root;
        }

        AVLNode **leftImbalancedNode = NULL;
        AVLNode **rightImbalancedNode = NULL;

        leftImbalancedNode = updateBalanceFactors(&(*root)->left);
        rightImbalancedNode = updateBalanceFactors(&(*root)->right);

        /**
         * We consider the deepest imbalanced node (closest to the leaves).
         * In case, we have no imbalanced left and right nodes, then the
         * imbalancedNode is what consider.
         *
         * In case leftImbalancedNode or rightImbalancedNode is not NULL, then
         * we take the non-null value of these as the overall imbalanced node.
         * Note leftImbalancedNode and rightImbalancedNode cannot be
         * simultaneously not null.
         */
        if(leftImbalancedNode || rightImbalancedNode) {
            imbalancedNode = leftImbalancedNode ? leftImbalancedNode : rightImbalancedNode;
        }
        // Else, we keep the value of imbalancedNode
    }

    return imbalancedNode;
}

/**
 * @brief Performs a left rotation on a given node in an AVL tree to maintain
 *        its balance property.
 *
 * @param node A pointer to a pointer to the node to be rotated.
 *
 * @note The function is statically typed to limit its scope to this file only.
 */
static void rotateLeft(AVLNode **node) {
    /**
     *  Let  x be imbalanced node we have such a case:
     *                         x
     *                  T1              y
     *                            T2        z
     *                                  T3      T4
     *
     * We transform into:
     *                     y
     *              x             z
     *          T1      T2    T3      T4
     *
     * So here we have:
     *          xNode = *node
     *          yNode = (*node)->right
     *          zNode = yNode->right
     *          T1 = xNode->left
     *          T2 = yNode->left
     *          T3 = zNode->left
     *          T4 = zNode->right
     */
    AVLNode *xNode = *node;

    // We set node to point to yNode
    *node = xNode->right;

    // We set xNode->right to point to T2 (yNode->left)
    xNode->right = (*node)->left;

    // We set yNode->left to point to xNode
    (*node)->left = xNode;
}

/**
 * @brief Performs a right rotation on a given node in an AVL tree to maintain
 *        its balance property.
 *
 * @param node A pointer to a pointer to the node to be rotated.
 *
 * @note The function is statically typed to limit its scope to this file only.
 */
static void rotateRight(AVLNode **node) {
    /**
     *  Let  x be imbalanced node we have such a case:
     *                         x
     *                  y             T1
     *             z         T2
     *        T3      T4
     *
     * We transform into:
     *                     y
     *              z             x
     *          T3      T4    T2      T1
     *
     * So here we have:
     *          xNode = *node
     *          yNode = (*node)->left
     *          zNode = yNode->left
     *          T1 = xNode->right
     *          T2 = yNode->right
     *          T3 = zNode->left
     *          T4 = zNode->right
     */
    AVLNode *xNode = *node;

    // We set node to point to yNode
    *node = xNode->left;

    // We set xNode->left to point to T2 (yNode->left)
    xNode->left = (*node)->right;

    // We set yNode->right to point to xNode
    (*node)->right = xNode;
}

/**
 * @brief Balances an AVL tree by performing rotation operations on the
 *        unbalanced nodes.
 *
 * @param root A pointer to a pointer to the root node of the AVL tree.
 *
 * @note The function is statically typed to limit its scope to this file only.
 */
static void balance(AVLNode **root) {
    AVLNode **imbalancedNode = updateBalanceFactors(root);

    if(imbalancedNode) {
        if((*imbalancedNode)->balanceFactor > 1) {
            /**
             * Right-heavy tree:
             *
             * Check if right child is left-heavy. If it is the case, then a
             * right rotation should be done and followed by a left rotation.
             * Otherwise, only left rotation is needed.
             */
            if((*imbalancedNode)->right->balanceFactor < 0) {
                rotateRight(&(*imbalancedNode)->right);
            }

            rotateLeft(imbalancedNode);
        }
        else {
            /**
             * Left-heavy tree:
             *
             * Check if left child is right-heavy. If it is the case, then a
             * left rotation should be done and followed by a right rotation.
             * Otherwise, only right rotation is needed.
             */
            if((*imbalancedNode)->left->balanceFactor > 0) {
                rotateLeft(&(*imbalancedNode)->left);
            }

            rotateRight(imbalancedNode);
        }
    }

    // Definitely no more imbalanced nodes
    updateBalanceFactors(root);
}

bool addAVLNode(AVLNode **root, int value) {
    /**
     * Note that left child has inferior or equal value and right child has a
     * superior value. Note also that duplicates are allowed.
     */
    bool added = false;

    if(root) {
        AVLNode **originalRoot = root;

        while(*root) {
            if(value == (*root)->value) {
                // Duplicates in AVL tree are not allowed.
                break;
            }

            if(value <= (*root)->value) {
                root = &(*root)->left;
            }
            else {
                root = &(*root)->right;
            }
        }

        /**
         * Only execute if *root is null. Otherwise, we have duplicate value
         * and thus, should not end (another choice if we had count in AVLNode
         * struct would be increment this count).
         */
        if(!(*root)) {
            // Reached here means *root is NULL
            *root = malloc(sizeof(AVLNode));
            if(*root) {
                // Allocation was successful
                (*root)->value = value;
                (*root)->left = (*root)->right = NULL;
                (*root)->balanceFactor = 0;
                added = true;
            }

            if(originalRoot && added) {
                /**
                 * It was non-empty AVL tree and new node node hence balance
                 * might be needed.
                 */
                balance(originalRoot);
            }
            // Else, it is the first tree item and no balancing is required.
        }
    }

    return added;
}

bool addAVLNodeRecursively(AVLNode **root, int value) {
    bool added = false;

    if(root) {
        if(!(*root)) {
            // *root is NULL
            *root = malloc(sizeof(AVLNode));
            (*root)->value = value;
            (*root)->left = (*root)->right = NULL;
            (*root)->balanceFactor = 0;
            added = true;
        }
        else {
            if(value != (*root)->value) {
                if(value < (*root)->value) {
                    added = addAVLNodeRecursively(&(*root)->left, value);
                }
                else {
                    added = addAVLNodeRecursively(&(*root)->right, value);
                }
            }
            // Else, duplicate value ==> discard.
        }
    }

    if(added) {
        balance(root);
    }

    return added;
}

AVLNode *findAVLNode(AVLNode *root, int value) {
    // As duplicates are allowed, the function stops at first occurrence
    AVLNode *itemPtr = NULL;

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

AVLNode *findAVLNodeRecursively(AVLNode *root, int value) {
    AVLNode *itemPtr = NULL;

    if(!root || root->value == value) {
        itemPtr = root;
    }
    else {
        if(value < root->value) {
            itemPtr = findAVLNodeRecursively(root->left, value);
        }
        else {
            itemPtr = findAVLNodeRecursively(root->right, value);
        }
    }

    return itemPtr;
}

/**
 * @brief This is a helper function used by deleteAVLNode and
 *        deleteAVLNodeRecursively in case of deleting an AVL tree node with no
 *        children. It is statically typed to limit its scope to this file only.
 *
 * @param node Pointer to the pointer of the AVL tree node to be deleted.
*/
static void deleteAVLNodeWithNoChildren(AVLNode **node) {
    /**
     * Here we did not check for node and *node as we assume that the input is
     * properly validated prior to calling.
     */
    free(*node);
    *node = NULL;
}

/**
 * @brief This is a helper function used by deleteAVLNode and
 *        deleteAVLNodeRecursively in case of deleting an AVL tree node with
 *        single child. It is statically typed to limit its scope to this file
 *        only.
 *
 * @param node Pointer to the pointer of the AVL tree node to be deleted.
 */
static void deleteAVLNodeWithSingleChild(AVLNode **node) {
    /**
     * Here we did not check for node and *node as we assume that the input is
     * properly validated prior to calling.
     */
    AVLNode *itemPtr = *node;

    if((*node)->left) {
        *node = (*node)->left;
    }
    else {
        *node = (*node)->right;
    }

    free(itemPtr);
}

/**
 * @brief This is a helper function used by deleteAVLNode and
 *        deleteAVLNodeRecursively in case of deleting an AVL tree node with
 *        two children. It is statically typed to limit its scope to this file
 *        only.
 *
 * @param node Pointer to the pointer of the AVL tree node to be deleted.
 */
static void deleteAVLNodeWithTwoChildren(AVLNode **node) {
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
     * as the aforementioned one.
     *
     * In the following, we will stick to the first approach.
     */
    AVLNode *itemPtr = *node;
    AVLNode *successor = (*node)->right;

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
         * Meaning successor is the same as itemPtr->right (i.e. (*node)->right)
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

bool deleteAVLNode(AVLNode **root, int value) {
    bool deleted = false;
    AVLNode **initialRoot = root; // Keep a copy for later balancing

    if(root) {
        while(*root) {
            if((*root)->value == value) {
                if((*root)->left == NULL && (*root)->right == NULL) {
                    // The node to be deleted has no children
                    deleteAVLNodeWithNoChildren(root);
                }
                else {
                    // At least one child is not NULL
                    if((*root)->left == NULL || (*root)->right == NULL) {
                        // One and only one of the child nodes exist
                        deleteAVLNodeWithSingleChild(root);
                    }
                    else {
                        // Having left and right children nodes
                        deleteAVLNodeWithTwoChildren(root);
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

    if(deleted) {
        balance(initialRoot);
    }

    return deleted;
}

bool deleteAVLNodeRecursively(AVLNode **root, int value) {
    bool deleted = false;
    AVLNode **initialRoot = root;   // Keep a copy for later balancing

    if(root) {
        if(*root) {
            if((*root)->value == value) {
                if((*root)->left == NULL && (*root)->right == NULL) {
                    deleteAVLNodeWithNoChildren(root);
                }
                else {
                    // At least one child is not NULL
                    if((*root)->left == NULL || (*root)->right == NULL) {
                        deleteAVLNodeWithSingleChild(root);
                    }
                    else {
                        deleteAVLNodeWithTwoChildren(root);
                    }
                }
                deleted = true;
            }
            else {
                if(value < (*root)->value) {
                    // Traverse the left subtree
                    deleted = deleteAVLNodeRecursively(&(*root)->left, value);
                }
                else {
                    // Traverse the right subtree
                    deleted = deleteAVLNodeRecursively(&(*root)->right, value);
                }
            }
        }
    }

    if(deleted) {
        balance(initialRoot);
    }

    return deleted;
}

void deleteEntireAVL(AVLNode **root) {
    /**
     * It will directly utilize recursion as iterative approach requires usage
     * of Stack structure, which makes it memory intensive and rather more
     * complex.
     */

    if(root && *root) {
        // Delete left subtree
        deleteEntireAVL(&(*root)->left);

        // Delete right subtree
        deleteEntireAVL(&(*root)->right);

        // Delete this node
        free(*root);
        *root = NULL;
    }
}

size_t getAVLCount(AVLNode *root) {
    // We'll use recursive approach as iterative approach is less efficient
    size_t count = 0;

    if(root) {
        count = 1 + getAVLCount(root->left) + getAVLCount(root->right);
    }

    return count;
}

size_t getAVLHeight(AVLNode *root) {
    // We'll use recursive approach here being more efficient and simpler
    size_t height = 0;

    if(root) {
        size_t  leftHeight = getAVLHeight(root->left);
        size_t rightHeight = getAVLHeight(root->right);

        // The parenthesis around ?: expression is needed to function properly.
        height = 1 + (leftHeight >= rightHeight? leftHeight : rightHeight);
    }

    return height;
}

bool maxAVL(AVLNode *root, int *maxValuePtr) {
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

bool minAVL(AVLNode *root, int *minValuePtr) {
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

int *getAVLAsSortedArray(AVLNode *root) {
    int *sortedArray = NULL;

    if(root) {
        // Getting items' count
        size_t count = getAVLCount(root);

        // Setting start index to zero
        size_t index = 0;

        // Allocating the sortedArray required memory
        sortedArray = malloc(count * sizeof(int));

        if(sortedArray) {
            // Allocation was successful
            traverseAVL(root, sortedArray, &index);
        }
    }

    return sortedArray;
}
