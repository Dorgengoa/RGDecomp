/* rgp:protos */
#define RGP_SELF_insect_InsectBattleObjInit_50e810 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050E810 -- 732 bytes, 183 instructions, 27 calls, 9 conditional
 * branches, br/ins 0.049.  The overlay's object CONSTRUCTOR: straight-line
 * field initialisation with six counted loops and no dispatch.  From
 * x_band.py's branch-light band.
 *
 * `insect_D_00525FF0` is REMATERIALISED inside the func_2912E0 loop (a `lui`/`addiu`
 * pair per iteration), so it is written as the bare NAME and not hoisted into a
 * local -- the rematerialise polarity of insect-extern-handle-hoist, and the
 * same extern insect_FUN_004FBA40 answers the same way.
 *
 * Every latch is `slti` into a GPR feeding `bnez`/`bnel`, which is
 * at-compare-class's natural `i < N` spelling; none of them is inverted.
 *
 * `o->f5EA0[i]` is stored 1 and then -1 in the SAME iteration, and the second
 * store is what mwcc sinks into the latch's delay slot.  Two consecutive
 * assignments to one field look like a transcription error and are not.
 *
 * The two field reads off func_1FEDE0()'s result are written as two separate
 * chains, so the `lw 0x24` is issued twice; only `o->fC0` is re-read from the
 * object (the func_1451E0 argument uses the value, the func_1451D0 argument
 * reloads the member).
 */

typedef struct Cfg {
    s32 m00;                        /* +0x00 */
    s32 m04;                        /* +0x04 */
} Cfg;

typedef struct Sys {
    u8   pad0000[0x1188];
    Cfg *m1188;                     /* +0x1188 */
} Sys;

typedef struct Top {
    u8   pad00[0x24];
    Sys *m24;                       /* +0x24 */
} Top;

typedef struct Ins {
    u8       pad0000[0xC0];
    s32      fC0;                   /* +0x00C0 */
    s32      fC4[5];                /* +0x00C4 .. 0x00D7; [4] IS 0x00D4 */
    s32      fD8[2];                /* +0x00D8 */
    u8       padE0[0x870 - 0xE0];
    s32      f870;                  /* +0x0870 */
    s32      f874;                  /* +0x0874 */
    const u8 *f878;                 /* +0x0878 */
    const u8 *f87C;                 /* +0x087C */
    const u8 *f880;                 /* +0x0880 */
    u8       pad884[0x35F0 - 0x884];
    s32      f35F0;                 /* +0x35F0 */
    s32      f35F4;                 /* +0x35F4 */
    u8       f35F8[0x3F8C - 0x35F8];  /* +0x35F8 */
    u8       f3F8C[0x4920 - 0x3F8C];  /* +0x3F8C */
    u8       f4920[0x4940 - 0x4920];  /* +0x4920 */
    u8       f4940[0x4960 - 0x4940];  /* +0x4940 */
    u8       f4960[0x506C - 0x4960];  /* +0x4960 */
    u8       f506C[0x50E8 - 0x506C];  /* +0x506C */
    u8       f50E8[0x51C4 - 0x50E8];  /* +0x50E8 */
    u8       f51C4[0x5214 - 0x51C4];  /* +0x51C4 */
    u8      *f5214;                 /* +0x5214 */
    u8      *f5218;                 /* +0x5218 */
    u8      *f521C;                 /* +0x521C */
    u8      *f5220;                 /* +0x5220 */
    u8      *f5224;                 /* +0x5224 */
    u8       pad5228[0x5AF8 - 0x5228];
    u8       f5AF8[0x5B18 - 0x5AF8];  /* +0x5AF8 */
    s32      f5B18;                 /* +0x5B18 */
    s32      f5B1C;                 /* +0x5B1C */
    s32      f5B20[4];              /* +0x5B20 */
    u8       pad5B30[0x5D8C - 0x5B30];
    s32      f5D8C;                 /* +0x5D8C */
    u8       pad5D90[0x5DA0 - 0x5D90];
    s32      f5DA0;                 /* +0x5DA0 */
    s32      f5DA4;                 /* +0x5DA4 */
    s32      f5DA8;                 /* +0x5DA8 */
    s32      f5DAC;                 /* +0x5DAC */
    s32      f5DB0;                 /* +0x5DB0 */
    u8       pad5DB4[0x5DD0 - 0x5DB4];
    s16      f5DD0;                 /* +0x5DD0 */
    u8       pad5DD2[0x5E94 - 0x5DD2];
    s8       f5E94[0xC];            /* +0x5E94 */
    s8       f5EA0[0xC];            /* +0x5EA0 */
    u8       pad5EAC[0x5EE9 - 0x5EAC];
    s8       f5EE9;                 /* +0x5EE9 */
    s8       f5EEA;                 /* +0x5EEA */
    u8       pad5EEB[0x5EF1 - 0x5EEB];
    u8       f5EF1;                 /* +0x5EF1 */
    u8       pad5EF2[0x5EF8 - 0x5EF2];
    s32      f5EF8;                 /* +0x5EF8 */
    u8       pad5EFC[0x5FC8 - 0x5EFC];
    f32      f5FC8;                 /* +0x5FC8 */
} Ins;

extern u8 insect_D_005250F8[];
extern u8 insect_D_00525FF0[];
extern u8 insect_D_00526004[];
extern u8 insect_D_00526018[];

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

void insect_InsectBattleObjInit_50e810(Ins *o)
{
    Top      *g;
    s32       c;
    s32       d;
    s32       i;
    s32       j;
    const u8 *r;

    g = ((Top *)GetGameData_1fede0());
    o->f5DA8 = g->m24->m1188->m00;
    o->f5DAC = g->m24->m1188->m04;
    insect_InsectBattleSetFlag_50dad0(o, 4);
    c = GetDrawCtx_15de80();
    o->fC0 = c;
    o->f5DA0 = DrawEnvGetWidth_1451e0(c);
    o->f5DA4 = DrawEnvGetHeight_1451d0(o->fC0);
    o->f878 = insect_D_00525FF0;
    o->f87C = insect_D_00526004;
    o->f880 = insect_D_00526018;
    d = GetCurrentScene_1f5be0();
    o->f870 = d;
    o->f5FC8 = GameSceneGetTimeStep_1ceba0(d);
    insect_InsectBattleReset_50e640(o);
    insect_InsectStoryLoadAttemptMaybe_5105d0();
    for (i = 0; i < 2; i++) {
        insect_InsectTeamSlotInit_514240((u8 *)o + (i << 5) + 0x4920);
    }
    for (j = 0; j < 2; j++) {
        o->fD8[j] = 0;
    }
    insect_InsectBattleClearFlags_50db00(o);
    for (i = 0; i < 0xC; i++) {
        insect_InsectBattleClearStateRow_50da00(o, i);
        insect_InsectBattleClearStepRow_50d9c0(o, i);
        o->f5E94[i] = -1;
        o->f5EA0[i] = 1;
        o->f5EA0[i] = -1;
    }
    for (j = 0; j < 5; j++) {
        o->fC4[j] = 0;
    }
    insect_InsectBattleFadeSet_50e230(o, 0, 0);
    o->f5EF1 = 0;
    insect_InsectBattleSetFlag_50dad0(o, 1);
    for (i = 0; i < 3; i++) {
        r = insect_D_00525FF0 + i * 0x14;
        if (r != 0) {
            UiWidgetListReset_2912e0(r);
        }
    }
    o->f5DD0 = 0;
    o->f5DB0 = 0;
    insect_InsectTeamSlotInit_514240(o->f4920);
    insect_InsectTeamSlotInit_514240(o->f4940);
    insect_InsectTeamReset_513d00(o->f35F8, o->f5FC8);
    insect_InsectTeamReset_513d00(o->f3F8C, o->f5FC8);
    insect_InsectMsgClearBank_512b90(o->f506C);
    insect_InsectAbilityTableClear_51d1d0(o->f50E8);
    insect_InsectAiInit_522c50(o->f51C4);
    o->f5220 = o->f50E8;
    o->f521C = o->f4960;
    o->f5218 = o->f35F8;
    o->f5214 = o->f3F8C;
    o->f5224 = o->f5AF8;
    o->f35F0 = -1;
    o->f5B1C = 0;
    for (j = 0; j < 4; j++) {
        o->f5B20[j] = 0;
    }
    o->f5B18 = 0;
    o->f5EF8 = 1;
    o->f874 = 0;
    o->f35F4 = 0;
    o->fC4[4] = ((s32)NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), insect_D_005250F8, 0x2A6));
    o->f5EE9 = -1;
    o->f5EEA = -1;
    o->f5D8C = 0;
    if (o->f5DA8 != 0) {
        insect_InsectBattleSetFlag_50dad0(o, 2);
    }
    if (o->f5DA8 == 6) {
        insect_InsectBattleSetFlag_50dad0(o, 3);
    }
}
