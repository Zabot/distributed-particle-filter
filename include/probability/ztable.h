#ifndef ZTABLE_H
#define ZTABLE_H

/**
 * @brief Performs a ztest on the given normal distribution
 *
 * @param mu The mean of the normal distribution
 * @param sigma The standard deviation of the normal distribution
 * @param z The value of the random variable to test
 *
 * @return The probability of a randomly selected value from the given normal
 * distribution being less than the tested value
 */
float ztest(float mu, float sigma, float z);

/**
 * @brief Performs a bounded ztest on the given normal distribution
 *
 * @param mu The mean of the normal distribution
 * @param sigma The standard deviation of the normal distribution
 * @param z The value of the random variable to test
 * @param delta The range either side of the test value to consider
 *
 * @return The probability of a randomly selected value from the given normal
 * distribution being within delta of the tested value
 */
float ztestBounded(float mu, float sigma, float z, float delta);

#endif

