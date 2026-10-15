#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

extern s32 GetEntryTableGlobal_32c2e0(void);
extern s32 EntryTableGetCurrent_323530(s32);
extern s32 VariantGetInt_15f780(E8 *);
extern void EntrySetGridSize_323bd0(s32, s32, s32);
extern s32 EntryListGetHeap_3237d0(s32);
extern void EntryAllocGrid_323b40(s32, s32);
extern void EntryListSetCellCursor_323380(s32, s32);

s32 EntryScriptCmdSetGrid_322c20(E8 *p0)
{
    s32 o1;
    s32 o2;
    f32 x;
    f32 y;
    s32 r;

    o1 = GetEntryTableGlobal_32c2e0();
    if (o1 == 0) {
        return 0;
    }
    o2 = EntryTableGetCurrent_323530(o1);
    if (o2 == 0) {
        return 0;
    }
    x = VariantGetInt_15f780(p0++);
    y = VariantGetInt_15f780(p0);
    EntrySetGridSize_323bd0(o2, (s32)x, (s32)y);
    r = EntryListGetHeap_3237d0(o1);
    EntryAllocGrid_323b40(o2, r);
    EntryListSetCellCursor_323380(o1, 0);
    return 1;
}
