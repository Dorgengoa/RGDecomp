/* rgp:protos */
#line 1
#include "types.h"

class Base {
public:
    u8 pad0[0xD0];
    s32 flags;
    u8 padD4[8];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    void update(void *p) { VCM(void, (void *, void *), 0x34, p); }
};

class VObj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void notify(s32 x) { VCM(void, (void *, s32), 0x1A4, x); }
};

struct Obj {
    u8 pad0[0x10];
    Base base;
};

struct Pair {
    f32 f;
    u8 b;
};

extern "C" {
extern void MemStackHeapFree_14dcb0(s32, s32);
extern f32 GameSceneGetTimeStep_1ceba0(s32);
extern s32 GetGameMode_1f59c0(void);
extern s32 GetCurrentScene_1f5be0(void);
extern s32 GetGameData_1fede0(void);
extern s32 EventRecGetHeapBuf_2e5720(Base *);
extern s32 TargetRefGetId_2e7120(s32);
extern s32 TargetRefGetKind_2e7130(s32);
extern s32 EvObjGetTargetRef_2f9ca0(Base *);
extern VObj *ActorFindById_3eb870(s32, s32);
extern void DListRemove_42e4e0(void *, Obj *);
extern Obj *DListGetHead_42ea60(void *);
extern Obj *DListGetNext_42eb30(Obj *);
}

extern "C" void EventObjMgrUpdateAll_2e8290(u8 *arg0)
{
    Pair sp __attribute__((aligned(16)));
    s32 i;
    u8 *list;
    Obj *o;
    s32 fl;
    s32 t;
    Obj *next;
    s32 t2;
    VObj *vo;
    Base *bp;

    sp.f = GameSceneGetTimeStep_1ceba0(GetCurrentScene_1f5be0());
    sp.b = GetGameMode_1f59c0() != 6 && GetGameMode_1f59c0() != 7;
    for (i = 0; i < 16; i++) {
        list = arg0 + i * 16;
        for (o = DListGetHead_42ea60(list + 0x50); o != NULL; o = next) {
            next = DListGetNext_42eb30(o);
            o->base.update(&sp);
            fl = o->base.flags;
            bp = &o->base;
            if (fl & 0x01000000) {
                if (i == 5) {
                    t = EvObjGetTargetRef_2f9ca0(bp);
                    if (((short)TargetRefGetKind_2e7130(t)) == 5) {
                        t2 = GetGameData_1fede0();
                        vo = ActorFindById_3eb870(t2, ((short)TargetRefGetId_2e7120(t)));
                        if (vo != NULL) {
                            vo->notify(0x1F);
                        }
                    }
                }
                t2 = *(s32 *)(arg0 + 0x150);
                if (o != NULL) {
                    if (t2 != 0) {
                        MemStackHeapFree_14dcb0(t2, EventRecGetHeapBuf_2e5720(&o->base));
                    }
                    DListRemove_42e4e0(list + 0x50, o);
                }
            }
        }
    }
}
