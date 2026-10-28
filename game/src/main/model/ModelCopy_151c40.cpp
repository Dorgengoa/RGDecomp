/* rgp:protos */
#line 1
#include "types.h"
extern "C" {
typedef struct { f32 v[4]; } V4a_;

extern void ModelPartCopy_152070(void *, void *, int);

class VC_0 {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER; void f(s32 x0) { VCM(void, (void *, s32), 0x8, x0); }
};
class VC_1 {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    void f() { VCM0(void, 0xC); }
};
void ModelCopy_151c40(void *arg0, void *arg1, s32 arg2)
{
    void *vtbl;

    *(s32 *)((u8 *)arg1 + 0x0) = *(s32 *)((u8 *)arg0 + 0x0);
    *(s32 *)((u8 *)arg1 + 0x4) = *(s32 *)((u8 *)arg0 + 0x4);
    *(s32 *)((u8 *)arg1 + 0x104) = *(s32 *)((u8 *)arg0 + 0x104);
    *(s32 *)((u8 *)arg1 + 0x108) = *(s32 *)((u8 *)arg0 + 0x108);
    *(s32 *)((u8 *)arg1 + 0x10C) = *(s32 *)((u8 *)arg0 + 0x10C);
    *(s32 *)((u8 *)arg1 + 0x110) = *(s32 *)((u8 *)arg0 + 0x110);
    ModelPartCopy_152070((u8 *)arg0 + 0x120, (u8 *)arg1 + 0x120, (int)arg2);
    *(V4a_ *)((u8 *)arg1 + 0x180) = *(V4a_ *)((u8 *)arg0 + 0x180);
    *(V4a_ *)((u8 *)arg1 + 0x190) = *(V4a_ *)((u8 *)arg0 + 0x190);
    *(V4a_ *)((u8 *)arg1 + 0x1A0) = *(V4a_ *)((u8 *)arg0 + 0x1A0);
    vtbl = *(void **)((u8 *)arg1 + 0x1B0);
    if (arg2 != 0) {
        ((VC_0 *)(arg1))->f(arg2);
        return;
    }
    ((VC_1 *)(arg1))->f();
}

}
