#include "triliteration/triliteration_data.h"

#include <stddef.h>


void initTriliterationData(TriliterationData *data) {
  data->count = 0;
}

void addTriliterationAnchor(TriliterationData* data, int key, const TriliterationAnchor* anchor) {
  data->anchors[data->count].anchor = *anchor;
  data->anchors[data->count].key = key;
  data->count++;
}

int removeTriliterationAnchor(TriliterationData* data, int key) {
  int deleting = 0;
  for (int i = 0; i < data->count; i++) {
    if (data->anchors[i].key == key)
      deleting = 1;

    if (deleting)
      data->anchors[i] = data->anchors[i + 1];
  }

  data->count -= deleting;
  return deleting;
}

int containsTriliterationAnchor(const TriliterationData* data, int key) {
  for (int i = 0; i < data->count; i++)
    if (data->anchors[i].key == key)
      return 1;

  return 0;
}

TriliterationAnchor* getTriliterationAnchor(const TriliterationData* data, int key) {
  for (int i = 0; i < data->count; i++)
    if (data->anchors[i].key == key)
      return &data->anchors[i].anchor;

  return NULL;
}

int updateTriliterationAnchor(TriliterationData* data, int key, const TriliterationAnchor* anchor) {
  for (int i = 0; i < data->count; i++)
  {
    if (data->anchors[i].key == key)
    {
      data->anchors[i].anchor = *anchor;
      return 1;
    }
  }
  return 0;
}

