/* PARKED s17b: not attempted, no draft read yet this session. See
   asm/matchings/main/MapCaptionLoadStep_33f700.s and build/b_drafts/MapCaptionLoadStep_33f700.txt
   (m2c draft already generated, just not worked). */
/* s49m: 88 bad (right length) */
#include "types.h"

typedef struct Tab {
    s32 w[0x24];
} Tab;

typedef struct Obj50 {
    u8 d[0x830];
} Obj50;

typedef struct G {
    u8 pad0[4];
    char *m4;
} G;

typedef struct Self {
    u8 pad0[2];
    s16 m2;
    s32 m4;
    u8 pad8[0xC];
    s32 m14;
    s32 m18;
    u8 pad1C[8];
    u8 m24;
} Self;

extern u8 D_00453780[];
extern char D_004626B0[];
extern char D_004626D0[];
extern s32 D_00482CB0;
extern char *strcpy(char *, const char *);
extern s32 strlen(const char *);
extern void LoadHandlePoll_1ccb00(Self *);
extern void MapCaptionRelease_33fa10(Self *);
extern void TexGroupLoadFromArchive_202be0(s32, char *, s32, s32, s32);
extern s32 GetCaptionCfg_340430(void);
extern void CaptionCfgInit_340240(s32, s32);
extern void CfgVmReset_42fc10(Obj50 *);
extern void CfgVmRegisterCmds_42fb00(Obj50 *, Tab *);
extern s32 ArchiveGetFileByPath_1c2800(s32, char *, s32 *);
extern void CfgVmLoad_42fac0(Obj50 *, s32, s32);
extern void CfgVmCopyStringPoolQwMaybe_42f570(Obj50 *, s32);
extern void CfgVmRun_42fa20(Obj50 *);
extern s16 CaptionCfgGetImageMode_33fe20(s32);
extern void MapCaptionSetImageMode_33f1b0(Self *, s64);
extern s16 MapCaptionGetImageMode_33f1a0(Self *);
extern G *MapCaptionGetText_33fa00(Self *);
extern s32 GetCaptionPanel_340420(void);
extern void UiPanelInit_33ea10(s32);
extern void UiPanelSetWidgetPoolSize_33eb60(s32, s32);
extern s32 CaptionCfgGetTexName_340220(s32);
extern void CaptionPanelSetup_33eac0(s32, s32, s32, s32, s32);
extern void MapCaptionSetGlyphSpacing_33f140(Self *, s32);
extern s32 MapCaptionGetGlyphSpacing_33f130(Self *);
extern void UiPanelSetGlyphSpacing_33dfb0(s32, s32);
extern void CaptionPanelSetText_33dfd0(s32, char *);
extern void UiPanelOpen_33dd40(s32);
extern void LoaderReleaseHandle_1ccb70(Self *);
extern void HudFadeOutAll_2f47e0(s32);

void MapCaptionLoadStep_33f700(Self *self)
{
    char s930[0x20];
    char s910[0x20];
    s32 n95C;
    Tab tab;
    Obj50 obj;
    s32 h;
    s32 a;
    s32 b;
    G *g;
    s32 len;
    s32 mode;

    if (self->m18 != 1) {
        return;
    }
    LoadHandlePoll_1ccb00(self);
    if (self->m2 == 0) {
        return;
    }
    if (self->m2 == -1) {
        MapCaptionRelease_33fa10(self);
        return;
    }
    h = self->m4;
    strcpy(s930, D_004626B0);
    strcpy(s910, D_004626D0);
    TexGroupLoadFromArchive_202be0(h, s930, self->m14, 0x1C8, self->m14);
    a = GetCaptionCfg_340430();
    CaptionCfgInit_340240(a, self->m14);
    tab = *(Tab *)D_00453780;
    CfgVmReset_42fc10(&obj);
    CfgVmRegisterCmds_42fb00(&obj, &tab);
    n95C = 0;
    {
        s32 r = ArchiveGetFileByPath_1c2800(h, s910, &n95C);
        CfgVmLoad_42fac0(&obj, r, n95C);
    }
    CfgVmCopyStringPoolQwMaybe_42f570(&obj, self->m14);
    CfgVmRun_42fa20(&obj);
    MapCaptionSetImageMode_33f1b0(self, CaptionCfgGetImageMode_33fe20(a));
    if (MapCaptionGetImageMode_33f1a0(self) == 0) {
        g = MapCaptionGetText_33fa00(self);
        b = GetCaptionPanel_340420();
        UiPanelInit_33ea10(b);
        UiPanelSetWidgetPoolSize_33eb60(b, self->m14);
        CaptionPanelSetup_33eac0(b, D_00482CB0, 0x1C8, a, CaptionCfgGetTexName_340220(a));
        len = strlen(g->m4);
        mode = 0;
        if (len >= 20) {
            mode = 2;
            if (len >= 30) {
                mode = 4;
            }
        }
        MapCaptionSetGlyphSpacing_33f140(self, mode);
        UiPanelSetGlyphSpacing_33dfb0(b, MapCaptionGetGlyphSpacing_33f130(self));
        CaptionPanelSetText_33dfd0(b, g->m4);
        UiPanelOpen_33dd40(b);
    }
    LoaderReleaseHandle_1ccb70(self);
    if (self->m24 != 0) {
        self->m18 = 4;
        HudFadeOutAll_2f47e0(0xF);
    } else {
        self->m18 = 2;
    }
}
