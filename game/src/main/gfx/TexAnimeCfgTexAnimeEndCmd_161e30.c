/* rgp:protos */
#define RGP_SELF_TexAnimeCfgTexAnimeEndCmd_161e30 1
#define RGP_SELF_find 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj00161E30 {
    s32 count;         /* 0x00 */
    u8 pad04[0xC4 - 0x04];
    s32 arr[1];         /* 0xC4 */
} Obj00161E30;

extern Obj00161E30 *D_0048112C;
extern s32 D_00481134;

static inline s32 find(Obj00161E30 *p)
{
    s32 i;
    for (i = 0; i < p->count; i++) {
        if (p->arr[i] == 0) {
            return i;
        }
    }
    return -1;
}

s32 TexAnimeCfgTexAnimeEndCmd_161e30(void)
{
    D_00481134 = -1;
    if (D_0048112C != NULL) {
        D_00481134 = find(D_0048112C);
    }
    return 1;
}
