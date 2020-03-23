#ifndef TRILITERRATION_TRILITERATION_DATA_H
#define TRILITERRATION_TRILITERATION_DATA_H

#include "utils/circular_buffer.h"
#include "vector/vector3f.h"

#define MAX_TRILITERATION_ANCHORS 10

typedef struct TriliterationAnchor {
  vector3f position;
  float distance;
} TriliterationAnchor;

typedef struct TriliterationDataEntry {
  int key;
  TriliterationAnchor anchor;
  //struct TriliterationDataEntry* next;
} TriliterationDataEntry;


/**
 * @struct TriliterationData
 * Groups data used by triliteration procedure
 * @var TriliterationData::count The number of measured anchors
 * @var TriliterationData::anchors The position of the measured anchors
 * @var TriliterationData::distances The distance measured to each anchor
 */
typedef struct TriliterationData {
  int count;
  TriliterationDataEntry anchors[MAX_TRILITERATION_ANCHORS];
} TriliterationData;

void initTriliterationData(TriliterationData *data);
void addTriliterationAnchor(TriliterationData* data,
                            int key,
                            const TriliterationAnchor* anchor);
int removeTriliterationAnchor(TriliterationData* data, int key);
int containsTriliterationAnchor(const TriliterationData* data, int key);
int updateTriliterationAnchor(TriliterationData* data,
                              int key,
                              const TriliterationAnchor* anchor);
const TriliterationAnchor *getTriliterationAnchorIndex(const TriliterationData* data, int index);

#endif

