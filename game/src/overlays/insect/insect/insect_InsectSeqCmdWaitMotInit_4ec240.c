/* rgp:protos */
#define RGP_SELF_insect_InsectSeqCmdWaitMotInit_4ec240 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EC240 -- the f_setkind3 shape with a float 1.0f at +0x0C.
 * `lui $3, 0x3F80` + `sw` (not `mtc1`/`swc1`) is how mwcc stores a float
 * constant whose low half is zero. */
typedef struct InsectSlot {
    s32 kind;    /* +0x00 */
    s32 arg;     /* +0x04 */
    s32 f08;
    f32 f0C;     /* +0x0C */
} InsectSlot;

/*rgp*/

void insect_InsectSeqCmdWaitMotInit_4ec240(InsectSlot *s)
{
    insect_InsectSeqCmdInit_4ec490(s);
    s->kind = 0x7;
    s->arg = 0;
    s->f0C = 1.0f;
}
