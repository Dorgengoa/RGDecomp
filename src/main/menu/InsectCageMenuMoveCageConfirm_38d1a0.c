#include "types.h"

extern s32 InsectCageMenuHasCage_391080(s32);
extern s32 PlayMenuSe_289ef0(s32);
extern s32 InsectCageMenuGetMoveTargetCage_38d4e0(void);
extern s32 InsectCageGetType_3910c0(void);
extern s32 InsectCageMenuSetCursorVisible_389d00(s32);
extern s32 InsectCageMenuSelectEntry_390d40(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s16 m10;
};

s32 InsectCageMenuMoveCageConfirm_38d1a0(struct Obj0 *p0)
{
    s16 t0;
    s32 r0;
    s32 rv9;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 rv8;
    s32 r4;
    s32 r5;
    s32 r6;
    s32 r7;

    t0 = p0->m10;
    r0 = InsectCageMenuHasCage_391080(t0);
    rv9 = rv8;
    if (r0 == 0) {
        r1 = PlayMenuSe_289ef0(6);
        rv9 = 1;
    } else {
        r2 = InsectCageMenuGetMoveTargetCage_38d4e0();
        r3 = InsectCageGetType_3910c0();
        rv8 = 1;
        if (r2 == r3) {
            r4 = PlayMenuSe_289ef0(6);
            rv8 = 0;
        } else {
            r5 = PlayMenuSe_289ef0(5);
            r6 = InsectCageMenuSetCursorVisible_389d00(0);
            r7 = InsectCageMenuSelectEntry_390d40(0x753B, 1);
            rv8 = 1;
        }
        rv9 = rv8;
    }
    return rv9;
}
