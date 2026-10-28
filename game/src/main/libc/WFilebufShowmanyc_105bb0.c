/* rgp:protos */
#define RGP_SELF_WFilebufShowmanyc_105bb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct V00105BB0 {
    u8 pad[0x8];
    s32 *b;                   /* +0x8 */
    s32 *e;                   /* +0xC */
} V00105BB0;

s64 WFilebufShowmanyc_105bb0(V00105BB0 *v)
{
    return v->e - v->b;
}
