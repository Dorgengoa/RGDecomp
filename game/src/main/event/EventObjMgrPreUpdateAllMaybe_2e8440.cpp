/* rgp:protos */
#line 1
#include "types.h"

struct P2E84 { f32 f; s8 b; };

class VE2E8440 {
public:
    u8 pad000[0xDC];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    void v10(P2E84 * a0) { VCM(void, (void *, P2E84 *), 0x30, a0); }
};

extern "C" void MemStackHeapFree_14dcb0(s32, s32);
extern "C" f32 GameSceneGetTimeStep_1ceba0(s32);
extern "C" s32 GetGameMode_1f59c0(void);
extern "C" s32 GetCurrentScene_1f5be0(void);
extern "C" s32 EventRecGetHeapBuf_2e5720(void *);
extern "C" void DListRemove_42e4e0(void *, void *);
extern "C" void *DListGetHead_42ea60(void *);
extern "C" void *DListGetNext_42eb30(void *);

/* Inner list walk as an inline: its `base` param gets a late variable id, and
   temp_21 is a second web (first web = list head) so it numbers above base. */
static inline void UpdateList(u8 *self, u8 *base, P2E84 *p)
{
    u8 *var_18;
    u8 *temp_17;
    s32 temp_5;
    s32 temp_21;

    temp_21 = (s32)DListGetHead_42ea60(base + 0x50);
    var_18 = (u8 *)temp_21;
    while (var_18 != NULL) {
        temp_17 = (u8 *)DListGetNext_42eb30(var_18);
        ((VE2E8440 *)(var_18 + 0x10))->v10(p);
        temp_5 = *(s32 *)(var_18 + 0xE0);
        u8 *o = var_18 + 0x10;
        if (temp_5 & 0x01000000) {
            temp_21 = *(s32 *)(self + 0x150);
            if (var_18 != NULL) {
                if (temp_21 != 0) {
                    MemStackHeapFree_14dcb0(temp_21, EventRecGetHeapBuf_2e5720(o));
                }
                DListRemove_42e4e0(base + 0x50, var_18);
            }
        }
        var_18 = temp_17;
    }
}

extern "C" void EventObjMgrPreUpdateAllMaybe_2e8440(u8 *arg0)
{
    P2E84 sp78 __attribute__((aligned(16)));
    s32 var_19;

    sp78.f = GameSceneGetTimeStep_1ceba0(GetCurrentScene_1f5be0());
    sp78.b = (GetGameMode_1f59c0() != 6) && (GetGameMode_1f59c0() != 7);
    var_19 = 0;
    do {
        UpdateList(arg0, arg0 + var_19 * 0x10, &sp78);
        var_19 += 1;
    } while (var_19 < 0x10);
}
