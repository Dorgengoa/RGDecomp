#include "types.h"

/* factory.bin overlay, 0x00504520 -- 76 B / 19 words.  Plant two table
 * pointers into the object, call through the one at 0xF0 with the sub-object
 * at 0x10 as `this`, return `this`.
 *
 * THE jalr SCREEN, read at the load site:
 *      lw $25,0xF0($16)  /  lw $25,0x10($25)  /  jalr $25
 * The board treats a two-level load as a blanket C++-virtual DROP.  Measured
 * here (round trip 1, build/obj-fy06): a plain C struct of function pointers
 * builds the whole function correctly EXCEPT that the target lands in $v0 --
 * `8E0200F0 / 8C420010 / 0040F809` against retail's
 * `8E1900F0 / 8F390010 / 0320F809`, three bad words and nothing else.  That
 * re-confirms factory_FactoryMoveShowPartInfo_4f4130.cpp's note: only a real `virtual` puts the
 * target in $t9.  So the unit is .cpp for that one call and nothing else.
 *
 * The layout that reproduces `lw $25,0xF0($16)` with `this` = $16+0x10 is a
 * class whose vptr sits AFTER a 0xE0-byte non-polymorphic base: the sub-object
 * starts at 0x10, its vptr is at 0x10+0xE0 = 0xF0, and mwcc folds the +0x10
 * into the load displacement.  mwcc puts the first virtual at vtable slot
 * +0x08, so slot 0x10 is index (0x10-8)/4 = 2 -- two placeholders, then the
 * real one.  The class is never constructed, so no vtable is emitted.
 *
 * The 0xF0 vptr is written by hand (an extern table address, not mwcc's own
 * vtable), so it stays a member of the plain struct and the call goes through
 * a cast.  Store order is retail's: 0x1B0 first, then 0xF0; the reload of 0xF0
 * right after storing it is "a load will not cross a store".
 */

struct IfaceBase { u8 d[0xE0]; };

struct Iface : IfaceBase {
    virtual void s00();
    virtual void s01();
    virtual void f10();
};

struct Fac4520 {
    u8    pad000[0x10];
    u8    sub010[0xE0];             /* 0x010, vptr at 0x0F0 */
    void *tF0;                      /* 0x0F0 */
    u8    pad0F4[0x1B0 - 0xF4];
    void *t1B0;                     /* 0x1B0 */
};

extern "C" u8 D_0046FFC0[];
extern "C" u8 D_0046FFA0[];

extern "C" Fac4520 *factory_ModelCtor_504520(Fac4520 *p);

Fac4520 *factory_ModelCtor_504520(Fac4520 *p)
{
    p->t1B0 = D_0046FFC0;
    p->tF0 = D_0046FFA0;
    ((Iface *)p->sub010)->f10();
    return p;
}
