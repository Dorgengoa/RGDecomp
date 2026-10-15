#include "types.h"

extern s32 GetGameData_1fede0(void);
extern s32 SlotRecordFindLatestMaybe_3e4c90(s32, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    s32 m00;
};

s32 SaveFindLatestSlotMaybe_37ba50(struct Obj0 *p0)
{
    struct Obj0 * rv0;
    s32 r1;
    s32 r2;

    rv0 = p0;
    if (rv0 != 0) {
        rv0->m00 = 0;
    }
    r1 = GetGameData_1fede0();
    if (r1 == 0) {
        return 0;
    }
    r2 = SlotRecordFindLatestMaybe_3e4c90(r1, rv0);
    return r2;
}
