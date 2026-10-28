/* rgp:protos */
#define RGP_SELF_insect_InsectTeamTurnReset_513430 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00513430 -- 268 bytes.  The same five-slot 488-byte record scan as
 * 0x00513690, driving state changes instead of reading a flag. */

typedef struct Ent {
    u8 pad00[0x3D];
    s8 f3D;                         /* +0x3D */
    u8 pad3E[0x40 - 0x3E];
    s8 f40;                         /* +0x40 */
    u8 pad41[0x4F - 0x41];
    s8 f4F;                         /* +0x4F */
    u8 pad50[0x71 - 0x50];
    s8 f71;                         /* +0x71 */
    u8 pad72[0x1E8 - 0x72];
} Ent;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectTeamTurnReset_513430(Ent *a, s32 k)
{
    s32  i;
    Ent *e;

    for (i = 0; i < 5; i++) {
        e = &a[i];
        if (e != 0) {
            insect_InsectPieceClearStatus_513340(e, 0x1C);
            if (insect_InsectPieceTestStatus_513280(e, 1) == 0) {
                if (insect_InsectPieceTestStatus_513280(e, 4) == 0) {
                    insect_InsectPieceClearStatus_513340(e, 0x26);
                    insect_InsectPieceClearStatus_513340(e, 0x27);
                }
            }
            if (e->f4F > 0) {
                insect_InsectPieceClearStatus_513340(e, 0x28);
            }
            if (k != e->f71) {
                insect_InsectPieceTickStatusTimers_512cd0(e);
                if (e->f3D > 0 || e->f40 > 0) {
                    insect_InsectPieceSetStatus_5132d0(e, 0x1C);
                }
            }
        }
    }
}
