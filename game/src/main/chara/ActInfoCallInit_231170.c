/* rgp:protos */
#define RGP_SELF_ActInfoCallInit_231170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* $7 is a 64-bit argument: `dsll32/dsra32` is (s32)y and `dsrl32` then
   dsll32/dsra32 is (s32)(y >> 32).
   The last guard arm is the `bnel`+`b` shape, which the ActInfoClsnLinInitFull_230d30 sweep
   measured to come only from an `||` early return. */

typedef struct {
    char *m00;
    s32 m04;
    s32 m08;
    s32 m0C;
} Rec;

void ActInfoCallInit_231170(Rec *o, char *s, s32 x, u64 y)
{
    o->m00 = 0;
    o->m08 = 0;
    o->m0C = 0;
    if (s == 0 || s[0] == 0 || y == 0) {
        return;
    }
    o->m00 = s;
    o->m04 = x;
    o->m08 = (s32)y;
    o->m0C = (s32)(y >> 32);
}
