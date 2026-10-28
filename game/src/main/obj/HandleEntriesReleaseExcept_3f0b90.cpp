#include "types.h"

typedef struct {
    s16 *unk0;
    u8 pad4[0xC - 0x4];
    s16 unkC;
    u8 padE[0x28 - 0xE];
} Elem18;

typedef struct {
    u8 pad0[0x18];
    Elem18 *unk18;
} Obj0Arg0;

extern "C" {
s32 GetNavMgr_2d1950(void);
void NpcObjTableReleaseByGroupId_2fa910(s32, s32);
s32 GetNpcObjTable_312860(void);
s32 GetTreasureBoxPool_3389b0(void);
void TreasureBoxPoolResetByGroupId_3389c0(s32, s32);
void HandleEntryRelease_3f1d80(Obj0Arg0 *, Elem18 *, s32);
void HandleEntryInit_3f4160(Elem18 *);
extern s32 D_004644A0[0x100];
}

extern "C" s32 HandleEntriesReleaseExcept_3f0b90(Obj0Arg0 *arg0, s32 arg1)
{
    s32 a = GetTreasureBoxPool_3389b0();
    s32 b = GetNpcObjTable_312860();
    GetNavMgr_2d1950();
    Elem18 *e = arg0->unk18;
    s32 n = D_004644A0[0];
    s32 i;
    for (i = 0; i < n; i++, e++) {
        bool found = false;
        s32 t = e->unkC;
        if (t == 3) goto body;
        if (t != 4) goto skip;
    body:
        if (e->unk0 != NULL) {
                s32 v = *e->unk0;
                if (v == arg1) {
                    found = true;
                }
                if (!found) {
                    if (a != 0) {
                        TreasureBoxPoolResetByGroupId_3389c0(a, v);
                    }
                    if (b != 0) {
                        NpcObjTableReleaseByGroupId_2fa910(b, v);
                    }
                }
            }
    skip:
        if (!found) {
            HandleEntryRelease_3f1d80(arg0, e, 1);
            HandleEntryInit_3f4160(e);
        }
    }
    return 1;
}
