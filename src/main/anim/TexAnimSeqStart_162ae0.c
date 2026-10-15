#include "types.h"

typedef struct S00162AE0 {
    s32 f0;                   /* +0x0 */
    s32 arr[1];               /* +0x4 */
} S00162AE0;

void TexAnimSeqStart_162ae0(S00162AE0 *p, s32 i)
{
    if (i < 0 || i >= p->f0) {
        return;
    }
    p->arr[i] = 1;
}
