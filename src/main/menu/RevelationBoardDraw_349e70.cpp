#include "types.h"

struct Sys1 {
    u8 pad0[0x14];
    s32 f14;
};

struct Cell {
    u32 id : 6;
    u32 pad6 : 3;
    u32 kind : 4;
    u32 conn : 8;
    u32 conn2 : 8;
    u32 rest : 3;
};

struct Map {
    Cell cells[1];
};

struct CState {
    u32 f0 : 1;
    u32 f1 : 1;
    u32 m1 : 8;
    u32 m2 : 8;
    u32 rest : 14;
};

struct Hit {
    u8 pad0[0x16];
    s16 v;
};

struct Tag {
    u8 pad0[2];
    u8 x2;
};

struct Ent {
    u8 pad0[0x2C];
    s16 x2C;
};

struct Rc {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 u;
    s16 v;
    s16 uw;
    s16 vh;
    u8 pad10[0x10];
};

struct Win {
    s32 h;
    u8 pad4[0x1C - 0x4];
    CState cs[18 * 26];
    u8 pad76C[2];
    s16 mode;
    s16 timer;
    u8 pad772[0x778 - 0x772];
    f32 f778;
};

extern "C" {
Sys1 *GetGameData_1fede0(void);
Map *RevelationBoardGetCells_3eb510(Sys1 *, s32);
s32 GetDrawCtxNameTable_15de40(void);
s32 GetDrawCtx_15de80(void);
s32 DrawListBeginPrim_141b00(s32);
void DrawListEndPrim_141a20(s32);
void DrawListAddTexLoad_1418c0(s32, s32, f32);
void GsPktSetOriginMode_13e2f0(s32, s32);
void GsPktSetAntialias_13e390(s32, s32);
void GsPktSetGouraud_13e3b0(s32, s32);
void GsPktSetTexFilter_13e3d0(s32, s32);
void GsPktSetUseUV_13e3e0(s32, s32);
void GsPktSetTextured_13e400(s32, s32);
void GsPktSetZWriteMask_13e430(s32, s32);
void GsPktEnableZTest_13e460(s32, s32);
void GsPktEnableAlphaTest_13e4d0(s32, s32);
void GsPktSetBlendMode_13e4f0(s32, s32);
void GsPktSetAlphaBlend_13e500(s32, s32);
s32 NameTableFindByName_159fb0(s32, void *, s32);
f32 *UiGetWidgetColor_2904b0(s32, s32);
void GsPktOpenPrim_13f730(s32, s32);
void GsPktClose_13f5b0(s32);
void GsPktSetTexture_13ec00(s32, s32);
void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
void GsPktSetUV_13ed60(s32, s32, s32);
void GsPktSetXYZPixel_13f110(s32, s32, s32, s32);
Hit *RevelationBoardCellGetEntry_3eae10(Sys1 *, s32, Cell *);
Tag *RevelationBoardCellGetValue_3eade0(Sys1 *, s32, Cell *);
Ent *RevelationBoardCellGetItemRec_3ead00(Sys1 *, s32, Cell *);
s32 RevelationBoardCellLinkMask_409b50(Cell *, s32, u8 *);
f32 Sinf_128fd0(f32);
f32 Cosf_128d30(f32);
void UiSetItemIconUv_288e50(Rc *, s32, s32, s32);
void RevelationBoardDrawSprite_34c170(Win *, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void RevelationBoardPktSetColorLerp_34ce10(Win *, s32, f32, f32, f32, f32, f32, f32, f32, f32, f32);
void RevelationBoardDrawItemBalloonMaybe_349920(Win *, s32, s32, s32);
}

extern "C" u8 D_00462900[];
extern "C" u8 D_00462908[];
extern "C" s16 D_004539F4[];
extern "C" s16 D_004539F6[];
extern "C" s16 D_00453A5C[];
extern "C" s16 D_00453A5E[];
extern "C" s16 D_00453A64[];
extern "C" s16 D_00453A66[];
extern "C" s16 D_00453A6C[];
extern "C" s16 D_00453A6E[];
extern "C" f32 D_0047D400 __attribute__((section(".sdata")));
extern "C" f32 D_0047D440 __attribute__((section(".sdata")));
extern "C" f32 D_0047D498 __attribute__((section(".sdata")));

static inline void DrawSpr(Win *w, s32 ctx, u8 spr, s32 x, s32 y, f32 rot)
{
    RevelationBoardDrawSprite_34c170(w, ctx, spr, x - 1, y - 1, D_004539F4[spr * 4], D_004539F6[spr * 4], rot,
                 128.0f, 128.0f, 128.0f, 128.0f, 255.0f, 255.0f, 255.0f, 255.0f);
}

static inline u16 M1(CState *c)
{
    return c->m1;
}

static inline bool Owned(Cell *c, Hit *h, s32 i)
{
    return c != 0 && h != 0 && c->kind >= 11 && h->v == i;
}

extern "C" void RevelationBoardDraw_349e70(Win *w, s32 id, s32 x0, s32 y0)
{
    Sys1 *s1;
    Map *map;
    s32 sb;
    s32 tb;
    s32 ctx;
    f32 *c;
    s32 col4[4];
    s32 pass2;
    s32 i;
    s32 k2;
    s32 u1, v1;
    s32 k;
    s32 idx;
    s32 conn;
    s32 conn2;
    s32 kind0;
    s32 n;
    s32 pass;
    s32 m2b;
    bool hl;
    bool sel;
    bool ok2;
    s32 s2;
    bool ok5;
    s32 s5;
    bool ok7;
    s32 s7;
    Cell *cell2;
    s32 kind02;
    s32 n2;
    s32 alpha;
    s32 y5, ym1, y2, y7, y8, y12, y38;
    s32 x9, xm1, x2, x10, x6, x8, x34;
    s32 u13, v13;
    s32 row;
    s32 col;
    s32 px, py;

    s1 = GetGameData_1fede0();
    if (s1 == 0) return;
    map = RevelationBoardGetCells_3eb510(s1, id);
    if (map == 0) return;
    sb = GetDrawCtxNameTable_15de40();
    tb = GetDrawCtx_15de80();
    ctx = DrawListBeginPrim_141b00(tb);
    GsPktSetBlendMode_13e4f0(ctx, 1);
    GsPktSetAlphaBlend_13e500(ctx, 1);
    GsPktSetAntialias_13e390(ctx, 0);
    GsPktEnableAlphaTest_13e4d0(ctx, 1);
    GsPktEnableZTest_13e460(ctx, 0);
    GsPktSetTextured_13e400(ctx, 1);
    GsPktSetUseUV_13e3e0(ctx, 1);
    GsPktSetOriginMode_13e2f0(ctx, 0);
    GsPktSetTexFilter_13e3d0(ctx, 0);
    GsPktSetZWriteMask_13e430(ctx, 1);
    GsPktSetGouraud_13e3b0(ctx, 0);
    NameTableFindByName_159fb0(sb, D_00462900, 0x32D);
    c = UiGetWidgetColor_2904b0(w->h, 0x47);
    for (i = 0; i < 4; i++) {
        col4[i] = (s32)(128.0f * c[i]);
    }
    k = 0;
    GsPktOpenPrim_13f730(ctx, 6);
    for (row = 0; row < 18; row++) {
        s32 y = y0 + row * 46;
        y5 = y + 5;
        ym1 = y - 1;
        y2 = y + 2;
        y7 = y + 7;
        y8 = y + 8;
        y12 = y + 12;
        y38 = y + 38;
        s32 by = y - 20;
        s32 by2 = y - 16;
        for (col = 0; col < 26; col++) {
            Cell *cell;
            CState *cs;
            Hit *hit;
            s32 cx;
            s32 x;
            s32 bx, bx2;
            idx = k++;
            cell = &map->cells[idx];
            cs = &w->cs[idx];
            hit = RevelationBoardCellGetEntry_3eae10(s1, id, cell);
            conn = cell->conn;
            conn2 = cell->conn2;
            kind0 = cell->kind;
            cx = col * 42;
            GsPktSetTexture_13ec00(ctx, NameTableFindByName_159fb0(sb, D_00462900, 0x32D));
            n = 1;
            {
                s32 m = w->mode;
                if (m == 5) goto two1;
                if (m == 6) goto two1;
                if (m == 7) goto two1;
                if (m == 8) {
                two1:
                    n = 2;
                }
            }
            x = x0 + cx;
            x9 = x + 9;
            xm1 = x - 1;
            x2 = x + 2;
            x10 = x + 10;
            x6 = x + 6;
            x8 = x + 8;
            x34 = x + 34;
            bx = x - 20;
            bx2 = x - 15;
            for (pass = 1; pass <= n; pass++) {
                f32 rot;
                s32 mask;
                s32 kind;
                s32 v;
                rot = 0.0f;
                m2b = conn2;
                mask = conn;
                kind = kind0;
                if (w->mode == 5) {
                    if (pass == 1) {
                        mask &= ~(cs->m1 & 0xFFFF);
                        m2b &= ~(cs->m1 & 0xFFFF);
                        if (cs->f0) kind = 0;
                    } else if (pass == 2) {
                        mask = cs->m1 & 0xFFFF;
                        m2b = mask;
                        if (cs->f0) kind = 14; else kind = 0;
                        rot = Sinf_128fd0(D_0047D400 * (f32)w->timer);
                    }
                }
                if (w->mode == 6) {
                    if (pass == 1) {
                        mask &= ~(cs->m1 & 0xFFFF);
                        m2b &= ~(cs->m1 & 0xFFFF);
                        if (cs->f0) kind = 0;
                    } else if (pass == 2) {
                        mask = cs->m1 & 0xFFFF;
                        m2b = mask;
                        if (cs->f0) kind = 14; else kind = 0;
                        rot = D_0047D440 + Sinf_128fd0(D_0047D498 * (f32)w->timer) / 4.0f;
                    }
                }
                if (w->mode == 7) {
                    if (pass == 1) {
                        mask &= ~(cs->m1 & 0xFFFF);
                        m2b &= ~(cs->m1 & 0xFFFF);
                        if (cs->f0) kind = 0;
                    } else if (pass == 2) {
                        mask = cs->m1 & 0xFFFF;
                        m2b = mask;
                        if (cs->f0) kind = 14; else kind = 0;
                        rot = Cosf_128d30(D_0047D498 * (f32)w->timer);
                    }
                } else if (w->mode == 8) {
                    if (cs->f0) kind = 14;
                    m2b |= cs->m1;
                    if (pass == 1) {
                        mask &= ~cs->m2;
                        m2b &= ~cs->m2;
                        if (cs->f1) kind = 0;
                    } else if (pass == 2) {
                        mask = cs->m2;
                        m2b = mask;
                        if (cs->f1) {
                            if (kind == 10) kind = 11;
                        } else {
                            kind = 0;
                        }
                        rot = Cosf_128d30(D_0047D498 * (f32)w->timer);
                    }
                }
                hl = false;
                v = m2b | cs->m1;
                switch (kind) {
                case 1:
                    hl = (v & 2) != 0;
                    break;
                case 3:
                    hl = (v & 8) != 0;
                    break;
                case 4:
                    hl = (v & 0x10) != 0;
                    break;
                case 2:
                    hl = (v & 0x40) != 0;
                    break;
                }
                sel = false;
                if (hit != 0 && kind >= 11 && hit->v == idx) sel = true;
                if (kind != 0) {
                    if (kind == 10) {
                        RevelationBoardDrawSprite_34c170(w, ctx, 0, x9, y5, -1, -1, rot, 128.0f, 128.0f, 128.0f, 128.0f,
                                     255.0f, 255.0f, 255.0f, 255.0f);
                    }
                    if ((u32)(kind - 11) < 3) {
                        RevelationBoardDrawSprite_34c170(w, ctx, 12, xm1, ym1, 0x2C, 0x30, rot, 128.0f, 128.0f, 128.0f, 128.0f,
                                     255.0f, 255.0f, 255.0f, 255.0f);
                    }
                    if (kind == 14) {
                        RevelationBoardDrawSprite_34c170(w, ctx, 12, x, y, 0x2A, 0x2E, rot, 128.0f, 112.0f, 96.0f, 56.0f,
                                     255.0f, 255.0f, 255.0f, 255.0f);
                    }
                    if ((u32)(kind - 10) < 4) {
                        RevelationBoardDrawSprite_34c170(w, ctx, 1, x, y, -1, -1, rot, 128.0f, 128.0f, 128.0f, 128.0f,
                                     255.0f, 255.0f, 255.0f, 255.0f);
                    }
                    if (kind == 12) {
                        RevelationBoardDrawSprite_34c170(w, ctx, 2, xm1, ym1, -1, -1, w->f778, 128.0f, 128.0f, 128.0f, 64.0f,
                                     128.0f, 128.0f, 128.0f, 255.0f);
                    }
                    if (kind == 13) {
                        RevelationBoardDrawSprite_34c170(w, ctx, 3, x2, y2, 0x24, 0x28, rot, 128.0f, 128.0f, 128.0f, 72.0f,
                                     255.0f, 255.0f, 255.0f, 255.0f);
                    }
                    if (kind == 14) {
                        RevelationBoardDrawSprite_34c170(w, ctx, 3, x, y, -1, -1, rot, 128.0f, 112.0f, 96.0f, 48.0f,
                                     255.0f, 255.0f, 255.0f, 255.0f);
                    }
                    if (kind == 1) {
                        s32 s = (u8)(hl ? 8 : 4);
                        f32 r = 128.0f, g = 128.0f, b = 128.0f, a = 128.0f;
                        if (row > 0 && cell[-26].kind == 14) {
                            r = 96.0f; g = 96.0f; b = 112.0f; a = 48.0f;
                        }
                        RevelationBoardDrawSprite_34c170(w, ctx, s, x10, y7, -1, -1, rot, r, g, b, a,
                                     255.0f, 255.0f, 255.0f, 255.0f);
                    }
                    if (kind == 2) {
                        s32 s = (u8)(hl ? 9 : 5);
                        f32 r = 128.0f, g = 128.0f, b = 128.0f, a = 128.0f;
                        if (row < 17 && cell[26].kind == 14) {
                            r = 96.0f; g = 96.0f; b = 112.0f; a = 48.0f;
                        }
                        RevelationBoardDrawSprite_34c170(w, ctx, s, x10, y8, -1, -1, rot, r, g, b, a,
                                     255.0f, 255.0f, 255.0f, 255.0f);
                    }
                    if (kind == 4) {
                        s32 s = (u8)(hl ? 10 : 6);
                        f32 r = 128.0f, g = 128.0f, b = 128.0f, a = 128.0f;
                        if (col < 25 && cell[1].kind == 14) {
                            r = 96.0f; g = 96.0f; b = 112.0f; a = 48.0f;
                        }
                        RevelationBoardDrawSprite_34c170(w, ctx, s, x6, y12, -1, -1, rot, r, g, b, a,
                                     255.0f, 255.0f, 255.0f, 255.0f);
                    }
                    if (kind == 3) {
                        s32 s = (u8)(hl ? 11 : 7);
                        f32 r = 128.0f, g = 128.0f, b = 128.0f, a = 128.0f;
                        if (col > 0 && cell[-1].kind == 14) {
                            r = 96.0f; g = 96.0f; b = 112.0f; a = 48.0f;
                        }
                        RevelationBoardDrawSprite_34c170(w, ctx, s, x6, y12, -1, -1, rot, r, g, b, a,
                                     255.0f, 255.0f, 255.0f, 255.0f);
                    }
                }
                if (mask != 0) {
                    if (mask & 1) {
                        u8 f = 0;
                        s32 t = RevelationBoardCellLinkMask_409b50(cell, 0, &f);
                        if (t == 0) {
                            RevelationBoardDrawSprite_34c170(w, ctx, (u8)(f ? 0x2D : 0x1D), x, y, 8, 8, rot, 128.0f, 128.0f, 128.0f, 128.0f,
                                         255.0f, 255.0f, 255.0f, 255.0f);
                        } else if (t == 0x10) {
                            s32 s = (u8)(f ? 0x2C : 0x1C);
                            if (row > 0 && col > 0 && (cell[-27].conn & 0x80)) s = (u8)(f ? 0x2A : 0x1A);
                            RevelationBoardDrawSprite_34c170(w, ctx, s, x, y, 8, 8, rot, 128.0f, 128.0f, 128.0f, 128.0f,
                                         255.0f, 255.0f, 255.0f, 255.0f);
                        } else if (t == 0x40) {
                            s32 s = (u8)(f ? 0x28 : 0x18);
                            if (row > 0 && col > 0 && (cell[-27].conn & 0x80)) s = (u8)(f ? 0x26 : 0x16);
                            RevelationBoardDrawSprite_34c170(w, ctx, s, x, y, 8, 8, rot, 128.0f, 128.0f, 128.0f, 128.0f,
                                         255.0f, 255.0f, 255.0f, 255.0f);
                        } else if (t == 0x50) {
                            s32 s = (u8)(f ? 0x30 : 0x10);
                            if (row > 0 && col > 0 && cell[-27].kind == 14) s = 0x34;
                            RevelationBoardDrawSprite_34c170(w, ctx, s, x, y, 8, 8, rot, 128.0f, 128.0f, 128.0f, 128.0f,
                                         255.0f, 255.0f, 255.0f, 255.0f);
                        }
                    }
                    if (mask & 2) {
                        u8 f = 0;
                        if (RevelationBoardCellLinkMask_409b50(cell, 1, &f) == 0x18) {
                            RevelationBoardDrawSprite_34c170(w, ctx, (u8)(f ? 0x2C : 0x1C), x8, y, 0x1A, 8, rot, 128.0f, 128.0f, 128.0f, 128.0f,
                                         255.0f, 255.0f, 255.0f, 255.0f);
                        }
                    }
                    if (mask & 4) {
                        u8 f = 0;
                        s32 t = RevelationBoardCellLinkMask_409b50(cell, 2, &f);
                        if (t == 0) {
                            RevelationBoardDrawSprite_34c170(w, ctx, (u8)(f ? 0x29 : 0x19), x34, y, 8, 8, rot, 128.0f, 128.0f, 128.0f, 128.0f,
                                         255.0f, 255.0f, 255.0f, 255.0f);
                        } else if (t == 8) {
                            s32 s = (u8)(f ? 0x2C : 0x1C);
                            if (row > 0 && col < 25 && (cell[-25].conn & 0x20)) s = (u8)(f ? 0x2E : 0x1E);
                            RevelationBoardDrawSprite_34c170(w, ctx, s, x34, y, 8, 8, rot, 128.0f, 128.0f, 128.0f, 128.0f,
                                         255.0f, 255.0f, 255.0f, 255.0f);
                        } else if (t == 0x40) {
                            ok2 = true;
                            s2 = (u8)(f ? 0x27 : 0x17);
                            if (row > 0 && col < 25 && (cell[-25].conn & 0x20)) {
                                Cell *nc;
                                s2 = (u8)(f ? 0x22 : 0x12);
                                nc = cell + 1;
                                {
                                    s32 ni = idx + 1;
                                    Hit *h2 = RevelationBoardCellGetEntry_3eae10(s1, id, nc);
                                    if (nc != 0 && h2 != 0 && nc->kind >= 11 && h2->v == ni) ok2 = false;
                                }
                            }
                            if (ok2) {
                                RevelationBoardDrawSprite_34c170(w, ctx, s2, x34, y, 8, 8, rot, 128.0f, 128.0f, 128.0f, 128.0f,
                                             255.0f, 255.0f, 255.0f, 255.0f);
                            }
                        } else if (t == 0x48) {
                            s32 s = (u8)(f ? 0x31 : 0x14);
                            if (row < 17 && col < 25 && cell[-25].kind == 14) s = 0x35;
                            RevelationBoardDrawSprite_34c170(w, ctx, s, x34, y, 8, 8, rot, 128.0f, 128.0f, 128.0f, 128.0f,
                                         255.0f, 255.0f, 255.0f, 255.0f);
                        }
                    }
                    if (mask & 8) {
                        u8 f = 0;
                        if (RevelationBoardCellLinkMask_409b50(cell, 3, &f) == 0x42) {
                            RevelationBoardDrawSprite_34c170(w, ctx, (u8)(f ? 0x28 : 0x18), x, y8, 8, 0x1E, rot, 128.0f, 128.0f, 128.0f, 128.0f,
                                         255.0f, 255.0f, 255.0f, 255.0f);
                        }
                    }
                    if (mask & 0x10) {
                        u8 f = 0;
                        if (RevelationBoardCellLinkMask_409b50(cell, 4, &f) == 0x42) {
                            RevelationBoardDrawSprite_34c170(w, ctx, (u8)(f ? 0x27 : 0x17), x34, y8, 8, 0x1E, rot, 128.0f, 128.0f, 128.0f, 128.0f,
                                         255.0f, 255.0f, 255.0f, 255.0f);
                        }
                    }
                    if (mask & 0x20) {
                        u8 f = 0;
                        s32 t = RevelationBoardCellLinkMask_409b50(cell, 5, &f);
                        if (t == 0) {
                            RevelationBoardDrawSprite_34c170(w, ctx, (u8)(f ? 0x24 : 0x14), x, y38, 8, 8, rot, 128.0f, 128.0f, 128.0f, 128.0f,
                                         255.0f, 255.0f, 255.0f, 255.0f);
                        } else if (t == 0x10) {
                            ok5 = true;
                            s5 = (u8)(f ? 0x23 : 0x13);
                            if (row < 17 && col > 0 && (cell[25].conn & 4)) {
                                Cell *nc;
                                s5 = (u8)(f ? 0x21 : 0x11);
                                nc = cell + 26;
                                {
                                    s32 ni = idx + 26;
                                    Hit *h2 = RevelationBoardCellGetEntry_3eae10(s1, id, nc);
                                    if (nc != 0 && h2 != 0 && nc->kind >= 11 && h2->v == ni) ok5 = false;
                                }
                            }
                            if (ok5) {
                                RevelationBoardDrawSprite_34c170(w, ctx, s5, x, y38, 8, 8, rot, 128.0f, 128.0f, 128.0f, 128.0f,
                                             255.0f, 255.0f, 255.0f, 255.0f);
                            }
                        } else if (t == 1) {
                            s32 s = (u8)(f ? 0x28 : 0x18);
                            if (row < 17 && col > 0 && (cell[25].conn & 4)) s = (u8)(f ? 0x2F : 0x1F);
                            RevelationBoardDrawSprite_34c170(w, ctx, s, x, y38, 8, 8, rot, 128.0f, 128.0f, 128.0f, 128.0f,
                                         255.0f, 255.0f, 255.0f, 255.0f);
                        } else if (t == 0x11) {
                            s32 s = (u8)(f ? 0x32 : 0x19);
                            if (row < 17 && col > 0 && cell[25].kind == 14) s = 0x36;
                            RevelationBoardDrawSprite_34c170(w, ctx, s, x, y38, 8, 8, rot, 128.0f, 128.0f, 128.0f, 128.0f,
                                         255.0f, 255.0f, 255.0f, 255.0f);
                        }
                    }
                    if (mask & 0x40) {
                        u8 f = 0;
                        if (RevelationBoardCellLinkMask_409b50(cell, 6, &f) == 0x18) {
                            RevelationBoardDrawSprite_34c170(w, ctx, (u8)(f ? 0x23 : 0x13), x8, y38, 0x1A, 8, rot, 128.0f, 128.0f, 128.0f, 128.0f,
                                         255.0f, 255.0f, 255.0f, 255.0f);
                        }
                    }
                    if (mask & 0x80) {
                        u8 f = 0;
                        s32 t = RevelationBoardCellLinkMask_409b50(cell, 7, &f);
                        if (t == 0) {
                            ok7 = true;
                            s7 = (u8)(f ? 0x20 : 0x10);
                            if (row < 17 && col < 25) {
                                Cell *nc = cell + 27;
                                {
                                    s32 ni = idx + 27;
                                    Hit *h2 = RevelationBoardCellGetEntry_3eae10(s1, id, nc);
                                    if (nc != 0 && h2 != 0 && nc->kind >= 11 && h2->v == ni) ok7 = false;
                                }
                            }
                            if (ok7) {
                                RevelationBoardDrawSprite_34c170(w, ctx, s7, x34, y38, 8, 8, rot, 128.0f, 128.0f, 128.0f, 128.0f,
                                             255.0f, 255.0f, 255.0f, 255.0f);
                            }
                        } else if (t == 8) {
                            s32 s = (u8)(f ? 0x23 : 0x13);
                            if (row < 17 && col < 25 && (cell[27].conn & 1)) s = (u8)(f ? 0x25 : 0x15);
                            RevelationBoardDrawSprite_34c170(w, ctx, s, x34, y38, 8, 8, rot, 128.0f, 128.0f, 128.0f, 128.0f,
                                         255.0f, 255.0f, 255.0f, 255.0f);
                        } else if (t == 1) {
                            s32 s = (u8)(f ? 0x27 : 0x17);
                            if (row < 17 && col < 25 && (cell[27].conn & 1)) s = (u8)(f ? 0x2B : 0x1B);
                            RevelationBoardDrawSprite_34c170(w, ctx, s, x34, y38, 8, 8, rot, 128.0f, 128.0f, 128.0f, 128.0f,
                                         255.0f, 255.0f, 255.0f, 255.0f);
                        } else if (t == 9) {
                            s32 s = (u8)(f ? 0x33 : 0x1D);
                            if (row < 17 && col < 25 && cell[27].kind == 14) s = 0x37;
                            RevelationBoardDrawSprite_34c170(w, ctx, s, x34, y38, 8, 8, rot, 128.0f, 128.0f, 128.0f, 128.0f,
                                         255.0f, 255.0f, 255.0f, 255.0f);
                        }
                    }
                }
                if (kind >= 11) {
                    if (sel) {
                        Tag *tg;
                        s32 sp;
                        s32 cw, ch;
                        cw = D_00453A5C[0]; ch = D_00453A5E[0]; sp = 13;
                        RevelationBoardDrawSprite_34c170(w, ctx, sp, bx - 1, by - 1, cw, ch, rot,
                                     128.0f, 128.0f, 128.0f, 128.0f, 255.0f, 255.0f, 255.0f, 255.0f);
                        tg = RevelationBoardCellGetValue_3eade0(s1, id, cell);
                        if (tg != 0) {
                            if (tg->x2 == 0) {
                                cw = D_00453A64[0]; ch = D_00453A66[0]; sp = 14;
                            } else {
                                cw = D_00453A6C[0]; ch = D_00453A6E[0]; sp = 15;
                            }
                            RevelationBoardDrawSprite_34c170(w, ctx, sp, bx2 - 1, by2 - 1, cw, ch, rot,
                                         128.0f, 128.0f, 128.0f, 128.0f, 255.0f, 255.0f, 255.0f, 255.0f);
                        }
                    }
                    RevelationBoardCellGetItemRec_3ead00(s1, id, cell);
                }
            }
        }
    }
    GsPktClose_13f5b0(ctx);
    DrawListEndPrim_141a20(tb);
    DrawListAddTexLoad_1418c0(tb, 0x32E, 1.0f);
    ctx = DrawListBeginPrim_141b00(tb);
    GsPktSetBlendMode_13e4f0(ctx, 1);
    GsPktSetAlphaBlend_13e500(ctx, 1);
    GsPktSetAntialias_13e390(ctx, 0);
    GsPktEnableAlphaTest_13e4d0(ctx, 1);
    GsPktEnableZTest_13e460(ctx, 0);
    GsPktSetTextured_13e400(ctx, 1);
    GsPktSetUseUV_13e3e0(ctx, 1);
    GsPktSetOriginMode_13e2f0(ctx, 0);
    GsPktSetTexFilter_13e3d0(ctx, 0);
    GsPktSetZWriteMask_13e430(ctx, 1);
    GsPktSetGouraud_13e3b0(ctx, 0);
    NameTableFindByName_159fb0(sb, D_00462908, 0x32E);
    c = UiGetWidgetColor_2904b0(w->h, 0x47);
    for (i = 0; i < 4; i++) {
        col4[i] = (s32)(128.0f * c[i]);
    }
    k2 = 0;
    GsPktOpenPrim_13f730(ctx, 6);
    alpha = (s32)(D_0047D440 * (f32)col4[3]);
    for (row = 0; row < 18; row++) {
        s32 ry = row * 46;
        for (col = 0; col < 26; col++) {
            s32 idx = k2++;
            CState *cs;
            s32 cx;
            cell2 = &map->cells[idx];
            cs = &w->cs[idx];
            RevelationBoardCellGetEntry_3eae10(s1, id, cell2);
            kind02 = cell2->kind;
            cx = col * 42;
            n2 = 1;
            {
                s32 m = w->mode;
                if (m == 5) goto two2;
                if (m == 6) goto two2;
                if (m == 7) goto two2;
                if (m == 8) {
                two2:
                    n2 = 2;
                }
            }
            for (pass2 = 1; pass2 <= n2; pass2++) {
                f32 rot;
                s32 kind;
                rot = 0.0f;
                kind = kind02;
                if (w->mode == 5) {
                    if (pass2 == 1) {
                        if (cs->f0) kind = 0;
                    } else if (pass2 == 2) {
                        if (cs->f0) kind = 14; else kind = 0;
                        rot = Sinf_128fd0(D_0047D400 * (f32)w->timer);
                    }
                }
                if (w->mode == 6) {
                    if (pass2 == 1) {
                        if (cs->f0) kind = 0;
                    } else if (pass2 == 2) {
                        if (cs->f0) kind = 14; else kind = 0;
                        rot = D_0047D440 + Sinf_128fd0(D_0047D498 * (f32)w->timer) / 4.0f;
                    }
                }
                if (w->mode == 7) {
                    if (pass2 == 1) {
                        if (cs->f0) kind = 0;
                    } else if (pass2 == 2) {
                        if (cs->f0) kind = 14; else kind = 0;
                        rot = Cosf_128d30(D_0047D498 * (f32)w->timer);
                    }
                } else if (w->mode == 8) {
                    if (cs->f0) kind = 14;
                    if (pass2 == 1) {
                        if (cs->f1) kind = 0;
                    } else if (pass2 == 2) {
                        if (cs->f1) {
                            if (kind == 10) kind = 11;
                        } else {
                            kind = 0;
                        }
                        rot = Cosf_128d30(D_0047D498 * (f32)w->timer);
                    }
                }
                if (kind >= 11) {
                    Ent *d = RevelationBoardCellGetItemRec_3ead00(s1, id, cell2);
                    if (d != 0) {
                        GsPktSetTexture_13ec00(ctx, NameTableFindByName_159fb0(sb, D_00462908, 0x32E));
                        if ((u32)(kind - 11) < 2) {
                            Rc rc;
                            s32 uw, vh;
                            UiSetItemIconUv_288e50(&rc, d->x2C, 0x20, 0x24);
                            px = cx + 4;
                            py = ry + 4;
                            u1 = rc.u;
                            v1 = rc.v;
                            uw = rc.uw;
                            vh = rc.vh;
                            GsPktSetRGBAQ_13ee40(ctx, 0, 0, 0, alpha);
                            GsPktSetUV_13ed60(ctx, u1, v1);
                            GsPktSetXYZPixel_13f110(ctx, x0 + px, y0 + py, 0);
                            GsPktSetUV_13ed60(ctx, u1 + uw, v1 + vh);
                            GsPktSetXYZPixel_13f110(ctx, x0 + px + 32, y0 + py + 36, 0);
                        }
                        if (kind == 13) {
                            Rc rc;
                            s32 uw, vh;
                            UiSetItemIconUv_288e50(&rc, d->x2C, 0x20, 0x24);
                            px = cx + 4;
                            py = ry + 4;
                            u13 = rc.u;
                            v13 = rc.v;
                            uw = rc.uw;
                            vh = rc.vh;
                            RevelationBoardPktSetColorLerp_34ce10(w, ctx, rot, 128.0f, 128.0f, 128.0f, 128.0f, 255.0f, 255.0f, 255.0f, 255.0f);
                            GsPktSetUV_13ed60(ctx, u13, v13);
                            GsPktSetXYZPixel_13f110(ctx, x0 + px, y0 + py, 0);
                            GsPktSetUV_13ed60(ctx, u13 + uw, v13 + vh);
                            GsPktSetXYZPixel_13f110(ctx, x0 + px + 32, y0 + py + 36, 0);
                        }
                        if (kind == 14) {
                            Rc rc;
                            s32 u, v, uw, vh;
                            UiSetItemIconUv_288e50(&rc, d->x2C, 0x20, 0x24);
                            px = cx + 4;
                            py = ry + 4;
                            u = rc.u;
                            v = rc.v;
                            uw = rc.uw;
                            vh = rc.vh;
                            RevelationBoardPktSetColorLerp_34ce10(w, ctx, rot, 128.0f, 128.0f, 128.0f, 88.0f, 255.0f, 255.0f, 255.0f, 255.0f);
                            GsPktSetUV_13ed60(ctx, u, v);
                            GsPktSetXYZPixel_13f110(ctx, x0 + px, y0 + py, 0);
                            GsPktSetUV_13ed60(ctx, u + uw, v + vh);
                            GsPktSetXYZPixel_13f110(ctx, x0 + px + 32, y0 + py + 36, 0);
                        }
                    }
                }
            }
        }
    }
    GsPktClose_13f5b0(ctx);
    DrawListEndPrim_141a20(tb);
    DrawListAddTexLoad_1418c0(tb, 0x32D, 1.0f);
    RevelationBoardDrawItemBalloonMaybe_349920(w, id, x0, y0);
}
