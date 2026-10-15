#include "types.h"

extern s32 EvM05ChangeGetMotionName_352030(void *);
extern s32 ModelObjPlayMotionByName_1867a0(s32, s32, s32);
extern s32 EvTargetMapObjDisable_352560(s32);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 GameSceneSoundSlotGet_1d0de0(s32, s32);
extern s32 SoundSlotGetLoadedId_1d2160(s32);
extern s32 GameSceneSoundSlot6GetHandle_1d0780(s32);
extern s32 SoundStopEntry_1b8bc0(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0xE8];
    s32 mE8;
    s32 mEC;
    u8 pad0F0[0x28];
    s32 m118;
    u8 pad11C[0x4];
    s32 m120;
    u8 pad124[0x18];
    struct Obj1 *m13C;
};

struct Obj1 {
    u8 pad000[0x6C];
    s32 m6C;
};

void EvM05ChangeSuspend_350a10(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s32 t1;
    s32 r0;
    s32 rv3;
    struct Obj1 * t2;
    s32 t3;
    s32 r1;
    s32 r2;
    s32 l5;
    s32 l4;
    s32 r6;
    s32 t5;
    s32 r7;
    s32 r8;
    s32 r9;
    s32 rv12;
    s32 r10;
    s32 t6;
    s32 t7;
    s32 r11;

    t0 = p0->m13C;
    if (t0 != 0) {
        t1 = p0->m13C->m6C;
        if (t1 != 0) {
            r0 = EvM05ChangeGetMotionName_352030(p0);
            rv3 = 0;
            if (r0 != 0) {
                t2 = p0->m13C;
                t3 = p0->m13C->m6C;
                r1 = EvM05ChangeGetMotionName_352030(p0);
                r2 = ModelObjPlayMotionByName_1867a0(t3, r1, 1);
                rv3 = r2;
            }
        }
    }
    l5 = p0->mE8;
    l4 = 0;
    while (l4 < p0->mEC) {
        r6 = EvTargetMapObjDisable_352560(l5);
        l4 = (l4 + 1);
        l5 = (l5 + 0x140);
    }
    t5 = p0->m120;
    if (t5 >= 0) {
        r7 = GetCurrentScene_1f5be0();
        r8 = GameSceneSoundSlotGet_1d0de0(r7, 6);
        r9 = SoundSlotGetLoadedId_1d2160(r8);
        rv12 = r9;
        if (r9 == 0xDBBAA) {
            r10 = GameSceneSoundSlot6GetHandle_1d0780(r7);
            t6 = p0->m120;
            t7 = p0->m118;
            r11 = SoundStopEntry_1b8bc0(r10, t6, t7);
            rv12 = r11;
        }
        p0->m120 = -1;
    }
}
