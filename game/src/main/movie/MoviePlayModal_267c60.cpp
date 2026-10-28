/* rgp:protos */
#line 1
#include "types.h"

struct Cfg {
    u8 pad[0xD8];
    s32 w;               /* 0xD8 */
    s32 h;               /* 0xDC */
    bool flag;           /* 0xE0 */
    u8 padE1[0xB];
    s32 n;               /* 0xEC */
};

struct Wnd {
    u8 pad[0x17970];
    s32 x;               /* 0x17970 */
    s32 y;               /* 0x17974 */
};

struct Game {
    u8 pad[0x5CF0];
    s32 id;              /* 0x5CF0 */
    s32 count;           /* 0x5CF4 */
};

struct Sub {
    u8 pad[0x1C];
    s16 kind;            /* 0x1C */
};

struct Ctl {
    u8 pad[0xC];
    Sub *sub;            /* 0x0C */
    s32 f10;             /* 0x10 */
};

extern "C" {
void DrawCtxVif1HandlerStop_15dc40(void);
f32 GameSceneGetTimeStep_1ceba0(Game *);
float GameSceneSoundGetVolume_1d0540(Game *);
float GameSceneSoundSlot4GetVolume_1d0770(Game *);
void GameSceneSoundSetVolumeNow_1d0400(Game *, f32);
void GameSceneSoundSlot4SetVolume_1d0630(Game *, f32);
s32 CdDiskWatchSetEnabled_17fe80(s32);
s32 GetDrawCtx_15de80(void);
s32 GetDrawCtxNameTable_15de40(void);
s32 GetMesMgr_277e90(void);
s32 DrawEnvGetWidth_1451e0(s32);
s32 DrawEnvGetHeight_1451d0(s32);
s32 DrawEnvGetPsmBpp_145140(s32);
Wnd *MemStackNew_14e230(s32, s32);
Wnd *MoviePlayerCtor_1d6130(Wnd *);
void MemStackAlign64_14d8e0(s32);
void MovieOpenParamInit_1d6230(Cfg *);
void MovieOpenParamSetSource_1d61c0(Cfg *, s32, s32);
void MoviePlayerOpen_1d61a0(Wnd *, Cfg *);
void NameTableFreeGroup_158ac0(s32, s32);
void NameTableAddEntry_159b70(s32, s32, void *, s32, s32, s32, s32, s32, s64, int);
void DrawListAddTexLoad_1418c0(s32, s32, f32);
void MoviePlayerStart_1d5b50(Wnd *, void *);
void MoviePlayerWaitTick_1d5810(Wnd *);
s32 MovieIsStarted_1d5640(void);
void MesFontPagesSetFlagRelated_270440(s32);
u8 PauseIsAllowed_2f6650(void);
s32 GetStreamMgr_207ea0(void);
Ctl *GetGameData_1fede0(void);
void DrawListFrameBegin_1425d0(s32, s32);
void PadUpdate_1843a0(void *);
s32 PadIsTriggered_1839f0(void *, s32);
s32 PadIsAnalogMode_184960(void *);
s32 MovieIsReadStalled_1d62a0(void);
void StateFlagSet_3ccb70(s32, s32, s32, s32);
void AudioDecSetInputVolumeF_1d52e0(f32);
void MoviePause_1d5b40(void);
void SoundRpcStopAllThunkMaybe_1bd680(s32, int, int, int);
void SoundRpcFrameTickThunkMaybe_1bd690(s32, int, int, int);
void StreamMgrUpdate_1d6940(s32, f32);
void MovieDrawFrame_1d5870(Wnd *);
void MovieFrameQueueSendNext_1d4b20(void);
void Nop_207f60(void);
void Nop_207f50(void);
void MesMgrDrawAll_277a50(s32);
void MesMgrUpdateAll_277ac0(s32);
void DrawTexturedRect_26a920(s32, s32, s32, s32, s32, s32, s32, s32, void *);
void PauseReasonDrawMaybe_2f5c40(u8);
void PadLostMsgDrawMaybe_2f5e90(s32, s32);
void DiscStatusMessageDraw_39ecf0(s32);
void GfxEndFrame_141c20(s32, s32);
void MovieFrameResend_1d4be0(void);
void DelayThread_117618(s32);
s32 SceneSoundGetSlot0HandleCur_207df0(void);
void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
void ScreenFadeOutColor_1cf730(Game *, s32, f32, f32, f32);
void MovieResume_1d5b30(void);
void MoviePlayerShutdown_1d56c0(Wnd *);
void MemStackReset_14d830(s32);
s32 MovieIsFinished_1d5680(void);
s32 MovieGetFrameCount_1d52d0(void);
void ScreenFadeDraw_1cf6d0(Game *);
void ScreenFadeStep_1cf6e0(Game *);
void EventCueStep_2491b0(u8 *, Game *);
void GameSceneSoundFadeVolume_1d0370(Game *, s32, f32);
void GameSceneSoundSlot4FadeTo_1d0610(Game *, s32, f32);
extern Game *D_00481F78;
extern u8 *D_00482040;
extern u8 D_0045F190[];
extern u8 D_0045F1A0[];
extern u8 D_004B2570[];
extern f32 D_0045B078[];
extern f32 D_0047DAD0;
}

extern "C" s32 MoviePlayModal_267c60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 mode, s32 arg5) {
    Cfg cfg __attribute__((aligned(16)));
    s32 quit;
    s32 saved;
    s32 db;
    s32 x154;
    s32 cnt;
    s32 st;
    s32 t120;
    s32 t110;
    bool drawn;
    s32 k;
    s32 kind;
    Ctl *ctl;
    s32 ok;
    Game *g;
    f32 f;
    s32 mgr;
    s32 W;
    s32 H;
    s32 K;
    Wnd *w;
    s32 n;
    s32 fade;
    s32 obj;
    s32 id;
    s32 state;
    s32 timer;

    DrawCtxVif1HandlerStop_15dc40();
    g = D_00481F78;
    f = GameSceneGetTimeStep_1ceba0(g);
    GameSceneSoundGetVolume_1d0540(g);
    GameSceneSoundSlot4GetVolume_1d0770(g);
    GameSceneSoundSetVolumeNow_1d0400(g, 0.0f);
    GameSceneSoundSlot4SetVolume_1d0630(g, 0.0f);
    saved = CdDiskWatchSetEnabled_17fe80(0);
    mgr = GetDrawCtx_15de80();
    db = GetDrawCtxNameTable_15de40();
    x154 = GetMesMgr_277e90();
    W = DrawEnvGetWidth_1451e0(mgr);
    H = DrawEnvGetHeight_1451d0(mgr);
    K = DrawEnvGetPsmBpp_145140(mgr);
    *(s32 *)(mgr + 0x3D2C) = 0;
    w = MemStackNew_14e230(0x17980, arg1);
    if (w != 0) {
        w = MoviePlayerCtor_1d6130(w);
    }
    MemStackAlign64_14d8e0(arg1);
    MovieOpenParamInit_1d6230(&cfg);
    MovieOpenParamInit_1d6230(&cfg);
    MovieOpenParamSetSource_1d61c0(&cfg, arg0, arg1);
    cfg.flag = arg2 != 0;
    switch (mode) {
    case 1:
        cfg.w = 0x200;
        cfg.h = 0x150;
        break;
    case 0:
        cfg.w = 0x200;
        cfg.h = 0x1C0;
        break;
    }
    MoviePlayerOpen_1d61a0(w, &cfg);
    switch (mode) {
    case 1:
        w->x = 0;
        w->y = -0x20;
        break;
    case 0:
        w->x = 0;
        w->y = 0;
        break;
    }
    n = D_00481F78->count;
    id = D_00481F78->id;
    cfg.n = n;
    if (n <= 0) return 0;
    NameTableFreeGroup_158ac0(db, id);
    NameTableAddEntry_159b70(db, id, D_0045F190, 0, W, 0x80, K, 0, 0, (int)(0));
    switch (mode) {
    case 1:
        NameTableAddEntry_159b70(db, id, D_0045F1A0, 0, W, 0x150, K, 0, 0, (int)(0));
        break;
    case 0:
        NameTableAddEntry_159b70(db, id, D_0045F1A0, 0, W, H, K, 0, 0, (int)(0));
        break;
    }
    DrawListAddTexLoad_1418c0(mgr, id, 1.0f);
    MoviePlayerStart_1d5b50(w, D_0045F1A0);
    MoviePlayerWaitTick_1d5810(w);
    while ((((unsigned char)MovieIsStarted_1d5640()) != 0) ^ 1) {
        MoviePlayerWaitTick_1d5810(w);
    }
    MoviePlayerWaitTick_1d5810(w);
    MesFontPagesSetFlagRelated_270440(1);
    cnt = 0;
    fade = -1;
    ok = PauseIsAllowed_2f6650();
    obj = GetStreamMgr_207ea0();
    ctl = GetGameData_1fede0();
    quit = 0;
    state = 0;
    kind = ctl->sub->kind;
    t120 = (s32)D_0045B078[0];
    timer = t120;
    t110 = t120;
    for (;;) {
        if (cnt != 0) DrawListFrameBegin_1425d0(mgr, 1);
        PadUpdate_1843a0(D_004B2570);
        if (state <= 0) {
            if (ok != 0 && PadIsTriggered_1839f0(D_004B2570, 0x800) != 0) state = 1;
        }
        if (state < 2) {
            if (((unsigned char)PadIsAnalogMode_184960(D_004B2570)) == 0) state = 2;
        }
        if (t110 < 0) {
            if (MovieIsReadStalled_1d62a0() == 0) {
                timer = t120;
            } else {
                timer--;
            }
            if (state < 3) {
                if (timer < 0) state = 3;
            }
        } else if (MovieIsReadStalled_1d62a0() == 0) {
            timer = t120;
            if (--t110 < 0) {
                timer = t120;
            }
        } else {
            timer--;
            t110 = t120;
        }
        st = state;
        drawn = 0;
        if (state > 0) {
            drawn = 1;
            StateFlagSet_3ccb70(ctl->f10, 0x143, 0, 1);
            AudioDecSetInputVolumeF_1d52e0(0.0f);
            MoviePause_1d5b40();
            SoundRpcStopAllThunkMaybe_1bd680(obj, 0, 0, 0);
            StreamMgrUpdate_1d6940(obj, f);
            k = 1;
            do {
                if (k == 2) DrawListFrameBegin_1425d0(mgr, 1);
                MoviePlayerWaitTick_1d5810(w);
                MovieDrawFrame_1d5870(w);
                MovieFrameQueueSendNext_1d4b20();
                Nop_207f60();
                Nop_207f50();
                if (D_00482040 != 0 && kind != 0 && *(s32 *)(D_00482040 + 0x43C) == 0) {
                    MesMgrDrawAll_277a50(x154);
                }
                DrawTexturedRect_26a920(0, 0, 0x200, 0x1C0, 0, 0, 0, 0x40, (void *)(0));
                if (state == 1) {
                    PauseReasonDrawMaybe_2f5c40(arg5 != 0 ? 3 : 2);
                }
                if (state == 2) {
                    PadLostMsgDrawMaybe_2f5e90(0, -0x40);
                }
                if (state == 3) {
                    DiscStatusMessageDraw_39ecf0(0);
                }
                GfxEndFrame_141c20(mgr, 1);
                MovieFrameResend_1d4be0();
                k++;
            } while (k <= 2);
            do {
                PadUpdate_1843a0(D_004B2570);
                MoviePlayerWaitTick_1d5810(w);
                DelayThread_117618(100);
                if (state == 1) {
                    if (PadIsTriggered_1839f0(D_004B2570, 0x800) != 0) {
                        state = 0;
                        break;
                    }
                    if (arg5 != 0 && PadIsTriggered_1839f0(D_004B2570, 0x10) != 0) {
                        SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 5, 0, 1.0f);
                        ScreenFadeOutColor_1cf730(g, 10, 0.0f, 0.0f, 0.0f);
                        fade = 10;
                        AudioDecSetInputVolumeF_1d52e0(0.0f);
                        quit = 1;
                        StateFlagSet_3ccb70(ctl->f10, 0x143, quit, quit);
                        state = 0;
                        break;
                    }
                }
                if (state == 2) {
                    if (PadIsTriggered_1839f0(D_004B2570, 0x40) != 0) {
                        state = 0;
                        break;
                    }
                }
                if (state == 3 && MovieIsReadStalled_1d62a0() == 0) {
                    state = 0;
                    break;
                }
            } while (1);
            if (st > 0 && state == 0) {
                MovieFrameResend_1d4be0();
                if (quit != 0) {
                    for (; fade >= 0;) {
                        DrawListFrameBegin_1425d0(mgr, 1);
                        MoviePlayerWaitTick_1d5810(w);
                        MovieDrawFrame_1d5870(w);
                        MovieFrameQueueSendNext_1d4b20();
                        DrawTexturedRect_26a920(0, 0, 0x200, 0x1C0, 0, 0, 0, (s32)(128.0f - D_0047DAD0 * (f32)fade), (void *)(0));
                        fade--;
                        GfxEndFrame_141c20(mgr, 1);
                    }
                    MovieResume_1d5b30();
                    MoviePlayerShutdown_1d56c0(w);
                    DrawListFrameBegin_1425d0(mgr, 1);
                    MemStackReset_14d830(arg1);
                    SoundRpcFrameTickThunkMaybe_1bd690(obj, 0, 0, 0);
                    StreamMgrUpdate_1d6940(obj, f);
                    break;
                }
                SoundRpcFrameTickThunkMaybe_1bd690(obj, 0, 0, 0);
                StreamMgrUpdate_1d6940(obj, f);
                MovieResume_1d5b30();
                AudioDecSetInputVolumeF_1d52e0(1.0f);
                DrawListFrameBegin_1425d0(mgr, 1);
            }
        }
        if (MovieIsFinished_1d5680() != 0 || (arg3 > 0 && MovieGetFrameCount_1d52d0() >= arg3)) {
            MoviePlayerShutdown_1d56c0(w);
            MovieDrawFrame_1d5870(w);
            MovieFrameQueueSendNext_1d4b20();
            ScreenFadeDraw_1cf6d0(g);
            ScreenFadeStep_1cf6e0(g);
            GfxEndFrame_141c20(mgr, 1);
            DrawListFrameBegin_1425d0(mgr, 1);
            MemStackReset_14d830(arg1);
            break;
        }
        MoviePlayerWaitTick_1d5810(w);
        MovieDrawFrame_1d5870(w);
        MovieFrameQueueSendNext_1d4b20();
        Nop_207f60();
        Nop_207f50();
        if (D_00482040 != 0) {
            if (!drawn) EventCueStep_2491b0(D_00482040, g);
            if (kind != 0 && *(s32 *)(D_00482040 + 0x43C) == 0) {
                if (!drawn) MesMgrUpdateAll_277ac0(x154);
                MesMgrDrawAll_277a50(x154);
            }
        }
        if (fade > 0) {
            DrawTexturedRect_26a920(0, 0, 0x200, 0x1C0, 0, 0, 0, 0x40, (void *)(0));
        }
        ScreenFadeDraw_1cf6d0(g);
        ScreenFadeStep_1cf6e0(g);
        GfxEndFrame_141c20(mgr, 1);
        cnt++;
        if (cnt == 1 && arg2 == 0) {
            AudioDecSetInputVolumeF_1d52e0(1.0f);
        }
    }
    NameTableFreeGroup_158ac0(db, id);
    CdDiskWatchSetEnabled_17fe80(saved);
    MesFontPagesSetFlagRelated_270440(0);
    GameSceneSoundFadeVolume_1d0370(g, 0xF, 1.0f);
    GameSceneSoundSlot4FadeTo_1d0610(g, 0xF, 1.0f);
    if (quit != 0) return 2;
    return 1;
}
