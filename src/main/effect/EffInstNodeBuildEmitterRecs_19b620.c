#include "types.h"

typedef struct Node {
    struct Node *next;
    s32 x4;
} Node;

typedef struct {
    u8 pad0[0x44];
    Node *x44;
} A0;

typedef struct {
    u8 pad0[0xC0];
    s32 unkC0;
    u8 *unkC4;
} A2;

extern u8 *ConstructNewArray_100710(s32, void *, s32, s32, s32);
extern s32 MemStackNew_14e1b0(s32, s32);
extern void EffInstEmitterRecCtor_19b750(void);
extern s32 EffObjBuildEmitterRecMaybe_1a9890(s32, s32, u8 *);
extern s32 EffObjAllocWorkSlots_1a9e40(void);

s32 EffInstNodeBuildEmitterRecs_19b620(A0 *o, s32 arg1, A2 *arg2)
{
    s32 n;
    s32 i;
    u8 *r;
    Node *p;

    if (EffObjAllocWorkSlots_1a9e40() == 0) {
        return 0;
    }
    p = o->x44;
    if (p == 0) {
        return 0;
    }
    n = 1;
    p = p->next;
    while (p != 0) {
        p = p->next;
        n++;
    }
    if (n == 0) {
        return 0;
    }
    r = ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x110 + 0x10, arg1), (void *)EffInstEmitterRecCtor_19b750, 0, 0x110, n);
    arg2->unkC4 = r;
    if (r == 0) {
        return 0;
    }
    arg2->unkC0 = n;
    for (p = o->x44, n = 0; p != 0; p = p->next, n++) {
        if (EffObjBuildEmitterRecMaybe_1a9890(p->x4, arg1, arg2->unkC4 + n * 0x110) == 0) {
            return 0;
        }
    }
    return 1;
}
