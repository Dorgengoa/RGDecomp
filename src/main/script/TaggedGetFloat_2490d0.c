#include "types.h"

/* Head of a 4-member BYTE-IDENTICAL group (28 B each): TaggedGetFloat_2490d0 /
   TaggedGetFloat_26a280 / ScriptSlotGetFloat_2cc9a0 / ScriptSlotGetFloat_334890.  A tagged scalar: when the tag
   is set the payload is already a float, otherwise it is an integer that has
   to be converted.  `lwc1` + `cvt.s.w` is mwcc's int-in-memory to float. */

typedef struct Tagged {
    s32 kind;
    union {
        f32 f;
        s32 i;
    } v;
} Tagged;

f32 TaggedGetFloat_2490d0(Tagged *t)
{
    if (t->kind == 0) {
        return (f32)t->v.i;
    }
    return t->v.f;
}
