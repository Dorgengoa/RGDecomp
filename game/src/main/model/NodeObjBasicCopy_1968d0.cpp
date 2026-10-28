/* rgp:protos */
#line 1
/* main s27m: CLOSED -- typed members (raw offsets CSE every address into callee-saved
   regs across the call) + the NodeAssign_193f60 struct copied memberwise as `base`. */
#include "types.h"

typedef struct { s32 a; s32 b; } P_193F60;
typedef struct {
    P_193F60 p[6];
    s16 h0;
    s16 h1;
    s32 w0;
    s32 w1;
    s32 arr[9];
    f32 f0;
    f32 f1;
} S_193F60;

extern "C" void NodeRelated_185f50(void);
extern "C" void NodeInit_185f60(void *);

struct D_1968D0 {
    S_193F60 base;
    s32 pad68;
    s32 m6C;
    s32 m70;
    s32 m74;
    s32 m78;
    s32 m7C;
    s32 m80;
    f32 m84;
    f32 m88;
    s32 m8C;
};

extern "C" void NodeObjBasicCopy_1968d0(D_1968D0 *arg0, D_1968D0 *arg1)
{
    NodeInit_185f60(arg1);
    arg1->m6C = 0;
    arg1->m70 = 0;
    arg1->m78 = 0;
    arg1->m74 = 0;
    arg1->m7C = 0;
    arg1->m80 = 0;
    arg1->m8C = 0;
    arg1->m88 = 0.0f;
    arg1->m84 = 0.0f;
    arg1->base = arg0->base;
    NodeRelated_185f50();
    arg1->m6C = arg0->m6C;
    arg1->m70 = arg0->m70;
    arg1->m74 = arg0->m74;
    arg1->m78 = arg0->m78;
    arg1->m8C = arg0->m8C;
    arg1->m84 = arg0->m84;
    arg1->m88 = arg0->m88;
    arg1->m7C = arg0->m7C;
    arg1->m80 = arg0->m80;
}
