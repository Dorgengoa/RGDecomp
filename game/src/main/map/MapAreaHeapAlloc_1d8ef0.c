/* rgp:protos */
#define RGP_SELF_MapAreaHeapAlloc_1d8ef0 1
#define RGP_SELF_busy 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

typedef struct {
    s32 unk0;
    void *unk4;
} T1d8ef0_arg0;
static inline u8 busy(void *p) { return *(u32 *)((u8 *)p + 0x28) != 0; }

s32 MapAreaHeapAlloc_1d8ef0(T1d8ef0_arg0 *arg0)
{
    s32 r;
    s32 n;
    s32 m;

    arg0->unk0 = 0;
    if (arg0->unk4 == NULL) {
        return -1;
    }
    if (busy(arg0->unk4)) {
        return -1;
    }
    r = 0;
    n = AlignUp_1cacf0(MapDataGetHeapSize_1e7ba0((void *)arg0), 0x100);
    m = MapDataIsMemRev_1e7b90(arg0);
    switch (m) {
    case 0:
        r = MemStackHeapAllocFront_14dd10(arg0->unk4, n);
        break;
    case 1:
        r = MemStackHeapAllocBack_14dcf0(arg0->unk4, n);
        break;
    }
    return MapAreaHeapInit_1d8c50(arg0, r, n);
}
