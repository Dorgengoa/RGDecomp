#include "types.h"
/* insect 0x00512B70 -- 2 instructions.  A one-line forwarder: the first
 * argument is dereferenced and the second passed through, so the call is a
 * tail call and mwcc emits `j func_28AA30` with the load in the delay slot. */

typedef struct Holder {
    void *m00;                      /* +0x00 */
} Holder;

extern void *func_28AA30(void *bank, s32 id);

void *insect_InsectMsgGet_512b70(Holder *h, s32 id)
{
    return func_28AA30(h->m00, id);
}
