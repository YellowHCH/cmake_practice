#pragma once
#include <stdio.h>
#include <setjmp.h>
#include <iostream>
#include <ucontext.h>
/*
 * makecontext: create context
 * getcontext : 
 * setcontext : 
 * swapcontext: 
 * */
//jmp_buf buf;

void print_coroutine(char *argv[]);

void test_ucontext();

void test_ucontext2();
