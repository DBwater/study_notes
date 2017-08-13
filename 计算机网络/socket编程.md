# socket编程

### select
- select是通过设置，检查存放fd标志位的数据结构(相当于数组)来对I/O调用进行处理
- 进程可以被监视的fd数量被限制，64位最大默认为2048
>int select(int maxfdp1，fd_set *readfds,，fd_set  *writefds，fd_set *exceptfds， struct timeval *timeout);

1. struct fd_set表示的是文件描述符
2. struct timeval 表示时间值
3. maxdp1是最大的文件描述符+1。
3. fd_set \* readfds 是指向fd_set结构的指针，这个集合中应该包括文件描述符，我们是要监视这些文件描述符的读变化的，即我们关心是否可以从这些文件中读取数据了，如果这个集合中有一个文件可读，select 就会返回一个大于 0 的值。
4. fd_set  \* writefds：是指向fd_set结构的指针，这个集合中应该包括文件描述符，我们是要监视这些文件描述符的写变化的，即我们关心是否可以向这些文件中写入数据了，如果这个集合中有一个文件可写，select就会返回一个大于0的值
5. fd_set \* errorfds：用来监视文件错误异常。
6. struct timeval\* timeout 是 select 的超时时间，这个参数至关重要，它可以使 select 处于三种状态:
	- 若将 NULL 以形参传入，即不传入时间结构，就是将 select 置于阻塞状态，一定等到监视文件描述符集合中某个文件描述符发生变化为止；
	- 若将时间值设为 0 秒 0 微妙，就变成一个纯粹的非阻塞函数，不管文件描述符是否有变化，都立刻返回继续执行，文件无变化返回 0，有变化返回一个正值；
	- timeout 的值大于 0，这就是等待的超时时间，即 select 在 timeout 时间内阻塞，超时时间之内有事件到来就返回了，否则在超时后不管怎样一定返回，返回值同上述。

FD_ZERO(fd_set \*); 清空集合
FD_SET(int, fd_set \*); 将一个给定的文件描述符加入集合之中
FD_CLR(int, fd_set \*); 将一个给定的文件描述符从集合中删除
FD_ISSET(int ,fd_set \* )检查集合中指定的文件描述符是否可以读写
当套接字比较多的时候需要通过遍历DF_SETSIZE个socket来完成调度，不管哪个socket是活跃都需要遍历一遍，这会浪费很多CPU的时间。

### poll
- poll本质和select没有区别，它将用户传入的数组拷贝到内核空间，然后查询每个fd对应的设备状态，如果设备就绪则在设备等待队列中加入一项并继续遍历，如果遍历完所有fd后没有发现就绪设备，则挂起当前进程，直到设备就绪或者主动超时，被唤醒后它又要再次遍历fd。这个过程经历了多次无谓的遍历。
- poll没有最大连接数的限制，这是因为他是用链表来储存的，并且poll还支持水平触发。

### epoll
- epoll既支持水平触发也支持边缘触发
- epoll没有最大并发连接的限制，不会随着f数量增多而效率下降，epoll只管活跃的连接，因此epoll的效率远远高于select和poll。
- 利用mmap()文件映射内存加速与内核空间的消息传递；即epoll使用mmap减少复制开销。
```epoll_create(int size)```

创建一个epoll实例，返回新创建的epoll实例，当这个文件描述符不用的时候需要通过close来关闭，当所有epoll实例相关的文件描述符被关闭的时候，实例被销毁。
```epoll_ctl(int epfd,int op,struct epoll_event *ev)```

修改epoll的兴趣列表
fd指明了要修改的兴趣列表中的哪一个文件描述符的限定
op用来指出需要执行的操作，可以是如下几种：
- EPOLL_CTL_ADD,将描述符号fd添加到epoll实例的兴趣列表中去，如果添加一个已经存在兴趣列表中的文件描述符，会出现EEXIST错误。
- EPOLL_CTL_MOD，修改描述符fd上设定的事件
- EPOLL_CTL_DEL,将文件描述符fd从epoll兴趣列表中移除

ev是指向结构体epoll_event的指针，结构体定义如下
```C
	struct epoll_event{
    	unit32_t events;
        epoll_data_t data;
    };
```
结构体epoll_event中的data字段的定义如下：
```c
	typedef union epoll_data{
    	void *ptr;
        int fd;
        unit32_t u32;
        unit64_t u64;
    } epoll_data_t;
```
> epoll_wait(int epfd, struct epoll_event *evilist, int maxevents, int timeout);

事件等待，返回epoll实例中处于就绪态的文件描述符信息。单个epoll_wait()调用就能返回多个就绪态文件描述符信息。
evlist所指向的结构体数组中返回的就是有关就绪态文件描述符的信息，数组evlist的空间由调用者负责申请，所包含的文件个数在参数maxevents中指定。
参数timeout用来确定epoll_wait()的阻塞行为，有如下几种：
- 如果timeout等于-1，调用将一直阻塞，直达兴趣列表中的文件描述符上有事件产生，或者捕捉到一个信号为止。
- 如果timeou等于0，执行一次非阻塞式检查，看兴趣列表上产生了哪个事件
- 如果timeout大于0,调用将阻塞至多timeout毫秒，直达文件描述符上有事件发生，或者直到捕捉到一个信号为止

epoll_wait()返回evlist中的元素个数如果在timeout超时就返回0,出错返回-1。
在多线程中可以在一个线程中使用epoll_clt将文件描述符添加到另一个线程的epollwait所监视的epoll实例中去，也会得到立刻处理，epoll_wait调用将返回 有关新添加的文件描述符的就绪信息。
**工作模式**
epoll对文件描述符的操作有两种模式：LT（level trigger）和ET（edge trigger）。LT模式是默认模式，LT模式与ET模式的区别如下：

- LT模式：当epoll_wait检测到描述符事件发生并将此事件通知应用程序，应用程序可以不立即处理该事件。下次调用epoll_wait时，会再次响应应用程序并通知此事件。
- ET模式：当epoll_wait检测到描述符事件发生并将此事件通知应用程序，应用程序必须立即处理该事件。如果不处理，下次调用epoll_wait时，不会再次响应应用程序并通知此事件。
ET模式在很大程度上减少了epoll事件被重复触发的次数，因此效率要比LT模式高。epoll工作在ET模式的时候，必须使用非阻塞套接口，以避免由于一个文件句柄的阻塞读/阻塞写操作把处理多个文件描述符的任务饿死。

### 三种I/O多路复用的具体实现和区别
[三种I/O复用的具体实现和区别](http://www.cnblogs.com/Anker/p/3265058.html)

## 文件描述符就绪条件

- 读条件
	- socket内核接受缓冲区的字节书大于等于其低水位标记SO\_RCVLOWAT,此时可以无阻塞的读该socket,并读操作返回的字节大于０
	- socket通信的对方关闭连接，此时对socket的读操作返回0
	- 监听socket上有未处理的错误，此时我们可以工getsockopt来读取和清楚该操作
- 写条件
	- socket的内核发送缓冲区中的可用字节大于等于低水位标记，SO\_SNDLOWAT, 此时我们可以无阻塞的写该soceket,并且写操作返回的字节数大于０
	- socket的写操作被关闭，对写操作，对写操作被关闭的socket执行写操作将会触发一个SIGPIPE信号。
	- socket使用非阻塞的connet连接成功或者失败之后
	- sokcet上有未处理的错误的时候

