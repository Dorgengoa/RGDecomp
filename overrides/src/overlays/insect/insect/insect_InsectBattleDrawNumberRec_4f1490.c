/* rg-override: replaces game/src/overlays/insect/insect/insect_InsectBattleDrawNumberRec_4f1490.c sha256 c03d4ee990dbfb47ef61cba9a07c425e357d3aed7203e650b5a0c715f51f4323
 * why: retail's insect_InsectBattleDrawNumberRec_4f1490 passes its entry $a2 (untouched)
 * to Sprintf(buf, "%d"); the decomp's definition has no third parameter and the
 * caller computes the five numbers (i, a, b, c, e: listing $20/$19/$18/$17/$22 moved
 * to $a2 before each jal) without passing them, so i686 printed stack garbage
 * (docs/VARARGS-CENSUS.md class 3, BRINGUP.md checkpoint) */
/* rgp:protos */
#define RGP_SELF_insect_InsectBattleDrawNumberRec_4f1490 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F1490 -- 76 bytes.  func_1343B8 is the sprintf-alike, so the
 * 0x80-byte frame local is a text buffer and insect_D_00524BC8 is its format. */

extern void Sprintf_1343b8(void *dst, const char *fmt, ...);
/*rgp*/
extern char insect_D_00524BC8[];

void insect_InsectBattleDrawNumberRec_4f1490(s32 a, void *r, s32 n)
{
    char buf[0x80] __attribute__((aligned(16)));

    Sprintf_1343b8(buf, insect_D_00524BC8, n);
    insect_InsectBattleDrawTextRec_4f1410(a, r, buf);
}
