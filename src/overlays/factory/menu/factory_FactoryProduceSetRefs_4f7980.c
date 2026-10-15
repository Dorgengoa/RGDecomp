#include "types.h"

/* factory.bin overlay, 0x004F7980 -- wire one module and allocate its three
 * work buffers.  Sibling of 0x004F2100 with three allocations instead of one;
 * the middle one comes from a different allocator (func_14E230).
 *
 * ★ Each allocation re-READS `o->f90` rather than reusing `$8`: retail issues
 * `lw $5, 0x90($16)` before every one of the three calls.
 */

typedef struct Mod {
    u8    pad0[0x72];
    u8    f72;
    u8    pad73[5];
    void *f78;
    void *f7C;
    void *f80;
    void *f84;
    void *f88;
    void *f8C;
    void *f90;
} Mod;

extern void *func_14E1B0(s32 size, void *heap);
extern void *func_14E230(s32 size, void *heap);
extern void  func_131B60(void *p, s32 v, s32 n);

void factory_FactoryProduceSetRefs_4f7980(Mod *o, void *a, void *b, void *c, void *d)
{
    void *p;

    o->f84 = a;
    o->f88 = b;
    o->f8C = c;
    o->f90 = d;
    p = func_14E1B0(0x78, o->f90);
    o->f78 = p;
    func_131B60(p, 0, 0x78);
    p = func_14E230(0x14, o->f90);
    o->f7C = p;
    func_131B60(p, 0, 0x14);
    p = func_14E1B0(0x20, o->f90);
    o->f80 = p;
    func_131B60(p, 0, 0x20);
    o->f72 = 0;
}
