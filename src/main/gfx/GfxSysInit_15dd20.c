#include "types.h"

/* Graphics/DMA bring-up.  D_004918B0 and D_004955E0 are reached with %hi/%lo,
   so they are incomplete arrays; D_004810A4 and the D_0047DFxx / D_004810Cx
   flags are gp_rel scalars.  Stack locals go in REVERSE declaration order:
   env (sp+0x70), sp1 (sp+0x50), sp2 (sp+0x30). */

typedef struct DmaEnv {
    s32 m00;
    s16 m04;
    s16 m06;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
} DmaEnv;

typedef struct Sema {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
} Sema;

extern u8 D_004918B0[];
extern u8 D_004955E0[];
extern u8 *D_004810A4;
extern s32 D_0047DF10;
extern s32 D_0047DF14;
extern s32 D_0047DF18;
extern s32 D_004810C4;
extern s32 D_004810CC;
extern s32 D_004810D0;
extern s32 D_004810D4;

extern s32 DisableIntr_120660(void);
extern void EnableIntr_1206b0(void);
extern void sceDmaReset(s32 mode);
extern void sceDmaGetEnv(DmaEnv *env);
extern void sceDmaPutEnv(DmaEnv *env);
extern void sceGsResetPath(void);
extern void *sceDmaGetChan(s32 ch);
extern void DrawCtxInit_145a10(void *p);
extern void GfxSetVideoMode_1451f0(void *p, void *q);
extern void DrawCtxNameTableResetMaybe_1459d0(void *p);
extern void DrawCtxCameraRecInit_143190(void *p);
extern s32 CreateSema(Sema *p);
extern void sceGsSyncVCallback_109b18(void *fn);
extern void GfxVblankStartHandler_15df20(void);
extern void Vif0SendInitPacketMaybe_13bcc0(void);

void GfxSysInit_15dd20(void *arg)
{
    DmaEnv env;
    Sema sp1;
    Sema sp2;
    s32 t;

    t = DisableIntr_120660();
    sceDmaReset(1);
    sceDmaGetEnv(&env);
    env.m06 = 0x100;
    sceDmaPutEnv(&env);
    sceGsResetPath();
    sceDmaGetChan(1);
    *(volatile s32 *)0x10000010 = 0x83;
    if (t != 0) {
        EnableIntr_1206b0();
    }
    D_004810A4 = D_004918B0;
    DrawCtxInit_145a10(D_004918B0);
    *(u8 **)(D_004810A4 + 0x3BA0) = D_004955E0;
    GfxSetVideoMode_1451f0(D_004810A4, arg);
    DrawCtxNameTableResetMaybe_1459d0(D_004810A4);
    DrawCtxCameraRecInit_143190(D_004810A4);
    sp1.m04 = 1;
    sp1.m08 = 0;
    sp1.m14 = 0;
    D_0047DF18 = CreateSema(&sp1);
    D_0047DF14 = -1;
    D_004810C4 = 0;
    D_004810CC = 0;
    sceGsSyncVCallback_109b18(GfxVblankStartHandler_15df20);
    sp2.m08 = 1;
    sp2.m04 = 1;
    D_004810D0 = 0;
    D_004810D4 = 0;
    sp2.m14 = 0;
    D_0047DF10 = CreateSema(&sp2);
    Vif0SendInitPacketMaybe_13bcc0();
}
