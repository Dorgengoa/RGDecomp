/* rgp:protos */
#define RGP_SELF_ShopBuyItem_3ce4e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x160];
    s64 unk160;
} Pool;

typedef struct {
    u8 pad0[0x10];
    s32 unk10;
    u8 pad14[0x18 - 0x14];
    Pool *unk18;
} Mgr;

typedef struct {
    u8 pad0[0x2];
    s16 unk2;
    s16 unk4;
} Def;

typedef struct {
    s32 unk0;
    Def *unk4;
    s16 unk8;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern Mgr *D_00483910;

s32 ShopBuyItem_3ce4e0(Obj *arg0, s32 arg1)
{
    s32 id;
    s64 lim;
    s32 unit;
    s32 n;
    s32 sum;
    s32 i;
    s16 h;

    if (arg1 < 0) {
        return 0;
    }
    if (D_00483910 == NULL) {
        return 0;
    }
    if (arg0->unk0 == 0) {
        return 0;
    }
    if (arg0->unk4 == NULL) {
        return 0;
    }
    if (arg0->unk8 >= 0 && arg0->unk8 < arg1) {
        return 0;
    }
    id = arg0->unk4->unk2;
    lim = D_00483910->unk18->unk160;
    unit = ShopRowGetPrice_3ce6e0(arg0);
    if (unit * arg1 > (s32)lim) {
        return 0;
    }
    n = 0;
    sum = 0;
    for (i = 0; i < arg1; i++) {
        if (((s32)InvAddItemCoreMaybe_3c6540(D_00483910->unk18, id, 0, 1, -1, 0, 0)) == 0) {
            break;
        }
        n++;
        sum += unit;
    }
    if (arg0->unk8 > 0 && arg0->unk8 < 100) {
        h = arg0->unk8 - (s16)n;
        arg0->unk8 = h;
        ShopStockSet_3cbc50(D_00483910->unk10, arg0->unk4->unk4, h);
    }
    PartyAddMoney_3c8e90(D_00483910->unk18, -sum);
    return 1;
}
