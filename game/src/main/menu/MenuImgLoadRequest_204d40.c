/* rgp:protos */
#define RGP_SELF_MenuImgLoadRequest_204d40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern void Sprintf_1343b8(void *arg0, void *arg1, void *arg2, s32 arg3);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0044B710[][2];
extern u8 D_0045C390[];
extern u8 D_0045C3A0[];
extern s32 D_0047E5C0;
extern s8 D_0047E5C4;
extern u8 D_004BBCE0[];

s32 MenuImgLoadRequest_204d40(s16 a, s16 b)
{
    u8 buf[0x20] __attribute__((aligned(16)));
    s32 h;

    if (a < 0 || b < 0) {
        return 1;
    }
    h = ((s32)GetLoaderMgr_1f59d0());
    GetDrawCtxNameTable_15de40();
    D_0047E5C0 = -1;
    D_0047E5C4 = 0;
    Sprintf_1343b8(buf, D_0045C390, D_0045C3A0, D_0044B710[a][b]);
    MemStackReset_14d830(D_004BBCE0);
    D_0047E5C0 = LoaderRequestFile_1cd870(h, buf, 0);
    LoaderQueueAppendSeparator_1cd670(h);
    return ~D_0047E5C0 == 0;
}
