/* rgp:protos */
#define RGP_SELF_InfoCfgAmixerCmd_1ab3c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 a;
    s32 b;
} Cur;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0049D390[];
extern s32 D_0049D39C[];
extern s32 D_0049D3B8[];
extern s32 *D_0049D3BC[];
extern s32 D_0049D3C0[];
extern s32 D_0049D418[];
extern s32 D_0049D41C[];
extern s32 D_0049D420[];

s32 InfoCfgAmixerCmd_1ab3c0(Cur *arg0, s32 arg1)
{
    s32 a;
    s32 b;
    s32 base;
    s32 n;
    s32 m;
    s32 o;
    s32 i;
    s32 x;

    a = D_0049D390[0];
    b = D_0049D39C[0];
    base = D_0049D418[0];
    if (base == 0) {
        return 0;
    }
    if (b == 0) {
        return 0;
    }
    n = 0;
    D_0049D420[0] = VariantGetInt_15f780(arg0++);
    m = SlotGetInt_15f720(arg0++);
    if (arg1 >= 3) {
        n = VariantGetInt_15f780(arg0);
    }
    o = MotionListAddEntry_172520(base + 0x1F0, n, D_0049D420[0], b, b);
    if (o == 0) {
        return 0;
    }
    MotionEntryLoadAmixer_1738e0(o, a, m, b);
    D_0049D41C[0] = o;
    x = D_0049D420[0];
    i = D_0049D3B8[0];
    if (i < D_0049D3C0[0]) {
        D_0049D3B8[0] = i + 1;
        D_0049D3BC[0][i] = x;
    }
    return 1;
}
