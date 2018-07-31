# AutoSignTool

## 使用注意
1. 必须加命令行参数cab=XXX、output=XXX, 分别表示待签名的cab文件的路径、签名成功后文件指定存放的目录
    - 文件路径必须使用英文双引号引住
    - 多个cab文件路径要用英文分号;分隔

2. AutoSignTool.exe目录下应包含config.ini文件，该文件为程序的配置文件
    - 配置文件如下
```
    [config.ini]
    ;登录共享文件夹的用户名
    userName=XXX
    ;登录共享文件夹的用户名对应的密码
    password=XXX
    ;签名类型
    signType=XXX
    ;签名服务器的输入目录
    signInputFile=XXX
    ;签名服务器的输出目录
    signOutputFile=XXX
    ;签名超时值(分钟为单位)
    timeOut=5
```

## 各种错误信息

|错误代号    |详情         |
|:----------:|:-----------:|
|Error 1     |程序根目录下config.ini配置文件缺失，导致错误|
|Error 2     |共享文件夹连接失败，可能是共享文件夹的输入输出路径有误，可能是登录共享文件夹的账号密码不正确|
|Error 3     |签名失败, 请重试；可能签名服务器出问题|
|Error 4     |命令行参数个数不对，必须是两个命令行参数|
|Error 5     |命令行参数格式不对，每个命令行参数应形如key=value形式|
|Error 6     |命令行参数缺少最终输出路径，即缺少了命令行参数output=XXXX|
|~~Error 7~~ |~~路径应使用英文双引号引起来(该错误已不会出现)~~|
|Error 8     |命令行参数缺少cab文件路径, 即缺少了命令行参数cab=XXXX|
|Error 9     |无有效cab文件路径, 所有的cab路径均是无效时，出现该错误|
