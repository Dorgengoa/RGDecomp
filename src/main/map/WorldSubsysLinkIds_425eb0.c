#include "types.h"

typedef struct Elem {
    u8 pad0[0x10];
    s32 unk10;
    u8 pad14[0x30];
} Elem;

typedef struct Obj0 {
    u8 pad0[0x7C];
    s16 unk7C;
    u8 pad7E[0x0E];
    Elem *unk8C;
    u8 pad90[4];
    s16 **unk94;
} Obj0;

typedef struct Obj1 {
    u8 pad0[0x74];
    s32 unk74;
} Obj1;

extern s32 GroupGetRecordById_4254b0(s32, s16, s16);

s32 WorldSubsysLinkIds_425eb0(Obj0 *arg0, Obj1 *arg1)
{
    s32 v;
    s16 **pp;
    s16 *p;
    s32 k;
    s32 i;
    Elem *e;

    if (arg1 == NULL) {
        return 0;
    }
    v = arg1->unk74;
    if (v == 0) {
        return 0;
    }
    pp = arg0->unk94;
    if (pp == NULL) {
        return 0;
    }
    p = *pp;
    if (p == NULL) {
        return 0;
    }
    k = *p;
    for (i = 0; i < arg0->unk7C; i++) {
        e = &arg0->unk8C[i];
        if (e == NULL) {
            break;
        }
        e->unk10 = GroupGetRecordById_4254b0(v, k, e->unk10);
    }
    return 1;
}
