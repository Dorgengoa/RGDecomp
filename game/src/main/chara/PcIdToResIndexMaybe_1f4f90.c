/* rgp:protos */
#define RGP_SELF_PcIdToResIndexMaybe_1f4f90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of a NEGATIVE displacement off the argument: the result is an
   interior pointer -- a C++ base-class subobject, or the enclosing object of
   a member the caller holds -- so there is no struct to declare it in from
   this side.  Spelled as the byte arithmetic the reference shows. */

void *PcIdToResIndexMaybe_1f4f90(void *o)
{
    return (u8 *)o - 0x2930;
}
