/* rgp:protos */
#define RGP_SELF_insect_InsectHelpGetEntry_510c00 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00510C00 -- 172 bytes.  Index fix-up: two feature queries, each of
 * which shifts the caller's slot index past a hole. */

typedef struct Ent {
    u8 pad0000[0x10];
} Ent;

typedef struct Own {
    u8   pad0000[0x8];
    Ent *f8;                        /* +0x08 */
    s32  fC;                        /* +0x0C */
} Own;

typedef struct Sys {
    u8  pad0000[0x10];
    s32 f10;                        /* +0x10 */
} Sys;

/*rgp*/
/*rgp*/

Ent *insect_InsectHelpGetEntry_510c00(Own *o, s32 i)
{
    Sys *s;

    s = ((Sys *)GetGameData_1fede0());
    if (i == -1) {
        return &o->f8[o->fC];
    }
    if (StateFlagTest_3ccd70(s->f10, 0x186) == 0) {
        if (i >= 4) {
            i++;
        }
    }
    if (StateFlagTest_3ccd70(s->f10, 0x187) == 0) {
        if (i >= 0x16) {
            i++;
        }
    }
    return &o->f8[i];
}
