#include "types.h"
/* normal 0x004F88B0 -- hides the 0x79 group: blanks its five 0x7A.. children
 * to fully transparent and clears the 0x3CC flag. */

typedef struct Obj { u8 pad000[0x3CC]; u8 f3CC; } Obj;

extern void func_290010(Obj *p, u16 id, s32 c, s32 d);
extern void func_2905B0(Obj *p, u16 id, f32 x, f32 y, f32 z, f32 w);

extern void normal_FieldHudLogClose_4f88b0(Obj *p);

void normal_FieldHudLogClose_4f88b0(Obj *p)
{
    u16 id;
    s32 i;

    func_290010(p, 0x79, 0, -1);
    id = 0x7A;
    for (i = 0; i < 5; i++) {
        func_2905B0(p, id, 0.0f, 0.0f, 0.0f, 0.0f);
        id++;
    }
    p->f3CC = 0;
}
