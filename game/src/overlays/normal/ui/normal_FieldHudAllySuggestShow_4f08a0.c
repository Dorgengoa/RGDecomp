/* rgp:protos */
#define RGP_SELF_normal_FieldHudAllySuggestShow_4f08a0 1
#include "port/game_protos.h"
#line 1
/* ★★★★★★★★ SESSION 45 (n45N): BYTE-IDENTICAL, 65/65 words, MERGED.
 * ONE CHARACTER.  `func_291110(p, 0x70, 0, 0)` -> `func_291110(p, 0x70, 0, 1)`.
 *
 * HOW IT WAS FOUND, because the method generalises.  The unit was 66 words vs
 * 65 and 8 bad; od.py showed a fifteen-row block of differences and nothing
 * that named a cause.  build/wf-normal/s45/mdiff.py -- difflib over the OPCODE
 * stream DECODED FROM THE ENCODED WORD on both sides -- reduced it to exactly
 * two lines:
 *     delete @retail 004F0970   OURS  move a2,zero
 *     insert @retail 004F09A4   RETAIL nop
 * i.e. we spend one instruction retail does not.  Retail's window is
 *     addiu $7,$0,0x1 | bne $3,$7,.L004F098C | nop |
 *     daddu $4,$18,$0 | addiu $5,$0,0x70 | jal func_291110 | daddu $6,$0,$0
 * -- `$7` is never re-loaded before the first call, so THE FIRST CALL PASSES
 * THE `1` THAT `if (p->f3A6 == 1)` BUILT.  m2c had guessed 0 for that argument;
 * an argument whose value equals a nearby compare constant is invisible to
 * every count-based screen because a wrong constant costs ONE WORD, not a
 * wrong opcode.  [[levers.d/normal-session45-levers]].
 *
 * ⚠ MEASURED: changing the SECOND call's last argument (0x72) to 0 instead is
 * still 66 words; doing both is 65 words and 1 bad.  Only the first call. */
#include "types.h"
/* normal 0x004F08A0 -- twin of normal_FUN_004F09B0: same two state gates, then
 * a five-row walk over the p->f2DC table and a tail gated on f3A6 == 1.
 * The orphan `addiu $5, $0, 0x5F` at 0x004F08D4 is the branch-likely
 * duplication of the body's first instruction. */
typedef struct N {
    u8  pad000[0x2DC];
    s16 f2DC[1];
    u8  pad2DE[0x3A2 - 0x2DE];
    s16 f3A2;
    u8  pad3A4[0x2];
    s16 f3A6;
    u8  pad3A8[0x4];
    s16 f3AC;
} N;

/*rgp*/
/*rgp*/

void normal_FieldHudAllySuggestShow_4f08a0(N *p)
{
    u16 id;
    s32 i;
    s16 st;

    st = p->f3A2;
    if (st == 10 || st == 0) {
        return;
    }
    p->f3AC = 0;
    UiSetWidgetVisible_290010(p, 0x5F, 1, -1);
    UiSetWidgetVisible_290010(p, 0x73, 1, -1);
    UiSetWidgetsVisibleById_291110(p, 0x6B, 0, 1);
    id = 0x74;
    for (i = 0; i < 5; i++) {
        if (p->f2DC[i * 4] == 0) {
            UiSetWidgetsVisibleById_291110(p, id, 0, 1);
        }
        id++;
    }
    if (p->f3A6 == 1) {
        UiSetWidgetsVisibleById_291110(p, 0x70, 0, 1);
        UiSetWidgetsVisibleById_291110(p, 0x72, 0, 1);
    }
}
