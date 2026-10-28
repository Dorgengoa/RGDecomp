/* rgp:protos */
#define RGP_SELF_HandleEntryInit_3f4160 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Sibling of HandleEntryInit_3f40a0, four bytes further in.  Same shape: a duplicated
   `sh -1` (0xE here), then the one-bit field at 0x24 assigned 0. */

typedef struct {
    s32 m00;
    s32 m04;
    s32 m08;
    s16 m0C;
    s16 m0E;
    s16 m10;
    s16 m12;
    s32 m14;
    s32 m18;
    s32 m1C;
    s16 m20;
    s16 m22;
    unsigned char b0 : 1;
} __attribute__((aligned(4))) S4160;

void HandleEntryInit_3f4160(S4160 *p)
{
    p->m00 = 0;
    p->m04 = 0;
    p->m0E = -1;
    p->m0E = -1;
    p->m0C = 0;
    p->m10 = -1;
    p->m14 = -1;
    p->m18 = 0;
    p->m1C = 0;
    p->m20 = 0;
    p->m22 = 0;
    p->b0 = 0;
}
