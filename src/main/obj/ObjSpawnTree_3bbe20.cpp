#include "types.h"
#undef NULL
#define NULL 0
class Lookup { public:
virtual void v8();
virtual void v12();
virtual void v16();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v32();
virtual void v36();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v52();
virtual void v56();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v72();
virtual void v76();
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v92();
virtual void v96();
virtual void v100();
virtual void v104();
virtual void v108();
virtual void *get(s64);
};
struct Node{u8 pad[0x18];s16 count;u16 pad2;void **children;};
extern "C" {

extern void *ObjSpawnFromDef_3bb5e0(void *, s32, s64);
extern s32 ObjDefCountTree_3bbfb0(void *, s64);
extern s32 ObjPoolCountFree_3bc080(void *);
extern s32 ObjIdCountFree_3bc120(void *);
extern s32 ObjIdFindFreeOrReclaim_3bc1a0(void *);

void *ObjSpawnTree_3bbe20(void *arg0, s64 arg1)
{
    void *t2;
    void *p4;
    void *vtbl;
    Node *found;
    s32 t19;
    s32 t18;
    s32 t2_3;
    s32 t2_4;
    void **arr;
s64 arg_h1;
    s32 i;
    void *child;
    void *sub;
    s16 slot;

    if (arg1 < 0) {
        return NULL;
    }
    p4 = *(void **)((u8 *)*(void **)((u8 *)arg0 + 0xC) + 0xC);
    vtbl = *(void **)p4;
    found = (Node *)((Lookup *)p4)->get((s64)(s16)arg1);
    if (found == NULL) {
        return NULL;
    }
    arg_h1 = arg1;
    t19 = ObjDefCountTree_3bbfb0(arg0, arg_h1);
    t18 = ObjIdCountFree_3bc120(arg0);
    t2_3 = ObjPoolCountFree_3bc080(arg0);
    if ((t18 < t19) || (t2_3 < t19)) return NULL;
    t2_4 = ObjIdFindFreeOrReclaim_3bc1a0(arg0);
    if (t2_4 < 0) {
        return NULL;
    }
    t2 = ObjSpawnFromDef_3bb5e0(arg0, t2_4, arg1);
    if (t2 == NULL) {
        return NULL;
    }
    arr = found->children;
    if (arr != NULL && found->count > 0) {
        i = 0;
        while (i < found->count) {
            child = *arr;
            if (child != NULL) {
                sub = ObjSpawnTree_3bbe20(arg0, *(s16*)((u8 *)child + 0x0));
                *(void **)((u8 *)sub + 0x3E0) = t2;
                *(s16 *)((u8 *)sub + 0x3E4) = *(s16 *)((u8 *)child + 0x84);
                slot = *(s16 *)((u8 *)t2 + 0x3E6);
                *(s16 *)((u8 *)t2 + 0x3E6) = slot + 1;
                *(void **)((u8 *)t2 + slot * 4 + 0x3E8) = sub;
                if (!(*(s16 *)((u8 *)t2 + 0x3E6) < 8)) {
                    break;
                }
            }
            i += 1;
            arr += 1;
        }
    }
    return t2;
}

}
