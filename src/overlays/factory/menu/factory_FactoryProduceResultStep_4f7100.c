#include "types.h"

/* factory.bin overlay, 0x004F7100 -- the parts-shop panel state machine: one
 * step per phase, re-laying the message box out at each transition.
 *
 * A compiled `switch` over phases 1..9, so mwcc emits a real jump table;
 * scripts/f_jtbl.py points it at the overlay's own jtbl_0050CCA0.
 *
 * ★★ EVERY INNER DISPATCH IS AN if/else-if CHAIN, NOT A `switch`, AND m2c
 * RENDERS ALL FIVE OF THEM AS `switch`.  `scripts/f_ds.py` classifies all
 * twelve conditional branches by delay slot in one run: not one converted
 * `beql`/`bnel` carries a case body's store -- they carry either the merge's
 * first instruction (which makes them PLAIN branches) or the NEXT GUARD'S
 * CONSTANT (0x004F71D0 carries `addiu $2, $0, 0xF`).  Written as switches they
 * would be the right length and the wrong bytes.
 *
 * ★ Chains are in SOURCE order, so the compare order in the listing IS the
 * order to write: 0xC then 0xF, and 0x4167 then 0x416A then 0x3ECF.  (The
 * reversed-case-order rule belongs to real switches only.)
 *
 * ★ Entry 0 of jtbl_0050CCA0 holds the default block's address, so phase 0 is
 * absent from the source; entries 4, 6 and 9 share one block.  Physical block
 * order -- 1, 2, 3, the shared 4/6/9, 5, 7, 8 -- is source order.
 *
 * ★ `func_288E50(func_28FE10(...), ...)` keeps the call INSIDE the argument
 * list: retail moves the result straight into $4 with `daddu $4, $2, $0`.
 */

typedef struct Rec {
    s16 f00;
    u8  pad02[0x2A];
    s16 f2C;
} Rec;

typedef struct Panel {
    u8    pad0[0x72];
    u8    f72;
    u8    pad73;
    Rec  *f74;
    u8    pad78[0xC];
    void *f84;
    u8    pad88[4];
    void *f8C;
} Panel;

extern void  factory_FactoryProduceShowMessage_4f62d0(Panel *o, s16 kind);
extern void  func_288E50(void *p, s32 k, s32 a, s32 b);
extern void  func_28EDE0(void *ctx, s32 id, s32 a);
extern void  func_28F9D0(void *ctx, s32 id, s32 a, s32 b, s32 c, s32 d, s32 e);
extern void *func_28FE10(void *ctx, s32 id, s32 a);
extern void  func_290010(void *ctx, s32 id, s32 a, s32 b);
extern void *func_367EC0(void);   /* the result is discarded here; see 004FB840 */

void factory_FactoryProduceResultStep_4f7100(Panel *o)
{
    Rec *r;
    s16  k;
    s16  id;
    u8   phase;

    func_367EC0();
    phase = o->f72;
    switch (phase) {
    case 1:
        func_290010(o->f84, 0x89, 0, -1);
        func_290010(o->f84, 0x8B, 1, -1);
        func_290010(o->f84, 0x8F, 0, -1);
        func_290010(o->f84, 0x90, 0, -1);
        k = o->f74->f2C;
        if (k == 0xC || k == 0xF) {
            func_290010(o->f84, 0x90, 1, -1);
            k = o->f74->f2C;
            if (k == 0xC) {
                func_28F9D0(o->f84, 0x90, 0x140, 0x20, 0x20, 0x20, 0);
            } else if (k == 0xF) {
                func_28F9D0(o->f84, 0x90, 0x140, 0, 0x20, 0x20, 0);
            }
        } else {
            func_290010(o->f84, 0x8F, 1, -1);
            func_288E50(func_28FE10(o->f84, 0x8F, 0), o->f74->f2C, 0x28, 0x2D);
        }
        factory_FactoryProduceShowMessage_4f62d0(o, 0);
        o->f72 = 2;
        break;
    case 2:
        func_290010(o->f84, 0x8F, 0, -1);
        func_290010(o->f84, 0x90, 0, -1);
        func_290010(o->f84, 0x8E, 0, -1);
        func_290010(o->f84, 0x8D, 0, -1);
        func_290010(o->f84, 0x8F, 0, -1);
        func_290010(o->f84, 0x90, 0, -1);
        k = o->f74->f2C;
        if (k == 0xC || k == 0xF) {
            factory_FactoryProduceShowMessage_4f62d0(o, 2);
        } else {
            factory_FactoryProduceShowMessage_4f62d0(o, 1);
        }
        o->f72 = 3;
        break;
    case 3:
        r = o->f74;
        k = r->f2C;
        if (k == 0xC || k == 0xF) {
            func_28EDE0(o->f8C, 0x89EE, 0);
            break;
        }
        id = r->f00;
        if (id == 0x4167 || id == 0x416A || id == 0x3ECF) {
            func_28EDE0(o->f8C, 0x89EE, 0);
            break;
        }
        factory_FactoryProduceShowMessage_4f62d0(o, 5);
        o->f72 = 4;
        break;
    case 4:
    case 6:
    case 9:
        func_28EDE0(o->f8C, 0x89EE, 0);
        break;
    case 5:
        func_290010(o->f84, 0x8A, 0, -1);
        func_290010(o->f84, 0x8B, 1, -1);
        func_290010(o->f84, 0x8E, 0, -1);
        func_290010(o->f84, 0x8D, 0, -1);
        func_290010(o->f84, 0x8F, 0, -1);
        func_290010(o->f84, 0x90, 0, -1);
        o->f72 = 8;
        factory_FactoryProduceShowMessage_4f62d0(o, 4);
        break;
    case 7:
        func_290010(o->f84, 0x8A, 1, -1);
        func_290010(o->f84, 0x8C, 0, -1);
        o->f72 = 5;
        break;
    case 8:
        o->f72 = 6;
        factory_FactoryProduceShowMessage_4f62d0(o, 3);
        break;
    }
}
