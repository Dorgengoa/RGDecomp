#include "types.h"
#pragma opt_common_subs off
typedef struct {
    u8 pad0[0x40];
    s16 key;
    u8 pad42[0x3E];
} Ent;

typedef struct {
    u8 pad0[0x22];
    s16 count;
    u8 pad24[0x28];
    Ent e[1];
} Tbl;

typedef struct {
    u8 pad0[0x18];
    Tbl *tbl;
} Obj;

extern void Clear128Bytes_3d2720(void *arg0);
extern void *memcpy(void *arg0, void *arg1, s32 arg2);

void InsectRecRemoveMsgsOfKind_3ceed0(Obj *arg0, s32 arg1)
{
    s32 i;
    s32 j;
    Tbl *t4;
    Tbl *t3;
    Tbl *t42;
    Tbl *t43;

    if (arg0->tbl == NULL) {
        return;
    }
    for (i = 0; i < (t4 = arg0->tbl)->count; i++) {
        if (t4->e[i].key == arg1) {
            for (j = i; j < (t3 = arg0->tbl)->count - 1; j++) {
                t42 = arg0->tbl;
                memcpy(&t42->e[j], &t42->e[j + 1], 0x80);
            }
            Clear128Bytes_3d2720(&t3->e[j]);
            t43 = arg0->tbl;
            i--;
            t43->count--;
        }
    }
}
