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
    /* +0x0C0 */ virtual s32 isActive();                /* +0xC0  tested != 0, gates the next call */
    /* +0x0C4 */ virtual void slot0C4();
    /* +0x0C8 */ virtual void slot0C8();
    /* +0x0CC */ virtual void slot0CC();
    /* +0x0D0 */ virtual void slot0D0();
    /* +0x0D4 */ virtual void slot0D4();
    /* +0x0D8 */ virtual void slot0D8();
    /* +0x0DC */ virtual void slot0DC();
    /* +0x0E0 */ virtual void slot0E0();
    /* +0x0E4 */ virtual void slot0E4();
    /* +0x0E8 */ virtual void slot0E8();
    /* +0x0EC */ virtual void slot0EC();
    /* +0x0F0 */ virtual void slot0F0();
    /* +0x0F4 */ virtual void slot0F4();
    /* +0x0F8 */ virtual void slot0F8();
    /* +0x0FC */ virtual void slot0FC();
    /* +0x100 */ virtual void slot100();
    /* +0x104 */ virtual void slot104();
    /* +0x108 */ virtual void slot108();
    /* +0x10C */ virtual void slot10C();
    /* +0x110 */ virtual void slot110();
    /* +0x114 */ virtual void slot114();
    /* +0x118 */ virtual void slot118();
    /* +0x11C */ virtual void slot11C();
    /* +0x120 */ virtual void slot120();
    /* +0x124 */ virtual void slot124();
    /* +0x128 */ virtual void slot128();
    /* +0x12C */ virtual void slot12C();
    /* +0x130 */ virtual void slot130();
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
    /* +0x1A8 */ virtual void reset(s32, s32, s32);     /* +0x1A8 called with (1, 1, 1) */
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
    /* +0x2BC */ virtual void rewind(s32, f32);         /* +0x2BC called with (0, 0.0f) */
};

#endif /* WORLDOBJ_CPP_H */
