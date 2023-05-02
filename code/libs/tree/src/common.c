/**
 * @file common.c
 *
 * @author Samah A. SHAYYA
 *
 * @brief This file contains the implementation of the common functions.
 */

#include <stdio.h>

#include "tree/common.h"

size_t getMaxNumberOfDigitsNeeded(int minValue, int maxValue) {
    size_t numDigits; // It includes also the sign (-) in case of negative int
    size_t numMin, numMax;

    // Number of digits corresponding to minValue
    numMin = snprintf(NULL, 0, "%d", minValue);

    // Number of digits corresponding to maxValue
    numMax = snprintf(NULL, 0, "%d", maxValue);

    // Setting numDigits as the largest among numMin and numMax
    numDigits = (numMax >= numMin)? numMax : numMax;

    return numDigits;
}

/**
 * REMARK:
 *
 * To compute margin padding and interspacing, we start with last level,
 * which is equal to height - 1. In what follows, we assume h = height and
 * l = level = 0, ...., h - 1 to simplify the equations.
 *
 * Consider last level, i.e. l = h - 1. At this level, we have zero margin
 * paddings and 2^(h-1) - 1 interspacing blocks and 2^(h - 1) node blocks. The
 * sum of blocks is: 0 (left padding) + (2 ^ (h - 1) - 1) * (1 space block) (
 * interspacing blocks) + 2 ^ (h - 1) * (1 node block) (nodes blocks with
 * node block being equal to space block) + 0 (right padding).
 *
 * Then at any level, the corresponding spacing and node blocks should be equal
 * to that of the last level.
 *
 * lp (left padding) + (2 ^ l - 1) * nis + 2 ^ l +rp (right padding)
 * =
 * 0 + (2 ^ (h - 1) - 1) * 1 + 2 ^ (h - 1) * 1 + 2 ^ (h - 1) * 1 + 0,
 *
 * where node block size = space block size (i.e. why we set it to one) and
 * lp = rp.
 *
 * Note also that lp (l) = lp (l + 1) + (nis - 1)  / 2 + 1 because we take
 * subsequent left padding and add to it (nis - 1) / 2 (the subtraction of 1
 * is to accommodate the first node size on level l and adding 1 is to
 * accommodate first node on level l + 1).
 *
 * For better understanding draw the last level and start from it to compute
 * previous level spacings.
 */
bool setPaddingAndInterSpacing(size_t height,
                               size_t level,
                               size_t *levelPaddingPtr,
                               size_t *levelInterSpacingPtr) {

    bool done = false;

    if((level < height) && levelPaddingPtr && levelInterSpacingPtr) {
        if (level == height - 1) {
            *levelPaddingPtr = 0;

            // We need to consider the case where height is one (i.e. level = 0)
            *levelInterSpacingPtr = level != 0 ? 1 : 0;
        }
        else {
            bool ok;

            ok = setPaddingAndInterSpacing(height,
                                           level + 1,
                                           levelPaddingPtr,
                                           levelInterSpacingPtr);

            if(ok) {
                (*levelPaddingPtr) += 1 + ((*levelInterSpacingPtr) - 1) / 2;

                if(level == 0) {
                    // No interspacing having only one node
                    *levelInterSpacingPtr = 0;
                }
                else {
                    /**
                     * interSpacing is equal to:
                     * (2 ^ h - 2 ^ l - 2 * padding -1) / (2 ^ l - 1)
                     * where 2 ^ a is equivalent to 1 << a .
                     *
                     * Note that below parenthesis about shift operator
                     * expressions are needed (otherwise we get wrong result).
                     *
                     * In fact, if we remove parenthesis, here is what we get:
                     * 1 << height - 1 << level = 1 << (height - 1 << level)
                     * due to precedence laws. So, be careful and add
                     * parenthesis if in doubt.
                     */
                    *levelInterSpacingPtr = (1 << height) - (1 << level);
                    (*levelInterSpacingPtr) -= 2 * (*levelPaddingPtr) + 1;
                    (*levelInterSpacingPtr) /= ((1 << level) - 1);
                }
            }
        }

        done = true;
    }

    return done;
}
