/* rgp:protos */
#define RGP_SELF_insect_InsectBattleDrawHud_50a530 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050A530 -- pass-28 unnamed-listing conversion, and the largest of
 * the thirty (0xB8).  Five independent `insect_InsectBattleTestFlag_50da40(o, K) != 0`
 * guards, each `beql $2, $0` past its arm; the repeated `daddu $4, $16, $0`
 * after every arm is the next guard's own first argument, not a residue. */
typedef struct Ins {
    u8 pad0000[0xC0];
    s32 mC0;           /* +0x00C0 */
    u8 pad00C4[0x35F4 - 0xC4];
    s32 m35F4;         /* +0x35F4 */
    u8 pad35F8[0x5178 - 0x35F8];
    u8 m5178[4];       /* +0x5178 */
} Ins;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleDrawHud_50a530(Ins *o)
{
    if (insect_InsectBattleTestFlag_50da40(o, 0x2A) != 0) {
        insect_InsectBattleEffectsDraw_51d410(o->m5178);
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x2D) != 0) {
        insect_InsectBattleDrawHpBars_4f5bd0(o, o->mC0);
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x2E) != 0) {
        insect_InsectBattleDrawPieceIcons_4f5430(o, o->mC0);
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x31) != 0) {
        DamagePopupDrawAll_2d2ea0(insect_InsectGetDamagePopupList_5108c0());
    }
    if (insect_InsectBattleTestFlag_50da40(o, 0x45) != 0) {
        TextEntryDraw_436610(o->m35F4);
    }
}
