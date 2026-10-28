/* rgp:protos */
#line 1
#include "types.h"
#undef NULL
#define NULL 0

class Obj80 {
public:
    u8 pad000[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v58() { VCM0(void, 0x58); }
};

struct ObjA4 {
    u8 pad[0x28];
    s32 x28;
    inline bool busy() { return x28 != 0; }
};

extern "C" {
void MemStackHeapFree_14dcb0(void *, s32);
void NameTableFreeGroup_158ac0(s32, s32);
void DrawCtxVif1HandlerStop_15dc40(void);
s32 GetDrawCtxNameTable_15de40(void);
void ModelObjExEffectsStopAll_1b0870(void *);
void EffectEntryReleaseNode_2da6c0(void *, s32, int, int);
void * EffectEntryReset_2dc550(void *);
}

extern "C" void * EffectEntryRelease_2da580(u8 *arg0, Obj80 *arg1)
{
    u8 *cur;
    u8 *next;
    s32 *rec;
    s32 v;
    s16 id;
    ObjA4 *a4;

    if (*(u8 **)(arg0 + 4) == NULL) {
        *(u8 **)(arg0 + 4) = *(u8 **)(arg0 + 0);
        *(s32 *)(arg0 + 8) = 0;
    }
    for (;;) {
        cur = *(u8 **)(arg0 + 4);
        if (cur == NULL) {
            rec = NULL;
        } else {
            rec = (s32 *)(cur + 0x10);
            next = *(u8 **)cur;
            *(u8 **)(arg0 + 4) = next;
            if (next == NULL) {
                *(s32 *)(arg0 + 8) = 1;
            }
        }
        if (rec == NULL) {
            break;
        }
        EffectEntryReleaseNode_2da6c0(arg0, *rec, 0, 0);
    }
    *(u8 **)(arg0 + 4) = NULL;
    *(s32 *)(arg0 + 8) = 0;
    DrawCtxVif1HandlerStop_15dc40();
    if (arg1 != NULL) {
        arg1 = *(Obj80 **)(arg0 + 0x80);
        if (arg1 != NULL) {
            ModelObjExEffectsStopAll_1b0870(arg1);
            arg1->v58();
        }
    }
    v = GetDrawCtxNameTable_15de40();
    id = *(s16 *)(arg0 + 0x14);
    if (id >= 0x2DB && id < 0x30B) {
        NameTableFreeGroup_158ac0(v, id);
    }
    a4 = *(ObjA4 **)(arg0 + 0xA4);
    if (a4 != NULL && (a4->x28 != 0) == 0) {
        if (*(s32 *)(arg0 + 0x84) != 0) {
            MemStackHeapFree_14dcb0(a4, *(s32 *)(arg0 + 0x84));
        }
        if (*(s32 *)(arg0 + 0x8C) != 0) {
            MemStackHeapFree_14dcb0(*(u8 **)(arg0 + 0xA4), *(s32 *)(arg0 + 0x8C));
        }
    }
    return EffectEntryReset_2dc550(arg0);
}
