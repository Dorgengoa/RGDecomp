/* rgp:protos */
#define RGP_SELF_ModelObjTexAnimIsPlayingByName_1ac490 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

typedef struct Link {
    struct Link *next;
    u8 pad4[0x10];
    s32 obj;
} Link;

s32 ModelObjTexAnimIsPlayingByName_1ac490(void *arg0, s32 arg1) {
    s32 idx;
    s32 o;
    s32 i;
    Link *p;

    for (p = *(Link **)((u8 *)arg0 + 0x220); p != NULL; p = p->next) {
        o = p->obj;
        if (o != 0) {
            i = TexAnimSeqFindByName_162e40(o, arg1);
            if (i >= 0) {
                *(volatile s32 *)&idx = i;
                goto found;
            }
        }
    }
    o = 0;
found:
    if (o != 0) {
        return TexAnimSeqIsPlaying_162a60(o, idx);
    }
    return 0;
}
