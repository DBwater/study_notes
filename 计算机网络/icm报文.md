# ICMP报文
## ICMP协议基础
　　ip协议本身并没未终端提供直接的方法来发现那些发往目的地址失败的IP数据包。此外，IP没有提供直接的方式来获取整段信息（例如，哪些路由器在沿途中被试用或使用一种方法来估计往返时间）。而ICMP协议协议就是为了解决此问题而产生的，他通常被认为是ip层的一部分，他需要在所有的ip实现中实现。

　　我们在网络中经常会使用到ICMP协议，比如我们经常使用的用于检查网络通不通的Ping命令，这个“Ping”的过程实际上就是ICMP协议工作的过程。还有其他的网络命令如跟踪路由的Tracert命令也是基于ICMP协议的。
　　ICMP报文的种类有两种，即ICMP差错报告报文和ICMP询问报文
##ICMP报头结构
 **ICMP报头有一个8字节长的包头，其中前4个字节是固定的格式，包含8位类型字段，8位代码字段和16位的校验和；后4个字节根据ICMP包的类型而取不同的值。**
## icmp报文结构
 **icmp报文的一般格式是这样：**

 ![](icmp1.jpg)
**但是ICMP是封装在IP报进行传输。ICMP报文本身被封装在IP数据报的数据区中，而这个IP数据报又被封装在帧数据中。在IP数据报报头中的协议（Protocol）字段设置成1，表示该数据是ICMP报文，具体如下:**

 ![](icmp.jpg)

**其中，ICMP报文包含：ICMP首部（8字节）+产生差错的数据报IP首部+IP首部后的8个字节。具体如下图：**

 ![](icmp2.jpg)

 **IP包首部要被传回的原因，因为IP首部中包含了协议字段，使得ICMP可以知道如何解释后面的8个字节。而IP首部后面的8字节（UDP的首部或者TCP首部，UDP和TCP首部的8个字节分别包含了16位的目的端口号和源端口号），根据源端口号就可以把差错报文与某个特定的用户进程关联。**
- 类型
长度是1字节，用于定义报文类型。

    类型代码|类型描述
    -------|---------
    0|响应应答（ECHO-REPLY）
    3|不可到达
    4|源抑制
    5|重定向
    8|响应请求（ECHO-REQUEST）
    11|超时
    12|参数失灵
    13|时间戳请求
    14|时间戳应答
    15|信息请求（*已作废）
    16|信息应答（*已作废）
    17|地址掩码请求
    18|地址掩码应答

- 代码
	长度是1字节，表示发送这个特定报文类型的原因。

- 检验和字段
	包括数据在内的整个ICMP数据包的检验和

- 常用的icmp报文
	- 类型8，代码0：表示回显请求(ping请求)。
	- 类型0，代码0：表示回显应答(ping应答)
	- 类型11，代码0：超时
	- 类型代码 类型描述

- 效验和
长度是2字节，用于数据报传输过程中的差错控制。与IP报头校验和的计算方法类似，不同的是其是对整个ICMP报文进行校验。

## ICMP报文格式
ICMP虽然是网络层的协议，但要将ICMP报文放入IP中发送。
ICMP报文的公共头标由1字节的类型（type）、1字节的代码（code）和2字节的校验和（checksum）组成。
类型域和代码域用来标识各种ICMP报文。类型域表示ICMP报文的类型，目前已定义了14种，从类型值来看ICMP报文可分为二大类。

1. 取值为1~127的差错报文：目的不可达、源主机消亡、超时、参数问题、重定向。
2. 取值128以上的是信息（informational）报文：回应请求和应答、信息请求和应答（已弃用）、时间戳和时间戳应答、地址掩码请求和应答、路由器通告和请求
代码|类型
---|---
1|不能到达信宿（Destination Unreachable）差错报文
2|分组过大（Packet Too Big）差错报文
3|超时（Time Exceeded）差错报文
4|参数问题（Parameter Problem）差错报文
128|返回请求（Echo Request）报文
129|返回应答（Echo Reply）报文
130|组成员查询（Group Membership Query）
131|组成员报告（Group Membership Report）
132|组成员结束（Group Membership Termination）
133|路由器请求（Router Solicitation）
134|路由器公告（Router Advertisement）
135|邻机请求（Neighbor Solicitation）
136|邻机公告（Neighbor Advertisement）
137|向（Redirect）
## ICMP报文在linux中的结构

icmp报文(能到达目的地,响应-请求包)

struct icmp
{
    u_char icmp_type; //type of message(报文类型)
    u_char icmp_code; //type sub code(报文类型子码)
    u_short icmp_cksum;//效验和
    u_short icmp_id;//标识符
    u_short icmp_seq;//序号列
    char icmp_data[1];
};
参考:
　　[风云逸](http://www.cnblogs.com/ccsccs/articles/4224441.html)
　　[转载不标明出处？](http://blog.csdn.net/cuipengchong/article/details/20205479)
  TCP/IP详解