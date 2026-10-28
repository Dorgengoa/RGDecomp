/* rgp:protos */
#define RGP_SELF_SoundStreamSlotRestoreResumePoint_1bcfa0 1
#define RGP_SELF_get0 1
#define RGP_SELF_get1 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern s32 D_004814F0;
extern u8 D_004A25F0[];

static inline u8 *get0(s32 i)
{
    if (i < 0 || i >= 4) {
        return NULL;
    }
    return D_004A25F0 + i * 0x128;
}

static inline u8 *get1(s32 i)
{
    u8 *p = get0(i);
    if (p == NULL || (&D_004814F0)[i] == 0) {
        return NULL;
    }
    return p;
}

s32 SoundStreamSlotRestoreResumePoint_1bcfa0(s32 arg0, s32 arg1)
{
    u8 *p = get1(arg0);

    return p != NULL ? (SoundStreamSlotQueueResumePoint_1be5a0(p,arg1) & 0xFF) : 0;
}
