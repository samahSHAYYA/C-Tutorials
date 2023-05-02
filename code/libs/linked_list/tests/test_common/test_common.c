/**
 * @file test_common.c
 *
 * @author Samah A. SHAYYA
 *
 * @brief This tests the functions in "common.h".
*/

#include <stdio.h>

#include "unity.h"
#include "unity_fixture.h"

#include "linked_list/common.h"

/**
 * @brief Creates InitializeFunction test group.
 */
TEST_GROUP(InitializeFunction);

/**
 * @brief Creates InitializeFunction test group setup, which is mandatory.
 */
TEST_SETUP(InitializeFunction) {
    // Add any test setup code here or keep empty (it runs before each test)
};

/**
 * @brief Creates InitializeFunction test group teardown, which is mandatory.
 */
TEST_TEAR_DOWN(InitializeFunction) {
    // Add any test setup code here or keep empty (it runs after each test)
};

/**
 * REMARK:
 *
 * Follow this test case naming convention:
 *
 * test_<function name as it is: camelCase>_<scenario: camelCase>
 */

/**
 * @brief Creates a test case for InitializeFunction group with the following
 *        name: test_initialize_withEmptyString.
 */
TEST(InitializeFunction, test_initialize_withEmptyString) {
    char *emptyStr = initialize("");

    TEST_ASSERT_EQUAL_STRING("", emptyStr);

    /**
     * REMARK:
     * Freeing emptyStr. Note that in case of above test failure, this won't
     * execute. One approach would be declare emptyStr as global variable and
     * define moduleTearDown function to deallocate non-null pointers (those
     * not freed by FREE_PTR, which sets them to NULL). Unfortunately, this did
     * not work as it generates free(): invalid pointer issue. I tried several
     * approaches to circumvent but failed.
     *
     * Another approach would be to inject Unity managment functions into the
     * tested code. This I have not tested and goes beyond the scope of this
     * tutorial.
     *
     * What I need to stress is that it is required to prevent memory leakage
     * and deallocate any manually allocated memory and assuring this works
     * even in case of test failure.
     *
     * Unity even finds issue with the line below:
     *      FREE_PTR(emptyStr).
     */
    // FREE_PTR(emptyStr);
}

/**
 * @brief Creates a test case for InitializeFunction group with the following
 *        name: test_initialize_withNonEmptyString.
 */
TEST(InitializeFunction, test_initialize_withNonEmptyString) {
    // Using a string literal
    const char *stringLiteral = "Hello World!!!";
    char *nonEmptyStr = initialize(stringLiteral);

    TEST_ASSERT_EQUAL_STRING(stringLiteral, nonEmptyStr);

    // FREE_PTR(nonEmptyStr);
}

/**
 * @brief Creates InitializeFunction test group runner.
 */
TEST_GROUP_RUNNER(InitializeFunction) {
    // Run all group test cases
    RUN_TEST_CASE(InitializeFunction, test_initialize_withEmptyString);
    RUN_TEST_CASE(InitializeFunction, test_initialize_withNonEmptyString);
}

/**
 * @brief Creates ConcatenateFunction test group.
 */
TEST_GROUP(ConcatenateFunction);

/**
 * @brief Creates ConcatenateFunction test group setup.
 */
TEST_SETUP(ConcatenateFunction) {
    // Add any test setup code here or keep empty (it runs before each test)
};

/**
 * @brief Creates ConcatenateFunction test group teardown.
 */
TEST_TEAR_DOWN(ConcatenateFunction) {
    // Add any test setup code here or keep empty (it runs after each test)
};

/**
 * @brief Creates ConcatenateFunction test case: test_concatenate_emptyStrings.
 */
TEST(ConcatenateFunction, test_concatenate_emptyStrings) {
    // Empty strings
    char *concatEmptyResult = concatenate("", "");

    TEST_ASSERT_EQUAL_STRING("", concatEmptyResult);

    // FREE_PTR(concatEmptyResult);
}

/**
 * @brief Creates ConcatenateFunction test case:
 *        test_concatenate_leftEmptyString.
 */
TEST(ConcatenateFunction, test_concatenate_leftEmptyString) {
    // Left empty string
    const char *stringLiteral = "Right is non-empty!";
    char *concatLeftEmptyResult = concatenate("", stringLiteral);

    TEST_ASSERT_EQUAL_STRING(stringLiteral, concatLeftEmptyResult);

    // FREE_PTR(concatLeftEmptyResult);
}

/**
 * @brief Creates ConcatenateFunction test case:
 *        test_concatenate_rightEmptyString.
 */
TEST(ConcatenateFunction, test_concatenate_rightEmptyString) {
    // Left empty string
    const char *stringLiteral = "Left is non-empty!";
    char *concatRightEmptyResult = concatenate(stringLiteral, "");

    TEST_ASSERT_EQUAL_STRING(stringLiteral, concatRightEmptyResult);

    // FREE_PTR(concatRightEmptyResult);
}

/**
 * @brief Creates ConcatenateFunction test case:
 *        test_concatenate_nonEmptyStrings.
 */
TEST(ConcatenateFunction, test_concatenate_nonEmptyStrings) {
    // Non-empty strings
    char *concatResult = concatenate("Left ", "Right");

    TEST_ASSERT_EQUAL_STRING("Left Right", concatResult);

    // FREE_PTR(concatResult);
}

/**
 * @brief Creates ConcatenateFunction test group runner.
 */
TEST_GROUP_RUNNER(ConcatenateFunction) {
    // Run all group test cases
    RUN_TEST_CASE(ConcatenateFunction, test_concatenate_emptyStrings);
    RUN_TEST_CASE(ConcatenateFunction, test_concatenate_leftEmptyString);
    RUN_TEST_CASE(ConcatenateFunction, test_concatenate_rightEmptyString);
    RUN_TEST_CASE(ConcatenateFunction, test_concatenate_nonEmptyStrings);
}

int main() {
    // Start testing
    UNITY_BEGIN();

    // Running InitializeFunction and ConcatenateFunction groups' tests
    RUN_TEST_GROUP(InitializeFunction);
    RUN_TEST_GROUP(ConcatenateFunction);

    // End testing
    UNITY_END();

    return 0;
}
