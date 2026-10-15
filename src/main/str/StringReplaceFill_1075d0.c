#pragma opt_foldconstants off
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
extern "C" char D_00455AA0[],D_00455B00[],D_00445E98[],D_00445EA0[];
struct RcPtr { char *p; int *n; RcPtr(char *); ~RcPtr(); };
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
static inline const u32 &minval(const u32 &a,const u32 &b){return a<b?a:b;}
static inline u32 mergeflag(u8 one,u32 x){if(one)one=one;u32 y=one;y=(x&~1u)|y;return y;}
extern "C" Str *StringReplaceFill_1075d0(Str *s,u32 pos,u32 n,u32 add,unsigned char ch) {
 bool heap=*(u32 *)s&1;
 u32 cap,len;char *data;
 if(!heap){len=s->u.s.size;cap=11;data=s->u.s.data;}
 else {cap=s->u.l.cap;data=s->u.l.data;len=s->u.l.size;}
 if(pos>len)throw std::out_of_range(D_00455AA0);
 u32 count=minval(len-pos,n);
 if(add>=0x7fffffff || len-count>0x7ffffffe-add)throw std::length_error(D_00455B00);
 u32 size=len-count+add;
 u32 tail=len-(pos+count);
 if(size>=cap){
  u32 c=(cap+15)&~15;
  while(c<size+1)c=(c*2+15)&~15;
  char *p=(char *)OperatorNew_100990(c);
  if(pos)memcpy(p,data,pos);
  char *q=p+pos;
  memset(q,ch,add);
  if(tail)memcpy(q+add,data+pos+count,tail);
  p[size]=D_00445E98[0];
  if(heap)OperatorDelete_100840(data);else *(u32 *)s=mergeflag(1,*(u32 *)s);
  s->u.l.data=p;s->u.l.size=size;s->u.l.cap=c;
 }else{
  if(tail)memmove(data+pos+add,data+pos+count,tail);
  memset(data+pos,ch,add);
  data[size]=D_00445EA0[0];
  if(!heap)s->u.s.size=size;else s->u.l.size=size;
 }
 return s;
}
