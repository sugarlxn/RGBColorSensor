# RGBColorSensor

**[中文](./README.md) / [English](./README_EN.md)**

<img src="./assets/image-20230604002839128.png" alt="image-20230604002839128" style="zoom:200%;" />

这是一个基于TCS34725多通道光传感器的颜色采集设备，使用stm32f103c8t6单片机，采集颜色传感器的原始值，并通过光强分量对RGB分量进行归一化。将传感器的原始数据上传到上位机，我们可以很方便地对RGB颜色空间可视化以及颜色空间变换，例如RGB2HSV、RGB2HSL、RGB2Lab(借助OPENCV-python库)。φ(*￣0￣)

## 示例

<img src="./assets/1.jpg" alt="1" style="zoom:10%;" />

## 如何使用

```Shell
#下载代码文件到本地，你可以 git clone ... 或者 download the code
```

## 贡献

- @**[MJJ](https://github.com/2481366805)** 一个低调的朋友

## 许可证

[GPL: General Public License](LICENSE)

