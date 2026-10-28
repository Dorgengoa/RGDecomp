/* rgp:protos */
#define RGP_SELF_title_TitleSessionShutdown_4f0820 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004F0820 -- tears the title scene down and starts the
 * outgoing transition effect.  Almost all of it is one 0x70-byte descriptor
 * built on the stack and handed to func_1C3560, filled differently in each of
 * six arms.
 *
 * BOTH dispatches are if/else-if CHAINS, not switches, and the delay slots say
 * so: every converted `bnel` carries THE NEXT GUARD'S CONSTANT
 * (`addiu $3,$0,0x2`, `addiu $3,$0,0x3`, `addiu $3,$0,0x2`), never a case
 * body's store.  The one exception is the last guard of the first chain, whose
 * slot carries the DEFAULT arm's `sb $2, 0x22($29)` -- that is a likely
 * branch duplicating its target's first instruction, which is what a chain's
 * final guard does when there is no next guard to materialise.  The case order
 * is therefore SOURCE order (1, 2, default and 1, 3, 2), not the reversed
 * order a switch's compare chain would have.
 *
 * Field 0x2C is written as an f32 in three arms and as an s16 in one, so the
 * descriptor is a variant record; the union is the only way to spell both.
 *
 * title_D_004F1A90 is overlay data and D_0045B090 is a main-image .data global, both
 * outside the 0x47D170..0x48D170 gp window, so both must be `const` or they
 * take a %gp_rel relocation that cannot be resolved at link time.  The
 * 0x47DDxx floats ARE inside it and must stay non-`const`.
 */

typedef struct Fx_title_FUN_004f0820 {
    s16 field020;
    s8 field022;
    s8 pad023;
    s16 field024;
    s16 field026;
    s16 field028;
    s16 field02A;
    union {
        f32 f;
        s16 h;
    } field02C;
    f32 field030;
    f32 field034;
    f32 field038;
    s16 field03C;
    s16 pad03E;
    f32 field040;
    f32 field044;
    s16 field048;
    s16 pad04A;
    f32 field04C;
    f32 field050;
    s16 field054;
    s16 field056;
    s16 field058;
    s16 field05A;
    u8 pad05C[0x34];
} Fx_title_FUN_004f0820;

extern f32 D_0047DD90;
extern f32 D_0047DD94;
extern f32 D_0047DD98;
extern f32 D_0047DD9C;
extern f32 D_0047DDA0;
extern f32 D_0047DDA4;
extern f32 D_0047DDA8;
extern f32 D_0047DDAC;
extern f32 D_0047DDB0;
extern f32 D_0047DDB4;
extern f32 D_0047DDB8;
extern f32 D_0047DDBC;
extern f32 D_0047DDC0;
extern s32 D_0045B090;
extern u8 title_D_004F1A90;

/*rgp*/
/*rgp*/
extern void SysMsgPostMaybe_1c3560(s32 a, Fx_title_FUN_004f0820 *b);
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

void title_TitleSessionShutdown_4f0820(void)
{
    Fx_title_FUN_004f0820 fx __attribute__((aligned(16)));
    void *w;
    s16 t;
    s32 u;

    SysMsgInit_1c69e0(&fx);
    if (IsTgsDemoBuild_207f20() != 0) {
        t = ((short)title_TitleGetSelection_4ecd30());
        if (t == 1) {
            fx.field020 = 5;
            fx.field022 = 1;
            fx.field024 = 0xC8;
            fx.field026 = -1;
            fx.field028 = -1;
            fx.field02C.f = D_0047DD90;
            fx.field030 = D_0047DD94;
            fx.field034 = D_0047DD98;
            fx.field038 = D_0047DD9C;
            fx.field03C = -1;
            fx.field040 = 20.0f;
            fx.field044 = -20.0f;
            fx.field048 = -1;
            fx.field04C = -20.0f;
            fx.field050 = -20.0f;
            fx.field054 = 3;
            fx.field056 = 0;
            fx.field058 = 0x1E;
            fx.field05A = 0x7FEF;
            SysMsgPostMaybe_1c3560(0, &fx);
        } else if (t == 2) {
            fx.field020 = 5;
            fx.field022 = 1;
            fx.field024 = 0x1F4;
            fx.field026 = -1;
            fx.field028 = -1;
            fx.field02C.f = D_0047DDA0;
            fx.field030 = D_0047DDA4;
            fx.field034 = D_0047DDA8;
            fx.field038 = 0.0f;
            fx.field03C = -1;
            fx.field040 = 20.0f;
            fx.field044 = -20.0f;
            fx.field048 = -1;
            fx.field04C = -20.0f;
            fx.field050 = -20.0f;
            fx.field054 = 6;
            fx.field056 = 0;
            fx.field058 = 0x1E;
            fx.field05A = 0x7FF0;
            SysMsgPostMaybe_1c3560(0, &fx);
        } else {
            fx.field020 = 5;
            fx.field022 = 1;
            fx.field024 = 0xC8;
            fx.field026 = -1;
            fx.field028 = -1;
            fx.field02C.f = (f32)-0xC77;
            fx.field030 = D_0047DDAC;
            fx.field034 = D_0047DDB0;
            fx.field038 = D_0047DDB4;
            fx.field03C = -1;
            fx.field040 = 20.0f;
            fx.field044 = -20.0f;
            fx.field048 = -1;
            fx.field04C = -20.0f;
            fx.field050 = -20.0f;
            fx.field054 = 8;
            fx.field056 = 2;
            fx.field058 = 0xA;
            fx.field05A = 0x7FF1;
            SysMsgPostMaybe_1c3560(0, &fx);
        }
    } else {
        u = ((short)title_TitleGetResult_4ec7d0());
        if (u == 1) {
            fx.field020 = 0;
            SysMsgPostMaybe_1c3560(0, &fx);
        } else if (u == 3) {
            fx.field020 = 2;
            fx.field024 = 4;
            fx.field02C.h = 4;
            fx.field026 = 0x190;
            fx.field028 = 0x190;
            fx.field02A = D_0045B090;
            fx.field030 = D_0047DDB8;
            fx.field034 = D_0047DDBC;
            fx.field038 = D_0047DDC0;
            SysMsgPostMaybe_1c3560(0, &fx);
        } else if (u == 2) {
            SysMsgPostMaybe_1c3560(0, ((Fx_title_FUN_004f0820 *)title_TitleGetLoadSysMsg_4ec7c0()));
        }
    }
    MemStackReset_14d830(&title_D_004F1A90);
    LoaderShutdown_1cdfe0(((s32)GetLoaderMgr_1f59d0()));
    SoundBankStopAll_1bad70(-1);
    SetCurrentScene_1f5bd0(0);
    title_TitleObjectsRelease_4ec700();
    w = GetMainStack_1c6dc0();
    MemStackReset_14d830(w);
    MemStackAlign64_14d8e0(w);
}
