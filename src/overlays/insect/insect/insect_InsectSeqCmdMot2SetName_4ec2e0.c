#include "types.h"
/* insect 0x004ec2e0 -- 80 B / 20 words.  RANK-5 twin pair:
 * insect_InsectSeqCmdMot2SetName_4ec2e0 and insect_InsectSeqCmdMotSetName_4ec380 are BYTE-FOR-BYTE identical
 * listings apart from their own addresses, so this file is the same source
 * under two names.
 *
 * `addiu $4, $17, 0xC` is emitted TWICE -- once for each call -- so the two
 * `&a->f0C` are two separate source expressions, not one CSE'd local.
 * `addiu $6, $0, 0x14` is hoisted above the callee-saved frame stores; that
 * is ordinary prologue scheduling, not a source order (same note as the
 * already-matching insect_InsectAbilitySetName_51d230.c, the plain clear-then-forward
 * template this is built from).
 * The guard's `beql $16, $0` skips the call, so the FALL-THROUGH is the if
 * body: `if (b != 0)`, the same polarity the seed insect_InsectAbilityTableLoad_51d0b0.c uses.
 * sq/lq callee-saved framing is the overlay default and implies no 128-bit
 * type here.
 */

typedef struct WObj { u8 pad00[0xC]; u8 f0C[0x14]; } WObj;

extern void func_131B60(void *p, s32 v, s32 n);
extern void func_134A98(void *a, void *b);

void insect_InsectSeqCmdMot2SetName_4ec2e0(WObj *a, void *b)
{
    func_131B60(&a->f0C, 0, 0x14);
    if (b != 0) {
        func_134A98(&a->f0C, b);
    }
}
