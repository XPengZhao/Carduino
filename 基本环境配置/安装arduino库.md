# 安装额外的 arduino 库

摘录自 arduino [官方文档]。


<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->

<!-- code_chunk_output -->

* [安装额外的 arduino 库](#安装额外的-arduino-库)
	* [1. 什么是库？](#1-什么是库)
	* [2. 如何安装库](#2-如何安装库)
		* [2.1 利用库管理器](#21-利用库管理器)
		* [2.2 导入zip格式的库](#22-导入zip格式的库)
		* [2.3 手动安装](#23-手动安装)

<!-- /code_chunk_output -->

一旦您对Arduino软件感到满意并使用内置函数时，您可能希望以增加额外的库来扩展Arduino的功能。

## 1. 什么是库？

库是代码的集合，使您可以轻松连接到传感器，显示器，模块等。例如，内置的LiquidCrystal库可以使你轻松地使用字符LCD显示器进行显示。在互联网上有数百个额外的库供下载。内置库和一些其他库在[参考]中列出。你只有安装其他库后才能使用。

## 2. 如何安装库

### 2.1 利用库管理器

为了将新库安装在你的Arduino软件中，你可以使用库管理器（1.6.2版及以上版本中可用）。

打开Arduino软件（IDE），点击“项目”菜单，然后再选择“Include Library > Manage Libraries ”。

![库管理器]

打开库管理器后，会出现已安装或可以安装的库清单。

在这里，我们将以安装Bridge库为例。滚动列表找到Bridge库，然后选择你想要安装的库版本。有时可能仅有一个库版本可用。若未出现版本选择菜单，不用担心，这属于正常情况。

![库安装]

最后点击安装，等待Arduino软件（IDE）安装新库。下载可能需要一段时间，时间长短取决于你的连接速度。 安装完成后，将会在Bridge库旁边显示“Installed”标签。你可以选择关闭库管理器。

![安装完成]

现在你可以在"Include Library" 菜单中找到新库了。
若你希望添加自己的库，只需点击 [github]。

### 2.2 导入zip格式的库

库通常以ZIP文件或文件夹的形式存在。库文件夹的名称即为库的名称。文件夹内将包括一份.cpp文件和一份.h文件，通常还有关键词.txt文件、示例文件夹以及该库所需要的其他文件。 从1.0.5版本起，你可以在Arduino软件（IDE）中安装第三方库。

请勿解压下载库，将其保留原样即可。

在Arduino软件（IDE）中，导航到 项目 >Include Library。在下拉列表的顶部，"Add .ZIP Library" 选项。

![安装zip库]

系统将提示你选择你想要添加的库。导航到该zip文件所在位置，并打开该文件。

![选择zip库]

返回 项目 >Include Library 菜单。现在可以在下拉菜单底部看到该库，这样你就可以在“项目”中使用该库了。

该zip文件将在你Arduino的“项目”目录（而不是Arduino软件（IDE）安装过程中直接生产的库文件夹）中的libraries文件夹中解压好。 注：导入后，可通过“项目”使用该库，但该库对应的示例需要重启IDE以后才能出现在“文件>示例”中。

### 2.3 手动安装

为安装库，首先需要退出Arduino软件。

然后解压包含该库的压缩包文件。例如，若你正在安装名为“ArduinoParty”的库，则需要先解压缩ArduinoParty.zip。解压后会产生一个名为ArduinoParty的文件夹，文件夹内包含ArduinoParty.cpp和ArduinoParty.h等类似文件。（若文件夹中没有.cpp和.h文件，则你需要创建此类文件。在这种情况下，你需要创建名为“ArduinoParty”的文件夹，并将压缩文件中的所有文件都移入其中，例如ArduinoParty.cpp和ArduinoParty.h。）

拖动ArduinoParty文件夹，将其放入你的库文件夹中。在Windows系统中，该文件夹的路径可能是“我的文档\Arduino\libraries”。对于Mac用户而言，其路径可能是“文稿/Arduino/ libraries”。在Linux系统中，该文件夹可能是你sketchbook路径中的“libraries”文件夹。

现在，你的Arduino库文件夹显示如下（在Windows系统中,mac和linux类似）

- My Documents\Arduino\libraries
  - ArduinoParty
    - ArduinoParty.cpp
    - ArduinoParty.h
    - examples

即：  
> My Documents\Arduino\libraries\ArduinoParty\ArduinoParty.cpp  
> My Documents\Arduino\libraries\ArduinoParty\ArduinoParty.h  
> My Documents\Arduino\libraries\ArduinoParty\examples  

文件夹中可能不仅仅包括.cpp和.h文件，你只需要确保所有文件都在该文件夹中即可。（若直接将.cpp和.h文件导入库文件夹，或是放入其他文件夹中，库将无法正常运行.）例如：

> Documents\Arduino\libraries\ArduinoParty.cpp 和
> Documents\Arduino\libraries\ArduinoParty\ArduinoParty\ArduinoParty.cpp

将无法正常工作。

重新启动Arduino应用程序。确保新增库已出现在”项目 >Include Library”菜单项中。 就是这样！你已经成功安装一个库！

**本教程参考了*Limor Fried*的文本。**

[参考]: <https://www.arduino.cc/en/Reference/Libraries>
[github]: <https://github.com/arduino/Arduino/issues>
[官方文档]: <https://www.arduino.cc/en/Guide/Libraries?setlang=en>

[库管理器]: <./image/1.png>
[库安装]: <./image/2.png>
[安装完成]: <./image/3.png>
[安装zip库]: <./image/4.png>
[选择zip库]: <./image/5.png>