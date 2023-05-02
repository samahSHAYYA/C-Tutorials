/**
 * @file common.h
 *
 * @author Samah A. SHAYYA
 *
 * @brief This file contains the common functions.
 */

#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>       // For size_t
#include <stdbool.h>      // For bool

/**
 * @brief Returns the maximum number of digits needed to represent a range of
 *        integers.
 *
 * @param minValue The minimum value of the range.
 *
 * @param maxValue The maximum value of the range.
 *
 * @return The maximum number of digits needed to represent the range of
 *         integers.
 *
 * @note This function assumes that the minimum value is less than or equal to
 *       the maximum value.
 */
size_t getMaxNumberOfDigitsNeeded(int minValue, int maxValue);

/**
 * @brief Sets the number of margin padding (left and right) and the number of
 *        inter-spacing blocking fo a given tree with certain height and at a
 *        given level. These are needed for properly visualizing tree nodes.
 *
 * @param height The tree height (zero means empty tree).
 *
 * @param level The level for which the padding is requested. It is zero-based
 *              index and strictly less than height.
 *
 * @param levelPaddingPtr Pointer to size_t variable that should hold the
 *                        current level padding. It should be a valid pointer.
 *
 * @param levelInterSpacingPtr Pointer to size_t variable that should hold the
 *                             current level padding. It should be a valid
 *                             pointer.
 *
 * @return True if the padding and inter-spacing values where successfully
 *         written and false, otherwise.
*/
bool setPaddingAndInterSpacing(size_t height,
                               size_t level,
                               size_t *levelPaddingPtr,
                               size_t *levelInterSpacingPtr);

#endif
