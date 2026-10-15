#include "types.h"

typedef struct Point3 {
    f32 x;
    f32 y;
    f32 z;
} Point3;

typedef struct Obj18 {
    u8 pad18[0x18];
    s32 unk18;
} Obj18;

typedef struct {
    u8 pad0[0xC];
    s32 unkC;
} Dbg;

typedef struct {
    volatile s32 base;
    volatile u32 off;
} Req;

void Abort_12de80(void);
void Fprintf_12f9a0(s32, void *);
Obj18 *GetGameData_1fede0(void);
s32 EntryListGetKind_323690(void *);
s32 EntryGetExploredOffset_3238f0(s32);
void EntryGetGridSize_323bb0(s32, s32 *, s32 *);
s32 BitArray64Test_32c340(s32, u32);
extern Dbg *D_00449858[4];
extern s32 D_004526E0[];
extern u8 D_00462510[];

s32 MinimapIsCellExplored_325550(u8 *arg0, Point3 *arg1, s32 arg2, s32 arg3)
{
    s32 w;
    s32 h;
    Req req;
    s32 x;
    s32 y;
    s32 c;
    s32 r;
    s32 off;
    s32 base;
    u32 addr;
    Obj18 *g;

    if (arg2 == 0) {
        return 0;
    }
    g = GetGameData_1fede0();
    x = arg1->x;
    y = arg1->z;
    off = EntryGetExploredOffset_3238f0(arg2);
    base = D_004526E0[EntryListGetKind_323690(arg0 + 0x12C)];
    EntryGetGridSize_323bb0(arg2, &w, &h);
    switch (arg3) {
    case 1:
        c = (w - 1) - y;
        r = x;
        break;
    case 2:
        c = (w - 1) - x;
        r = (h - 1) - y;
        break;
    case 3:
        c = y;
        r = (h - 1) - x;
        break;
    case 0:
    default:
        c = x;
        r = y;
        break;
    }
    if (c >= 0 && c < w && r >= 0 && r < h) {
        req.base = g->unk18 + 0x2D0;
        addr = c + (base + off) + r * w;
        req.off = addr;
        if (!(addr < 0x20000)) {
            Fprintf_12f9a0(D_00449858[0]->unkC, D_00462510);
            Abort_12de80();
        }
        if (BitArray64Test_32c340(req.base, addr) != 0) {
            return 1;
        }
    }
    return 0;
}
