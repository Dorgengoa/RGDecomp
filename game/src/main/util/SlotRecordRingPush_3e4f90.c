/* rgp:protos */
#define RGP_SELF_SlotRecordRingPush_3e4f90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 unk0;
    s16 unk2;
} Elem003E4F90;

typedef struct {
    s16 unk0;
    u8 pad2[2];
    Elem003E4F90 *unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 padE[2];
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
} Sub68_003E4F90;

typedef struct {
    u8 pad0[0x68];
    Sub68_003E4F90 *unk68;
} Obj003E4F90;

/*rgp*/

s32 SlotRecordRingPush_3e4f90(Obj003E4F90 *arg0, s16 arg1, s32 arg2)
{
    Sub68_003E4F90 *s;
    s32 n;
    s32 idx;
    s32 v;
    Elem003E4F90 *e;
    s16 *fp;

    s = arg0->unk68;
    if (s == NULL) {
        return -1;
    }
    if (s->unk4 == NULL) {
        return -1;
    }
    n = s->unk0;
    fp = &s->unk8;
    if (*fp >= n) {
        return -1;
    }
    if (*fp == 0) {
        *fp = 1;
        idx = 0;
        v = 0;
        arg0->unk68->unkA = 0;
        arg0->unk68->unkC = 0;
        arg0->unk68->unk10 = 0;
        arg0->unk68->unk12 = 0;
        arg0->unk68->unk14 = 0;
        arg0->unk68->unk16 = 0;
    } else if (arg2 != 0) {
        idx = s->unkC + 1;
        v = s->unk12 + 1;
        fp = &s->unkC;
        if (idx >= n) {
            idx = 0;
        }
        *fp = idx;
        arg0->unk68->unk12 = v;
        arg0->unk68->unk8++;
    } else {
        fp = &s->unkA;
        idx = s->unkA - 1;
        v = s->unk10 - 1;
        if (idx < 0) {
            idx = n - 1;
        }
        if (v < 0) {
            return -1;
        }
        *fp = idx;
        arg0->unk68->unk10 = v;
        arg0->unk68->unk8++;
    }
    e = (Elem003E4F90 *)((u8 *)arg0->unk68->unk4 + idx * 0x350);
    SlotRecordReset_3eeca0(e);
    e->unk0 = arg1;
    e->unk2 = v;
    return idx;
}
