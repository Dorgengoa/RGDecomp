#include "types.h"

struct W4 { f32 w[4]; };
struct T460 { s32 t[0x118]; };
struct S2E { u8 pad0[0x1A0]; W4 v0; W4 v1; s32 i1C0; f32 f1C4; f32 f1C8; s32 i1CC; T460 tail; };

struct ObjF;

class VEF {
public:
    u8 pad000[0xB0];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void v25(s32);
};

struct ObjF { VEF *unk0; s32 unk4; };
union HPunF { ObjF **p; s32 i; };

extern "C" void HandleHeapPoolAlloc_312880(ObjF **, s32, s32);
extern "C" s32 GetObjRefTable_313de0(void);
extern "C" s32 GetJudgeObjectHeap_313df0(void);
extern "C" s32 HandleRegistryRegister_3147e0(s32, ObjF **);
extern "C" void *ProjectileCopyCtor_317f00(void *);
extern "C" void AttackObjBaseAssign_22e710(void *, void *);


extern "C" s32 ProjectileCloneAndRegister_22e560(S2E * arg0) {
    ObjF *volatile sp3C;
    ObjF *volatile sp38;
    ObjF *sp34;
    ObjF *temp_2;
    void *var_4;
    s32 temp_16;
    s32 rc;
    VEF *q;
    ObjF *p;
    ObjF *p2;
    S2E *dst;

    HandleHeapPoolAlloc_312880(&sp34, GetJudgeObjectHeap_313df0(), 0x630);
    { HPunF hu; hu.i = (s32)&sp34; temp_2 = *hu.p; }
    sp3C = temp_2;
    if (temp_2 != NULL) {
        var_4 = (void *)temp_2->unk0;
    } else {
        var_4 = NULL;
    }
    if (var_4 != NULL) {
        var_4 = ProjectileCopyCtor_317f00(var_4);
    }
    if (var_4 == NULL) {
        return 0;
    }
    AttackObjBaseAssign_22e710(var_4, arg0);
    dst = (S2E *)var_4;
    dst->v0 = arg0->v0;
    dst->v1 = arg0->v1;
    dst->i1C0 = arg0->i1C0;
    dst->f1C4 = arg0->f1C4;
    dst->f1C8 = arg0->f1C8;
    dst->i1CC = arg0->i1CC;
    dst->tail = arg0->tail;
    sp38 = sp3C;
    temp_16 = HandleRegistryRegister_3147e0(GetObjRefTable_313de0(), (ObjF **)&sp38);
    p = sp38;
    if (((p != NULL) ^ 1) != 0) {
        goto done;
    }
    if (p != NULL) {
        p->unk4 = p->unk4 - 1;
    }
    p2 = sp38;
    rc = (p2 != NULL) ? p2->unk4 : 0;
    if ((rc == 0) && (p2 != NULL)) {
        q = p2->unk0;
        if (q != NULL) {
            q->v25(-1);
        }
        sp38->unk4 = 0;
        sp38 = (ObjF *)NULL;
    }
    sp38 = (ObjF *)NULL;
done:
    return temp_16;
}
