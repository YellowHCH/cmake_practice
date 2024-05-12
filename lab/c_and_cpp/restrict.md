## `restrict` key word

- [stackoverflow](https://stackoverflow.com/questions/776283/what-does-the-restrict-keyword-mean-in-c)
- [cppreference](https://en.cppreference.com/w/c/language/restrict)

> restrict says that two pointers cannot point to overlapping memory regions. The most common usage is for function arguments.


当RAM中的值更新了，寄存器中的值失效，需要重新load一次（一条move指令）。通过`__restrict__` 关键字告诉compiler 某块内存不会存在alias，那么寄存器中的值就不会失效，从而不需要强制的reload（当编译器不确定RAM是否更新了，那么就会保守的去reload）。


Run: `clang -S -O3 restrict.cc` 生成asm，对比增加该关键字后的指令区别。

- without `__restrict__`

```asm
	movl	(%rdx), %eax
	addl	%eax, (%rdi)
  # 编译器不知道%eax 寄存器中对应的RAM的值（%rdx）有没有变化，因为它可能是%rdi 的alias
  # 所以%eax中的值是无效的
	movl	(%rsi), %eax
	imull	(%rdx), %eax
	movl	%eax, (%rsi)
	retq
```

- with `__restrict__`

```asm
	movl	(%rdx), %eax
	addl	%eax, (%rdi)
  # 有了restrict的保证，%eax寄存器中的值依然有效
  # imul 指令的第二个操作数必须是eax寄存器，所以需要在imul之后进行一次move，而非直接将mul的结果存在%rsi中
	imull	(%rsi), %eax
	movl	%eax, (%rsi)
	retq
```

`func_xxx(%rdi, %rsi, %rdx)`
