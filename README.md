# SlidesScanner
 Turn slides photos into plain view

### Abs
- Core:OpenCV
- UI:Qt control and interact
- Class：Image.h
- test UI: OpenCV waitKey()
- features: open/batch open, recon, modify, trans, - postprocessing, save

### Todo
- 优化找中心点
- 优化UI
- 优化标记方式（Mask + 框）
- 提速
- 拖拽点问题，若重叠怎么办？按点排序算法调整交叠激活顺序
- 后处理优化，更新基础图像处理和OCR、化学式识别、公式识别等功能  
- OCR引擎抄作业：https://github.com/hiroi-sora/Umi-OCR  
- PPT 图片抠像  

### Sildes Scanner 开题
- 背景：拍ppt，需要透视变换，现有软件准确率不高，需要优化
- 提升：锐化，ocr，建档，ppt专用优化，自动摘要
- 竞品：扫描全能王、OfficeLens  
   这两个软件的用途是扫描文档，适用于文档在画面中占据很大比例的情况，识别准确度很高。在课室这种充满干扰的环境下会失效，另外一次性可以处理30张照片，可以参考
- 主要功能：
    - 输入图片、自动识别PPT/板书、输出识别结果、手动调整选区、透视转换和锐化、保存图片
    - 提供多种修正模式：单张照片自动修正，一组照片全自动修正（并且互相校正）、一组照片半自动修正（用户先手动修正第一张，剩余的自动修正，这样做可以提高准确度）等
    - 需要用户交互界面、设置界面等
    - 在移动端上比较实用，但需要一定移动开发基础，视开发进度选做
    - 移动端还可以加上随拍随识别的功能
- 初步实现方案：
    - C++ & OpenCV
    - 霍夫变换识别照片中直线，结合已有的车道线检测、相机位置矫正等涉及透视线识别的问题，标记照片中的透视线、减少干扰
    - 通过区域特征针对性地识别PPT，如确定的长宽比、背景亮色、区域内包括文字等等，并标记边框、顶角
    - 通过机器学习进一步提升识别准确度
- 工作流程：
    - 结合案例作业“OpenCV”人脸识别，学习OpenCV的使用
    - 结合案例作业Qt设计计算器，学习图形界面开发
    - 分头做识别模块与机器学习、透视转换模块和用户交互模块
- Inspirations  
    需要一个人专门学学设计，我来做全栈吧 

    注意识别不到对象时的break问题（视频流实时/动态识别）静态转换，动态捕捉
    
    notability也内置了这个功能，大家有需求
    点击区域对焦/点击区域准确识别

    注意提高批量处理能力！因为一场讲座可能有很多PPT

    PPT边框搜索工具  
    用AI训练调整参数？  
    竞品：扫描全能王、OfficeLens  
    霍夫变换+透视变换  
    大比例矩形识别准确使用，大干扰环境下失效  
    评价软件成效：直接作比较！  

    思路：图像预处理  
    搜索、迭代、系列关联（某一个搜索正确后以此为标准，因为同一场讲座人的位置是一定的，四象限可以分区）  
    训练素材来自大家自己的拍摄  

    困难：课室里边框太多、灯、桌子、黑板、窗户……  

    兼顾板书的扫描  
    PPT上有边框的也会干扰www  
    这可以用常见屏幕比例限制之  
    也可以用有边框PPT做平面校验  

    还要注意，在课室内，PPT边框是竖直、水平的，可以找参考线&平移  
    测算竖直参考线斜率，俯仰的透视不明显！  
    测算水平透视线和灭点！水平  

    哦哦哦！先识别线，再识别区域！好家伙！
    备选区域用屏幕比例控制一下，筛选输出

    内置一下图像旋转和镜像功能？
    通过文字识别判定方向？

    通过提升/降低区域权重来实现精准推送
    比如，通过区域内有无文字来判断边框是不是ppt的线条

    套娃，ppt上放ppt照片，这个可以通过透视解决
    看看我们能做到什么样？

    手动部分直接参考OfficeLens

    牺牲通用性提升效率和准确度
    作为新式扫描相机的一个模块也挺好的

    拍照直接生成PPT，做功能设计
    iOS开发
    找老师拷贝PPT不好吗哈哈哈？

    不过呀，还是推荐同学们上课认真听讲记笔记、课前预习课后复习
    毕竟，拍到了并不代表学到了嘛qwq

    前排干扰少，后排干扰多，都要训练到
    讲台和人头阻挡的不完整边框解决方案

    添加功能，同一张ppt可能拍了好几次（因为动画），做舍去，连拍保留最后一张
    复现扫描全能王，交给UI去完成

    识别窗帘的干扰、未播放ppt的干扰？
