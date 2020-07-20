#ifndef __CTX_SWAP_H__
#define __CTX_SWAP_H__

#include <stdlib.h>
// -----------
#define RSP 0
#define RIP 1
#define RBX 2
#define RDI 3
#define RSI 4

#define RBP 5
#define R12 6
#define R13 7
#define R14 8
#define R15 9
#define RDX 10
#define RCX 11
#define R8 12
#define R9 13

//-------------
// 64 bit
// low | regs[0]: r15 |
//    | regs[1]: r14 |
//    | regs[2]: r13 |
//    | regs[3]: r12 |
//    | regs[4]: r9  |
//    | regs[5]: r8  |
//    | regs[6]: rbp |
//    | regs[7]: rdi |
//    | regs[8]: rsi |
//    | regs[9]: ret |  //ret func addr
//    | regs[10]: rdx |
//    | regs[11]: rcx |
//    | regs[12]: rbx |
// hig | regs[13]: rsp |
enum {
  kRDI = 7,
  kRSI = 8,
  kRETAddr = 9,
  kRSP = 13,
};

/*
  coroutine stack info
  regs: registor for used to matain context
*/
struct coctx_t
{
	void *regs[ 14 ];
	size_t ss_size;
	char *ss_sp; // button of stack

};

// pointer of routine function 
typedef void *(*pfn_co_routine_t)( void * );

/*
  struct of routine
  pfn: function
  ctx: function enviroment
  arg: arguments belong to pfn
*/
struct stroutine
{
	pfn_co_routine_t pfn;
	coctx_t ctx;
	void *arg;	
};

// interface to make stack for coroutine
int ctx_make(coctx_t *ctx, pfn_co_routine_t pfn, const void *s, const void *s1);

// init coroutine(expecialy stack mem)
stroutine * co_init(pfn_co_routine_t pfn, int stack_size = 8 * 1024, void *arg1 = NULL, void *arg2 = NULL);
void co_resume(stroutine *cur, stroutine *next);

#endif
