#include "types.h"

extern f32 TaggedGetFloat_2490d0(void *);
extern s32 ScriptGetInt_2490f0(s32);
extern void Vec4VectorPushBack_249120(s32, void *);
extern f32 D_0047D288;
extern void *gEventContext;

typedef struct {
    s32 type;
    s32 val;
    f32 f;
} Ev;

s32 EvCmdCueStreamPlay_2414c0(s64 *arg0) {
    Ev ev;
    f32 f;
    s32 id;
    s32 t;

    id = ScriptGetInt_2490f0((s32)arg0++);
    f = 1.0f;
    if (*(s32 *)arg0 == 1) {
        f = TaggedGetFloat_2490d0(arg0);
    } else if (*(s32 *)arg0 == 0) {
        t = (s32)TaggedGetFloat_2490d0(arg0);
        if (t == 0) {
            f = 1.0f;
        }
        if (t == 1) {
            f = D_0047D288;
        }
    }
    ev.val = id;
    ev.type = 6;
    ev.f = f;
    Vec4VectorPushBack_249120(*(s32 *)((u8 *)gEventContext + 4), &ev);
    return 1;
}
