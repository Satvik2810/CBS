#include <stdio.h>
#include <stdlib.h>

#define M 4
#define m 2

typedef struct point
{
    float x; // x coordinate
    float y; // y coordinate
} Point;

typedef struct rectangle
{
    Point lowest;  // Bottom left corner
    Point highest; // Top right corner
} Rectangle;

typedef struct leafNode
{
    struct non_leafNode *parent;
    Rectangle *mbr;
    float tuple_id [21][2];
} LN;

typedef struct non_leafNode
{
    struct non_leafNode *parent;
    Rectangle *MBR;
    Rectangle *child_ptr[M]; 
} NLN;

typedef struct rtree
{
    
}
