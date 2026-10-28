/* rgp:protos */
#define RGP_SELF_SoundBankStopAll_1bad70 1
#define RGP_SELF_apply 1
#define RGP_SELF_clear 1
#define RGP_SELF_get_entry 1
#define RGP_SELF_is_special 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 id;
    s16 pad[3];
} Slot;

typedef struct {
    s32 unk0;
    s32 a;
    s32 b;
    u8 pad[0x160 - 0xC];
    Slot slot[16];
    u8 pad2[0x1E0 - 0x1E0];
} Entry;

typedef struct {
    s32 key;
    s32 unk4;
    s32 used;
    u8 pad[0x90 - 0xC];
} Obj;

/*rgp*/
/*rgp*/
extern Entry D_0049EB10[];
extern Obj D_004A0910[];

static inline Entry *get_entry(s32 n) {
    if (n < 0 || n > 16) {
        return NULL;
    }
    return &D_0049EB10[n];
}

static inline s32 is_special(s32 n) {
    if (n == 0 || n == 11) {
        return 1;
    }
    return 0;
}

static inline void clear(s32 n) {
    Entry *e;
    s32 j;
    s32 key;
    e = get_entry(n);
    if (e != NULL) {
        key = e->a;
        for (j = 0; j < 32; j++) {
            Obj *o = &D_004A0910[j];
            if (o->used != 0 && key == o->key) {
                SoundSeqStop_1b5980(o);
            }
        }
    }
    e = get_entry(n);
    if (e != NULL) {
        for (j = 0; j < 16; j++) {
            e->slot[j].id = -1;
        }
    }
}


static inline void apply(s32 n) {
    Entry *e;
    if (n < 0) return;
    e = get_entry(n);
    if (e == NULL) return;
    if (e->a >= 0) {
        SoundSendCmd_1b6cc0(1, 1, e->a);
        SoundSendCmd_1b6cc0(2, 1, e->a);
    }
    if (e->b >= 0) {
        SoundSendCmd_1b6cc0(0xF, 1, e->b);
        if (e->a != e->b) {
            SoundSendCmd_1b6cc0(1, 1, e->b);
            SoundSendCmd_1b6cc0(2, 1, e->b);
        }
    }
}

void SoundBankStopAll_1bad70(s32 arg0) {
    s32 i;
    if (arg0 < 0) {
        for (i = 0; i <= 12; i++) {
            if (!is_special(arg0)) {
                clear(arg0);
                apply(i);
            }
        }
        return;
    }
    clear(arg0);
    apply(arg0);
}
