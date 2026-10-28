/* rgp:protos */
#define RGP_SELF_insect_InsectAiCfgParseScript_522cc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00522CC0 -- run a script through the SB2 VM the overlay keeps in its
 * own frame (0xED0 bytes at $29+0x40), against the command table insect_D_00524590.
 * Three arguments, all marshalled by the caller at 0x004F9820 ($4/$5/$6).
 *
 * D_004851B8 is inside the gp window (_gp = 0x00485170, window
 * 0x47D170..0x48D170), so it stays a PLAIN extern and takes %gp_rel; the table
 * at 0x00524590 is overlay data, outside the window, so it must be `const` or
 * mwcc gives it a %gp_rel relocation that cannot be resolved at link time.
 *
 * `sw $18, 0x48($28)` sits in func_15F270's delay slot, which is the recorded
 * "a store written before a call fills that call's delay slot" shape -- the
 * context publish is written immediately ahead of that call.  ⚠ The sibling
 * 0x00510B30 is the same function with the publish one call LATER, so read the
 * slot rather than copying this one's order. */
typedef struct ScriptVm { u8 raw[0xED0]; } ScriptVm;

extern void *D_004851B8;
extern u8 insect_D_00524590[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectAiCfgParseScript_522cc0(void *ctx, s32 b, s32 c)
{
    ScriptVm sp40 __attribute__((aligned(16)));

    TextReaderCtor_15f140(&sp40);
    D_004851B8 = ctx;
    BuildKeywordHashTable_15f270(&sp40, insect_D_00524590);
    TextReaderOpen_15f1b0(&sp40, b, c);
    TextReaderParseAll_15f3f0(&sp40);
    D_004851B8 = 0;
}
