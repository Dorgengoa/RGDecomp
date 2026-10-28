/* rgp:protos */
#define RGP_SELF_TreasureBoxGetItemCount_33ad70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Null-checked pointer chase; the likely branch carries 0 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_0033ad70 {
    u8 pad000[0x10];
    s16 val;         /* +0x10 */
} Sub_FUN_0033ad70;

typedef struct Obj_FUN_0033ad70 {
    u8 pad000[0x68];
    Sub_FUN_0033ad70 *p;         /* +0x68 */
} Obj_FUN_0033ad70;

s16 TreasureBoxGetItemCount_33ad70(Obj_FUN_0033ad70 *o)
{
    Sub_FUN_0033ad70 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return 0;
}
