#include "types.h"

/* Known-positive sibling shape of MapBlockInit_1e0100 (byte-identical, in cunits). */

extern void MapDataInit_1e7c50(s32);
extern void Nop_1ed0b0(s32);
extern void Nop_1ed090(s32);
extern void MapDataSetType_1e7430(s32, s32);
extern void MapDataClearLoadStateThunk_1e7c30(s32);

void MapShareInit_1ed040(s32 p0)
{
    MapDataInit_1e7c50(p0);
    Nop_1ed0b0((p0 + 0x54));
    Nop_1ed090((p0 + 0x55));
    MapDataSetType_1e7430(p0, 0x3);
    MapDataClearLoadStateThunk_1e7c30(p0);
}
