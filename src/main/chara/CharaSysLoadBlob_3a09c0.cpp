#include "types.h"

class Obj003a09c0 {
public:
    virtual s32 slot08();
    virtual void slot0C();
    virtual s32 slot10();
    u8 pad4[0x238 - 0x4];
    s32 unk238;
    s32 unk23C;
    s32 unk240;
    s32 unk244;
    s32 unk248;
    u8 pad24C[0xB94 - 0x24C];
    s32 unkB94;
};

extern "C" void *memcpy(void *, const void *, u32);

extern "C" s32 CharaSysLoadBlob_3a09c0(Obj003a09c0 *obj, void *src, s32 len)
{
    s32 s238;
    s32 s23C;
    s32 s244;
    s32 sB94;
    s32 s248;
    s32 n;

    if (src == NULL || len <= 0) {
        return 0;
    }

    s238 = obj->unk238;
    s23C = obj->unk23C;
    s244 = obj->unk244;
    sB94 = obj->unkB94;
    s248 = obj->unk248;
    n = obj->slot10();
    if (len < n) {
        n = len;
    }

    memcpy((u8 *)obj + obj->slot08(), src, n);
    obj->unk238 = s238;
    obj->unk23C = s23C;
    obj->unk244 = s244;
    obj->unkB94 = sB94;
    obj->unk248 = s248;
    return n;
}
