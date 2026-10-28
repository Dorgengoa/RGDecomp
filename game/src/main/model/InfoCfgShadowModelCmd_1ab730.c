/* rgp:protos */
#define RGP_SELF_InfoCfgShadowModelCmd_1ab730 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 cnt;
    s32 *p4;
    s32 *p8;
    s32 best;
    s32 n;
} Info;

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
extern s32 D_0049D390[4];
extern s32 D_0049D398[4];
extern u8 *D_0049D418[4];

s32 InfoCfgShadowModelCmd_1ab730(s32 arg0)
{
    s32 a;
    s32 b;
    s32 c;
    u8 *base;
    u8 *q;
    s32 v;
    s32 t;
    s32 sp88[2];
    s32 *list;
    Info *info;
    s32 n;
    s32 cnt;
    s32 best;
    s32 i;
    s32 *e;
    s32 r;

    a = D_0049D390[0];
    b = D_0049D398[0];
    c = GetDrawCtx_15de80();
    base = D_0049D418[0];
    if (b == 0 || base == NULL) {
        return 0;
    }
    v = ((s32)ArchiveGetFileData_181dd0(a, SlotGetInt_15f720(arg0), 0));
    if (v == 0) {
        return 0;
    }
    sp88[0] = 0;
    ModelResRelocate_14bfd0(sp88, v);
    ModelResStripToPositionsMaybe_14e2b0(sp88);
    q = base + 0x270;
    ModelInit_151d50(q);
    ModelBuildFrames_1506c0(q, sp88, c, b);
    list = *(s32 **)(q + 0x104);
    t = *(s32 *)(base + 0x104);
    info = (Info *)(base + 0x430);
    while (t != 0 && list != NULL) {
        n = *list;
        if (n == 0) {
            break;
        }
        {
            info->p4 = ((s32 *)MemStackNew_14e1b0(n * 4, b));
            info->p8 = ((s32 *)MemStackNew_14e1b0(n * 4, b));
            if (info->p4 != NULL && info->p8 != NULL) {
                cnt = 0;
                best = -1;
                for (i = 0; i < n; i++) {
                    e = ((s32 *)ArrayGetChecked_152fd0(list, i));
                    if (e == NULL) {
                        continue;
                    }
                    if (*e == 0) {
                        continue;
                    }
                    r = ModelFindFrameIndexByName_151220(base, *e);
                    if (r < 0) {
                        continue;
                    }
                    info->p4[cnt] = r;
                    info->p8[cnt] = i;
                    if (best < 0 || best < r) {
                        best = r;
                    }
                    cnt++;
                }
                info->best = best;
                info->n = n;
                info->cnt = cnt;
            }
        }
        break;
    }
    *(s32 *)(base + 0x45C) = 1;
    return 1;
}
