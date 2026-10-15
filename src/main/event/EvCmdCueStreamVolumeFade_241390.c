#include "types.h"

typedef struct { u8 b[8]; } E8;
f32 TaggedGetFloat_2490d0(E8 *);
s32 ScriptGetInt_2490f0(E8 *);
s32 Vec4VectorPushBack_249120(s32, void *);
extern f32 D_0047D288;
extern u8 *gEventContext;

typedef struct { s32 a; s32 b; f32 c; s32 d; } Ev;

s32 EvCmdCueStreamVolumeFade_241390(E8 *arg0) {
    Ev sp40;
    s32 id;
    s32 t;
    s32 k;
    s32 n;
    f32 f;

    id = ScriptGetInt_2490f0(arg0++);
    f = 1.0f;
    t = *(s32 *)arg0;
    if (t == 1) {
        f = TaggedGetFloat_2490d0(arg0++);
    } else if (t == 0) {
        k = (s32)TaggedGetFloat_2490d0(arg0++);
        if (k == 0) f = 1.0f;
        if (k == 1) f = D_0047D288;
    }
    n = (s32)(f32)ScriptGetInt_2490f0(arg0);
    sp40.a = 8;
    sp40.b = id;
    sp40.c = f;
    sp40.d = n;
    Vec4VectorPushBack_249120(*(s32 *)(gEventContext + 4), &sp40);
    return 1;
}
