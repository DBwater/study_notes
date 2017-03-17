---
title: socket编程

---

#socket编程
>int select(int maxfdp1，fd_set *readfds,，fd_set  *writefds，fd_set *exceptfds， struct timeval *timeout);

struct fd_set表示的是文件描述符
struct timeval 表示时间值
maxdp1是最大的文件描述符+1。
fd_set \* readfds 是指向fd_set结构的指针，这个集合中应该包括文件描述符，我们是要监视这些文件描述符的读变化的，即我们关心是否可以从这些文件中读取数据了，如果这个集合中有一个文件可读，select 就会返回一个大于 0 的值。
fd_set  \* writefds：是指向fd_set结构的指针，这个集合中应该包括文件描述符，我们是要监视这些文件描述符的写变化的，即我们关心是否可以向这些文件中写入数据了，如果这个集合中有一个文件可写，select就会返回一个大于0的值
fd_set * errorfds：用来监视文件错误异常。
struct timeval* timeout 是 select 的超时时间，这个参数至关重要，它可以使 select 处于三种状态:
 - 若将 NULL 以形参传入，即不传入时间结构，就是将 select 置于阻塞状态，一定等到监视文件描述符集合中某个文件描述符发生变化为止；
 - 若将时间值设为 0 秒 0 微妙，就变成一个纯粹的非阻塞函数，不管文件描述符是否有变化，都立刻返回继续执行，文件无变化返回 0，有变化返回一个正值；
 - timeout 的值大于 0，这就是等待的超时时间，即 select 在 timeout 时间内阻塞，超时时间之内有事件到来就返回了，否则在超时后不管怎样一定返回，返回值同上述。
FD_ZERO(fd_set \*); 清空集合
FD_SET(int, fd_set \*); 将一个给定的文件描述符加入集合之中
FD_CLR(int, fd_set \*); 将一个给定的文件描述符从集合中删除
FD_ISSET(int ,fd_set \* )检查集合中指定的文件描述符是否可以读写