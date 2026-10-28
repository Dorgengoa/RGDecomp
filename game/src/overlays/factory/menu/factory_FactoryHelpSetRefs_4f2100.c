/* rgp:protos */
#define RGP_SELF_factory_FactoryHelpSetRefs_4f2100 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x004F2100 -- wire one module and allocate its 0x40-byte
 * work buffer.
 *
 * ★ The allocator's second argument is re-READ from `o->f94` rather than reused
 * from `$8`: retail issues `lw $5, 0x94($16)` after the four stores, which is
 * the field read the source wrote and not a copy of the parameter.
 */

typedef struct Mod {
    u8    pad0[0x74];
    void *f74;
    u8    pad78[0x10];
    void *f88;
    void *f8C;
    void *f90;
    void *f94;
} Mod;

/*rgp*/
extern void  memset(void *p, s32 v, s32 n);

void factory_FactoryHelpSetRefs_4f2100(Mod *o, void *a, void *b, void *c, void *d)
{
    void *p;

    o->f88 = a;
    o->f8C = b;
    o->f90 = c;
    o->f94 = d;
    p = MemStackNew_14e1b0(0x40, o->f94);
    o->f74 = p;
    memset(p, 0, 0x40);
}
