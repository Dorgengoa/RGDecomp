#include "types.h"


typedef struct Ctx {
    u8 pad0[0x193C];
    s32 line;
    u8 pad1940[0x1C20 - 0x1940];
    s16 col;
    s16 row;
} Ctx;

s32 MesWinGetMsgData_276e90(Ctx *);
u16 *MesWinLookupMsg_2745f0(Ctx *, s32);
void MesWinClearChars_2744b0(Ctx *);
void MesWinSetFlush_2775f0(Ctx *, s32);
void MesWinPushChar_2743c0(Ctx *, s32);
void MesWinCountPageLines_2726d0(Ctx *);
void MesWinSetPenX_272af0(Ctx *, s32);
void MesWinAddPenY_272ab0(Ctx *, s32);
void MesWinSetPenY_272ac0(Ctx *, s32);
s32 MesWinGetLineSpacing_2722e0(Ctx *, s32);
void MesWinAddPenX_272ae0(Ctx *, s32);
s32 TextStyleGetSpaceWidth_26f5d0(Ctx *);
s16 FontGetGaijiWidth_26f890(Ctx *, s32);
s16 TextCalcGapWidthMaybe_2741c0(Ctx *, s32, s32, u16 *);
void MesWinLayoutStrVar_274e60(Ctx *, s32);
s32 MesNumVarFindIndex_277640(s32);
void MesWinPushNumVar_275db0(Ctx *, s32);
void MesWinPushNumVar0_275dd0(Ctx *);
s32 MesWinLayoutItemName_2748f0(Ctx *, s32);
s32 FontIsAsciiCode_26ed80(Ctx *, s32);
s32 FontGetCharWidth_26f4c0(Ctx *, u16);
extern s32 D_0045F200[];
extern s32 D_0045F208[];

void MesWinLayoutMsg_273cf0(Ctx *a, s32 arg1) {
    u16 *p;
    s32 c;
    s16 size;
    s16 def;
    s32 t;
    s32 r;

    if (MesWinGetMsgData_276e90(a) == 0) {
        return;
    }
    p = MesWinLookupMsg_2745f0(a, arg1);
    if (p == 0) {
        return;
    }
    MesWinClearChars_2744b0(a);
    MesWinSetFlush_2775f0(a, 0);
    size = D_0045F208[0] + 4;
    def = D_0045F200[0] - 1;
    for (;;) {
        c = *p++;
        if (c == 0xFF00 || c == 0xFF03 || c == 0xFF01) {
            a->col = -1;
            a->row = -1;
        }
        switch (c) {
        case 0xFF01:
            MesWinPushChar_2743c0(a, 0xFF01);
            MesWinCountPageLines_2726d0(a);
            return;
        case 0xFF00:
            MesWinPushChar_2743c0(a, 0xFF00);
            MesWinSetPenX_272af0(a, 0);
            MesWinAddPenY_272ab0(a, size);
            MesWinAddPenY_272ab0(a, MesWinGetLineSpacing_2722e0(a, a->line));
            a->line++;
            break;
        case 0xFF03:
            MesWinPushChar_2743c0(a, 0xFF03);
            MesWinSetPenX_272af0(a, 0);
            MesWinSetPenY_272ac0(a, 0);
            a->line++;
            break;
        case 0xFF02:
            MesWinPushChar_2743c0(a, 0xFF02);
            if (a->row >= 0 || a->col >= 0) {
                MesWinAddPenX_272ae0(a, a->col);
            } else {
                MesWinAddPenX_272ae0(a, (u8)TextStyleGetSpaceWidth_26f5d0(a));
            }
            break;
        default:
            if (c >= 0xFD00 && c < 0xFE00) {
                MesWinPushChar_2743c0(a, c);
                MesWinAddPenX_272ae0(a, FontGetGaijiWidth_26f890(a, c));
            } else if (c >= 0xFC00 && c < 0xFD00) {
                MesWinPushChar_2743c0(a, c);
            } else if (c >= 0xF500 && c < 0xF600) {
                MesWinPushChar_2743c0(a, c);
            } else if (c >= 0xF400 && c < 0xF500) {
                MesWinPushChar_2743c0(a, c);
            } else if (c >= 0xF300 && c < 0xF400) {
                MesWinPushChar_2743c0(a, c);
            } else if (c >= 0xF200 && c < 0xF300) {
                MesWinPushChar_2743c0(a, c);
            } else if (c >= 0xF700 && c < 0xF800) {
                t = (c - 0xF700) * 4;
                a->row = t;
                a->col = TextCalcGapWidthMaybe_2741c0(a, (s16)t, def, p - 1);
            } else if (c >= 0xF800 && c < 0xF900) {
                a->col = c - 0xF800;
            } else if (c >= 0xF900 && c < 0xFA00) {
                MesWinAddPenX_272ae0(a, c - 0xF900);
            } else if (c >= 0xFAEA && c < 0xFAFA) {
                MesWinLayoutStrVar_274e60(a, 0xFAF9 - c);
            } else {
                r = MesNumVarFindIndex_277640(c);
                if (r >= 0) {
                    if (r != 0) {
                        MesWinPushNumVar_275db0(a, r - 1);
                    } else {
                        MesWinPushNumVar0_275dd0(a);
                    }
                } else if (MesWinLayoutItemName_2748f0(a, c) == 0) {
                    MesWinPushChar_2743c0(a, c);
                    if (FontIsAsciiCode_26ed80(a, c) != 0) {
                        MesWinAddPenX_272ae0(a, (u8)FontGetCharWidth_26f4c0(a, c));
                    } else {
                        MesWinAddPenX_272ae0(a, def);
                    }
                }
            }
            break;
        }
    }
}
