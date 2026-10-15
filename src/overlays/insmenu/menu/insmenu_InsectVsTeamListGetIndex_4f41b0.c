#include "types.h"

/* insmenu 0x004F41B0 (124 bytes) -- the caption's Y: the sum of the widget's
 * two extents, or the scene's own value when the lab scene is running. */

typedef struct Kind Kind;
struct Kind {
    u8  pad00[8];
    s32 field08;
};

typedef struct Ctx Ctx;
struct Ctx {
    u8   pad0000[0x1188];
    Kind *field1188;
};

typedef struct Handle Handle;
struct Handle {
    u8  pad00[0x24];
    Ctx *field24;
};

typedef struct Widget Widget;
struct Widget {
    u8  pad00[0x16];
    s16 field16;
    u8  pad18[2];
    s16 field1A;
};

typedef struct Scene Scene;
struct Scene {
    u8  pad0000[0x4EE];
    s16 field04EE;
};

extern const u8 D_004FA1A0[];

extern Handle *func_1FEDE0(void);
extern void func_430580(void *a, s32 b);
extern Widget *func_28EA40(const void *a, s32 id);
extern Scene *insmenu_InsectVsGetSaveCtx_4f3850(void);

s32 insmenu_InsectVsTeamListGetIndex_4f41b0(void)
{
    Handle *h;
    Widget *w;
    s32 y;

    h = func_1FEDE0();
    func_430580(h->field24, 0);
    w = func_28EA40(D_004FA1A0, 0x88BD);
    y = 0;
    if (w != 0) {
        y = w->field1A + w->field16;
    }
    if (h->field24->field1188->field08 == 0x278) {
        y = insmenu_InsectVsGetSaveCtx_4f3850()->field04EE;
    }
    return y;
}
