#include "types.h"

class A {
    u8 pad000[0xC0];
public:
    /* +0x08 */ virtual void slot08();
    /* +0x0C */ virtual void slot0C();
    /* +0x10 */ virtual void slot10();
    /* +0x14 */ virtual void slot14();
    /* +0x18 */ virtual void slot18();
    /* +0x1C */ virtual void slot1C();
    /* +0x20 */ virtual void slot20();
    /* +0x24 */ virtual void slot24();
    /* +0x28 */ virtual void slot28();
    /* +0x2C */ virtual void slot2C();
    /* +0x30 */ virtual void slot30();
    /* +0x34 */ virtual void slot34();
    /* +0x38 */ virtual void slot38();
    /* +0x3C */ virtual void slot3C();
    /* +0x40 */ virtual void slot40();
    /* +0x44 */ virtual void slot44();
    /* +0x48 */ virtual void slot48();
    /* +0x4C */ virtual void slot4C();
    /* +0x50 */ virtual void slot50();
    /* +0x54 */ virtual void slot54();
    /* +0x58 */ virtual void slot58();
    /* +0x5C */ virtual void slot5C();
    /* +0x60 */ virtual void slot60();
    /* +0x64 */ virtual void slot64();
    /* +0x68 */ virtual void slot68();
    /* +0x6C */ virtual void slot6C();
    /* +0x70 */ virtual void slot70();
    /* +0x74 */ virtual void slot74();
    /* +0x78 */ virtual void slot78();
    /* +0x7C */ virtual void slot7C();
    /* +0x80 */ virtual void slot80();
    /* +0x84 */ virtual void slot84();
    /* +0x88 */ virtual void slot88();
    /* +0x8C */ virtual void slot8C();
    /* +0x90 */ virtual void slot90();
    /* +0x94 */ virtual void slot94();
    /* +0x98 */ virtual void slot98();
    /* +0x9C */ virtual void slot9C();
    /* +0xA0 */ virtual void slotA0();
    /* +0xA4 */ virtual void slotA4();
    /* +0xA8 */ virtual void slotA8();
    /* +0xAC */ virtual void slotAC();
    /* +0xB0 */ virtual void slotB0();
    /* +0xB4 */ virtual void slotB4();
    /* +0xB8 */ virtual void slotB8();
};

extern "C" void CameraGetYawThunk_160460(A *self)
{
    self->slotB8();
}
