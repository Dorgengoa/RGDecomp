/* rgp:protos */
#define RGP_SELF_ItemGetStatusClassResist_3d3d90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Resolve a sub-object, then read a signed byte out of its 8-entry table at
   +0x09 through the asymmetric guard pair. */

typedef struct Owner10c {
    u8 pad000[0x10];
    void *sub;         /* +0x10 */
} Owner10c;

typedef struct Table09 {
    u8 pad000[0x9];
    s8 slot[1];        /* +0x09 */
} Table09;

/*rgp*/

s32 ItemGetStatusClassResist_3d3d90(Owner10c *o, s32 index)
{
    Table09 *t;
    u8 ok;

    t = ((Table09 *)ItemDefGetKind2Or3Data_40e140(o->sub));
    if (t == 0) {
        return (s8)(0);
    }
    if (index < 0) {
        goto none;
    }
    ok = index < 8;
    if (ok != 0) {
        goto found;
    }
none:
    return (s8)(0);
found:
    return (s8)(t->slot[index]);
}
