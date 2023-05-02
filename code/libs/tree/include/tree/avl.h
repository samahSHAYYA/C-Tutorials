/**
 * @file avl.h
 *
 * @author Samah A. SHAYYA
 *
 * @brief This file contains the data structure and functions associated with
 *        AVL (balanced) tree.
 */

#ifndef AVL_H
#define AVL_H

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
 * @struct AVLNode
 *
 * @brief A typical AVL Node structure consisting of a value, left and right
 *        node pointers as AVL treeNode, but with the additional balanceFactor.
 *
 * @attention In AVLTree, duplicate nodes are not allowed because it could
 *            result in violation of tree property upon balancing by rotation,
 *            unlike the case of binary search tree (BST) where duplicates can
 *            be added on left subtree.
 *
 *            For AVL Tree, we can still incorporate duplicates by adding a
 *            count which is set by default to one upon first insertion then
 *            incremented with duplicates insertion. Nevertheless, we
 *            prohibited duplicates in AVL Tree. Incorporating count is left
 *            as an exercise for the learner.
 */
typedef struct AVLNode {
    /**
     * @brief The value stored in the node. It can be of any type as long as it
     *        is comparable.
     */
    int value;

    /**
     * @brief Pointer to the left node in the tree that necessarily have less
     *        than or equal value to that of the current node.
     */
    struct AVLNode *left;

    /**
     * @brief Pointer to the right node in the tree that necessarily have
     *        greater value than that of the current node.
     */
    struct AVLNode *right;

    /**
     * @brief It is the difference between the right and left heights of the
     *        sub-tree with current node being its root. To be balanced, the
     *        value should be -1, 0, or 1.
     */
    int balanceFactor;

} AVLNode;

/**
 * @brief Retrieves the nodes at a specific level in an AVL tree using a
 *        prefeed approach. It keeps empty nodes as NULL elements to maintain
 *        the structural integrity of the AVL tree.
 *
 * @param root Pointer to the root node of the AVL tree.
 *
 * @param height The height of the AVL tree.
 *
 * @param level The level for which to retrieve the nodes (zero-based index).
 *
 * @param previousLevelNodes An array of AVLNode * pointers representing the
 *                           nodes at the previous level. It should be NULL if
 *                           level is zero.
 *
 * @return A pointer to a dynamically allocated array of AVLNode * pointers.
 *         The size of the array is 2^level.
 *
 * @note The caller is responsible for freeing the memory allocated for the
 *       returned array using the free() function. It is expected that the
 *       height has been computed before calling this function to improve
 *       performance.
 */
AVLNode **getAVLLevelNodesWithPrefeed(AVLNode *root,
                                      size_t height,
                                      size_t level,
                                      AVLNode **previousLevelNodes);

/**
 * @brief Retrieves the nodes at a specific level in an AVL tree. It keeps
 *        empty nodes as NULL elements to maintain the structural integrity
 *        of the AVL tree.
 *
 * @param root Pointer to the root node of the AVL tree.
 *
 * @param height The height of the AVL tree.
 *
 * @param level The level for which to retrieve the nodes (zero-based index).
 *
 * @return A pointer to a dynamically allocated array AVLNode * pointers of
 *         size being 2^level.
 *
 * @note The caller is responsible for freeing the memory allocated for the
 *       returned array using the free() function. Note also that the height
 *       is required as input as to improve performance, especially that is
 *       expected that has been computed prior to function call.
 */
AVLNode **getAVLLevelNodes(AVLNode *root, size_t height, size_t level);

/**
 * @brief Displays the values of an AVL tree in order.
 *
 * @param root Pointer to the root node of the AVL tree.
 */
void displayAVLTree(AVLNode *root);

/**
 * @brief Converts an AVL tree to a string representation. It gives the
 *        representation as a sorted list in ascending order.
 *
 * @param root Pointer to the root node of the AVL tree.
 *
 * @return A dynamically allocated string representing the AVL tree values in
 *         ascending order. The caller is responsible for freeing the memory
 *         allocated for the string.
 */
char *avlTreeToStr(AVLNode *root);

/**
 * @brief Adds a new node with the specified value to a AVL tree.
 *
 * @param root Pointer to the pointer to the root node of the AVL tree.
 *
 * @param value The value to be added to the AVL tree.
 *
 * @return True if the value was successfully added to the AVL tree and false
 *         otherwise.
 */
bool addAVLNode(AVLNode **root, int value);

/**
 * @brief Adds a new node with the specified value to the AVL tree. It utilizes
 *        recursive approach.
 *
 * @param root Pointer to the pointer to the root node of the AVL tree.
 *
 * @param value The value to be added to the AVL tree.
 *
 * @return True if the value was successfully added to the AVL tree and false
 *         otherwise.
 */
bool addAVLNodeRecursively(AVLNode **root, int value);

/**
 * @brief Finds a node with the specified value in aAVL tree(AVL tree).
 *
 * @param root Pointer to the root node of the AVL tree.
 *
 * @param value The value to be searched for.
 *
 * @return Pointer to the node with the specified value if found and NULL
 *         otherwise.
 */
AVLNode *findAVLNode(AVLNode *root, int value);

/**
 * @brief Finds a node with the specified value in an AVL tree. It is based on
 *        recursive approach.
 *
 * @param root Pointer to the root node of the AVL tree.
 *
 * @param value The value to be searched for.
 *
 * @return Pointer to the node with the specified value if found and NULL
 *         otherwise.
 */
AVLNode *findAVLNodeRecursively(AVLNode *root, int value);

/**
 * @brief Deletes a node with the specified value from an AVL tree.
 *
 * @param root Pointer to the pointer to the root node of the AVL tree.
 *
 * @param value The value to be deleted from the AVL tree.
 *
 * @return True if the deletion is successful and false otherwise.
 */
bool deleteAVLNode(AVLNode **root, int value);

/**
 * @brief Deletes a node with the specified value from an AVL tree. It is based
 *        on recursive approach.
 *
 * @param root Pointer to the pointer to the root node of the AVL tree.
 *
 * @param value The value to be deleted from the AVL tree.
 *
 * @return True if the deletion is successful and false otherwise.
 */
bool deleteAVLNodeRecursively(AVLNode **root, int value);

/**
 * @brief Deletes the entire AVL tree.
 *
 * @param root Pointer to the pointer to the root node of the AVL tree.
 */
void deleteEntireAVL(AVLNode **root);

/**
 * @brief Retrieves the number of nodes in aAVL tree(AVL tree).
 *
 *  @param root Pointer to the root node of the AVL tree.
 *
 * @return The total number of nodes in the AVL tree (as non-negative integer).
 */
size_t getAVLCount(AVLNode *root);

/**
 * @brief Retrieves the height of the AVL tree. The height of an AVL tree
 *        represents the number of levels in the tree. An empty tree has a
 *        zero height, and a tree with only the root node has a height of one.
 *
 * @param root Pointer to the root node of the AVL tree.
 *
 * @return The height of the AVL tree as a non-negative integer.
 */
size_t getAVLHeight(AVLNode *root);

/**
 * @brief Finds the maximum value in an AVL tree.
 *
 * @param root Pointer to the root node of the AVL tree.
 *
 * @param[out] maxValuePtr Pointer to the variable that will store the maximum
 *                         value once found.
 *
 * @return True if the maximum value is found and stored in `maxValue`and false
 *         if the AVL tree is empty (root is `NULL`), in which case `maxValue`
 *         is not modified.
 *
 * @note The `maxValue` parameter must be a valid pointer to an `int` variable.
 *
 * @sa AVL treeNode
 */
bool maxAVL(AVLNode *root, int *maxValuePtr);

/**
 * @brief Finds the minimum value in an AVL tree.
 *
 * @param root Pointer to the root node of the AVL tree.
 *
 * @param[out] minValuePtr Pointer to the variable that will store the minimum
 *                         value once found.
 *
 * @return True if the maximum value is found and stored in `maxValue`and false
 *         if the AVL tree is empty (root is `NULL`), in which case `minValue`
 *         is not modified.
 *
 * @note The `minValue` parameter must be a valid pointer to an `int` variable.
 *
 * @sa AVLNode
 */
bool minAVL(AVLNode *root, int *minValuePtr);

/**
 * @brief Converts an AVL tree into a sorted array.
 *
 * @param root Pointer to the root node of the AVL tree.
 *
 * @return Pointer to the dynamically allocated array containing the sorted
 *         elements of the AVL tree. The caller is responsible for freeing the
 *         memory.
 *
 * @note The AVL tree nodes must have an integer key value. Note also that the
 *       returned array is allocated dynamically and should be freed by the
 *       caller to avoid memory leaks.
 */
int *getAVLAsSortedArray(AVLNode *root);

#endif
