/* rgp:protos */
#define RGP_SELF_DynClothCopy_168e90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef struct {
    s32 v[16];
} Blk00168e90;

typedef struct {
    f32 x, y, z, w;
} FV00168e90;

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 pad8[8];
    Blk00168e90 unk10;
    Blk00168e90 unk50;
    s32 unk90;
    s32 **unk94;
    s32 unk98;
    s32 unk9C;
    s32 unkA0;
    u128 *unkA4;
    u128 *unkA8;
    u128 *unkAC;
    u128 *unkB0;
    u128 *unkB4;
    s32 unkB8, unkBC, unkC0, unkC4, unkC8, unkCC, unkD0, unkD4;
    s32 unkD8, unkDC, unkE0, unkE4, unkE8, unkEC, unkF0, unkF4, unkF8;
    u8 padFC[4];
    FV00168e90 unk100;
    f32 unk110;
    f32 unk114;
    s32 unk118;
    f32 unk11C;
    f32 unk120;
    u8 pad124[0xC];
    FV00168e90 unk130;
    s32 unk140;
    f32 unk144;
    s32 unk148;
    f32 unk14C;
    s32 unk150;
    s32 unk154;
    u8 pad158[8];
    FV00168e90 unk160;
} S00168e90;

/*rgp*/
/*rgp*/

void DynClothCopy_168e90(S00168e90 *src, S00168e90 *dst, s32 arg2, s32 arg3)
{
    s32 i;
    s32 *p;

    dst->unk0 = src->unk0;
    dst->unk4 = src->unk4;
    dst->unk10 = src->unk10;
    dst->unk50 = src->unk50;
    dst->unk90 = src->unk90;
    dst->unk94 = src->unk94;
    dst->unk98 = src->unk98;
    dst->unk9C = src->unk9C;
    dst->unkA0 = src->unkA0;
    dst->unkA4 = src->unkA4;
    dst->unkA8 = src->unkA8;
    dst->unkAC = src->unkAC;
    dst->unkB0 = src->unkB0;
    dst->unkB4 = src->unkB4;
    dst->unkB8 = src->unkB8;
    dst->unkBC = src->unkBC;
    dst->unkC0 = src->unkC0;
    dst->unkC4 = src->unkC4;
    dst->unkC8 = src->unkC8;
    dst->unkCC = src->unkCC;
    dst->unkD0 = src->unkD0;
    dst->unkD4 = src->unkD4;
    dst->unkD8 = src->unkD8;
    dst->unkDC = src->unkDC;
    dst->unkE0 = src->unkE0;
    dst->unkE4 = src->unkE4;
    dst->unkE8 = src->unkE8;
    dst->unkEC = src->unkEC;
    dst->unkF0 = src->unkF0;
    dst->unkF4 = src->unkF4;
    dst->unkF8 = src->unkF8;
    dst->unk100 = src->unk100;
    dst->unk110 = src->unk110;
    dst->unk114 = src->unk114;
    dst->unk118 = src->unk118;
    dst->unk11C = src->unk11C;
    dst->unk120 = src->unk120;
    dst->unk130 = src->unk130;
    dst->unk140 = src->unk140;
    dst->unk144 = src->unk144;
    dst->unk148 = src->unk148;
    dst->unk14C = src->unk14C;
    dst->unk150 = src->unk150;
    dst->unk154 = src->unk154;
    dst->unk160 = src->unk160;
    dst->unk4 = arg2;
    if (arg2 == 0) {
        return;
    }
    if (src->unk90 > 0 && src->unk94 != 0) {
        dst->unk94 = (s32 **)MemStackNew_14e1b0(src->unk90 * 4, arg3);
        if (dst->unk94 == 0) {
            return;
        }
        for (i = 0; i < src->unk90; i++) {
            dst->unk94[i] = 0;
            p = src->unk94[i];
            if (p != 0) {
                dst->unk94[i] = (s32 *)((s32)FrameFindByName_149ed0(arg2, *p));
            }
        }
    }
    if (src->unkA0 > 0) {
        dst->unkA4 = (u128 *)MemStackNew_14e1b0(src->unkA0 * 16, arg3);
        dst->unkA8 = (u128 *)MemStackNew_14e1b0(src->unkA0 * 16, arg3);
        dst->unkAC = (u128 *)MemStackNew_14e1b0(src->unkA0 * 16, arg3);
        dst->unkB0 = (u128 *)MemStackNew_14e1b0(src->unkA0 * 16, arg3);
        dst->unkB4 = (u128 *)MemStackNew_14e1b0(src->unkA0 * 16, arg3);
        for (i = 0; i < src->unkA0; i++) {
            dst->unkA4[i] = src->unkA4[i];
            dst->unkA8[i] = src->unkA8[i];
            dst->unkAC[i] = src->unkAC[i];
            dst->unkB0[i] = src->unkB0[i];
            dst->unkB4[i] = src->unkB4[i];
        }
    }
}
