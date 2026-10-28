/* rgp:protos */
#define RGP_SELF_MinimapSetAllExplored_32b6d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern void Fprintf_12f9a0(s32, void *, s32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 *D_00449858[];
extern s32 D_004526E0[];
extern u8 D_00462540[];

void MinimapSetAllExplored_32b6d0(s32 arg0, s32 arg1) {
    u8 *p;
    s32 x;
    u8 *d;
    s32 t;
    s32 n;
    u8 flag;
    f32 fz;
    s32 i;
    s32 e;
    s32 sp10C;
    s32 sp108;
    s32 w;
    s32 h;
    s32 W;
    s32 H;
    s32 rot;
    s32 base;
    s32 yy;
    s32 xx;
    s32 px;
    s32 py;
    u32 addr;
    volatile u32 dst;
    volatile s32 buf;

    p = ((u8 *)GetMinimapMgr_201a70());
    if (p == 0) {
        return;
    }
    x = *(s32 *)(p + 0x514);
    if (x == 0) {
        x = *(s32 *)(p + 0x510);
    }
    if (arg1 != 0) {
        x = arg1;
    }
    if (x == 0) {
        return;
    }
    d = ((u8 *)GetGameData_1fede0());
    t = ((s32)MinimapGetEntryList_32a8b0(x));
    if (t == 0) {
        return;
    }
    n = ((short)EntryListGetCount_323680(t));
    fz = 0.0f;
    flag = arg0;
    for (i = 0; i < n; i++) {
        e = EntryListSelectByIndex_323540(t, i);
        if (e == 0) {
            continue;
        }
        EntryGetScale_323b30(e);
        EntryGetTileSize_323ad0(e);
        MinimapGetEntryGridOrigin_323e40(x, e, &sp10C, &sp108);
        EntryGetGridSize_323bb0(e, &w, &h);
        W = (s32)(f32)w;
        H = (s32)(f32)h;
        rot = GetQuadrantAngle_324120(x);
        base = D_004526E0[MinimapGetKind_32a8c0(x)];
        base += EntryGetExploredOffset_3238f0(e);
        for (yy = fz; yy < H; yy++) {
            for (xx = fz; xx < W; xx++) {
                switch (rot) {
                case 0x5A:
                    py = xx;
                    px = (w - 1) - yy;
                    break;
                case 0xB4:
                    px = (w - 1) - xx;
                    py = (h - 1) - yy;
                    break;
                case 0x10E:
                    px = yy;
                    py = (h - 1) - xx;
                    break;
                case 0:
                default:
                    px = xx;
                    py = yy;
                    break;
                }
                addr = px + py * w;
                addr += base;
                if (px >= 0 && px < w && py >= 0 && py < h) {
                    dst = addr;
                    buf = *(s32 *)(d + 0x18) + 0x2D0;
                    if (addr >= 0x20000) {
                        Fprintf_12f9a0(*(s32 *)(D_00449858[0] + 0xC), D_00462540, px);
                        Abort_12de80();
                    }
                    BitsetAssignBit_32c2f0(buf, addr, flag);
                }
            }
        }
    }
}
