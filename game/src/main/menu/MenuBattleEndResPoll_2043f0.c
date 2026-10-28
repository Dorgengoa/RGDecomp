/* rgp:protos */
#define RGP_SELF_MenuBattleEndResPoll_2043f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S2043f0 {
    s32 id;
    u8 done;
} S2043f0;

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
/*rgp*/
extern u8 D_0045C350[0x20];
extern u8 D_0045C370[0x20];
extern s32 D_00481BDC;
extern S2043f0 D_00481C10[] __attribute__((section(".sdata")));
extern u8 D_004BBA40[0x300];
extern u8 D_004BBD40[0x400];

s32 MenuBattleEndResPoll_2043f0(void)
{
    S2043f0 *p;
    s32 ctx;
    s32 sum;
    s32 i;
    s32 id;
    s32 r;
    s32 h;
    s32 sp8C;

    ctx = ((s32)GetLoaderMgr_1f59d0());
    sum = 0;
    for (i = 0; i < 2; i++) {
        p = &D_00481C10[i];
        id = p->id;
        if (p->done != 0 || id <= -1) {
            continue;
        }
        r = LoaderGetStatus_1cd4f0(ctx, id);
        if (r == 1) {
            if (D_00481BDC == 0) {
                MenuBattleEndStackInit_2065e0();
                if (D_00481BDC == 0) {
                    return 0;
                }
            }
            sp8C = 0;
            h = ((s32)LoaderGetData_1cd490(ctx, id, &sp8C));
            if (i == 0) {
                ResGroupLoadByKind_42b840(((s32)GetMenuResGroup_206a40()), 2, 1, D_004BBD40, h);
                func_4EE600(D_004BBA40, D_004BBD40);
                TexGroupLoadFromArchive_202be0(h, D_0045C350, D_004BBD40, 0x32D, D_004BBD40);
                func_4EE5C0(D_004BBA40, MsgTableLoadFromArchive_202a50(h, D_0045C370, D_004BBD40));
            } else {
                TexGroupLoadFromBuf_202ad0(h, sp8C, D_004BBD40, 0x32D, D_004BBD40, 1, 0);
            }
            LoaderReleaseById_1cd340(ctx, id);
            p->id = -2;
        }
        p->done = r != 0;
    }
    for (i = 0; i < 2; i++) {
        sum += D_00481C10[i].done;
    }
    return sum == 2;
}
