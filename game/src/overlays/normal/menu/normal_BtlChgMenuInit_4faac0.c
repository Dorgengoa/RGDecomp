/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuInit_4faac0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004FAAC0 -- the gameplay panel/roster builder.  1,120 bytes.
 *
 * D_005278xx / D_005250xx / D_005263xx are OVERLAY data, far outside the gp
 * window (_gp 0x00485170 +/- 0x8000), so every one of them is `const` to take
 * %hi/%lo; the two that are WRITTEN go through the documented
 * `*(s32 *)&D_x = v` cast form.  The gp globals at 0x004844xx are inside the
 * window and are plain.
 *
 * The parameter is stored to D_00484444 immediately and every later use reads
 * the GLOBAL back -- retail reloads it at each site rather than holding it. */
typedef struct Rec {
    u8    pad00[4];
    void *f04;
    u8    pad08[2];
    __extension__ unsigned short   fA_lo : 2;
    unsigned short   fA_hi : 14;
} __attribute__((aligned(2))) Rec;
typedef struct Hdl { u8 pad00[0x16]; s16 f16; } Hdl;

extern u8  normal_D_00527820[];
extern s32 normal_D_00527828;
extern u8  normal_D_00527840[];
extern s32 normal_D_00527848;
extern u8  normal_D_00525030[];
extern u8  normal_D_00525050[];
extern u8  normal_D_005263B8[];
extern u8  normal_D_005263D0[];
extern u8  normal_D_005263E8[];
extern u8  normal_D_005263F0[];

extern void *D_00484444;
extern s32   D_0048444C;
extern void *D_00484450;
extern void *D_00484454;
extern void *D_00484458;
extern s16   D_00484464;
extern s16   D_00484468;
extern u8    D_00484470;
extern s16   D_004804DC;

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
extern void  memcpy(void *a, const void *b, s32 c);
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
extern s32   strlen(const void *a);
/*rgp*/

void normal_BtlChgMenuInit_4faac0(void *p)
{
    void *g;
    Rec *r;
    void *t;
    s32 n;
    u8 *a;
    u8 *b;
    u8 *c;
    s32 i;
    s32 k;
    s32 m;

    g = GetMenuResGroup_206a40();
    r = ((Rec *)ResGroupListFindById_42c500(g, 0x13));
    t = r->f04;
    n = r->fA_hi;
    D_00484444 = p;
    D_0048444C = 0;
    UiWidgetListReset_2912e0(normal_D_00527820);
    UiInitWidgetPool_290390(normal_D_00527820, D_00484444, n);
    UiAddWidgets_2901d0(normal_D_00527820, t, 0);
    *(s32 *)&normal_D_00527828 = 0x32B;
    D_00484450 = SceneSoundGetSlot0HandleCur_207df0();

    r = ((Rec *)ResGroupListFindById_42c500(g, 0x14));
    t = r->f04;
    n = r->fA_hi;
    UiWidgetListReset_2912e0(normal_D_00527840);
    UiInitWidgetPool_290390(normal_D_00527840, D_00484444, n);
    UiAddWidgets_2901d0(normal_D_00527840, t, 0);
    *(s32 *)&normal_D_00527848 = 0x32B;

    a = ((u8 *)MemStackAllocQw_14d950(D_00484444, 0x52));
    b = ((u8 *)MemStackAllocQw_14d950(D_00484444, 0x52));
    c = ((u8 *)MemStackAllocQw_14d950(D_00484444, 0x52));

    UiSetWidgetSprites_290b90(normal_D_00527840, 0x26, a);
    for (i = 0; i < 0x28; i++) {
        memcpy(a, normal_D_00525030, 0x20);
        a += 0x20;
    }
    *(s16 *)a = -1;
    UiSetWidgetSprites_290b90(normal_D_00527840, 0x55, b);
    for (i = 0; i < 0x28; i++) {
        memcpy(b, normal_D_00525030, 0x20);
        b += 0x20;
    }
    *(s16 *)b = -1;
    UiSetWidgetSubItems_28eec0(normal_D_00527840, 0x27, c);
    for (i = 0; i < 0x28; i++) {
        memcpy(c, normal_D_00525050, 0x20);
        c += 0x20;
    }
    *(s16 *)c = -1;

    D_00484458 = MemStackAlloc1K_28c2a0(D_00484444);
    r = ((Rec *)ResGroupListFindById_42c040(g, 0xA));
    t = r->f04;
    n = r->fA_hi;
    D_00484454 = MemStackNew_14e230(0x518, D_00484444);
    normal_BtlChgPageInit_5062f0(D_00484454);
    normal_BtlChgPageSetMemStack_506270(D_00484454, D_00484444);
    normal_BtlChgPageEntryListLoad_506210(D_00484454, t, D_00484450, n);
    normal_BtlChgPageSetLayout_506250(D_00484454, normal_D_00527840);
    ((Hdl *)UiEntryListFindByTag_28ea40(normal_UiPageGetList_289b50(D_00484454), 0x55F2))->f16 = 0;

    UiLayoutStringGlyphs_28a800(UiGetWidgetSprite_28fe10(normal_D_00527840, 0x51, 0), normal_D_005263B8, 0, 0, -2);
    m = strlen(normal_D_005263B8);
    for (k = 0; k < m; k++) {
        UiSetSpriteY_28fc90(normal_D_00527840, 0x51, 0, k);
    }
    UiLayoutStringGlyphs_28a800(UiGetWidgetSprite_28fe10(normal_D_00527840, 0x52, 0), normal_D_005263D0, 0, 0, -2);
    m = strlen(normal_D_005263D0);
    for (k = 0; k < m; k++) {
        UiSetSpriteY_28fc90(normal_D_00527840, 0x52, 0x19, k);
    }
    UiLayoutStringGlyphs_28a800(UiGetWidgetSprite_28fe10(normal_D_00527840, 0x53, 0), normal_D_005263E8, 0, 0, -2);
    m = strlen(normal_D_005263E8);
    for (k = 0; k < m; k++) {
        UiSetSpriteY_28fc90(normal_D_00527840, 0x53, 0x32, k);
    }
    UiLayoutStringGlyphs_28a800(UiGetWidgetSprite_28fe10(normal_D_00527840, 0x54, 0), normal_D_005263F0, 0, 0, -2);
    m = strlen(normal_D_005263F0);
    for (k = 0; k < m; k++) {
        UiSetSpriteY_28fc90(normal_D_00527840, 0x54, 0x4B, k);
    }

    D_00484464 = 0;
    D_004804DC = -1;
    D_00484468 = 0;
    D_00484470 = 0;
}
