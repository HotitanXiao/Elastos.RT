# Elastos Carrier

## 功能介绍
  - 解决互联网上app节点没有公网ip无法直接互联的问题。通常解决这个问题需要部署一台中心服务器来做数据中转。亦来云Carrier基于P2P通信技术实现了无中心的直连通信方案。
  - 提供跨网络访问能力，例如，任意两个app节点可以在不同的子网内，例如，一个在家里wifi环境，一个在公司wifi环境。App之间通过一个“地址”字符串，互相“加好友”确认授权，即可直接通信。
  
## Carrier编程基本概念
  - Whisper
  
    代表一个Carrier节点对象。通过它来控制节点的初始化、开启和停止。
    
  - Friend
  
    好友，代表一个节点对另一个节点的授权许可。例如，一个节点向另一个节点发送数据，必须先建立好友关系，否则无法通信。
    针对好友可以进行：添加、删除、发送消息等操作。
    基于好友的消息通信，是一个长度受限、不可靠的通信机制，类似UDP数据包。
    
  - Session
  
    会话，两个节点之间要想建立长连接、高时效、高可靠性的数据传输通道，可以选择用Session方式。针对Session要进行初始化、请求和确认请求等等操作。
    
  - Stream
  
    流，在Session建立成功以后，节点之间通过读写Stream传送数据。
    
  - Channel
  
    这是针对同一个session实现的多路复用，是对一个Session使用上进行的封装。
    
## Android版
  - 代码库&编译方法
  
    <https://github.com/elastos/Elastos.NET.Carrier.Android.SDK>
  
  - 用法
  
    <https://github.com/elastos/Elastos.NET.Carrier.Android.SDK#basic-tests>
    
  - 接口文档
  
    <https://github.com/elastos/Elastos.NET.Carrier.Android.SDK#build-docs>
    
## JS版
  - <https://github.com/elastos/Elastos.NET.Carrier.Nodejs.SDK>
  
## C++版
  - <https://github.com/elastos/Elastos.NET.Carrier.Native.SDK/>
