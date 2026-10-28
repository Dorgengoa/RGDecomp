/* rgp:protos */
#define RGP_SELF_SoundSetListener_1b7fa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The two destinations are gp-relative 128-bit slots.  Declaring them as
   u128 (16 B) pushes them OUT of small data and costs a %hi/%lo pair each;
   declaring them s32 keeps the gp displacement and the cast supplies the sq. */

typedef rg_u128 u128;

extern s32 D_00481480;
extern s32 D_00481490;

void SoundSetListener_1b7fa0(u128 *p0, u128 *p1)
{
    *(u128 *)&D_00481480 = *p0;
    *(u128 *)&D_00481490 = *p1;
}
