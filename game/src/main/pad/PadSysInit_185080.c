/* rgp:protos */
#define RGP_SELF_PadSysInit_185080 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct ee_sema {
    s32 count;                /* +0x0 */
    s32 max_count;            /* +0x4 */
    s32 init_count;           /* +0x8 */
    s32 wait_threads;         /* +0xC */
    s32 attr;                 /* +0x10 */
    s32 option;               /* +0x14 */
} ee_sema;

extern s32 CreateSema(ee_sema *);
extern s32 scePadInit(s32);
extern s32 D_0047E03C;

void PadSysInit_185080(void)
{
    ee_sema sema __attribute__((aligned(16)));
    s32 id;

    sema.init_count = 1;
    sema.max_count = 1;
    sema.option = 0;
    id = CreateSema(&sema);
    D_0047E03C = id;
    if (id >= 0) {
        scePadInit(0);
    }
}
