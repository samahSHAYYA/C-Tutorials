/**
 * @file test_unidirectional_and_bidirectional.c
 *
 * @author Samah A. SHAYYA
 *
 * @brief This tests the functions related to unordered and ordered linked
 *        lists in "unidirectional.h" and "bidirectional.h". By default, it
 *        tests iterative undidirectional unordered methods. As for ordered,
 *        recursive, and bidirectional lists, a corresponding option should be
 *        passed.
 */

#include <stdio.h>
#include <string.h>

/**
 * REMARK:
 *
 * Note that on Windows, we have strcmpi for case-insensitive comparison.
 * However, on Linux, we have strcasecmp, which is part of strings.h.
 * In what follows, we use preprocessor commands to deal with such situation.
*/
#ifdef _WIN32
    /**
     * REMARK:
     *
     * Windows platform: Note that _stricmp is present in string.h which is
     * already included.
     */
    #define strcasecmp _stricmp
#else
    #include <strings.h>
#endif

#define UNITY_EXCLUDE_THREAD_SUPPORT
#include "unity.h"
#include "unity_fixture.h"

/**
 * REMARK:
 *
 * Note that in the code below, there is no updateOrdered<...>, as it does not
 * make sense in the case ordered linked list. In ordered list, there is no
 * update of a node but we delete an existing one and add a new node with the
 * new value.
 */
#ifdef BIDIRECTIONAL
    #include "linked_list/bidirectional.h"

    typedef BiNode Node;

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

// Global variables that will be set based on main arguments
bool ordered = false;
bool recursive = false;

/**
 * We define function pointers to allow testing iterative and recursive
 * methods in case of unordered and ordered linked list. It is good practice
 * to initialize function pointers with NULL.
 */
bool (*add)(Node **, int) = NULL;
Node *(*find)(Node *, int) = NULL;
bool (*update)(Node *, int, int) = NULL;
bool (*deleteNode)(Node **, int) = NULL;
void (*deleteAll)(Node **) = NULL;
size_t (*getCount)(Node *) = NULL;

/**
 * @brief It is intended to be run once before all tests (just after
 *        UNITY_BEGIN()). It should be manually called as needed. There is no
 *        built-in Unity macro for such thing.
 */
void moduleSetUp() {
    // Choosing the proper functions iterative / recursive.
    if(recursive) {
        // Recursive approach
        if(ordered) {
            // For setting a function pointer, the & is not needed.
            add = addOrderedRec;
            find = findOrderedRec;
            deleteNode = deleteOrderedRec;
            // update is not useful in case of ordered list
        }
        else {
            // Unordered list with recursive
            add = addRec;
            find = findRec;
            update = updateRec;
            deleteNode = deleteRec;
        }

        // These are the same regardless of being unordered or ordered list
        deleteAll = deleteAllRec;
        getCount = getCountRec;
    }
    else {
        // Iterative approach
        if (ordered) {
            add = addOrderedIter;
            find = findOrderedIter;
            deleteNode = deleteOrderedIter;
            // update is not useful in case of ordered list
        }
        else {
            // Unordered
            add = addIter;
            find = findIter;
            update = updateIter;
            deleteNode = deleteIter;
        }

        // These are the same regardless of being unordered or ordered list
        deleteAll = deleteAllIter;
        getCount = getCountIter;
    }
}

/**
 * @brief Creates CombinedFunctions test group.
 */
TEST_GROUP(CombinedFunctions);

/**
 * @brief Creates CombinedFunctions group setup that run prior to every test.
 */
TEST_SETUP(CombinedFunctions) {
    // Add any test setup code here or keep empty (it runs before each test)
};

/**
 * @brief Creates CombinedFunctions group teardown that run after every test.
 */
TEST_TEAR_DOWN(CombinedFunctions) {
    // Add any test setup code here or keep empty (it runs before each test)
};

/**
 * @brief Creates CombinedFunctions test case: test_emptyList.
 */
TEST(CombinedFunctions, test_emptyList) {
    Node *emptyListRoot = NULL;
    char *emptyListStr = NULL;

    emptyListStr = listToString(emptyListRoot);
    TEST_ASSERT_EQUAL_STRING("< >", emptyListStr);
};

/**
 * @brief Creates CombinedFunctions test case: test_singleElementList.
 */
TEST(CombinedFunctions, test_singleElementList) {
    Node *singleElementListRoot = NULL;
    char *singleElementListStr = NULL;

    TEST_ASSERT_TRUE(add(&singleElementListRoot, 1));

    singleElementListStr = listToString(singleElementListRoot);

    TEST_ASSERT_EQUAL_STRING("< 1 >", singleElementListStr);

    deleteAll(&singleElementListRoot);
};

/**
 * @brief Creates CombinedFunctions test case: test_doubleElementList.
 */
TEST(CombinedFunctions, test_doubleElementList) {
    Node *doubleElementListRoot = NULL;
    char *doubleElementListStr = NULL;

    TEST_ASSERT_TRUE(add(&doubleElementListRoot, 1));
    TEST_ASSERT_TRUE(add(&doubleElementListRoot, -2));

    doubleElementListStr = listToString(doubleElementListRoot);

    if(ordered) {
        // It should be in ascending order
        TEST_ASSERT_EQUAL_STRING("< -2 | 1 >", doubleElementListStr);
    }
    else {
        // Unordered list (they should be displayed as they have been added)
        TEST_ASSERT_EQUAL_STRING("< 1 | -2 >", doubleElementListStr);
    }

    deleteAll(&doubleElementListRoot);
}

/**
 * @brief Creates CombinedFunctions test case: test_severalElementList.
 */
TEST(CombinedFunctions, test_severalElementList) {
    Node *severalElementListRoot = NULL;
    char *severalElementListStr = NULL;

    TEST_ASSERT_TRUE(add(&severalElementListRoot, 1));
    TEST_ASSERT_TRUE(add(&severalElementListRoot, -2));
    TEST_ASSERT_TRUE(add(&severalElementListRoot, 3));
    TEST_ASSERT_TRUE(add(&severalElementListRoot, -4));
    TEST_ASSERT_TRUE(add(&severalElementListRoot, -6));
    TEST_ASSERT_TRUE(add(&severalElementListRoot, 7));
    TEST_ASSERT_TRUE(add(&severalElementListRoot, 1));
    TEST_ASSERT_TRUE(add(&severalElementListRoot, -2));
    TEST_ASSERT_TRUE(add(&severalElementListRoot, -2));

    severalElementListStr = listToString(severalElementListRoot);

    if(ordered) {
        TEST_ASSERT_EQUAL_STRING("< -6 | -4 | -2 | -2 | -2 | 1 | 1 | 3 | 7 >",
                                 severalElementListStr);
    }
    else {
        TEST_ASSERT_EQUAL_STRING("< 1 | -2 | 3 | -4 | -6 | 7 | 1 | -2 | -2 >",
                                 severalElementListStr);
    }

    deleteAll(&severalElementListRoot);
};

/**
 * @brief Creates CombinedFunctions test case: test_find.
 */
TEST(CombinedFunctions, test_find) {
    Node *findListRoot = NULL;

    int elements[] = {1, -2, 3, -4, 5, -6, 7, 1, -2, -2};
    size_t length = sizeof(elements) / sizeof(int);

    int i = 0;
    for(i = 0; i < length; ++i) {
        TEST_ASSERT_TRUE(add(&findListRoot, elements[i]));
    }

    /**
     * For existing elements, find should return a pointer that is not NULL
     * evaluating to true.
     */
    for(i = 0; i < length; ++i) {
        TEST_ASSERT_TRUE(find(findListRoot, elements[i]));
    }

    /**
     * For non-existing elements, find should return{ NULL pointer evaluating
     * to false.
    */
    for(i = 10; i < 20; ++i) {
        TEST_ASSERT_FALSE(find(findListRoot, i));
        TEST_ASSERT_FALSE(find(findListRoot, -i));
    }

    // Cleaning up
    deleteAll(&findListRoot);
};

/**
 * @brief Creates CombinedFunctions test case: test_update.
 */
TEST(CombinedFunctions, test_update) {
    /**
     * This test is meaningful in the case of unordered linked list. In case of
     * ordered list, it is not used and have no sense. In such a case it should
     * be ignored.
     */
    Node *updateListRoot = NULL;

    if(ordered) {
        // Case of ordered linked list
        TEST_IGNORE_MESSAGE("Skipping update test having ordered list!");
    }

    // Reached here implies working with unordered linked list
    int elements[] = {1, -2, 3, -4, 5, -6, 7, 1, -2, -2};
    size_t length = sizeof(elements) / sizeof(int);

    int i = 0;
    for(i = 0; i < length; ++i) {
        TEST_ASSERT_TRUE(add(&updateListRoot, elements[i]));
    }

    /**
     * Updating the nodes containing -2 values into 0. The update should return
     * trye three times before returning false.
    */
    for(i = 0; i < 3; ++i) {
        TEST_ASSERT_TRUE(update(updateListRoot, -2, 0));
    }

    TEST_ASSERT_FALSE(update(updateListRoot, -2, 0));

    /**
     * Updating all nodes with 1 into 0 values. It should return true twice and
     * false afterwards.
    */
    for(i = 0; i < 2; ++i) {
        TEST_ASSERT_TRUE(update(updateListRoot, 1, 0));
    }

    TEST_ASSERT_FALSE(update(updateListRoot, 1, 0));

    /**
     * Updating all nodes with 3 into 0 values. It should return true once and
     * false afterwards.
    */
    TEST_ASSERT_TRUE(update(updateListRoot,3 , 0));
    TEST_ASSERT_FALSE(update(updateListRoot, 3, 0));

    /**
     * Updating all nodes with 5 into 0 values. It should return true once and
     * false afterwards.
    */
    TEST_ASSERT_TRUE(update(updateListRoot, 5, 0));
    TEST_ASSERT_FALSE(update(updateListRoot, 5, 0));

    /**
     * Updating all nodes with -4 into 0 values. It should return true once and
     * false afterwards.
    */
    TEST_ASSERT_TRUE(update(updateListRoot, -4, 0));
    TEST_ASSERT_FALSE(update(updateListRoot, -4, 0));

    /**
     * Updating all nodes with 6 into 0 values. It should return true once and
     * false afterwards.
    */
    TEST_ASSERT_TRUE(update(updateListRoot, -6, 0));
    TEST_ASSERT_FALSE(update(updateListRoot, -6, 0));

    /**
     * Updating all nodes with 7 into 0 values. It should return true once and
     * false afterwards.
    */
    TEST_ASSERT_TRUE(update(updateListRoot, 7, 0));
    TEST_ASSERT_FALSE(update(updateListRoot, 7, 0));

    // Cleaning up
    deleteAll(&updateListRoot);
};

/**
 * @brief Creates CombinedFunctions test case: test_delete_and_count.
 */
TEST(CombinedFunctions, test_delete_and_count) {
    Node *deleteListRoot = NULL;

    int elements[] = {1, -2, 3, -4, 5, -6, 7, 1, -2, -2};
    size_t length = sizeof(elements) / sizeof(int);

    size_t i = 0;
    for(i = 0; i < length; ++i) {
        TEST_ASSERT_TRUE(add(&deleteListRoot, elements[i]));
        TEST_ASSERT_EQUAL(i + 1, getCount(deleteListRoot));
    }

    /**
     * Deletion of non-existing elements should return false and getCount
     * should not change.
    */
    for (i = 10; i < 20; ++i) {
        TEST_ASSERT_FALSE(deleteNode(&deleteListRoot, i));
        TEST_ASSERT_FALSE(deleteNode(&deleteListRoot, -i));
        TEST_ASSERT_EQUAL(length, getCount(deleteListRoot));
    }

    /**
     * We will delete existing elements starting with odd indices then even
     * indices and check that count decreases until zero.
     *
     * Note it is important to assure length and deletedCount are of same type,
     * here being size_t.
    */
    size_t deletedCount = 0;
    for(i = 1; i < length; i += 2) {
        TEST_ASSERT_TRUE(deleteNode(&deleteListRoot, elements[i]));
        TEST_ASSERT_EQUAL(length - (++deletedCount), getCount(deleteListRoot));
    }

    for(i = 0; i < length; i += 2) {
        TEST_ASSERT_TRUE(deleteNode(&deleteListRoot, elements[i]));
        TEST_ASSERT_EQUAL(length - (++deletedCount), getCount(deleteListRoot));
    }

    // Cleaning up
    deleteAll(&deleteListRoot);
};

 /**
 * @brief Creates ConcatenateFunction test group runner.
 */
TEST_GROUP_RUNNER(CombinedFunctions) {
    // Adding all test cases
    RUN_TEST_CASE(CombinedFunctions, test_emptyList);
    RUN_TEST_CASE(CombinedFunctions, test_singleElementList);
    RUN_TEST_CASE(CombinedFunctions, test_doubleElementList);
    RUN_TEST_CASE(CombinedFunctions, test_severalElementList);
    RUN_TEST_CASE(CombinedFunctions, test_find);
    RUN_TEST_CASE(CombinedFunctions, test_update);
    RUN_TEST_CASE(CombinedFunctions, test_delete_and_count);
};

int main(int argc, char *args[]) {
    /**
     * Consuming arguments including "--ordered" and "--recursive" if passed
    */
    if(argc > 3) {
        // Printing to standard error (square brackets enclose optional args)
        fprintf(stderr, "Usage: %s [--ordered] [--recursive]\n", args[0]);

        // Exist with an error
        exit(1);
    }
    else {
        for(int i = 1; i < argc; ++i) {
            // strcasecmp: performs case-insensitive string comparison
            if(strcasecmp(args[i], "--ordered") == 0) {
                if(!ordered) {
                    // First-time argument encounter
                    ordered = true;
                }
                else {
                    // Printing error and exitting
                    fprintf(stderr, "Arg --ordered was used more than once!");
                    exit(1);
                }
            }

            if(strcasecmp(args[i], "--recursive") == 0) {
                if(!recursive) {
                    // First-time argument encounter
                    recursive = true;
                }
                else {
                    // Printing error and exiting
                    fprintf(stderr, "Arg --recursive was used more than once!");
                    exit(1);
                }
            }
        }
    }

    // Start testing
    UNITY_BEGIN();

    // Running moduleSetUp to properly set the different function pointers
    moduleSetUp();

    // Running the CombinedFunctions group tests
    RUN_TEST_GROUP(CombinedFunctions);

    // End testing
    UNITY_END();

    return 0;
}
