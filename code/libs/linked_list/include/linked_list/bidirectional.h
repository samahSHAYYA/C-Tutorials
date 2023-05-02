/**
 * @file bidirectional.h
 *
 * @author Samah A. SHAYYA
 *
 * @brief This file contains the data structure and functions associated with
 *        bidirectional linked lists, embracing both unordered and ordered
 *        versions.
 */

#ifndef BIDIRECTIONAL_H
#define BIDIRECTIONAL_H

#include <stdbool.h>
#include <stddef.h>

// Task 1: Data Structure Declaration and Textual Description
/**
 * @struct BiNode
 *
 * @brief A bidirectional / doubly linked list node.
 */
typedef struct BiNode {
    /**
     * @brief The value stored in the node. It can be of any type.
     *        In case of ordered list, the type should be comparable.
     */
    int value;

    /**
     * @brief Pointer to the previous node in the list.
     */
    struct BiNode *prev;

    /**
     * @brief Pointer to the next node in the list.
     */
    struct BiNode *next;
} BiNode;

/**
 * @brief Displays the elements of a biidirectional / doubly linked list
 *        starting from the given root node.
 *
 * @param root The root node pointer of the linked list.
 *
 */
void displayBiList(BiNode *root);

/**
 * @brief Converts a bidirectional / doubly linked list to a string
 *        representation.
 *
 * @param root Pointer to the root node of the list.
 *
 * @return A string representation of the list.
 */
char *biListToString(BiNode *root);

// Task 2: Creation Operation
/**
 * @brief Adds a new node with the specified value to the end of the
 *        bidirectional linked list.
 *
 * @param root Pointer to a pointer to the first node of the list. If the list
 *             is empty, *root should be NULL. The value of root should not
 *             be NULL. Otherwise, nothing is done.
 *
 * @param value Value to be stored in the new node.
 *
 * @return True if the node was added successfully and false otherwise.
*/
bool addBiNode(BiNode **root, int value);

/**
 * @brief Recursively adds a new node with the specified value to the end of the
 *        bidirectional linked list.
 *
 * @param root Pointer to a pointer to the first node of the list. If the list
 *             is empty, *root should be NULL. The value of root should not
 *             be NULL. Otherwise, nothing is done.
 *
 * @param value Value to be stored in the new node.
 *
 * @return True if the node was added successfully and false otherwise.
*/
bool addBiNodeRecursively(BiNode **root, int value);

// Task 3: Read / Find Operations
/**
 * @brief Finds the first node with specified value in the given bidirectional
 *        list.
 *
 * @param root Pointer to the root node of the  bidirectional list to search.
 *
 * @param value The value to search for.
 *
 * @return A pointer to the first node found with the specified value, or NULL
 *         in case of non-existing value.
 */
BiNode *findBiNode(BiNode *root, int value);

/**
 * @brief Finds recursively the first node with specified value in the given
 *        bidirectional list.
 *
 * @param root Pointer to the root node of the bidirectional list to search.
 *
 * @param value The value to search for.
 *
 * @return A pointer to the first node found with the specified value, or NULL
 *         in case of non-existing value.
 */
BiNode *findBiNodeRecursively(BiNode *root, int value);

// Task 4: Update Operation
/**
 * @brief Updates the value of the first node with the given original value.
 *
 * @param root Pointer to the root node of the bidirectional list to update.
 *
 * @param originalValue The original value to search for.
 *
 * @param newValue The new value to set for the first found node.
 *
 * @return True if a node is found and updated and false otherwise.
 */
bool updateBiNode(BiNode *root, int originalValue, int newValue);

/**
 * @brief Updates the value of the first node with the given original value. It
 *        is based on recursive approach.
 *
 * @param root Pointer to the root node of the bidirectional list to update.
 *
 * @param originalValue The original value to search for.
 *
 * @param newValue The new value to set for the first found node.
 *
 * @return True if a node is found and updated and false otherwise.
 */
bool updateBiNodeRecursively(BiNode *root, int originalValue, int newValue);

// Task 5: Delete Operation
/**
 * @brief Deletes the first node with the specified value from the given
 *        bidirectional list.
 *
 * @param root A pointer to the root node of the bidirectional list to search.
 *
 * @param value The value to search for and delete.
 *
 * @return True if a node is found and deleted and false otherwise.
 */
bool deleteBiNode(BiNode **root, int value);

/**
 * @brief Deletes the first node with the specified value from the given
 *        bidirectional list. It is based on recursion.
 *
 * @param root A pointer to the root node of the bidirectional list to search.
 *
 * @param value The value to search for and delete.
 *
 * @return True if a node is found and deleted and false otherwise.
 */
bool deleteBiNodeRecursively(BiNode **root, int value);

// Task 6: Delete Entire List
/**
 * @brief Deletes the bidirectional list starting from the given root node.
 *
 * @param root A pointer to a pointer to the root node of the list to delete
 *             entirely.
 */
void deleteEntireBiList(BiNode **root);

/**
 * @brief Deletes the bidirectional list starting from the given root node. It
 *        is based on recursion.
 *
 * @param root A pointer to a pointer to the root node of the list to delete
 *             entirely.
 */
void deleteEntireBiListRecursively(BiNode **root);

// Task 7: Getting List Length / BiNodes Count
/**
 * @brief Counts the number of nodes in the given bidirectional list.
 *
 * @param root A pointer to the root node of the bidirectional list to count.
 *
 * @return The total number of nodes in the list.
 */
size_t getBiNodesCount(BiNode *root);

/**
 * @brief Counts the number of nodes in the given bidirectional list. It is
 *        based on recursion.
 *
 * @param root A pointer to the root node of the bidirectional list to count.
 *
 * @return The total number of nodes in the list.
 */
size_t getBiNodesCountRecursively(BiNode *root);

// Task 8: Ordered Bidirectional List
/**
 * @brief Adds a new node with the specified value to the given bidirectional
 *        list in ascending order.
 *
 * @param root A pointer to a pointer to the root node of the bidirectional
 *             list to add to.
 *
 * @param value The value to add to the bidirectional list.
 *
 * @return True if a new node is added to the list and false otherwise.
 */
bool addOrderedBiNode(BiNode **root, int value);

/**
 * @brief Adds a new node with the specified value to the given bidirectional
 *        list in ascending order. It utilizes recursion.
 *
 * @param root A pointer to a pointer to the root node of the bidirectional
 *             list to add to.
 *
 * @param value The value to add to the bidirectional list.
 *
 * @return True if a new node is added to the list and false otherwise.
 */
bool addOrderedBiNodeRecursively(BiNode **root, int value);

/**
 * @brief Finds the node with the specified value in an ordered bidirectional
 *        list.
 *
 * @param root A pointer to the root node of the ordered bidirectional list to
 *             search.
 *
 * @param value The value to search for in the bidirectional list.
 *
 * @return A pointer to the node that contains the specified value, or NULL if
 *         the value does not exist.
 */
BiNode *findOrderedBiNode(BiNode *root, int value);

/**
 * @brief Finds the node with the specified value in an ordered bidirectional
 *        list. It is based on recursion.
 *
 * @param root A pointer to the root node of the ordered bidirectional list to
 *             search.
 *
 * @param value The value to search for in the bidirectional list.
 *
 * @return A pointer to the node that contains the specified value, or NULL if
 *         the value does not exist.
 */
BiNode *findOrderedBiNodeRecusrively(BiNode *root, int value);

/**
 * @brief Deletes the node with the specified value from an ordered
 *        bidirectional list.
 *
 * @param root A pointer to a pointer to the root node of the ordered
 *             bidirectional list to delete from.
 *
 * @param value The value to delete from the bidirectional list.
 *
 * @return True if a node with the specified value is found and deleted from
 *         the list and false otherwise.
 */
bool deleteOrderedBiNode(BiNode **root, int value);

/**
 * @brief Deletes the node with the specified value from an ordered
 *        bidirectional list. It is based on recursion.
 *
 * @param root A pointer to a pointer to the root node of the ordered
 *             bidirectional list to delete from.
 *
 * @param value The value to delete from the bidirectional list.
 *
 * @return True if a node with the specified value is found and deleted from
 *         the list and false otherwise.
 */
bool deleteOrderedBiNodeRecursively(BiNode **root, int value);

#endif
