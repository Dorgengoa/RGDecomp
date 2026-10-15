#include "types.h"

extern s32 ScriptArgGetInt_302d70(s32);
extern s32 ScriptArgGetStr_302cb0(s32);
extern s32 GetObjNodeByName_1ce3a0(s32, s32, s32);

struct Obj0 {
    s32 m00;
};

s32 CharaCmdFrameShow_22dec0(struct Obj0 *p0, s32 p1, s32 argc)
{
    s32 a;
    s32 b;
    s32 o;

    if (argc != 3) {
        return 0;
    }
    a = ScriptArgGetInt_302d70(p1);
    b = ScriptArgGetStr_302cb0(p1 + 5);
    o = GetObjNodeByName_1ce3a0(p0->m00, a, b);
    if (o == 0) {
        return 1;
    }
    *(s8 *)(o + 0x24) = ScriptArgGetInt_302d70(p1 + 0xA);
    return 1;
}
