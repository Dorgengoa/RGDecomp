#include "types.h"

/* MAIN CameraObjAssign_2f72a0 -- assignment operator shape: the +0xC0 table
   pointer is installed TWICE (base then derived) with the field copy
   in between.  Two 64-byte members (at 0x10 and 0x80) are struct
   assignments and come out as mwcc's 8-bytes-per-iteration block-copy
   loop; the 16-byte float members are batched lwc1 x4 / swc1 x4. */

typedef struct V4 { f32 x, y, z, w; } V4;
typedef struct B64 { u32 w[16]; } B64;

extern u8 D_00470090[];
extern u8 D_00470340[];

u8 *CameraObjAssign_2f72a0(u8 *d, u8 *s)
{
    *(u8 **)(d + 0xC0) = D_00470090;
    *(f32 *)(d + 0x00) = *(f32 *)(s + 0x00);
    *(B64 *)(d + 0x10) = *(B64 *)(s + 0x10);
    *(V4 *)(d + 0x50) = *(V4 *)(s + 0x50);
    *(V4 *)(d + 0x60) = *(V4 *)(s + 0x60);
    *(f32 *)(d + 0x70) = *(f32 *)(s + 0x70);
    *(B64 *)(d + 0x80) = *(B64 *)(s + 0x80);
    *(u8 **)(d + 0xC0) = D_00470340;
    *(V4 *)(d + 0xD0) = *(V4 *)(s + 0xD0);
    *(V4 *)(d + 0xE0) = *(V4 *)(s + 0xE0);
    *(V4 *)(d + 0xF0) = *(V4 *)(s + 0xF0);
    *(f32 *)(d + 0x100) = *(f32 *)(s + 0x100);
    *(f32 *)(d + 0x104) = *(f32 *)(s + 0x104);
    *(s32 *)(d + 0x108) = *(s32 *)(s + 0x108);
    *(s32 *)(d + 0x10C) = *(s32 *)(s + 0x10C);
    *(s32 *)(d + 0x110) = *(s32 *)(s + 0x110);
    *(V4 *)(d + 0x120) = *(V4 *)(s + 0x120);
    *(f32 *)(d + 0x130) = *(f32 *)(s + 0x130);
    *(f32 *)(d + 0x134) = *(f32 *)(s + 0x134);
    *(f32 *)(d + 0x138) = *(f32 *)(s + 0x138);
    *(f32 *)(d + 0x13C) = *(f32 *)(s + 0x13C);
    *(f32 *)(d + 0x140) = *(f32 *)(s + 0x140);
    *(f32 *)(d + 0x144) = *(f32 *)(s + 0x144);
    *(f32 *)(d + 0x148) = *(f32 *)(s + 0x148);
    *(f32 *)(d + 0x14C) = *(f32 *)(s + 0x14C);
    *(f32 *)(d + 0x150) = *(f32 *)(s + 0x150);
    *(f32 *)(d + 0x154) = *(f32 *)(s + 0x154);
    *(s32 *)(d + 0x158) = *(s32 *)(s + 0x158);
    *(f32 *)(d + 0x15C) = *(f32 *)(s + 0x15C);
    *(f32 *)(d + 0x160) = *(f32 *)(s + 0x160);
    *(f32 *)(d + 0x164) = *(f32 *)(s + 0x164);
    *(f32 *)(d + 0x168) = *(f32 *)(s + 0x168);
    *(f32 *)(d + 0x16C) = *(f32 *)(s + 0x16C);
    *(f32 *)(d + 0x170) = *(f32 *)(s + 0x170);
    *(f32 *)(d + 0x174) = *(f32 *)(s + 0x174);
    *(f32 *)(d + 0x178) = *(f32 *)(s + 0x178);
    *(f32 *)(d + 0x17C) = *(f32 *)(s + 0x17C);
    *(f32 *)(d + 0x180) = *(f32 *)(s + 0x180);
    *(s32 *)(d + 0x184) = *(s32 *)(s + 0x184);
    return d;
}
