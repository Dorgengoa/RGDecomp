#include "types.h"
/* insect 0x004EA060 -- 60 bytes, 15 instructions.  `beql $2, $0` with
 * `sw $0, 0x190($16)` in the delay slot annuls the STORE, so the store must be
 * the ELSE arm: the `if (s == 0) { store; return; }` spelling annuls the
 * `lw 0($2)` instead and costs a join `b` (16 words vs 15). */

typedef struct Sub {
    s32 f00;                        /* +0x00 */
} Sub;

typedef struct Obj {
    u8  pad000[0x2C];
    u8  f02C[0x190 - 0x2C];
    s32 f190;                       /* +0x190 */
} Obj;

extern Sub *insect_InsectSeqCmdQueueHead_4ea5c0(void *p);
extern void insect_InsectSeqFindHandler_4ea010(Obj *o, s32 v);

void insect_InsectSeqBindHeadHandler_4ea060(Obj *o)
{
    Sub *s = insect_InsectSeqCmdQueueHead_4ea5c0(o->f02C);

    if (s != 0) {
        insect_InsectSeqFindHandler_4ea010(o, s->f00);
    } else {
        o->f190 = 0;
    }
}
