#include "types.h"

typedef unsigned __int128 u128;

struct Buf {
    u8 pad0[0x10];
    u32 count;
    u8 *data;
};

struct Obj {
    u8 pad0[0x12];
    u8 bpp;
    u8 pad13[0x50 - 0x13];
    u128 m50;
    Buf *m60;
    u8 pad64[8];
    u16 m6C;
};

extern "C" void UvDecodeU8_14b260(u128 *, u16 *, u128 *);
extern "C" void UvDecodeU16_14b300(u128 *, u32 *, u128 *);
extern "C" void UvDecodeF32_14b480(u128 *, u64 *);

extern "C" s32 ModelReadUVs_14c870(Obj **h, u128 *dst, s32 n, s32 start)
{
    bool ok;
    Obj *o;
    Buf *b;
    u128 v;
    s32 i;
    u8 *data;
    s32 bpp;

    ok = false;
    o = *h;
    if (o != 0 && o->m6C == 0) {
        ok = true;
    }
    if ((ok & 0xFF) == 0) {
        return 0;
    }
    b = o ? o->m60 : 0;
    if ((u32)(start + n) >= b->count) {
        n = b->count - start;
    }
    if (n <= 0) {
        return 0;
    }
    {
        data = b->data;
        v = o->m50;
        bpp = *h ? (*h)->bpp : 32;
        switch (bpp) {
        case 32:
            for (i = 0; i < n; i++) {
                UvDecodeF32_14b480(dst + i, (u64 *)data + (start + i));
            }
            break;
        case 16:
            for (i = 0; i < n; i++) {
                UvDecodeU16_14b300(dst + i, (u32 *)data + (start + i), &v);
            }
            break;
        case 8:
            for (i = 0; i < n; i++) {
                UvDecodeU8_14b260(dst + i, (u16 *)data + (start + i), &v);
            }
            break;
        }
    }
    return n;
}
