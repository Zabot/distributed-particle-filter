#include "simulate/communication.h"

#include "utils/circular_buffer.h"

#define MAX_QUEUE 128

int nodeID;

int getID() {
  return nodeID;
}


int txSize = 0;
Message txQueue[MAX_QUEUE];

int broadcastMessage(const Message* m)
{
  if (txSize >= MAX_QUEUE) return 1;

  txQueue[txSize] = *m;
  txQueue[txSize].sender = getID();
  txSize++;
  return 0;
}


Message rxQueue[MAX_QUEUE];

Message* rxHead = rxQueue;
Message* rxTail = rxQueue;

int recieveMessage(Message* m) {
  if (rxHead == rxTail) return 1;

  *m = *rxHead;
  rxHead = circularBufferOffset(rxQueue, MAX_QUEUE, sizeof(Message), rxHead, 1);

  return 0;
}


/////////// For binding from python simulation wrapper
/**
 * @brief sets the eeprom node id
 */
void set_node_id(int id) {
  nodeID = id;
}

/**
 * @brief Adds a message to the pending message queue
 */
int add_pending_rx_message(Message m) {
  if (circularBufferOffset(rxQueue, MAX_QUEUE, sizeof(Message), rxTail, 1) == rxHead)
    return 1;

  *rxTail = m;
  rxTail = circularBufferOffset(rxQueue, MAX_QUEUE, sizeof(Message), rxTail, 1);

  return 0;
}

/**
 * @brief retrieve the messages on the tx queue
 */
Message *get_tx_queue() {
  return txQueue;
}

int get_tx_queue_length() {
  return txSize;
}

void clear_tx_queue() {
  txSize = 0;
}

