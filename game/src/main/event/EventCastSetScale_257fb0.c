/* rgp:protos */
#define RGP_SELF_EventCastSetScale_257fb0 1
#define RGP_SELF_clr 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

typedef struct {
    s32 type;
    s32 pad4;
    s32 pad8;
    s32 obj;
} Ent;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline void clr(void *dst)
{
    u8 *p = (u8 *)dst;
    u32 n = 16;

    if (p != NULL) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
}

s32 EventCastSetScale_257fb0(Ent *arg0, s32 arg1, f32 a, f32 b, f32 c)
{
    Ent *e;
    s32 o;
    V4 v40 __attribute__((aligned(16)));
    V4 v30 __attribute__((aligned(16)));
    V4 v20 __attribute__((aligned(16)));
    V4 v10 __attribute__((aligned(16)));

    if (arg1 < 0 || arg1 >= 0x20) {
        return 0;
    }
    e = &arg0[arg1];
    switch (e->type) {
    case 0:
        o = e->obj;
        if (o == 0) {
            return 0;
        }
        clr(&v30);
        v30.x = a;
        v30.y = b;
        v30.z = c;
        ModelSetScale_150ff0(o, &v30);
        return 1;
    case 1:
        o = e->obj;
        if (o == 0) {
            return 0;
        }
        clr(&v20);
        v20.x = a;
        v20.y = b;
        v20.z = c;
        NodeSetScale_1865b0(o, &v20);
        return 1;
    case 2:
        o = e->obj;
        MenuWinSetScale_26c2f0(o, (float)a, (float)b);
        return 1;
    case 3:
        o = e->obj;
        clr(&v10);
        v10.x = a;
        v10.y = b;
        v10.z = c;
        FrameSetScale_14a2c0(o, &v10);
        return 1;
    case 4:
        o = e->obj;
        if (o == 0) {
            return 0;
        }
        v40.x = a;
        v40.y = b;
        v40.z = c;
        v40.w = 1.0f;
        NodeSetScale_1865b0(o, &v40);
        return 1;
    }
    return 0;
}
