#include "types.h"

struct It { u8 b[0x8]; };
struct A { u8 b[0x18]; };
struct X { u8 pad000[0x88]; };
struct D : X, A { };

class V {
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
    /* +0x70 */ virtual void *slot70(s16 id);
};

struct H { u8 pad000[0x14]; V *obj; };
struct Q { u8 pad000[0x34]; H *h; };
struct E { u8 pad000[0xC]; s16 id; };

extern "C" void IterInit_370170(It *, A *);
extern "C" E *IterNext_370040(It *);

extern "C" s32 WorldSubsysLinkIds_415aa0(D *d, Q *q)
{
    It it;
    E *e;

    if (q == 0) {
        return 0;
    }
    IterInit_370170(&it, d);
    while ((e = IterNext_370040(&it)) != 0) {
    *(void **)&e->id = q->h->obj->slot70(e->id);
    }
    return 1;
}
