#include "vector/vector3f.h"

#include <math.h>
#include <stdio.h>

#include "utils/random.h"

// Initalization functions
void zero(vector3f *p) {
  p->x = 0;
  p->y = 0;
  p->z = 0;
}

void randomize(vector3f *p, float min, float max, float res) {
  p->x = randomf(min, max, res);
  p->y = randomf(min, max, res);
  p->z = randomf(min, max, res);
}

void assign(vector3f *v, const vector3f *u) {
  v->x = u->x;
  v->y = u->y;
  v->z = u->z;
}

// Mathmatical functions
float norm(const vector3f *r) {
  return sqrt(r->x * r->x + r->y * r->y + r->z * r->z);
}

void scale(vector3f* v, float c) {
  v->x *= c;
  v->y *= c;
  v->z *= c;
}

void multiply(vector3f* v, const vector3f* u) {
	v->x *= u->x;
	v->y *= u->y;
	v->z *= u->z;
}

void add(vector3f* v, const vector3f* u) {
	v->x += u->x;
	v->y += u->y;
	v->z += u->z;
}

void subtract(vector3f* v, const vector3f* u) {
	v->x -= u->x;
	v->y -= u->y;
	v->z -= u->z;
}

vector3f difference(const vector3f* u, const vector3f* v) {
  vector3f r;
  assign(&r, u);
  subtract(&r, v);
  return r;
}

float distance(const vector3f* u, const vector3f* v) {
  vector3f r = difference(u, v);
  return norm(&r);
}

// Display functions
void print(const vector3f *v) {
  printf("[%f;\t%f;\t%f]", v->x, v->y, v->z);
}

