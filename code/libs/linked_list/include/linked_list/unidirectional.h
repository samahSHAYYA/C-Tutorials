/**
 * @file unidirectional.h
 *
 * @author Samah A. SHAYYA
 *
 * @brief This file contains the data structure and functions associated with
 *        unidirectional linked lists, embracing both unordered and ordered
 *        versions.
 */

#ifndef UNIDIRECTIONAL_H
#define UNIDIRECTIONAL_H

#include <stdbool.h>
#include <stddef.h>

// Task 1: Data Structure Declaration and Textual Description
/**
 * @struct UniNode
 *
 * @brief A unidirectional / singly linked list node.
 */
typedef struct UniNode {
    /**
     * @brief The value stored in the node. It can be of any type.
     *        In case of ordered list, the type should be comparable.
     */
    int value;

    /**
     * @brief Pointer to the next node in the list.
     */
    struct UniNode *next;
} UniNode;


/**
 * @brief Displays the elements of a unidirectional / singly linked list
 *        starting from the given root node.
 *
 * @param root The root node pointer of the linked list.
 */
void displayUniList(UniNode *root);

/**
 * @brief Converts a unidirectional / singly linked list to a string
 *        representation.
 *
 * @param root Pointer to the root node of the list.
 *
 * @return A string representation of the list.
 */
char *uniListToString(UniNode *root);

// Task 2: Creation Operation
/**
 * @brief Adds a new node with the specified value to the end of the
 *        unidirectional linked list.
 *
 * @param root Pointer to a pointer to the first node of the list. If the list
 *             is empty, *root should be NULL. The value of root should not
 *             be NULL. Otherwise, nothing is done.
 *
 * @param value Value to be stored in the new node.
 *
 * @return True if the node was added successfully and false otherwise.
*/
bool addUniNode(UniNode **root, int value);

/**
 * @brief Recursively adds a new node with the specified value to the end of the
 *        unidirectional linked list.
 *
 * @param root Pointer to a pointer to the first node of the list. If the list
 *             is empty, *root should be NULL. The value of root should not
 *             be NULL. Otherwise, nothing is done.
 *
 * @param value Value to be stored in the new node.
 *
 * @return True if the node was added successfully and false otherwise.
*/
bool addUniNodeRecursively(UniNode **root, int value);

// Task 3: Read / Find Operations
/**
 * @brief Finds the first node with specified value in the given unidirectional
 *        list.
 *
 * @param root Pointer to the root node of the unidirectional list to search.
 *
 * @param value The value to search for.
 *
 * @return A pointer to the first node found with the specified value, or NULL
 *         in case of non-existing value.
 */
UniNode *findUniNode(UniNode *root, int value);

/**
 * @brief Finds recursively the first node with specified value in the given
 *        unidirectional list.
 *
 * @param root Pointer to the root node of the unidirectional list to search.
 *
 * @param value The value to search for.
 *
 * @return A pointer to the first node found with the specified value, or NULL
 *         in case of non-existing value.
 */
UniNode *findUniNodeRecursively(UniNode *root, int value);

// Task 4: Update Operation
/**
 * @brief Updates the value of the first node with the given original value.
 *
 * @param root Pointer to the root node of the unidirectional list to update.
 *
 * @param originalValue The original value to search for.
 *
 * @param newValue The new value to set for the first found node.
 *
 * @return True if a node is found and updated and false otherwise.
 */
bool updateUniNode(UniNode *root, int originalValue, int newValue);

/**
 * @brief Updates the value of the first node with the given original value. It
 *        is based on recursive approach.
 *
 * @param root Pointer to the root node of the unidirectional list to update.
 *
 * @param originalValue The original value to search for.
 *
 * @param newValue The new value to set for the first found node.
 *
 * @return True if a node is found and updated and false otherwise.
 */
bool updateUniNodeRecursively(UniNode *root, int originalValue, int newValue);

// Task 5: Delete Operation
/**
 * @brief Deletes the first node with the specified value from the given
 *        unidirectional list.
 *
 * @param root A pointer to the root node of the unidirectional list to search.
 *
 * @param value The value to search for and delete.
 *
 * @return True if a node is found and deleted and false otherwise.
 */
bool deleteUniNode(UniNode **root, int value);

/**
 * @brief Deletes the first node with the specified value from the given
 *        unidirectional list. It is based on recursion.
 *
 * @param root A pointer to the root node of the unidirectional list to search.
 *
 * @param value The value to search for and delete.
 *
 * @return True if a node is found and deleted and false otherwise.
 */
bool deleteUniNodeRecursively(UniNode **root, int value);

// Task 6: Delete Entire List
/**
 * @brief Deletes the unidirectional list starting from the given root node.
 *
 * @param root A pointer to a pointer to the root node of the list to delete
 *             entirely.
 */
void deleteEntireUniList(UniNode **root);

/**
 * @brief Deletes the unidirectional list starting from the given root node. It
 *        is based on recursion.
 *
 * @param root A pointer to a pointer to the root node of the list to delete
 *             entirely.
 */
void deleteEntireUniListRecursively(UniNode **root);

// Task 7: Getting List Length / UniNodes Count
/**
 * @brief Counts the number of nodes in the given unidirectional list.
 *
 * @param root A pointer to the root node of the unidirectional list to count.
 *
 * @return The total number of nodes in the list.
 */
size_t getUniNodesCount(UniNode *root);

/**
 * @brief Counts the number of nodes in the given unidirectional list. It is
 *        based on recursion.
 *
 * @param root A pointer to the root node of the unidirectional list to count.
 *
 * @return The total number of nodes in the list.
 */
size_t getUniNodesCountRecursively(UniNode *root);

// Task 8: Ordered Unidirectional List
/**
 * @brief Adds a new node with the specified value to the given unidirectional
 *        list in ascending order.
 *
 * @param root A pointer to a pointer to the root node of the unidirectional
 *             list to add to.
 *
 * @param value The value to add to the unidirectional list.
 *
 * @return True if a new node is added to the list and false otherwise.
 */
bool addOrderedUniNode(UniNode **root, int value);

/**
 * @brief Adds a new node with the specified value to the given unidirectional
 *        list in ascending order. It utilizes recursion.
 *
 * @param root A pointer to a pointer to the root node of the unidirectional
 *             list to add to.
 *
 * @param value The value to add to the unidirectional list.
 *
 * @return True if a new node is added to the list and false otherwise.
 */
bool addOrderedUniNodeRecursively(UniNode **root, int value);

/**
 * @brief Finds the node with the specified value in an ordered unidirectional
 *        list.
 *
 * @param root A pointer to the root node of the ordered unidirectional list to
 *             search.
 *
 * @param value The value to search for in the unidirectional list.
 *
 * @return A pointer to the node that contains the specified value, or NULL if
 *         the value does not exist.
 */
UniNode *findOrderedUniNode(UniNode *root, int value);

/**
 * @brief Finds the node with the specified value in an ordered unidirectional
 *        list. It is based on recursion.
 *
 * @param root A pointer to the root node of the ordered unidirectional list to
 *             search.
 *
 * @param value The value to search for in the unidirectional list.
 *
 * @return A pointer to the node that contains the specified value, or NULL if
 *         the value does not exist.
 */
UniNode *findOrderedUniNodeRecusrively(UniNode *root, int value);

/**
 * @brief Deletes the node with the specified value from an ordered
 *        unidirectional list.
 *
 * @param root A pointer to a pointer to the root node of the ordered
 *             unidirectional list to delete from.
 *
 * @param value The value to delete from the unidirectional list.
 *
 * @return True if a node with the specified value is found and deleted from
 *         the list and false otherwise.
 */
bool deleteOrderedUniNode(UniNode **root, int value);

/**
 * @brief Deletes the node with the specified value from an ordered
 *        unidirectional list. It is based on recursion.
 *
 * @param root A pointer to a pointer to the root node of the ordered
 *             unidirectional list to delete from.
 *
 * @param value The value to delete from the unidirectional list.
 *
 * @return True if a node with the specified value is found and deleted from
 *         the list and false otherwise.
 */
bool deleteOrderedUniNodeRecursively(UniNode **root, int value);

#endif
