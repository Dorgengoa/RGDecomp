#include "types.h"
/* insect 0x005107D0 -- 80 bytes, 20 instructions, 3 calls.  The root handle is
 * fetched FIRST (the parameter copy sits in that call's delay slot), then two
 * nested guards gate the forward.  Both guards fall out to the shared
 * epilogue, so neither is an early return.
 */

typedef struct Root { u8 raw[4]; } Root;

extern Root *func_31A8D0(void);
extern s32   insect_InsectBattleGetSoundBank_50db50(Root *r);
extern void  func_1B9AE0(s32 a, s32 b, s32 c);

void insect_InsectBattlePlayBankSe_5107d0(s32 id)
{
    Root *r;

    r = func_31A8D0();
    if (id != -1) {
        if (r != 0) {
            func_1B9AE0(insect_InsectBattleGetSoundBank_50db50(r), id, 0);
        }
    }
}
