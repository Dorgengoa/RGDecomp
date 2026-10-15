#include "types.h"
#include "vm_slot.h"
/* insect 0x00523210 -- 52 B / 13 words.
 *
 * FIRST BUILD residue (11 words, len 0x2C vs 0x34): writing the global
 * straight into the argument list --
 *     insect_InsectAiCfgSelectLevel_522d30(D_004851B8, func_15F780(v));
 * let mwcc SINK the gp load past the call (`jal func_15F780` with a nop delay
 * slot, then `lw $4,0x48($28)`), so nothing was live across the call, no
 * callee-saved register was allocated and the frame shrank to 0x10 -- two
 * words short of retail's sq/lq $16 pair.
 *
 * NAMING THE HANDLE IN A LOCAL FIRST is the fix ([[insect-load-across-store]],
 * read the other way round): a call may write a global, so mwcc may not float
 * the load of D_004851B8 down past `func_15F780`, and the value has to live in
 * $16 across it -- which is exactly retail's `lw $16,0x48($28)` in the call's
 * delay slot.
 *
 * Argument two is spelled s32, not the callee's own s16: retail moves $2 into
 * $5 with a bare `daddu` and no narrowing, so no (short) conversion is present
 * at this call site. */
extern void *D_004851B8;
extern void *insect_InsectAiCfgSelectLevel_522d30(void *a, s32 b);
extern s32 func_15F780(Slot *v);

s32 insect_InsectAiCfgParseAiLevel_523210(Slot *v)
{
    void *h;

    h = D_004851B8;
    insect_InsectAiCfgSelectLevel_522d30(h, func_15F780(v));
    return 1;
}
