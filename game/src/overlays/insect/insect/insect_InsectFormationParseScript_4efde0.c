/* rgp:protos */
#define RGP_SELF_insect_InsectFormationParseScript_4efde0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EFDE0 -- the THIRD member of the script-runner family
 * (0x00522CC0 / 0x00510B30 / here): same 0xED0-byte VM frame at $29+0x40 and
 * the same four calls, with its own command table (insect_D_005249F0) and its own
 * context global (D_00484F58, at _gp-0x218 and so inside the gp window).
 * ⚠ The publish sits in func_15F3F0's delay slot as in 0x00510B30, and one call
 * EARLIER in 0x00522CC0.  Read the delay slot per member; the family shares
 * everything else. */
typedef struct ScriptVm { u8 raw[0xED0]; } ScriptVm;

extern void *D_00484F58;
extern u8 insect_D_005249F0[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectFormationParseScript_4efde0(void *ctx, s32 b, s32 c)
{
    ScriptVm sp40 __attribute__((aligned(16)));

    TextReaderCtor_15f140(&sp40);
    BuildKeywordHashTable_15f270(&sp40, insect_D_005249F0);
    TextReaderOpen_15f1b0(&sp40, b, c);
    D_00484F58 = ctx;
    TextReaderParseAll_15f3f0(&sp40);
    D_00484F58 = 0;
}
