#include "types.h"

extern f32 EvObjReset_2f9eb0(void *);
extern s32 GetMapMgr_201a90(void);
extern s32 MapSlotsFindBlockIdByName_1e44f0(s32, void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004629B8[];
extern u8 D_004629C8[];
extern u8 D_004629D8[];
extern u8 D_004629E8[];
extern u8 D_004629F8[];
extern u8 D_00462A08[];
extern u8 D_00462A18[];
extern f32 D_0047D2C0;
extern f32 D_0047D2C4;
extern f32 D_0047D2C8;

struct Obj0;

struct Obj0 {
    u8 pad000[0xE0];
    s32 mE0;
    s32 mE4;
    s32 mE8;
    s32 mEC;
    f32 mF0;
    f32 mF4;
    f32 mF8;
    s32 mFC;
    s32 m100;
    s32 m104;
    s32 m108;
    s32 m10C;
    s32 m110;
    s32 m114;
    s32 m118;
    s32 m11C;
    s32 m120;
    s32 m124;
    s32 m128;
    s32 m12C;
    s32 m130;
    s32 m134;
    s32 m138;
    s32 m13C;
    s32 m140;
    s32 m144;
    u8 m148;
    u8 pad149[0xF];
    s16 m158;
    s16 m15A;
};

s32 EvM05ChangeReset_3522b0(struct Obj0 *p0)
{
    f32 r0;
    f32 t0;
    f32 t1;
    f32 t2;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 r5;
    s32 r6;
    s32 r7;
    s32 r8;

    r0 = EvObjReset_2f9eb0(p0);
    p0->mE4 = 0;
    t0 = D_0047D2C0;
    p0->mE0 = 0;
    t1 = D_0047D2C4;
    p0->mE8 = 0;
    t2 = D_0047D2C8;
    p0->mEC = 0;
    p0->mF0 = t0;
    p0->mF4 = t1;
    p0->mF8 = t2;
    r1 = GetMapMgr_201a90();
    r2 = MapSlotsFindBlockIdByName_1e44f0(r1, D_004629B8, 0);
    p0->mFC = r2;
    r3 = MapSlotsFindBlockIdByName_1e44f0(r1, D_004629C8, 0);
    p0->m100 = r3;
    r4 = MapSlotsFindBlockIdByName_1e44f0(r1, D_004629D8, 0);
    p0->m104 = r4;
    r5 = MapSlotsFindBlockIdByName_1e44f0(r1, D_004629E8, 0);
    p0->m108 = r5;
    r6 = MapSlotsFindBlockIdByName_1e44f0(r1, D_004629F8, 0);
    p0->m10C = r6;
    r7 = MapSlotsFindBlockIdByName_1e44f0(r1, D_00462A08, 0);
    p0->m110 = r7;
    r8 = MapSlotsFindBlockIdByName_1e44f0(r1, D_00462A18, 0);
    p0->m114 = r8;
    p0->m13C = 0;
    p0->m140 = 0;
    p0->m144 = 0;
    p0->m118 = 0;
    p0->m11C = -1;
    p0->m120 = -1;
    p0->m124 = -1;
    p0->m128 = -1;
    p0->m12C = 0x3F800000;
    p0->m130 = 0x3F800000;
    p0->m134 = 0;
    p0->m138 = 0x3F800000;
    p0->m148 = 0;
    p0->m158 = -1;
    p0->m15A = 0;
    return r8;
}
