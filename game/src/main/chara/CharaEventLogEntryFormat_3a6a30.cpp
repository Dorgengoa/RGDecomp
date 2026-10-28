#include "types.h"

class Ent {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v16() { return VCM0(s32, 0x48); }
    
    
    
    
    
    char * v22() { return VCM0(char *, 0x60); }
    void v23(char * a0) { VCM(void, (void *, char *), 0x64, a0); }
};
class Tbl {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    u8 * get(s32 a0) { return VCM(u8 *, (void *, s32), 0x70, a0); }
};

typedef struct Key {
    s16 id;
    s16 sub;
    s16 arg;
} Key;

typedef struct Holder {
    u8 pad0[8];
    Tbl *tbl;
} Holder;

typedef struct Holder2 {
    u8 pad0[0x14];
    Tbl *tbl;
} Holder2;

typedef struct Db {
    u8 pad0[0x44];
    Holder *h44;
    Holder2 *h48;
} Db;

typedef struct Mgr {
    u8 pad0[8];
    Db *db;
} Mgr;

extern "C" {
void Sprintf_1343b8(char *, char *, char *, s32);
char *ScriptStrTableGet_2ccd90(s32);
Ent *ActorFindById_3eb870(Mgr *, s32);
char *strcpy(char *, const char *);
extern char D_00465E18[];
extern Mgr *D_004837B8;
}

extern "C" s32 CharaEventLogEntryFormat_3a6a30(Key *k, char *out)
{
    char buf[32] __attribute__((aligned(16)));
    char *s;
    Ent *e;
    u8 *r;
    u8 *r2;
    char *name;

    if (out == 0) {
        return 0;
    }
    *out = 0;
    if (k->sub == -2) {
        s = ScriptStrTableGet_2ccd90(k->id);
        if (s == 0) {
            return 0;
        }
        strcpy(out, s);
        return 1;
    }
    r = (u8 *)D_004837B8->db;
    e = ActorFindById_3eb870(D_004837B8, k->id);
    if (e == 0) {
        return 0;
    }
    if (k->sub == -1) {
        r2 = ((Db *)r)->h44->tbl->get(k->arg);
        if (r2 != 0) {
            if (*(char **)(r2 + 0x18) != 0) {
                strcpy(out, *(char **)(r2 + 0x18));
            }
        }
        return 1;
    }
    if (k->sub == 0x83) {
        strcpy(buf, e->v22());
    } else {
        e->v23(buf);
    }
    *out = 0;
    name = D_00465E18;
    r = ((Db *)r)->h48->tbl->get(k->sub);
    if (r != 0) {
        name = *(char **)(r + 0xC);
        if (e->v16() == 0 && *(char **)(r + 0x10) != 0) {
            name = *(char **)(r + 0x10);
        }
    }
    Sprintf_1343b8(out, name, buf, k->arg);
    return 1;
}
