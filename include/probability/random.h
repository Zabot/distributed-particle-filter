#ifndef RANDOM_H
#define RANDOM_H

/**
 * @brief Generates a uniform random float between min and max
 * @param min The minimum possible value to generate
 * @param max The maximum possible value to generate
 * @param res The number of possible values between each integer step
 * @return A random float
 */
float uniform(float min, float max);

/**
 * @brief Generates a random float following a standard normal distribution.
 *
 * Estimates the gaussian using the fact that the sum of a series of
 * uniformly distributed numbers is normally distributed
 */
float gaussian();

#endif

