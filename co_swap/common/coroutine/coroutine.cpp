/*
 * =====================================================================================
 *
 *       Filename:  coroutine.cpp
 *
 *    Description:  coroutine
 *
 *        Version:  1.0
 *        Created:  07/27/2017 17:21:29 PM
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  huangyun.goddard (), 895175589@qq.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <cstdlib>
#include <cstring>
#include <cstdio>
#include "coroutine.h"

namespace goddard
{
	const int DEFAULT_COROUTINE_COUNT = 2000;
	const int MAX_COROUTINE_COUNT = 10000;
        // default stack size 128k
	const int DEFAULT_STACK_SIZE = 128 * 1024;

	enum CoroutineStatus
	{
		CoroutineDead = 0,
		CoroutineReady,
		CoroutineRunning,
		CoroutineSuspend,
	};

        /* coroutine info, include context, fun, args, status and stack*/
	struct coroutine
	{
		ucontext c;
		CoroutineFun fun;
		void *args;
		CoroutineStatus status;
		char stack[DEFAULT_STACK_SIZE];
	};

        /*
          cos       : matained in schedule, 
          running_id: which co is running
          use_count : number of cos
          max_size  : max size of co array
         */
	struct schedule
	{
		ucontext main;
		coroutine **cos;
		int running_id;
		int use_count;
		int max_size;
	};

        /// operation for schedule:

        // init schedule obj, i guess this method is used inside, so is static
	static bool schedule_init(schedule *s)
	{
		s->cos = NULL; // coroutines array initialized to NULL
		s->running_id = -1; // active id set to -1, siguoyi
		s->use_count = 0;
		s->max_size = DEFAULT_COROUTINE_COUNT;
                // alloc mem for coroutines objs
		s->cos = (coroutine **)malloc(sizeof(coroutine *) * s->max_size);
		if (NULL == s->cos)
		{
                        // if alloc mem fail
			return false;
		}
                // set mem to NULL, is very nice 
		memset(s->cos, 0, sizeof(coroutine *) * s->max_size);
		return true;
	}

        // creat a new schedule obj
	schedule* schedule_new()
	{
		schedule *s = (schedule *)malloc(sizeof(schedule));
		if (schedule_init(s))
		{
			return s;
		}
		schedule_destory(s);
		return NULL;
	}

        // free schedule obj and coroutine obj matained by schedule
	void schedule_destory(schedule *s)
	{
		if (NULL == s)
		{
			return;
		}
		for (int i = 0; i < s->max_size; ++i)
		{
			coroutine *co = s->cos[i];
			if (NULL != co)
			{
				free(co);
			}
		}
		free(s->cos);
		free(s);
	}

        // get schedule use count
	int schedule_usecount(schedule *s)
	{
		return s->use_count;
	}

        /// operations for coroutine obj

        // creat coroutine boj
	static coroutine *coroutine_new(CoroutineFun fun, void *args)
	{
		coroutine *co = (coroutine *)malloc(sizeof(coroutine));
		if (NULL == co)
		{
			return NULL;
		}
		co->status = CoroutineDead; // set status as ...
		co->fun = fun;
		co->args = args;
		return co;
	}

        // creat coroutine in schedule, if usc count exceed max_size, make new room for cos with double mem 
	int coroutine_create(schedule *s, CoroutineFun fun, void *args)
	{
                // check if number of coroutines over than max size
		if (s->use_count < s->max_size)
		{
			for (int i = 0; i < s->max_size; ++i)
			{
				int id = (i + s->use_count) % s->max_size;
                                // get coroutine obj pointer
				coroutine *co = s->cos[id];
				if (NULL == co)
				{
                                        // if point to nullptr, creat a new coroutine obj and add to schedule
					co = coroutine_new(fun, args);
					if (NULL == co)
					{
						return -1;
					}
					s->cos[id] = co;
				}
				if (CoroutineDead == co->status)
				{
					co->fun = fun;
					co->args = args;
					co->status = CoroutineReady;
                                        // copy coroutine stack
					memset(co->stack, 0, sizeof(co->stack));
					++s->use_count; // use_count increcement
//					printf("use count incr %d, %d\n", s->use_count, id);
					return id;
				}
                                // how about co != NULL && co->status is not dead, I guess he thought as: use_count<max_size, so co is null
			}
		}
		else // use_count >= max_size
		{
			if (s->max_size > MAX_COROUTINE_COUNT)
			{
				return -2;
			}
                        // realloc double size mem for cos, I donot think is a nice method, why not use list
			coroutine **p = (coroutine **)realloc(s->cos, s->max_size * 2 * sizeof(struct coroutine *));
			if (NULL == p)
			{
				return -1;
			}
			int id = s->max_size;
			s->cos = p; // set s->cos to new address which contain enough mem
                        // set new mem to 0
			memset(s->cos + s->max_size, 0, sizeof(coroutine *) * s->max_size);
			s->max_size *= 2;
			++s->use_count;
                        // creat new coroutin and add to schedule
			coroutine *co = coroutine_new(fun, args);
			if (NULL == co)
			{
				return -1;
			}
			co->status = CoroutineReady;
			memset(co->stack, 0, sizeof(co->stack));
			s->cos[id] = co;
//			printf("use count incr %d, %d\n", s->use_count, id);
			return id;
		}
		return -1;
	}

        // 
	static void schedule_fun(schedule *s)
	{
                // co = s->cos[s->id]
		int id = s->running_id;
		coroutine *co = s->cos[id];
                // run coroutine fun
		co->fun(co->args);
                // set status to end or said dead
		co->status = CoroutineDead;
                // set current schedule running_id to -1, because there is no coroutine is active now
		s->running_id = -1;
                // I do not agree with this, you must to try every co in cos, why not use list as empty_co, busy_co to matain cos
		--s->use_count;
//		free(co);
//		s->cos[id] = NULL;
//		printf("use count decr %d, %d\n", s->use_count, id);
	}

        // resume s->cos[id], run this coroutine
	void coroutine_resume(schedule *s, int id)
	{
		if (id < 0 || id >= s->max_size)
		{
			return;
		}
		coroutine *co = s->cos[id];
		if (NULL == co)
		{
			return;
		}

                // get status
		switch(co->status)
		{
			case CoroutineReady:
				{
                                        // ready stat, but has not run, so we need to set content and make content
					getcontext(&co->c);
                                        // set coroutine stack address and size
					co->c.uc_stack.ss_sp = co->stack;
					co->c.uc_stack.ss_size = sizeof(co->stack); // 128k
					co->c.uc_flags = 0; // ?
					co->c.uc_link = &s->main; // schedule ucontent, so is main content
					s->running_id = id; // set coroutine id
					co->status = CoroutineRunning; // set status ti running
                                        // make content mem for co
					makecontext(&co->c, (void (*)())schedule_fun, 1, s);
                                        // swap main content with co contebt
					swapcontext(&s->main, &co->c);
				}
				break;
			case CoroutineSuspend:
				{
                                        // just resume from suspend
					s->running_id = id;
					co->status = CoroutineRunning;
					swapcontext(&s->main, &co->c);
				}
				break;
			default:
				{
				}
				break;
		}
	}

        // yield current active coroutine, checkout current content to main content
	void coroutine_yield(schedule *s)
	{
		if (-1 == s->running_id)
		{
			return;
		}
		coroutine *co = s->cos[s->running_id];
		s->running_id = -1;
		co->status = CoroutineSuspend;
		swapcontext(&co->c, &s->main);
	}

        // just print all coroutines
	void schedule_check(schedule *s, int num)
	{
		if (num > s->max_size)
		{
			num = s->max_size;
		}
		printf("schedule_check num %d\n", num);
		for (int i = 0; i < num; ++i)
		{
			coroutine *co = s->cos[i];
			if (NULL != co)
			{
				printf("schedule_check id: %d, status: %d\n", i, co->status);
			}
		}
	}

        // delete coroutine from schedule through id
	void coroutine_del(schedule *s, int id)
	{
		if (id < 0 || id >= s->max_size)
		{
			return;
		}
		coroutine *co = s->cos[id];
		if (NULL != co)
		{
			free(co);
			s->cos[id] = NULL;
		}
	}
}
