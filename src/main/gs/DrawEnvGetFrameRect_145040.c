#include "types.h"
typedef struct A145040 { u8 pad000[0x4]; s32 m04; s32 m08; } A145040;
typedef struct B145040 { u8 pad000[0x270]; A145040 *m270; } B145040;
typedef struct O145040 { s32 m0; s32 m4; s32 m8; s32 mC; } O145040;
void DrawEnvGetFrameRect_145040(B145040 *b, O145040 *out)
{
    A145040 *d;

    d = b->m270;
    out->m0 = 0;
    out->m4 = 0;
    out->m8 = d->m08;
    out->mC = d->m04;
}
