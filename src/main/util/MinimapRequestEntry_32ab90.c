#include "types.h"

typedef struct {
    f32 x, y, z, w;
} V4;

extern s32 EntryListGetKind_323690(u8 *);
extern void MinimapStartCrossfade_32ab40(u8 *, f32);
extern void MinimapSelectNow_32ad20(u8 *, s32);
extern void MinimapCopyExplored_32bd50(void *, void *, void *, V4 *, V4 *, V4 *);
extern u8 D_00462458[];
extern u8 D_00462460[];
extern u8 D_00462468[];
extern f32 D_0047F2F0;
extern f32 D_0047F2F4;
extern f32 D_0047F2F8;
extern f32 D_0047F2FC;
extern f32 D_0047F300;
extern f32 D_0047F304;
extern f32 D_0047F308;
extern f32 D_0047F30C;
extern f32 D_0047F310;
extern f32 D_0047F314;
extern f32 D_0047F318;
extern f32 D_0047F31C;
extern f32 D_0047F320;
extern f32 D_0047F324;
extern f32 D_0047F328;
extern f32 D_0047F32C;
extern f32 D_0047F330;
extern f32 D_0047F334;
extern f32 D_0047F338;
extern f32 D_0047F33C;
extern f32 D_0047F340;
extern f32 D_0047F344;
extern f32 D_0047F348;
extern f32 D_0047F34C;

void MinimapRequestEntry_32ab90(u8 *arg0, s32 arg1)
{
    V4 a;
    V4 b;
    V4 c;
    V4 d;
    V4 e;
    V4 f;

    if (arg1 == 0) {
        return;
    }
    if (*(s32 *)(arg0 + 0x170) == 0) {
        MinimapSelectNow_32ad20(arg0, arg1);
        return;
    }
    if (*(s32 *)(arg0 + 0x170) == arg1) {
        return;
    }
    if (*(s32 *)(arg0 + 0x174) == arg1) {
        return;
    }
    *(s32 *)(arg0 + 0x174) = arg1;
    if (EntryListGetKind_323690(arg0 + 0x12C) == 1) {
        { f32 *p = (f32 *)&a; p[0] = D_0047F2F0; p[1] = D_0047F2F4; p[2] = D_0047F2F8; p[3] = D_0047F2FC; }
        { f32 *p = (f32 *)&b; p[0] = D_0047F300; p[1] = D_0047F304; p[2] = D_0047F308; p[3] = D_0047F30C; }
        { f32 *p = (f32 *)&c; p[0] = D_0047F310; p[1] = D_0047F314; p[2] = D_0047F318; p[3] = D_0047F31C; }
        { f32 *p = (f32 *)&d; p[0] = D_0047F320; p[1] = D_0047F324; p[2] = D_0047F328; p[3] = D_0047F32C; }
        { f32 *p = (f32 *)&e; p[0] = D_0047F330; p[1] = D_0047F334; p[2] = D_0047F338; p[3] = D_0047F33C; }
        { f32 *p = (f32 *)&f; p[0] = D_0047F340; p[1] = D_0047F344; p[2] = D_0047F348; p[3] = D_0047F34C; }
        MinimapCopyExplored_32bd50(D_00462458, D_00462460, D_00462468, &a, &b, &c);
        MinimapCopyExplored_32bd50(D_00462458, D_00462468, D_00462460, &d, &e, &f);
    }
    MinimapStartCrossfade_32ab40(arg0, 16.0f);
}
