#include "types.h"
#undef NULL
#define NULL 0

class Elem {
public:
    VC_VPTR_MEMBER;
    
    
    s32 write(u8 * a0, s32 a1) { return VCM(s32, (void *, u8 *, s32), 0x14, a0, a1); }
};

class Saver {
public:
    VC_VPTR_MEMBER; s32 dataOffset() { return VCM0(s32, 0x8); }
    
    s32 dataSize() { return VCM0(s32, 0x10); }
};

extern "C" {
u8 *PoolGetUsedElem_36acb0(s32, s32);
s32 SerialWriteChunkHeader_370e50(u8 *, s32, s32, s32, s32 **);
void *memcpy(void *, const void *, u32);
}
extern "C" s32 D_00465B50[];
extern "C" s32 D_00465B70[];

extern "C" s32 PartySerialize_3bf820(Saver *self, u8 *pb, s32 sz) {
    s32 total;
    u8 *buf;
    u32 size;
    s32 *h0;
    s32 *h1;
    s32 *h2;
    s32 *h3;
    s32 *h4;
    s32 n;
    s32 len;
    s32 cnt;
    s32 i;
    u8 *e;



    if (pb == NULL || sz <= 0) {
        return 0;
    }
    size = sz;
    buf = pb;
    h0 = NULL;
    total = 0;
    n = SerialWriteChunkHeader_370e50(buf, size, 8, 0, &h0);
    total += n;
    buf += n;
    size -= n;
    h1 = NULL;
    n = SerialWriteChunkHeader_370e50(buf, size, 9, 0, &h1);
    total += n;
    buf += n;
    size -= n;
    if (h0 != NULL) {
        *h0 += n;
    }
    len = self->dataSize();
    if (len <= (s32)size) {
        memcpy(buf, (u8 *)self + self->dataOffset(), len);
        total += len;
        buf += len;
        size -= len;
        if (h1 != NULL) {
            *h1 += len;
        }
        if (h0 != NULL) {
            *h0 += len;
        }
    }
    h2 = NULL;
    n = SerialWriteChunkHeader_370e50(buf, size, 0xC, 0, &h2);
    total += n;
    buf += n;
    size -= n;
    if (h0 != NULL) {
        *h0 += n;
    }
    if ((s32)size >= 0x33C0) {
        memcpy(buf, *(void **)((u8 *)self + 0x174), 0x33C0);
        total += 0x33C0;
        buf += 0x33C0;
        size -= 0x33C0;
        if (h2 != NULL) {
            *h2 += 0x33C0;
        }
        if (h0 != NULL) {
            *h0 += 0x33C0;
        }
    }
    h3 = NULL;
    n = SerialWriteChunkHeader_370e50(buf, size, 0xA, 0, &h3);
    total += n;
    buf += n;
    size -= n;
    if (h0 != NULL) {
        *h0 += n;
    }
    cnt = D_00465B50[0];
    for (i = 0; i < cnt; i++) {
        e = PoolGetUsedElem_36acb0(*(s32 *)((u8 *)self + 0x168), i);
        if (e == NULL) {
            continue;
        }
        if (((u64)((s64)e[0xA] << 62) >> 63) != 0) {
            continue;
        }
        n = ((Elem *)e)->write(buf, size);
        total += n;
        buf += n;
        size -= n;
        if (h3 != NULL) {
            *h3 += n;
        }
        if (h0 != NULL) {
            *h0 += n;
        }
    }
    h4 = NULL;
    n = SerialWriteChunkHeader_370e50(buf, size, 0xD, 0, &h4);
    size -= n;
    total += n;
    buf += n;
    if (h0 != NULL) {
        *h0 += n;
    }
    len = D_00465B70[0] * 4;
    if (len <= (s32)size) {
        memcpy(buf, *(void **)((u8 *)self + 0x17C), len);
        total += len;
        if (h4 != NULL) {
            *h4 += len;
        }
        if (h0 != NULL) {
            *h0 += len;
        }
    }
    return total;
}
