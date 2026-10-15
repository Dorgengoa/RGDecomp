#include "types.h"
struct S3a5ec0 {
    u8 pad000[0x238];
    s32 m238; s32 m23C; u8 pad240[0x4]; s32 m244; s32 m248;
    u8 b0 : 3; u8 b3 : 1; u8 rest : 4;
    u8 pad24D[0x947];
    s32 mB94;
};
extern s32 D_004837C0;
extern s32 D_004837C4;
extern void CharaSysResetAll_3a5ca0(struct S3a5ec0 *);

void CharaSysReset_3a5ec0(struct S3a5ec0 *p)
{
    D_004837C0 = 0;
    D_004837C4 = 0;
    p->m238 = 0;
    p->m23C = 0;
    p->m244 = 0;
    p->mB94 = 0;
    p->m248 = 0;
    p->b3 = 1;
    CharaSysResetAll_3a5ca0(p);
}
