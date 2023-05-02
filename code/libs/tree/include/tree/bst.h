/**
 * @file bst.h
 *
 * @author Samah A. SHAYYA
 *
 * @brief This file contains the data structure and functions associated with
 *        binary search tree (BST).
 */

#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <stdlib.h>

/**
 * REMARK:
 *
 * In what follows we define iterative and recursive versions when they are
 * rather effective. Nonetheless, in some case, iterative version would require
 * usage of additional Stack structure. In such a case, the iterative approach
 * becomes rather more complex and it is more suited to stick with the
 * recursive approach being more efficient.
*/

/**
 * @struct BSTNode
 *
 * @brief A typical BST Node structure consisting of a value, left and right
 *        node pointers.
 */
typedef struct BSTNode {
    /**
     * @brief The value stored in the node. It can be of any type as long as it
     *        is comparable.
     */
    int value;

    /**
     * @brief Pointer to the left node in the tree that necessarily have less
     *        than or equal value to that of the current node.
     */
    struct BSTNode *left;

    /**
     * @brief Pointer to the right node in the tree that necessarily have
     *        greater value than that of the current node.
     */
    struct BSTNode *right;

} BSTNode;

/**
 * @brief Retrieves the nodes at a specific level in a Binary Search Tree (BST)
 *        using a prefeed approach. It keeps empty nodes as NULL elements to
 *        maintain the structural integrity of the BST.
 *
 * @param root Pointer to the root node of the BST.
 *
 * @param height The height of the BST.
 *
 * @param level The level for which to retrieve the nodes (zero-based index).
 *
 * @param previousLevelNodes An array of BSTNode * pointers representing the
 *                           nodes at the previous level. It should be NULL if
 *                           level is zero.
 *
 * @return A pointer to a dynamically allocated array of BSTNode * pointers.
 *         The size of the array is 2^level.
 *
 * @note The caller is responsible for freeing the memory allocated for the
 *       returned array using the free() function. It is expected that the
 *       height has been computed before calling this function to improve
 *       performance.
 */
BSTNode **getBSTLevelNodesWithPrefeed(BSTNode *root,
                                      size_t height,
                                      size_t level,
                                      BSTNode **previousLevelNodes);

/**
 * @brief Retrieves the nodes at a specific level in a Binary Search Tree (BST).
 *        It keeps empty nodes as NULL elements to maintain the structural
 *        integrity of the BST.
 *
 * @param root Pointer to the root node of the BST.
 *
 * @param height The height of the BST.
 *
 * @param level The level for which to retrieve the nodes (zero-based index).
 *
 * @return A pointer to a dynamically allocated array BSTNode * pointers of
 *         size being 2^level.
 *
 * @note The caller is responsible for freeing the memory allocated for the
 *       returned array using the free() function. Note also that the height
 *       is required as input as to improve performance, especially that is
 *       expected that has been computed prior to function call.
 */
BSTNode **getBSTLevelNodes(BSTNode *root, size_t height, size_t level);

/**
 * @brief Displays the values of a Binary Search Tree (BST) in order.
 *
 * @param root Pointer to the root node of the BST.
 */
void displayBST(BSTNode *root);

/**
 * @brief Converts a Binary Search Tree (BST) to a string representation. It
 *        gives the representation as a sorted list in ascending order.
 *
 * @param root Pointer to the root node of the BST.
 *
 * @return A dynamically allocated string representing the BST values in
 *         ascending order. The caller is responsible for freeing the memory
 *         allocated for the string.
 */
char *bstToStr(BSTNode *root);

/**
 * @brief Adds a new node with the specified value to a Binary Search Tree
 *        (BST).
 *
 * @param root Pointer to the pointer to the root node of the BST.
 *
 * @param value The value to be added to the BST.
 *
 * @return True if the value was successfully added to the BST and false
 *         otherwise.
 */
bool addBSTNode(BSTNode **root, int value);

/**
 * @brief Adds a new node with the specified value to a Binary Search Tree
 *        (BST). It utilizes recursive approach.
 *
 * @param root Pointer to the pointer to the root node of the BST.
 *
 * @param value The value to be added to the BST.
 *
 * @return True if the value was successfully added to the BST and false
 *         otherwise.
 */
bool addBSTNodeRecursively(BSTNode **root, int value);

/**
 * @brief Finds a node with the specified value in a Binary Search Tree (BST).
 *
 * @param root Pointer to the root node of the BST.
 *
 * @param value The value to be searched for.
 *
 * @return Pointer to the node with the specified value if found and NULL
 *         otherwise.
 */
BSTNode *findBSTNode(BSTNode *root, int value);

/**
 * @brief Finds a node with the specified value in a Binary Search Tree (BST).
 *        It is based on recursive approach.
 *
 * @param root Pointer to the root node of the BST.
 *
 * @param value The value to be searched for.
 *
 * @return Pointer to the node with the specified value if found and NULL
 *         otherwise.
 */
BSTNode *findBSTNodeRecursively(BSTNode *root, int value);

/**
 * @brief Deletes a node with the specified value from a Binary Search Tree
 *        (BST).
 *
 * @param root Pointer to the pointer to the root node of the BST.
 *
 * @param value The value to be deleted from the BST.
 *
 * @return True if the deletion is successful and false otherwise.
 */
bool deleteBSTNode(BSTNode **root, int value);

/**
 * @brief Deletes a node with the specified value from a Binary Search Tree
 *        (BST). It is based on recursive approach.
 *
 * @param root Pointer to the pointer to the root node of the BST.
 *
 * @param value The value to be deleted from the BST.
 *
 * @return True if the deletion is successful and false otherwise.
 */
bool deleteBSTNodeRecursively(BSTNode **root, int value);

/**
 * @brief Deletes the entire Binary Search Tree (BST).
 *
 * @param root Pointer to the pointer to the root node of the BST.
 */
void deleteEntireBST(BSTNode **root);

/**
 * @brief Retrieves the number of nodes in a Binary Search Tree (BST).
 *
 *  @param root Pointer to the root node of the BST.
 *
 * @return The total number of nodes in the BST (as non-negative integer).
 */
size_t getBSTCount(BSTNode *root);

/**
 * @brief Retrieves the height of a Binary Search Tree (BST). The height of a
 *        BST represents the number of levels in the tree. An empty tree has a
 *        zero height, and a tree with only the root node has a height of one.
 *
 * @param root Pointer to the root node of the BST.
 *
 * @return The height of the BST as a non-negative integer.
 */
size_t getBSTHeight(BSTNode *root);

/**
 * @brief Finds the maximum value in a binary search tree (BST).
 *
 * @param root Pointer to the root node of the BST.
 *
 * @param[out] maxValuePtr Pointer to the variable that will store the maximum
 *                         value once found.
 *
 * @return True if the maximum value is found and stored in `maxValue`and false
 *         if the BST is empty (root is `NULL`), in which case `maxValue` is
 *         not modified.
 *
 * @note The `maxValue` parameter must be a valid pointer to an `int` variable.
 *
 * @sa BSTNode
 */
bool maxBST(BSTNode *root, int *maxValuePtr);

/**
 * @brief Finds the minimum value in a binary search tree (BST).
 *
 * @param root Pointer to the root node of the BST.
 *
 * @param[out] minValuePtr Pointer to the variable that will store the minimum
 *                         value once found.
 *
 * @return True if the maximum value is found and stored in `maxValue`and false
 *         if the BST is empty (root is `NULL`), in which case `minValue` is
 *         not modified.
 *
 * @note The `minValue` parameter must be a valid pointer to an `int` variable.
 *
 * @sa BSTNode
 */
bool minBST(BSTNode *root, int *minValuePtr);

/**
 * @brief Converts a binary search tree (BST) into a sorted array.
 *
 * @param root Pointer to the root node of the BST.
 *
 * @return Pointer to the dynamically allocated array containing the sorted
 *         elements of the BST. The caller is responsible for freeing the
 *         memory.
 *
 * @note The BST nodes must have an integer key value. Note also that the
 *       returned array is allocated dynamically and should be freed by the
 *       caller to avoid memory leaks.
 */
int *getBSTAsSortedArray(BSTNode *root);

#endif
