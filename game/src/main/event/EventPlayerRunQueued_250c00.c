/* rgp:protos */
#define RGP_SELF_EventPlayerRunQueued_250c00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Consume the queued entry point. With one queued, start the script at it and
   clear the queue; with none, just resume whatever is already running. The
   return is the same "is it live" sense EventPlayerIsIdle_250ba0 reports. */

typedef struct EventPlayer {
    u8 pad00[0x3C];
    s32 state;         /* +0x3C */
    u8 pad40[0x14];
    s32 queuedEntry;   /* +0x54, -1 = idle */
} EventPlayer;

/*rgp*/
/*rgp*/

s32 EventPlayerRunQueued_250c00(EventPlayer *self)
{
    s32 entry = self->queuedEntry;

    if (entry < 0 && self->state == 1) {
        return 1;
    }
    if (entry >= 0) {
        /* The pair is `sltu` then `xori 1`: a bool built from an inequality
           and THEN logically negated, in one expression. Storing the bool in
           a u8 first makes mwcc re-normalise it with a second sltu. */
        u8 idle = !(ScriptVmRunEntry_176940(self, entry) != 0);

        self->queuedEntry = -1;
        return idle;
    }
    ScriptVmResume_176ab0(self);
    return self->state;
}
