/* rgp:protos */
#define RGP_SELF_Find23a2b0 1
#define RGP_SELF_SurfaceParamFindByTriAttr_23a2b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Table lookup: 0x10-byte entries keyed by s32 id@0, terminated by id < 0 (terminator returned on miss);
 * key = (s16)obj->+0x42. Plain C; formerly a hand transcription. */
typedef struct E23a2b0 { s32 id; u8 pad04[0xC]; } E23a2b0;
static inline E23a2b0 *Find23a2b0(E23a2b0 *e, s32 id)
{
    if (e == 0 || id < 0) return 0;
    while (e->id >= 0) {
        if (id == e->id) return e;
        e++;
    }
    return e;
}
void *SurfaceParamFindByTriAttr_23a2b0(void *p0, void *p1)
{
    if (p1 == 0) return 0;
    return Find23a2b0((E23a2b0 *)p0, *(s16 *)((u8 *)p1 + 0x42));
}
