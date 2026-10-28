/* rgp:protos */
#define RGP_SELF_NpcViewGetCount_41c080 1
#define RGP_SELF_getElem 1
#define RGP_SELF_getRow 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0xC];
    s16 *unkC;
    u8 pad10[0x48];
} Elem;

typedef struct {
    u8 pad0[0x7C];
    s16 unk7C;
    u8 pad7E[0xE];
    Elem *unk8C;
    u8 pad90[4];
    void *unk94;
} Row;

typedef struct {
    u8 pad0[0xC];
    Row *unkC;
} Tbl;

typedef struct {
    u8 pad0[4];
    Tbl *unk4;
    u8 pad8[2];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 pad : 6;
    u8 padB;
    s16 unkC;
    s16 unkE;
    s16 unk10;
} Obj;

extern s32 D_004644A8[];
/*rgp*/

static inline Row *getRow(Tbl *t, s32 i, s32 max)
{
    return (i >= 0 && i < max) ? &t->unkC[i] : NULL;
}

static inline Elem *getElem(Row *r, s32 j)
{
    return (j >= 0 && j < r->unk7C) ? &r->unk8C[j] : NULL;
}

s32 NpcViewGetCount_41c080(Obj *obj)
{
s32 count;
s32 i;
s32 j;
s32 max;
Row *row;
Elem *e;
    if (obj->unk4 == NULL) {
        return 0;
    }
    count=0;
    i=0;
    max = D_004644A8[0];
    for (; i < max; i++) {
        row = getRow(obj->unk4, i, max);
        if (row == NULL) {
            continue;
        }
        if (row->unk94 == NULL || GroupEntryMatchesKey_3f40e0(row->unk94, -1) == 0) {
            continue;
        }
        for (j=0; j < row->unk7C; j++) {
            e = getElem(row, j);
            if (e == NULL) {
                continue;
            }
            if (e->unkC == NULL) {
                continue;
            }
            if (*e->unkC == 0) {
                if (!obj->b1) {
                    continue;
                }
            } else {
                if (!obj->b0) {
                    continue;
                }
            }
            count++;
        }

    }
    obj->unkC=-1;obj->unkE=-1;obj->unk10=-1;
    return count;
}
