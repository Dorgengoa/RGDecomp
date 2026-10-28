/* rgp:protos */
#define RGP_SELF_ScriptSlotGetFloat_2cc9a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Member of the 4-member BYTE-IDENTICAL group headed by TaggedGetFloat_2490d0; the shape and
   every lever are documented there.  A tagged scalar: when the tag
   is set the payload is already a float, otherwise it is an integer that has
   to be converted.  `lwc1` + `cvt.s.w` is mwcc's int-in-memory to float. */

typedef struct Tagged {
    s32 kind;
    union {
        f32 f;
        s32 i;
    } v;
} Tagged;

f32 ScriptSlotGetFloat_2cc9a0(Tagged *t)
{
    if (t->kind == 0) {
        return (f32)t->v.i;
    }
    return t->v.f;
}
