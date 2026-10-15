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

/* Event native: byte-identical sibling of EvCmdCastSetFrameSwing1Maybe_241c40 (same shape, same
   normalized opcode stream) except the payload struct it fills is 8 bytes
   narrower before the float pair (a different EventSlot layout for a
   different event opcode) -- see EvCmdCastSetFrameSwing1Maybe_241c40 for the full explanation of
   the free-list pop and the argument-stream walk.

   ⚠ RESIDUE: same as EvCmdCastSetFrameSwing1Maybe_241c40, 1 word short (0x1A8 vs retail's 0x1AC),
   localised to the same free-list search loop rotation. See EvCmdCastSetFrameSwing1Maybe_241c40's
   header for the full writeup; nothing here differs from that analysis
   except the struct offsets. */

typedef struct EventNodeDF0 {
    struct EventNodeDF0 *next; /* +0x00 */
    u8 pad04[0x8];
    s32 id;                    /* +0x0C */
} EventNodeDF0;

typedef struct EventFreeListDF0 {
    EventNodeDF0 *base; /* +0x00, wrap-around/reset base */
    EventNodeDF0 *head; /* +0x04, current free-list head */
    s32 exhausted;       /* +0x08 */
} EventFreeListDF0;

typedef struct EventSlotDF0 {
    u8 pad000[0x1C];
    s32 unk1C;
    u8 pad20[0xD8 - 0x20];
    s32 unkD8;
    u8 pad0dc[0x100 - 0xDC];
    f32 unk100;
    u8 pad104[0x108 - 0x104];
    f32 unk108;
    f32 unk10C;
    u8 pad110[0x118 - 0x110];
    s32 unk118;
    u8 pad11c[0x120 - 0x11C];
    s32 unk120;
    u8 pad124[0x128 - 0x124];
    s32 unk128;
} EventSlotDF0;

s32 EvCmdCastSetFrameSwing0Maybe_241df0(Slot *args, s32 argc)
{
    s32 empty;
    EventNodeDF0 *node;
    EventNodeDF0 *next;
    EventSlotDF0 *slot;
    s32 wantId;
    s32 nodeId;
    EventFreeListDF0 *list;
    s32 id;
    void *camObj;
    f32 f;

    GetDrawCtxNameTable_15de40();

    list = (EventFreeListDF0 *)((u8 *)gEventContext->player + 0x60);
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
        goto next;
    check:
        if (wantId == nodeId) {
            goto done;
        }
    next:
        node = list->head;
        if (node == NULL) {
            slot = NULL;
        } else {
            nodeId = node->id;
            slot = (EventSlotDF0 *)((u8 *)node + 0x10);
            next = node->next;
            list->head = next;
            if (next == NULL) {
                list->exhausted = 1;
            }
        }
        if (slot != NULL) {
            goto check;
        }
    done:
        list->head = NULL;
        list->exhausted = 0;
    }

    slot->unkD8 = ScriptGetInt_2490f0(args++);

    if (argc >= 4) {
        f = TaggedGetFloat_2490d0(args++);
        slot->unk108 = f;
        f = -f;
        slot->unk10C = f;
        slot->unk100 = TaggedGetFloat_2490d0(args++);
    }

    if (argc >= 6) {
        camObj = ObjRecGetLiveObject_1c4a90(gEventContext->arg, slot->unk1C);
        if (camObj != NULL) {
            id = ScriptGetCodeAddr_249050(args++);
            slot->unk118 = ModelFindFrameIndexByName_151220(camObj, id);
            slot->unk120 = ScriptGetInt_2490f0(args++);
        }
    } else {
        slot->unk118 = -1;
        slot->unk120 = -1;
    }

    if (argc >= 7) {
        if (!(ScriptGetInt_2490f0(args) != 0)) {
            slot->unk10C = 0.0f;
        } else {
            slot->unk108 = 0.0f;
        }
    }
    slot->unk128 = 0;

    return 1;
}
