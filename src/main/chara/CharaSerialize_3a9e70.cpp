/* PARKED at triage (0 round trips): heavy vtable-call chain over an
 * unresolved "?"-typed arg0 with several output-pointer parameters
 * (sp6C/sp68/sp64) whose real struct layout is unclear from the draft alone
 * -- worth a raw-asm read in a future session. Deferred to preserve lane
 * throughput. See asm/matchings/main/CharaSerialize_3a9e70.s. */
/* s49m: 25 */
#include "types.h"

class Part {
public:
    virtual void v08();
    virtual void v0C();
    virtual void v10();
    virtual s32 write(u8 *p, s32 n);
};

class Obj {
public:
    virtual s32 dataOffset();
    virtual void v0C();
    virtual s32 dataSize();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual s32 version();
};

extern "C" {
s32 SerialWriteChunkHeader_370e50(u8 *, s32, s32, s32, s32 **);
void memcpy(void *, void *, s32);
}

extern "C" s32 CharaSerialize_3a9e70(Obj *self, u8 *dst, s32 size)
{
    s32 len;
    s32 *c6C;
    s32 *c68;
    s32 total;
    u8 *p;
    s32 remain;
    s32 *c64;
    s32 i;
    s32 n;

    if (dst == 0 || size <= 0) {
        return 0;
    }
    c6C = 0;
    remain = (s32)(u32)size;
    total = 0;
    n = SerialWriteChunkHeader_370e50(dst, remain, 4, self->version(), &c6C);
    total += n;
    p = dst + n;
    remain -= n;
    c68 = 0;
    n = SerialWriteChunkHeader_370e50(p, remain, 5, 0, &c68);
    total += n;
    p += n;
    remain -= n;
    if (c6C != 0) {
        *c6C += n;
    }
    len = self->dataSize();
    if (len <= remain) {
        memcpy(p, (u8 *)self + self->dataOffset(), len);
        total += len;
        p += len;
        remain -= len;
        if (c68 != 0) {
            *c68 += len;
        }
        if (c6C != 0) {
            *c6C += len;
        }
    }
    c64 = 0;
    n = SerialWriteChunkHeader_370e50(p, remain, 6, 0, &c64);
    total += n;
    p += n;
    remain -= n;
    if (c6C != 0) {
        *c6C += n;
    }
    for (i = 0; i < 10; i++) {
        n = ((Part *)((u8 *)self + 0x308 + i * 0x28))->write(p, remain);
        total += n;
        p += n;
        remain -= n;
        if (c64 != 0) {
            *c64 += n;
        }
        if (c6C != 0) {
            *c6C += n;
        }
    }
    return total;
}
