# 模拟器使用指导

## 准备
本工程基于Qt Creator搭建，开发者使用前需要下载和安装Qt Creator。
### Qt 下载与安装
#### Qt 下载
Qt 官方下载
https://download.qt.io/archive/

国内镜像站下载
中国科学技术大学：http://mirrors.ustc.edu.cn/qtproject/
清华大学：https://mirrors.tuna.tsinghua.edu.cn/qt/
北京理工大学：http://mirror.bit.edu.cn/qtproject/
中国互联网络信息中心：https://mirrors.cnnic.cn/qt/

具体Qt下载相关可参考地址：http://c.biancheng.net/view/3851.html

#### Qt 安装
双击下载的Qt安装程序，按引导界面完成安装即可。
注意事项：
1. 注册安装界面
可选择注册账号进行安装，或者断网安装跳过注册界面。
2. 选择组件界面。
需勾选Qt x.x.x展开栏（这栏是为qt自动配置构建套件，如果漏选，开发者可后期在Qt控件中自行手动配置）和Developer and Designer Tools展开栏（这栏是编译器组件下载）都要勾选minGW组件（基于当前电脑操作系统选择32-bit还是64-bit）。

![安装组件选择](../../../../figures/MinGW-select.png)



## 2、打开工程

### 场景一：JS应用打开方式：

1. **打开QT Creator**

2. **点击菜单：文件—>打开文件或项目**

   - 弹出的文件选择框中选择工程项目

   - 参考源码路径（请下载到windows本地，不要使用"\\\wsl$"路径映射）：

     [源码工程目录]\foundation\ace\ace_engine_lite\frameworks\tools\qt\simulator\simulator.pro。

     注意：第一次打开项目时，需要在Configure Project界面，kits列表中勾选minGW（仅勾选minGW）。

   - 点击configure project按钮加载工程。

3. **设置JS bundle路径**

   - 展开项目树

     ```
     simulator
       |-entry
         |-Sources
           |-main.cpp
     ```

   - 双击main.cpp文件，修改

     `jsAbility.Launch("D:\\app\\slider", "MyApplication", 0)`

     函数中的第一个参数为要运行的JS bundle路径。

     备注：JS bundle可通过下载DevEco Studio创建后编译生成，示例源码可从目录ace_engine_lite\frameworks\examples获取

4. **编译**

​    依次点击：**构建—>编译项目**，或者直接在项目树中右键，在右键菜单中选择**重新构建**即可。

5. **调试**

​    编译完成后，点击调试按钮即可运行调试。



### 场景二：C++ UI应用打开方式：

1. **打开QT Creator**

2. **点击菜单：文件—>打开文件或项目**

   - 弹出的文件选择框中选择工程项目

   - 参考源码路径（请下载到windows本地，不要使用"\\\wsl$"路径映射）：

     [源码工程目录]\foundation\graphic\ui\tools\qt\simulator\simulator.pro。

     注意：第一次打开项目时，需要在Configure Project界面，kits列表中勾选minGW（仅勾选minGW）。

   - 点击configure project按钮加载工程。

3. **UI Test应用运行入口**

   - 展开项目树

   ```
   simulator
     |-UITest
       |-Sources
         |-main.cpp
   ```

4. **编译**

​    依次点击：**构建—>编译项目**，或者直接在项目树中右键，在右键菜单中选择**重新构建**即可。

5. **调试**

​    编译完成后，点击调试按钮即可运行调试。

