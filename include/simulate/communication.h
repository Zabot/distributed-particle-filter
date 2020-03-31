#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "vector/vector3f.h"

#define LOCALIZATION_MSG 1
#define NUMERIC_MSG 0

#define NODE_PRINT(f_, ...) printf(("[Node %d]: "f_), nodeID, __VA_ARGS__)

typedef struct LocalizationPayload {
  vector3f location;
  float confidence;
  int clusterID;
} LocalizationPayload;

typedef union MessagePayload {
  LocalizationPayload localization;
} MessagePayload;

typedef struct Message {
  int sender;
  float range;
  int type;
  MessagePayload payload;
} Message;

/**
 * @brief Retrieves a message off the incoming message queue
 * @param m A pointer to a message buffer
 * @return 0 if a message was successfully retrieved
 */
int recieveMessage(Message* m);

/**
 * @brief Broadcasts a message to any nearby nodes
 * @param m The message to broadcast
 * @return 0 if the message was succesfully broadcast
 */
int broadcastMessage(const Message* m);

/**
 * @brief Gets the ID of the node
 * @return The current id of the node
 */
int getID();

#endif

