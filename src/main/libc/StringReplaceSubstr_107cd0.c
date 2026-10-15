#include "types.h"
#pragma cplusplus on
#pragma exceptions on
#pragma inline_depth(8)
extern "C" u32 strlen(const char *);
extern "C" char *strcpy(char *, const char *);
extern "C" void *OperatorNewArray_100900(u32);
extern "C" char D_00455AA0[];
struct RcPtr { char *p; int *n; RcPtr(char *); ~RcPtr(); };
namespace std {
struct exception { exception() {} virtual ~exception(); };
struct Msg { RcPtr rc; Msg(const char *s):rc((char *)OperatorNewArray_100900(strlen(s)+1)) {strcpy(rc.p,s);} ~Msg(); };
struct logic_error:exception { Msg msg; logic_error(const char *s):msg(s) {} virtual ~logic_error(); };
struct out_of_range:logic_error { out_of_range(const char *s):logic_error(s) {} virtual ~out_of_range(); };
}
struct Str {
 union {
  struct {u32 flag:1;u32 cap:31;u32 size;char *data;} l;
  struct {u8 flag:1;u8 size:7;char data[11];} s;
 } u;
};
static inline const u32 &minval(const u32 &a,const u32 &b){return a<b?a:b;}
extern "C" Str *StringReplace_106f90(Str *,u32,u32,const char *,const char *,char);
extern "C" Str *StringReplaceSubstr_107cd0(Str *s,u32 pos,u32 n,const Str *other,u32 start,u32 count) {
 /* The unused sixth callee argument retains the runtime iterator tag slot. */
 struct Tag {char c;Tag(){}}; struct Frame {Tag tag;u32 delta;} frame;
 const char *data;u32 len;
 if(!(*(const u32 *)other&1)){len=other->u.s.size;data=other->u.s.data;}
 else {data=other->u.l.data;len=other->u.l.size;}
 if(start>len)throw std::out_of_range(D_00455AA0);
 data+=start;
 frame.delta=len-start;
 count=minval(frame.delta,count);
 return StringReplace_106f90(s,pos,n,data,data+count,frame.tag.c);
}
