/* rgp:protos */
#define RGP_SELF_insect_InsectBattleFadeSet_50e230 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x0050E230 -- 20 B / 5 words.  `addu $3, $5, $4` once, then three byte
 * stores off it at 0x5EF0 / 0x5EEF / 0x5EAC.  One index expression shared by
 * three parallel byte arrays, written in DESCENDING offset order because that
 * is the order retail issues them; the third store is a zero, not the value.
 *
 * The prototype is the one already settled by insect_InsectBattleObjInit_50e810.c:
 *   extern void insect_InsectBattleFadeSet_50e230(Ins *o, s32 a, s32 b);
 */

typedef struct Ins {
    u8 pad0000[0x5EAC];
    s8 f5EAC[0x5EEF - 0x5EAC];  /* +0x5EAC */
    s8 f5EEF[1];                /* +0x5EEF */
    s8 f5EF0[1];                /* +0x5EF0 */
} Ins;

void insect_InsectBattleFadeSet_50e230(Ins *o, s32 i, s32 v)
{
    o->f5EF0[i] = v;
    o->f5EEF[i] = v;
    o->f5EAC[i] = 0;
}
