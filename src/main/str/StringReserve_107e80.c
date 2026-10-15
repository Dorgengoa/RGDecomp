#pragma opt_unpromotetypes on
#pragma opt_treetransformation off
#pragma opt_arithtransformation off
#include "types.h"
#pragma cplusplus on
#pragma exceptions on
#pragma inline_depth(8)
extern "C" u32 strlen(const char *);
extern "C" char *strcpy(char *, const char *);
extern "C" void *memcpy(void *,const void *,u32);
extern "C" void *memset(void *,int,u32);
extern "C" void *memmove(void *,const void *,u32);
extern "C" void *OperatorNewArray_100900(u32);
extern "C" void *OperatorNew_100990(u32);
extern "C" void OperatorDelete_100840(void *);
extern "C" char D_00455C10[];
extern "C" void OperatorDeleteArray_100820(void *);
struct RcPtr { char *p; int *n; RcPtr(char *q):p(q),n(0) {try {if(p){int *c=(int *)OperatorNew_100990(4);if(c)*c=1;n=c;}}catch(...){OperatorDeleteArray_100820(p);throw;}} ~RcPtr(); };
namespace std {
struct exception { exception() {} virtual ~exception(); };
struct Msg { RcPtr rc; Msg(const char *s):rc((char *)OperatorNewArray_100900(strlen(s)+1)) {strcpy(rc.p,s);} ~Msg(); };
struct logic_error:exception { Msg msg; logic_error(const char *s):msg(s) {} virtual ~logic_error(); };
struct out_of_range:logic_error { out_of_range(const char *s):logic_error(s) {} virtual ~out_of_range(); };
struct length_error:logic_error { length_error(const char *s):logic_error(s) {} virtual ~length_error(); };
}
struct Str {
 union {
  struct {u32 flag:1;u32 cap:31;u32 size;char *data;} l;
  struct {u8 flag:1;u8 size:7;char data[11];} s;
 } u;
};
static inline u32 mergeflag(bool & one,u32 x){one&=1;x&=~1u;x|=one;return x;}
extern "C" void StringReserve_107e80(Str *s,u32 n) {
 if(n>0x7ffffffe)throw std::length_error(D_00455C10);
 bool heap=*(u32 *)s&1;
 u32 len,cap;
 if(!heap){len=s->u.s.size;cap=11;}else{len=s->u.l.size;cap=s->u.l.cap;}
 if(n<len)n=len;
 if(n+1<12)n=11;else n=(n+16)&~15;
 if(n==cap)return;
 char *p,*old;bool newheap;
 if(n==11){old=s->u.l.data;p=s->u.s.data;newheap=false;}
 else {
  if(cap<n)p=(char *)OperatorNew_100990(n);
  else {try{p=(char *)OperatorNew_100990(n);}catch(...){return;}}
  newheap=(u8)1;
  if(heap)old=s->u.l.data;else old=s->u.s.data;
 }
 memcpy(p,old,len);p[len]=0;
 if(heap)OperatorDelete_100840(old);
 bool branchflag=newheap; *(u32 *)s=mergeflag(newheap,*(u32 *)s);
 if(!branchflag)s->u.s.size=len;
 else{s->u.l.data=p;s->u.l.size=len;s->u.l.cap=n;}
}
