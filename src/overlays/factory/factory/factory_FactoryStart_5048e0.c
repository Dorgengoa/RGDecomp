#include "types.h"

/* factory.bin overlay, 0x005048E0 -- enter the factory screen: fetch the
 * global game record, hand it to the scene setup, then arm the panel's own
 * three fields and start the two fades.
 * 120 bytes, 32 instructions, 0 conditional branches, 5 calls.
 *
 * * `func_1F5BE0()` takes no parameters -- four overlay sources already in the
 * tree declare it that way -- and the `$4` still holding `o` at the `jal` is
 * the caller's own value, not an argument.
 *
 * * `addiu $2, $0, -0x1` (not `daddiu`) says the shared -1 is materialised as
 * an `s32`; the two `sh` stores narrow it at the store
 * ([[factory-optimization-level-3]]'s `d`-prefix reading).
 */

typedef struct Panel {
    u8  pad000[0x50];
    s32 f050;
    u8  pad054[0x274];
    s32 f2C8;
    u8  pad2CC[0x1A];
    s16 f2E6;
    s16 f2E8;
} Panel;

typedef struct Game {
    u8  pad0000[0x4344];
    s32 f4344;
} Game;

extern Game *func_1F5BE0(void);
extern void  func_1CED50(Game *g);
extern void  func_207E20(s32 a, s32 b);
extern void  func_207880(s32 a, s32 b);
extern void  factory_FactoryCameraInit_505af0(Panel *o);

void factory_FactoryStart_5048e0(Panel *o)
{
    Game *g;

    g = func_1F5BE0();
    func_1CED50(g);
    g->f4344 = 5;
    factory_FactoryCameraInit_505af0(o);
    o->f050 = 3;
    o->f2C8 = -1;
    o->f2E6 = -1;
    o->f2E8 = -1;
    func_207E20(0x1FF, 0);
    func_207880(0x1F, 1);
}
