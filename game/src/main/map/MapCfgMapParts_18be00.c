/* rgp:protos */
#define RGP_SELF_MapCfgMapParts_18be00 1
#include "port/game_protos.h"
#line 1
#pragma opt_propagation off
#include "types.h"

typedef rg_u128 u128;

/*rgp*/
/*rgp*/
/*rgp*/
extern void strcpy(void *dst, const char *src);

extern s32 D_00481254;
extern u128 D_00481270 __attribute__((section(".sdata")));
extern u128 D_00481280 __attribute__((section(".sdata")));
extern f32 D_00481290;
extern f32 D_00481294;
extern f32 D_00481298;
extern s32 D_0048129C;
extern s32 D_004812C0;
extern s32 D_004812C4;
extern s8 D_0049CE80[0x80];
extern s8 D_0049CF00[0x80];
extern s8 D_0049CF80[0x80];
extern s8 D_0049D000[0x80];
extern u8 D_0049D080[0x400];

s32 MapCfgMapParts_18be00(s64 *arg0, s32 arg1) {
    s32 temp_2;

    temp_2 = SlotGetInt_15f720((s32)arg0++);
    D_00481254 = 0;
    if (temp_2 == 0) {
        return 0;
    }
    strcpy(D_0049CE80, (const char *)temp_2);
    {
        u8 *p = D_0049D080;
        D_00481298 = 1.0f;
        D_00481294 = 1.0f;
        D_00481290 = 1.0f;
        D_00481270 = 0;
        D_00481280 = 0;
        D_0048129C = 0;
        FarClipRecInit_186e30(p);
    }
    D_004812C4 = 1;
    if (arg1 > 1) {
        D_004812C4 = VariantGetInt_15f780((s32)arg0);
    }
    D_004812C0 = 0;
    D_0049CF00[0] = 0;
    D_0049CF80[0] = 0;
    D_0049D000[0] = 0;
    return 1;
}
