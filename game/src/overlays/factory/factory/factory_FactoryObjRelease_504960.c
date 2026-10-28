/* rgp:protos */
#define RGP_SELF_factory_FactoryObjRelease_504960 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00504960 -- reset the panel: rewind its three list
 * cursors to their heads, then re-run the constructor.
 * 76 bytes, 20 instructions, 0 conditional branches, 4 calls.
 *
 * * The three `func_201D10(&head, &tail)` pairs are the same three list bodies
 * `factory_FactoryObjReset_5049b0` hands to `func_14DFF0`, in the REVERSE order --
 * 0x304/0x35C, 0x238/0x290, 0x68/0xC0.
 */

typedef struct Panel {
    u8  pad000[0x68];
    u8  f068[0x58];
    s32 f0C0;
    u8  pad0C4[0x174];
    u8  f238[0x58];
    s32 f290;
    u8  pad294[0x70];
    u8  f304[0x58];
    s32 f35C;
} Panel;

/*rgp*/
/*rgp*/

void factory_FactoryObjRelease_504960(Panel *o)
{
    RecStackSlotRelease_201d10(o->f304, &o->f35C);
    RecStackSlotRelease_201d10(o->f238, &o->f290);
    RecStackSlotRelease_201d10(o->f068, &o->f0C0);
    factory_FactoryObjReset_5049b0(o);
}
