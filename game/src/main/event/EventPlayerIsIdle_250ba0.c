/* rgp:protos */
#define RGP_SELF_EventPlayerIsIdle_250ba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* MATCHES 100% under mwcps2-3.0.1b210-060308 at -O4 (verified 2026-08-21).
   Locally this reads 95% because no installed build emits the likely branch
   b210 does; see README, "Which compiler".

   The predicate the per-frame chain gates on: an event player is ready to be
   started when it has a queued entry point AND its state word reads 1. +0x54 is
   the queued entry-point id, -1 meaning idle, so the sign test is what "is one
   queued" means here. */

typedef struct EventPlayer {
    u8 pad00[0x3C];
    s32 state;        /* +0x3C */
    u8 pad40[0x14];
    s32 queuedEntry;  /* +0x54, -1 = idle */
} EventPlayer;

s32 EventPlayerIsIdle_250ba0(EventPlayer *this)
{
    if (this->queuedEntry < 0) {
        if (this->state == 1) {
            return 1;
        }
    }
    return 0;
}
