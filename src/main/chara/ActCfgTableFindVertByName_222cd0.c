#include "types.h"

typedef struct E {
    void *m00;
    u8    pad04[0x18 - 4];
} E;

typedef struct Self {
    u8   pad00[0x12];
    s16  m12;
    u8   pad14[0x34 - 0x14];
    E   *list;
    u8   padb[0x66 - (0x34 + 4)];
    s16  count;
} Self;

extern void *GetActionMgr_1fdb50(void);
extern Self *ActionMgrGetGlobalTable_234850(void *w);
extern s32   StrEqualNonNull_1ca6c0(const char *key, void *name);

E *ActCfgTableFindVertByName_222cd0(Self *self, const char *key)
{
    Self *p;
    E *e;
    s32 i;

    if (key == NULL) {
        return NULL;
    }
    if (self->m12 != 0x7FFF && key[0] == '#') {
        p = ActionMgrGetGlobalTable_234850(GetActionMgr_1fdb50());
        if (p != NULL) {
            return ActCfgTableFindVertByName_222cd0(p, key);
        }
        return NULL;
    }
    e = self->list;
    if (e == NULL) {
        return NULL;
    }
    i = 0;
    while (i < self->count) {
        if (StrEqualNonNull_1ca6c0(key, e->m00) != 0) {
            return e;
        }
        i++;
        e++;
    }
    return NULL;
}
