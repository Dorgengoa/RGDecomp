/* rgp:protos */
#define RGP_SELF_GameStartModeUpdate_2858f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Phase driver of the SetGameModePhase_1f59a0 family, with a second switch nested in
   its case 1.  Outer chain is 1, 0, -1 -> source order -1, 0, 1; inner chain
   is 4, 2, 1, 0, 6 -> source order 6, 0, 1, 2, 4, and the inner bodies are
   laid out in exactly that order.

   ⚠⚠ EVERY inner case is a `break` to a shared `return 1`, INCLUDING case 6,
   whose exit is `b <epilogue>` with `addiu $2,$0,1` in the delay slot.  That
   spelling is the family's tell for a per-case `return` -- and here it is
   not one: mwcc duplicates the shared tail's single word into exactly ONE
   break's otherwise-empty delay slot and leaves the other four as
   `b .L00285C48 / nop`.  Writing case 6 as `return 1;` puts the duplicate on
   case 0 instead and is two wrong words.  ⇒ the tell only means `return`
   when EVERY exit materialises its own value.

   ★ The `and ~1 / or / sb` blocks are BITFIELD INSERTS, not mask arithmetic:
   the generator spelling `p->b = (p->b & ~1) | 1` folds the value into an
   `ori` immediate and is a word short, while a real `u8 b : 1` field
   materialises the value in a register.  See
   memory/levers.d/main-bitfield-insert.md. */

struct Node {
    u8 pad0[4];
    union {
        u8 raw;
        struct {
            u8 b : 1;
            u8 rest : 7;
        } f;
    } u;
};

struct Root {
    u8 pad0[0x20];
    struct Node *m20;
};

struct Rec {
    s16 m0;
    u8  pad2[6];
    s16 m8;
    s16 mA;
};

extern char D_0045FED0[];
extern char D_004605C0[];
extern char D_004605D8[];

extern s8 D_00483998;
extern s8 D_004839A0;

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 GameStartModeUpdate_2858f0(void)
{
    u8 blk[0x30] __attribute__((aligned(16)));
    struct Rec *rec;
    struct Root *root;
    struct Node *p;
    u8 old;
    s32 anim;
    s32 scene;

    rec = ((struct Rec *)SysGetModeMsg_1c39b0());
    root = ((struct Root *)GetGameData_1fede0());
    anim = ((s32)GetGameReqQueue_1f5bc0());
    scene = GetCurrentScene_1f5be0();
    GetMapMgr_201a90();
    GetActionMgr_1fdb50();
    if (rec->m0 == 5) {
        TaskSetEnabled_27c2a0(1, D_0045FED0);
    }
    switch (GetGameModePhase_1f59b0()) {
    case -1:
        GameReqListClear_209f50(anim);
        SetGameReqHold_1f5890();
        ScreenFadeOutColor_1cf730(scene, 0, 0.0f, 0.0f, 0.0f);
        TaskStatePushAll_27c220();
        TaskSetupGameStart_287a10();
        SetGameModePhase_1f59a0(0);
        return 1;
    case 0:
        OptionsApply_1fe350();
        SetGameModePhase_1f59a0(1);
        return 1;
    case 1:
        if (ReturnZero_207f40() != 0) {
            return 0;
        }
        if (LoaderCountQueued_1cd620(((s32)GetLoaderMgr_1f59d0())) > 0) {
            return 0;
        }
        TaskSetEnabled_27c2a0(1, D_004605C0);
        TaskSetEnabled_27c2a0(1, D_004605D8);
        SysStateSetFlagRelated_1c6ac0(1);
        ClearGameReqHold_1f5880();
        GameReqQueuePushBack_1f5b50(6, -1);
        GameSceneSoundSlot4FadeIn_1d0600(scene, 0xF);
        GameSceneSoundFadeIn_1d0350(scene, 0xF);
        switch (rec->m0) {
        case 6:
            GameDataUpdateManagers_3e63a0(root, 1.0f);
            GameReqQueuePushWarp_1f5af0(rec->m8, rec->mA, 0, -1);
            break;
        case 0:
            D_00483998 = 1;
            D_004839A0 = 1;
            p = root->m20;
            old = p->u.raw;
            p->u.f.b = 1;
            CharaSysEncounterDistRoll_3a59d0(p, 1);
            CharaSysFlag4Bit1SetRelated_3a5300(root->m20);
            SoundCmdNopRelated_207eb0();
            ActionPacketReset_3e3d00(blk);
            ActionPacketInitGameStart_3e3bb0(blk, scene, 0);
            EventFireTriggers_3e2660(blk, 0);
            break;
        case 1:
            D_00483998 = 1;
            D_004839A0 = 1;
            p = root->m20;
            old = p->u.raw;
            p->u.f.b = 1;
            CharaSysEncounterDistRoll_3a59d0(p, 1);
            CharaSysFlag4Bit1SetRelated_3a5300(root->m20);
            SoundCmdNopRelated_207eb0();
            ScreenFadeIn_1cf740(scene, 0xF);
            break;
        case 2:
            D_00483998 = 0;
            D_004839A0 = 0;
            p = root->m20;
            p->u.f.b = 0;
            CharaSysFlag4Bit1SetArg0Related_3a5310(root->m20);
            SoundCmdNopRelated_207eb0();
            GameDataUpdateManagers_3e63a0(root, 1.0f);
            GameReqQueuePushWarp_1f5af0(rec->m8, rec->mA, 0, -1);
            break;
        case 4:
            GameStartRecFillPresetMaybe_3e7440(root, rec);
            D_00483998 = 1;
            D_004839A0 = 1;
            p = root->m20;
            old = p->u.raw;
            p->u.f.b = 1;
            CharaSysEncounterDistRoll_3a59d0(p, 1);
            CharaSysFlag4Bit1SetRelated_3a5300(root->m20);
            SoundCmdNopRelated_207eb0();
            ScreenFadeIn_1cf740(scene, 0xF);
            GameReqQueuePushBack_1f5b50(rec->m8, -1);
            break;
        default:
            ScreenFadeIn_1cf740(scene, 0xF);
            break;
        }
        return 1;
    }
    return 0;
}
