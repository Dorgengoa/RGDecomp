#include "types.h"

/* factory.bin overlay, 0x00504590 -- 108 B / 27 words.  0x00504520 verbatim
 * (same two table stores, same call through the 0xF0 table) followed by two
 * more writes of the 0x1B0 slot and one call.
 *
 * .cpp for the same measured reason as factory_ModelCtor_504520.cpp: the plain-C
 * struct-of-function-pointers spelling built every other word of this function
 * and put the call target in $v0 instead of $t9 (round trip 1: three bad
 * words, `8E0200F0 / 8C420010 / 0040F809`).  Only a real `virtual` uses $t9.
 * Vptr after a 0xE0 non-polymorphic base; slot 0x10 = index (0x10-8)/4 = 2.
 *
 * The two consecutive writes of DIFFERENT values to the same 0x1B0 slot are
 * retail's: a constructor chain, each layer overwriting the slot the layer
 * below just wrote.  The second lands in func_1726F0's delay slot.
 */

struct IfaceBase { u8 d[0xE0]; };

struct Iface : IfaceBase {
    virtual void s00();
    virtual void s01();
    virtual void f10();
};

struct Fac4590 {
    u8    pad000[0x10];
    u8    sub010[0xE0];             /* 0x010, vptr at 0x0F0 */
    void *tF0;                      /* 0x0F0 */
    u8    pad0F4[0x1B0 - 0xF4];
    void *t1B0;                     /* 0x1B0 */
    u8    pad1B4[0x1F0 - 0x1B4];
    u8    sub1F0[0x40];             /* 0x1F0 */
};

extern "C" u8 D_0046FFC0[];
extern "C" u8 D_0046FFA0[];
extern "C" u8 D_00470440[];
extern "C" u8 D_0047CD60[];

extern "C" void func_1726F0(void *p);

extern "C" Fac4590 *factory_ModelObjBaseCtor_504590(Fac4590 *p);

Fac4590 *factory_ModelObjBaseCtor_504590(Fac4590 *p)
{
    p->t1B0 = D_0046FFC0;
    p->tF0 = D_0046FFA0;
    ((Iface *)p->sub010)->f10();
    p->t1B0 = D_00470440;
    p->t1B0 = D_0047CD60;
    func_1726F0(p->sub1F0);
    return p;
}
