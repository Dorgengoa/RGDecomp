#include "types.h"

typedef struct {
    u8 pad0[8];
    s32 x8;
    u16 xC;
    u8 padE[3];
    u8 x11;
    u8 pad12[0xE];
    s64 x20;
    u8 pad28[0x18];
    s32 x40[4];
} Sub;

typedef struct {
    u8 pad0[0x18];
    u8 x18;
} Obj;

extern s32 TexSwizzleBlocks_157780(u16, u16, void *);
extern s32 NameTableAddEntry_159b70(Obj *, s32, s32, void **, u16, u16, s32, u8 *, s64, s64);
extern void *memcpy(void *, const void *, u32);

s32 Tim2RegisterPicture_159940(Obj *arg0, s32 arg1, s32 arg2, u8 *hdr, s64 arg4, s32 arg5) {
    u8 name[5];
    void *ptrs[4];
    u8 type;
    u16 w;
    u16 h;
    Sub *sub;
    s32 bpp;
    u8 *pal;
    s32 i;
    u8 *p;

    memcpy(name, hdr, 4);
    name[4] = 0;
    type = hdr[0x23];
    w = *(u16 *)(hdr + 0x24);
    h = *(u16 *)(hdr + 0x26);
    sub = (Sub *)(hdr + 0x10);
    switch (type) {
    case 1:
        bpp = 16;
        break;
    case 2:
        bpp = 24;
        break;
    case 3:
        bpp = 32;
        break;
    case 4:
        bpp = 4;
        break;
    case 5:
        bpp = 8;
        break;
    default:
        return 0;
    }
    pal = NULL;
    for (i = 0; i < 4; i++) {
        ptrs[i] = NULL;
    }
    if (arg5 == 0) {
        p = (u8 *)sub + sub->xC;
        ptrs[0] = p;
        if (bpp < 9) {
            pal = p + sub->x8;
        }
        if (sub->x11 > 1) {
            { u8 *q = (u8 *)ptrs[0] + sub->x40[0];
            for (i = 1; i < sub->x11; i++) {
                ptrs[i] = q;
                q += sub->x40[i];
            } }
        }
    }
    if (arg0->x18 != 0 && arg4 != 0 && ptrs[0] != NULL && bpp == 8 && sub->x11 == 1 &&
        TexSwizzleBlocks_157780(w, h, ptrs[0]) != 0) {
        arg4 = 0;
    }
    return NameTableAddEntry_159b70(arg0, arg1, arg2, ptrs, w, h, bpp, pal, sub->x20, arg4);
}
