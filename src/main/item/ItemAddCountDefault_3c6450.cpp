#include "types.h"

class A {
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
};

extern "C" void ItemAddCountDefault_3c6450(A *self)
{
    self->slot50();
}
