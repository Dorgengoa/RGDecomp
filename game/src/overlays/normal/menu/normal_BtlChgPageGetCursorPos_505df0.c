/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageGetCursorPos_505df0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00505DF0 -- reads back the row's two callback words. */
typedef struct Obj { u8 pad00[0x60]; s32 f60; s32 f64; } Obj;
extern s32 normal_BtlChgPageGetCursorPos_505df0(Obj *p, s32 *a, s32 *b);
s32 normal_BtlChgPageGetCursorPos_505df0(Obj *p, s32 *a, s32 *b)
{
    *a = p->f60;
    *b = p->f64;
    return 1;
}
