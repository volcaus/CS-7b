#ifndef FairPlay_Included
#define FairPlay_Included

#include <string>

/**
 * Given a number n, returns the A-sequence of order n. If n is negative,
 * then this function reports an error by calling the error() function.
 *
 * @param n The order of the A-sequence to generate.
 * @return The A-sequence of order n.
 */
std::string aSequence(int n);

/**
 * Given a number n, returns the B-sequence of order n. If n is negative,
 * then this function reports an error by calling the error() function.
 *
 * @param n The order of the B-sequence to generate.
 * @return The B-sequence of order n.
 */
std::string bSequence(int n);


#endif
