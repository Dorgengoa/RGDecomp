#include "types.h"

extern s32 MapAreaReleaseAndReset_1e2d60(s32, s32, s32);
extern s32 MapIdListClearThunk_1e5ac0(s32);
extern s32 MapPendingLoadReset_1e5b40(s32);
extern s32 MapMgrGetHeap_1e5810(s32);
extern s32 MemStackHeapReinit_14de90(s32);
extern s32 MapMgrSkyUnload_1e2e40(s32);
extern s32 MapEnvSlotsInit_1e5f40(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapReset_1e2e60(s32 p0)
{
    s32 l1;
    s32 l0;
    s32 r2;
    s32 r3;
    s32 r4;
    s32 r5;
    s32 r6;
    s32 r7;
    s32 rv9;
    s32 r8;
    s32 r10;
    s32 r11;

    l1 = (p0 + 0x1928);
    l0 = 0;
    do {
        r2 = MapAreaReleaseAndReset_1e2d60(p0, l1, 1);
        l0 = (l0 + 1);
        l1 = (l1 + 0x1CC);
    } while (l0 < 4);
    r3 = MapIdListClearThunk_1e5ac0((p0 + 0x20B0));
    r4 = MapIdListClearThunk_1e5ac0((p0 + 0x2154));
    r5 = MapIdListClearThunk_1e5ac0((p0 + 0x21F8));
    r6 = MapPendingLoadReset_1e5b40((p0 + 0x20AC));
    r7 = MapMgrGetHeap_1e5810(p0);
    rv9 = r7;
    if (r7 != 0) {
        r8 = MemStackHeapReinit_14de90(r7);
        rv9 = r8;
    }
    r10 = MapMgrSkyUnload_1e2e40(p0);
    r11 = MapEnvSlotsInit_1e5f40((p0 + 0x68));
    return r11;
}
