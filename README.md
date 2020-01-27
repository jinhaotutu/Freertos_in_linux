# Freertos_in_linux
Freertos_in_linux: Freertos demo run in the linux to study

---
## 说明
1. Posix_GCC_Simulator_6.0.4.zip为移植在linux上的一版freertos demo
2. Posix_GCC_Simulator原本来上面文件压缩出来的文件，现在进行了部分修改，去除了多余的文件函数，升级了freertos版本至v10.2.1，剩下最简单的函数用于freertos初步学习。
3. 上述demo在ubuntu-18上测试通过

---
## 运行
```
# 编译
cd Posix_GCC_Simulator/FreeRTOS_Posix/study_demo/rtos_start_1/
sh build.sh

# 运行
./rtos_start_1_app.bin

# 清除
sh build.sh clean
```
---

Enjoy

Tuu
