#include "types.h"

class VC_2690a0 {
public:
    u8 pad0[0x1B0];
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
    virtual void f58();
};

extern "C" {

typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} Slot_2690a0;

extern void Sprintf_1343b8(void *arg0, void *arg1, s32 arg2);
extern void NameTableFreeGroup_158ac0(void *arg0, s32 arg1);
extern void *GetDrawCtxNameTable_15de40(void);
extern VC_2690a0 *ObjRecGetLiveObject_1c4a90(s32 arg0, s32 arg1);
extern void ObjRecReleaseResAndReset_1c4c70(s32 arg0, s32 arg1);
extern void strcpy(void *arg0, void *arg1);
extern u8 D_0045EF98[0x400];
extern s32 D_00481F78;
extern Slot_2690a0 D_004BDDB0[32];

s32 EvSceneObjRemove_2690a0(s32 arg0)
{
    u8 sp40[0x20];
    s32 i;
    VC_2690a0 *obj;
    u8 *w;
    Slot_2690a0 *s;

    obj = ObjRecGetLiveObject_1c4a90(D_00481F78, arg0);
    if (obj == NULL) {
        return 0;
    }
    w = (u8 *)GetDrawCtxNameTable_15de40();
    NameTableFreeGroup_158ac0(w, *(s32 *)((u8 *)obj + 0x4DC));
    Sprintf_1343b8(sp40, D_0045EF98, arg0);
    if ((arg0 >= 0x40) && (arg0 < 0x80)) {
        strcpy(w + 0x1E4, sp40);
    }
    if (obj != NULL) {
        obj->f58();
    }
    ObjRecReleaseResAndReset_1c4c70(D_00481F78, arg0);
    for (i = 0; i < 0x20; i++) {
        s = &D_004BDDB0[i];
        if (s->a == 0) {
            s32 *pb = &s->b;
            if (arg0 == *pb) {
                s->a = -1;
                *pb = -1;
                s->c = 1;
                s->d = 0;
                s->d = 0;
                s->d = 0;
                s->d = 0;
                s->d = 0;
            }
        }
    }
    if ((arg0 >= 0x40) && (arg0 < 0x80)) {
        w[0x1E4] = 0;
    }
    return 1;
}

}
