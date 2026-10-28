/* rgp:protos */
#define RGP_SELF_NodeObjFindChildByName_195040 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 strcmp(const char *, const char *);

void *NodeObjFindChildByName_195040(void *self, const char *key)
{
    void *node;
    void *p;
    void *rec;

    node = *(void **)((u8 *)self + 0x94);
    if (node == NULL || key == NULL) return NULL;
    for (p = node; p != NULL; p = *(void **)p) {
        rec = *(void **)((u8 *)p + 0x10);
        if (strcmp(key, *(const char **)((u8 *)rec + 0x74)) == 0) {
            return rec;
        }
    }
    return NULL;
}
