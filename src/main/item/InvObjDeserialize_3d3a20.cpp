#include "types.h"

/* clone group cg06-000 -- exemplar StateBlockDeserialize_3cb970, MATCHED.
   Two guards are ONE || (separate ifs put the shared return-0 block in the
   wrong place); the range extern must be an ARRAY or mwcc puts it in sdata and
   emits gp-relative instead of hi/lo; and "total = 0;" sits BETWEEN the ||
   guard and the range guard -- that is what fills the third branch's delay
   slot and leaves the jalr slot a nop.  Vtable slot read off each member's own
   listing. */

class Obj {
public:
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual void slot44();
    virtual void slot48();
    virtual void slot4C();
    virtual void slot50();
    virtual void slot54();
    virtual void slot58();
    virtual void slot5C();
    virtual void slot60();
    virtual void slot64();
    virtual void slot68();
    virtual void slot6C();
    virtual void slot70();
    virtual void slot74();
    virtual void slot78();
    virtual void slot7C();
    virtual void slot80();
    virtual void slot84();
    virtual void slot88();
    virtual void slot8C();
    virtual void slot90();
    virtual void slot94();
    virtual void slot98();
    virtual void slot9C();
    virtual void slotA0();
    virtual void slotA4();
    virtual void slotA8();
    virtual void slotAC();
    virtual void slotB0();
    virtual void slotB4();
    virtual void slotB8();
    virtual void slotBC();
    virtual void slotC0();
    virtual void slotC4();
    virtual void slotC8();
    virtual void slotCC();
    virtual void slotD0();
    virtual void slotD4();
    virtual void slotD8();
    virtual void slotDC();
    virtual void slotE0();
    virtual void slotE4();
    virtual void slotE8();
    virtual void slotEC();
    virtual void slotF0();
    virtual void slotF4();
    virtual void slotF8();
    virtual void slotFC();
    virtual void slot100();
    virtual void slot104();
    virtual void slot108();
    virtual void slot10C();
    virtual s32 slot110(void *p, s32 n);
};

extern s32 D_004658F8[4];

extern "C" s32 InvObjDeserialize_3d3a20(Obj *self, void *p, s32 n)
{
    s32 total;

    if (p == 0 || n <= 0) return 0;
    total = 0;
    if (D_004658F8[0] < n) return 0;
    total += self->slot110(p, n);
    return total;
}
