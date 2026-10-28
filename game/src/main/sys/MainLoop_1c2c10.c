/* rgp:protos */
#define RGP_SELF_IsBusy 1
#define RGP_SELF_MainLoop_1c2c10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;
typedef struct Sys {
    u8 pad[0x28];
    u128 *buf;
    s32 base;
    s32 f30;
    s32 n;
} Sys;
typedef struct Ctx { u8 pad[0x3D2C]; s32 f3D2C; } Ctx;

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
extern u8 D_0045B010[];
extern s32 D_0047E224;
extern s32 D_0047E228;
extern void (*D_0047E230[2])(void *);
extern s32 (*D_0047E238[2])(void);
extern void (*D_0047E240[2])(void);
extern s32 D_00481550;
extern s32 D_00481554;
extern u8 D_004A3EF0[];
extern u8 D_004B2570[];
extern u8 D_004B27E0[];

static inline u8 IsBusy(s32 s) { u8 r = 0; if (s == 0 || s == 1) {} else { r = 1; } return r; }

void MainLoop_1c2c10(void)
{
    s32 sp4C;
    Sys *s;
    s32 i;
    u128 *p;
    s32 h;
    Ctx *c;
    s32 done;
    s32 r;
    s32 f;

    SysBootInit_1c2ee0();
    s = ((Sys *)GetMainStack_1c6dc0());
    i = 0;
    p = s->buf + s->base;
    for (; i < s->n; i++) {
        *p = 0;
        p++;
    }
    Nop_207fb0();
    h = AlignUp_1c39c0(s->buf + s->base, 0x40);
    if (ResidentFileReadLocalizedMaybe_1c2860(D_0045B010, h, &sp4C) != 0) {
        SysCfgParse_1c2950(h, sp4C);
    }
    OverlayLocateFiles_1c3300();
    for (;;) {
        D_0047E224 = D_0047E228;
        c = ((Ctx *)GetDrawCtx_15de80());
        PadUpdate_1843a0(D_004B2570);
        MemStackReset_14d830(s);
        if (D_00481550 != 0) {
            Srand_1336f8(0x270F);
        }
        switch (D_0047E224) {
        case 0:
            if (((unsigned char)SysModeMsgIsInsMenu_1c6970(((s16 *)SysGetModeMsg_1c39b0()))) != 0) {
                OverlayLoad_1c3210(6);
            } else {
                OverlayLoad_1c3210(3);
            }
            break;
        case 1:
            OverlayLoad_1c3210(2);
            break;
        case 2:
            OverlayLoad_1c3210(1);
            break;
        default:
            OverlayLoad_1c3210(0);
            break;
        }
        D_0047E230[D_0047E224](D_004A3EF0);
        do {
            DrawListFrameBegin_1425d0(c, 1);
            done = 0;
            r = DiscStatusMessagePoll_39ee00(IsBusy(D_0047E224));
            if (D_0047E224 == 0 || D_0047E224 == 1 || r == 0) {
                done = D_0047E238[D_0047E224]();
            }
            GfxEndFrame_141c20(c, 1);
            if (D_00481554 == 0) {
                SoundSeqPlayersUpdateAll_1bb110(DrawCtxGetFrameTime_144120(c));
            }
            PadUpdate_1843a0(D_004B2570);
            PadUpdate_1843a0(D_004B27E0);
        } while ((done != 0) ^ 1);
        Vif1HandlerStop_141bf0(c);
        c->f3D2C = 0;
        D_0047E240[D_0047E224]();
        if (D_0047E224 != 2) {
            if (D_00481550 == 1) {
                PadKeyCapDump_1837d0(D_004B2570);
            }
            D_00481550 = 0;
        }
        DrawCtxSetPerfMeterOn_15ca00(0);
        PadKeyCapReset_1837f0(D_004B2570);
    }
}
