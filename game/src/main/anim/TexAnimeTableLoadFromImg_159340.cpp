#include "types.h"
#pragma opt_propagation off

extern "C" {
extern s32 MemStackNew_14e230(s32 arg0, s32 arg1);
extern void TexAnimeCfgParse_162780(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 TexAnimeTableCtor_162ed0(s32 arg0);
extern s32 memcmp(void *arg0, const void *arg1, s32 arg2);
extern u8 D_00458B18[0x400];
extern u8 D_00458B20[0x400];
extern u8 D_00458B28[0x400];
extern u8 D_00458B30[0x400];
}




extern "C" s32 TexAnimeTableLoadFromImg_159340(s32 arg0, u8 *arg1, s32 arg2)
{
    s32 type;
    u8 *p;
    u32 i;
    s32 r;
    bool b;

    if (arg1 == 0) {
        type = 0;
    } else if (memcmp(arg1, D_00458B20, 2) != 0) {
        type = 0;
    } else if (memcmp(arg1, D_00458B28, 3) == 0) {
        type = 1;
    } else if (memcmp(arg1, D_00458B30, 3) == 0) {
        type = 2;
    } else if (memcmp(arg1, D_00458B18, 3) == 0) {
        type = 3;
    } else {
        type = 0;
    }
    if (type != 3) {
        return 0;
    }
    if (arg2 == 0) {
        return 0;
    }
    p = arg1 + 0x10;
    for (i = 0; i < *(u32 *)(arg1 + 8); i++) {
        b = *p == 0x23;
        if (b) {
            r = MemStackNew_14e230(0x3C4, arg2);
            if (r != 0) {
                r = TexAnimeTableCtor_162ed0(r);
            }
            if (r == 0) {
                return 0;
            }
            TexAnimeCfgParse_162780(arg0, arg1 + *(s32 *)(p + 0x24), *(s32 *)(p + 0x34), arg2, r);
            return r;
        }
        p += 0x40;
    }
    return 0;
}
