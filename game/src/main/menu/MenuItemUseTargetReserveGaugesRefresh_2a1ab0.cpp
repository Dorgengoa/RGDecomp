#include "types.h"

/* MenuItemUseTargetReserveGaugesRefresh_2a1ab0 -- sibling of MenuPartyReserveGaugesRefresh_29e4e0 (see that file's header comment
   for the full mechanism writeup; this file only notes the two literal
   differences measured between the two retail listings).

   Difference 1: self->m4C4 there is self's OWN first field here (offset
   0, not 0x4C4) -- `struct Self` below has no leading pad.
   Difference 2: the three s16[0x15] source tables are the SAME array's
   next row, each address +0x600 from MenuPartyReserveGaugesRefresh_29e4e0's: D_00450EF0 (was
   D_004508F0), D_00450F20 (was D_00450920), D_00450F50 (was D_00450950).
   Every other byte of the two retail listings is identical (glabel and
   local .L labels aside) -- confirmed with a normalized diff before
   drafting either file, so the body below is a straight clone. */

extern "C" {
extern void *GetGameData_1fede0(void);
extern s32 PartyCountReserve_3c1c20(s32, s32, s32);
extern void *UiGetWidgetSprite_28fe10(s32, s32, s32);
extern void *UiSetSpriteUvSize_28f890(s32, s32, s32, s32, s32);
extern void *UiSetSubItemGlyphUvSize_28f100(s32, s32, s32, s32, s32);
extern void *UiSetWidgetSubItemValue_291250(s32, s32, s32, s64);
extern void *UiGetWidgetSubItem_28f2b0(s32, s32, s32);

extern s16 D_00450EF0[0x15];
extern s16 D_00450F20[0x15];
extern s16 D_00450F50[0x15];
extern void *PartyGetReserveChara_3c1d20(s32 p0, s32 p1);
}

struct Self {
    s32 m4C4;   /* at offset 0 in this sibling, vs 0x4C4 in MenuPartyReserveGaugesRefresh_29e4e0 */
};

struct Top {
    u8 pad18[0x18];
    s32 m18;
};

typedef struct Group {
    s16 f0;
    u8  pad02[2];
    s16 f4;
    u8  pad06[6];
    s16 fC;
    u8  pad0E[0x12];
} Group; /* 0x20 bytes */

typedef struct Item {
    Group g[3];
    s16 f60;
} Item;

class Rec {
public:
    /* vtbl +0x8 */ VC_VPTR_MEMBER;
    /* vtbl +0xC */ 
    /* vtbl +0x10 */ 
    /* vtbl +0x14 */ 
    /* vtbl +0x18 */ 
    /* vtbl +0x1C */ 
    /* vtbl +0x20 */ 
    /* vtbl +0x24 */ 
    /* vtbl +0x28 */ 
    /* vtbl +0x2C */ 
    /* vtbl +0x30 */ 
    /* vtbl +0x34 */ 
    /* vtbl +0x38 */ 
    /* vtbl +0x3C */ 
    /* vtbl +0x40 */ 
    /* vtbl +0x44 */ 
    /* vtbl +0x48 */ 
    /* vtbl +0x4C */ 
    /* vtbl +0x50 */ 
    /* vtbl +0x54 */ 
    /* vtbl +0x58 */ 
    /* vtbl +0x5C */ 
    /* vtbl +0x60 */ 
    /* vtbl +0x64 */ 
    /* vtbl +0x68 */ 
    /* vtbl +0x6C */ 
    /* vtbl +0x70 */ 
    /* vtbl +0x74 */ 
    /* vtbl +0x78 */ 
    /* vtbl +0x7C */ 
    /* vtbl +0x80 */ 
    /* vtbl +0x84 */ 
    /* vtbl +0x88 */ 
    /* vtbl +0x8C */ 
    /* vtbl +0x90 */ 
    /* vtbl +0x94 */ 
    /* vtbl +0x98 */ 
    /* vtbl +0x9C */ 
    /* vtbl +0xA0 */ 
    /* vtbl +0xA4 */ 
    /* vtbl +0xA8 */ 
    /* vtbl +0xAC */ 
    /* vtbl +0xB0 */ 
    /* vtbl +0xB4 */ 
    /* vtbl +0xB8 */ 
    /* vtbl +0xBC */ 
    /* vtbl +0xC0 */ 
    /* vtbl +0xC4 */ 
    /* vtbl +0xC8 */ 
    /* vtbl +0xCC */ 
    /* vtbl +0xD0 */ 
    /* vtbl +0xD4 */ 
    /* vtbl +0xD8 */ 
    /* vtbl +0xDC */ 
    /* vtbl +0xE0 */ 
    /* vtbl +0xE4 */ 
    /* vtbl +0xE8 */ s32 slotE8() { return VCM0(s32, 0xE8); }
    /* vtbl +0xEC */ 
    /* vtbl +0xF0 */ s32 slotF0() { return VCM0(s32, 0xF0); }
    /* vtbl +0xF4 */ 
    /* vtbl +0xF8 */ 
    /* vtbl +0xFC */ 
    /* vtbl +0x100 */ 
    /* vtbl +0x104 */ 
    /* vtbl +0x108 */ 
    /* vtbl +0x10C */ s32 slot10C() { return VCM0(s32, 0x10C); }
    /* vtbl +0x110 */ 
    /* vtbl +0x114 */ 
    /* vtbl +0x118 */ 
    /* vtbl +0x11C */ 
    /* vtbl +0x120 */ 
    /* vtbl +0x124 */ 
    /* vtbl +0x128 */ s32 slot128(s32 a) { return VCM(s32, (void *, s32), 0x128, a); }
    /* vtbl +0x12C */ 
    /* vtbl +0x130 */ s32 slot130(s32 a) { return VCM(s32, (void *, s32), 0x130, a); }
    /* vtbl +0x134 */ 
    /* vtbl +0x138 */ 
    /* vtbl +0x13C */ 
    /* vtbl +0x140 */ 
    /* vtbl +0x144 */ 
    /* vtbl +0x148 */ 
    /* vtbl +0x14C */ 
    /* vtbl +0x150 */ 
    /* vtbl +0x154 */ 
    /* vtbl +0x158 */ 
    /* vtbl +0x15C */ 
    /* vtbl +0x160 */ 
    /* vtbl +0x164 */ 
    /* vtbl +0x168 */ 
    /* vtbl +0x16C */ 
    /* vtbl +0x170 */ 
    /* vtbl +0x174 */ 
    /* vtbl +0x178 */ 
    /* vtbl +0x17C */ 
    /* vtbl +0x180 */ 
    /* vtbl +0x184 */ 
    /* vtbl +0x188 */ 
    /* vtbl +0x18C */ 
    /* vtbl +0x190 */ 
    /* vtbl +0x194 */ 
    /* vtbl +0x198 */ 
    /* vtbl +0x19C */ 
    /* vtbl +0x1A0 */ 
    /* vtbl +0x1A4 */ 
    /* vtbl +0x1A8 */ 
    /* vtbl +0x1AC */ 
    /* vtbl +0x1B0 */ 
    /* vtbl +0x1B4 */ 
    /* vtbl +0x1B8 */ 
    /* vtbl +0x1BC */ 
    /* vtbl +0x1C0 */ 
    /* vtbl +0x1C4 */ 
    /* vtbl +0x1C8 */ 
    /* vtbl +0x1CC */ 
    /* vtbl +0x1D0 */ 
    /* vtbl +0x1D4 */ 
    /* vtbl +0x1D8 */ 
    /* vtbl +0x1DC */ 
    /* vtbl +0x1E0 */ 
    /* vtbl +0x1E4 */ 
    /* vtbl +0x1E8 */ 
    /* vtbl +0x1EC */ 
    /* vtbl +0x1F0 */ 
    /* vtbl +0x1F4 */ 
    /* vtbl +0x1F8 */ 
    /* vtbl +0x1FC */ 
    /* vtbl +0x200 */ 
    /* vtbl +0x204 */ 
    /* vtbl +0x208 */ 
    /* vtbl +0x20C */ 
    /* vtbl +0x210 */ 
    /* vtbl +0x214 */ 
    /* vtbl +0x218 */ 
    /* vtbl +0x21C */ 
    /* vtbl +0x220 */ 
    /* vtbl +0x224 */ 
    /* vtbl +0x228 */ 
    /* vtbl +0x22C */ 
    /* vtbl +0x230 */ 
    /* vtbl +0x234 */ 
    /* vtbl +0x238 */ 
    /* vtbl +0x23C */ 
    /* vtbl +0x240 */ 
    /* vtbl +0x244 */ 
    /* vtbl +0x248 */ 
    /* vtbl +0x24C */ 
    /* vtbl +0x250 */ 
    /* vtbl +0x254 */ 
    /* vtbl +0x258 */ 
    /* vtbl +0x25C */ 
    /* vtbl +0x260 */ 
    /* vtbl +0x264 */ 
    /* vtbl +0x268 */ 
    /* vtbl +0x26C */ 
    /* vtbl +0x270 */ 
    /* vtbl +0x274 */ 
    /* vtbl +0x278 */ 
    /* vtbl +0x27C */ 
    /* vtbl +0x280 */ 
    /* vtbl +0x284 */ 
    /* vtbl +0x288 */ 
    /* vtbl +0x28C */ 
    /* vtbl +0x290 */ 
    /* vtbl +0x294 */ 
    /* vtbl +0x298 */ 
    /* vtbl +0x29C */ 
    /* vtbl +0x2A0 */ 
    /* vtbl +0x2A4 */ 
    /* vtbl +0x2A8 */ 
    /* vtbl +0x2AC */ 
    /* vtbl +0x2B0 */ 
    /* vtbl +0x2B4 */ 
    /* vtbl +0x2B8 */ 
    /* vtbl +0x2BC */ 
    /* vtbl +0x2C0 */ 
    /* vtbl +0x2C4 */ 
    /* vtbl +0x2C8 */ 
    /* vtbl +0x2CC */ 
    /* vtbl +0x2D0 */ 
    /* vtbl +0x2D4 */ 
    /* vtbl +0x2D8 */ 
    /* vtbl +0x2DC */ 
    /* vtbl +0x2E0 */ 
    /* vtbl +0x2E4 */ 
    /* vtbl +0x2E8 */ 
    /* vtbl +0x2EC */ 
    /* vtbl +0x2F0 */ 
    /* vtbl +0x2F4 */ 
    /* vtbl +0x2F8 */ 
    /* vtbl +0x2FC */ 
    /* vtbl +0x300 */ 
    /* vtbl +0x304 */ 
    /* vtbl +0x308 */ 
    /* vtbl +0x30C */ 
    /* vtbl +0x310 */ 
    /* vtbl +0x314 */ 
    /* vtbl +0x318 */ 
    /* vtbl +0x31C */ 
    /* vtbl +0x320 */ 
    /* vtbl +0x324 */ 
    /* vtbl +0x328 */ 
    /* vtbl +0x32C */ 
    /* vtbl +0x330 */ 
    /* vtbl +0x334 */ 
    /* vtbl +0x338 */ 
    /* vtbl +0x33C */ 
    /* vtbl +0x340 */ 
    /* vtbl +0x344 */ 
    /* vtbl +0x348 */ 
    /* vtbl +0x34C */ 
    /* vtbl +0x350 */ 
    /* vtbl +0x354 */ 
    /* vtbl +0x358 */ 
    /* vtbl +0x35C */ 
    /* vtbl +0x360 */ 
    /* vtbl +0x364 */ 
    /* vtbl +0x368 */ 
    /* vtbl +0x36C */ 
    /* vtbl +0x370 */ 
    /* vtbl +0x374 */ 
    /* vtbl +0x378 */ 
    /* vtbl +0x37C */ 
    /* vtbl +0x380 */ 
    /* vtbl +0x384 */ 
    /* vtbl +0x388 */ 
    /* vtbl +0x38C */ 
    /* vtbl +0x390 */ 
    /* vtbl +0x394 */ 
    /* vtbl +0x398 */ 
    /* vtbl +0x39C */ 
    /* vtbl +0x3A0 */ 
    /* vtbl +0x3A4 */ 
    /* vtbl +0x3A8 */ 
    /* vtbl +0x3AC */ 
    /* vtbl +0x3B0 */ 
    /* vtbl +0x3B4 */ 
    /* vtbl +0x3B8 */ 
    /* vtbl +0x3BC */ 
    /* vtbl +0x3C0 */ 
    /* vtbl +0x3C4 */ 
    /* vtbl +0x3C8 */ 
    /* vtbl +0x3CC */ 
    /* vtbl +0x3D0 */ 
    /* vtbl +0x3D4 */ 
    /* vtbl +0x3D8 */ 
    /* vtbl +0x3DC */ 
    /* vtbl +0x3E0 */ 
    /* vtbl +0x3E4 */ 
    /* vtbl +0x3E8 */ 
    /* vtbl +0x3EC */ 
    /* vtbl +0x3F0 */ 
    /* vtbl +0x3F4 */ 
    /* vtbl +0x3F8 */ 
    /* vtbl +0x3FC */ 
    /* vtbl +0x400 */ 
    /* vtbl +0x404 */ 
    /* vtbl +0x408 */ 
    /* vtbl +0x40C */ 
    /* vtbl +0x410 */ 
    /* vtbl +0x414 */ 
    /* vtbl +0x418 */ 
    /* vtbl +0x41C */ 
    /* vtbl +0x420 */ s32 slot420() { return VCM0(s32, 0x420); }
    /* vtbl +0x424 */ 
    /* vtbl +0x428 */ 
    /* vtbl +0x42C */ 
    /* vtbl +0x430 */ 
    /* vtbl +0x434 */ 
    /* vtbl +0x438 */ 
    /* vtbl +0x43C */ 
    /* vtbl +0x440 */ 
    /* vtbl +0x444 */ s32 slot444(s32 a) { return VCM(s32, (void *, s32), 0x444, a); }
};

extern "C" s32 MenuItemUseTargetReserveGaugesRefresh_2a1ab0(Self *self, s32 a1)
{
    f32 stat = 54.0f;
    Top *topObj;
    s32 count;
    s32 n;
    u16 base;
    s32 i, j;
    u16 idx, idx7;
    Item *obj;
    s16 buf1[0x15] __attribute__((aligned(16)));
    s16 buf2[0x15] __attribute__((aligned(16)));
    s16 buf3[0x15] __attribute__((aligned(16)));
    s16 *p1;
    s16 *p2;
    s16 *p3;
    s16 *src, *dst;
    s32 cnt;
    Rec *rec;
    s32 r1;
    f32 fnum1, fnum2, ratio;
    s16 *v;
    s16 *obj2;

    topObj = (Top *)GetGameData_1fede0();
    count = PartyCountReserve_3c1c20(topObj->m18, 1, 1);
    count = (s32)(u32)count;

    n = count - 5;
    if (n <= 0) {
        n = 0;
    }
    if (n == 2) {
        stat -= 8.0f;
    }

    src = D_00450EF0;
    dst = buf1;
    for (cnt = 0x15; cnt > 0; cnt--) {
        *dst = *src;
        src++;
        dst++;
    }
    src = D_00450F20;
    dst = buf2;
    for (cnt = 0x15; cnt > 0; cnt--) {
        *dst = *src;
        src++;
        dst++;
    }
    src = D_00450F50;
    dst = buf3;
    for (cnt = 0x15; cnt > 0; cnt--) {
        *dst = *src;
        src++;
        dst++;
    }

    base = (u16)a1;

    for (i = 0; i < 7; i++) {
        idx = (u16)(base + i);
        obj = (Item *)UiGetWidgetSprite_28fe10(self->m4C4, idx, 0);
        if (obj == 0) {
            return 0;
        }
        obj->g[2].fC = 0;
        obj->g[2].f4 = 0;
        obj->g[1].fC = 0;
        obj->g[1].f4 = 0;
        obj->g[0].fC = 0;
        obj->g[0].f4 = 0;
        obj->f60 = -1;
        idx7 = (u16)((u32)idx + 7);
        UiSetSpriteUvSize_28f890(self->m4C4, idx7, 0, 0, 0);
        UiSetSubItemGlyphUvSize_28f100(self->m4C4, idx7, 0, 0, 0);
    }

    p1 = &buf1[n * 7];
    p2 = &buf2[n * 7];
    p3 = &buf3[n * 7];

    for (j = 0; j < count; j++) {
        idx = (u16)(base + j);
        obj = (Item *)UiGetWidgetSprite_28fe10(self->m4C4, idx, 0);
        if (obj == 0) {
            return 0;
        }

        rec = (Rec *)PartyGetReserveChara_3c1d20(topObj->m18, j);
        if (rec == 0) {
            return 0;
        }

        /* group 0 */
        fnum1 = (f32)rec->slot128(1);
        fnum2 = (f32)rec->slotF0();
        ratio = fnum2 / fnum1;
        obj->g[0].f0 = p1[j];
        obj->g[0].fC = 10;
        obj->g[0].f4 = (s16)(s32)(stat * ratio);
        if (fnum2 > 0.0f && obj->g[0].f4 <= 0) {
            obj->g[0].f4 = 1;
        } else if (ratio <= 0.0f || ratio > 1.0f) {
            obj->g[0].fC = 0;
            obj->g[0].f4 = 0;
        }

        /* group 1 */
        fnum1 = (f32)rec->slot130(1);
        fnum2 = (f32)rec->slot10C();
        ratio = fnum2 / fnum1;
        obj->g[1].f0 = p1[j];
        obj->g[1].fC = 10;
        obj->g[1].f4 = (s16)(s32)(stat * ratio);
        if (fnum2 > 0.0f && obj->g[1].f4 <= 0) {
            obj->g[1].f4 = 1;
        } else if (ratio <= 0.0f || ratio > 1.0f) {
            obj->g[1].fC = 0;
            obj->g[1].f4 = 0;
        }

        /* group 2 -- fnum1 chains through TWO virtuals, not one */
        r1 = rec->slotE8();
        fnum1 = (f32)rec->slot444(r1);
        fnum2 = (f32)rec->slot420();
        ratio = fnum2 / fnum1;
        obj->g[2].f0 = p1[j];
        obj->g[2].fC = 10;
        obj->g[2].f4 = (s16)(s32)(stat * ratio);
        if (fnum2 > 0.0f && obj->g[2].f4 <= 0) {
            obj->g[2].f4 = 1;
        } else if (ratio <= 0.0f || ratio > 1.0f) {
            obj->g[2].fC = 0;
            obj->g[2].f4 = 0;
        }

        idx7 = (u16)((u32)idx + 7);
        UiSetSpriteUvSize_28f890(self->m4C4, idx7, 18, 13, 0);
        UiSetSubItemGlyphUvSize_28f100(self->m4C4, idx7, 12, 15, 0);

        r1 = rec->slotE8();
        UiSetWidgetSubItemValue_291250(self->m4C4, idx7, 0, (s64)r1);

        v = (s16 *)UiGetWidgetSubItem_28f2b0(self->m4C4, idx7, 0);
        if (v == 0) {
            return 0;
        }
        *v = p2[j];

        obj2 = (s16 *)UiGetWidgetSprite_28fe10(self->m4C4, idx7, 0);
        if (obj2 == 0) {
            return 0;
        }
        *obj2 = p3[j];
    }

    return 1;
}
