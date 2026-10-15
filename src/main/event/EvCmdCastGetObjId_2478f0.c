#include "types.h"

typedef struct N2478 { struct N2478 *next; u8 pad4[8]; s32 unkC; u8 unk10[0xC]; s32 unk1C; } N2478;
typedef struct {
    N2478 *unk0;
    N2478 *unk4;
    s32 unk8;
} It2478;
static inline s32 it_begin(It2478 *it) {
    if (it->unk4 != NULL) {
        return -1;
    }
    it->unk4 = it->unk0;
    it->unk8 = 0;
    return 0;
}
static inline void *it_next(It2478 *it, s32 *key) {
    N2478 *n;
    N2478 *nx;
    void *p;
    n = it->unk4;
    if (n == NULL) {
        return NULL;
    }
    *key = n->unkC;
    p = &n->unk10;
    nx = n->next;
    it->unk4 = nx;
    if (nx == NULL) {
        it->unk8 = 1;
    }
    return p;
}
static inline void it_end(It2478 *it) {
    it->unk4 = NULL;
    it->unk8 = 0;
}

extern void ScriptSetRefInt_249030(s32, s32);
extern s32 ScriptGetCodeAddr_249050(void);
extern s32 EventCastFindKeyByName_24bb50(void *, s32);
extern u8 *gEventContext;
#pragma opt_propagation off
s32 EvCmdCastGetObjId_2478f0(s32 arg0)
{
    s32 key;
    s32 v;
    It2478 *it;
    void *p;

    arg0 += 8;
    it = (It2478 *)(*(u8 **)(gEventContext + 0x4) + 0x60);
    key = EventCastFindKeyByName_24bb50(it, ScriptGetCodeAddr_249050());
    if (it_begin(it) != 0) {
        p = NULL;
    } else {
        while ((p = it_next(it, &v)) != NULL) {
            if (key == v) {
                break;
            }
        }
        it_end(it);
    }
    if (p == NULL) {
        return 0;
    }
    ScriptSetRefInt_249030(arg0, *(s32 *)((u8 *)p + 0x1C));
    return 1;
}
