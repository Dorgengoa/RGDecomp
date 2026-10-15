#include "types.h"
#include "event_vm.h"
#include "vm_slot.h"

extern s32 GetDrawCtxNameTable_15de40(void);
extern s32 ScriptGetCodeAddr_249050(Slot *v);
extern s32 ScriptGetInt_2490f0(Slot *v);
extern f32 TaggedGetFloat_2490d0(Slot *v);
extern s32 EventCastFindKeyByName_24bb50(void *list, s32 id);
extern void *ObjRecGetLiveObject_1c4a90(void *table, s32 id);
extern s32 ModelFindFrameIndexByName_151220(void *obj, s32 id);

/* s41 agent10: MATCH (goto-into-do/while loop). */

typedef struct EventNodeC40 {
    struct EventNodeC40 *next; /* +0x00 */
    u8 pad04[0x8];
    s32 id;                    /* +0x0C */
} EventNodeC40;

typedef struct EventFreeListC40 {
    EventNodeC40 *base; /* +0x00, wrap-around/reset base */
    EventNodeC40 *head; /* +0x04, current free-list head */
    s32 exhausted;      /* +0x08 */
} EventFreeListC40;

typedef struct EventSlotC40 {
    u8 pad000[0x1C];
    s32 unk1C;
    u8 pad20[0xDC - 0x20];
    s32 unkDC;
    u8 pad0e0[0x104 - 0xE0];
    f32 unk104;
    u8 pad108[0x110 - 0x108];
    f32 unk110;
    f32 unk114;
    u8 pad118[0x11C - 0x118];
    s32 unk11C;
    u8 pad120[0x124 - 0x120];
    s32 unk124;
    u8 pad128[0x12C - 0x128];
    s32 unk12C;
} EventSlotC40;

s32 EvCmdCastSetFrameSwing1Maybe_241c40(Slot *args, s32 argc)
{
    s32 empty;
    EventNodeC40 *node;
    EventNodeC40 *next;
    EventSlotC40 *slot;
    s32 wantId;
    s32 nodeId;
    EventFreeListC40 *list;
    s32 id;
    void *camObj;
    f32 f;

    GetDrawCtxNameTable_15de40();

    list = (EventFreeListC40 *)((u8 *)gEventContext->player + 0x60);
    id = ScriptGetCodeAddr_249050(args++);
    wantId = EventCastFindKeyByName_24bb50(list, id);

    if (!(list->head == NULL)) {
        empty = -1;
    } else {
        empty = 0;
        list->head = list->base;
        list->exhausted = 0;
    }

    if (empty != 0) {
        slot = NULL;
    } else {
        goto test;
        do {
            if (wantId == nodeId) {
                break;
            }
        test:
            node = list->head;
            if (node == NULL) {
                slot = NULL;
            } else {
                nodeId = node->id;
                slot = (EventSlotC40 *)((u8 *)node + 0x10);
                next = node->next;
                list->head = next;
                if (next == NULL) {
                    list->exhausted = 1;
                }
            }
        } while (slot != NULL);
        list->head = NULL;
        list->exhausted = 0;
    }

    slot->unkDC = ScriptGetInt_2490f0(args++);

    if (argc >= 4) {
        f = TaggedGetFloat_2490d0(args++);
        slot->unk110 = f;
        f = -f;
        slot->unk114 = f;
        slot->unk104 = TaggedGetFloat_2490d0(args++);
    }

    if (argc >= 6) {
        camObj = ObjRecGetLiveObject_1c4a90(gEventContext->arg, slot->unk1C);
        if (camObj != NULL) {
            id = ScriptGetCodeAddr_249050(args++);
            slot->unk11C = ModelFindFrameIndexByName_151220(camObj, id);
            slot->unk124 = ScriptGetInt_2490f0(args++);
        }
    } else {
        slot->unk11C = -1;
        slot->unk124 = -1;
    }

    if (argc >= 7) {
        if (!(ScriptGetInt_2490f0(args) != 0)) {
            slot->unk114 = 0.0f;
        } else {
            slot->unk110 = 0.0f;
        }
    }
    slot->unk12C = 0;

    return 1;
}
