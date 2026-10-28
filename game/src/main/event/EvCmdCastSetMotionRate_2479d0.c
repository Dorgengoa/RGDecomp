/* rgp:protos */
#define RGP_SELF_EvCmdCastSetMotionRate_2479d0 1
#include "port/game_protos.h"
#line 1
#pragma opt_propagation off
#include "types.h"

typedef struct Node {
    struct Node *next;
    u8 pad4[8];
    s32 key;
    u8 ent[0x20];
} Node;

typedef struct {
    Node *head;
    Node *cur;
    s32 done;
} Iter;

typedef struct {
    s32 unk0;
    u8 *unk4;
} EvCtx;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern EvCtx *gEventContext;

s32 EvCmdCastSetMotionRate_2479d0(s64 * arg0)
{ __typeof__(arg0) rgp_entry_arg0 = arg0;
    s32 obj;
    Node *n;
    s32 k;
    u8 *ent;
    s32 r;
    s32 key;
    Iter *it;

    arg0++;
    it = (Iter *)(gEventContext->unk4 + 0x60);
    key = EventCastFindKeyByName_24bb50(it, ScriptGetCodeAddr_249050((void *)rgp_entry_arg0));
    if (it->cur != NULL) {
        r = -1;
    } else {
        it->cur = it->head;
        it->done = 0;
        r = 0;
    }
    if (r != 0) {
        ent = NULL;
    } else {
        goto next;
    loop:
        if (key == k) {
            goto found;
        }
    next:
            n = it->cur;
            if (n != NULL) {
                goto have;
            }
            ent = NULL;
            goto chk;
        have:
            k = n->key;
            ent = n->ent;
            n = n->next;
            it->cur = n;
            if (n == NULL) {
                it->done = 1;
            }
        chk:
        if (ent != NULL) {
            goto loop;
        }
    found:
        it->cur = NULL;
        it->done = 0;
    }
    if (ent == NULL) {
        return 0;
    }
    obj = ((s32)ObjRecGetLiveObject_1c4a90(gEventContext->unk0, *(s32 *)(ent + 0x1C)));
    if (obj == 0) {
        return 0;
    }
    ModelObjSetMotionRate_1add50(obj, 1, TaggedGetFloat_2490d0(arg0));
    return 1;
}
