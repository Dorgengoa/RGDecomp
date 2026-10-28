/* rgp:protos */
#define RGP_SELF_EntryPosRecInit_32afd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct P_FUN_0032afd0 P_FUN_0032afd0;

typedef struct Obj_FUN_0032afd0 {
    s32 f00;
    s32 f04;
    s32 f08;
} Obj_FUN_0032afd0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void EntryPosRecInit_32afd0(Obj_FUN_0032afd0 *o, P_FUN_0032afd0 *p)
{
    EntryPosRecClear_32b0c0(o);
    Vec3Unpack_32b080(p, o, &o->f04, &o->f08);
    EntryPosRecSetEntry_32b0a0(o, EntryPosRecGetEntry_32b070(p));
}
