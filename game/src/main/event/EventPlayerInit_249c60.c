/* rgp:protos */
#define RGP_SELF_EventPlayerInit_249c60 1
#define RGP_SELF_recordOf 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_propagation off

/* Event-player init -- vtable slot 8. Bring up the three sub-machines, reset
   the player's own state, and then build one four-entry record per track the
   project reports.

   The reset block is worth reading as documentation of the player's state: a
   queued-entry field set to -1 (idle, the same sense EventPlayerQueueEntry_250bd0 writes), a
   pair of counters cleared, an eight-slot table of -1, a wait counter of -1
   with its enable at 1, and two bytes at +0x474/+0x475 that start at 10 and 0.

   The four `ObjRecHasFlags6_1c3eb0` calls per track differ only in a constant -- 12, 13,
   14, 15 -- added to `track * 4`. That is one inlined accessor, four times:
   a track index below 0 or at/above 12 has no record and the argument is -1.

   MATCH: the accessor is a single ternary; the table reset is a do-while;
   the count comes through the dead loop index (`i = f(); count = i;`),
   which puts it in the s-reg retail uses. */

typedef struct PlayerSlot {
    void *a[4];          /* 16 bytes, based at +0x9A0 */
} PlayerSlot;

typedef struct EventPlayer {
    u8 pad000[0x60];
    u8 sub060[0x3C0];    /* +0x060 */
    s32 x420;            /* +0x420 */
    s32 x424;
    s32 x428;
    s32 x42C;
    s32 x430;            /* +0x430, -1 */
    u8 pad434[0x4];
    s32 x438;
    s32 x43C;            /* +0x43C, 1 */
    s32 x440;
    s32 table[8];        /* +0x444, all -1 */
    s32 x464;
    s32 x468;
    s32 x46C;
    u8 pad470[0x4];
    u8 x474;             /* +0x474, 10 */
    u8 x475;             /* +0x475, 0 */
    u8 pad476[0xE];
    s32 x484;            /* +0x484, -1 */
    s32 x488;            /* +0x488, 1 */
    u8 pad48c[0x14];
    u8 sub4A0[0x500];    /* +0x4A0 */
    PlayerSlot slots[12];/* +0x9A0 */
    s32 xA60;            /* +0xA60 */
} EventPlayer;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

typedef struct Project {
    u8 pad00[0x18];
    void *list;          /* +0x18 */
} Project;

/* A track index below zero, or at or past twelve, has no record. */
static inline s32 recordOf(s32 track, s32 which)
{
    return (track >= 0 && track < 12) ? track * 4 + 12 + which : -1;
}

void EventPlayerInit_249c60(EventPlayer *self)
{
    void *owner;
    Project *project;
    s32 count;
    s32 i;
    s32 m1;

    EventCastInit_24d310(self->sub060);
    EventSoundTableReset_249e60(self->sub4A0);
    self->x468 = 0;
    self->x42C = 0;
    EventVoiceListClear_24f4e0(&self->x420);

    m1 = -1;
    self->x420 = 0;
    self->x424 = 0;
    self->x428 = 0;
    self->x430 = m1;
    self->x438 = 0;
    self->x43C = 1;
    i = 0;
    do {
        self->table[i] = m1;
        i++;
    } while (i < 8);
    self->x464 = 0;
    self->x46C = 0;
    self->x484 = m1;
    self->x488 = 1;
    self->x474 = 10;
    self->x475 = 0;
    self->xA60 = 0;

    owner = GetCurrentScene_1f5be0();
    project = (Project *)GetGameData_1fede0();
    i = PartyCountMembers_3c2010(project->list, 1, 1);
    count = i;

    for (i = 0; i < count; i++) {
        s32 track = ((short)PartyGetMemberId_3c2490(project->list, i));

        self->slots[i].a[0] = ObjRecHasFlags6_1c3eb0(owner, 1, recordOf(track, 0));
        self->slots[i].a[1] = ObjRecHasFlags6_1c3eb0(owner, 1, recordOf(track, 1));
        self->slots[i].a[2] = ObjRecHasFlags6_1c3eb0(owner, 1, recordOf(track, 2));
        self->slots[i].a[3] = ObjRecHasFlags6_1c3eb0(owner, 1, recordOf(track, 3));
    }
}
