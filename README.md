# Simple-MCAST

简单的多播服务端和客户端。

## 实验目的

了解单播、广播和多播的区别，熟悉多播的实现原理和编程框架，掌握多播服务器和客户端的功能区分。

## 实验要求

1. 阅读课本第11章；
2. 了解单播、广播和多播的原理；
3. 了解多播的编程框架；
4. 编写多播的服务器端和客户端：  
  多播服务器端发送本地的一个文件到多播地址；  
  多播客户端加入多播组，接收多播服务器发送的数据；  
  多播客户端把接收的数据放到本地文件中，统计接收的字符数；  
  多播客户端正常退出；

## Usage

```
Usage: ./simple-mcast [-s] [-a 224.0.0.88] [-p 5555] [-f FILE]
 -s, --server      start as a server
 -a, --addr IPv4   set address (numbers-and-dots notation)
 -p, --port NUM    set port
 -f, --file FILE   upload/save filepath
 -h, --help        display this message and exit
```

服务端:

```bash
# 多播地址为 224.0.0.88
# 端口号为 5555 
# 上传文件为 test.txt
./simple-mcast -s -a 224.0.0.88 -p 5555 -f test.txt
```

客户端:

```bash
./simple-mcast -a 224.0.0.88 -p 5555
```

## Notes