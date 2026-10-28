/* rgp:protos */
#line 1
/* PARKED: 1 round trip: 3 vtable calls through unk0; length 0x13C vs retail 0x11C (large gap). */
#include "types.h"
#undef NULL
#define NULL 0
class Self { public:
VC_VPTR_MEMBER;





void setup() { VCM0(void, 0x20); }

s32 default8(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x28, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
s32 default78() { return VCM0(s32, 0x2C); }











s32 finish() { return VCM0(s32, 0x5C); }
u32 pad4; s32 value;u32 padC;void *ptr;u8 buffer[0x58];u8 other[12];s16 count;
};
extern "C" {

extern void MemStackInit_14d810(void *, s32, s16);
extern void MemStackReset_14d830(void *);
extern s32 MemStackAllocQw_14d950(void *, s32);
extern void ArenaCtxInit_370610(void *, void *);

s32 DataTableInit_368e30(Self *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4)
{
    s32 temp_5;
    s32 temp_2;

    if (arg1 == NULL) {
        return 0;
    }
    if (arg2 != 0) {
        arg0->value = arg2;
    } else {
        arg0->value = ((Self *)arg0)->default8((int)(long)(arg1), (int)(long)(arg2), (int)(long)(arg3));
    }
    if ((arg3 != 0)) { if (arg4 > 0) {
        arg0->count = arg4;
    } else {
        arg0->count = ((Self *)arg0)->default78();
    } } else {
        arg0->count = 0;
    }
    temp_5 = arg0->count;
    if (temp_5 > 0) {
        temp_2 = MemStackAllocQw_14d950(arg1, temp_5);
        if (temp_2 == 0) {
            return 0;
        }
        MemStackInit_14d810(arg0->buffer, temp_2, arg0->count);
        MemStackReset_14d830(arg0->buffer);
        arg0->ptr = arg0->buffer;
    } else {
        arg0->count = 0;
        MemStackInit_14d810(arg0->buffer, 0, 0);
        arg0->ptr = arg1;
    }
    ArenaCtxInit_370610(arg0->other, arg0->ptr);
    ((Self *)arg0)->setup();
    return ((Self *)arg0)->finish();
}

}
