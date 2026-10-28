/* rgp:protos */
#define RGP_SELF_title_TitleSessionInit_4f0cb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004F0CB0 -- boot the title screen.
 *
 * Copies the caller's 0x70-byte boot descriptor into the frame, brings up the
 * renderer, streams the title's three archives (0x800 script, 0x124F8 and
 * 0x61A80 data), builds the nine background layers, and hands the two big
 * buffers to title_TitleObjectsCreate_4ecbc0.
 *
 * CLOSED 2026-08-25 by the pragma below, after every source axis was a
 * measured null (154 statement orders, 24 declaration orders, all flat or
 * floored at 2: the copy loop's cursor bump landed between retail's two
 * stores).  With const-nonchanging analysis on, mwcc stops treating the
 * cursor as freshly derived per store and the bump drops below both, which is
 * retail's schedule.  Found by t_knob.py's recognised-pragma sweep (116
 * variants: 108 inert, this one 0 bad).  Per-TU; inert on 004ECE80/004F0600.
 */
#pragma opt_constnonchanging on

typedef struct Cfg {
    u8 pad0[4];
    s16 f4;
    u8 pad6[0x6A];
} Cfg;

typedef struct Scene {
    u8 pad0[0x3D2C];
    s32 f3D2C;
} Scene;

extern f32 D_0047D4A0;
extern u8 D_00480434;
extern u8 D_00480440;
extern s16 D_00481B90;
extern s32 D_00484288;
extern s32 D_0048428C;
extern u8 D_00484298;
extern s32 D_00484294;
extern u8 D_004842A4;
extern u8 D_004842B0;
extern u8 D_004B2570;
extern u8 title_D_004F1420;
extern u8 title_D_004F1460;
extern u8 title_D_004F1638;
extern u8 title_D_004F1648;
extern u8 title_D_004F1660;
extern u8 title_D_004F1678;
extern u8 title_D_004F1688;
extern u8 title_D_004F1698;
extern u8 title_D_004F1A30;
extern u8 title_D_004F1A90;
extern u8 title_D_004F1AF0;

extern void sceGsSyncV(s32 a);
/*rgp*/
extern void strcpy(void *a, void *b);
extern u32 strlen(void *a);
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

void title_TitleSessionInit_4f0cb0(const s32 *arg)
{
    Cfg c __attribute__((aligned(16)));
    s32 n;
    void *buf;
    void *disc;
    Scene *sc;
    void *fs;
    s32 *env;
    s32 i;
    void *prim;
    s32 *d;
    s32 k;
    s32 a;
    s32 b;

    d = (s32 *)&c;
    k = 14;
    do {
        a = arg[0];
        b = arg[1];
        arg += 2;
        d[0] = a;
        d[1] = b;
        d += 2;
        k--;
    } while (k > 0);
    D_00480434 = 1;
    D_00484294 = 0;
    D_004842A4 = 0;
    DbgLogMarkerMaybe_208a10();
    PadWaitReady_1849e0((void *)&D_004B2570);
    SoundInitStubRelated_207ed0();
    if (c.f4 == 1) {
        Nop_207f10();
    }
    if (GetKeyCapModeMaybe_1c3540() != 0) {
        SetAspectMode_1c6a90(1);
    }
    PauseSysInit_2f65a0();
    SetCurrentScene_1f5bd0(GetStaticScene_1c6c70());
    disc = GetMainStack_1c6dc0();
    MemStackReset_14d830(disc);
    MemStackAlign64_14d8e0(disc);
    DrawBufPairInitMaybe_15dc50(disc, 0x2710, disc, 0, 0xEA60);
    MemStackAlign64_14d8e0(disc);
    sc = ((Scene *)GetDrawCtx_15de80());
    MemStackHeapInit_14dee0((void *)((char *)sc + 0xD0), MemStackAllocQw_14d950(disc, 0x3A98), 0x3A98);
    DrawEnvSetVsyncInterval_144140(sc, 2, 0);
    DepthProbeSlotsReset_13fcb0(sc);
    fs = GetDrawCtxNameTable_15de40();
    DrawCtxNameTableConfigureMaybe_145980(sc, 0x180, 0x33A, disc);
    MemStackAlign64_14d8e0(disc);
    SceneResetDefaults_2f7720();
    WorldDataRebuild_1feac0(1);
    ReadBuffHeapInit_202290(disc);
    env = ((s32 *)GetLoaderMgr_1f59d0());
    LoaderClear_1ce040(env);
    *env = ((s32)GetReadBuffHeap_2025e0());
    LoaderInit_1cde60(env, 0x80, 0xC0, 0x10, 0x80, disc);
    MenuResGroupInit_206940();
    PadWaitReady_1849e0((void *)&D_004B2570);
    if (D_00481B90 != 0) {
        MemStackClear_14dff0((void *)&title_D_004F1AF0);
        MemStackInit_14d810((void *)&title_D_004F1AF0, MemStackAllocAligned64_14da10(disc, 0x800), 0x800);
        if (strlen((void *)&title_D_004F1648) < 0x10) {
            strcpy((void *)&title_D_004F1AF0, (void *)&title_D_004F1648);
        }
        MemStackReset_14d830((void *)&title_D_004F1AF0);
        MemStackAlign64_14d8e0((void *)&title_D_004F1AF0);
        buf = MemStackAllocQw_14d950((void *)&title_D_004F1AF0, 0x400);
        if (ResidentFileReadLocalizedMaybe_1c2860((void *)&title_D_004F1660, buf, &n) != 0) {
            NameTableRegisterImArchive_1594d0(fs, buf, 0x32C, (void *)&title_D_004F1AF0, 0);
            MemStackAlign64_14d8e0((void *)&title_D_004F1AF0);
            sc->f3D2C = 0;
            i = 0;
            do {
                sceGsSyncV(0);
                DrawListFrameBegin_1425d0(sc, 1);
                DrawListAddTexLoad_1418c0(sc, 0x32C, 1.0f);
                prim = DrawListBeginPrim_141b00(sc);
                GsPktSetTextured_13e400(prim, 0);
                GsPktSetOriginMode_13e2f0(prim, 0);
                GsPktSetAlphaBlend_13e500(prim, 1);
                GsPktSetBlendMode_13e4f0(prim, 1);
                GsPktEnableAlphaTest_13e4d0(prim, 1);
                GsPktSetZWriteMask_13e430(prim, 0);
                GsPktEnableZTest_13e460(prim, 0);
                GsPktSetTexFilter_13e3d0(prim, 0);
                GsPktOpenPrim_13f730(prim, 6);
                GsPktSetRGBAQ_13ee40(prim, 0, 0, 0, 0x80);
                GsPktSetXYZPixel_13f110(prim, 0, 0, 0);
                GsPktSetXYZPixel_13f110(prim, 0x1FF, 0x1BF, 0);
                GsPktClose_13f5b0(prim);
                GsPktSetOriginMode_13e2f0(prim, 0);
                GsPktSetAlphaBlend_13e500(prim, 1);
                GsPktSetBlendMode_13e4f0(prim, 2);
                GsPktEnableAlphaTest_13e4d0(prim, 1);
                GsPktSetZWriteMask_13e430(prim, 0);
                GsPktEnableZTest_13e460(prim, 0);
                GsPktSetTexFilter_13e3d0(prim, 1);
                GsPktSetTextured_13e400(prim, 1);
                GsPktSetUseUV_13e3e0(prim, 1);
                GsPktOpenPrim_13f730(prim, 6);
                GsPktSetTexture_13ec00(prim, NameTableFindByName_159fb0(fs, (void *)&title_D_004F1678, 0x32C));
                GsPktSetRGBAQ_13ee40(prim, 0x80, 0x80, 0x80, i << 5);
                GsPktSetUVFixed_13ed90(prim, title_TitleUvToFixed_4f13a0(0), title_TitleUvToFixed_4f13a0(0));
                GsPktSetXYZPixel_13f110(prim, 0x160, 0x160, 0);
                GsPktSetUVFixed_13ed90(prim, title_TitleUvToFixed_4f13a0(0x7F),
                            title_TitleUvToFixed_4f13a0(0x3F));
                GsPktSetXYZPixel_13f110(prim, 0x1DF, 0x19F, 0);
                GsPktClose_13f5b0(prim);
                DrawListEndPrim_141a20(sc);
                GfxEndFrame_141c20(sc, 1);
                i = i + 1;
            } while (i <= 8);
        }
    }
    WorldDataLoadParamPac_1fe5a0(0, 1);
    PadWaitReady_1849e0((void *)&D_004B2570);
    LightStateSetMatrices_15cc00((void *)&title_D_004F1420, (void *)&title_D_004F1460);
    LightStateSetAmbient_15cb30((void *)&D_00480440);
    DrawEnvSetClearColorVec_15ca70((void *)&D_004842B0);
    Tanf_1290b8(D_0047D4A0);
    ViewSetProjectionBasic_143180(sc, D_0047D4A0, 5.0f, (f32)0x2710, 0.75f);
    PadWaitReady_1849e0((void *)&D_004B2570);
    GameSceneBufsInitMaybe_202390(disc);
    SoundEnvPresetTableInitMaybe_207be0();
    SoundMapTablesLoad_207ac0(1);
    SceneSoundEnvApplyPreset_207e20(0x1F4, 1);
    LoaderSetSyncMode_1cd880(env, 1, 1);
    while (LoaderCountQueued_1cd620(env) > 0) {
        LoaderTickGlobal_2f74c0();
        FUN_00207a80_e1(1);
    }
    LoaderSetSyncMode_1cd880(env, 0, 0);
    MemStackClear_14dff0((void *)&title_D_004F1A90);
    MemStackInit_14d810((void *)&title_D_004F1A90, MemStackAllocAligned64_14da10(disc, 0x124F8), 0x124F8);
    if (strlen((void *)&title_D_004F1688) < 0x10) {
        strcpy((void *)&title_D_004F1A90, (void *)&title_D_004F1688);
    }
    MemStackReset_14d830((void *)&title_D_004F1A90);
    MemStackClear_14dff0((void *)&title_D_004F1A30);
    MemStackInit_14d810((void *)&title_D_004F1A30, MemStackAllocAligned64_14da10(disc, 0x61A80), 0x61A80);
    if (strlen((void *)&title_D_004F1698) < 0x10) {
        strcpy((void *)&title_D_004F1A30, (void *)&title_D_004F1698);
    }
    MemStackReset_14d830((void *)&title_D_004F1A30);
    D_00484288 = 0;
    D_0048428C = 0;
    title_TitleObjectsCreate_4ecbc0((void *)&title_D_004F1A90, (void *)&title_D_004F1A30);
    D_00484298 = 0;
}
