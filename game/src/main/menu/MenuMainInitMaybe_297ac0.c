/* rgp:protos */
#define RGP_SELF_MenuMainInitMaybe_297ac0 1
#include "port/game_protos.h"
#line 1
#pragma opt_dead_assignments off
#include "types.h"

typedef struct Res {
    u32 x0;
    s32 x4;
    u16 x8;
    __extension__ unsigned short lo : 2;
    unsigned short id : 14;
} __attribute__((aligned(2))) Res;

typedef struct Box {
    s16 x0;
    s16 x2;
    s16 x4;
    s16 x6;
    s16 x8;
    s16 xA;
    s16 xC;
    s16 xE;
    f32 x10;
    s32 x14;
    s16 x18;
    s16 x1A;
} Box;

typedef struct Elem {
    u8 pad0[0x20];
    Box *x20;
} Elem;

typedef struct Flags {
    u8 b0 : 1;
} Flags;

extern u8 D_00461110[];
extern s32 D_004659E8[];
extern f32 D_0047D288;
extern f32 D_0047D5D0;
extern f32 D_0047D920;
extern s16 D_0047EBC0;
extern s16 D_0047EBC2;
extern s16 D_0047EBC4;
extern s16 D_0047EBC8;
extern s16 D_0047EBCA;
extern s16 D_0047EBCC;
extern s16 D_0047EBD0;
extern s16 D_0047EBD2;
extern s16 D_0047EBD4;
extern s16 D_0047EBD8;
extern s16 D_0047EBDA;
extern s16 D_0047EBDC;
extern s32 D_00482330;
extern s32 D_00482334;
extern s16 D_00482350;
extern s32 D_00482354;
extern s32 D_00482358;
extern s16 *D_0048235C;
extern void *D_00482360;
extern void *D_00482364;
extern void *D_00482368;
extern void *D_0048236C;
extern s32 D_00482370;
extern s32 D_00482374;
extern s32 D_00482378;
extern s32 D_0048237C;
extern s32 D_00482380;
extern s32 D_00482384;
extern s32 D_00482388;
extern s32 D_0048238C;
extern s16 D_0048239C;
extern u8 D_004B2570[];
extern u8 D_004DB1B0[];
extern s32 D_004DB1B8[];
extern u8 D_004DB1D0[];
extern s32 D_004DB1D8[];
extern u8 D_004DB1F0[];
extern s32 D_004DB208[];
extern Flags D_004DB210[];
extern u8 D_004DB211[];

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
/*rgp*/
/*rgp*/
/*rgp*/
void *memcpy(void *, const void *, u32);

void MenuMainInitMaybe_297ac0(void)
{
    s32 k;
    s32 base;
    Res *r;
    s32 h;
    u32 id;
    s32 h3;
    s32 p;
    s32 i;
    Elem *e;
    Box *b;

    base = ((s32)GetMenuResGroup_206a40());
    r = ((Res *)ResGroupListFindById_42c500(base, 0x28));
    h = r->x4;
    id = r->id;
    UiWidgetListReset_2912e0(D_004DB1B0);
    UiInitWidgetPool_290390(D_004DB1B0, D_00482334, id);
    UiAddWidgets_2901d0(D_004DB1B0, h, 0);
    D_004DB1B8[0] = 0x32B;
    UiTextStyleReset_290450();
    MenuMainPanelBuffersInit_293f50(D_00482334);
    r = ((Res *)ResGroupListFindById_42c500(base, 0x29));
    h = r->x4;
    id = r->id;
    UiWidgetListReset_2912e0(D_004DB1D0);
    UiInitWidgetPool_290390(D_004DB1D0, D_00482334, id);
    UiAddWidgets_2901d0(D_004DB1D0, h, 0);
    D_004DB1D8[0] = 0x32D;
    UiTextStyleReset_290450();
    r = ((Res *)ResGroupListFindById_42c040(base, 0x1E));
    h3 = r->x4;
    id = r->id;
    UiEntryListReset_28ec80(D_004DB1F0);
    UiEntryListAlloc_28e0c0(D_004DB1F0, D_00482334, id);
    UiEntryListLoad_28eb70(D_004DB1F0, h3, D_004DB1B0);
    D_004DB208[0] = D_00482330;
    D_004DB210[0].b0 = 0;
    D_004DB211[0] = 0;
    UiSetWidgetsVisibleById_291110(D_004DB1B0, 0x227, 0, 1);
    k = MenuStateTableForId_42c950(base, 0x1E);
    D_00482354 = 0;
    D_00482350 = 0;
    D_00482358 = k;
    PadClearRepeatAll_183960(D_004B2570);
    PadSetRepeat_183d50(D_004B2570, 0xF00C, 0xC, 7);
    PadSetStickDpadThreshold_183950(D_004B2570, 0x78);
    D_00482368 = D_004DB1B0;
    D_0048236C = D_004DB1D0;
    D_00482370 = ((s32)MemStackNew_14e230(0x4D4, D_00482334));
    D_00482374 = ((s32)MemStackNew_14e230(0x1B4, D_00482334));
    D_0048237C = ((s32)MemStackNew_14e230(0x74, D_00482334));
    D_00482378 = ((s32)MemStackNew_14e230(0x78, D_00482334));
    p = ((s32)MemStackNew_14e230(0x178, D_00482334));
    if (p != 0) {
        UiSelFrameReset_28db70(p + 0x144);
    }
    D_00482380 = p;
    D_00482384 = ((s32)MemStackNew_14e230(0x98, D_00482334));
    D_00482388 = (p = ((s32)MemStackNew_14e230(0x290, D_00482334))) ? (EffTableCtor_1a11b0(p + 0x5C), MemStackCtor_14e030(p + 0x178), UiSelFrameReset_28db70(p + 0x1D8), (s32)p) : (s32)p;
    D_0048238C = ((s32)MemStackNew_14e230(0x7AC, D_00482334));
    MenuItemGridInitMaybe_2a5920(D_00482374, D_004659E8[0] + 1, 0, 1);
    MenuSetPanelHandles_2a5900(D_00482374, D_00482368, D_004DB1F0, &D_00482350, D_00482334);
    MenuPartyStateReset_29fbf0(D_00482370);
    MenuSetPanelHandles_29fbd0(D_00482370, D_004DB1B0, D_004DB1F0, &D_00482350, D_00482334);
    MenuClearPanelHandles_357320(D_0048237C);
    MenuSetPanelHandles_357300(D_0048237C, D_004DB1B0, D_004DB1F0, &D_00482350, D_00482334);
    MenuClearPanelHandles_341120(D_00482378);
    MenuSetPanelHandles_341100(D_00482378, D_004DB1B0, D_004DB1F0, &D_00482350, D_00482334);
    MenuClearPanelHandles_35b8e0(D_00482380);
    MenuSetPanelHandles_35b8c0(D_00482380, D_004DB1B0, D_004DB1F0, &D_00482350, D_00482334);
    MenuWeaponCombineClearHandles_3636c0(D_00482384);
    MenuWeaponCombineSetHandles_3636a0(D_00482384, D_004DB1B0, D_004DB1F0, &D_00482350, D_00482334);
    MenuCatalogPageClearHandles_360e40(D_00482388);
    MenuCatalogPageInit_360d60(D_00482388, D_004DB1B0, D_004DB1F0, &D_00482350, D_00482334);
    UiPageSetMemStack_289c40(D_00482370, D_00482334);
    UiPageSetStateTable_289c10(D_00482370, k);
    UiPageSetLayout_289c30(D_00482370, D_004DB1B0);
    UiPageSetLayout_289c30(D_00482378, D_004DB1B0);
    UiPageSetLayout_289c30(D_0048237C, D_004DB1B0);
    UiPageSetLayout_289c30(D_00482380, D_004DB1B0);
    UiPageSetLayout_289c30(D_00482388, D_004DB1B0);
    UiPageEntryListReload_289b70(D_00482370, h3, D_00482330, -1);
    D_00482364 = D_004DB1F0;
    D_00482360 = D_004DB1B0;
    D_0048235C = &D_00482350;
    UiSetWidgetsVisibleById_291110(D_004DB1B0, 7, 1, 1);
    UiSetWidgetsVisibleById_291110(D_004DB1B0, 1, 1, 1);
    UiSetWidgetsVisibleById_291110(D_004DB1B0, 3, 1, 1);
    UiSetWidgetsVisibleById_291110(D_004DB1B0, 4, 1, 1);
    UiSetWidgetAlpha_2907a0(D_004DB1B0, 0xA, 1.0f);
    UiSetWidgetAlpha_2907a0(D_004DB1B0, 9, 1.0f);
    UiSetWidgetPos_290f60(D_004DB1B0, 2, 0xFA, 0xA2);
    UiSetWidgetPos_290f60(D_004DB1B0, 1, -0x40, -0x40);
    UiSetWidgetPos_290f60(D_004DB1B0, 4, 0, 0);
    UiSetWidgetPos_290f60(D_004DB1B0, 0xA, 0xE7, 0x89);
    UiSetWidgetPos_290f60(D_004DB1B0, 9, 0xF6, 0x9A);
    UiSetWidgetPos_290f60(D_004DB1B0, 8, 0xED, 0x8E);
    UiSetWidgetColor_2905b0(D_004DB1B0, 8, 0.0f, 0.0f, 0.0f, D_0047D920);
    UiSetWidgetAlpha_2907a0(D_004DB1B0, 1, 1.0f);
    UiSetWidgetAlpha_2907a0(D_004DB1B0, 2, 1.0f);
    UiSetWidgetPos_290f60(D_004DB1B0, 0x33, 0x9A, -0x28);
    UiSetWidgetPos_290f60(D_004DB1B0, 0x32, 0x9D, -0x25);
    MenuShowLocationName_299190(0x35);
    UiSetSpriteW_28fbf0(D_004DB1B0, 0x15, 0x74, 0);
    UiSetSpriteX_28fcd0(D_004DB1B0, 0x1E, -2, 0);
    UiSetSpriteX_28fcd0(D_004DB1B0, 0x25, -2, 0);
    if (D_0048239C == 1) {
        UiSetWidgetAlpha_2907a0(D_004DB1B0, 0x3F, 1.0f);
        UiSetWidgetsVisibleById_291110(D_004DB1B0, 0x33, 1, 1);
        UiSetWidgetsVisibleById_291110(D_004DB1B0, 0x32, 1, 1);
        UiSetWidgetColor_2905b0(D_004DB1B0, 0x32, 0.0f, 0.0f, 0.0f, D_0047D920);
        UiMoveWidgetUniform_290f50(D_004DB1B0, 0x33, 0x9A, 0x12, D_0047D5D0, 0);
        UiMoveWidgetUniform_290f50(D_004DB1B0, 0x32, 0x9D, 0x15, D_0047D5D0, 0);
    }
    UiSetWidgetsVisibleById_291110(D_004DB1B0, 0x41, 0, 1);
    UiSetWidgetPos_290f60(D_004DB1B0, 0x41, -0x32, -0x32);
    UiSetWidgetsVisibleById_291110(D_004DB1B0, 0x27, 0, 1);
    UiSetWidgetPos_290f60(D_004DB1B0, 0x27, -0x32, -0x32);
    UiSetWidgetsVisibleById_291110(D_004DB1B0, 0x11B, 0, 1);
    UiSetWidgetsVisibleById_291110(D_004DB1B0, 0x11C, 0, 1);
    UiSetWidgetsVisibleById_291110(D_004DB1B0, 0x11D, 0, 1);
    UiSetWidgetsVisibleById_291110(D_004DB1B0, 0x14C, 0, 1);
    UiSetWidgetAlpha_2907a0(D_004DB1B0, 0x14C, 0.0f);
    UiSetWidgetsVisibleById_291110(D_004DB1B0, 0x183, 0, 1);
    UiSetWidgetVisible_290010(D_004DB1B0, 0x151, 0, -1);
    UiSetWidgetsVisibleById_291110(D_004DB1B0, 0x14D, 0, 1);
    UiSetWidgetsVisibleById_291110(D_004DB1B0, 0x15, 0, 1);
    UiSetWidgetsVisibleById_291110(D_004DB1B0, 0x1A9, 0, 1);
    if (IsTgsDemoBuild_207f20() != 0) {
        s16 xs[3];
        s16 ys[3];
        {
        s16 *py = (s16 *)(u32)ys;
        xs[0] = D_0047EBC0;
        xs[1] = D_0047EBC2;
        xs[2] = D_0047EBC4;
        py[0] = D_0047EBC8;
        py[1] = D_0047EBCA;
        py[2] = D_0047EBCC;
        }
        for (i = 0; i < 3; i++) {
            e = ((Elem *)UiFindWidget_290460(D_004DB1B0, i + 0x22));
            if (e != 0) {
                b = e->x20;
                if (b != 0) {
                    b->x0 = xs[i] + 10;
                    b->x2 = ys[i];
                    b->x8 = 0xAC;
                    b->xA = 0x40;
                    b->xC = 0x14;
                    b->x4 = 0x14;
                    b->xE = 0x14;
                    b->x6 = 0x14;
                    b->x10 = 3.0f;
                    b->x14 = 0;
                    b->x18 = 0x14;
                    b->x1A = -1;
                }
            }
        }
        UiSetWidgetColor_2905b0(D_004DB1B0, 0x22, D_0047D288, D_0047D288, D_0047D288, -1.0f);
        { f32 m = -1.0f; UiSetWidgetColor_2905b0(D_004DB1B0, 0x23, D_0047D288, D_0047D288, D_0047D288, m); }
        { f32 m = -1.0f; UiSetWidgetColor_2905b0(D_004DB1B0, 0x24, D_0047D288, D_0047D288, D_0047D288, m); }
        { f32 m = -1.0f; UiSetWidgetColor_2905b0(D_004DB1B0, 0x1B1, D_0047D288, D_0047D288, D_0047D288, m); }
    } else {
        s16 xs[3];
        s16 ys[3];
        {
        s16 *py = (s16 *)(u32)ys;
        xs[0] = D_0047EBD0;
        xs[1] = D_0047EBD2;
        xs[2] = D_0047EBD4;
        py[0] = D_0047EBD8;
        py[1] = D_0047EBDA;
        py[2] = D_0047EBDC;
        }
        for (i = 0; i < 3; i++) {
            e = ((Elem *)UiFindWidget_290460(D_004DB1B0, i + 0x22));
            if (e != 0) {
                b = e->x20;
                if (b != 0) {
                    s32 ok = 0;
                    if (i == 0) {
                        ok = TopMenuIsHunterUnlocked_29ac90();
                    } else if (i == 1) {
                        ok = TopMenuRow5UnlockedMaybe_29ac50();
                    } else if (i == 2) {
                        ok = TopMenuRow6UnlockedMaybe_29ac20();
                    }
                    if (ok != 0 || D_0048239C == 1) {
                        memcpy(b, D_00461110 + i * 32, 32);
                    } else {
                        b->x0 = xs[i] + 10;
                        b->x2 = ys[i];
                        b->x8 = 0xAC;
                        b->xA = 0x40;
                        b->xC = 0x14;
                        b->x4 = 0x14;
                        b->xE = 0x14;
                        b->x6 = 0x14;
                        b->x10 = 3.0f;
                        b->x14 = 0;
                        b->x18 = 0x14;
                        b->x1A = -1;
                    }
                }
            }
        }
    }
}
