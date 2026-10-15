#include "types.h"

/* lane N4 family: ScriptCmdCharaGetMp_32d1e0 / ScriptCmdCharaGetHp_32d2b0 (208 B each).
   C++: two virtual calls through a vptr at 0x00, slots 0xF0 and 0x128. */

typedef struct { s32 a; s32 b; } Arg;

class VE {
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
    virtual s32 vA();
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
    virtual s32 vB(s32);
};

extern "C" void *GetGameData_1fede0(void);
extern "C" s32 ScriptSlotGetInt_3348b0(Arg *);
extern "C" void *CharaMgrPoolFindById_3a8c60(void *, s32);
extern "C" void ScriptSlotStoreIntRef_3347f0(Arg *, s32);

extern "C" s32 ScriptCmdCharaGetHp_32d2b0(Arg *p, s32 kind)
{
    s32 r1;
    s32 r2;
    void *a;
    VE *o;
    s32 t;

    a = GetGameData_1fede0();
    t = ScriptSlotGetInt_3348b0(p++);
    r1 = 0;
    r2 = 0;
    o = (VE *)CharaMgrPoolFindById_3a8c60(*(void **)((u8 *)a + 0x14), t);
    if (o != 0) {
        r1 = o->vA();
        r2 = o->vB(1);
    }
    ScriptSlotStoreIntRef_3347f0(p++, r1);
    if (kind == 3) {
        ScriptSlotStoreIntRef_3347f0(p, r2);
    }
    return 1;
}
