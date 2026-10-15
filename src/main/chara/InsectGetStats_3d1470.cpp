#include "types.h"

/* Same "vptr at object offset +0" shape used across the corpus (see
   src/s13d/CharaMgrPoolUpdate_3a8490.cpp, src/s13o/CharaGetEquippedWeapon_3acd40.cpp, etc.) -- `arg0` is
   directly the polymorphic object; m2c's `(*arg0)->` is its usual confused
   spelling of a plain `arg0->method()`, and its "(arg0, ...)" first argument
   on two of the calls is really just the (implicit) `this`, not a real
   parameter. Four slots used: +0x14C, +0x174, +0x180, +0x18C -> virtual
   indices 81, 91, 94, 97. */

class V {
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
    /* +0x14C */ virtual void slot14C(s32 arg1);
    /* +0x150 */ virtual void slot150();
    /* +0x154 */ virtual s32 slot154();
    /* +0x158 */ virtual void slot158();
    /* +0x15C */ virtual void slot15C();
    /* +0x160 */ virtual void slot160();
    /* +0x164 */ virtual void slot164();
    /* +0x168 */ virtual void slot168();
    /* +0x16C */ virtual void slot16C();
    /* +0x170 */ virtual s32 slot170();
    /* +0x174 */ virtual void slot174(s32 arg1);
    /* +0x178 */ virtual void slot178();
    /* +0x17C */ virtual s32 slot17C();
    /* +0x180 */ virtual void slot180(s32 arg1);
    /* +0x184 */ virtual void slot184();
    /* +0x188 */ virtual s32 slot188(s32);
    /* +0x18C */ virtual void slot18C(s32 arg1, s32 arg2);
};

typedef struct Arg1FUN_003d1470 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 arr[6];   /* accessed as (u8*)arg1 + i*4 + 0xC, i.e. an s32[6] at +0xC */
} Arg1FUN_003d1470;

extern "C" void InsectGetStats_3d1470(V *arg0, Arg1FUN_003d1470 *arg1)
{
    s32 i;

    arg1->unk0 = arg0->slot154();
    arg1->unk4 = arg0->slot170();
    arg1->unk8 = arg0->slot17C();
    i = 0;
    do {
        arg1->arr[i] = arg0->slot188(i);
        i += 1;
    } while (i < 6);
}
