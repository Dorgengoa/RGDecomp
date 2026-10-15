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
    /* vtbl +0x8 */ virtual void slotPad_8();
    /* vtbl +0xC */ virtual void slotPad_C();
    /* vtbl +0x10 */ virtual void slotPad_10();
    /* vtbl +0x14 */ virtual void slotPad_14();
    /* vtbl +0x18 */ virtual void slotPad_18();
    /* vtbl +0x1C */ virtual void slotPad_1C();
    /* vtbl +0x20 */ virtual void slotPad_20();
    /* vtbl +0x24 */ virtual void slotPad_24();
    /* vtbl +0x28 */ virtual void slotPad_28();
    /* vtbl +0x2C */ virtual void slotPad_2C();
    /* vtbl +0x30 */ virtual void slotPad_30();
    /* vtbl +0x34 */ virtual void slotPad_34();
    /* vtbl +0x38 */ virtual void slotPad_38();
    /* vtbl +0x3C */ virtual void slotPad_3C();
    /* vtbl +0x40 */ virtual void slotPad_40();
    /* vtbl +0x44 */ virtual void slotPad_44();
    /* vtbl +0x48 */ virtual void slotPad_48();
    /* vtbl +0x4C */ virtual void slotPad_4C();
    /* vtbl +0x50 */ virtual void slotPad_50();
    /* vtbl +0x54 */ virtual void slotPad_54();
    /* vtbl +0x58 */ virtual void slotPad_58();
    /* vtbl +0x5C */ virtual void slotPad_5C();
    /* vtbl +0x60 */ virtual void slotPad_60();
    /* vtbl +0x64 */ virtual void slotPad_64();
    /* vtbl +0x68 */ virtual void slotPad_68();
    /* vtbl +0x6C */ virtual void slotPad_6C();
    /* vtbl +0x70 */ virtual void slotPad_70();
    /* vtbl +0x74 */ virtual void slotPad_74();
    /* vtbl +0x78 */ virtual void slotPad_78();
    /* vtbl +0x7C */ virtual void slotPad_7C();
    /* vtbl +0x80 */ virtual void slotPad_80();
    /* vtbl +0x84 */ virtual void slotPad_84();
    /* vtbl +0x88 */ virtual void slotPad_88();
    /* vtbl +0x8C */ virtual void slotPad_8C();
    /* vtbl +0x90 */ virtual void slotPad_90();
    /* vtbl +0x94 */ virtual void slotPad_94();
    /* vtbl +0x98 */ virtual void slotPad_98();
    /* vtbl +0x9C */ virtual void slotPad_9C();
    /* vtbl +0xA0 */ virtual void slotPad_A0();
    /* vtbl +0xA4 */ virtual void slotPad_A4();
    /* vtbl +0xA8 */ virtual void slotPad_A8();
    /* vtbl +0xAC */ virtual void slotPad_AC();
    /* vtbl +0xB0 */ virtual void slotPad_B0();
    /* vtbl +0xB4 */ virtual void slotPad_B4();
    /* vtbl +0xB8 */ virtual void slotPad_B8();
    /* vtbl +0xBC */ virtual void slotPad_BC();
    /* vtbl +0xC0 */ virtual void slotPad_C0();
    /* vtbl +0xC4 */ virtual void slotPad_C4();
    /* vtbl +0xC8 */ virtual void slotPad_C8();
    /* vtbl +0xCC */ virtual void slotPad_CC();
    /* vtbl +0xD0 */ virtual void slotPad_D0();
    /* vtbl +0xD4 */ virtual void slotPad_D4();
    /* vtbl +0xD8 */ virtual void slotPad_D8();
    /* vtbl +0xDC */ virtual void slotPad_DC();
    /* vtbl +0xE0 */ virtual void slotPad_E0();
    /* vtbl +0xE4 */ virtual void slotPad_E4();
    /* vtbl +0xE8 */ virtual s32 slotE8();
    /* vtbl +0xEC */ virtual void slotPad_EC();
    /* vtbl +0xF0 */ virtual s32 slotF0();
    /* vtbl +0xF4 */ virtual void slotPad_F4();
    /* vtbl +0xF8 */ virtual void slotPad_F8();
    /* vtbl +0xFC */ virtual void slotPad_FC();
    /* vtbl +0x100 */ virtual void slotPad_100();
    /* vtbl +0x104 */ virtual void slotPad_104();
    /* vtbl +0x108 */ virtual void slotPad_108();
    /* vtbl +0x10C */ virtual s32 slot10C();
    /* vtbl +0x110 */ virtual void slotPad_110();
    /* vtbl +0x114 */ virtual void slotPad_114();
    /* vtbl +0x118 */ virtual void slotPad_118();
    /* vtbl +0x11C */ virtual void slotPad_11C();
    /* vtbl +0x120 */ virtual void slotPad_120();
    /* vtbl +0x124 */ virtual void slotPad_124();
    /* vtbl +0x128 */ virtual s32 slot128(s32 a);
    /* vtbl +0x12C */ virtual void slotPad_12C();
    /* vtbl +0x130 */ virtual s32 slot130(s32 a);
    /* vtbl +0x134 */ virtual void slotPad_134();
    /* vtbl +0x138 */ virtual void slotPad_138();
    /* vtbl +0x13C */ virtual void slotPad_13C();
    /* vtbl +0x140 */ virtual void slotPad_140();
    /* vtbl +0x144 */ virtual void slotPad_144();
    /* vtbl +0x148 */ virtual void slotPad_148();
    /* vtbl +0x14C */ virtual void slotPad_14C();
    /* vtbl +0x150 */ virtual void slotPad_150();
    /* vtbl +0x154 */ virtual void slotPad_154();
    /* vtbl +0x158 */ virtual void slotPad_158();
    /* vtbl +0x15C */ virtual void slotPad_15C();
    /* vtbl +0x160 */ virtual void slotPad_160();
    /* vtbl +0x164 */ virtual void slotPad_164();
    /* vtbl +0x168 */ virtual void slotPad_168();
    /* vtbl +0x16C */ virtual void slotPad_16C();
    /* vtbl +0x170 */ virtual void slotPad_170();
    /* vtbl +0x174 */ virtual void slotPad_174();
    /* vtbl +0x178 */ virtual void slotPad_178();
    /* vtbl +0x17C */ virtual void slotPad_17C();
    /* vtbl +0x180 */ virtual void slotPad_180();
    /* vtbl +0x184 */ virtual void slotPad_184();
    /* vtbl +0x188 */ virtual void slotPad_188();
    /* vtbl +0x18C */ virtual void slotPad_18C();
    /* vtbl +0x190 */ virtual void slotPad_190();
    /* vtbl +0x194 */ virtual void slotPad_194();
    /* vtbl +0x198 */ virtual void slotPad_198();
    /* vtbl +0x19C */ virtual void slotPad_19C();
    /* vtbl +0x1A0 */ virtual void slotPad_1A0();
    /* vtbl +0x1A4 */ virtual void slotPad_1A4();
    /* vtbl +0x1A8 */ virtual void slotPad_1A8();
    /* vtbl +0x1AC */ virtual void slotPad_1AC();
    /* vtbl +0x1B0 */ virtual void slotPad_1B0();
    /* vtbl +0x1B4 */ virtual void slotPad_1B4();
    /* vtbl +0x1B8 */ virtual void slotPad_1B8();
    /* vtbl +0x1BC */ virtual void slotPad_1BC();
    /* vtbl +0x1C0 */ virtual void slotPad_1C0();
    /* vtbl +0x1C4 */ virtual void slotPad_1C4();
    /* vtbl +0x1C8 */ virtual void slotPad_1C8();
    /* vtbl +0x1CC */ virtual void slotPad_1CC();
    /* vtbl +0x1D0 */ virtual void slotPad_1D0();
    /* vtbl +0x1D4 */ virtual void slotPad_1D4();
    /* vtbl +0x1D8 */ virtual void slotPad_1D8();
    /* vtbl +0x1DC */ virtual void slotPad_1DC();
    /* vtbl +0x1E0 */ virtual void slotPad_1E0();
    /* vtbl +0x1E4 */ virtual void slotPad_1E4();
    /* vtbl +0x1E8 */ virtual void slotPad_1E8();
    /* vtbl +0x1EC */ virtual void slotPad_1EC();
    /* vtbl +0x1F0 */ virtual void slotPad_1F0();
    /* vtbl +0x1F4 */ virtual void slotPad_1F4();
    /* vtbl +0x1F8 */ virtual void slotPad_1F8();
    /* vtbl +0x1FC */ virtual void slotPad_1FC();
    /* vtbl +0x200 */ virtual void slotPad_200();
    /* vtbl +0x204 */ virtual void slotPad_204();
    /* vtbl +0x208 */ virtual void slotPad_208();
    /* vtbl +0x20C */ virtual void slotPad_20C();
    /* vtbl +0x210 */ virtual void slotPad_210();
    /* vtbl +0x214 */ virtual void slotPad_214();
    /* vtbl +0x218 */ virtual void slotPad_218();
    /* vtbl +0x21C */ virtual void slotPad_21C();
    /* vtbl +0x220 */ virtual void slotPad_220();
    /* vtbl +0x224 */ virtual void slotPad_224();
    /* vtbl +0x228 */ virtual void slotPad_228();
    /* vtbl +0x22C */ virtual void slotPad_22C();
    /* vtbl +0x230 */ virtual void slotPad_230();
    /* vtbl +0x234 */ virtual void slotPad_234();
    /* vtbl +0x238 */ virtual void slotPad_238();
    /* vtbl +0x23C */ virtual void slotPad_23C();
    /* vtbl +0x240 */ virtual void slotPad_240();
    /* vtbl +0x244 */ virtual void slotPad_244();
    /* vtbl +0x248 */ virtual void slotPad_248();
    /* vtbl +0x24C */ virtual void slotPad_24C();
    /* vtbl +0x250 */ virtual void slotPad_250();
    /* vtbl +0x254 */ virtual void slotPad_254();
    /* vtbl +0x258 */ virtual void slotPad_258();
    /* vtbl +0x25C */ virtual void slotPad_25C();
    /* vtbl +0x260 */ virtual void slotPad_260();
    /* vtbl +0x264 */ virtual void slotPad_264();
    /* vtbl +0x268 */ virtual void slotPad_268();
    /* vtbl +0x26C */ virtual void slotPad_26C();
    /* vtbl +0x270 */ virtual void slotPad_270();
    /* vtbl +0x274 */ virtual void slotPad_274();
    /* vtbl +0x278 */ virtual void slotPad_278();
    /* vtbl +0x27C */ virtual void slotPad_27C();
    /* vtbl +0x280 */ virtual void slotPad_280();
    /* vtbl +0x284 */ virtual void slotPad_284();
    /* vtbl +0x288 */ virtual void slotPad_288();
    /* vtbl +0x28C */ virtual void slotPad_28C();
    /* vtbl +0x290 */ virtual void slotPad_290();
    /* vtbl +0x294 */ virtual void slotPad_294();
    /* vtbl +0x298 */ virtual void slotPad_298();
    /* vtbl +0x29C */ virtual void slotPad_29C();
    /* vtbl +0x2A0 */ virtual void slotPad_2A0();
    /* vtbl +0x2A4 */ virtual void slotPad_2A4();
    /* vtbl +0x2A8 */ virtual void slotPad_2A8();
    /* vtbl +0x2AC */ virtual void slotPad_2AC();
    /* vtbl +0x2B0 */ virtual void slotPad_2B0();
    /* vtbl +0x2B4 */ virtual void slotPad_2B4();
    /* vtbl +0x2B8 */ virtual void slotPad_2B8();
    /* vtbl +0x2BC */ virtual void slotPad_2BC();
    /* vtbl +0x2C0 */ virtual void slotPad_2C0();
    /* vtbl +0x2C4 */ virtual void slotPad_2C4();
    /* vtbl +0x2C8 */ virtual void slotPad_2C8();
    /* vtbl +0x2CC */ virtual void slotPad_2CC();
    /* vtbl +0x2D0 */ virtual void slotPad_2D0();
    /* vtbl +0x2D4 */ virtual void slotPad_2D4();
    /* vtbl +0x2D8 */ virtual void slotPad_2D8();
    /* vtbl +0x2DC */ virtual void slotPad_2DC();
    /* vtbl +0x2E0 */ virtual void slotPad_2E0();
    /* vtbl +0x2E4 */ virtual void slotPad_2E4();
    /* vtbl +0x2E8 */ virtual void slotPad_2E8();
    /* vtbl +0x2EC */ virtual void slotPad_2EC();
    /* vtbl +0x2F0 */ virtual void slotPad_2F0();
    /* vtbl +0x2F4 */ virtual void slotPad_2F4();
    /* vtbl +0x2F8 */ virtual void slotPad_2F8();
    /* vtbl +0x2FC */ virtual void slotPad_2FC();
    /* vtbl +0x300 */ virtual void slotPad_300();
    /* vtbl +0x304 */ virtual void slotPad_304();
    /* vtbl +0x308 */ virtual void slotPad_308();
    /* vtbl +0x30C */ virtual void slotPad_30C();
    /* vtbl +0x310 */ virtual void slotPad_310();
    /* vtbl +0x314 */ virtual void slotPad_314();
    /* vtbl +0x318 */ virtual void slotPad_318();
    /* vtbl +0x31C */ virtual void slotPad_31C();
    /* vtbl +0x320 */ virtual void slotPad_320();
    /* vtbl +0x324 */ virtual void slotPad_324();
    /* vtbl +0x328 */ virtual void slotPad_328();
    /* vtbl +0x32C */ virtual void slotPad_32C();
    /* vtbl +0x330 */ virtual void slotPad_330();
    /* vtbl +0x334 */ virtual void slotPad_334();
    /* vtbl +0x338 */ virtual void slotPad_338();
    /* vtbl +0x33C */ virtual void slotPad_33C();
    /* vtbl +0x340 */ virtual void slotPad_340();
    /* vtbl +0x344 */ virtual void slotPad_344();
    /* vtbl +0x348 */ virtual void slotPad_348();
    /* vtbl +0x34C */ virtual void slotPad_34C();
    /* vtbl +0x350 */ virtual void slotPad_350();
    /* vtbl +0x354 */ virtual void slotPad_354();
    /* vtbl +0x358 */ virtual void slotPad_358();
    /* vtbl +0x35C */ virtual void slotPad_35C();
    /* vtbl +0x360 */ virtual void slotPad_360();
    /* vtbl +0x364 */ virtual void slotPad_364();
    /* vtbl +0x368 */ virtual void slotPad_368();
    /* vtbl +0x36C */ virtual void slotPad_36C();
    /* vtbl +0x370 */ virtual void slotPad_370();
    /* vtbl +0x374 */ virtual void slotPad_374();
    /* vtbl +0x378 */ virtual void slotPad_378();
    /* vtbl +0x37C */ virtual void slotPad_37C();
    /* vtbl +0x380 */ virtual void slotPad_380();
    /* vtbl +0x384 */ virtual void slotPad_384();
    /* vtbl +0x388 */ virtual void slotPad_388();
    /* vtbl +0x38C */ virtual void slotPad_38C();
    /* vtbl +0x390 */ virtual void slotPad_390();
    /* vtbl +0x394 */ virtual void slotPad_394();
    /* vtbl +0x398 */ virtual void slotPad_398();
    /* vtbl +0x39C */ virtual void slotPad_39C();
    /* vtbl +0x3A0 */ virtual void slotPad_3A0();
    /* vtbl +0x3A4 */ virtual void slotPad_3A4();
    /* vtbl +0x3A8 */ virtual void slotPad_3A8();
    /* vtbl +0x3AC */ virtual void slotPad_3AC();
    /* vtbl +0x3B0 */ virtual void slotPad_3B0();
    /* vtbl +0x3B4 */ virtual void slotPad_3B4();
    /* vtbl +0x3B8 */ virtual void slotPad_3B8();
    /* vtbl +0x3BC */ virtual void slotPad_3BC();
    /* vtbl +0x3C0 */ virtual void slotPad_3C0();
    /* vtbl +0x3C4 */ virtual void slotPad_3C4();
    /* vtbl +0x3C8 */ virtual void slotPad_3C8();
    /* vtbl +0x3CC */ virtual void slotPad_3CC();
    /* vtbl +0x3D0 */ virtual void slotPad_3D0();
    /* vtbl +0x3D4 */ virtual void slotPad_3D4();
    /* vtbl +0x3D8 */ virtual void slotPad_3D8();
    /* vtbl +0x3DC */ virtual void slotPad_3DC();
    /* vtbl +0x3E0 */ virtual void slotPad_3E0();
    /* vtbl +0x3E4 */ virtual void slotPad_3E4();
    /* vtbl +0x3E8 */ virtual void slotPad_3E8();
    /* vtbl +0x3EC */ virtual void slotPad_3EC();
    /* vtbl +0x3F0 */ virtual void slotPad_3F0();
    /* vtbl +0x3F4 */ virtual void slotPad_3F4();
    /* vtbl +0x3F8 */ virtual void slotPad_3F8();
    /* vtbl +0x3FC */ virtual void slotPad_3FC();
    /* vtbl +0x400 */ virtual void slotPad_400();
    /* vtbl +0x404 */ virtual void slotPad_404();
    /* vtbl +0x408 */ virtual void slotPad_408();
    /* vtbl +0x40C */ virtual void slotPad_40C();
    /* vtbl +0x410 */ virtual void slotPad_410();
    /* vtbl +0x414 */ virtual void slotPad_414();
    /* vtbl +0x418 */ virtual void slotPad_418();
    /* vtbl +0x41C */ virtual void slotPad_41C();
    /* vtbl +0x420 */ virtual s32 slot420();
    /* vtbl +0x424 */ virtual void slotPad_424();
    /* vtbl +0x428 */ virtual void slotPad_428();
    /* vtbl +0x42C */ virtual void slotPad_42C();
    /* vtbl +0x430 */ virtual void slotPad_430();
    /* vtbl +0x434 */ virtual void slotPad_434();
    /* vtbl +0x438 */ virtual void slotPad_438();
    /* vtbl +0x43C */ virtual void slotPad_43C();
    /* vtbl +0x440 */ virtual void slotPad_440();
    /* vtbl +0x444 */ virtual s32 slot444(s32 a);
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
    s16 buf1[0x15];
    s16 buf2[0x15];
    s16 buf3[0x15];
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
