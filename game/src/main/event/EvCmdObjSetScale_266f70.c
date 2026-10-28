/* rgp:protos */
#define RGP_SELF_EvCmdObjSetScale_266f70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Slot { s32 type; union { s32 i; f32 f; } u; } Slot;
typedef struct V4 { f32 x, y, z, w; } V4;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdObjSetScale_266f70(Slot *arg0)
{
    V4 v __attribute__((aligned(16)));
    u8 *q;
    u32 n;
    s32 id;
    s32 h;
    f32 x;
    f32 y;
    f32 z;

    id = ScriptGetInt_26a2a0(arg0++);
    x = TaggedGetFloat_26a280(arg0++);
    y = TaggedGetFloat_26a280(arg0++);
    z = TaggedGetFloat_26a280(arg0++);
    h = ((s32)EventSceneGetObj_2676e0(id));
    if (h == 0) {
        return 0;
    }
    q = (u8 *)&v;
    n = 0x10;
    if (q != NULL) {
        do {
            *q = 0;
            n--;
            q++;
        } while (n != 0);
    }
    v.x = x;
    v.y = y;
    v.z = z;
    ModelSetScale_150ff0(h, &v);
    return 1;
}
