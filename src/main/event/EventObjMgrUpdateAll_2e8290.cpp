#include "types.h"

class Base {
public:
    u8 pad0[0xD0];
    s32 flags;
    u8 padD4[8];
    virtual void v000();
    virtual void v001();
    virtual void v002();
    virtual void v003();
    virtual void v004();
    virtual void v005();
    virtual void v006();
    virtual void v007();
    virtual void v008();
    virtual void v009();
    virtual void v010();
    virtual void update(void *p);
};

class VObj {
public:
    virtual void v000();
    virtual void v001();
    virtual void v002();
    virtual void v003();
    virtual void v004();
    virtual void v005();
    virtual void v006();
    virtual void v007();
    virtual void v008();
    virtual void v009();
    virtual void v010();
    virtual void v011();
    virtual void v012();
    virtual void v013();
    virtual void v014();
    virtual void v015();
    virtual void v016();
    virtual void v017();
    virtual void v018();
    virtual void v019();
    virtual void v020();
    virtual void v021();
    virtual void v022();
    virtual void v023();
    virtual void v024();
    virtual void v025();
    virtual void v026();
    virtual void v027();
    virtual void v028();
    virtual void v029();
    virtual void v030();
    virtual void v031();
    virtual void v032();
    virtual void v033();
    virtual void v034();
    virtual void v035();
    virtual void v036();
    virtual void v037();
    virtual void v038();
    virtual void v039();
    virtual void v040();
    virtual void v041();
    virtual void v042();
    virtual void v043();
    virtual void v044();
    virtual void v045();
    virtual void v046();
    virtual void v047();
    virtual void v048();
    virtual void v049();
    virtual void v050();
    virtual void v051();
    virtual void v052();
    virtual void v053();
    virtual void v054();
    virtual void v055();
    virtual void v056();
    virtual void v057();
    virtual void v058();
    virtual void v059();
    virtual void v060();
    virtual void v061();
    virtual void v062();
    virtual void v063();
    virtual void v064();
    virtual void v065();
    virtual void v066();
    virtual void v067();
    virtual void v068();
    virtual void v069();
    virtual void v070();
    virtual void v071();
    virtual void v072();
    virtual void v073();
    virtual void v074();
    virtual void v075();
    virtual void v076();
    virtual void v077();
    virtual void v078();
    virtual void v079();
    virtual void v080();
    virtual void v081();
    virtual void v082();
    virtual void v083();
    virtual void v084();
    virtual void v085();
    virtual void v086();
    virtual void v087();
    virtual void v088();
    virtual void v089();
    virtual void v090();
    virtual void v091();
    virtual void v092();
    virtual void v093();
    virtual void v094();
    virtual void v095();
    virtual void v096();
    virtual void v097();
    virtual void v098();
    virtual void v099();
    virtual void v100();
    virtual void v101();
    virtual void v102();
    virtual void notify(s32 x);
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
extern s32 EvObjGetTargetRef_2f9ca0(Base *, s32);
extern VObj *ActorFindById_3eb870(s32, s32);
extern void DListRemove_42e4e0(void *, Obj *);
extern Obj *DListGetHead_42ea60(void *);
extern Obj *DListGetNext_42eb30(Obj *);
}

extern "C" void EventObjMgrUpdateAll_2e8290(u8 *arg0)
{
    Pair sp;
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
                    t = EvObjGetTargetRef_2f9ca0(bp, fl);
                    if (TargetRefGetKind_2e7130(t) == 5) {
                        t2 = GetGameData_1fede0();
                        vo = ActorFindById_3eb870(t2, TargetRefGetId_2e7120(t));
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
