/* rgp:protos */
#define RGP_SELF_AiInit_2c1250 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* A constructor-shaped INITIALISER with two 21-word block copies, a
   stride-12 fill of eight elements, and four float-argument setters.

   Retail's two 21-word block copies are UNROLLED lw/sw pairs, so they are
   21 EXPLICIT member assignments in the source -- a struct assignment emits
   mwcc's `li 0x15` + lw/sw LOOP instead (measured this pass, 66 words short).

   The four setters take a FLOAT in $f12, materialised with `lui`/`mtc1`:
   28.0f, 4.0f, 24.0f and 48.0f.  The `-1` m2c prints as a second argument
   to AiSetApproachMarginMaybe_2c0f00 is $5 left over from the neighbouring `sh` stores, and
   the same is true of the `0x3F800000` it prints for ScriptVmCtor_176be0.

   Stack slots go to the LAST-declared local first, so `t1` (retail's
   0x80) is declared before `t0` (retail's 0x20). */

extern s32  memset(s32, s32, s32);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

typedef struct {
    s32 w[21];
} Blk;

/*rgp*/

void AiInit_2c1250(u8 *p)
{
    Blk t1 __attribute__((aligned(16)));
    Blk t0 __attribute__((aligned(16)));
    s32 i;

    memset((s32)(p + 0x1C0), 0, 0xA0);
    *(s32 *)(p + 0x1B0) = 0;
    *(s32 *)(p + 0x1B4) = 0;
    *(s32 *)(p + 0x1B8) = 0;
    *(s32 *)(p + 0x1BC) = 0x3F800000;
    *(s32 *)(p + 0x26C) = -1;
    *(s32 *)(p + 0x288) = -1;
    *(s32 *)(p + 0x28C) = 0;
    *(s32 *)(p + 0x294) = 0;
    *(s32 *)(p + 0x290) = 0;
    *(s32 *)(p + 0x270) = 0;
    *(s32 *)(p + 0x274) = 0x43480000;
    *(s32 *)(p + 0x278) = 0;
    *(s32 *)(p + 0x27C) = 0;
    *(s32 *)(p + 0x280) = 0x3F800000;
    *(s32 *)(p + 0x284) = 0x3F800000;
    *(s8 *)(p + 0x261) = 0;
    *(s8 *)(p + 0x251) = 0;
    *(s8 *)(p + 0x250) = 0;
    ScriptVmCtor_176be0(&t1);
    *(s32 *)(p + 0x0) = t1.w[0];
    *(s32 *)(p + 0x4) = t1.w[1];
    *(s32 *)(p + 0x8) = t1.w[2];
    *(s32 *)(p + 0xC) = t1.w[3];
    *(s32 *)(p + 0x10) = t1.w[4];
    *(s32 *)(p + 0x14) = t1.w[5];
    *(s32 *)(p + 0x18) = t1.w[6];
    *(s32 *)(p + 0x1C) = t1.w[7];
    *(s32 *)(p + 0x20) = t1.w[8];
    *(s32 *)(p + 0x24) = t1.w[9];
    *(s32 *)(p + 0x28) = t1.w[10];
    *(s32 *)(p + 0x2C) = t1.w[11];
    *(s32 *)(p + 0x30) = t1.w[12];
    *(s32 *)(p + 0x34) = t1.w[13];
    *(s32 *)(p + 0x38) = t1.w[14];
    *(s32 *)(p + 0x3C) = t1.w[15];
    *(s32 *)(p + 0x40) = t1.w[16];
    *(s32 *)(p + 0x44) = t1.w[17];
    *(s32 *)(p + 0x48) = t1.w[18];
    *(s32 *)(p + 0x4C) = t1.w[19];
    *(s32 *)(p + 0x50) = t1.w[20];
    ScriptVmCtor_176be0(&t0);
    *(s32 *)(p + 0x54) = t0.w[0];
    *(s32 *)(p + 0x58) = t0.w[1];
    *(s32 *)(p + 0x5C) = t0.w[2];
    *(s32 *)(p + 0x60) = t0.w[3];
    *(s32 *)(p + 0x64) = t0.w[4];
    *(s32 *)(p + 0x68) = t0.w[5];
    *(s32 *)(p + 0x6C) = t0.w[6];
    *(s32 *)(p + 0x70) = t0.w[7];
    *(s32 *)(p + 0x74) = t0.w[8];
    *(s32 *)(p + 0x78) = t0.w[9];
    *(s32 *)(p + 0x7C) = t0.w[10];
    *(s32 *)(p + 0x80) = t0.w[11];
    *(s32 *)(p + 0x84) = t0.w[12];
    *(s32 *)(p + 0x88) = t0.w[13];
    *(s32 *)(p + 0x8C) = t0.w[14];
    *(s32 *)(p + 0x90) = t0.w[15];
    *(s32 *)(p + 0x94) = t0.w[16];
    *(s32 *)(p + 0x98) = t0.w[17];
    *(s32 *)(p + 0x9C) = t0.w[18];
    *(s32 *)(p + 0xA0) = t0.w[19];
    *(s32 *)(p + 0xA4) = t0.w[20];
    *(s16 *)(p + 0x298) = -1;
    *(s16 *)(p + 0xAC) = -1;
    *(s16 *)(p + 0xAE) = -1;
    AiAllySuggestRecReset_3a80e0(p + 0x130);
    *(u8 *)(p + 0x143) = 0xFF;
    *(u8 *)(p + 0x13A) = 0xFF;
    *(u8 *)(p + 0x13B) = 0xFF;
    *(s16 *)(p + 0xB4) = 0x64;
    *(s16 *)(p + 0xB6) = 0;
    *(s8 *)(p + 0x260) = 0;
    for (i = 0; i < 8; i++) {
        *(s32 *)(p + 0xD0 + i * 12) = -1;
        *(s32 *)(p + 0xD4 + i * 12) = 0;
    }
    *(s16 *)(p + 0x13C) = -1;
    *(s16 *)(p + 0xA8) = -1;
    *(s16 *)(p + 0xB0) = -1;
    *(s16 *)(p + 0xB2) = -1;
    *(s8 *)(p + 0x16A) = 0;
    *(s8 *)(p + 0x262) = 0;
    *(u8 *)(p + 0x142) = 0xFF;
    *(s16 *)(p + 0x148) = -1;
    AiSetApproachMarginMaybe_2c0f00(p, 28.0f);
    AiSetStopDistance_2c0ef0(p, 4.0f);
    AiSetRunDistance_2c0ee0(p, 24.0f);
    AiSetKeepDistanceMaybe_2c0ed0(p, 48.0f);
    *(s8 *)(p + 0x16B) = 0;
    *(s8 *)(p + 0x16C) = 0;
    *(s8 *)(p + 0x170) = 0;
    *(s8 *)(p + 0x171) = 0;
    *(s16 *)(p + 0x144) = -1;
    *(s16 *)(p + 0x146) = 0;
    *(s16 *)(p + 0x174) = 0;
    *(s16 *)(p + 0x172) = 0;
    *(s16 *)(p + 0x176) = 0;
    *(s32 *)(p + 0x178) = 0;
    *(s32 *)(p + 0x180) = 0xBF800000;
    *(s32 *)(p + 0x17C) = 0x3F000000;
    *(s32 *)(p + 0x184) = 0;
    *(s32 *)(p + 0x188) = 0x40800000;
    *(s32 *)(p + 0xB8) = 0;
    *(s16 *)(p + 0x13E) = -1;
    *(s16 *)(p + 0x29A) = 0;
}
