#ifndef WORLDOBJ_CPP_H
#define WORLDOBJ_CPP_H

#include "types.h"

/* An entry in the world's object list, as a REAL C++ class -- which is what it
   has to be for EvCmdEventStartMaybe_248450's last loop to match. The loop's body is three
   VIRTUAL calls and retail spells them `lw t9 / lw t9 / jalr t9`; a struct of
   function pointers gives `jalr v0` instead. See the vtable recipe in the
   track note.

   ⚠ The class name and all three method names are INVENTED. What is read off
   the reference is only the shape: the vptr sits at offset +0x00 (so there are
   NO leading data members -- mwcc places the vptr after them, which is why the
   camera's lands at +0xC0 and this one does not), and three slots are used.

   Slot offset is 8 + index*4, so the three used slots are indices 46, 104 and
   173 and every slot below the highest has to be declared, in order, to push
   them to the right offsets. The placeholders carry no meaning. */

class WorldEntity {
public:
    /* +0x008 */ VC_VPTR_MEMBER; void slot008() { VCM0(void, 0x8); }
    /* +0x00C */ void slot00C() { VCM0(void, 0xC); }
    /* +0x010 */ void slot010() { VCM0(void, 0x10); }
    /* +0x014 */ void slot014() { VCM0(void, 0x14); }
    /* +0x018 */ void slot018() { VCM0(void, 0x18); }
    /* +0x01C */ void slot01C() { VCM0(void, 0x1C); }
    /* +0x020 */ void slot020() { VCM0(void, 0x20); }
    /* +0x024 */ void slot024() { VCM0(void, 0x24); }
    /* +0x028 */ void slot028() { VCM0(void, 0x28); }
    /* +0x02C */ void slot02C() { VCM0(void, 0x2C); }
    /* +0x030 */ void slot030() { VCM0(void, 0x30); }
    /* +0x034 */ void slot034() { VCM0(void, 0x34); }
    /* +0x038 */ void slot038() { VCM0(void, 0x38); }
    /* +0x03C */ void slot03C() { VCM0(void, 0x3C); }
    /* +0x040 */ void slot040() { VCM0(void, 0x40); }
    /* +0x044 */ void slot044() { VCM0(void, 0x44); }
    /* +0x048 */ void slot048() { VCM0(void, 0x48); }
    /* +0x04C */ void slot04C() { VCM0(void, 0x4C); }
    /* +0x050 */ void slot050() { VCM0(void, 0x50); }
    /* +0x054 */ void slot054() { VCM0(void, 0x54); }
    /* +0x058 */ void slot058() { VCM0(void, 0x58); }
    /* +0x05C */ void slot05C() { VCM0(void, 0x5C); }
    /* +0x060 */ void slot060() { VCM0(void, 0x60); }
    /* +0x064 */ void slot064() { VCM0(void, 0x64); }
    /* +0x068 */ void slot068() { VCM0(void, 0x68); }
    /* +0x06C */ void slot06C() { VCM0(void, 0x6C); }
    /* +0x070 */ void slot070() { VCM0(void, 0x70); }
    /* +0x074 */ void slot074() { VCM0(void, 0x74); }
    /* +0x078 */ void slot078() { VCM0(void, 0x78); }
    /* +0x07C */ void slot07C() { VCM0(void, 0x7C); }
    /* +0x080 */ void slot080() { VCM0(void, 0x80); }
    /* +0x084 */ void slot084() { VCM0(void, 0x84); }
    /* +0x088 */ void slot088() { VCM0(void, 0x88); }
    /* +0x08C */ void slot08C() { VCM0(void, 0x8C); }
    /* +0x090 */ void slot090() { VCM0(void, 0x90); }
    /* +0x094 */ void slot094() { VCM0(void, 0x94); }
    /* +0x098 */ void slot098() { VCM0(void, 0x98); }
    /* +0x09C */ void slot09C() { VCM0(void, 0x9C); }
    /* +0x0A0 */ void slot0A0() { VCM0(void, 0xA0); }
    /* +0x0A4 */ void slot0A4() { VCM0(void, 0xA4); }
    /* +0x0A8 */ void slot0A8() { VCM0(void, 0xA8); }
    /* +0x0AC */ void slot0AC() { VCM0(void, 0xAC); }
    /* +0x0B0 */ void slot0B0() { VCM0(void, 0xB0); }
    /* +0x0B4 */ void slot0B4() { VCM0(void, 0xB4); }
    /* +0x0B8 */ void slot0B8() { VCM0(void, 0xB8); }
    /* +0x0BC */ void slot0BC() { VCM0(void, 0xBC); }
    /* +0x0C0 */ s32 isActive() { return VCM0(s32, 0xC0); }                /* +0xC0  tested != 0, gates the next call */
    /* +0x0C4 */ void slot0C4() { VCM0(void, 0xC4); }
    /* +0x0C8 */ void slot0C8() { VCM0(void, 0xC8); }
    /* +0x0CC */ void slot0CC() { VCM0(void, 0xCC); }
    /* +0x0D0 */ void slot0D0() { VCM0(void, 0xD0); }
    /* +0x0D4 */ void slot0D4() { VCM0(void, 0xD4); }
    /* +0x0D8 */ void slot0D8() { VCM0(void, 0xD8); }
    /* +0x0DC */ void slot0DC() { VCM0(void, 0xDC); }
    /* +0x0E0 */ void slot0E0() { VCM0(void, 0xE0); }
    /* +0x0E4 */ void slot0E4() { VCM0(void, 0xE4); }
    /* +0x0E8 */ void slot0E8() { VCM0(void, 0xE8); }
    /* +0x0EC */ void slot0EC() { VCM0(void, 0xEC); }
    /* +0x0F0 */ void slot0F0() { VCM0(void, 0xF0); }
    /* +0x0F4 */ void slot0F4() { VCM0(void, 0xF4); }
    /* +0x0F8 */ void slot0F8() { VCM0(void, 0xF8); }
    /* +0x0FC */ void slot0FC() { VCM0(void, 0xFC); }
    /* +0x100 */ void slot100() { VCM0(void, 0x100); }
    /* +0x104 */ void slot104() { VCM0(void, 0x104); }
    /* +0x108 */ void slot108() { VCM0(void, 0x108); }
    /* +0x10C */ void slot10C() { VCM0(void, 0x10C); }
    /* +0x110 */ void slot110() { VCM0(void, 0x110); }
    /* +0x114 */ void slot114() { VCM0(void, 0x114); }
    /* +0x118 */ void slot118() { VCM0(void, 0x118); }
    /* +0x11C */ void slot11C() { VCM0(void, 0x11C); }
    /* +0x120 */ void slot120() { VCM0(void, 0x120); }
    /* +0x124 */ void slot124() { VCM0(void, 0x124); }
    /* +0x128 */ void slot128() { VCM0(void, 0x128); }
    /* +0x12C */ void slot12C() { VCM0(void, 0x12C); }
    /* +0x130 */ void slot130() { VCM0(void, 0x130); }
    /* +0x134 */ void slot134() { VCM0(void, 0x134); }
    /* +0x138 */ void slot138() { VCM0(void, 0x138); }
    /* +0x13C */ void slot13C() { VCM0(void, 0x13C); }
    /* +0x140 */ void slot140() { VCM0(void, 0x140); }
    /* +0x144 */ void slot144() { VCM0(void, 0x144); }
    /* +0x148 */ void slot148() { VCM0(void, 0x148); }
    /* +0x14C */ void slot14C() { VCM0(void, 0x14C); }
    /* +0x150 */ void slot150() { VCM0(void, 0x150); }
    /* +0x154 */ void slot154() { VCM0(void, 0x154); }
    /* +0x158 */ void slot158() { VCM0(void, 0x158); }
    /* +0x15C */ void slot15C() { VCM0(void, 0x15C); }
    /* +0x160 */ void slot160() { VCM0(void, 0x160); }
    /* +0x164 */ void slot164() { VCM0(void, 0x164); }
    /* +0x168 */ void slot168() { VCM0(void, 0x168); }
    /* +0x16C */ void slot16C() { VCM0(void, 0x16C); }
    /* +0x170 */ void slot170() { VCM0(void, 0x170); }
    /* +0x174 */ void slot174() { VCM0(void, 0x174); }
    /* +0x178 */ void slot178() { VCM0(void, 0x178); }
    /* +0x17C */ void slot17C() { VCM0(void, 0x17C); }
    /* +0x180 */ void slot180() { VCM0(void, 0x180); }
    /* +0x184 */ void slot184() { VCM0(void, 0x184); }
    /* +0x188 */ void slot188() { VCM0(void, 0x188); }
    /* +0x18C */ void slot18C() { VCM0(void, 0x18C); }
    /* +0x190 */ void slot190() { VCM0(void, 0x190); }
    /* +0x194 */ void slot194() { VCM0(void, 0x194); }
    /* +0x198 */ void slot198() { VCM0(void, 0x198); }
    /* +0x19C */ void slot19C() { VCM0(void, 0x19C); }
    /* +0x1A0 */ void slot1A0() { VCM0(void, 0x1A0); }
    /* +0x1A4 */ void slot1A4() { VCM0(void, 0x1A4); }
    /* +0x1A8 */ void reset(s32 a0, s32 a1, s32 a2) { VCM(void, (void *, s32, s32, s32), 0x1A8, a0, a1, a2); }     /* +0x1A8 called with (1, 1, 1) */
    /* +0x1AC */ void slot1AC() { VCM0(void, 0x1AC); }
    /* +0x1B0 */ void slot1B0() { VCM0(void, 0x1B0); }
    /* +0x1B4 */ void slot1B4() { VCM0(void, 0x1B4); }
    /* +0x1B8 */ void slot1B8() { VCM0(void, 0x1B8); }
    /* +0x1BC */ void slot1BC() { VCM0(void, 0x1BC); }
    /* +0x1C0 */ void slot1C0() { VCM0(void, 0x1C0); }
    /* +0x1C4 */ void slot1C4() { VCM0(void, 0x1C4); }
    /* +0x1C8 */ void slot1C8() { VCM0(void, 0x1C8); }
    /* +0x1CC */ void slot1CC() { VCM0(void, 0x1CC); }
    /* +0x1D0 */ void slot1D0() { VCM0(void, 0x1D0); }
    /* +0x1D4 */ void slot1D4() { VCM0(void, 0x1D4); }
    /* +0x1D8 */ void slot1D8() { VCM0(void, 0x1D8); }
    /* +0x1DC */ void slot1DC() { VCM0(void, 0x1DC); }
    /* +0x1E0 */ void slot1E0() { VCM0(void, 0x1E0); }
    /* +0x1E4 */ void slot1E4() { VCM0(void, 0x1E4); }
    /* +0x1E8 */ void slot1E8() { VCM0(void, 0x1E8); }
    /* +0x1EC */ void slot1EC() { VCM0(void, 0x1EC); }
    /* +0x1F0 */ void slot1F0() { VCM0(void, 0x1F0); }
    /* +0x1F4 */ void slot1F4() { VCM0(void, 0x1F4); }
    /* +0x1F8 */ void slot1F8() { VCM0(void, 0x1F8); }
    /* +0x1FC */ void slot1FC() { VCM0(void, 0x1FC); }
    /* +0x200 */ void slot200() { VCM0(void, 0x200); }
    /* +0x204 */ void slot204() { VCM0(void, 0x204); }
    /* +0x208 */ void slot208() { VCM0(void, 0x208); }
    /* +0x20C */ void slot20C() { VCM0(void, 0x20C); }
    /* +0x210 */ void slot210() { VCM0(void, 0x210); }
    /* +0x214 */ void slot214() { VCM0(void, 0x214); }
    /* +0x218 */ void slot218() { VCM0(void, 0x218); }
    /* +0x21C */ void slot21C() { VCM0(void, 0x21C); }
    /* +0x220 */ void slot220() { VCM0(void, 0x220); }
    /* +0x224 */ void slot224() { VCM0(void, 0x224); }
    /* +0x228 */ void slot228() { VCM0(void, 0x228); }
    /* +0x22C */ void slot22C() { VCM0(void, 0x22C); }
    /* +0x230 */ void slot230() { VCM0(void, 0x230); }
    /* +0x234 */ void slot234() { VCM0(void, 0x234); }
    /* +0x238 */ void slot238() { VCM0(void, 0x238); }
    /* +0x23C */ void slot23C() { VCM0(void, 0x23C); }
    /* +0x240 */ void slot240() { VCM0(void, 0x240); }
    /* +0x244 */ void slot244() { VCM0(void, 0x244); }
    /* +0x248 */ void slot248() { VCM0(void, 0x248); }
    /* +0x24C */ void slot24C() { VCM0(void, 0x24C); }
    /* +0x250 */ void slot250() { VCM0(void, 0x250); }
    /* +0x254 */ void slot254() { VCM0(void, 0x254); }
    /* +0x258 */ void slot258() { VCM0(void, 0x258); }
    /* +0x25C */ void slot25C() { VCM0(void, 0x25C); }
    /* +0x260 */ void slot260() { VCM0(void, 0x260); }
    /* +0x264 */ void slot264() { VCM0(void, 0x264); }
    /* +0x268 */ void slot268() { VCM0(void, 0x268); }
    /* +0x26C */ void slot26C() { VCM0(void, 0x26C); }
    /* +0x270 */ void slot270() { VCM0(void, 0x270); }
    /* +0x274 */ void slot274() { VCM0(void, 0x274); }
    /* +0x278 */ void slot278() { VCM0(void, 0x278); }
    /* +0x27C */ void slot27C() { VCM0(void, 0x27C); }
    /* +0x280 */ void slot280() { VCM0(void, 0x280); }
    /* +0x284 */ void slot284() { VCM0(void, 0x284); }
    /* +0x288 */ void slot288() { VCM0(void, 0x288); }
    /* +0x28C */ void slot28C() { VCM0(void, 0x28C); }
    /* +0x290 */ void slot290() { VCM0(void, 0x290); }
    /* +0x294 */ void slot294() { VCM0(void, 0x294); }
    /* +0x298 */ void slot298() { VCM0(void, 0x298); }
    /* +0x29C */ void slot29C() { VCM0(void, 0x29C); }
    /* +0x2A0 */ void slot2A0() { VCM0(void, 0x2A0); }
    /* +0x2A4 */ void slot2A4() { VCM0(void, 0x2A4); }
    /* +0x2A8 */ void slot2A8() { VCM0(void, 0x2A8); }
    /* +0x2AC */ void slot2AC() { VCM0(void, 0x2AC); }
    /* +0x2B0 */ void slot2B0() { VCM0(void, 0x2B0); }
    /* +0x2B4 */ void slot2B4() { VCM0(void, 0x2B4); }
    /* +0x2B8 */ void slot2B8() { VCM0(void, 0x2B8); }
    /* +0x2BC */ void rewind(s32 a0, f32 a1) { VCM(void, (void *, s32, f32), 0x2BC, a0, a1); }         /* +0x2BC called with (0, 0.0f) */
};

#endif /* WORLDOBJ_CPP_H */
