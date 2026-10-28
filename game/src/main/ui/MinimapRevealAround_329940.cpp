/* rgp:protos */
#line 1
#include "types.h"

struct Vec299 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
};

extern "C" {
void *memcpy(void *, const void *, u32);
s32 strcmp(const char *, const char *);
s32 EntryGetTileSize_323ad0(u8 *);
void EntryGetGridSize_323bb0(u8 *, s32 *, s32 *);
void EntryGetOrigin_323b10(u8 *, s32 *, s32 *);
void EntryGetRange_323af0(u8 *, s32 *, s32 *);
f32 EntryGetScale_323b30(u8 *);
void MinimapGetEntryGridOrigin_323e40(u8 *, u8 *, f32 *, f32 *);
u8 *GetGameData_1fede0(void);
s32 StateGetChapter_3cd5b0(s32);
s32 EntryListGetKind_323690(void *);
s32 EntryGetExploredOffset_3238f0(u8 *);
s32 AngleToQuadrant_323fd0(u8 *);
void Fprintf_12f9a0(s32, void *);
void Abort_12de80(void);
void BitsetAssignBit_32c2f0(s32, u32, s32);
extern struct rgp_anon_D_00449858 { u8 *p; u8 pad[0x1C]; } D_00449858;
extern s32 D_004526E0[];
extern char D_00462418[];
extern u8 D_00462540[];
}

static inline f32 fmul(f32 a, f32 b) { return a * b; }
#define BZERO(d, n) { u8 *p_ = (u8 *)(d); u32 n_ = (n); if (p_) while (n_) { *p_ = 0; n_--; p_++; } }

extern "C" void MinimapRevealAround_329940(u8 *self, u8 *obj, Vec299 *pos, s32 mode)
{
    f32 s;
    s32 a13C;
    s32 a138;
    s32 a134;
    s32 a130;
    s32 a12C;
    s32 a128;
    Vec299 p __attribute__((aligned(16)));
    Vec299 q __attribute__((aligned(16)));
    f32 ox;
    f32 oz;
    f32 fx;
    f32 fz;
    s8 on;
    s8 m;
    u8 *g;
    s32 lv;
    s32 base;
    s32 off;
    s32 w;
    s32 h;
    s32 x;
    s32 y;
    s32 bo;
    s32 dy;
    s32 dx;
    s32 xx;
    s32 yy;
    u32 idx;
    bool ok;
    volatile u32 vidx;
    volatile s32 tbl;

    if (obj == 0) {
        return;
    }
    switch (mode) {
    case 0:
        memcpy(self + 0x20, self, 0x10);
        break;
    case 1:
        memcpy(self + 0x20, self + 0x10, 0x10);
        break;
    }
    s = EntryGetTileSize_323ad0(obj);
    EntryGetGridSize_323bb0(obj, &a13C, &a138);
    EntryGetOrigin_323b10(obj, &a134, &a130);
    EntryGetRange_323af0(obj, &a12C, &a128);
    s = fmul(EntryGetScale_323b30(obj), s);
    BZERO(&p, 0x10);
    p.x = pos->x;
    p.y = pos->y;
    p.z = pos->z;
    BZERO(&q, 0x10);
    q.x = *(f32 *)(self + 0x20);
    q.y = *(f32 *)(self + 0x24);
    q.z = *(f32 *)(self + 0x28);
    MinimapGetEntryGridOrigin_323e40(self, obj, &ox, &oz);
    ox = ox + q.x;
    oz = oz + q.z;
    fx = (p.x - ox) / s;
    fz = (p.z - oz) / s;
    m = *(s8 *)(self + 0x11C);
    switch (m) {
    case 0:
        on = 1;
        break;
    case 2:
    case 1:
    default:
        on = 0;
        break;
    }
    if (!on) {
        return;
    }
    g = GetGameData_1fede0();
    lv = ((short)StateGetChapter_3cd5b0(*(s32 *)(g + 0x10)));
    base = D_004526E0[((short)EntryListGetKind_323690(self + 0x12C))];
    off = EntryGetExploredOffset_3238f0(obj);
    EntryGetGridSize_323bb0(obj, &w, &h);
    switch (AngleToQuadrant_323fd0(self)) {
    case 1:
        x = w - 1 - (s32)fz;
        y = (s32)fx;
        break;
    case 2:
        x = w - 1 - (s32)fx;
        y = h - 1 - (s32)fz;
        break;
    case 3:
        x = (s32)fz;
        y = h - 1 - (s32)fx;
        break;
    case 0:
    default:
        x = (s32)fx;
        y = (s32)fz;
        break;
    }
    bo = base + off;
    for (dy = -1; dy <= 1; dy++) {
        for (dx = -1; dx <= 1; dx++) {
            yy = y + dy;
            xx = x + dx;
            if (xx < 0 || xx >= w || yy < 0 || yy >= h) {
                continue;
            }
            idx = xx + bo + yy * w;
            ok = true;
            switch (((short)EntryListGetKind_323690(self + 0x12C))) {
            case 0:
                if (strcmp((char *)obj + 0x54, D_00462418) == 0 && lv < 6 && xx >= 0x18 && xx < 0x26) {
                    if (yy >= 2 && yy < 7) {
                        ok = false;
                    }
                    if (xx >= 0x1F && yy == 7) {
                        ok = false;
                    }
                }
                break;
            }
            if (ok) {
                vidx = idx;
                tbl = *(s32 *)(g + 0x18) + 0x2D0;
                if (idx >= 0x20000) {
                    Fprintf_12f9a0(*(s32 *)(D_00449858.p + 0xC), D_00462540);
                    Abort_12de80();
                }
                BitsetAssignBit_32c2f0(tbl, idx, 1);
            }
        }
    }
}
