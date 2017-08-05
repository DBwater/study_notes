# http协议详解

##http的主要特点
1. 支持客户/服务器模式
2. 简单快速，客户向服务器请求服务的时候，只需要传送请求方法，常用的请求方法有GET,HEAD,POST.每个方法规定了客户与服务器的类型不同。由于http协议很简单，使得http服务的程序规模小，因而通信速度很快
3. 灵活,http允许传输类型的数据对象，正在传输的类型又，Content-Type加以标记。
4. 无连接，限制每次连接只处理一个请求，服务器处理完客户的请求，并收到客户的应答后，即断开连接，采用这种方式可以节省传输时间
5. 无状态，http的协议是无状态协议的，对于事务的处理没有记忆能力，缺少状态意味着，如果后续处理需要前面的信息，他必须重新传送，这样可能导致，每次连接传送的数据量很大，另一方面，在服务器不需要前面信息的时候，他的应答就很快

## http协议的请求

http的请求包括三个组成部分，分别是：请求行，消息报头，请求正文：
![](/home/dbwater/桌面/http1.png)

1. 第一部分：请求行，用来说明请求类型,要访问的资源以及所使用的HTTP版本；GET说明请求类型为GET,URL为要访问的资源，该行的最后一部分说明使用的是HTTP版本。
2. 第二部分：请求头部，紧接着请求行（即第一行）之后的部分，用来说明服务器要使用的附加信息；从第二行起为请求头部，HOST将指出请求的目的地.User-Agent,服务器端和客户端脚本都能访问它,它是浏览器类型检测逻辑的重要基础.该信息由你的浏览器来定义,并且在每个请求中自动发送等等
3. 第三部分：空行，请求头部后面的空行是必须的,即使第四部分的请求数据为空，也必须有空行。
4. 第四部分：请求数据也叫主体，可以添加任意的其他数据。

### 请求行

请求行以一个方法符号开头，以空格分开，后面跟着请求的URL和协议的版本，格式如下
> Method Request-URL HTTP-version (CRLF)

其中 Method表示请求方法；Request-URI是一个统一资源标识符；HTTP-Version表示请求的HTTP协议版本；CRLF表示回车和换行（除了作为结尾的CRLF外，不允许出现单独的CR或LF字符）

**请求方法（所有方法全为大写）：**
请求方法 |意义
--------|---
GET     |请求获取Request-URI所标识的资源
POST    |在Request-URI所标识的资源后附加新的数据
HEAD    |请求获取由Request-URI所标识的资源的响应消息报头
PUT     |请求服务器存储一个资源，并用Request-URI作为其标识
DELETE  |请求服务器删除Request-URI所标识的资源
TRACE　  |请求服务器回送收到的请求信息，主要用于测试或诊断
CONNECT |保留将来使用
OPTIONS |请求查询服务器的性能，或者查询与资源相关的选项和需求

### 请求报头
请求报头允许客户端向服务器端传递请求的附加信息以及客户端自身的信息。
**常用的请求报头:**

- Accept
	Accept请求报头域用于指定客户端接受哪些类型的信息。eg：Accept：image/gif，表明客户端希望接受GIF图象格式的资源；Accept：text/html，表明客户端希望接受html文本。
- Accept-Charset
	Accept-Charset请求报头域用于指定客户端接受的字符集。eg：Accept-Charset:iso-8859-1,gb2312.如果在请求消息中没有设置这个域，缺省是任何字符集都可以接受。
- Accept-Encoding
	Accept-Encoding请求报头域类似于Accept，但是它是用于指定可接受的内容编码。eg：Accept-Encoding:gzip.deflate.如果请求消息中没有设置这个域服务器假定客户端对各种内容编码都可以接受。
- Accept-Language
	Accept-Language请求报头域类似于Accept，但是它是用于指定一种自然语言。eg：Accept-Language:zh-cn.如果请求消息中没有设置这个报头域，服务器假定客户端对各种语言都可以接受。
- Authorization
	Authorization请求报头域主要用于证明客户端有权查看某个资源。当浏览器访问一个页面时，如果收到服务器的响应代码为401（未授权），可以发送一个包含Authorization请求报头域的请求，要求服务器对其进行验证。
- Host（发送请求时，该报头域是必需的）
	Host请求报头域主要用于指定被请求资源的Internet主机和端口号，它通常从HTTP URL中提取出来的，eg：
	我们在浏览器中输入：http://www.guet.edu.cn/index.html
	浏览器发送的请求消息中，就会包含Host请求报头域，如下：
	Host：www.guet.edu.cn
	此处使用缺省端口号80，若指定了端口号，则变成：Host：www.guet.edu.cn:指定端口号
- User-Agent
	我们上网登陆论坛的时候，往往会看到一些欢迎信息，其中列出了你的操作系统的名称和版本，你所使用的浏览器的名称和版本，这往往让很多人感到很神奇，实际上，服务器应用程序就是从User-Agent这个请求报头域中获取到这些信息。User-Agent请求报头域允许客户端将它的操作系统、浏览器和其它属性告诉服务器。不过，这个报头域不是必需的，如果我们自己编写一个浏览器，不使用User-Agent请求报头域，那么服务器端就无法得知我们的信息了。
**请求报头举例：**
GET /form.html HTTP/1.1 (CRLF)
Accept:image/gif,image/x-xbitmap,image/jpeg,application/x-shockwave-flash,application/vnd.ms-excel,application/vnd.ms-powerpoint,application/msword,*/* (CRLF)
Accept-Language:zh-cn (CRLF)
Accept-Encoding:gzip,deflate (CRLF)
If-Modified-Since:Wed,05 Jan 2007 11:21:25 GMT (CRLF)
If-None-Match:W/"80b1a4c018f3c41:8317" (CRLF)
User-Agent:Mozilla/4.0(compatible;MSIE6.0;Windows NT 5.0) (CRLF)
Host:www.guet.edu.cn (CRLF)
Connection:Keep-Alive (CRLF)

### 请求正文

**当请求为GET时，请求正文为空。**

### 一个完整请求报文
**POST请求例子，使用Charles抓取的request：**

POST / HTTP1.1
Host:www.wrox.com
User-Agent:Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 2.0.50727; .NET CLR 3.0.04506.648; .NET CLR 3.5.21022)
Content-Type:application/x-www-form-urlencoded
Content-Length:40
Connection: Keep-Alive
（空行）
name=Professional%20Ajax&publisher=Wiley

第一部分：请求行，第一行明了是post请求，以及http1.1版本。
第二部分：请求头部，第二行至第六行。
第三部分：空行，第七行的空行。
第四部分：请求数据，第八行。

##　http协议的响应

一般情况下，服务器接收并处理客户端发过来的请求后会返回一个HTTP的响应消息。
HTTP响应也由四个部分组成，分别是：状态行、消息报头、空行和响应正文。

![](/home/dbwater/桌面/http2.jpg)

- 第一部分：状态行，由HTTP协议版本号， 状态码， 状态消息 三部分组成。
第一行为状态行，（HTTP/1.1）表明HTTP版本为1.1版本，状态码为200，状态消息为（ok）

- 第二部分：消息报头，用来说明客户端要使用的一些附加信息
第2~4行为消息报头，
Date:生成响应的日期和时间；Content-Type:指定了MIME类型的HTML(text/html),编码类型是UTF-8

- 第三部分：空行，消息报头后面的空行是必须的

- 第四部分：响应正文，服务器返回给客户端的文本信息。

### 状态行

**状态行格式如下：**
HTTP-Version Status-Code Reason-Phrase CRLF
其中，HTTP-Version表示服务器HTTP协议的版本；Status-Code表示服务器发回的响应状态代码；Reason-Phrase表示状态代码的文本描述。
**状态代码有三位数字组成，第一个数字定义了响应的类别，且有五种可能取值：**

- 1xx：指示信息--表示请求已接收，继续处理
- 2xx：成功--表示请求已被成功接收、理解、接受
- 3xx：重定向--要完成请求必须进行更进一步的操作
- 4xx：客户端错误--请求有语法错误或请求无法实现
- 5xx：服务器端错误--服务器未能实现合法的请求

**常见状态代码、状态描述、说明：**

- 200 OK      //客户端请求成功
- 400 Bad Request  //客户端请求有语法错误，不能被服务器所理解
- 401 Unauthorized //请求未经授权，这个状态代码必须和WWW-Authenticate报头域一起使用 
- 403 Forbidden  //服务器收到请求，但是拒绝提供服务
- 404 Not Found  //请求资源不存在，eg：输入了错误的URL
- 500 Internal Server Error //服务器发生不可预期的错误
- 503 Server Unavailable  //服务器当前不能处理客户端的请求，一段时间后可能恢复正常
eg：HTTP/1.1 200 OK （CRLF）

###　响应报头

响应报头允许服务器传递不能放在状态行中的附加响应信息，以及关于服务器的信息和对Request-URI所标识的资源进行下一步访问的信息。
**常见的响应报头：**

- Date           生成报头的时间
- Content-Type　　响应文档的mime类型
- Connection 　　　指定连接的类型是持续性，还是一次性
- Content-Language　描述了资源所用的自然语言。
- Content-Length	　描述资源长度

### 一个完整响应报文

HTTP/1.1 200 OK
Date: Fri, 22 May 2009 06:07:21 GMT
Content-Type: text/html; charset=UTF-8
(空行)
```
<html>
      <head></head>
      <body>
            <!--body goes here-->
      </body>
</html>
```
## HTTP工作原理
hHTTP协议定义Web客户端如何从Web服务器请求Web页面，以及服务器如何把Web页面传送给客户端。HTTP协议采用了请求/响应模型。客户端向服务器发送一个请求报文，请求报文包含请求的方法、URL、协议版本、请求头部和请求数据。服务器以一个状态行作为响应，响应的内容包括协议的版本、成功或者错误代码、服务器信息、响应头部和响应数据。

以下是 HTTP 请求/响应的步骤：

1. 客户端连接到Web服务器
	一个HTTP客户端，通常是浏览器，与Web服务器的HTTP端口（默认为80）建立一个TCP套接字连接。例如，http://www.oakcms.cn。
2. 发送HTTP请求
	通过TCP套接字，客户端向Web服务器发送一个文本的请求报文，一个请求报文由请求行、请求头部、空行和请求数据4部分组成。
3. 服务器接受请求并返回HTTP响应
	Web服务器解析请求，定位请求资源。服务器将资源复本写到TCP套接字，由客户端读取。一个响应由状态行、响应头部、空行和响应数据4部分组成。
4. 释放连接TCP连接
	若connection 模式为close，则服务器主动关闭TCP连接，客户端被动关闭连接，释放TCP连接;若connection 模式为keepalive，则该连接会保持一段时间，在该时间内可以继续接收请求;
5. 客户端浏览器解析HTML内容
	客户端浏览器首先解析状态行，查看表明请求是否成功的状态代码。然后解析每一个响应头，响应头告知以下为若干字节的HTML文档和文档的字符集。客户端浏览器读取响应数据HTML，根据HTML的语法对其进行格式化，并在浏览器窗口中显示。

例如：在浏览器地址栏键入URL，按下回车之后会经历以下流程：

1. 浏览器向 DNS 服务器请求解析该 URL 中的域名所对应的 IP 地址;
2. 解析出 IP 地址后，根据该 IP 地址和默认端口 80，和服务器建立TCP连接;
3. 浏览器发出读取文件(URL 中域名后面部分对应的文件)的HTTP 请求，该请求报文作为 TCP 三次握手的第三个报文的数据发送给服务器;
4. 服务器对浏览器请求作出响应，并把对应的 html 文本发送给浏览器;
5. 释放 TCP连接;

## GET和POST请求的区别
- GET提交的数据会放在URL之后，以?分割URL和传输数据，参数之间以&相连，如EditPosts.aspx?name=test1&id=123456. POST方法是把提交的数据放在HTTP包的Body中.
- GET提交的数据大小有限制（因为浏览器对URL的长度有限制），而POST方法提交的数据没有限制.
- GET方式需要使用Request.QueryString来取得变量的值，而POST方式通过Request.Form来获取变量的值。
- GET方式提交数据，会带来安全问题，比如一个登录页面，通过GET方式提交数据时，用户名和密码将出现在URL上，如果页面可以被缓存或者其他人可以访问这台机器，就可以从历史记录获得该用户的账号和密码.
