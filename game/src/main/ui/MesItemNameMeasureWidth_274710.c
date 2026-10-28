/* rgp:protos */
#define RGP_SELF_MesItemNameMeasureWidth_274710 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0045F200[0x400];

s32 MesItemNameMeasureWidth_274710(s32 arg0, s32 arg1)
{
    s16 def;
    u16 *p;
    s32 c;
    s32 cur;
    s32 max;
    s32 r;

    if (arg1 < 0) {
        return -1;
    }
    if (FontGetMesItemNameTable_270610((int)arg0) == 0) {
        return -1;
    }
    p = ((u16 *)MesItemNameLookup_274580(arg0, arg1));
    if (p == 0) {
        return -1;
    }
    cur = 0;
    max = 0;
    def = *(s32 *)D_0045F200 - 1;
    for (;;) {
        c = *p++;
        switch (c) {
        case 0xFF01:
            if (max < cur) {
                max = cur;
            }
            return max;
        case 0xFF00:
            if (max < cur) {
                max = cur;
            }
            cur = 0;
            break;
        default:
            if (c >= 0xFAEA && c < 0xFAFA) {
                r = MesWinGetStrVarWidth_277390(arg0, 0xFAF9 - c);
                if (r != -1) {
                    cur += r;
                }
            } else if (c >= 0xFD00 && c < 0xFE00) {
                cur += FontGetGaijiWidth_26f890(arg0, c);
            } else if (c >= 0xF900 && c < 0xFA00) {
                cur += c - 0xF900;
            } else if (FontIsAsciiCode_26ed80(arg0, c) != 0) {
                cur += FontGetCharWidth_26f4c0(arg0, c);
            } else {
                cur += def;
            }
            break;
        }
    }
}
