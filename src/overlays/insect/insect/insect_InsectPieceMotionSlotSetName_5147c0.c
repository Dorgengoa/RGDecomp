#include "types.h"
/* insect 0x005147C0 -- 72 B / 18 words.  Branch-free clear-then-forward,
 * a pure SUBSTITUTION off the already-matching insect_InsectAbilitySetName_51d230.c: the
 * only differences are the fill length (0x14 instead of 0x20) and that the
 * object handed to both calls is a SUB-STRUCT at +0x0C rather than the
 * parameter itself -- retail recomputes `addiu $4, $17, 0xC` before EACH
 * call, which is the tell for `&a->f0C` written twice rather than a named
 * local (a named local would be materialised once).
 * `addiu $6, $0, 0x14` scheduled above the callee-saved frame stores is
 * ordinary prologue scheduling, exactly as in the 0051D230 seed. */
typedef struct Sub14 { u8 raw[0x14]; } Sub14;
typedef struct WObj { u8 pad00[0xC]; Sub14 f0C; } WObj;

extern void func_131B60(void *a, s32 v, s32 n);
extern void func_134A98(void *a, void *b);

void insect_InsectPieceMotionSlotSetName_5147c0(WObj *a, void *b)
{
    func_131B60(&a->f0C, 0, 0x14);
    func_134A98(&a->f0C, b);
}
