#include "types.h"

class VE {
    u8 pad_[0x68];
public:
    virtual void vs0();
    virtual void vs1();
    virtual void vs2();
    virtual void vs3();
    virtual void vs4();
    virtual void vs5();
    virtual void vs6();
    virtual void vs7();
    virtual void vs8();
    virtual void vs9();
    virtual void vs10();
    virtual void vs11();
    virtual void vs12();
    virtual void vs13();
    virtual void vs14();
    virtual void vs15();
    virtual void vs16();
    virtual void vs17();
    virtual void vs18();
    virtual void vs19();
    virtual void vs20();
    virtual void vs21();
    virtual void vs22();
    virtual void vs23();
    virtual void vs24();
    virtual void vs25();
    virtual void vs26();
    virtual void vs27();
    virtual void vs28();
    virtual void vs29();
    virtual void vs30();
    virtual void f84();
};

/* Reset.  Indirect call is a vtable pointer at 0x98, slot 0x84, and the object
   passed is `this + 0x30` (an embedded sub-object), not `this`. */


extern "C" void LoadHandleReset_1ccc10(void *);

extern "C" void MapAreaDataReset_1e8fe0(u8 *p)
{
    s32 i;
    s32 j;
    s32 k;

    ((VE *)(p + 0x30))->f84();
    *(s32 *)(p + 0x16B0) = 0;
    *(s16 *)(p + 0x16B8) = 0;
    *(s32 *)(p + 0x16B4) = 0;
    *(s16 *)(p + 0x16BA) = 0;
    for (i = 0; i < 4; i++) {
        LoadHandleReset_1ccc10(p + i * 0xC);
    }
    *(u8 *)(p + 0x16BC) = 0;
    *(s16 *)(p + 0x16C8) = -1;
    *(s32 *)(p + 0x16C0) = -1;
    *(s32 *)(p + 0x16C4) = 0;
    *(s16 *)(p + 0x16CA) = 0;
    *(s32 *)(p + 0x16CC) = 0;
    *(s32 *)(p + 0x16D0) = 0;
    *(s32 *)(p + 0x16D4) = 0;
    *(s32 *)(p + 0x16D8) = 0;
    *(s32 *)(p + 0x16DC) = 0;
    *(s32 *)(p + 0x16E0) = 0;
    for (j = 0; j < 4; j++) {
        *(s32 *)(p + 0x16E4 + j * 4) = 0;
    }
    for (k = 0; k < 4; k++) {
        *(s32 *)(p + 0x16F4 + k * 4) = 0;
    }
}
