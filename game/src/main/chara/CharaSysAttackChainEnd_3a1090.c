/* rgp:protos */
#define RGP_SELF_CharaSysAttackChainEnd_3a1090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Pass 29 -- a BITFIELD INSERT of zero.
   Offsets, shifts and access widths are read off the reference listing;
   the structs are STAND-INS, not recovered headers. */

typedef struct Obj {
    u8  pad[0x24C];
    u8  lo : 4;
    u8  b : 1;
    u8  hi : 3;
} Obj;

s32 CharaSysAttackChainEnd_3a1090(Obj *p)
{
    p->b = 0;
    return 1;
}
