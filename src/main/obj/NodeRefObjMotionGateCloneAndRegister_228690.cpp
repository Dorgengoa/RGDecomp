#include "types.h"

struct B32 { u8 b[0x20]; };
struct S22 { u8 pad0[0x890]; B32 nm; f32 f8B0; f32 f8B4; };

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
extern "C" void *NodeRefObjMotionGateDefaultCtor_318440(void *);
extern "C" void NodeRefObjAssign_2287f0(void *, void *);


extern "C" s32 NodeRefObjMotionGateCloneAndRegister_228690(S22 * arg0) {
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
    S22 *dst;

    HandleHeapPoolAlloc_312880(&sp34, GetJudgeObjectHeap_313df0(), 0x8C0);
    { HPunF hu; hu.i = (s32)&sp34; temp_2 = *hu.p; }
    sp3C = temp_2;
    if (temp_2 != NULL) {
        var_4 = (void *)temp_2->unk0;
    } else {
        var_4 = NULL;
    }
    if (var_4 != NULL) {
        var_4 = NodeRefObjMotionGateDefaultCtor_318440(var_4);
    }
    if (var_4 == NULL) {
        return 0;
    }
    NodeRefObjAssign_2287f0(var_4, arg0);
    dst = (S22 *)var_4;
    dst->nm = arg0->nm;
    dst->f8B0 = arg0->f8B0;
    dst->f8B4 = arg0->f8B4;
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
