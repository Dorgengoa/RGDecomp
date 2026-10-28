/* rgp:protos */
#define RGP_SELF_SoundStreamQueueOpen_1c0360 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
s32 PollSema(s32);
s32 SignalSema(s32);
s32 WaitSema(s32);
s8 *strcpy(s8 *, const s8 *);
u32 strlen(const s8 *);

struct Obj {
    u8 pad0[0x3C];
    volatile s32 sema3C;
    volatile s32 sema40;
    u8 pad44[4];
    u8 busy;
    u8 pad49[3];
    s32 head;
    s32 tail;
    u8 flags[16];
    s8 *buf;
};
struct Lock {
    volatile s32 *s;
};

u8 SoundStreamQueueOpen_1c0360(struct Obj *obj, const s8 *src)
{
    u8 ret;
    volatile s32 *t;
    s32 v;
    volatile struct Lock lk __attribute__((aligned(16)));

    {
        t = &obj->sema40;
        v = *t;
        lk.s = t;
        if (v > 0) {
            WaitSema(*t);
        }
        if (obj->buf == 0) {
            t = lk.s;
            if (*t > 0) {
                SignalSema(*t);
            }
            return 0;
        }
        if (*obj->buf != 0) {
            t = lk.s;
            if (*t > 0) {
                SignalSema(*t);
            }
            return 0;
        }
        if (strlen(src) >= 0x100) {
            t = lk.s;
            if (*t > 0) {
                SignalSema(*t);
            }
            return 0;
        }
        strcpy(obj->buf, src);
        t = lk.s;
        if (*t > 0) {
            SignalSema(*t);
        }
    }
    if (obj->sema40 > 0) {
        WaitSema(obj->sema40);
    }
    if (obj->busy == 0 && obj->head == obj->tail) {
        ret = 0;
    } else {
        ret = 1;
        obj->flags[obj->tail] = 1;
        obj->tail = (obj->tail + 1) & 0xF;
        obj->busy = 0;
    }
    if (obj->sema40 > 0) {
        SignalSema(obj->sema40);
    }
    if (ret) {
        s32 s = obj->sema3C;
        if (s > 0 && PollSema(s) < 0) {
            SignalSema(obj->sema3C);
        }
    }
    SoundStreamQueueFill_1bfdf0(obj);
    return ret;
}
