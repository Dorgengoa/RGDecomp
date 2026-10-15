#include "types.h"

/* factory.bin overlay, 0x00504850 -- 136 B / 34 words.  Tear-down: two chained
 * calls, a three-slot loop that calls through each live slot's table, two more
 * chained calls, then the overlay's own 0x00504960.
 *
 * .cpp for the call only: measured in round trip 1, the plain-C
 * struct-of-function-pointers spelling produced every word of this function
 * correctly except `8C8201B0 / 8C420058 / 0040F809` where retail has
 * `8C9901B0 / 8F390058 / 0320F809` -- the target in $v0, not $t9.  Only a real
 * `virtual` uses $t9.  Here `this` is the slot pointer itself, so the vptr is
 * at the class's own offset 0x1B0: a 0x1B0-byte non-polymorphic base, vptr
 * after it.  Slot 0x58 is index (0x58-8)/4 = 20 -- twenty placeholders.
 *
 * `slti $2,$16,3` lands in a GENERAL register, so it is the non-strict form
 * `i < 3`.  `addiu $16,$16,1` appears twice because the null test is a
 * branch-likely whose delay slot tail-duplicates the increment -- one `for`
 * with one `if` inside, not two loops.
 */

struct Obj850Base { u8 d[0x1B0]; };

struct Obj850 : Obj850Base {
    virtual void s00();  virtual void s01();  virtual void s02();
    virtual void s03();  virtual void s04();  virtual void s05();
    virtual void s06();  virtual void s07();  virtual void s08();
    virtual void s09();  virtual void s10();  virtual void s11();
    virtual void s12();  virtual void s13();  virtual void s14();
    virtual void s15();  virtual void s16();  virtual void s17();
    virtual void s18();  virtual void s19();
    virtual void f58();
};

struct Ctx850 {
    u8       pad000[0x54];
    Obj850  *slot[3];               /* 0x054 */
};

extern "C" void *func_1F5BE0(void);
extern "C" void  func_1CED20(void *p);
extern "C" void *func_15DE40(void);
extern "C" void  func_158AC0(void *p, s32 n);
extern "C" void  factory_FactoryObjRelease_504960(Ctx850 *c);

extern "C" void factory_FactoryShutdown_504850(Ctx850 *c);

void factory_FactoryShutdown_504850(Ctx850 *c)
{
    s32 i;

    func_1CED20(func_1F5BE0());

    for (i = 0; i < 3; i++) {
        Obj850 *o = c->slot[i];
        if (o != NULL) {
            o->f58();
        }
    }

    func_158AC0(func_15DE40(), 0x2A4);
    factory_FactoryObjRelease_504960(c);
}
