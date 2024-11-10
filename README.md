### 很抱歉啊助教学长,当时说要用单文件的时候我已经做了一半的呜呜呜

### 这边提供了g++编译指令,辛苦学长了呜呜呜

```shell
g++  main.cpp src/*.cpp -Iinclude -o main.exe -std=c++17 -lpthread
.\main.exe
```
# 执行效果如图
![image](https://github.com/user-attachments/assets/85872524-c63b-40f9-a34d-fead50a79c3d)

# 心得1 关于智能指针和抽象基类的new

一开始写peison的时候,发现personVec(统一管理person)里面应该要存放的是指针,因为要实现多态,但是我发现这样子内存管理会有点困难,因为我习惯于谁申请的谁释放,但是这个地方是外部传进来的

所以我统一使用了智能指针来执行,即把裸指针全部隐藏,统一使用智能指针

ps:有一个地方想了挺久
![image](https://github.com/user-attachments/assets/b7137040-f441-46a5-aca8-85adfe82be1c)

![image](https://github.com/user-attachments/assets/7c6d1ea2-6f17-488f-ab4f-e09aa726cb4e)

![image](https://github.com/user-attachments/assets/7df44a9c-51bf-4a37-805b-fd4f4ee0dba9)

![image](https://github.com/user-attachments/assets/74ba5089-e477-4713-8f1a-8efba06a6491)

![image](https://github.com/user-attachments/assets/a45a4a18-71a0-4665-9105-bb3dc1a4f54d)

![image](https://github.com/user-attachments/assets/ea3345a3-3648-4d3f-821e-199b54f9ef31)

![image](https://github.com/user-attachments/assets/afc7ebb5-d49c-43b6-9f53-50693e7cc961)

![image](https://github.com/user-attachments/assets/a57ac586-d042-4fa5-8129-5952eff81963)

ps:但是实际上还是不对,因为解引用emp会得到person类,而派生类没有接收person类的构造函数
![image](https://github.com/user-attachments/assets/5b796796-c3a4-43e9-9e7c-f51c9b543841)

![image](https://github.com/user-attachments/assets/e0e1f020-e957-43e8-a12a-7d112199930e)



# 心得2 关于中文字符集问题

把一切都解决之后,跑起来了,同时把建议的command也写上了,然后试了试操作,发现输入中文的时候是乱码

经过一顿解决,我发现我程序里默认都是utf-8,但是vscode的cmd终端应该是使用的gbk

然后我查询我的vscode的setting.json,但是那里都是黑的

"此设置无法应用于此工作区。它将在您直接打开包含的工作区文件夹时应用。"

然后我发现这个setting不是当前工作区的,是应该去全局的工作区

左上角文件->首选项->设置->搜索setting.json,然后"在setting.json内部编辑"

然后输入了一大堆东西,但是还是不能正确识别中文字符,把vscode重启也不行

![image](https://github.com/user-attachments/assets/80c4d54e-83e3-42f6-8606-759bb1710645)

![image](https://github.com/user-attachments/assets/13d10ab2-e8f2-4d34-9247-40f3efc49935)

![image](https://github.com/user-attachments/assets/02e818c1-8266-408e-92d3-429ee5bdbaa7)

还是没解决,无论是切换gbk和utf8都是乱码

解析：chcp全称—> changes the active console code page, 936代表gbk编码(简体中文)

使用chcp 65001切换编码，65001代表中文编码

最后发现cmd直接开是没问题
![image](https://github.com/user-attachments/assets/b1472eaa-2bc7-4e29-adbb-3a0dc24066d4)

![image](https://github.com/user-attachments/assets/f937352b-97f4-4b54-9e74-1ac0fe13b98b)

所以说还真就是vscode的内部终端的问题 
![image](https://github.com/user-attachments/assets/b57b0141-2deb-47d8-b538-91e8831d8cd4)


# 心得3 关于路径的问题

因为我是引入了第三方的csv解析库

但是不支持相对路径,导致我如果要在助教的环境上跑的话还需要助教手动写入绝对路径

![image](https://github.com/user-attachments/assets/69ebc900-d06e-4e0d-905d-810c5bdc6cb8)
于是我就想着应该自己获取可执行文件的路径然后拼接成绝对路径,但是这其中一直没有成功

无论是调用window自身的api还是啥其他的
![image](https://github.com/user-attachments/assets/0448a747-a8d1-403e-a3c5-e261ca5e7969)
最终这样子执行成功

# 心得4 关于再次提交代码
![image](https://github.com/user-attachments/assets/8b92e15d-9452-44e9-b889-a8db1e0c0399)
然后这边我不知道要怎么处理冲突
![image](https://github.com/user-attachments/assets/f4df66fb-be4a-48e5-8b76-bc096e46bfc0)

![image](https://github.com/user-attachments/assets/63e0f376-372c-4d49-a14e-cb35e454cd21)

![image](https://github.com/user-attachments/assets/39a529eb-01b5-4234-bc71-19054e560dc8)
