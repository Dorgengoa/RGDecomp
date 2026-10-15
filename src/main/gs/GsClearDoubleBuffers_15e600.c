#include "types.h"

extern void sceGsSetDefDBuff(void *db, s32 psm, s32 w, s32 h, s32 zpsm,
                             s32 zbuf, s32 clear);
extern void FlushCache(s32 mode);
extern void sceGsSyncV(s32 x);
extern void sceGsPutDrawEnv(void *env);
extern void sceGsSyncPath_109030(s32 a, s32 b);

void GsClearDoubleBuffers_15e600(void)
{
    u8 db[0x230];

    sceGsSetDefDBuff(db, 0, 0x280, 0x1C0, 2, 0x31, 1);
    FlushCache(0);
    sceGsSyncV(0);
    sceGsPutDrawEnv(db + 0x50);
    sceGsSyncPath_109030(0, 0);
    sceGsPutDrawEnv(db + 0x140);
    sceGsSyncPath_109030(0, 0);
}
