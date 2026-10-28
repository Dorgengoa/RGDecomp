/* rgp:protos */
#define RGP_SELF_CharaSysStateGetField28Related_3a3820 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Null-checked pointer chase; the likely branch carries -1 in its
   own delay slot.  Recipe proven on ModelResGetMeshCount_14c5c0. */

typedef struct Sub_FUN_003a3820 {
    u8 pad000[0x28];
    s32 val;         /* +0x28 */
} Sub_FUN_003a3820;

typedef struct Obj_FUN_003a3820 {
    u8 pad000[0x238];
    Sub_FUN_003a3820 *p;         /* +0x238 */
} Obj_FUN_003a3820;

s32 CharaSysStateGetField28Related_3a3820(Obj_FUN_003a3820 *o)
{
    Sub_FUN_003a3820 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return -1;
}
