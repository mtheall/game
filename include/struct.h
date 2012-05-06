#pragma once
#ifndef STRUCTS_H
#define STRUCTS_H

typedef enum {
  DIR_NONE = 0,
  DIR_RIGHT,
  DIR_DOWN,
  DIR_LEFT,
  DIR_UP,
} direction_t;

typedef struct {
  int x;
  int y;
} vector2_t;

#endif
