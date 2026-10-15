#include "types.h"

extern s32 GetCharaDataMgr_1fdb70(void);
extern void CharaDataReleaseSubRecsByKey_1ed750(s32, s32, s32);
extern void SoundBankRelease_1bb6e0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x7];
    u8 m07;
};

struct Obj1 {
    u8 pad000[0x4];
    s16 m04;
    u8 pad006[0x1];
    u8 m07;
};

void CharaResReleaseSounds_1effa0(s32 p0)
{
    struct Obj0 *l1;
    s32 l0;
    u8 t0;
    s32 r2;
    struct Obj1 *l3;
    s32 l4;
    u8 t1;
    s16 t2;

    l0 = 0;
    l1 = (struct Obj0 *)p0;
    while (l0 < 0x20) {
        t0 = l1->m07;
        if (t0 == 3) {
            return;
        }
        l0 = (l0 + 1);
        l1 = (struct Obj0 *)((u8 *)l1 + 0x68);
    }
    r2 = GetCharaDataMgr_1fdb70();
    l3 = (struct Obj1 *)p0;
    l4 = 0;
    do {
        t1 = l3->m07;
        if (t1 == 2) {
            t2 = l3->m04;
            CharaDataReleaseSubRecsByKey_1ed750(r2, t2, 5);
        }
        l3 = (struct Obj1 *)((u8 *)l3 + 0x68);
        l4 = (l4 + 1);
    } while (l4 < 0x20);
    SoundBankRelease_1bb6e0(5);
}
