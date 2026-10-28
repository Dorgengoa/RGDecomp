/* rgp:protos */
#define RGP_SELF_RecStackPush_1c4240 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 used[0x5C0];
    s32 cur;
    s32 hist[0x40];
    s32 n;
} T001c4240;

/*rgp*/
/*rgp*/
/*rgp*/
char *strcpy(char *, const char *);
u32 strlen(const char *);

s32 RecStackPush_1c4240(T001c4240 *arg0, const char *arg1) {
    s32 id;
    s32 a;
    s32 b;

    id = RecStackFindFreeSlot_1c4420((int)arg0);
    if (id < 0) {
        return id;
    }
    {
        a = ((s32)RecStackGetSlot_1c4330(arg0, arg0->cur));
        b = ((s32)RecStackGetSlot_1c4330(arg0, id));
        if (a == 0 || b == 0) {
            return -1;
        }
        MemStackCarveFromParent_14d3b0(b, a, -1);
        if (arg1 != NULL && strlen(arg1) < 0x10) {
            strcpy((char *)b, arg1);
        }
        arg0->used[id] = 1;
        arg0->hist[arg0->n++] = id;
        arg0->cur = id;
    }
    return id;
}
