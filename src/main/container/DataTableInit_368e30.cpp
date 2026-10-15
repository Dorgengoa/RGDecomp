/* PARKED: 1 round trip: 3 vtable calls through unk0; length 0x13C vs retail 0x11C (large gap). */
#include "types.h"
#undef NULL
#define NULL 0
class Self { public:
virtual void v8();
virtual void v12();
virtual void v16();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void setup();
virtual void v36();
virtual s32 default8();
virtual s32 default78();
virtual void v48();
virtual void v52();
virtual void v56();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v72();
virtual void v76();
virtual void v80();
virtual void v84();
virtual void v88();
virtual s32 finish();
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
        arg0->value = ((Self *)arg0)->default8();
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
