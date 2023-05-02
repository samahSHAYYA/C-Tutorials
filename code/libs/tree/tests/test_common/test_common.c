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

#include "tree/common.h"

/**
 * @brief Creates GetMaxNumberOfDigitsNeededFunction test group.
 */
TEST_GROUP(GetMaxNumberOfDigitsNeededFunction);

/**
 * @brief Creates GetMaxNumberOfDigitsNeededFunction test group setup, which is
 *        mandatory.
 */
TEST_SETUP(GetMaxNumberOfDigitsNeededFunction) {
    // Add any test setup code here or keep empty (it runs before each test)
};

/**
 * @brief Creates GetMaxNumberOfDigitsNeededFunction test group teardown, which
 *        is mandatory.
 */
TEST_TEAR_DOWN(GetMaxNumberOfDigitsNeededFunction) {
    // Add any test setup code here or keep empty (it runs after each test)
};

/**
 * @brief Creates a test case for GetMaxNumberOfDigitsNeededFunction group with
 *        zero as min and max values.
 */
TEST(GetMaxNumberOfDigitsNeededFunction, test_zeros) {
    TEST_ASSERT_EQUAL_UINT64(1, getMaxNumberOfDigitsNeeded(0, 0));
}

/**
 * @brief Creates a test case for GetMaxNumberOfDigitsNeededFunction group with
 *        the min = -1 and max = 0.
 */
TEST(GetMaxNumberOfDigitsNeededFunction, test_negative_unity_and_zero) {
    TEST_ASSERT_EQUAL_UINT64(2, getMaxNumberOfDigitsNeeded(-1, 0));
}

/**
 * @brief Creates a test case for GetMaxNumberOfDigitsNeededFunction group with
 *        the min = -1 and max = 100.
 */
TEST(GetMaxNumberOfDigitsNeededFunction, test_negative_unity_and_hundred) {
    TEST_ASSERT_EQUAL_UINT64(3, getMaxNumberOfDigitsNeeded(-1, 100));
}

/**
 * @brief Creates a test case for GetMaxNumberOfDigitsNeededFunction group with
 *        the min = -1225 and max = 1254575.
 */
TEST(GetMaxNumberOfDigitsNeededFunction, test_general) {
    TEST_ASSERT_EQUAL_UINT64(7, getMaxNumberOfDigitsNeeded(-1225, 1254575));
}


/**
 * @brief Creates InitializeFunction test group runner.
 */
TEST_GROUP_RUNNER(GetMaxNumberOfDigitsNeededFunction) {
    // Run all group test cases
    RUN_TEST_CASE(GetMaxNumberOfDigitsNeededFunction, test_zeros);

    RUN_TEST_CASE(GetMaxNumberOfDigitsNeededFunction,
                  test_negative_unity_and_zero);

    RUN_TEST_CASE(GetMaxNumberOfDigitsNeededFunction,
                  test_negative_unity_and_hundred);

    RUN_TEST_CASE(GetMaxNumberOfDigitsNeededFunction, test_general);
}

int main() {
    // Start testing
    UNITY_BEGIN();

    // Running GetMaxNumberOfDigitsNeededFunction group' tests
    RUN_TEST_GROUP(GetMaxNumberOfDigitsNeededFunction);

    // End testing
    UNITY_END();

    return 0;
}
