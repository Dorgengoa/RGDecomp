/* rgp:protos */
#define RGP_SELF_normal_LeaderHudSetField98Related_506a40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00506A40 -- the `dsll32/dsra32 ..,16` is mwcc re-extending an s16
 * PARAMETER for the compare; the store keeps the raw incoming $5. */
typedef struct Obj { u8 pad00[0x98]; s16 f98; } Obj;
extern s32 normal_LeaderHudSetField98Related_506a40(Obj *p, s16 v);
s32 normal_LeaderHudSetField98Related_506a40(Obj *p, s16 v)
{
    if (v < 0) {
        p->f98 = 0;
        return 1;
    }
    p->f98 = v;
    return 0;
}
