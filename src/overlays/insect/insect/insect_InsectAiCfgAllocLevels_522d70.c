#include "types.h"
/* insect 0x00522D70 -- 168 bytes, 42 instructions, 5 calls.  func_14DB10 and
 * func_100710 take FOUR and FIVE integer arguments: under the PS2 EABI the
 * fifth goes in $8, which is why `daddu $8,$17,$0` sits between the call and
 * its own argument setup. */

typedef struct Ent {
    u8 pad[0x10];
} Ent;

typedef struct Obj {
    void *m00;                      /* +0x00 */
    Ent  *m04;                      /* +0x04 */
    void *m08;                      /* +0x08 */
    s16   m0C;                      /* +0x0C */
} Obj;

extern void *func_14DB10(void *h, s32 a, s32 b, s32 c);
extern Ent  *func_14E1B0(s32 size, void *h);
extern Ent  *func_100710(Ent *p, s32 a, s32 b, s32 c, s32 d);
extern void  func_14DAD0(void *h);
extern void  insect_InsectAiLevelReset_522ed0(Ent *e);

void insect_InsectAiCfgAllocLevels_522d70(Obj *o, s16 n)
{
    s16 c;
    s32 i;

    o->m0C = n;
    o->m00 = func_14DB10(o->m08, 2, 0, 0x40);
    if (o->m00 == 0) {
        return;
    }
    c = o->m0C;
    o->m04 = func_100710(func_14E1B0(c * 16 + 0x10, o->m08), 0, 0, 0x10, c);
    for (i = 0; i < o->m0C; i++) {
        insect_InsectAiLevelReset_522ed0(&o->m04[i]);
    }
    func_14DAD0(o->m08);
}
