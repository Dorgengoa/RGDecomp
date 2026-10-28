/* rgp:protos */
#define RGP_SELF_MinimapCopyExplored_32bd50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern void Fprintf_12f9a0(s32, void *);
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
extern s32 strcmp(const char *, const char *);
extern u8 *D_00449858[];
extern s32 D_004526E0[];
extern u8 D_00462540[];

void MinimapCopyExplored_32bd50(s32 arg0, char *arg1, char *arg2, f32 *arg3, f32 *arg4, f32 *arg5) {
    s32 m;
    s32 o;
    s32 e1;
    s32 e2;
    u8 *d;
    s32 base;
    s32 t;
    u8 flags;
    s32 n;
    s32 i;
    u8 f;
    s32 x0;
    s32 z0;
    s32 x2;
    s32 z2;
    s32 w;
    s32 h;
    s32 W;
    s32 H;
    s32 yy;
    s32 xx;
    s32 zz;
    s32 px;
    s32 fx;
    s32 fy;
    s32 py;
    s32 r;
    u32 addr;
    volatile u32 dst;
    volatile s32 buf;

    m = ((s32)GetMinimapMgr_201a70());
    e1 = 0;
    e2 = 0;
    d = ((u8 *)GetGameData_1fede0());
    if (arg0 == 0 || arg1 == 0 || arg2 == 0) {
        return;
    }
    o = MinimapMgrFindSlotByName_322340(m, arg0);
    if (o == 0) {
        return;
    }
    base = D_004526E0[MinimapGetKind_32a8c0(o)];
    t = ((s32)MinimapGetEntryList_32a8b0(o));
    if (t == 0) {
        return;
    }
    flags = 0;
    n = ((short)EntryListGetCount_323680(t));
    for (i = 0; i < n; i++) {
        f = flags;
        if (!(f & 1)) {
            e1 = EntryListSelectByIndex_323540(t, i);
        }
        if (!(f & 2)) {
            e2 = EntryListSelectByIndex_323540(t, i);
        }
        if (e1 != 0 && strcmp((char *)(e1 + 0x54), arg2) == 0) {
            flags |= 1;
        }
        if (e2 != 0 && strcmp((char *)(e2 + 0x54), arg1) == 0) {
            flags |= 2;
        }
    }
    if (e1 != 0 && e2 != 0) {
        MinimapWorldPosToGrid_32c0f0(arg4, arg4, o, e1);
        MinimapWorldPosToGrid_32c0f0(arg5, arg5, o, e1);
        MinimapWorldPosToGrid_32c0f0(arg3, arg3, o, e2);
        x0 = arg4[0];
        z0 = arg4[2];
        x2 = arg3[0];
        z2 = arg3[2];
        w = (s32)arg5[0] - x0;
        h = (s32)arg5[2] - z0;
        EntryGetGridSize_323bb0(e2, &W, &H);
        base += EntryGetExploredOffset_3238f0(e2);
        for (yy = 0; yy < h; yy++) {
            for (xx = 0; xx < w; xx++) {
                fy = yy + z0;
                py = yy + z2;
                fx = xx + x0;
                px = xx + x2;
                if (px >= 0 && px < W && py >= 0 && py < H) {
                    addr = px + base + py * W;
                    r = MinimapIsCellExploredXZ_3254f0(o, e1, 0, (f32)fx, (f32)fy);
                    dst = addr;
                    buf = *(s32 *)(d + 0x18) + 0x2D0;
                    if (addr >= 0x20000) {
                        Fprintf_12f9a0(*(s32 *)(D_00449858[0] + 0xC), D_00462540);
                        Abort_12de80();
                    }
                    BitsetAssignBit_32c2f0(buf, addr, r != 0);
                }
            }
        }
    }
}
