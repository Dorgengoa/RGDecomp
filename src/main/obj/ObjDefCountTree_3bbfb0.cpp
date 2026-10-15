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
struct Node {u8 pad[0x18];s16 count;u16 pad2;u8 **children;};
extern "C" {

s32 ObjDefCountTree_3bbfb0(void *arg0, s64 arg1) {
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
    temp_2=(Node *)((Lookup *)temp_4)->get((s64)(s16)arg1);
    if(temp_2 == NULL) return 0;
    {
        var_18 = temp_2->children;
        var_19 = 1;
        if ((var_18 != NULL) && (temp_2->count > 0)) {
            var_17 = 0;
            while (var_17 < temp_2->count) {
                temp_2_2 = *(s16 **)var_18;
                if (temp_2_2 != NULL) {
                    var_19 += ObjDefCountTree_3bbfb0(arg0, *temp_2_2);
                }
                var_17 += 1;
                var_18 += 1;
            }
        }
        return var_19;
    }
}

}
