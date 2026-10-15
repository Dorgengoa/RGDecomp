#include "types.h"

typedef struct S00162AA0 {
    s32 f0;                   /* +0x0 */
    s32 a[0x30];              /* +0x4 */
    s32 b[0x30];              /* +0xC4 */
    s32 c[0x60];              /* +0x184 */
    s32 d[0x30];              /* +0x304 */
} S00162AA0;

void TexAnimSeqReset_162aa0(S00162AA0 *p, s32 i)
{
    if (i < 0 || i >= p->f0) {
        return;
    }
    p->a[i] = 0;
    p->c[i] = p->b[i];
    p->d[i] = 0;
}
