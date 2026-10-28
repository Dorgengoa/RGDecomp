/* rgp:protos */
#define RGP_SELF_MapCfgFuncAnimeData_18aaa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Item {
    s32 x0;
    s32 x4;
    s32 x8;
    s8 xC;
    s8 xD;
    s8 xE;
    s8 xF;
    s8 x10;
    u8 pad11[0xF];
    u8 x20[0x10];
    u8 x30[0x10];
    u8 x40[0x10];
} Item;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0048125C;
extern u8 *D_004812DC;

s32 MapCfgFuncAnimeData_18aaa0(s64 *arg0, s32 arg1)
{
    Item *p;

    if (D_004812DC == 0) {
        return 0;
    }
    p = (Item *)(D_004812DC + 0x60);
    p->x0 = ((s32)MemStackStrDup_14cff0(SlotGetInt_15f720(arg0++), D_0048125C));
    p->x4 = ((s32)MemStackStrDup_14cff0(SlotGetInt_15f720(arg0++), D_0048125C));
    p->x8 = ((s32)MemStackStrDup_14cff0(SlotGetInt_15f720(arg0++), D_0048125C));
    p->xC = VariantGetInt_15f780(arg0++);
    p->xD = VariantGetInt_15f780(arg0++);
    VariantReadVec3_15f6c0(p->x20, arg0);
    VariantReadVec3_15f6c0(p->x30, arg0 + 3);
    VariantReadVec3_15f6c0(p->x40, arg0 + 6);
    arg0 += 9;
    p->xE = 0;
    if (arg1 >= 15) {
        p->xE = VariantGetInt_15f780(arg0++);
    }
    if (arg1 >= 16) {
        p->xF = VariantGetInt_15f780(arg0++);
    }
    if (arg1 >= 17) {
        p->x10 = VariantGetInt_15f780(arg0++);
    }
    return 1;
}
