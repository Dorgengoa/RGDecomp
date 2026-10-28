/* rgp:protos */
#define RGP_SELF_normal_ThinkMenuGetResult_5219c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005219C0 -- a TWELVE-byte float triple copied out of small data.
 *
 * ★ Retail's shape (ascending loads into DESCENDING FPRs, then ascending
 * stores) is a STRUCT ASSIGNMENT, exactly like the eight-byte siblings
 * normal_TransMenuGetWarpRequest_518620 / normal_InsectEntryMenuGetResult_524ce0.  Twelve bytes is over mwcc's small-data
 * threshold, so `extern Vec3 D_00484948;` compiles to three `lui`/%lo pairs
 * and the unit is three words long.  ALL 36 permutations of the three load
 * statements x the three store statements of the memberwise form were
 * measured (scripts/n_oprobe.py) and the best is 2 bad -- the memberwise form
 * cannot produce this shape at all.
 *
 * ⇒ Take the address of the FIRST SCALAR into a pointer local and assign
 * through it.  The scalar is 4 bytes, so it keeps its `%gp_rel`, and the +4
 * and +8 offsets ride on that one relocation -- which is what retail has.
 * The pointer local is a RELOCATION control, like a gp array's declared size;
 * do not "simplify" it into an extern of the struct's own type.
 * One of the 55 unnamed functions; see scripts/n_unnamed.py. */
typedef struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
} Vec3;

extern f32 D_00484948;

void normal_ThinkMenuGetResult_5219c0(Vec3 *o)
{
    Vec3 *s;

    s = (Vec3 *)&D_00484948;
    *o = *s;
}
