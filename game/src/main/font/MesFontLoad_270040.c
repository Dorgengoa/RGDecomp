/* rgp:protos */
#define RGP_SELF_MesFontLoad_270040 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3
#pragma peephole off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *memcpy(void *, void *, s32);
extern u8 D_0045F5B0[0x400];
extern s32 D_004C3140[8];

s32 MesFontLoad_270040(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 *list;
    s32 h;
    s32 k;
    s32 i;
    s32 size;
    s32 p;
    s32 n;

    i = 0;
    do {
        D_004C3140[i] = 0;
        i++;
    } while (i < 8);
    if (arg1 == 0 || arg2 == 0) {
        return 0;
    }
    list = ((s32 *)MesFontGetTexFileList_270480(arg0));
    h = GetDrawCtxNameTable_15de40();
    for (k = 0; list[k] != 0; k++) {
        size = 0;
        p = ((s32)ArchiveGetFileByPath_1c2800(arg2, list[k], &size));
        if (p != 0 && size > 0) {
        if (k < 2) {
            FixedTexUpload_15d670(k, p, 0, 0);
            D_004C3140[k] = ((s32)FixedTexGet_15d610(k));
        } else if (k < 4) {
            FixedTexUpload_15d660(k - 2, p, 0, 0);
            D_004C3140[k] = ((s32)FixedTexGet_15d5c0(k - 2));
        } else {
            n = MemStackAllocQw_14d950(arg1, size / 16 + 1);
            memcpy((void *)n, (void *)p, size);
            D_004C3140[k] = Tim2RegisterPicture_159940(h, arg3, list[k], n, (long long)(0), 0);
        }
        }
    }
    NameTableAddEntry_159b70(h, arg3, D_0045F5B0, 0, 0x200, 0x20, 8, 0, 0, (int)(0));
    FontTablesLoad_2702e0(arg0, arg2);
    return 0;
}
