// SPDX-License-Identifier: CC0-1.0
// tests/protos: the staged IconRec_3ae3e0.cpp with a real implementation of
// its (dummy) virtual class.  STAGED_ICONREC is the generated file's path.
#include <new>
#include STAGED_ICONREC

void O3ae3e0::v0() {}
void *O3ae3e0::v1(s32) { return 0; }

namespace {
struct D : O3ae3e0 {
    unsigned char rec[0x40];
    void v0() {}
    void *v1(s32 a) { rec[0x2C] = 0x30 + a; rec[0x2D] = 0x12; return rec; }
};
}

extern "C" int rg_test_vcall_make(void *buf)
{
    static_assert(sizeof(D) <= 256, "fixture object");
    new (buf) D();
    return 0;
}
