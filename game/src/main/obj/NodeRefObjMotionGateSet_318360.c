/* rgp:protos */
#define RGP_SELF_NodeRefObjMotionGateSet_318360 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad[0x682];
    s16 f682;
    u8 pad2[0x890 - 0x684];
    char f890[0x8B0 - 0x890];
    f32 f8B0;
    f32 f8B4;
} T_00318360;

extern char *strcpy(char *, const char *);

void NodeRefObjMotionGateSet_318360(T_00318360 *p, s32 n, char *s, f32 a, f32 b)
{
    p->f682 = n;
    if (s != 0) {
        if (s[0] != 0) {
            strcpy(p->f890, s);
        } else {
            p->f890[0] = 0;
        }
    } else {
        p->f890[0] = 0;
    }
    p->f8B0 = a;
    p->f8B4 = b;
    if (p->f8B0 < 0.0f) {
        p->f8B0 = 0.0f;
    }
}
