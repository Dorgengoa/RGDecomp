#include "types.h"

/* Call the setup below, then return the object itself.
   Callee arity is the read-before-write scan in build/w1_arity.py
   (transitive through untouched jals, rotated-loop reads rejected);
   parameters past the first are PASS-THROUGH and typed s32 as a
   placeholder -- the bytes cannot see their types, only their count. */

typedef struct Obj_FUN_003fd2a0 Obj_FUN_003fd2a0;

extern void RankingEntryInit_3fdad0(Obj_FUN_003fd2a0 *);

Obj_FUN_003fd2a0 *RankingEntryCtor_3fd2a0(Obj_FUN_003fd2a0 *o)
{
    RankingEntryInit_3fdad0(o);
    return o;
}
