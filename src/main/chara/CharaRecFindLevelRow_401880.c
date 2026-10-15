#include "types.h"

/* Known-positive sibling shape of MapAreaModelFindModelCfgEntry_1896e0 (byte-identical, in cunits). */

extern s32 TableFindFloorKey_401610(s32, s32, s32);

struct Obj0;

struct Obj0 {
    u8 pad000[0x30];
    s32 m30;
};

s32 CharaRecFindLevelRow_401880(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 t0;
    s32 r0;

    t0 = p0->m30;
    if (t0 != 0) {
        r0 = TableFindFloorKey_401610(t0, p1, p2);
        return r0;
    }
    return 0;
}
