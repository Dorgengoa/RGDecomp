/* rgp:protos */
#define RGP_SELF_CharaInit_2150c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* A constructor-shaped INITIALISER: one call, ~130 stores in listing order,
   nine sub-object constructors and a four-iteration fill.

   Transcribed with build/rk_init.py -- the LISTING gives the order and the
   access width, the m2c draft gives the value.  The three TargetRefClear_2e71d0 calls
   take ONE argument each: retail hoists `addiu $4,$16,0x97C` to the top of
   the function and the `-1` m2c prints as a second argument is $5, which is
   the value feeding the neighbouring `sh` stores.

   The loop latch is `slti $3,$5,4` into a GPR, which is a bare `<` with the
   tested value on the left -- memory/at-compare-class.md. */

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

void CharaInit_2150c0(u8 *p)
{
    s32 i;

    CharaBodyInitMaybe_238980(p);
    *(s32 *)(p + 0x420) = 0;
    *(s16 *)(p + 0x424) = -1;
    *(s16 *)(p + 0x426) = -1;
    *(s32 *)(p + 0x430) = 0;
    *(s32 *)(p + 0x434) = 0;
    *(s32 *)(p + 0x438) = 0x3F800000;
    *(s32 *)(p + 0x43C) = 0;
    *(s32 *)(p + 0x440) = 0;
    *(s32 *)(p + 0x444) = 0;
    *(s32 *)(p + 0x448) = 0x3F800000;
    *(s32 *)(p + 0x44C) = 0;
    *(s32 *)(p + 0x450) = 0;
    *(s32 *)(p + 0x454) = 0;
    *(s32 *)(p + 0x458) = 0x3F800000;
    *(s32 *)(p + 0x45C) = 0;
    *(s32 *)(p + 0x460) = 0;
    *(s32 *)(p + 0x464) = 0;
    *(s32 *)(p + 0x468) = 0;
    *(s32 *)(p + 0x46C) = 0x3F800000;
    *(s32 *)(p + 0x470) = 0;
    *(s32 *)(p + 0x474) = 0;
    *(s32 *)(p + 0x478) = 0;
    *(s32 *)(p + 0x47C) = 0x3F800000;
    *(s32 *)(p + 0x480) = 0;
    *(s32 *)(p + 0x484) = 0;
    *(s32 *)(p + 0x488) = 0;
    *(s32 *)(p + 0x48C) = 0x3F800000;
    *(s64 *)(p + 0x560) = 0;
    *(s64 *)(p + 0x568) = 0;
    *(s64 *)(p + 0x570) = 0;
    *(s64 *)(p + 0x578) = 0;
    *(s32 *)(p + 0x4A0) = 0;
    *(s32 *)(p + 0x4A4) = 0;
    *(s32 *)(p + 0x4A8) = 0;
    *(s32 *)(p + 0x4AC) = 0;
    *(s32 *)(p + 0x4B0) = 0;
    *(s32 *)(p + 0x4B4) = 0;
    *(s32 *)(p + 0x4B8) = 0;
    *(s32 *)(p + 0x4BC) = 0;
    *(s32 *)(p + 0x4C0) = 0;
    *(s32 *)(p + 0x4C4) = 0;
    *(s32 *)(p + 0x4C8) = 0;
    *(s32 *)(p + 0x4CC) = 0;
    *(s16 *)(p + 0xA2C) = 0;
    *(s32 *)(p + 0x428) = 0;
    *(s32 *)(p + 0x42C) = 0;
    *(s16 *)(p + 0xA2E) = 0;
    *(s16 *)(p + 0xA32) = -1;
    *(s16 *)(p + 0xA34) = -1;
    *(s16 *)(p + 0xA36) = 0;
    *(s16 *)(p + 0xA38) = 0;
    *(s16 *)(p + 0xA3A) = -1;
    *(s16 *)(p + 0xA3E) = -1;
    *(s16 *)(p + 0xA3C) = 0;
    *(s16 *)(p + 0xA40) = 0;
    *(s32 *)(p + 0xA44) = 0;
    *(s32 *)(p + 0xA60) = 0;
    *(s32 *)(p + 0xA64) = 0;
    *(s32 *)(p + 0xA48) = -1;
    *(s32 *)(p + 0xA4C) = -1;
    *(s32 *)(p + 0xA50) = 0;
    *(s32 *)(p + 0xA54) = 0;
    *(s16 *)(p + 0xA58) = -1;
    *(s16 *)(p + 0xA5A) = -1;
    *(s16 *)(p + 0xA5C) = -1;
    *(s16 *)(p + 0xA5E) = -1;
    *(s8 *)(p + 0xA68) = 0;
    *(s32 *)(p + 0xA88) = 0x3F800000;
    *(s32 *)(p + 0xA10) = 0x3F800000;
    *(s32 *)(p + 0xA0C) = 0;
    *(s32 *)(p + 0xA20) = 0;
    *(s32 *)(p + 0xA24) = 0;
    *(s8 *)(p + 0xA28) = 0;
    *(s32 *)(p + 0xA1C) = 0;
    *(s32 *)(p + 0xA14) = 0;
    *(s32 *)(p + 0xA18) = 0;
    *(s8 *)(p + 0xA8C) = 0;
    *(s8 *)(p + 0xAAC) = 0;
    *(s32 *)(p + 0xACC) = 0;
    *(s32 *)(p + 0xAD0) = 0;
    *(s32 *)(p + 0xAD4) = 0;
    *(s32 *)(p + 0xAD8) = 0;
    *(s32 *)(p + 0xADC) = 0;
    *(s32 *)(p + 0xAE0) = 0;
    *(s8 *)(p + 0xAE4) = 0;
    *(s32 *)(p + 0xB04) = 0;
    *(s32 *)(p + 0xB08) = 4;
    *(s32 *)(p + 0xB0C) = -1;
    *(s32 *)(p + 0xB10) = 0;
    *(s32 *)(p + 0xB14) = 0;
    *(s8 *)(p + 0xB18) = 0;
    *(s32 *)(p + 0xB1C) = 0;
    *(s32 *)(p + 0xB20) = -1;
    *(s8 *)(p + 0xB24) = 0;
    *(s16 *)(p + 0xB44) = -1;
    *(s16 *)(p + 0xB46) = -1;
    TargetRefClear_2e71d0(p + 0x97C);
    TargetRefClear_2e71d0(p + 0x9AC);
    TargetRefClear_2e71d0(p + 0x9DC);
    *(s32 *)(p + 0x580) = 0;
    *(s32 *)(p + 0x584) = 0;
    *(s32 *)(p + 0x588) = 0;
    AiInit_2c1250(p + 0x590);
    CharaLadderStateReset_21ae70(p + 0x830);
    CharaHitInfoInit_219140(p + 0x870);
    CharaExecInfoInit_219100(p + 0x8B0);
    CharaMoveReqReset_2194d0(p + 0x930);
    CharaSquashReset_219300(p + 0x950);
    CharaTintClear_21f520(p + 0x95C);
    CharaAimCtrlInit_1d8340(p + 0x4D0);
    *(s16 *)(p + 0x550) = 2;
    *(s16 *)(p + 0x552) = 0;
    *(s16 *)(p + 0x558) = 0;
    *(s16 *)(p + 0x55E) = -1;
    *(s16 *)(p + 0x55A) = -1;
    *(s16 *)(p + 0x55C) = -1;
    *(s32 *)(p + 0x500) = 0;
    *(s32 *)(p + 0x504) = 0;
    *(s32 *)(p + 0x508) = 0;
    *(s32 *)(p + 0x50C) = 0x3F800000;
    *(s32 *)(p + 0x510) = 0;
    *(s32 *)(p + 0x514) = 0;
    *(s32 *)(p + 0x518) = 0;
    *(s32 *)(p + 0x51C) = 0x3F800000;
    *(s32 *)(p + 0x520) = 0;
    *(s32 *)(p + 0x524) = 0;
    *(s32 *)(p + 0x528) = 0;
    *(s32 *)(p + 0x52C) = 0x3F800000;
    XformRecSetDefaultNameMaybe_1c6940(p + 0x500);
    for (i = 0; i < 4; i++) {
        *(s32 *)(p + 0x530 + i * 4) = 0x41000000;
    }
    *(s16 *)(p + 0xB48) = 0;
    *(s16 *)(p + 0xB4A) = 0;
    *(s16 *)(p + 0xB4C) = 0;
    *(s16 *)(p + 0xB4E) = 0;
    *(s16 *)(p + 0xB50) = 0;
    *(s16 *)(p + 0xB52) = 0;
    *(s32 *)(p + 0xB58) = 0;
    *(s32 *)(p + 0xB54) = 0;
    *(s32 *)(p + 0xB5C) = 0;
    *(s16 *)(p + 0xB60) = -1;
    *(s16 *)(p + 0xB62) = 0;
}
