#include "types.h"
/* insect 0x0051CF50 -- 200 bytes, 50 instructions, 5 calls.  The sibling of
 * 0x00522D70 / 0x00523A00: allocate an n-element array of 0x80-byte records
 * through func_14E1B0 / func_100710 and clear every one.  func_100710 takes
 * FIVE arguments (the fifth in $8) and here arguments two and three are the
 * two record hooks 0x0051D370 / 0x0051D320.  `lw $3, 0x58($17)` sits in the
 * loop test's delay slot, so the base is RE-READ every iteration; the tail
 * reads it once more into a local that the two stores share.
 */

typedef struct Elem { u8 raw[0x80]; } Elem;

typedef struct Ctx {
    u8    pad00[0x58];
    Elem *f58;                      /* +0x58 */
    u8    pad5C[0x64 - 0x5C];
    Elem *f64;                      /* +0x64 */
    s32   f68;                      /* +0x68 */
} Ctx;

extern void *func_14DB10(void *h, s32 a, s32 b, s32 c);
extern Elem *func_14E1B0(s32 size, void *h);
extern Elem *func_100710(Elem *p, void (*a)(void), void (*b)(void), s32 c, s32 d);
extern void  func_14DAD0(void *h);
extern void  insect_InsectAbilityReset_51d280(Elem *e);
extern void  insect_InsectAbilityDtor_51d320(void);
extern void  insect_InsectAbilityCtor_51d370(void);

void insect_InsectAbilityTableAllocRecords_51cf50(Ctx *o, s32 n)
{
    Elem *e;
    Elem *b;
    s32 i;

    if (n > 0) {
        func_14DB10(o, 2, 0, 0x40);
        o->f58 = func_100710(func_14E1B0(n * 128 + 0x10, o), insect_InsectAbilityCtor_51d370,
                             insect_InsectAbilityDtor_51d320, 0x80, n);
        func_14DAD0(o);
        for (i = 0; i < n; i++) {
            e = o->f58 + i;
            if (e != 0) {
                insect_InsectAbilityReset_51d280(e);
            }
        }
        b = o->f58;
        if (b != 0) {
            o->f64 = b;
            o->f68 = 0;
        }
    }
}
