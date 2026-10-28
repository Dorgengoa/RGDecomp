#include "types.h"

struct A500 { s32 a[0x140]; };
struct B0C0 { s32 b[0x30]; };
struct C140 { s32 c[0x50]; };
struct S19 { u8 pad0[0x180]; A500 m180; s16 h680; s16 h682; B0C0 m684; C140 m744; s16 h884; s16 h886; };

struct ObjF;

class VEF {
public:
    u8 pad000[0xB0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v25(s32 a0) { VCM(void, (void *, s32), 0x6C, a0); }
};

struct ObjF { VEF *unk0; s32 unk4; };
union HPunF { ObjF **p; s32 i; };

extern "C" void HandleHeapPoolAlloc_312880(ObjF **, s32, s32);
extern "C" s32 GetObjRefTable_313de0(void);
extern "C" s32 GetJudgeObjectHeap_313df0(void);
extern "C" s32 HandleRegistryRegister_3147e0(s32, ObjF **);
extern "C" void *NodeRefObjDefaultCtor_3190e0(void *);
extern "C" void JudgeObjectAssign_219710(void *, void *);


extern "C" s32 NodeRefObjCloneAndRegister_219500(S19 * arg0) {
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
    S19 *dst;

    HandleHeapPoolAlloc_312880(&sp34, GetJudgeObjectHeap_313df0(), 0x890);
    { HPunF hu; hu.i = (s32)&sp34; temp_2 = *hu.p; }
    sp3C = temp_2;
    if (temp_2 != NULL) {
        var_4 = (void *)temp_2->unk0;
    } else {
        var_4 = NULL;
    }
    if (var_4 != NULL) {
        var_4 = NodeRefObjDefaultCtor_3190e0(var_4);
    }
    if (var_4 == NULL) {
        return 0;
    }
    JudgeObjectAssign_219710(var_4, arg0);
    dst = (S19 *)var_4;
    dst->m180 = arg0->m180;
    dst->h680 = arg0->h680;
    dst->h682 = arg0->h682;
    dst->m684 = arg0->m684;
    dst->m744 = arg0->m744;
    dst->h884 = arg0->h884;
    dst->h886 = arg0->h886;
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
