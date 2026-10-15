#include "types.h"
#include "worldobj_cpp.h"

/* Command 0x05: event start / reset.

   Three passes over the world. First drain the player's own pending list;
   then, for every track the project reports, wire it up -- clear its four
   record slots, bind it, register it with the scene, and light its four
   display entries; then reset the 0x1C standing slots and the 0x20 slots from
   0xC0 up, and finally re-run whatever the map script left armed.

   Ã¢Ëœâ€¦ The four `ObjRecClearFlag2_1c3e40` calls per track use the SAME inlined accessor as
   EventPlayerInit_249c60 -- `track * 4 + 12 + n` for a track index in [0, 12), -1
   otherwise -- which is the strongest sign yet that the record table is a flat
   twelve-by-four array with a twelve-entry header in front of it.

   STATUS 88.21% on b210 (67.60 -> 78.15 -> 88.21). This file is C++ now: the
   last loop's body is three VIRTUAL calls and needs a real class. The
   conversion from C was measured SCORE-NEUTRAL (78.15 both sides), so nothing
   in the older C-mode work was paid for by it.

   The 2026-08-22 steps, each measured in order:
     C -> C++, no other change ............................. 78.15 (neutral)
     the three virtual calls via class WorldEntity ......... 83.86
     findByKey rotated so the compare block leads .......... 83.87 (see below)
     the FIFTH ObjRecClearFlag2_1c3e40 call, the one passing raw track  85.35
     inner loop bound as the NEXT track's base ............. 87.32
     DListGetNext_42eb30 takes p -- it was declared (void) ........ 88.21
     p + 0x10 hoisted into a local ......................... 88.21 (neutral)

   Ã¢Ëœâ€¦ Two of those are worth more than their percentages. The rotation scored
   +0.01% but took the longest mismatch run from 16 to 8 and removed three
   spurious likely-branches -- judge the diff, not the number. The hoist was
   flat and turned a 7-line run into pure register naming. */

typedef struct EventContext {
    void *arg;      /* +0x00 */
    void *player;   /* +0x04 */
} EventContext;

typedef struct Player {
    u8 pad000[0x60];
    u8 sub060[0x32C];
    s32 x38C;       /* +0x38C */
    u8 pad390[0xD8];
    s32 x468;       /* +0x468 */
    s32 x46C;       /* +0x46C */
} Player;

typedef struct World {
    u8 pad00[0xC];
    void *sub0C;    /* +0x0C */
    void *x10;      /* +0x10 */
    u8 pad14[0x4];
    void *list;     /* +0x18 */
} World;

/* player+0x60 is a CURSOR over a singly-linked list, not a node: head at
   +0x00, the walk position at +0x04, and a "ran off the end" flag at +0x08.
   Every link carries its key at +0x0C and its payload from +0x10. */
typedef struct Link {
    struct Link *next;  /* +0x00 */
    u8 pad04[0x8];
    s32 key;            /* +0x0C */
    u8 body[0x20];      /* +0x10 */
} Link;

typedef struct Item {
    u8 pad00[0x8];
    s32 kind;           /* +0x08, one of 1, 2, 3 */
    u8 pad0c[0x10];
    s32 x1C;            /* +0x1C */
} Item;

typedef struct Cursor {
    Link *head;         /* +0x00 */
    Link *cur;          /* +0x04 */
    s32 ended;          /* +0x08 */
} Cursor;

extern "C" {
extern EventContext *gEventContext;
extern const u8 D_0045EA80[];
extern const u8 D_0045EB08[];
extern const u8 D_0045EB10[];
extern s32 D_0047E7E4;

extern World *GetGameData_1fede0(void);
extern s32 TransporterWarpFlagTest_27a930(void);
extern void ScreenFadeIn_1cf740(void *arg, s32 zero);
extern s32 EventCastIdListGet_24b190(void *sub, s32 i);
extern void ObjRecSetFlag2_1c3e80(void *arg, s32 one, s32 x);
extern s32 PartyCountMembers_3c2010(void *list, s32 a, s32 b);
extern s32 PartyGetMemberId_3c2490(void *list, s32 i);
extern s32 EventCastFindKeyByObjId_24b1d0(void *sub, s32 track);
extern s32 EventCastIdListContains_24c1f0(void *sub, s32 entry);
extern void ObjRecClearFlag2_1c3e40(void *arg, s32 one, s32 record);
extern void EventCastObjPlayMotion_24b020(void *sub, s32 entry, const u8 *name, s32 zero);
extern void *GetActionMgr_1fdb50(void);
extern void *ActionMgrFindById_233b50(void *p, s32 track);
extern void CharaStopSwordTrails_214bc0(void *p);
extern void ParamTableSetAlpha_1cfb10(void *arg, s32 track, f32 one);
extern void ObjRecClearFlags_1c3dc0(void *arg, s32 one, s32 slot, s32 mask);
extern void GameSceneObjSetCBlurMaybe_1cf900(void *arg, s32 slot, s32 zero, f32 one);
extern void *ActionMgrGetCharaList_233b40(void *p);
extern void *DListGetHead_42ea60(void *p);
extern void *CharaGetActionTable_214cd0(void *p);
extern void *CharaGetId_214a80(void *p);
extern void ActCfgTableRunEvntByName_21f680(void *a, void *b, const u8 *name);
extern void *DListGetNext_42eb30(void *p);
extern void *GetEventObjMgr_2d1960(void);
extern void EventObjMgrSetAllDoorsClosed_2e8be0(void *p);
extern void EventObjMgrSuspend_27aef0(void);
extern void CameraSwitchTo2KeepView_309fa0(void);
extern void TaskEnableEventSceneSetMaybe_286f40(void);
extern void *LiveTalkGet_3216f0(void);
extern void LiveTalkCancel_3215c0(void *p);
extern void *ObjRecGetLiveObject_1c4a90(void *arg, s32 slot);
extern s32 ModelMotionEventReleaseHandlers_1b02b0(void *);
extern void GameSceneCBlurReset_2f1e20(void);
extern void EffectResetAll_2d8900(void);
extern void TaskSetEnabled_27c2a0(s32 zero, const u8 *name);
extern s32 StateFlagTest_3ccd70(void *p, s32 id);
extern void StateFlagSet_3ccb70(void *p, s32 id, s32 zero, s32 one);
extern s32 PartyCountReserve_3c1c20(void *list, s32 a, s32 b);
extern WorldEntity *PartyGetSlotChara_3c2fb0(void *list, s32 i);
extern void GameDataStatusClearAllPartial_3e6760(World *world);
extern void *GetDamagePopupList_2d9020(void);
extern void DamagePopupListClearBufs_2d2d90(void *p);
}


/* Reset the cursor to the head. Fails if a walk is already in progress -- the
   list carries exactly one, so a re-entrant find just reports "not found". */
static inline s32 beginWalk(Cursor *c)
{
    if (c->cur != 0) {
        return -1;
    }
    c->cur = c->head;
    c->ended = 0;
    return 0;
}

/* Find the payload whose link key matches. Both exits -- match and exhausted --
   close the cursor, and retail SHARES that tail: the match path jumps into it
   after its own `cur = 0`, so `ended = 0` is written once. The stepped-cursor
   read is inlined here rather than factored out because retail loads the key
   off the link BEFORE it forms the payload pointer.

   Ã¢Å¡Â  The negative-key guard is what makes the caller's loop carry a second
   `bltzl` on the same value its own loop test already rejected. */
static inline Item *findByKey(Cursor *c, s32 key)
{
    Link *e;
    Link *nx;
    Item *item;
    s32 k;

    if (beginWalk(c) != 0) return 0;
    while ((item = ((e = c->cur) == 0 ? 0 : (k = e->key, item = (Item *)e->body, nx = e->next, c->cur = nx, (nx == 0 ? (void)(c->ended = 1) : (void)0), item))) != 0) {
        if (key == k) {
            break;
        }
    }
    c->cur = 0;
    c->ended = 0;
    return item;
}

/* Same accessor as EventPlayerInit_249c60 -- a track outside [0, 12) has no record --
   and it takes the SAME spelling: the bounds guard returns -1 on its OWN so the
   -1 is the FALL-THROUGH and the compute is the branch target, which is retail's
   `bnel ok != 0 -> compute` with the `sll` in the likely delay slot. Sharing the
   `none:` label for BOTH guards (the older spelling) emitted `beq` here at all
   four sites. 88.21 -> 90.06%.

   Ã¢Å¡Â  The length moved the WRONG WAY, +1 word to -3, and that is not a regression:
   the correct polarity exposes a per-site scheduling deficit that the wrong one
   was masking. Retail fills the `track < 0` guard's delay slot with the NEXT
   argument's `lw $3, %gp_rel(gEventContext)` and so gets a plain `bltz` plus a
   two-word tail (`b merge` / `addiu $6, -1`); mwcc gives us `bltzl` with the -1
   duplicated instead, one word shorter, four times. It is the same
   fill-availability rule that makes EventPlayerInit_249c60's site 1 differ from its
   sites 2-4, reached from the other side -- there the filler is the previous
   call's `sw`. What makes mwcc hoist that load here is open. */
static inline s32 recordOf(s32 track, s32 which)
{
    u8 ok;
    if (track < 0) {
        goto none;
    }
    ok = track < 12;
    if (ok == 0) {
        return -1;
    }
    return track * 4 + 12 + which;
none:
    return -1;
}

#define REC(t, w) (((t) >= 0 && (t) < 12) ? (t) * 4 + 12 + (w) : -1)
static inline s32 recordOf2(s32 track, s32 which) { return (track >= 0 && track < 12) ? track * 4 + 12 + which : -1; }
static inline s32 recordOf3(s32 track, s32 which) { if (track >= 0 && track < 12) return track * 4 + 12 + which; return -1; }
extern "C" s32 EvCmdEventStartMaybe_248450(void)
{
    World *world;
  s32 i_w119;
    Cursor *sub;
    Player *player;
  s32 i_w55;
    Item *item;
    void *p;
    void *q;
    WorldEntity *ent;
    s32 count;
    s32 track;
    s32 entry;
    u32 i;
    s32 n;

    world = GetGameData_1fede0();
    player = (Player *)gEventContext->player;
    player->x468 = 0;
    player->x46C = 1;
    player->x38C = 1;
    sub = (Cursor *)player->sub060;

    if (TransporterWarpFlagTest_27a930() != 0) {
        ScreenFadeIn_1cf740(gEventContext->arg, 0);
    }

    /* Drain whatever the player still has queued: for every id the sub-machine
       reports, look the entry up and re-arm it if it is one of the three live
       kinds. */
    for (i = 0; ; i++) {
        s32 id = EventCastIdListGet_24b190(sub, i);
        if (id < 0) {
            break;
        }
        if (id < 0) {
            continue;
        }
        item = findByKey(sub, id);
        if (item != 0) {
            /* Ã¢Å¡Â  A switch, NOT `kind == 3 || kind == 2 || kind == 1` -- the
               || form is range-optimised into `addiu -1 / sltiu 3` and retail
               compares all three values separately. mwcc tests the cases in
               REVERSE source order, so ascending 1, 2, 3 here is what produces
               retail's 3, 2, 1 chain, and all three share ONE body. */
            switch (item->kind) {
            case 1:
            case 2:
            case 3:
                ObjRecSetFlag2_1c3e80(gEventContext->arg, 1, item->x1C);
                break;
            }
        }
    }

    count = PartyCountMembers_3c2010(world->list, 1, 1);
    for (i_w55 = 0; i_w55 < count; i_w55++) {
        track = PartyGetMemberId_3c2490(world->list, i_w55);
        entry = EventCastFindKeyByObjId_24b1d0(sub, track);
        if (EventCastIdListContains_24c1f0(sub, entry) == 0) {
            ObjRecClearFlag2_1c3e40(gEventContext->arg, 1, track);
            ObjRecClearFlag2_1c3e40(gEventContext->arg, 1, ((track >= 0 && track < 12) ? track * 4 + 12 + 0 : -1));
            ObjRecClearFlag2_1c3e40(gEventContext->arg, 1, ((track >= 0 && track < 12) ? track * 4 + 12 + 1 : -1));
            ObjRecClearFlag2_1c3e40(gEventContext->arg, 1, ((track >= 0 && track < 12) ? track * 4 + 12 + 2 : -1));
            ObjRecClearFlag2_1c3e40(gEventContext->arg, 1, ((track >= 0 && track < 12) ? track * 4 + 12 + 3 : -1));
        }
        EventCastObjPlayMotion_24b020(sub, entry, D_0045EB08, 0);
        { void *t_bt = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), track); p = t_bt; }
        if (p != 0) {
            CharaStopSwordTrails_214bc0(p);
        }
        ParamTableSetAlpha_1cfb10(gEventContext->arg, track, 1.0f);
        ObjRecClearFlags_1c3dc0(gEventContext->arg, 1, track, 0x2000000);
        GameSceneObjSetCBlurMaybe_1cf900(gEventContext->arg, track, 0, 1.0f);
        { s32 end = (track + 1) * 4 + 11; for (n = track * 4 + 12; n <= end; n++) {
            ObjRecClearFlags_1c3dc0(gEventContext->arg, 1, n, 0x2000000);
            GameSceneObjSetCBlurMaybe_1cf900(gEventContext->arg, n, 0, 1.0f);
        }}
    }

    p = DListGetHead_42ea60(ActionMgrGetCharaList_233b40(GetActionMgr_1fdb50()));
    while (p != 0) {
        void *sub = (u8 *)p + 0x10;
        q = CharaGetActionTable_214cd0(sub);
        if (sub != 0 && q != 0) {
            ActCfgTableRunEvntByName_21f680(q, CharaGetId_214a80(sub), D_0045EB10);
        }
        p = DListGetNext_42eb30(p);
    }

    EventObjMgrSetAllDoorsClosed_2e8be0(GetEventObjMgr_2d1960());
    EventObjMgrSuspend_27aef0();

    for (i_w55 = 0; i_w55 < 0x1C; i_w55++) {
        track = i_w55 + 0x80;
        entry = EventCastFindKeyByObjId_24b1d0(sub, track);
        if (EventCastIdListContains_24c1f0(sub, entry) == 0) {
            ObjRecClearFlag2_1c3e40(gEventContext->arg, 1, track);
        }
    }

    CameraSwitchTo2KeepView_309fa0();
    TaskEnableEventSceneSetMaybe_286f40();
    D_0047E7E4 = 1;
    LiveTalkCancel_3215c0(LiveTalkGet_3216f0());

    for (i_w55 = 0xC0; i_w55 <= 0xdf; i_w55++) {
        ObjRecClearFlag2_1c3e40(gEventContext->arg, 1, i_w55);
        p = ObjRecGetLiveObject_1c4a90(gEventContext->arg, i_w55);
        if (p != 0) {
            ModelMotionEventReleaseHandlers_1b02b0(p);
        }
    }

    GameSceneCBlurReset_2f1e20();
    EffectResetAll_2d8900();

    if (*(s16 *)((u8 *)world->sub0C + 0x1C) == 0) {
        TaskSetEnabled_27c2a0(0, D_0045EA80);
    }
    if (StateFlagTest_3ccd70(world->x10, 0x7E6) != 0) {
        { void *lst = world->list; n = PartyCountMembers_3c2010(lst, 1, 1) + PartyCountReserve_3c1c20(lst, 1, 1); }
        for (i_w119 = 0; i_w119 < n; i_w119++) {
            ent = PartyGetSlotChara_3c2fb0(world->list, i_w119);
            if (ent != 0) {
                if (ent->isActive() != 0) {
                    ent->rewind(0, 0.0f);
                }
                ent->reset(1, 1, 1);
            }
        }
        StateFlagSet_3ccb70(world->x10, 0x7E6, 0, 1);
    }
    if (StateFlagTest_3ccd70(world->x10, 0x7F1) == 0) {
        GameDataStatusClearAllPartial_3e6760(world);
    }
    if (!(!(StateFlagTest_3ccd70(world->x10, 0x7E3) == 0))) {
        DamagePopupListClearBufs_2d2d90(GetDamagePopupList_2d9020());
    } else {
        StateFlagSet_3ccb70(world->x10, 0x7E3, 0, 1);
    }
    return 1;
}

/* MATCH s88m (37 -> 0 bad). Closing levers, each measured:
   - ModelMotionEventReleaseHandlers_1b02b0 takes ONE argument (retail sets only a0).
   - world->list read once into a local for the 0x7E6 count sum.
   - the 0x1C and 0xC0 loops count with a SIGNED index (slti, not sltiu); the
     0x1C loop names `track = i + 0x80` once (one s3 home, recomputed in the
     bnel delay slot).
   - inner loop bound is `(track + 1) * 4 + 11` with `<=`, held in its OWN local
     `end` declared before the loop (the bound then takes the lower vreg: v1). */
