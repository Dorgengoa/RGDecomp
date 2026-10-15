#include "types.h"

/* Clone pair with MenuPartyMemberStatValues_29edc0 (same normalized opcode stream, different
   registers/offsets) -- found via the s44b clone census. Identical to
   MenuPartyMemberStatValues_29edc0 in every respect except `self`'s pointer field sits at
   offset 0x0 here instead of 0x4C4 (confirmed by diffing the two .s
   listings -- the only non-address/non-label difference is
   `lw $4, 0x0($21)` vs `lw $4, 0x4C4($21)`). See MenuPartyMemberStatValues_29edc0.cpp for the
   full derivation.

   Sibling of the already-matched MenuItemUseTargetMemberGaugesRefresh_2a2800 (retail address
   MenuItemUseTargetMemberStatValues_2a25c0 + 0x240, right next door, same TU: same class V vtable,
   same helper calls GetGameData_1fede0/PartyCountMembers_3c2010/PartyGetMemberChara_3c2420). MenuItemUseTargetMemberGaugesRefresh_2a2800
   computes float ratios into a 3-slot `E` struct; this function instead
   stores six RAW (sign-extended s32->s64) vtable results plus two s16
   "kind"/"flag" tag words into a 6-slot record fetched through
   UiGetWidgetSubItem_28f2b0(self->unk0, id, 0) (that helper's own file,
   src/s31a/UiGetWidgetSubItem_28f2b0.c, already establishes it returns &array[idx]
   into a 0x20-byte-strided array -- our record is just a richer view of
   the same element).

   Loop 1 (fixed 3 iterations) zeroes the "kind"/"flag" tag pair of all
   six slots for ids [base, base+1, base+2]. Loop 2 (0..n, n from
   PartyCountMembers_3c2010) fills all six slots' value + tag pair from six distinct
   vtable calls on the object returned by PartyGetMemberChara_3c2420.

   RESIDUE: 21/144 words, exact length, and it is PURE REGISTER PERMUTATION
   -- every mismatched word is the same instruction with a different
   register field, never a different opcode/immediate. The four
   long-lived cross-call locals `r`/`n`/`base`/`o` want retail's
   {r:$22, o:$18, n:$19, base:$17}; this draft colours them
   {r:$17, base:$18, o:$19, n:$22} -- a clean 4-cycle rotation. `i`/`j`/`e`
   already land on retail's $16/$20/$16.

   Tried (all inert or worse, same 21-bad object unless noted):
     - reordering the DECLARATIONS of r/n/base amongst each other (no
       change at all -- confirms decl order is normalised away for the
       first-defined trio, matching the "C++ throws away the point of
       declaration" finding in mwcc-callee-saved-creation-order.md)
     - moving the `base = (u16)arg1;` STATEMENT before/after the
       PartyCountMembers_3c2010 call (no change -- independent pure expressions get
       rescheduled by the allocator regardless of source position)
     - moving `o`'s (and `e`'s) declaration earlier in the list, ahead of
       r/n/base: this one is NOT inert -- it also perturbs `j`'s register
       (24 bad, worse) -- so decl position does matter once it crosses
       `o`, just not among r/n/base themselves
     - splitting the shared `e` into two distinct per-loop locals
       (matching m2c's own temp_2_2/temp_2_3 split) -- byte-for-byte the
       same 21-bad object
   None of these separate r/n/base from o's placement, and o must stay
   declared after i/j or the (already-correct) i/j/e colouring breaks.
   This reads as the "pure register PERMUTATION, no front-end input left
   to turn" class from the s58 note in mwcc-callee-saved-creation-order.md
   -- parking it here rather than continuing to guess spellings. */

typedef struct Self002a25c0 {
    void *unk0;
} Self002a25c0;

typedef struct Res002a25c0 {
    u8 pad000[0x18];
    void *unk18;
} Res002a25c0;

typedef struct Rec002a25c0 {
    u8 pad000[0x08];
    s64 unk08;
    u8 pad010[0x06];
    s16 unk16;
    s16 unk18;
    u8 pad01A[0x0E];
    s64 unk28;
    u8 pad030[0x06];
    s16 unk36;
    s16 unk38;
    u8 pad03A[0x0E];
    s64 unk48;
    u8 pad050[0x06];
    s16 unk56;
    s16 unk58;
    u8 pad05A[0x0E];
    s64 unk68;
    u8 pad070[0x06];
    s16 unk76;
    s16 unk78;
    u8 pad07A[0x0E];
    s64 unk88;
    u8 pad090[0x06];
    s16 unk96;
    s16 unk98;
    u8 pad09A[0x0E];
    s64 unkA8;
    u8 pad0B0[0x06];
    s16 unkB6;
    s16 unkB8;
} Rec002a25c0;

class V002a25c0 {
public:
    /* +0x008 */ virtual void slot008();
    /* +0x00C */ virtual void slot00C();
    /* +0x010 */ virtual void slot010();
    /* +0x014 */ virtual void slot014();
    /* +0x018 */ virtual void slot018();
    /* +0x01C */ virtual void slot01C();
    /* +0x020 */ virtual void slot020();
    /* +0x024 */ virtual void slot024();
    /* +0x028 */ virtual void slot028();
    /* +0x02C */ virtual void slot02C();
    /* +0x030 */ virtual void slot030();
    /* +0x034 */ virtual void slot034();
    /* +0x038 */ virtual void slot038();
    /* +0x03C */ virtual void slot03C();
    /* +0x040 */ virtual void slot040();
    /* +0x044 */ virtual void slot044();
    /* +0x048 */ virtual void slot048();
    /* +0x04C */ virtual void slot04C();
    /* +0x050 */ virtual void slot050();
    /* +0x054 */ virtual void slot054();
    /* +0x058 */ virtual void slot058();
    /* +0x05C */ virtual void slot05C();
    /* +0x060 */ virtual void slot060();
    /* +0x064 */ virtual void slot064();
    /* +0x068 */ virtual void slot068();
    /* +0x06C */ virtual void slot06C();
    /* +0x070 */ virtual void slot070();
    /* +0x074 */ virtual void slot074();
    /* +0x078 */ virtual void slot078();
    /* +0x07C */ virtual void slot07C();
    /* +0x080 */ virtual void slot080();
    /* +0x084 */ virtual void slot084();
    /* +0x088 */ virtual void slot088();
    /* +0x08C */ virtual void slot08C();
    /* +0x090 */ virtual void slot090();
    /* +0x094 */ virtual void slot094();
    /* +0x098 */ virtual void slot098();
    /* +0x09C */ virtual void slot09C();
    /* +0x0A0 */ virtual void slot0A0();
    /* +0x0A4 */ virtual void slot0A4();
    /* +0x0A8 */ virtual void slot0A8();
    /* +0x0AC */ virtual void slot0AC();
    /* +0x0B0 */ virtual void slot0B0();
    /* +0x0B4 */ virtual void slot0B4();
    /* +0x0B8 */ virtual void slot0B8();
    /* +0x0BC */ virtual void slot0BC();
    /* +0x0C0 */ virtual void slot0C0();
    /* +0x0C4 */ virtual void slot0C4();
    /* +0x0C8 */ virtual void slot0C8();
    /* +0x0CC */ virtual void slot0CC();
    /* +0x0D0 */ virtual void slot0D0();
    /* +0x0D4 */ virtual void slot0D4();
    /* +0x0D8 */ virtual void slot0D8();
    /* +0x0DC */ virtual void slot0DC();
    /* +0x0E0 */ virtual void slot0E0();
    /* +0x0E4 */ virtual void slot0E4();
    /* +0x0E8 */ virtual s32 slot0E8();
    /* +0x0EC */ virtual void slot0EC();
    /* +0x0F0 */ virtual s32 slot0F0();
    /* +0x0F4 */ virtual void slot0F4();
    /* +0x0F8 */ virtual void slot0F8();
    /* +0x0FC */ virtual void slot0FC();
    /* +0x100 */ virtual void slot100();
    /* +0x104 */ virtual void slot104();
    /* +0x108 */ virtual void slot108();
    /* +0x10C */ virtual s32 slot10C();
    /* +0x110 */ virtual void slot110();
    /* +0x114 */ virtual void slot114();
    /* +0x118 */ virtual void slot118();
    /* +0x11C */ virtual void slot11C();
    /* +0x120 */ virtual void slot120();
    /* +0x124 */ virtual void slot124();
    /* +0x128 */ virtual s32 slot128(s32 a);
    /* +0x12C */ virtual void slot12C();
    /* +0x130 */ virtual s32 slot130(s32 a);
    /* +0x134 */ virtual void slot134();
    /* +0x138 */ virtual void slot138();
    /* +0x13C */ virtual void slot13C();
    /* +0x140 */ virtual void slot140();
    /* +0x144 */ virtual void slot144();
    /* +0x148 */ virtual void slot148();
    /* +0x14C */ virtual void slot14C();
    /* +0x150 */ virtual void slot150();
    /* +0x154 */ virtual void slot154();
    /* +0x158 */ virtual void slot158();
    /* +0x15C */ virtual void slot15C();
    /* +0x160 */ virtual void slot160();
    /* +0x164 */ virtual void slot164();
    /* +0x168 */ virtual void slot168();
    /* +0x16C */ virtual void slot16C();
    /* +0x170 */ virtual void slot170();
    /* +0x174 */ virtual void slot174();
    /* +0x178 */ virtual void slot178();
    /* +0x17C */ virtual void slot17C();
    /* +0x180 */ virtual void slot180();
    /* +0x184 */ virtual void slot184();
    /* +0x188 */ virtual void slot188();
    /* +0x18C */ virtual void slot18C();
    /* +0x190 */ virtual void slot190();
    /* +0x194 */ virtual void slot194();
    /* +0x198 */ virtual void slot198();
    /* +0x19C */ virtual void slot19C();
    /* +0x1A0 */ virtual void slot1A0();
    /* +0x1A4 */ virtual void slot1A4();
    /* +0x1A8 */ virtual void slot1A8();
    /* +0x1AC */ virtual void slot1AC();
    /* +0x1B0 */ virtual void slot1B0();
    /* +0x1B4 */ virtual void slot1B4();
    /* +0x1B8 */ virtual void slot1B8();
    /* +0x1BC */ virtual void slot1BC();
    /* +0x1C0 */ virtual void slot1C0();
    /* +0x1C4 */ virtual void slot1C4();
    /* +0x1C8 */ virtual void slot1C8();
    /* +0x1CC */ virtual void slot1CC();
    /* +0x1D0 */ virtual void slot1D0();
    /* +0x1D4 */ virtual void slot1D4();
    /* +0x1D8 */ virtual void slot1D8();
    /* +0x1DC */ virtual void slot1DC();
    /* +0x1E0 */ virtual void slot1E0();
    /* +0x1E4 */ virtual void slot1E4();
    /* +0x1E8 */ virtual void slot1E8();
    /* +0x1EC */ virtual void slot1EC();
    /* +0x1F0 */ virtual void slot1F0();
    /* +0x1F4 */ virtual void slot1F4();
    /* +0x1F8 */ virtual void slot1F8();
    /* +0x1FC */ virtual void slot1FC();
    /* +0x200 */ virtual void slot200();
    /* +0x204 */ virtual void slot204();
    /* +0x208 */ virtual void slot208();
    /* +0x20C */ virtual void slot20C();
    /* +0x210 */ virtual void slot210();
    /* +0x214 */ virtual void slot214();
    /* +0x218 */ virtual void slot218();
    /* +0x21C */ virtual void slot21C();
    /* +0x220 */ virtual void slot220();
    /* +0x224 */ virtual void slot224();
    /* +0x228 */ virtual void slot228();
    /* +0x22C */ virtual void slot22C();
    /* +0x230 */ virtual void slot230();
    /* +0x234 */ virtual void slot234();
    /* +0x238 */ virtual void slot238();
    /* +0x23C */ virtual void slot23C();
    /* +0x240 */ virtual void slot240();
    /* +0x244 */ virtual void slot244();
    /* +0x248 */ virtual void slot248();
    /* +0x24C */ virtual void slot24C();
    /* +0x250 */ virtual void slot250();
    /* +0x254 */ virtual void slot254();
    /* +0x258 */ virtual void slot258();
    /* +0x25C */ virtual void slot25C();
    /* +0x260 */ virtual void slot260();
    /* +0x264 */ virtual void slot264();
    /* +0x268 */ virtual void slot268();
    /* +0x26C */ virtual void slot26C();
    /* +0x270 */ virtual void slot270();
    /* +0x274 */ virtual void slot274();
    /* +0x278 */ virtual void slot278();
    /* +0x27C */ virtual void slot27C();
    /* +0x280 */ virtual void slot280();
    /* +0x284 */ virtual void slot284();
    /* +0x288 */ virtual void slot288();
    /* +0x28C */ virtual void slot28C();
    /* +0x290 */ virtual void slot290();
    /* +0x294 */ virtual void slot294();
    /* +0x298 */ virtual void slot298();
    /* +0x29C */ virtual void slot29C();
    /* +0x2A0 */ virtual void slot2A0();
    /* +0x2A4 */ virtual void slot2A4();
    /* +0x2A8 */ virtual void slot2A8();
    /* +0x2AC */ virtual void slot2AC();
    /* +0x2B0 */ virtual void slot2B0();
    /* +0x2B4 */ virtual void slot2B4();
    /* +0x2B8 */ virtual void slot2B8();
    /* +0x2BC */ virtual void slot2BC();
    /* +0x2C0 */ virtual void slot2C0();
    /* +0x2C4 */ virtual void slot2C4();
    /* +0x2C8 */ virtual void slot2C8();
    /* +0x2CC */ virtual void slot2CC();
    /* +0x2D0 */ virtual void slot2D0();
    /* +0x2D4 */ virtual void slot2D4();
    /* +0x2D8 */ virtual void slot2D8();
    /* +0x2DC */ virtual void slot2DC();
    /* +0x2E0 */ virtual void slot2E0();
    /* +0x2E4 */ virtual void slot2E4();
    /* +0x2E8 */ virtual void slot2E8();
    /* +0x2EC */ virtual void slot2EC();
    /* +0x2F0 */ virtual void slot2F0();
    /* +0x2F4 */ virtual void slot2F4();
    /* +0x2F8 */ virtual void slot2F8();
    /* +0x2FC */ virtual void slot2FC();
    /* +0x300 */ virtual void slot300();
    /* +0x304 */ virtual void slot304();
    /* +0x308 */ virtual void slot308();
    /* +0x30C */ virtual void slot30C();
    /* +0x310 */ virtual void slot310();
    /* +0x314 */ virtual void slot314();
    /* +0x318 */ virtual void slot318();
    /* +0x31C */ virtual void slot31C();
    /* +0x320 */ virtual void slot320();
    /* +0x324 */ virtual void slot324();
    /* +0x328 */ virtual void slot328();
    /* +0x32C */ virtual void slot32C();
    /* +0x330 */ virtual void slot330();
    /* +0x334 */ virtual void slot334();
    /* +0x338 */ virtual void slot338();
    /* +0x33C */ virtual void slot33C();
    /* +0x340 */ virtual void slot340();
    /* +0x344 */ virtual void slot344();
    /* +0x348 */ virtual void slot348();
    /* +0x34C */ virtual void slot34C();
    /* +0x350 */ virtual void slot350();
    /* +0x354 */ virtual void slot354();
    /* +0x358 */ virtual void slot358();
    /* +0x35C */ virtual void slot35C();
    /* +0x360 */ virtual void slot360();
    /* +0x364 */ virtual void slot364();
    /* +0x368 */ virtual void slot368();
    /* +0x36C */ virtual void slot36C();
    /* +0x370 */ virtual void slot370();
    /* +0x374 */ virtual void slot374();
    /* +0x378 */ virtual void slot378();
    /* +0x37C */ virtual void slot37C();
    /* +0x380 */ virtual void slot380();
    /* +0x384 */ virtual void slot384();
    /* +0x388 */ virtual void slot388();
    /* +0x38C */ virtual void slot38C();
    /* +0x390 */ virtual void slot390();
    /* +0x394 */ virtual void slot394();
    /* +0x398 */ virtual void slot398();
    /* +0x39C */ virtual void slot39C();
    /* +0x3A0 */ virtual void slot3A0();
    /* +0x3A4 */ virtual void slot3A4();
    /* +0x3A8 */ virtual void slot3A8();
    /* +0x3AC */ virtual void slot3AC();
    /* +0x3B0 */ virtual void slot3B0();
    /* +0x3B4 */ virtual void slot3B4();
    /* +0x3B8 */ virtual void slot3B8();
    /* +0x3BC */ virtual void slot3BC();
    /* +0x3C0 */ virtual void slot3C0();
    /* +0x3C4 */ virtual void slot3C4();
    /* +0x3C8 */ virtual void slot3C8();
    /* +0x3CC */ virtual void slot3CC();
    /* +0x3D0 */ virtual void slot3D0();
    /* +0x3D4 */ virtual void slot3D4();
    /* +0x3D8 */ virtual void slot3D8();
    /* +0x3DC */ virtual void slot3DC();
    /* +0x3E0 */ virtual void slot3E0();
    /* +0x3E4 */ virtual void slot3E4();
    /* +0x3E8 */ virtual void slot3E8();
    /* +0x3EC */ virtual void slot3EC();
    /* +0x3F0 */ virtual void slot3F0();
    /* +0x3F4 */ virtual void slot3F4();
    /* +0x3F8 */ virtual void slot3F8();
    /* +0x3FC */ virtual void slot3FC();
    /* +0x400 */ virtual void slot400();
    /* +0x404 */ virtual void slot404();
    /* +0x408 */ virtual void slot408();
    /* +0x40C */ virtual void slot40C();
    /* +0x410 */ virtual void slot410();
    /* +0x414 */ virtual void slot414();
    /* +0x418 */ virtual void slot418();
    /* +0x41C */ virtual void slot41C();
    /* +0x420 */ virtual s32 slot420();
};

extern "C" Res002a25c0 *GetGameData_1fede0();
extern "C" s32 PartyCountMembers_3c2010(void *, s32, s32);
extern "C" Rec002a25c0 *UiGetWidgetSubItem_28f2b0(void *, u16, s32);
extern "C" V002a25c0 *PartyGetMemberChara_3c2420(void *, s32);

extern "C" s32 MenuItemUseTargetMemberStatValues_2a25c0(Self002a25c0 *self, s32 arg1)
{
    u32 j;
    s32 n;
    u16 base;
    s32 i;
    Res002a25c0 *r;
    Rec002a25c0 *e;
    V002a25c0 *o;

    r = GetGameData_1fede0();
    n = PartyCountMembers_3c2010(r->unk18, 1, 1);
    base = (u16)arg1;
    for (i = 0; i < 3; i++) {
        e = UiGetWidgetSubItem_28f2b0(self->unk0, (u16)(base + i), 0);
        if (e == 0) {
            return 0;
        }
        e->unk18 = 0;
        e->unk16 = 0;
        e->unk38 = 0;
        e->unk36 = 0;
        e->unk58 = 0;
        e->unk56 = 0;
        e->unk78 = 0;
        e->unk76 = 0;
        e->unk98 = 0;
        e->unk96 = 0;
        e->unkB8 = 0;
        e->unkB6 = 0;
    }
    for (j = 0; (s32)j < (s32)n; j++) {
        e = UiGetWidgetSubItem_28f2b0(self->unk0, (u16)(base + j), 0);
        if (e == 0) {
            return 0;
        }
        o = PartyGetMemberChara_3c2420(r->unk18, j);
        if (o == 0) {
            return 0;
        }

        e->unk08 = (s64)o->slot0F0();
        e->unk16 = 0xC;
        e->unk18 = 0xF;

        e->unk28 = (s64)o->slot10C();
        e->unk36 = 0xC;
        e->unk38 = 0xF;

        e->unk48 = (s64)o->slot420();
        e->unk56 = 0xC;
        e->unk58 = 0xF;

        e->unk68 = (s64)o->slot0E8();
        e->unk76 = 0xC;
        e->unk78 = 0xF;

        e->unk88 = (s64)o->slot128(1);
        e->unk96 = 0xA;
        e->unk98 = 0xC;

        e->unkA8 = (s64)o->slot130(1);
        e->unkB6 = 0xA;
        e->unkB8 = 0xC;
    }
    return 1;
}
