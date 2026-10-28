/* rgp:protos */
#define RGP_SELF_IosFail_1a1f40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* the extra `andi 0xFF` is a u8-typed INTERMEDIATE, not the field width. */
typedef struct P1A1F40 { u8 pad000[0x3A]; u8 m3A; } P1A1F40;
u8 IosFail_1a1f40(P1A1F40 *p)
{
    u8 t;

    t = p->m3A & 5;
    return t != 0;
}
