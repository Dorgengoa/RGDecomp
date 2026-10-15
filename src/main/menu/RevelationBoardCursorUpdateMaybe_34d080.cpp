#pragma optimization_level 3
#include "types.h"
#pragma divbyzerocheck on
#pragma inline_intrinsics off

extern "C" {

typedef struct Sub {
    u8 pad0[0x26];
    s16 x26;
} Sub;

typedef struct Game {
    u8 pad0[0xC];
    Sub *xC;
    u8 pad10[0x8];
    s32 x18;
} Game;

typedef struct Cur {
    s32 x0;
    u8 pad4[0x4];
    s32 x8;
    u8 padC[0x4];
    s16 x10;
    s16 x12;
    s16 x14;
    s16 x16;
    u8 pad18[0x756];
    s16 x76E;
    u8 pad770[0x4];
    f32 x774;
} Cur;

extern f32 Sinf_128fd0(f32);
extern s32 PadIsTriggered_1839f0(void *, s32);
extern s32 PadIsHeld_183a20(void *, s32);
extern f32 PadGetAnalogLYNorm_183a50(void *);
extern f32 PadGetAnalogLXNorm_183af0(void *);
extern s32 PadGetAnalogLY_184050(void *);
extern s32 PadGetAnalogLX_1840d0(void *);
extern void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
extern Game *GetGameData_1fede0(void);
extern void UiGetWidgetPos_2910a0(s32, s32, s32 *, s32 *);
extern void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);
extern void UiSetWidgetPos_290f60(s32, s32, s32, s32);
extern void RevelationBoardPixelToCell_34cfd0(Cur *, s32 *, s32 *, s32, s32, s32, s32);
extern void RevelationBoardCellToPixel_34d010(Cur *, s32 *, s32 *, s32, s32, s32, s32, f32, f32);
extern s16 PartyMenuCursorGet_3c0760(s32, s32);
extern s32 RevelationBoardSearchDirMaybe_3eaa50(Game *, s32, s32, s32, s32, s32, s32);
extern s32 RevelationBoardFindMarkedEntryMaybe_3eaca0(Game *, s32);
extern u8 *RevelationBoardGetCells_3eb510(Game *, s32);
extern s32 abs(s32);
extern f32 D_0047D1FC;
extern f32 D_0047D3B8;
extern u8 D_004B2570[0x400];

}

static inline void Split(Cur *c, s32 v, s32 n) {
    c->x12 = v / n;
    c->x10 = v % n;
}

extern "C" s32 RevelationBoardCursorUpdateMaybe_34d080(Cur *self, s32 arg1, s32 arg2, s32 arg3) {
    s32 px;
    s32 py;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 e;
    s32 f;
    s32 g1;
    s32 g2;
    s32 h1;
    s32 h2;
    s32 ret;
    s16 ox;
    s16 oy;
    f32 wob;
    f32 t;
    Game *g;
    s32 cell;
    s32 exp;
    s32 r;
    s16 v;
    s32 lo;
    s32 hi;
    s32 y;
    s32 x;
    f32 fx;
    s32 lim1;
    s32 lim2;
    s32 dir;
    bool changed;
    u8 *p;
    s32 k;

    ret = 0;
    if (self->x76E != 0) {
        return 0;
    }
    if (self->x0 != 0) {
    ox = self->x10;
    oy = self->x12;
    UiGetWidgetPos_2910a0(self->x0, 0x47, &px, &py);
    wob = 6.0f * Sinf_128fd0(self->x774);
    t = self->x774 + D_0047D3B8;
    self->x774 = t;
    if (t > 0.0f) {
        self->x774 = t - D_0047D1FC;
    }
    g = GetGameData_1fede0();
    if (arg2 != -1) {
        if (arg3 != 0) {
            cell = RevelationBoardFindMarkedEntryMaybe_3eaca0(g, arg2);
            if (g->xC->x26 == 1) {
                exp = 0xDD;
                r = RevelationBoardSearchDirMaybe_3eaa50(g, arg2, 8, 0xD, 1, 0xC, 0xC);
                if (r == exp) {
                    exp = 0xF6;
                    r = RevelationBoardSearchDirMaybe_3eaa50(g, arg2, 9, 0xC, 0, 0xC, 0xC);
                    if (r == exp) {
                        exp = 0xC2;
                        r = RevelationBoardSearchDirMaybe_3eaa50(g, arg2, 7, 0xC, 3, 0xC, 0xC);
                        if (r == exp) {
                            exp = 0xDB;
                            r = RevelationBoardSearchDirMaybe_3eaa50(g, arg2, 8, 0xB, 2, 0xC, 0xC);
                        }
                    }
                }
                v = PartyMenuCursorGet_3c0760(g->x18, arg1 + 7);
                { u16 w = v; lo = (u8)w; hi = (u8)(w >> 8); }
                if (r != exp) {
                    Split(self, r, 26);
                } else if (lo == 0 && hi == 0) {
                    Split(self, cell, 26);
                } else {
                    self->x10 = lo;
                    self->x12 = hi;
                }
            } else {
                if (RevelationBoardSearchDirMaybe_3eaa50(g, arg2, 0, 0, 3, 0xC, 0xC) == 0) {
                    RevelationBoardSearchDirMaybe_3eaa50(g, arg2, 0, 0, 2, 0xC, 0xC);
                }
                Split(self, cell, 26);
            }
            x = self->x10;
            y = self->x12;
            a = 0;
            b = 0;
            RevelationBoardCellToPixel_34d010(self, &a, &b, x, y, 0, 0, 0.0f, 0.0f);
            if (a < 0x26) {
                a = 0x26;
            } else if (a > 0x416) {
                a = 0x416;
            }
            if (b < 0x26) {
                b = 0x26;
            } else if (b > 0x306) {
                b = 0x306;
            }
            px = -(a - 0x100);
            py = -(b - 0xE0);
            if (px < -0x222) {
                px = -0x222;
            } else if (px > 0) {
                px = 0;
            }
            if (py < -0x1C0) {
                py = -0x1C0;
            } else if (py > 0x50) {
                py = 0x50;
            }
            UiSetWidgetPos_290f60(self->x0, 0x47, px, py);
            c = 0;
            d = 0;
            RevelationBoardCellToPixel_34d010(self, &c, &d, x, y, px, py, 0.0f, 0.0f);
            self->x14 = c;
            self->x16 = d;
            UiSetWidgetPos_290f60(self->x0, 0x4F, c + (s32)wob, d + (s32)wob);
        } else if (abs(PadGetAnalogLX_1840d0(D_004B2570)) >= 0x15 || abs(PadGetAnalogLY_184050(D_004B2570)) > 0x14) {
            fx = PadGetAnalogLXNorm_183af0(D_004B2570);
            t = PadGetAnalogLYNorm_183a50(D_004B2570);
            self->x14 += (s16)(s32)(8.0f * fx);
            self->x16 += (s16)(s32)(8.0f * t);
            wob = 0.0f;
            e = 0;
            f = 0;
            RevelationBoardPixelToCell_34cfd0(self, &e, &f, self->x14, self->x16, px, py);
            self->x10 = e;
            self->x12 = f;
        } else {
            lim1 = 0xA;
            lim2 = 0xE;
            if (PadIsHeld_183a20(D_004B2570, 2) != 0 && PadIsHeld_183a20(D_004B2570, 1) != 0) {
                lim1 = 0xC;
                lim2 = 0xC;
            } else if (PadIsHeld_183a20(D_004B2570, 2) != 0) {
                lim1 = 0xB;
                lim2 = 0xC;
            }
            dir = -1;
            if (PadIsTriggered_1839f0(D_004B2570, 0x1000) != 0) {
                dir = 0;
            } else if (PadIsTriggered_1839f0(D_004B2570, 0x8000) != 0) {
                dir = 1;
            } else if (PadIsTriggered_1839f0(D_004B2570, 0x2000) != 0) {
                dir = 2;
            } else if (PadIsTriggered_1839f0(D_004B2570, 0x4000) != 0) {
                dir = 3;
            }
            if (dir != -1) {
                Split(self, RevelationBoardSearchDirMaybe_3eaa50(g, arg2, self->x12, self->x10, dir, lim1, lim2), 26);
                if (ox != self->x10 || oy != self->x12) {
                    SoundPlayScaledVolume_1b9520(self->x8, 4, 0, 1.0f);
                }
            }
            g1 = 0;
            g2 = 0;
            RevelationBoardCellToPixel_34d010(self, &g1, &g2, self->x10, self->x12, px, py, wob, wob);
            self->x14 = g1;
            self->x16 = g2;
        }
    }
    changed = false;
    if (self->x10 <= 0) {
        self->x10 = 1;
        changed = true;
    } else if (self->x10 > 0x18) {
        self->x10 = 0x18;
        changed = true;
    }
    if (self->x12 <= 0) {
        self->x12 = 1;
        changed = true;
    } else if (self->x12 > 0x10) {
        self->x12 = 0x10;
        changed = true;
    }
    if (changed) {
        h1 = 0;
        h2 = 0;
        RevelationBoardCellToPixel_34d010(self, &h1, &h2, self->x10, self->x12, px, py, wob, wob);
        self->x14 = h1;
        self->x16 = h2;
    }
    if (ox != self->x10 || oy != self->x12) {
        ret = 1;
    }
    if (arg3 == 0) {
        UiMoveWidgetUniform_290f50(self->x0, 0x4F, (s32)((f32)self->x14 + wob), (s32)((f32)self->x16 + wob), 0, 0.25f);
    }
    p = RevelationBoardGetCells_3eb510(g, arg2);
    y = self->x12;
    x = self->x10;
    p += (x + y * 26) * 4;
    if (p != 0) {
        k = (u8)(((u64)p[1] << 59) >> 60);
        if (k == 0xB) {
            goto draw;
        }
        if (k == 0xC) {
        draw:
            UiSetWidgetPos_290f60(self->x0, 0x5A, px + x * 0x2A - 0x3C, py + y * 0x2E - 5);
            UiSetWidgetPos_290f60(self->x0, 0x5C, (s32)(wob / 2.0f + (f32)(px + self->x10 * 0x2A - 7)), py + self->x12 * 0x2E + 0x10);
        }
    }
    }
    return ret;
}
