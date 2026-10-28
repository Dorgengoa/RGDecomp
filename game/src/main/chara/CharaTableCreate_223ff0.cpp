#include "types.h"
#pragma opt_dead_assignments off

extern "C" void *MemStackHeapAlloc_14db10(void *heap, s32 kind, s32 n, s32 sz);
extern "C" void *MemStackNew_14e130(s32 sz, void *heap);
extern "C" void MemStackReturnToOwnerMaybe_14dad0(void *self);
extern "C" void MemStackHeapFree_14dcb0(void *self, void *p);
extern "C" void *CharaTableObjCtor_224190(void *obj);
extern "C" void CharaTableObjInit_224120(void *obj);
extern "C" void *SortedNodeGetData_21ff00(void *obj);
extern "C" s32 CharaTableClone_225490(void *a, void *buf, void *c, s32 m, void *e);

class Sub {
public:
    u8 pad0[0xC];
    VC_VPTR_MEMBER; s32 v8(void * a0) { return VCM(s32, (void *, void *), 0x8, a0); }
};

typedef struct Obj {
    u8 pad00[0x1C];
    u8 sub1C[0x8C - 0x1C];
    Sub sub8C;
} Obj;

extern "C" s32 CharaTableCreate_223ff0(Obj *o, void *c, s32 m)
{
    void *obj;
    void *buf;
    s32 x;
    if (c == 0 || m == 0) {
        obj = 0;
        goto done;
    }
    buf = MemStackHeapAlloc_14db10((void *)m, 2, 0, 0x40);
    if (buf != 0) {
        obj = MemStackNew_14e130(0x48, (void *)m);
        if (obj != 0) {
            obj = CharaTableObjCtor_224190(obj);
        }
        if (obj != 0) {
            CharaTableObjInit_224120(obj);
            if (CharaTableClone_225490(SortedNodeGetData_21ff00(obj), buf, c, m, o->sub1C) != 0) {
                MemStackReturnToOwnerMaybe_14dad0((void *)m);
                if (o->sub8C.v8(obj) != 0) {
                    buf = 0;
                    goto done;
                }
            }
        }
    }
    MemStackReturnToOwnerMaybe_14dad0((void *)m);
    MemStackHeapFree_14dcb0((void *)m, buf);
    obj = 0;
done:
    return (s32)obj;
}
