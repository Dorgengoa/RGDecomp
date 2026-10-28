/* rgp:protos */
#define RGP_SELF_EventPlayerUpdate_249a80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The event-player tick: run the player's three sub-machines, publish a
   {arg, player} frame as the current event context for the duration, count
   down the wait, and step the script. Both tick counters advance once per
   call, which is why they read identically.

   The context frame is pushed and popped around the step, so a handler
   reached from here sees this player at gp-0x3248 and the previous one is
   restored on the way out. `prev = gEventContext ? gEventContext : NULL` is
   redundant as written and retail still emits the branch -- the same inlined
   C++ accessor shape as the null test in CameraApplyMotionList_171c40. */

typedef struct EventContext {
    void *arg;      /* +0x00 */
    void *player;   /* +0x04 */
} EventContext;

typedef struct EventPlayer {
    u8 sub000[0x60];
    u8 sub060[0x3C0];
    u8 sub420[0x64];
    s32 wait;       /* +0x484 */
    u8 pad488[0x18];
    u8 sub4A0[0x4];  /* +0x4A0 */
} EventPlayer;

extern EventContext *gEventContext;

/*rgp*/
/*rgp*/
/*rgp*/
extern void memset(void *dst, s32 fill, s32 len);
/*rgp*/
/*rgp*/

s32 EventPlayerUpdate_249a80(EventPlayer *player, void *arg)
{
    EventContext frame __attribute__((aligned(16)));
    EventContext *prev;
    s32 ret;

    EventCastLoadPollAll_24d2a0(&player->sub060, (void *)arg);
    EventVoiceTick_24f720(&player->sub420);
    EventSoundTableUpdateFades_249f40(&player->sub4A0);
    memset(&frame, 0, 8);

    frame.arg = arg;
    frame.player = player;
    prev = NULL;
    if (gEventContext != NULL) {
        prev = gEventContext;
    }
    gEventContext = &frame;

    if (player->wait > 0) {
        player->wait--;
    }
    if (player->wait == 0) {
        EventMenuWinInitAll_26b410();
        return 0;
    }

    ret = EventPlayerRunQueued_250c00(player);
    gEventContext = prev;
    *(s32 *)((u8 *)player + 0x468) += 1;
    *(s32 *)((u8 *)player + 0x470) += 1;
    return ret;
}
