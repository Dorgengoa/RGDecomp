/* rgp:protos */
#define RGP_SELF_insect_InsectBattleRollHit_50fb10 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050FB10 -- 320 bytes.  A hit-chance roll: a base weight built from
 * the two actors' 0x18 stats and the attacker's 0x36 modifier, doubled when
 * the defender stands on a marked cell and halved when the attacker does. */

typedef struct Grid {
    u8 pad0000[0x13B];
    u8 f13B[7][5];                  /* +0x13B */
} Grid;

typedef struct Actor {
    u8 pad0000[0x18];
    s8 f18;                         /* +0x18 */
    u8 pad0019[0x36 - 0x19];
    s8 f36;                         /* +0x36 */
    u8 pad0037[0x38 - 0x37];
    s8 f38;                         /* +0x38 */
} Actor;

typedef struct Sys {
    u8   pad0000[0x4960];
    Grid f4960;                     /* +0x4960 */
} Sys;

/*rgp*/
/*rgp*/
/*rgp*/

s32 insect_InsectBattleRollHit_50fb10(Actor *a, Actor *b)
{
    s32   x;
    s32   y;
    s32   v;
    s32   t;
    Grid *g;

    t = b->f18 * b->f18 - a->f18 * a->f18;
    v = (0x55 - t) + (a->f36 * -5 + 10);
    g = &((Sys *)InsectBattleGet_31a8d0())->f4960;
    insect_InsectBoardFindPiece_4ee190(g, b, &x, &y);
    if ((g->f13B[y][x] & 8) != 0) {
        if (b->f38 != 0x12) {
            v = v * 2;
        }
    }
    insect_InsectBoardFindPiece_4ee190(g, a, &x, &y);
    if ((g->f13B[y][x] & 8) != 0) {
        if (a->f38 != 0x12) {
            v = v / 2;
        }
    }
    return Rand_133710() % 100 < v;
}
