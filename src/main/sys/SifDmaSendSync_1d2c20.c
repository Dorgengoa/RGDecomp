#include "types.h"

typedef struct SifDma_FUN_001d2c20 {
    void *data;
    void *addr;
    s32 size;
    s32 mode;
} SifDma_FUN_001d2c20;

extern void FlushCache(s32 n);
extern s32 sceSifSetDma(SifDma_FUN_001d2c20 *d, s32 n);
extern s32 sceSifDmaStat(s32 id);
extern void DelayThread_117618(s32 n);

s32 SifDmaSendSync_1d2c20(void *addr, void *data, s32 size)
{
    SifDma_FUN_001d2c20 d;
    s32 id;

    if (size <= 0) {
        return 0;
    }
    d.addr = addr;
    d.data = data;
    d.size = size;
    d.mode = 0;
    FlushCache(0);
    id = sceSifSetDma(&d, 1);
    while (sceSifDmaStat(id) >= 0) {
        DelayThread_117618(10);
    }
    return size;
}
