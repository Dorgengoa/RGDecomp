/* rgp:protos */
#line 1
#include "types.h"
#undef NULL
#define NULL 0
class Lookup { public:
VC_VPTR_MEMBER;

























void * get(s64 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(void *, (void *, s64, int, int), 0x70, a0, rgp_fwd2, rgp_fwd3); }
};
struct Node {u8 pad[0x18];s16 count;u16 pad2;u8 **children;};
extern "C" {

s32 ObjDefCountTree_3bbfb0(void *arg0, s64 arg1, int rgp_a2, int rgp_a3) {
    s16 *temp_2_2;
    s32 var_19;
u8 **var_18;
    s32 var_17;
    void **temp_4;
    Node *temp_2;

    if (arg1 < 0) {
        return 0;
    }
    temp_4 = *(void ***)((u8 *)(*(void **)((u8 *)arg0 + 0xC)) + 0xC);
    temp_2=(Node *)((Lookup *)temp_4)->get((s64)(s16)arg1, (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    if(temp_2 == NULL) return 0;
    {
        var_18 = temp_2->children;
        var_19 = 1;
        if ((var_18 != NULL) && (temp_2->count > 0)) {
            var_17 = 0;
            while (var_17 < temp_2->count) {
                temp_2_2 = *(s16 **)var_18;
                if (temp_2_2 != NULL) {
                    var_19 += ObjDefCountTree_3bbfb0(arg0, *temp_2_2, 0, 0);
                }
                var_17 += 1;
                var_18 += 1;
            }
        }
        return var_19;
    }
}

}
