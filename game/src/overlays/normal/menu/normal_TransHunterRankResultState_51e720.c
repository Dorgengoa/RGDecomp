/* rgp:protos */
#define RGP_SELF_normal_TransHunterRankResultState_51e720 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051E720 -- the 0x7919/0x791A result banner: picks the win/lose
 * colour pair, formats both scores into two 8-byte gp buffers and starts the
 * 90-frame hold.  `slti $1, $3, 0x5B` puts the clamp compare in $at, so the
 * source token is `> 0x5A` and not `>= 0x5B` ([[at-compare-class]]).
 * The two format buffers are SEPARATE 8-byte gp objects -- one 16-byte array
 * is over the small-data threshold and comes out lui/%lo.
 * Three placement levers, all needed together:
 *  - the score-EQUAL arm is the `else` (`if (mine != theirs)`), or mwcc lays
 *    it inline and the whole function shifts;
 *  - `D_004848D0 = 90.0f` is written at the END OF BOTH arms, which is what
 *    puts the `sw` in the `b`'s delay slot instead of the next call's `lw`;
 *  - the hold test is `> 0.0f` with the SUBTRACT as the `if` body, so the
 *    expire call is the cold block.  Changing this one alone re-laid out the
 *    score-equal arm 130 words earlier -- block placement here is global.
 * Declarations: `i` FIRST and `theirs` BEFORE `mine` is what puts mine in $16,
 * theirs in $17 and the loop counter in $18 (11 -> 8 -> 0 bad). */

extern u8 normal_D_00526850;

extern void *D_00484718;          /* gp - 0xA58  */
extern void *D_00484720;          /* gp - 0xA50  */
extern void *D_00484770;          /* gp - 0xA00  */
extern void *D_0048470C;          /* gp - 0xA64  */
extern s16   D_0048075C;          /* gp - 0x4A14 */
extern f32   D_004848D0;          /* gp - 0x8A0  */
extern s32   D_004848D4;          /* gp - 0x89C  */
extern u8    D_004848E0[8];       /* gp - 0x890  */
extern u8    D_004848E8[8];       /* gp - 0x888  */
extern f32   D_0047D288;          /* gp - 0x7EE8 */

typedef struct Rec {
    u8   pad000[0x1A];
    s16  f01A;
} Rec;

typedef struct Root {
    u8   pad000[0x18];
    s32  f018;
} Root;

typedef struct Game {
    u8   pad0000[0x4C90];
    s16  f4C90;
    u8   pad4C92[2];
    s16  f4C94;
} Game;

extern void  memset(u8 *p, s32 v, s32 n);
extern void  Sprintf_1343b8(u8 *p, const u8 *fmt, s16 a);
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

s32 normal_TransHunterRankResultState_51e720(void *a, s32 b)
{
    s32 i;
    Game *g;
    s16 theirs;
    s16 mine;
    Rec *r;
    s16 v;
    f32 t;
    f32 hold;

    if (b != 0) {
        StreamSetChanVolumeFade_1cd960(((s32)GetLoaderMgr_1f59d0()), 0, 0xF, 1.0f);
        UiSetWidgetAlpha_2907a0(D_00484718, 0x7919, 0.0f);
        UiEntryListSelectByTag_28ea90(D_00484720, 0xF, 0);
        D_0048075C = 0x64;
        g = (Game *)((Root *)GetGameData_1fede0())->f018;
        mine = g->f4C90;
        theirs = g->f4C94;
        if (mine != theirs) {
            StreamSetChanVolumeFade_1cd960(((s32)GetLoaderMgr_1f59d0()), 0, 0xF, 0.0f);
            if (mine < theirs) {
                UiSetTextString_28f510(D_00484718, 0x7919, MsgTableLookup_28aa30(D_00484770, 4), 0);
                UiSetTextColor_290a40(D_00484718, 0x791A, 0xFF004F4F, 0);
                UiSetTextColor_290a40(D_00484718, 0x791A, 0xFF004F4F, 1);
                UiSetWidgetColor_2905b0(D_00484718, 0x791A, 1.0f, 1.0f, 1.0f, 1.0f);
                StreamPlayMwv_207340(0x327, 0, 1.0f);
                D_004848D0 = 90.0f;
            } else {
                UiSetTextString_28f510(D_00484718, 0x7919, MsgTableLookup_28aa30(D_00484770, 0xB), 0);
                UiSetTextColor_290a40(D_00484718, 0x791A, 0xFF00002F, 0);
                UiSetTextColor_290a40(D_00484718, 0x791A, 0xFF00002F, 1);
                t = D_0047D288;
                UiSetWidgetColor_2905b0(D_00484718, 0x791A, t, t, t, 1.0f);
                StreamPlayMwv_207340(0x329, 0, 1.0f);
                D_004848D0 = 90.0f;
            }
            UiSetTextString_28f510(D_00484718, 0x791A, MsgTableLookup_28aa30(D_00484770, 5), 0);
            i = 0;
            do {
                memset(&D_004848E0[i * 8], 0, 8);
                i += 1;
            } while (i < 2);
            Sprintf_1343b8(D_004848E0, &normal_D_00526850, mine);
            UiSetTextString_28f510(D_00484718, 0x791A, D_004848E0, 1);
            Sprintf_1343b8(D_004848E8, &normal_D_00526850, theirs);
            UiSetTextString_28f510(D_00484718, 0x791A, D_004848E8, 2);
            UiSetWidgetsVisibleById_291110(D_00484718, 0x791A, 1, 1);
            D_004848D4 = 0x17;
        } else {
            D_004848D0 = 0.0f;
            D_004848D4 = 0x18;
        }
        D_0048075C = mine;
        r = ((Rec *)UiEntryListFindByTag_28ea40(D_00484720, 0xA));
        v = mine - 1;
        if (v > 0x5A) {
            v = 0x5A;
        }
        r->f01A = v;
    }
    t = GameSceneGetTimeStep_1ceba0(GetCurrentScene_1f5be0());
    hold = D_004848D0;
    if (hold > 0.0f) {
        D_004848D0 = hold - t;
    } else {
        StateMachineSetState_28ede0(D_0048470C, (u16)D_004848D4, 0);
    }
    return 1;
}
