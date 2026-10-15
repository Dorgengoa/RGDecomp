#include "types.h"

extern "C" void Sprintf_1343b8(s8 *, const void *, s32);
extern "C" u8 D_004640E0[];

class Obj390DE0 {
public:
    virtual void *slot08();
    virtual void *slot0C();
    virtual void *slot10();
    virtual void *slot14();
    virtual void *slot18();
    virtual void *slot1C();
    virtual void *slot20();
    virtual void *slot24();
    virtual void *slot28();
    virtual void *slot2C();
    virtual void *slot30();
    virtual void *slot34();
    virtual void *slot38();
    virtual void *slot3C();
    virtual void *slot40();
    virtual void *slot44();
    virtual void *slot48();
    virtual void *slot4C();
    virtual void *slot50();
    virtual void *slot54();
    virtual void *slot58();
    virtual void *slot5C();
    virtual void *slot60();
    virtual void *slot64();
    virtual void *slot68();
    virtual void *slot6C();
    virtual void *slot70();
    virtual void *slot74();
    virtual void *slot78();
    virtual void *slot7C();
    virtual void *slot80();
    virtual void *slot84();
    virtual void *slot88();
    virtual void *slot8C();
    virtual void *slot90();
    virtual void *slot94();
    virtual void *slot98();
    virtual void *slot9C();
    virtual void *slotA0();
    virtual void *slotA4();
    virtual void *slotA8();
    virtual void *slotAC();
    virtual void *slotB0();
    virtual void *slotB4();
    virtual void *slotB8();
    virtual void *slotBC();
    virtual void *slotC0();
    virtual void *slotC4();
    virtual void *slotC8();
    virtual void *slotCC();
    virtual void *slotD0();
    virtual void *slotD4();
    virtual void *slotD8();
    virtual void *slotDC();
    virtual void *slotE0();
    virtual void *slotE4();
    virtual void *slotE8();
    virtual void *slotEC();
    virtual void *slotF0();
    virtual void *slotF4();
    virtual void *slotF8();
    virtual void *slotFC();
    virtual void *slot100();
    virtual void *slot104();
    virtual void *slot108();
    virtual void *slot10C();
    virtual void *slot110();
    virtual void *slot114();
    virtual void *slot118();
    virtual void *slot11C();
    virtual void *slot120();
    virtual void *slot124();
};

extern "C" s32 InsectCharaPathFormat_390de0(s8 *buf, Obj390DE0 *obj)
{
    void *r;
    void *p;

    if (buf == NULL) {
        return 0;
    }
    *buf = 0;
    if (obj == NULL) {
        return 0;
    }
    r = obj->slot124();
    if (r == NULL) {
        return 0;
    }
    p = *(void **)((u8 *)r + 4);
    if (p == NULL) {
        return 0;
    }
    Sprintf_1343b8(buf, D_004640E0, *(s32 *)((u8 *)p + 8));
    return 1;
}
