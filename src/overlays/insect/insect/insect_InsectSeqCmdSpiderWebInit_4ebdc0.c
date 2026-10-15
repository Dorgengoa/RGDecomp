#include "types.h"
/* insect 0x004EBDC0 -- pass-28 unnamed-listing conversion.  The f_setkind
 * family shape (see insect_InsectSeqCmdSnailThrowInit_4ebe10) with a memset and three more field
 * initialisers: insect_InsectSeqCmdInit_4ec490 takes ONE argument, read off the callee's
 * own listing.  ⚠ The +0x24 store precedes the +0x20 store in the listing and
 * that order is kept. */
typedef struct Slot {
    s32 kind;          /* +0x00 */
    s32 arg;           /* +0x04 */
    u8 pad08[0x0C - 0x08];
    u8 mC[0x14];       /* +0x0C */
    s32 m20;           /* +0x20 */
    s32 m24;           /* +0x24 */
    s32 m28;           /* +0x28 */
} Slot;

extern void insect_InsectSeqCmdInit_4ec490(Slot *s);
extern void func_131B60(void *dst, s32 c, s32 n);

void insect_InsectSeqCmdSpiderWebInit_4ebdc0(Slot *s)
{
    insect_InsectSeqCmdInit_4ec490(s);
    s->kind = 0x1D;
    s->arg = 0;
    func_131B60(s->mC, 0, 0x14);
    s->m24 = 0;
    s->m20 = 0;
    s->m28 = 6;
}
