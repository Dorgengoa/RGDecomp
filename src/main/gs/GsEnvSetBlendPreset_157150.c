#include "types.h"

typedef struct S00157150 {
    u8 pad0[0x10];
    s64 f10;                  /* +0x10 */
} S00157150;

extern s64 D_00449EF0[];

void GsEnvSetBlendPreset_157150(S00157150 *p, s32 i)
{
    if (i < 0 || i > 11) {
        return;
    }
    p->f10 = D_00449EF0[i];
}
