/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageGetAbilityReq_5052d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005052D0 -- an EIGHT-BYTE float pair copied out of a record.
 *
 * ★ This is a STRUCT ASSIGNMENT, not two member assignments.  Retail is
 * `lwc1 $f1,0x444 / lwc1 $f0,0x448 / swc1 $f1,0x0 / swc1 $f0,0x4` -- both
 * loads first, and the FIRST-loaded value in $f1.  Twelve spellings of the
 * two-assignment form (n_oprobe, one build) all rank the loads the other way
 * round or interleave them; `*o = s->pair` produces retail's exact shape.
 * The recorded "a run of lwc1/swc1 is N assignments, not a copy" rule was
 * measured on a SIXTEEN-byte block, where mwcc proves qword alignment and
 * emits lq/sq.  At eight bytes there is no coalescing to avoid.
 * One of the 55 unnamed functions; see scripts/n_unnamed.py. */
typedef struct Pair {
    f32 x;
    f32 y;
} Pair;

typedef struct Src {
    u8   pad000[0x444];
    Pair f444;
} Src;

void normal_BtlChgPageGetAbilityReq_5052d0(Pair *o, Src *s)
{
    *o = s->f444;
}
