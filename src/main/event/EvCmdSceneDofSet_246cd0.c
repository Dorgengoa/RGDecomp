#include "types.h"

typedef struct {
    s32 a;
    f32 b;
    f32 c;
    f32 d;
    f32 e;
} Ev;

extern s32 ScriptGetInt_2490f0(s32);
extern f32 TaggedGetFloat_2490d0(s32);
extern void GameSceneDofSetParams_1cf1b0(void *, Ev *);
extern void GameSceneDofReset_1cf200(void *);
extern void **gEventContext;

static inline void init(Ev *e, s32 a, f32 b, s32 c, f32 d, s32 f) {
    e->a = a;
    e->b = b;
    e->c = c;
    e->d = d;
    e->e = f;
}

s32 EvCmdSceneDofSet_246cd0(s64 *arg0) {
    Ev ev;

    if (ScriptGetInt_2490f0((s32)arg0++) != 1) {
        GameSceneDofReset_1cf200(*gEventContext);
    } else {
        init(&ev, 1, 1.0f, 3000, 4000.0f, 5000);
        ev.b = TaggedGetFloat_2490d0((s32)arg0++);
        ev.a = ScriptGetInt_2490f0((s32)arg0++);
        ev.c = TaggedGetFloat_2490d0((s32)arg0++);
        ev.d = TaggedGetFloat_2490d0((s32)arg0++);
        ev.e = TaggedGetFloat_2490d0((s32)arg0);
        GameSceneDofSetParams_1cf1b0(*gEventContext, &ev);
    }
    return 1;
}
