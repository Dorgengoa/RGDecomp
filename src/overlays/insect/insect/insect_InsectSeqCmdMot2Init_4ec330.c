#include "types.h"
/* insect 0x00004EC330 -- 76 B / 19 words.  EXACT TWIN of the
 * other member of this pair (insect_InsectSeqCmdMot2Init_4ec330 / insect_InsectSeqCmdMotInit_4ec3d0): the
 * listings differ only in the forwarded callee and in the `kind` constant.
 *
 * The Slot base (kind at +0x00, arg at +0x04, insect_InsectSeqCmdInit_4ec490 run first)
 * is the f_setkind family shape already byte-identical in
 * src/overlays/insect/insect_InsectSeqCmdSetAtkElemInit_4ec1b0.c; this pair extends it with the
 * 0x20/0x24/0x28 triple.
 * `lui $3, 0x3F80 / sw 0x24` is mwcc storing the float constant 1.0f with
 * integer ops (the low half is zero, so no .lit4 load is needed) -- the lane
 * is float-op free by the same token.
 * Store order is 0x20, 0x24, 0x28, 0x00, 0x04: the base fields are written
 * LAST, so `kind`/`arg` are the tail of the ctor, not the head.
 * `addiu $3, $0, 4` between the 0x24 and 0x28 stores is scheduling. */

typedef struct Slot {
    s32 kind;                   /* +0x00 */
    s32 arg;                    /* +0x04 */
    u8  pad08[0x20 - 0x08];
    s32 m20;                    /* +0x20 */
    f32 m24;                    /* +0x24 */
    s32 m28;                    /* +0x28 */
} Slot;

extern void insect_InsectSeqCmdInit_4ec490(Slot *s);
extern void insect_InsectSeqCmdMot2SetName_4ec2e0(Slot *s, void *b);

void insect_InsectSeqCmdMot2Init_4ec330(Slot *s)
{
    insect_InsectSeqCmdInit_4ec490(s);
    insect_InsectSeqCmdMot2SetName_4ec2e0(s, 0);
    s->m20 = 0;
    s->m24 = 1.0f;
    s->m28 = 0;
    s->kind = 4;
    s->arg = 0;
}
