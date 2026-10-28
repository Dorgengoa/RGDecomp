#ifndef EVENT_VM_H
#define EVENT_VM_H

#include "types.h"

/* The event player, as the command handlers see it. Every handler reaches it
   the same way: a pointer parked in small data at gp-0x3248, whose +0x04 is
   the player EventPlayerUpdate_249a80 pushed there. */
typedef struct EventPlayer {
    u8 pad000[0x60];
    u8 sub60[0x408];   /* +0x60, what the 0x1e chain walks */
    s32 tick;          /* +0x468, bumped once per EventPlayerUpdate_249a80 */
} EventPlayer;

typedef struct EventContext {
    void *arg;              /* +0x00 */
    EventPlayer *player;    /* +0x04 */
} EventContext;

extern EventContext *gEventContext;

#endif
