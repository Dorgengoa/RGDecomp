/* rgp:protos */
#define RGP_SELF_SpaceMenuModeUpdate_27d130 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Phase driver of the SetGameModePhase_1f59a0 family.  Compare chain is 0x12E, 0x12D,
   0x12C, 0xC8, 0x64, 1, 0, -1, so the source order is -1, 0, 1, 100, 200,
   300, 301, 302 -- and the bodies appear in exactly that order.

   ★ D_004D7E00 / D_004D7E02 are WRITTEN .bss globals outside the gp window,
   so they are declared as INCOMPLETE ARRAYS and indexed [0]: mwcc small-datas
   any <=4-byte extern and emits %gp_rel, but an incomplete array type has no
   size for it to test, so the relocation comes out %hi/%lo.  See
   memory/levers.d/main-phase-driver-family.md.
   ★ case 300 falls through into 301, and it reuses the 0x12D the compare
   chain already left in $4. */

struct Track {
    u8  pad0[0x1A4];
    u8  m1A4;
    u8  pad1A5;
    s16 m1A6;
    s16 m1A8;
    u8  pad1AA[2];
    f32 m1AC;
    f32 m1B0;
};

struct Root {
    u8 pad0[0x18];
    struct Track *m18;
};

/* ★ The copy at 0x60 -> 0x68 is TWO lwc1/swc1 pairs, not ld/sd, so the
   assigned member is a pair of FLOATS while the value read back out is
   s16/s32 -- i.e. a union with a float view.  Measured over six spellings in
   build/pt/probe1.c: the plain 8-byte struct copy is elided entirely, an
   8-byte `ld`/`sd` copy is one register pair, and only the union's float
   member reproduces the two lwc1/swc1. */
struct Pair {
    f32 x;
    f32 y;
};

struct Sel {
    s16 a;
    s16 b;
    s32 c;
};

/* ★ And the copy is written THROUGH A CAST, not through a union member.
   Both spellings emit the two lwc1/swc1, but only the cast stops mwcc
   reordering the `lh` above the second store: with a union member store it
   sinks `swc1 $f0` into a plain `bne` delay slot (one word short), and with
   the cast it keeps both stores, leaving the slot empty -- so mwcc turns the
   branch into `bnel` and pulls the else-arm's `addiu $4, 0xC8` into it,
   which is retail.  Six more spellings in build/pt/probe2.c. */

extern char D_00460430[];
extern char D_00460AF0[];

extern s8  D_004D7E00[];
extern s16 D_004D7E02[];

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
extern void SpaceMenuGetResult_204730(struct Pair *);
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

s32 SpaceMenuModeUpdate_27d130(void)
{
    u8 blk[0x30] __attribute__((aligned(16)));
    struct Sel sel __attribute__((aligned(16)));
    struct Pair tmp __attribute__((aligned(16)));
    struct Root *root;
    struct Track *trk;
    s32 scene;

    root = ((struct Root *)GetGameData_1fede0());
    scene = GetCurrentScene_1f5be0();
    GetMapMgr_201a90();
    GetActionMgr_1fdb50();
    GetCharaResMgr_1fdb60();
    GameReqQueueRemoveById_1f5a10(0xC);
    GameReqQueueRemoveById_1f5a10(0xD);
    GameReqQueueRemoveById_1f5a10(0x11);
    GameReqQueueRemoveById_1f5a10(0x13);
    GameReqQueueRemoveById_1f5a10(0x14);
    switch (GetGameModePhase_1f59b0()) {
    case -1:
        SetGameReqHold_1f5890();
        TaskStatePushAll_27c220();
        TaskDisableFieldHudSet_285ff0();
        SetGameModePhase_1f59a0(0);
        return 0;
    case 0:
        TaskEnableLoadingSet_285f90();
        TaskSetEnabled_27c2a0(1, D_00460430);
        TaskSetEnabled_27c2a0(1, D_00460AF0);
        SceneSoundMutePush_2f6710();
        SceneOverlayModeOn_288340();
        SpaceMenuInit_2047e0();
        SetGameModePhase_1f59a0(1);
        return 0;
    case 1:
        if (ReturnTrue_204720() == 0) {
            return 0;
        }
        SetGameModePhase_1f59a0(0x64);
        return 1;
    case 100:
        TaskSetRenderTasksEnabled_287b90(SpaceMenuIsBusyThunk_511690() != 0);
        if (SpaceMenuIsRunningThunk_5110c0() != 0) {
            return 0;
        }
        SceneOverlayModeOff_288300();
        SpaceMenuGetResult_204730(&tmp);
        *(struct Pair *)&sel = tmp;
        if (sel.a == 2) {
            D_004D7E00[0] = 0;
            D_004D7E02[0] = sel.c;
            SetGameModePhase_1f59a0(0x12C);
        } else {
            SetGameModePhase_1f59a0(0xC8);
        }
        SpaceMenuClose_204690();
        return 1;
    case 200:
        SceneSoundMutePop_2f6670();
        ClearGameReqHold_1f5880();
        GameReqQueuePushBack_1f5b50(0, -1);
        TaskStatePopAll_27c250();
        return 0;
    case 300:
        SetGameModePhase_1f59a0(0x12D);
    case 301:
        ClearGameReqHold_1f5880();
        trk = root->m18;
        if ((trk->m1A4 & 1) == 0) {
            PartyPendingWarpSet_3c98b0(trk, D_004D7E02[0], -1, -1.0f, -1.0f);
            scene = GetCurrentScene_1f5be0();
            ActionPacketReset_3e3d00(blk);
            ActionPacketInitSpaceMenuMaybe_3e39f0(blk, scene, 1, 0);
            if (EventFireTriggers_3e2660(blk, 0) == 0) {
                ScreenFadeIn_1cf740(scene, 0xF);
            }
        } else {
            if (D_004D7E02[0] != trk->m1A6) {
                PartyPendingWarpSet_3c98b0(trk, D_004D7E02[0], trk->m1A6, -1.0f, -1.0f);
            } else {
                PartyPendingWarpSet_3c98b0(trk, D_004D7E02[0], trk->m1A8, trk->m1AC,
                             trk->m1AC - trk->m1B0);
            }
            ScreenFadeIn_1cf740(scene, 0xF);
        }
        SetGameModePhase_1f59a0(0x12E);
        return 1;
    case 302:
        SetGameModePhase_1f59a0(0xC8);
        return 1;
    }
    return 0;
}
