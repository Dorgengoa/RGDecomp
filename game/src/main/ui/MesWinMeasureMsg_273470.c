/* rgp:protos */
#define RGP_SELF_MesWinMeasureMsg_273470 1
#include "port/game_protos.h"
#line 1
#define KA 1
#define KE 1
#define KC 0
#define KK 1
#include "types.h"
#ifndef KA
#define KA 0
#endif
#ifndef KB
#define KB 0
#endif
#ifndef KE
#define KE 0
#endif
#if KE == 0
#define RNG_HI(c, h) (c < h)
#elif KE == 1
#define RNG_HI(c, h) (c <= h - 1)
#else
#define RNG_HI(c, h) !(c >= h)
#endif
#ifndef KC
#define KC 0
#endif

typedef struct {
    u8 pad0[0x56];
    s16 width;
    u8 pad58[0x1B9C - 0x58];
    s32 vals[31];
    s32 v1c18;
    s8 f1c1c;
    s8 f1c1d;
    u8 pad1e[2];
    s16 f1c20;
    s16 f1c22;
} Msg;

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
void Sprintf_1343b8(char *, void *, s32);
s32 strlen(char *);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
#if KK
extern s32 D_0045F200[];
extern s32 D_0045F208[];
#else
extern s32 D_0045F200[];
extern s32 D_0045F208[];
#endif
extern u8 D_0045F720[];
extern u8 D_0045F728[];

void MesWinMeasureMsg_273470(Msg *self, s32 arg1)
{
    char buf[0x80] __attribute__((aligned(16)));
    u16 *p;
    s32 width;
    s32 line;
    s32 para;
    s32 sp;
    s32 dflt;
    s32 r;
    s32 v;
    u16 c;

    if (MesWinGetMsgData_276e90(self) == 0) return;
    p = ((u16 *)MesWinLookupMsg_2745f0(self, arg1));
    if (p == 0) return;
#if KC == 0
    width = 0;
    line = 0;
    self->width = 0;
    para = 0;
    sp = D_0045F208[0] + 4;
    dflt = D_0045F200[0] - 1;
#elif KC == 1
    sp = D_0045F208[0] + 4;
    dflt = D_0045F200[0] - 1;
    width = 0;
    line = 0;
    self->width = 0;
    para = 0;
#elif KC == 2
    width = 0;
    line = 0;
    para = 0;
    sp = D_0045F208[0] + 4;
    dflt = D_0045F200[0] - 1;
    self->width = 0;
#elif KC == 3
    sp = D_0045F208[0] + 4;
    dflt = D_0045F200[0] - 1;
    self->width = 0;
    width = 0;
    line = 0;
    para = 0;
#elif KC == 4
    width = 0;
    line = 0;
    sp = D_0045F208[0] + 4;
    dflt = D_0045F200[0] - 1;
    self->width = 0;
    para = 0;
#elif KC == 5
    sp = D_0045F208[0] + 4;
    width = 0;
    dflt = D_0045F200[0] - 1;
    line = 0;
    self->width = 0;
    para = 0;
#elif KC == 6
    sp = D_0045F208[0] + 4;
    dflt = D_0045F200[0] - 1;
    width = 0;
    line = 0;
    para = 0;
    self->width = 0;
#elif KC == 7
    width = 0;
    sp = D_0045F208[0] + 4;
    line = 0;
    dflt = D_0045F200[0] - 1;
    self->width = 0;
    para = 0;
#elif KC == 8
    sp = D_0045F208[0] + 4;
    width = 0;
    line = 0;
    dflt = D_0045F200[0] - 1;
    self->width = 0;
    para = 0;
#elif KC == 9
    width = 0;
    line = 0;
    sp = D_0045F208[0] + 4;
    self->width = 0;
    para = 0;
    dflt = D_0045F200[0] - 1;
#elif KC == 10
    sp = D_0045F208[0] + 4;
    width = 0;
    line = 0;
    self->width = 0;
    dflt = D_0045F200[0] - 1;
    para = 0;
#elif KC == 11
    sp = D_0045F208[0] + 4;
    dflt = D_0045F200[0] - 1;
    line = 0;
    width = 0;
    self->width = 0;
    para = 0;
#endif
    for (;;) {
        c = *p++;
        if (c == 0xFF00 || c == 0xFF03 || c == 0xFF01) {
            self->f1c20 = -1;
            self->f1c22 = -1;
        }
        switch (c) {
        case 0xFF01:
            MesWinSetPageLineCount_273b90(self, line, para);
            self->width += (s16)sp;
            MesWinCalcMaxLineWidth_273b00(self);
            MesWinCalcLineCentering_273a10(self);
            return;
        case 0xFF02:
            if (self->f1c22 >= 0 || self->f1c20 >= 0) {
                MesWinAddLineWidth_273c20(self, line, (long long)(self->f1c20));
            } else {
                MesWinAddLineWidth_273c20(self, line, (long long)(TextStyleGetSpaceWidth_26f5d0(self)));
            }
            break;
        case 0xFF00:
#if KA
            r = width + (s16)sp;
            width = r + ((short)MesWinGetLineSpacing_2722e0(self, line));
#else
            width = width + (s16)sp + ((short)MesWinGetLineSpacing_2722e0(self, line));
#endif
            if (self->width < width) self->width = width;
            line++;
            MesWinSetLineWidth_273be0(self, line, 0);
            break;
        case 0xFF03:
            MesWinSetPageLineCount_273b90(self, line, para);
            line++;
            MesWinSetLineWidth_273be0(self, line, 0);
            width = 0;
            para++;
            break;
        case 0xFF0B:
            while (*p++ != 0xFF0C) {
            }
            break;
        case 0xFF0C:
            break;
        default:
            if (c >= 0xFE00 && RNG_HI(c, 0xFF00)) {
            } else if (c >= 0xFC00 && RNG_HI(c, 0xFD00)) {
            } else if (c >= 0xF500 && RNG_HI(c, 0xF600)) {
            } else if (c >= 0xF400 && RNG_HI(c, 0xF500)) {
            } else if (c >= 0xF300 && RNG_HI(c, 0xF400)) {
            } else if (c >= 0xF200 && RNG_HI(c, 0xF300)) {
            } else if (c >= 0xF700 && c < 0xF800) {
                self->f1c22 = (c - 0xF700) * 4;
                self->f1c20 = TextCalcGapWidthMaybe_2741c0(self, self->f1c22, (s16)dflt, p - 1);
            } else if (c >= 0xF800 && c < 0xF900) {
                self->f1c20 = c - 0xF800;
            } else if (c >= 0xF900 && c < 0xFA00) {
                MesWinAddLineWidthUnchecked_272330(self, line, c - 0xF900);
            } else {
                r = MesNumVarFindIndex_277640(c);
                if (r >= 0) {
                    if (r != 0) {
                        v = self->vals[r];
                    } else {
                        v = self->v1c18;
                    }
                    if (self->f1c1d != 0 || v != 0) {
                        if (self->f1c1c != 0 && v > 0) {
                            Sprintf_1343b8(buf, D_0045F720, v);
                        } else {
                            Sprintf_1343b8(buf, D_0045F728, v);
                        }
                        r = strlen(buf) - 1;
                        MesWinAddLineWidth_273c20(self, line, (long long)(r * FontGetDigitWidth_26f5a0()));
                    }
                } else {
                    r = MesItemCodeFindIndex_277260(c);
                    if (r != 0) {
                        r = MesWinMeasureItemSlot_2746b0(self, r);
                        if (r != -1) MesWinAddLineWidth_273c20(self, line, (long long)(r));
                    } else if (c >= 0xFAEA && c < 0xFAFA) {
                        r = MesWinGetStrVarWidth_277390(self, 0xFAF9 - c);
                        if (r != -1) MesWinAddLineWidth_273c20(self, line, (long long)(r));
                    } else if (c >= 0xFD00 && c < 0xFE00) {
                        MesWinAddLineWidth_273c20(self, line, (long long)(FontGetGaijiWidth_26f890(self, c)));
                    } else if (FontIsAsciiCode_26ed80(self, c) != 0) {
                        MesWinAddLineWidth_273c20(self, line, (long long)(FontGetCharWidth_26f4c0(self, c)));
                    } else {
                        MesWinAddLineWidth_273c20(self, line, (long long)((s16)dflt));
                    }
                }
            }
            break;
        }
    }
}
