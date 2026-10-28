/* rgp:protos */
#define RGP_SELF_FontDrawGlyph_26de80 1
#define RGP_SELF_MesWinDrawGlyphs_271b70 1
#define RGP_SELF_MesWinGetGlyphColor_2724a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

typedef struct RGBA {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} __attribute__((aligned(8))) RGBA;

typedef struct Pair {
    s64 v;
} Pair;

typedef struct Ent {
    u16 id;
    s16 x;
    s16 y;
    u8 cnt;
    u8 pad;
} Ent;

typedef struct Off {
    s16 x;
    s16 y;
} Off;

typedef struct Self {
    u8 pad0[0x40];
    s32 ox;
    s32 oy;
    u8 pad48[0x7C];
    Ent ents[787];
    u8 alpha;
    u8 pad195D[0x2FF];
    s16 adj[20];
    Off off[25];
    s8 kind[180];
    s16 pri[40];
    u8 pad1DEC;
    s8 flag;
} Self;

#define ALPHA(s) ((s)->alpha)
#define ADJ(s, i) ((s)->adj[i])
#define OFF(s, i) ((s)->off[i])
#define KIND(s, i) ((s)->kind[i])
#define PRI(s, i) ((s)->pri[i])
#define FLAG(s) ((s)->flag)

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
void FontDrawGlyph_26de80(Self *, s32, u16, s32, s32, Pair, u8, f32);
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
void MesWinGetGlyphColor_2724a0(void *, void *, int);
extern s32 D_0045F200[];
extern s32 D_0045F208[];

void MesWinDrawGlyphs_271b70(Self *self, s32 arg1) {
    RGBA col __attribute__((aligned(16)));
    Pair pr __attribute__((aligned(16)));
    Pair tmp __attribute__((aligned(16)));
    s16 def;
    s32 last;
    s32 w;
    s32 x;
    s32 y;
    Ent *e;
    s16 p;
    s32 id;
    s32 idx;
    s16 div;
    s32 i;

    if (arg1 != 0) {
    GsPktSetup2DState_26fdc0(arg1);
    GsPktOpenPrim_13f730(arg1, 6);
    last = MesWinGetShownEnd_271680(self) - 1;
    i = MesWinGetShownStart_2716a0(self);
    div = D_0045F208[0] + 4;
    def = D_0045F200[0] - 1;
    for (; i <= last; i++) {
        e = &self->ents[i];
        x = e->x;
        y = e->y;
        id = e->id;
        if (e->cnt <= 0xFE) {
            e->cnt++;
        }
        idx = e->y / div;
        if (KIND(self, idx) == 4) {
            continue;
        }
        MesWinSetScissor_271fa0(self, arg1, idx);
        if (MesWinGetLineFixedPos_272440(self, idx) != 0) {
            x += OFF(self, idx).x;
            y = OFF(self, idx).y;
        } else {
            x += self->ox;
            y += self->oy;
            if (FLAG(self) != 0) {
                x += ADJ(self, idx);
            }
            y += MesWinGetScrollY_271700(self);
        }
        if (id >= 0xFD00 && id <= 0xFDFF) {
            col.r = col.g = col.b = 0x80;
            col.a = ALPHA(self) * 0x80 / 0x80;
            FontDrawGaiji_26dd50(self, arg1, id, x, y, __builtin_bit_cast(long long, (col)));
            MesWinSetLastGlyphPos_272320(self, x + FontGetGaijiWidth_26f890(self, id), y);
        } else {
            tmp = ({ Pair rgp_sret; MesWinGetGlyphColor_2724a0((void *)&rgp_sret, (void *)(self), (int)(i)); rgp_sret; });
            pr = tmp;
            FontGlyphDigitValue_26ec20(self, id);
            TextStyleSetAlpha_26dd40(self, ALPHA(self));
            p = PRI(self, idx);
            if (p >= 0) {
                FontDrawGlyph_26de80(self, arg1, id, x, y, pr, p & 0xFF, 1.0f);
            } else {
                FontDrawGlyph_26de80(self, arg1, id, x, y, pr, ALPHA(self), 1.0f);
            }
            if (FontIsAsciiCode_26ed80(self, id) != 0) {
                w = ((unsigned char)FontGetCharWidth_26f4c0(self, id)) & 0xFF;
            } else {
                w = def;
            }
            MesWinSetLastGlyphPos_272320(self, x + w, y);
        }
        MesWinSetScissorFull_271ef0(self, arg1, idx);
    }
    GsPktClose_13f5b0(arg1);
    }
}
