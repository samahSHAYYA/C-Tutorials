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

#ifdef BIDIRECTIONAL
    #include "linked_list/bidirectional.h"
    typedef BiNode Node;

    // Defining macros to be use functions
    #define displayList displayBiList
    #define listToString biListToString
    #define addIter addBiNode
    #define addOrderedIter addOrderedBiNode
    #define addRec addBiNodeRecursively
    #define addOrderedRec addOrderedBiNodeRecursively
    #define findIter findBiNode
    #define findOrderedIter findOrderedBiNode
    #define findRec findBiNodeRecursively
    #define findOrderedRec findOrderedBiNodeRecusrively
    #define updateIter updateBiNode
    #define updateRec updateBiNodeRecursively
    #define deleteIter deleteBiNode
    #define deleteOrderedIter deleteOrderedBiNode
    #define deleteRec deleteBiNodeRecursively
    #define deleteOrderedRec deleteOrderedBiNodeRecursively
    #define deleteAllIter deleteEntireBiList
    #define deleteAllRec deleteEntireBiListRecursively
    #define getCountIter getBiNodesCount
    #define getCountRec getBiNodesCountRecursively
#else
    #include "linked_list/unidirectional.h"
    typedef UniNode Node;

    #define displayList displayUniList
    #define listToString uniListToString
    #define addIter addUniNode
    #define addOrderedIter addOrderedUniNode
    #define addRec addUniNodeRecursively
    #define addOrderedRec addOrderedUniNodeRecursively
    #define findIter findUniNode
    #define findOrderedIter findOrderedUniNode
    #define findRec findUniNodeRecursively
    #define findOrderedRec findOrderedUniNodeRecusrively
    #define updateIter updateUniNode
    #define updateRec updateUniNodeRecursively
    #define deleteIter deleteUniNode
    #define deleteOrderedIter deleteOrderedUniNode
    #define deleteRec deleteUniNodeRecursively
    #define deleteOrderedRec deleteOrderedUniNodeRecursively
    #define deleteAllIter deleteEntireUniList
    #define deleteAllRec deleteEntireUniListRecursively
    #define getCountIter getUniNodesCount
    #define getCountRec getUniNodesCountRecursively
#endif

/**
 * @brief An enumeration of the list types that can be unordered and ordered.
 */
typedef enum LIST_TYPE{
    UNORDERED,
    ORDERED
} LIST_TYPE;

/**
 * @brief An enumeration of the operation types that can be add, find, delete,
 *        delete entire list, or update an element (allowed only in case of
 *        unordered list).
 */
typedef enum OPERATION_TYPE{
    ADD,
    FIND,
    DELETE,
    DELETE_ALL,
    UPDATE
} OPERATION_TYPE;

/**
 *  @brief Displays a general welcoming message.
 */
void displayWelcomeMessage();

/**
 * @brief Gets the list type selected by the user. It prompts the user to
 *        select a list type from the available options and returns the
 *        corresponding LIST_TYPE value.
 *
 * @return The LIST_TYPE value corresponding to the list type selected by the
 *         user.
 */
LIST_TYPE getListType();

/**
 * @brief Prompts the user to know whether recursive approach should be used or
 *        not.
 *
 * @return True if the user selects to use recursion and false otherwise.
 */
bool shouldUseRecursiveApproach();

/**
 *  @brief Displays the linked list content.
 *
 *  @param root Pointer to the root node of the linked list.
 *
 *  @param recursive If true, it will use recursive function to get list size.
 *                   Otherwise, it will use iterative approach to get the size.
 *
 */
void displayCurrentList(Node *root, bool recursive);

/**
 * @brief Gets the operation type selected by the user. It prompts the user to
 *        select an operation and returns the corresponding OPERATION_TYPE
 *        value.
 *
 * @param excludeUpdate If true, it will not present update operation as
 *                      possible choice (case of ordered list). Otherwise,
 *                      update will be presented.
 *
 * @return The OPERATION_TYPE value corresponding to the list operation type
 *         selected by the user.
 */
OPERATION_TYPE getOperationType(bool excludeUpdate);

/**
 * @brief Performs a list operation specified by the given operation type.
 *
 * @param root A pointer to the pointer to the root node of the linked list. It
 *             is expected to be different than NULL.
 *
 * @param listType The LIST_TYPE of the list indicating whether is unordered or
 *                 ordered.
 *
 * @param operationType The type of operation to perform on the linked list.
 *
 * @param recursive If true, recusrsive method will be used. Otherwise, it
 *                  utilizes iterative approach.
 *
 * @attention The value of root is assumed to be different than NULL. But it is
 *            fine if *root is NULL, which is the case when we have empty list.
 *            We also assume that if listType == ORDERED then operationType is
 *            different than UPDATE.
 */
void performListOperation(Node **root,
                          LIST_TYPE listType,
                          OPERATION_TYPE operationType,
                          bool recursive);

#endif
