#include <stdio.h>
#include <stdlib.h>

#define M 4
#define m 2
#define DIM 2

// typedef struct Point {
//     int coord[DIM];
// } Point;

// typedef struct Rectangle {
//     Point lowest;
//     Point highest;
// } Rectangle;

// typedef struct Node {
//     int is_leaf;
//     int num_children;
//     struct Node* parent;
//     Rectangle bbox;
//     union {
//         struct Node* children[M];
//         Point* points[M];
//     } data;
// } Node;

// Node* root = NULL;

// typedef struct leafNode
// {
//     struct non_leafNode *parent;
//     Rectangle *mbr;
//     float tuple_id [21][2];
// } LN;

// typedef struct non_leafNode
// {
//     struct non_leafNode *parent;
//     Rectangle *MBR;
//     Rectangle *child_ptr[M];
// } NLN;

typedef struct point
{
    int coord[2];
} Point;

typedef struct rectangle
{
    Point lowest;  // Bottom left corner
    Point highest; // Top right corner
} Rectangle;

typedef struct Node
{
    int isleaf;
    int num_children;
    Node *parent;
    Rectangle *mbr;
    union
    {
        Node *children[M];
        Point *points[2 * M];
    } data;
} Node;

typedef struct rtree
{
    Node *root;
} RTree;

int rect_area(Rectangle *rect)
{
    int area = 1;
    for (int i = 0; i < DIM; i++)
    {
        area *= (rect->highest.coord[i] - rect->lowest.coord[i]);
    }
    return area;
}

int calculate_enlargement(Rectangle *rect, Point *point)
{
    int old_area = calculate_area(rect);
    int new_area = 1;
    for (int i = 0; i < DIM; i++)
    {
        if (point->coord[i] < rect->lowest.coord[i])
        {
            new_area *= (rect->highest.coord[i] - point->coord[i]);
        }
        else if (point->coord[i] > rect->highest.coord[i])
        {
            new_area *= (point->coord[i] - rect->lowest.coord[i]);
        }
        else
        {
            new_area *= (rect->highest.coord[i] - rect->lowest.coord[i]);
        }
    }
    return new_area - old_area;
}

void calculate_mbr(Rectangle *rect1, Rectangle *rect2, Rectangle *result)
{
    for (int i = 0; i < DIM; i++)
    {
        result->lowest.coord[i] = rect1->lowest.coord[i] < rect2->lowest.coord[i] ? rect1->lowest.coord[i] : rect2->lowest.coord[i];
        result->highest.coord[i] = rect1->highest.coord[i] > rect2->highest.coord[i] ? rect1->highest.coord[i] : rect2->highest.coord[i];
    }
}

Node *createNode(int isleaf)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->parent = NULL;
    new_node->isleaf = isleaf;
    new_node->num_children = 0;
    new_node->mbr = NULL;
}
