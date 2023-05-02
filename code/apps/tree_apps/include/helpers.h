/**
 * @file helpers.h
 *
 * @author Samah A. SHAYYA
 *
 * @brief This file contains data structure and other useful helper functions
 *        that can be used within a general linked list app.
 */

#ifndef HELPERS_H
#define HELPERS_H

#ifdef AVL
    #include "tree/avl.h"

    typedef AVLNode Node;

    #define nodeToStr avlTreeToStr
    #define addIter addAVLNode
    #define addRec addAVLNodeRecursively
    #define findIter findAVLNode
    #define findRec findAVLNodeRecursively
    #define getLevelNodesWithPrefeed getAVLLevelNodesWithPrefeed
    #define getLevelNodes getAVLLevelNodes
    #define deleteIter deleteAVLNode
    #define deleteRec deleteAVLNodeRecursively
    #define deleteAll deleteEntireAVL
    #define getCount getAVLCount
    #define getHeight getAVLHeight
    #define maxTree maxAVL
    #define minTree minAVL
    #define displayTree displayAVLTree
#else
    #include "tree/bst.h"

    typedef BSTNode Node;

    #define nodeToStr bstToStr
    #define addIter addBSTNode
    #define addRec addBSTNodeRecursively
    #define findIter findBSTNode
    #define findRec findBSTNodeRecursively
    #define getLevelNodesWithPrefeed getBSTLevelNodesWithPrefeed
    #define getLevelNodes getBSTLevelNodes
    #define deleteIter deleteBSTNode
    #define deleteRec deleteBSTNodeRecursively
    #define deleteAll deleteEntireBST
    #define getCount getBSTCount
    #define getHeight getBSTHeight
    #define maxTree maxBST
    #define minTree minBST
    #define displayTree displayBST
#endif

/**
 * @brief An enumeration of the operation types that can be add, find, delete,
 *        or delete entire list.
 */
typedef enum OPERATION_TYPE{
    ADD,
    FIND,
    DELETE,
    DELETE_ALL
} OPERATION_TYPE;

/**
 *  @brief Displays a general welcoming message.
 */
void displayWelcomeMessage();

/**
 * @brief Prompts the user to know whether recursive approach should be used or
 *        not.
 *
 * @return True if the user selects to use recursion and false otherwise.
 */
bool shouldUseRecursiveApproach();

/**
 *  @brief Displays the tree content.
 *
 *  @param root Pointer to the root node of the tree.
 */
void displayTree(Node *root);

/**
 * @brief Gets the operation type selected by the user. It prompts the user to
 *        select an operation and returns the corresponding OPERATION_TYPE
 *        value.
 *
 * @return The OPERATION_TYPE value corresponding to the tree operation type
 *         selected by the user.
 */
OPERATION_TYPE getOperationType();

/**
 * @brief Performs a tree operation specified by the given operation type.
 *
 * @param root A pointer to the pointer to the root node of the tree. It is
 *             expected to be different than NULL.
 *
 * @param operationType The type of operation to perform on the tree.
 *
 * @param recursive If true, recursive method will be used. Otherwise, it
 *                  utilizes iterative approach.
 *
 * @attention The value of root is assumed to be different than NULL. But it is
 *            fine if *root is NULL, which is the case when we have empty tree.
 */
void performTreeOperation(Node **root,
                          OPERATION_TYPE operationType,
                          bool recursive);

#endif
