#include "types.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    u8 padC[0x18 - 0xC];
    s32 unk18;
    u8 padTail[0x90 - 0x1C];
} Elem004A0910;

typedef struct {
    u8 pad0[0x4];
    s32 unk4;
    u8 padTail[0x1E0 - 0x8];
} Elem0049EB10;

extern void SoundSeqPlayerAssignVoiceIds_1b5a30(Elem004A0910 *, s32);
extern void SoundSeqPlayerInit_1b5a90(Elem004A0910 *);
extern Elem004A0910 D_004A0910[];
extern Elem0049EB10 D_0049EB10[];

s32 SoundSeqPlayerAlloc_1b7bf0(u32 arg0, s32 arg1, s32 arg2)
{
    s32 lo;
    s32 idx;
    s32 hi;
    Elem0049EB10 *p;
    s32 i;
    Elem004A0910 *e;

    for (i = 0; i < 0x20; i++) {
        e = &D_004A0910[i];
        if (e->unk8 == 0) {
            idx = i;
            goto found;
        }
    }
    e = NULL;
found:
    if (e == NULL || arg1 == 0) {
        return -1;
    }
    SoundSeqPlayerInit_1b5a90(e);
    SoundSeqPlayerAssignVoiceIds_1b5a30(e, 0);
    if (arg0 == 0xFFFFFFFF) {
        return -1;
    }
    hi = (arg0 >> 24) & 0xFF;
    lo = (arg0 >> 16) & 0xFF;
    if (hi < 0) {
        goto null;
    }
    if (hi <= 0x10) {
        goto ok;
    }
null:
    p = NULL;
    goto join;
ok:
    p = &D_0049EB10[hi];
join:
    if (p == NULL) {
        return -1;
    }
    if (arg2 < 0) {
        arg2 = 0x7F;
    }
    e->unk8 = arg1;
    e->unk0 = p->unk4;
    e->unk4 = lo;
    e->unk18 = arg2;
    return idx;
}
