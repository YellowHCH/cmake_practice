/*
 * kernel src code tree
 * arch                 ->      特定体系结构源码
 * block                ->      块设备I/O层
 * crypto               ->      加密API
 * Documentation        ->      内核源码文档
 * drivers              ->      设备驱动程序
 * firmware             ->      使用某些驱动程序而需要的设备固件
 * fs                   ->      vfs等文件系统
 * include              ->      内核头文件
 * init                 ->      内核引导和初始化
 * ipc                  ->      进程间通信
 * kernel               ->      核心子系统（调度程序）
 * lib                  ->      通用内核函数
 * mm                   ->      内存管理子系统和虚拟内存
 * net                  ->      网络子系统
 * samples              ->      实例示范代码
 * scripts              ->      编译内核所需要的脚本
 * security             ->      linux安全模块
 * sound                ->      语音子系统
 * usr                  ->      早期用户空间代码
 * tools                ->      linux开发中的工具
 * virt                 ->      虚拟化基础结构
 * */
/*
 * 内核开发特点
 * 1. 无libc库和标准头文件
 * 2. 必须使用GNU C
 * 3. 没有内存保护机制
 * 4. 浮点运算困难
 * 5. 堆栈大小为 2 page
 * 6. 抢占式内核导致大量同步和并发
 * 7. 移植性
 * */
/*
 * process manager
 * 进程：可执行代码段，打开的文件，挂起的信号，内核内部数据，处理器状态，内核地址空间和数据段
 * 内核管理进程：每个进程由进程独有的task_struct管理所有的信息，内核通过操作task_struce对象对进程进行创建、调度等动作。
 * */
