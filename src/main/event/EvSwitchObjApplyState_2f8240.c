#include "types.h"

/* MAIN EvSwitchObjApplyState_2f8240.  Stack: a 48-byte matrix at 0x50 and a 36-byte
   record at 0x20; REVERSE declaration order puts the matrix first.
   The index into the 0x24-stride array at +0x110 is the u8 result of
   EvSwitchObjGetState_2f83f0. */

typedef struct V4 { f32 x, y, z, w; } V4;
typedef struct Mtx { V4 r[4]; } Mtx;
typedef struct Rec36 { s32 a; s32 b[8]; } Rec36;

extern s32 TargetRefIsActive_2e6f00(u8 *);
extern s32 TargetRefGetMatrix_2e6870(u8 *, Mtx *);
extern void VecNormalize_1cbb80(V4 *, V4 *);
extern s32 EvSwitchObjGetState_2f83f0(u8 *);
extern void EvSwitchRecMulMatrix_2f8700(u8 *, Mtx *, Mtx *);
extern void TargetRefDetachFromParent_2e5890(u8 *);
extern void TargetRefSetMatrix_2e5950(u8 *, Mtx *);
extern s32 EventRecGetId_2e5710(u8 *);
extern void EvScriptDispatchByName_2f9bb0(u8 *, Rec36 *, u8 *);
extern u8 D_00461DC8[];
extern u8 D_00461DD0[];

void EvSwitchObjApplyState_2f8240(u8 *p)
{
    Mtx m;
    Rec36 rec;
    u8 idx;

    if (TargetRefIsActive_2e6f00(p + 0xA0) != 0) {
        if (TargetRefGetMatrix_2e6870(p + 0xE0, &m) != 0) {
            VecNormalize_1cbb80(&m.r[0], &m.r[0]);
            VecNormalize_1cbb80(&m.r[1], &m.r[1]);
            VecNormalize_1cbb80(&m.r[2], &m.r[2]);
            idx = EvSwitchObjGetState_2f83f0(p);
            EvSwitchRecMulMatrix_2f8700(p + idx * 0x24 + 0x110, &m, &m);
            TargetRefDetachFromParent_2e5890(p + 0xA0);
            TargetRefSetMatrix_2e5950(p + 0xA0, &m);
            rec.a = -1;
            rec.b[0] = 0;
            rec.b[1] = 0;
            rec.b[2] = 0;
            rec.b[3] = 0;
            rec.b[4] = 0;
            rec.b[5] = 0;
            rec.b[6] = 0;
            rec.b[7] = 0;
            rec.a = EventRecGetId_2e5710(p);
            if (EvSwitchObjGetState_2f83f0(p) != 0) {
                EvScriptDispatchByName_2f9bb0(p, &rec, D_00461DC8);
            } else {
                EvScriptDispatchByName_2f9bb0(p, &rec, D_00461DD0);
            }
        }
    }
}
