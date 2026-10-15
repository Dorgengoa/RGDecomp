#include "eekernel.h"
typedef unsigned int u32;
extern int func_075158(u32, u32 *, u32 *, u32 *);
/* C control flow with approved narrow CP0/TLB SDK macros. */
int KernelTlbMapPage_446470(u32 address)
{
    u32 entry[3];
    int index;
    int wired;
    u32 hi;
    if ((address & 0xfff) || (address != 0 && address < 0x100000)) return -1;
    index=func_075158(0x70004000, &entry[0], &entry[1], &entry[2]);
    if (index < 0) {
        if (address == 0) return 0;
        GetWired(index);
        SetWired(index+1);
        SyncPipeline();
    } else if (address == 0) {
        wired=(index-1)<<13;
        hi=0xe0010000+wired;
        GetWired(wired);
        SetWired(wired-1);
        ClearTLBEntry(index, hi);
        return 0;
    }
    entry[0]=0;
    entry[1]=((address & 0xfffff000)>>6)|0x1f;
    entry[2]=(((address+0x1000)&0xfffff000)>>6)|0x1f;
    hi=0x70004000;
    SetTLBIndex(index);
    WriteTLBFields(entry[0], hi, entry[1], entry[2]);
    return index;
}
