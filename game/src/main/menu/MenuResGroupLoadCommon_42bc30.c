/* rgp:protos */
#define RGP_SELF_MenuResGroupLoadCommon_42bc30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

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

extern s32 D_00480264;
extern s32 D_0048027C;
extern s32 D_00480280;
extern s32 D_00480288;
extern s32 D_0048028C;
extern s32 D_00480290;
extern s32 D_00480294;
extern s32 D_00480298;
extern s32 D_0048029C;

s32 MenuResGroupLoadCommon_42bc30(s32 arg0)
{
    s32 cnt;
    s32 len;
    s8 key[0x108] __attribute__((aligned(16)));
    s8 val[0x1000] __attribute__((aligned(16)));
    s32 h;
    s32 buf;
    s8 *p;
    s8 *k;
    s8 *v;
    s32 i;
    s8 c;

    ResGroupUnloadGroup_42b650(arg0, 0);
    h = ((s32)GetReadBuffHeap_2025e0());
    buf = ((s32)MemStackHeapAlloc_14db10(h, 2, 0x14000, 0x40));
    if (buf == 0) {
        return 0;
    }
    cnt = 0;
    if (!(ResidentFileReadLocalizedMaybe_1c2860(D_00480264, buf, &cnt) & 0xFF) || cnt <= 0) {
        return 0;
    }
    len = 0;
    p = ((s8 *)ArchiveGetFileByPath_1c2800(buf, D_0048027C, &len));
    k = key;
    v = val;
    i = 0;
    while (i < len) {
        c = *p;
        i++;
        p++;
        if (c == 13 || c == 10) {
            break;
        }
        *k++ = c;
    }
    *k = 0;
    while (i < len) {
        c = *p;
        if (c != 13 && c != 10) {
            break;
        }
        p++;
        i++;
    }
    while (i < len) {
        i++;
        *v++ = *p++;
    }
    *v = 0;
    UiGlyphTableBuild_206b50(((s32)ResGroupGetStack_42c720(arg0, 0)), key, val);
    ResGroupRunScriptFromArchive_42bf70(arg0, 0, buf, D_00480280);
    ResGroupRunScriptFromArchive_42bf70(arg0, 0, buf, D_00480288);
    ResGroupRunScriptFromArchive_42bf70(arg0, 0, buf, D_0048028C);
    ResGroupRunScriptFromArchive_42bf70(arg0, 0, buf, D_00480290);
    ResGroupRunScriptFromArchive_42bf70(arg0, 0, buf, D_00480294);
    ResGroupRunScriptFromArchive_42bf70(arg0, 0, buf, D_00480298);
    ResGroupRunScriptFromArchive_42bf70(arg0, 0, buf, D_0048029C);
    MemStackReturnToOwnerMaybe_14dad0(h);
    MemStackHeapFree_14dcb0(h, buf);
    return 1;
}
