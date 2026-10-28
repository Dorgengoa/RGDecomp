/* rgp:protos */
#define RGP_SELF_MesWinPushNumber_275de0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x1C1C];
    s8 unk1C1C;
    s8 unk1C1D;
    s16 unk1C1E;
} Obj00275DE0;

void Sprintf_1343b8(s8 *, char *, s32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
s32 strlen(s8 *);
extern s32 D_0045F200[];
extern char D_0045F720[];
extern char D_0045F728[];

void MesWinPushNumber_275de0(Obj00275DE0 *arg0, s32 arg1, s32 arg2) {
    s8 sp40[0x78] __attribute__((aligned(16)));
    s32 w;
    s32 len;
    s32 c;
    s8 *p;

    if ((arg0->unk1C1D != 0) || (arg1 != 0)) {
        if ((arg0->unk1C1C != 0) && (arg1 > 0)) {
            Sprintf_1343b8(sp40, D_0045F720, arg1);
        } else {
            Sprintf_1343b8(sp40, D_0045F728, arg1);
        }
        len = strlen(sp40);
        p = sp40;
        if (arg2 != 0) {
            MesWinAddPenX_272ae0(arg0, (arg2 - len) * (arg0->unk1C1E + (s16)(D_0045F200[0] - 1)));
        }
        w = arg0->unk1C1E + (FontGetDigitWidth_26f5a0() & 0xFF);
        for (; *p != 0; p++) {
            c = FontMapChar_26ed60(arg0, *p);
            if (c >= 0) {
                MesWinPushChar_2743c0(arg0, c);
                MesWinAddPenX_272ae0(arg0, w);
            }
        }
    }
}
