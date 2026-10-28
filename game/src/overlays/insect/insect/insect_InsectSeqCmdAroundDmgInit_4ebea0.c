/* rgp:protos */
#define RGP_SELF_insect_InsectSeqCmdAroundDmgInit_4ebea0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EBEA0 -- the f_setkind shape.  The `kind` constant lands in $4
 * and the byte flag in $3, which is the documented "two adjacent stores: source
 * order does not set STORE order but does set which value gets which register"
 * lever -- the flag is assigned first. */
typedef struct InsectSlot {
    s32 kind; s32 arg; s32 f08; u8 f0C; u8 f0D; s16 f0E; u8 f10;
} InsectSlot;
/*rgp*/
void insect_InsectSeqCmdAroundDmgInit_4ebea0(InsectSlot *s)
{
    insect_InsectSeqCmdInit_4ec490(s);
    s->kind = 0x19;
    s->arg = 0;
    s->f0C = 1;
    s->f0E = 0;
    s->f10 = 0;
}
