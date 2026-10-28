#include "types.h"
#pragma divbyzerocheck on

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    u8 pad38[0x18];
    s32 unk50;
    u8 pad54[0x4];
    s32 unk58;
    u8 pad5C[0x1C];
    u8 *unk78;
    u8 pad7C[0x50];
    f32 unkCC;
} Snd1bc;

typedef struct {
    s32 x;
    s32 y;
} Pair1bc;

typedef struct {
    u8 id[4];
    s32 a;
    s32 b;
    s32 c;
    Pair1bc e[0x30];
} Big1bc;

extern "C" s32 memcmp(const void *, const void *, u32);
extern "C" void *memset(void *, s32, u32);
extern "C" char D_0045AC58[];
extern "C" char D_0045AC60[];
extern "C" char D_0045AC68[];
extern "C" char D_0045AC70[];
extern "C" char D_0045AC78[];
extern "C" char D_0045AC80[];
extern "C" char D_0045AC88[];

extern "C" s32 WavHeaderParse_1bc220(Snd1bc *arg0, u8 *arg1, s32 arg2)
{
    u8 *keep;
    u8 *p;
    u8 *c;
    u8 *buf;
    u32 q;
    f32 f;
    u8 *data;
    s32 size;
    s32 *src;
    s32 *dst;
    s32 n;

    keep = arg0->unk78;
    memset(arg0, 0, 0xD0);
    arg0->unk78 = keep;
    if (memcmp(arg1, D_0045AC58, 4) != 0) {
        return 0;
    }
    if (memcmp(arg1 + 8, D_0045AC60, 4) != 0) {
        return 0;
    }
    p = arg1 + 0xC;
    arg0->unkCC = 1.0f;
    while (1) {
        if (memcmp(p, D_0045AC68, 4) == 0) {
            c = p;
            size = *(s32 *)(c + 4);
            data = c + 8;
            arg0->unk8 = *(s32 *)(c + 0xC);
            p = data + size;
            arg0->unkC = 0x10;
            q = (*(u32 *)(c + 0xC) << 12) / 48000;
            arg0->unk10 = q;
            if ((s32)q > 0x1000) {
                arg0->unk10 = 0x1000;
            }
            arg0->unk14 = *(u16 *)(c + 0xA);
            arg0->unk1C = *(u16 *)(c + 0x14);
            arg0->unk18 = 0;
            if (*(u16 *)(c + 8) == 0x555) {
                arg0->unk18 = 1;
                arg0->unk20 = 0x20;
            } else {
                arg0->unk20 = 1;
                arg0->unk1C = *(u16 *)(c + 0x14);
            }
        } else if (memcmp(p, D_0045AC70, 4) == 0) {
            arg0->unk4 = *(s32 *)(p + 4);
            arg0->unk0 = (p + 8) - arg1;
            break;
        } else if (memcmp(p, D_0045AC78, 4) == 0) {
            c = p;
            size = *(s32 *)(c + 4);
            buf = arg0->unk78;
            data = c + 8;
            p = data + size;
            if (buf != 0) {
                *(Big1bc *)buf = *(Big1bc *)c;
            }
        } else if (memcmp(p, D_0045AC80, 4) == 0) {
            size = *(s32 *)(p + 4);
            data = p + 8;
            p = data + size;
        } else if (memcmp(p, D_0045AC88, 4) == 0) {
            size = *(s32 *)(p + 4);
            data = p + 8;
            arg0->unk24 = p[8];
            if (arg2 != 0) {
                arg0->unk24 = 1;
            }
            arg0->unk28 = *(s32 *)(p + 0xC) / arg0->unk20;
            arg0->unk2C = *(s32 *)(p + 0xC) - arg0->unk28 * arg0->unk20;
            arg0->unk34 = arg0->unk28 * arg0->unk1C;
            arg0->unk30 = 0;
            arg0->unk50 = 0;
            f = *(f32 *)(p + 0x10);
            p = data + size;
            arg0->unkCC = f;
        } else {
            size = *(s32 *)(p + 4);
            data = p + 8;
            p = data + size;
        }
    }
    arg0->unk58 = arg0->unk4 / arg0->unk1C;
    return 1;
}
