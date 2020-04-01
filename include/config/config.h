#ifndef CONFIG_H
#define CONFIG_H

// Global target localization tolerance
#define LOCALIZATION_TOLERANCE 0.25

// Standard deviation of range sensors
#define RANGE_SENSOR_DEVIATION 0.1

// Particle filter confidence is the ratio of samples in within tolerance of
// the belief to total samples
#define FILTER_CONFIDENCE_TOLERANCE LOCALIZATION_TOLERANCE

// Range sensor measuremets
#define RANGE_SENSOR_TOLERANCE LOCALIZATION_TOLERANCE

// What is the probability of measuring a distance if the anchor that is being
// measured is incorrect
#define MEASUREMENT_P_IF_FAIL 0.05

// Maximum number of samples in a particle filter
#define MAX_SAMPLES 10000

// How long to wait before broadcasting position, even if no changes were made
#define UNPROMPTED_INTERVAL 100

// Inital size for microcontroller filter
#define INITAL_FILTER_SIZE 1000

// Number of samples to seed the filter with when encountering a new node
#define FILTER_SEED_SIZE 128

// Maximum number of neighbors
#define MAX_TRILITERATION_ANCHORS 50

// Minimum confidence needed to join a cluster
#define CLUSTER_JOIN_CONFIDENCE 0.80

#endif

