#CAP数据包结构

## cap文件头
　　前面24个字节是.cap文件的文件头。
　　头信息对应的结构体为：
```c
struct pcap_file_header {
    bpf_u_int32 magic;
    u_short version_major;
    u_short version_minor;
    bpf_int32 thiszone;    /* gmt to local correction */
    bpf_u_int32 sigfigs;    /* accuracy of timestamps */
    bpf_u_int32 snaplen;    /* max length saved portion of each pkt */
    bpf_u_int32 linktype;    /* data link type (LINKTYPE_*) */
};
```
cap文件中的linktype在不同的网络环境下抓包，数据帧的帧头是不一样的。比如：
- 在局域网内抓包，linktype为1，以太网的帧头就是两个网卡物理地址
- 如果直接用ADSL拨号上线，则linktype为9，数据帧头为PPP协议。

## 每个帧的头信息
在cap文件头后面接的的就是每个数据包的信息
其中前16字节是抓包时间、捕获的包长度、真实的数据包长度，然后才是具体的数据帧的内容。
数据段的头对应的结构体为：
```c
struct pcap_pkthdr {
    struct timeval ts;    /* time stamp */
    bpf_u_int32 caplen;    /* length of portion present */
    bpf_u_int32 len;    /* length this packet (off wire) */
};
```

## 帧内容

之后就是包的信息了。比如以太网帧头结构体如下：

```c
struct EthernetPacket
{
    char MacDst[6];             ///< 目的网卡物理地址
    char MacSrc[6];             ///< 源网卡物理地址
    unsigned short PacketType; ///< 包类型， ip或ARP等
};
    PacketType=0x0008是IP包，PacketType=0x0608是ARP包。
```
之后的具体数据包信息根据协议进行解析即可。