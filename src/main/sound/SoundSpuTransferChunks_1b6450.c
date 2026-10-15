#include "types.h"

s32 SoundQueueCmd_1b6d60(s32, void *, s32);
s32 SifDmaSendSync_1c21e0(s32, s32, s32);

typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 e;
} Msg;

s32 SoundSpuTransferChunks_1b6450(s32 arg0, s32 arg1, s32 total, s32 arg3, s32 chunk)
{
    s32 d;
    s32 src;
    s32 dst;
    s32 i;
    s32 n;
    Msg m;

    chunk = chunk / 64 * 64;
    if (chunk <= 0) {
        return -1;
    }
    src = arg0;
    dst = arg1;
    d = arg3;
    for (i = 0; i < total;) {
        n = total - i;
        if (chunk < n) {
            n = chunk;
        }
        SifDmaSendSync_1c21e0(src, d, chunk);
        m.b = 0;
        m.c = d;
        m.a = 0;
        m.e = n;
        m.d = dst;
        SoundQueueCmd_1b6d60(9, &m, 0x14);
        i += n;
        dst += n;
        src += n;
    }
    return 0;
}
