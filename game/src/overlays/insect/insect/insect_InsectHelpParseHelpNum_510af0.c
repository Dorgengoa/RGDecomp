/* rgp:protos */
#define RGP_SELF_insect_InsectHelpParseHelpNum_510af0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00510AF0 -- 56 bytes, 14 instructions, 2 calls.  The script-VM
 * context global D_00484FD0 (`lw $2,-0x1A0($28)`) is tested, then RE-LOADED
 * after the argument read -- mwcc will not move the load across the call
 * ([[insect-load-across-store]]).  The guard is the positive `if` so the
 * `return 0` folds into the `beql`'s delay slot.
 */

typedef struct Arg { u8 raw[8]; } Arg;

extern void *D_00484FD0;

/*rgp*/
/*rgp*/

s32 insect_InsectHelpParseHelpNum_510af0(Arg *p)
{
    if (D_00484FD0 != 0) {
        insect_InsectHelpAllocEntries_510d20(D_00484FD0, VariantGetInt_15f780(p));
        return 1;
    }
    return 0;
}
