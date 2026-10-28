/* rgp:protos */
#define RGP_SELF_MapCaptionLoadStep_33f700 1
#include "port/game_protos.h"
#line 1
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

void MapCaptionLoadStep_33f700(Self *self)
{
    char s930[0x20] __attribute__((aligned(16)));
    char s910[0x20] __attribute__((aligned(16)));
    s32 n95C;
    Tab tab __attribute__((aligned(16)));
    Obj50 obj __attribute__((aligned(16)));
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
    a = ((s32)GetCaptionCfg_340430());
    CaptionCfgInit_340240(a, self->m14);
    tab = *(Tab *)D_00453780;
    CfgVmReset_42fc10(&obj);
    CfgVmRegisterCmds_42fb00(&obj, &tab);
    n95C = 0;
    {
        s32 r = ((s32)ArchiveGetFileByPath_1c2800(h, s910, &n95C));
        CfgVmLoad_42fac0(&obj, r, n95C);
    }
    CfgVmCopyStringPoolQwMaybe_42f570(&obj, self->m14, 0, 0);
    CfgVmRun_42fa20(&obj);
    MapCaptionSetImageMode_33f1b0(self, (short)(CaptionCfgGetImageMode_33fe20(a)));
    if (MapCaptionGetImageMode_33f1a0(self) == 0) {
        g = ((G *)MapCaptionGetText_33fa00(self));
        b = ((s32)GetCaptionPanel_340420());
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
