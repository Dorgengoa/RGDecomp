#include "types.h"

extern void ReqEntryInit_3ee700(void *);

/* $18 = pointer, $17 = counter, $16 = the flag: the flag takes the LOWEST
   callee-saved register, so it is the LAST-declared local, not the parameter
   itself.  `andi $16,$5,0xFF` is that local's u8 truncation. */

typedef struct {
    u8 b0 : 1;
} Elt640;

void ReqListResetWithFlagMaybe_3ee640(u8 *p, s32 flagp)
{
    u8 *q;
    s32 i;
    u8 flag;

    q = p + 8;
    flag = (u8)flagp;
    *(s32 *)(p + 0) = 0;
    *(s32 *)(p + 4) = 0;
    for (i = 0; i < 6; i++) {
        ReqEntryInit_3ee700(q);
        ((Elt640 *)q)->b0 = flag;
        q += 0xC;
    }
}
