#include "types.h"

typedef struct Sub_FUN_001950c0 {
    u8 pad000[0x78];
    s32 f78;
} Sub_FUN_001950c0;

typedef struct Node_FUN_001950c0 {
    struct Node_FUN_001950c0 *f00;
    struct Node_FUN_001950c0 *f04;
    u8 pad008[0x8];
    Sub_FUN_001950c0 *f10;
} Node_FUN_001950c0;

typedef struct Obj_FUN_001950c0 {
    u8 pad000[0x94];
    Node_FUN_001950c0 *f94;
    u8 pad098[0x4];
    s32 f9C;
} Obj_FUN_001950c0;

void NodeObjAppendChild_1950c0(Obj_FUN_001950c0 *o, Node_FUN_001950c0 *n)
{
    Node_FUN_001950c0 *p;
    Node_FUN_001950c0 *q;

    if (n == 0) {
        return;
    }
    if (n->f10 == 0) {
        return;
    }
    if (n->f10 != 0) {
        if ((n->f10->f78 & 4) != 0) {
            o->f9C = 1;
        }
    }
    p = o->f94;
    if (p == 0) {
        o->f94 = n;
        return;
    }
    while (p != 0) {
        q = p->f00;
        if (q == 0) {
            break;
        }
        p = q;
    }
    p->f00 = n;
    if (n == 0) {
        return;
    }
    n->f04 = p;
}
