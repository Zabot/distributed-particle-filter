#ifndef VECTOR3F_H
#define VECTOR3F_H

typedef struct vector3f {
  float x;
  float y;
  float z;
} vector3f;

/**
 * @brief Initalizes all components of a vector to zero
 * @param v The vector to zero
 */
void zero(vector3f *v);

/**
 * @brief Initalize each component of a vector a uniformly distributed random
 * float between min and max.
 * @param v The vector to randomize
 * @param min The minimum value of any component
 * @param max The maximum value of any component
 * @param res The number of possible values between two integer steps
 */
void randomize(vector3f *v, float min, float max);

/**
 * @brief Generates a uniformly distributed random unit vector.
 * @param v The generated vector
 */
void randomUnit(vector3f *v);

/**
 * @brief Generates a uniformly distributed random 2d unit vector.
 * @param v The generated vector. Z will be zero
 */
void random2dUnit(vector3f *v);

/**
 * @brief Initalizes all components of a vector using corresponding components
 * in another vector.
 * @param target The vector to update
 * @param source The vector to copy
 */
void assign(vector3f* target, const vector3f *source);

/**
 * @brief computes the norm of a vector
 * @param v The vector to calculate
 * @return The norm of the vector
 */
float norm(const vector3f *v);

/**
 * @brief scales v by c
 * @param v The vector to scale
 * @param c The scaling factor
 */
void scale(vector3f* v, float c);

/**
 * @brief Multiplies every element of v by the corresponding element in u
 * @param v The vector to multiply
 * @param u The corresponding multiples
 */
void multiply(vector3f* v, const vector3f* u);

/**
 * @brief adds u to v and updates v.
 * @param v The vector to add to
 * @param u The vector to be added
 */
void add(vector3f* v, const vector3f* u);

/**
 * @brief subtracts u from v and updates v.
 * @brief v The vector to subtract from
 * @brief u The vector to be subtracted
 */
void subtract(vector3f* v, const vector3f* u);

/**
 * @brief returns the difference between u and v.
 * @param u The vector to subtract from
 * @param v The vector to be subtracted
 * @return The result of u - v
 */
vector3f difference(const vector3f* u, const vector3f* v);

/**
 * @brief returns the norm of the difference between u and v.
 * @param u One vector representing a point
 * @param v Another vector representing a point
 * @return The distance between the two points
 */
float distance(const vector3f* u, const vector3f* v);

/**
 * @brief prints the vector to stdio
 * @param v The vector to be printed
 */
void print(const vector3f* v);

#endif

