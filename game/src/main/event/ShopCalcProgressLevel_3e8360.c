/* rgp:protos */
#define RGP_SELF_ShopCalcProgressLevel_3e8360 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 *unk8;
} Ent003E8360;

typedef struct {
    u8 pad0[0x94];
    s16 unk94;
} Tbl003E8360;

typedef struct {
    u8 pad0[0xC];
    Tbl003E8360 *unkC;
} Sub003E8360;

typedef struct {
    u8 pad0[0xA8];
    Sub003E8360 *unkA8;
} Mid003E8360;

typedef struct {
    u8 pad0[8];
    Mid003E8360 *unk8;
    u8 pad0C[4];
    s32 unk10;
    u8 pad14[4];
    s32 unk18;
} Obj003E8360;

/*rgp*/
/*rgp*/
/*rgp*/

s32 ShopCalcProgressLevel_3e8360(Obj003E8360 *arg0)
{
    s32 lv;
    s32 k;
    s16 *p;
    s32 count;
    Ent003E8360 *e;
    s32 j;
    s32 i;
    s32 n;

    if (arg0->unk18 == 0) {
        return 0;
    }
    count = 0;
    n = arg0->unk8->unkA8->unkC->unk94;
    for (i = 0; i < n; i++) {
        e = ((Ent003E8360 *)ArrayGetChecked_4247f0(arg0->unk8->unkA8->unkC, i));
        if (e == NULL) {
            continue;
        }
        lv = ((short)StateGetChapter_3cd5b0(arg0->unk10));
        k = e->unk0;
        if (k > lv) {
            continue;
        }
        lv = ((short)ProgressValueGet_3cd2c0(arg0->unk10, (long long)(k), (long long)(e->unk2), 0));
        p = e->unk8;
        for (j = 0; j < e->unk6; j++, p++) {
            if (*p > lv) {
            } else {
                count++;
            }
        }
    }
    if (count > 0) {
        count--;
    }
    return count;
}
