/**
 * @file test_bst_and_avl.c
 *
 * @author Samah A. SHAYYA
 *
 * @brief This tests the functions related to unordered and ordered linked
 *        lists in "unidirectional.h" and "bidirectional.h". By default, it
 *        tests iterative unidirectional unordered methods. As for ordered,
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

#include <math.h>   // For log2 and ceil functions


#define UNITY_EXCLUDE_THREAD_SUPPORT
#include "unity.h"
#include "unity_fixture.h"

#include "tree/common.h"

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

    /**
     * @brief Tells if an AVL tree node is balanced or not.
     *
     * @param root Pointer to the root node of the AVL tree.
     *
     * @return True if balanced AVL tree (or if empty) and false otherwise.
     */
    bool isBalanced(Node *root) {
        bool balanced = true;
        if(root) {
            balanced = balanced && (abs(root->balanceFactor) <= 1);

            if(balanced) {
                balanced = isBalanced(root->left);
            }

            if(balanced) {
                balanced = isBalanced(root->right);
            }
        }

        return balanced;
    }
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
#endif

/**
 * @brief Returns a string containing numbers corresponding to passed list of
 *        nodes, where non-existing node is represented by "e" to maintain
 *        structural integrity.
 *
 * @param nodes Pointer to array of node pointers.
 *
 * @param numNodes The size / length of nodes array.
 *
 * @param numDigits The maximum number of digits needed to represent a node
 *                  value. It is used to estimate the string length.
 *
 * @attention The caller is responsible of freeing the char * pointer after
 *            using it.
 */
char *getLevelAsFormattedStr(Node **nodes, size_t numNodes, size_t numDigits) {
    char *str = NULL;
    if(nodes) {
        /**
         * len = numDigits * numNodes (numbers) + (numNodes - 1) (spaces) + 1
         * where we add the last 1 for null '\0' character.
         */
        size_t len = (numDigits + 1) * numNodes;
        str = malloc(len * sizeof(char));

        if(str) {
            // Successful allocation
            for(size_t i = 0; i < numNodes - 1; ++i) {
                if(nodes[i]) {
                    sprintf(str + strlen(str), "%d ", nodes[i]->value);
                }
                else {
                    // Empty node (NULL valued)
                    sprintf(str + strlen(str), "e ");
                }
            }

            size_t lastIndex = numNodes - 1;
            if(nodes[lastIndex]) {
                    sprintf(str + strlen(str), "%d", nodes[lastIndex]->value);
            }
            else {
                // Empty node (NULL valued)
                sprintf(str + strlen(str), "e");
            }
        }
    }

    return str;
}


// Global variable that will be set based on main arguments
bool recursive = false;

/**
 * We define function pointers to allow testing iterative and recursive
 * methods in case of binary trees (whether BST or AVL). It is good practice
 * to initialize function pointers with NULL.
 */
bool (*add)(Node **, int) = NULL;
Node *(*find)(Node *, int) = NULL;
bool (*deleteNode)(Node **, int) = NULL;

/**
 * @brief It is intended to be run once before all tests (just after
 *        UNITY_BEGIN()). It should be manually called as needed. There is no
 *        built-in Unity macro for such thing.
 */
void moduleSetUp() {
    // Choosing the proper functions iterative / recursive.
    if(recursive) {
        // Recursive approach
        add = addRec;
        find = findRec;
        deleteNode = deleteRec;
    }
    else {
        // Iterative approach
        add = addIter;
        find = findIter;
        deleteNode = deleteIter;
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
 * @brief Creates CombinedFunctions test case: unique items.
 */
TEST(CombinedFunctions, test_unique_items) {
    Node *root = NULL, **nodes_1 = NULL, **prevNodes = NULL, **nodes_2 = NULL;
    char *str_1 = NULL, *str_2 = NULL;
    int nums[] = {8, 3, 10, 5, 1, 12, 7, 9, 2, 6};
    size_t len = sizeof(nums) / sizeof(int);

    for(size_t i = 0; i < len; ++i) {
        TEST_ASSERT_TRUE(add(&root, nums[i]));
        TEST_ASSERT_EQUAL(i + 1, getCount(root));

        #ifdef AVL
            // Assuring that the AVL tree remains balanced at all times.
            TEST_ASSERT_TRUE(isBalanced(root));
        #endif
    }

    // Checking the exact structure
    int minValue, maxValue;

    // Testing minTree
    TEST_ASSERT_TRUE(minTree(root, &minValue));
    TEST_ASSERT_EQUAL(1, minValue);

    // Testing maxTree
    TEST_ASSERT_TRUE(maxTree(root, &maxValue));
    TEST_ASSERT_EQUAL(12, maxValue);

    size_t height = getHeight(root);
    size_t maxNumDigits = getMaxNumberOfDigitsNeeded(minValue, maxValue);

    #ifdef AVL
        // TODO: Case of AVL tree

    #else
        char levelStrs[][32] = {"8",
                                "3 10",
                                "1 5 9 12",
                                "e 2 e 7 e e e e",
                                "e e e e e e 6 e e e e e e e e e"};

        for(size_t level = 0; level < height; ++level) {
            nodes_1 = getLevelNodes(root, height, level);
            str_1 = getLevelAsFormattedStr(nodes_1, 1 << level, maxNumDigits);

            nodes_2 = getLevelNodesWithPrefeed(root, height, level, prevNodes);
            str_2 = getLevelAsFormattedStr(nodes_2, 1 << level, maxNumDigits);

            prevNodes = nodes_2;

            TEST_ASSERT_EQUAL_STRING(levelStrs[level], str_1);
            TEST_ASSERT_EQUAL_STRING(levelStrs[level], str_2);
        }
    #endif

    // Deleting entire tree
    deleteAll(&root);

    // Asserting deletion success
    TEST_ASSERT_EQUAL(NULL, root);
};

/**
 * @brief Creates CombinedFunctions test case: duplicate items.
 */
TEST(CombinedFunctions, test_duplicate_items) {
    Node *root = NULL;
    int nums[] = {8, 3, 10, 5, 1, 12, 7, 9, 2, 6, 8, 5};
    size_t len = sizeof(nums) / sizeof(int);

    for(size_t i = 0; i < len - 2; ++i) {
        TEST_ASSERT_TRUE(add(&root, nums[i]));
        TEST_ASSERT_EQUAL(i + 1, getCount(root));

        #ifdef AVL
        // Assuring that the AVL tree remains balanced at all times.
            TEST_ASSERT_TRUE(isBalanced(root));
        #endif
    }

    // Duplicates ok with BSTree and not with AVLTree.
    #ifdef AVL
        for(size_t i = len - 2; i < len; ++i) {
            TEST_ASSERT_FALSE(add(&root, nums[i]));
            TEST_ASSERT_EQUAL(len - 2, getCount(root));
            TEST_ASSERT_TRUE(isBalanced(root));
        }
    #else
        for(size_t i = len - 2; i < len; ++i) {
            TEST_ASSERT_TRUE(add(&root, nums[i]));
            TEST_ASSERT_EQUAL(i + 1, getCount(root));
        }
    #endif

    // Deleting entire tree
    deleteAll(&root);

    // Asserting deletion success
    TEST_ASSERT_EQUAL(NULL, root);
};

/**
 * @brief Creates CombinedFunctions test case: one-by-one deletion.
 */
TEST(CombinedFunctions, test_one_by_one_deletion) {
    Node *root = NULL;
    int nums[] = {8, 3, 10, 5, 1, 12, 7, 9, 2, 6, 8, 5};
    size_t len = sizeof(nums) / sizeof(int);

    for(size_t i = 0; i < len; ++i) {
        TEST_ASSERT_TRUE(add(&root, nums[i]));
        TEST_ASSERT_EQUAL(i + 1, getCount(root));

        #ifdef AVL
        // Assuring that the AVL tree remains balanced at all times.
            TEST_ASSERT_TRUE(isBalanced(root));
        #endif
    }

    // Attempting to delete non-existing item
    TEST_ASSERT_FALSE(deleteNode(&root, 11));

    // Testing find with non-existing element
    TEST_ASSERT_EQUAL(NULL, find(root, -55));

    for(size_t j = 0; j < len; ++j) {
        TEST_ASSERT_TRUE(find(root, nums[j]) != NULL);
        TEST_ASSERT_TRUE(deleteNode(&root, nums[j]));
        TEST_ASSERT_EQUAL(len - j - 1, getCount(root));

        #ifdef AVL
            // Assuring that the AVL tree remains balanced at all times.
            TEST_ASSERT_TRUE(isBalanced(root));
        #endif
    }

    /**
     * Here no need to deleteEntire as if successful, all elements are deleted.
     * We just assert root being NULL.
     */
    TEST_ASSERT_EQUAL(NULL, root);
}

/**
 * @brief Creates CombinedFunctions test case: for AVL tree balancing.
 */
TEST(CombinedFunctions, test_avl_balancing) {
    #ifdef AVL
        Node *root = NULL;
        int nums[][10] = {
            // Sorted in ascending order ==> right-skewed ==> left rotations
            {10, 20, 30, 40, 50, 60, 70, 80, 90, 100},

            // Sorted in descending order ==> left-skewed ==> right rotations
            {100, 90, 80, 70, 60, 50, 40, 30, 20, 10},

            /**
             * Others in which various types of rotations would be required for
             * balancing:
             */
            {50, 30, 70, 20, 40, 60, 80, 10, 90, 100},
            {5, 4, 3, 2, 1, 6, 7, 8, 9, 10},
            {50, 40, 60, 30, 45, 55, 70, 20, 35, 25},
            {10, 5, 15, 3, 7, 12, 20, 2, 4, 6}
        };

        size_t numRows = sizeof(nums) / sizeof(int[10]);

        for(size_t row = 0; row < numRows; ++row) {
            for(size_t i = 0; i < 10; ++i) {
                TEST_ASSERT_TRUE(add(&root, nums[row][i]));
                TEST_ASSERT_EQUAL(i + 1, getCount(root));

                // Assuring that the AVL tree remains balanced at all times.
                TEST_ASSERT_TRUE(isBalanced(root));
            }

            // Attempting to delete non-existing item
            TEST_ASSERT_FALSE(deleteNode(&root, 11));

            // Testing find with non-existing element
            TEST_ASSERT_EQUAL(NULL, find(root, -55));

            for(size_t j = 0; j < 10; ++j) {
                TEST_ASSERT_TRUE(find(root, nums[row][j]) != NULL);
                TEST_ASSERT_TRUE(deleteNode(&root, nums[row][j]));
                TEST_ASSERT_EQUAL(10 - j - 1, getCount(root));

                // Assuring that the AVL tree remains balanced at all times.
                TEST_ASSERT_TRUE(isBalanced(root));
            }

            /**
             * Here no need to deleteEntire as if successful, all elements are
             * deleted. We just assert root being NULL.
             */
            TEST_ASSERT_EQUAL(NULL, root);
        }
    #else
        TEST_IGNORE_MESSAGE("Tree balancing test is skipped as we have BST!");
    #endif
}

/**
 * @brief Creates CombinedFunctions test case: testing nodeToStr.
 */
TEST(CombinedFunctions, test_nodeToStr) {
    Node *root = NULL;
    char *str = NULL;
    int nums[] = {8, 3, 5, 1, 7, 9, 2, 6, 8, 5};
    size_t len = sizeof(nums) / sizeof(int);

    // Empty tree
    str = nodeToStr(root);
    TEST_ASSERT_EQUAL_STRING("< >", str);

    // Testing single item
    TEST_ASSERT_TRUE(add(&root, nums[0]));
    TEST_ASSERT_EQUAL(1, getCount(root));

    str = nodeToStr(root);
    TEST_ASSERT_EQUAL_STRING("< 8 >", str);

    for(size_t i = 1; i < len; ++i) {
        add(&root, nums[i]);

        #ifdef AVL
            // Assuring that the AVL tree remains balanced at all times.
            TEST_ASSERT_TRUE(isBalanced(root));
        #endif
    }

    // Testing several elements
    str = nodeToStr(root);

    #ifdef AVL
        // No duplicates are allowed.
        TEST_ASSERT_EQUAL_STRING("< 1 | 2 | 3 | 5 | 6 | 7 | 8 | 9 >", str);
    #else
        TEST_ASSERT_EQUAL_STRING("< 1 | 2 | 3 | 5 | 5 | 6 | 7 | 8 | 8 | 9 >", str);
    #endif

    // Deleting entire tree
    deleteAll(&root);

    str = nodeToStr(root);
    TEST_ASSERT_EQUAL_STRING("< >", str);

    // Asserting deletion success
    TEST_ASSERT_EQUAL(NULL, root);
};

 /**
 * @brief Creates ConcatenateFunction test group runner.
 */
TEST_GROUP_RUNNER(CombinedFunctions) {
    // Adding all test cases
    RUN_TEST_CASE(CombinedFunctions, test_unique_items);
    RUN_TEST_CASE(CombinedFunctions, test_duplicate_items);
    RUN_TEST_CASE(CombinedFunctions, test_one_by_one_deletion);
    RUN_TEST_CASE(CombinedFunctions, test_avl_balancing);
    RUN_TEST_CASE(CombinedFunctions, test_nodeToStr);
};

int main(int argc, char *args[]) {
    /**
     * Consuming "--recursive" argument if passed
    */
    if(argc > 2) {
        // Printing to standard error (square brackets enclose optional args)
        fprintf(stderr, "Usage: %s [--recursive]\n", args[0]);

        // Exist with an error
        exit(1);
    }
    else {
        if(argc == 2 && strcasecmp(args[1], "--recursive") == 0) {
            recursive = true;
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
