#include "types.h"

typedef struct Item {
    s32 a;
    s32 b;
    struct Item *next;
} Item;

typedef struct Node {
    f32 x, y, z;
    s32 pad;
    f32 half;
    struct Node *child[2][2];
    Item *items;
    s32 pad2[2];
} Node;

typedef struct Tree {
    s32 pad0;
    u8 heap[0x98];
    f32 minSize;
    f32 size;
} Tree;

typedef struct Box {
    f32 min[4];
    f32 max[4];
} Box;

void *MemStackNew_14e230(s32 size, void *heap);
void HitShapeListCalcBounds_315350(Box *out, void *arg);

void *QuadTreeInsert_315880(Tree *tree, Node *node, s32 div, void *arg) {
    Box box;
    s32 ix;
    s32 iz;
    f32 size;
    Node **pp;

    if (node == 0) {
        return 0;
    }
    HitShapeListCalcBounds_315350(&box, arg);
    ix = 2;
    if (box.min[0] < node->x) {
        ix = 0;
    } else if (box.max[0] > node->x) {
        ix = 1;
    }
    iz = 2;
    if (box.min[2] < node->z) {
        iz = 0;
    } else if (box.max[2] > node->z) {
        iz = 1;
    }
    size = tree->size / (f32)div;
    if (ix == 2 || iz == 2 || size <= tree->minSize) {
        Item *item = MemStackNew_14e230(0xC, tree->heap);
        if (item != 0) {
            item->a = 0;
            item->b = 0;
            item->next = 0;
        }
        if (item != 0) {
            item->next = node->items;
            node->items = item;
        }
        return item;
    }
    pp = &node->child[ix][iz];
    if (*pp == 0) {
        Node *n = MemStackNew_14e230(0x30, tree->heap);
        if (n != 0) {
            s32 i;
            n->items = 0;
            for (i = 0; i < 4; i++) {
                (&n->child[0][0])[i] = 0;
            }
        }
        *pp = n;
        if (n == 0) {
            return 0;
        }
        n->half = size / 2.0f;
        (*pp)->x = node->x + (*pp)->half * ((f32)ix - 0.5f);
        (*pp)->y = node->y;
        (*pp)->z = node->z + (*pp)->half * ((f32)iz - 0.5f);
    }
    return QuadTreeInsert_315880(tree, *pp, div * 2, arg);
}
