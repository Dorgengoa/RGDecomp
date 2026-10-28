/* rgp:protos */
#define RGP_SELF_WorkIconCopyCharaItemIcon_28dc80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

/*rgp*/
/*rgp*/
extern void *memcpy(void *, void *, s32);
extern s32 D_0044B710[][2];
extern u8 D_004610E0[0x400];

s32 WorkIconCopyCharaItemIcon_28dc80(s32 *arg0, s32 arg1, s32 arg2)
{
    s32 h;
    s32 rem;
    s32 q;
    s32 dst;
    s32 src;
    s16 sel;
    void *p;
    s32 i;

    h = GetDrawCtxNameTable_15de40();
    if (h == 0) {
        return 1;
    }
    rem = arg1 % 8;
    q = arg1 / 8;
    p = NameTableFindByName_159fb0(h, D_004610E0, -1);
    if (p == NULL) {
        return 2;
    }
    sel = 1;
    dst = S32(p, 0x50) + (arg0[1] << 8);
    dst = dst + arg0[0];
    if (arg2 == 6) {
        sel = 0;
    }
    p = NameTableFindByName_159fb0(h, (void *)D_0044B710[arg2][sel], -1);
    if (p == NULL) {
        return 3;
    }
    src = S32(p, 0x50) + (q << 13) + rem * 32;
    for (i = 0; i < 32; i++) {
        memcpy((void *)dst, (void *)src, 0x20);
        dst += 0x100;
        src += 0x100;
    }
    return 0;
}
