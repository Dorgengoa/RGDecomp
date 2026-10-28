/* rgp:protos */
#define RGP_SELF_MinimapSetRectExplored_32b9a0 1
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
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 *D_00449858[];
extern s32 D_004526E0[];
extern u8 D_00462540[];

void MinimapSetRectExplored_32b9a0(f32 *v0p, f32 *v1p, s32 flag, s32 arg3, s32 arg4) {
    u8 *p;
    s32 x;
    u8 *d;
    s32 t;
    f32 fz;
    s32 k;
    s32 i;
    void *q;
    f32 sp10C;
    f32 sp108;
    s32 w;
    s32 h;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
    s32 rot;
    s32 base;
    s32 yy;
    s32 xx;
    s32 px;
    s32 py;
    u32 addr;
    u8 fl;
    volatile u32 dst;
    volatile s32 buf;
    f32 a[4] __attribute__((aligned(16)));
    f32 b[4] __attribute__((aligned(16)));
    f32 vec[4] __attribute__((aligned(16)));

    p = ((u8 *)GetMinimapMgr_201a70());
    if (p == 0) {
        return;
    }
    x = *(s32 *)(p + 0x514);
    if (x == 0) {
        x = *(s32 *)(p + 0x510);
    }
    if (arg3 != 0) {
        x = arg3;
    }
    if (x == 0) {
        return;
    }
    t = MinimapGetPendingOrCurEntry_32a8f0(x);
    if (t == 0) {
        t = MinimapGetCurOrPendingEntry_32a920(x);
    }
    if (arg4 != 0) {
        t = arg4;
    }
    if (t == 0) {
        return;
    }
    d = ((u8 *)GetGameData_1fede0());
    fz = EntryGetScale_323b30(t);
    k = EntryGetTileSize_323ad0(t);
    MinimapGetEntryGridOrigin_323e40(x, t, &sp10C, &sp108);
    EntryGetGridSize_323bb0(t, &w, &h);
    if (v0p != 0 && v1p != 0) {
        q = GetMapMgr_201a90();
        if (q != 0) {
            q = MapSlotsFindBlockByName_1e4910(q, (u8 *)t + 0x34, 0);
            if (q != 0) {
                MapDataGetPosVec4_1e7740(q, vec);
            }
        }
        sp10C = sp10C + vec[0];
        sp108 = sp108 + vec[2];
        for (i = 0; i < 3; i++) {
            a[i] = v0p[i];
            b[i] = v1p[i];
        }
        MinimapWorldToMapXZ_32c280(a, fz, sp10C, sp108, (f32)k);
        MinimapWorldToMapXZ_32c280(b, fz, sp10C, sp108, (f32)k);
    } else {
        a[0] = 0.0f;
        a[2] = 0.0f;
        b[0] = (f32)w;
        b[2] = (f32)h;
    }
    x0 = a[0];
    y0 = a[2];
    x1 = b[0];
    y1 = b[2];
    rot = GetQuadrantAngle_324120(x);
    base = D_004526E0[MinimapGetKind_32a8c0(x)];
    base += EntryGetExploredOffset_3238f0(t);
    fl = flag;
    for (yy = y0; yy <= y1; yy++) {
        for (xx = x0; xx <= x1; xx++) {
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
                BitsetAssignBit_32c2f0(buf, addr, fl);
            }
        }
    }
}
