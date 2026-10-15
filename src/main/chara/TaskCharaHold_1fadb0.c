#include "types.h"

extern void * GetGameData_1fede0(void);
extern s32 ActionMgrFindById_233b50(void *, s32);
extern void CharaGetHoldDir_2143b0(s32, void *);
extern void CharaSetDirNormalizedMaybe_213b30(s32, void *);
extern void CharaSetMoveDirMaybe_213b00(s32, void *);
extern s32 CharaGetHoldFlags_214280(s32);
extern void CharaSetFlags_212470(s32, s32);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004B8680[];

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x18];
    struct Obj1 *m18;
};

struct Obj1 {
    u8 pad000[0x18E];
    s16 m18E;
};

s32 TaskCharaHold_1fadb0(void)
{
    u128 v20;
    struct Obj0 *r0;
    struct Obj1 * t0;
    s16 t1;
    s32 r1;
    s32 r5;

    r0 = (struct Obj0 *)GetGameData_1fede0();
    t0 = r0->m18;
    t1 = r0->m18->m18E;
    r1 = ActionMgrFindById_233b50(D_004B8680, t1);
    if (r1 != 0) {
        CharaGetHoldDir_2143b0(r1, &v20);
        CharaSetDirNormalizedMaybe_213b30(r1, &v20);
        CharaSetMoveDirMaybe_213b00(r1, &v20);
        r5 = CharaGetHoldFlags_214280(r1);
        CharaSetFlags_212470(r1, (r5 & 3));
    }
}
