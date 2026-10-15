#include "types.h"

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
    /* +0x1A8 */ virtual void slot1A8(s32 b, s32 c, s32 d);
};

struct H { u8 pad000[0x14]; s32 f14; };
struct A { u8 pad000[0x8]; struct H *fh; };

extern "C" V *PoolGetUsedElem_36acb0(struct H *h, s32 i);

extern "C" s32 CharaMgrPoolStatusClearAll_3a8960(struct A *a, s32 b, s32 c, s32 d)
{
    s32 i;
    s32 n;
    V *e;

    if (a->fh == 0) {
        return 0;
    }
    n = a->fh->f14;
    for (i = 0; i < n; i++) {
        e = PoolGetUsedElem_36acb0(a->fh, i);
        if (e != 0) {
            e->slot1A8(b, c, d);
        }
    }
    return 1;
}
