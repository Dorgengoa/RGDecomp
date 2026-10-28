/* rgp:protos */
#define RGP_SELF_ItemGetEffect28Maybe_3d4ee0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Null-checked pointer chase; the likely branch carries 0 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_003d4ee0 {
    u8 pad000[0x28];
    s32 val;         /* +0x28 */
} Sub_FUN_003d4ee0;

typedef struct Obj_FUN_003d4ee0 {
    u8 pad000[0x10];
    Sub_FUN_003d4ee0 *p;         /* +0x10 */
} Obj_FUN_003d4ee0;

s32 ItemGetEffect28Maybe_3d4ee0(Obj_FUN_003d4ee0 *o)
{
    Sub_FUN_003d4ee0 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return 0;
}
