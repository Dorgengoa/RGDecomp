/* rgp:protos */
#define RGP_SELF_insect_InsectHelpParseScript_510b30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00510B30 -- the sibling of 0x00522CC0: same VM frame, same four
 * calls, a different command table (insect_D_00525150) and a different context global
 * (D_00484FD0, the one 0x005109F0 reads as `lw $2,-0x1A0($28)`).
 * ⚠ The context publish is one call LATER here -- `sw $18, -0x1A0($28)` sits in
 * func_15F3F0's delay slot, not func_15F270's -- so the two siblings differ by
 * where that statement goes.  Read the delay slot, do not copy the sibling. */
typedef struct ScriptVm { u8 raw[0xED0]; } ScriptVm;

extern void *D_00484FD0;
extern u8 insect_D_00525150[];
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectHelpParseScript_510b30(void *ctx, s32 b, s32 c)
{
    ScriptVm sp40 __attribute__((aligned(16)));

    TextReaderCtor_15f140(&sp40);
    BuildKeywordHashTable_15f270(&sp40, insect_D_00525150);
    TextReaderOpen_15f1b0(&sp40, b, c);
    D_00484FD0 = ctx;
    TextReaderParseAll_15f3f0(&sp40);
    D_00484FD0 = 0;
}
