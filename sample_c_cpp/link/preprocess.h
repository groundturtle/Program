/*
 * @Author: avert-win
 * @Date: 2022-05-06 17:27:22
 * @LastEditTime: 2022-05-06 17:42:48
 * @FilePath: /ProgramDaily/cppSmaple/preprocess.h
 * @Description: 简介
 * @LastEditors: avert-win
 */

// 在gcc命令中加入参数`-DINITIALIZE`，则预处理器会认为已经进行了初始化，
// 打印出来的值将会是_g: 23 和 _i: 1；否则打印出来的是未初始化的结果。

#ifdef INITIALIZE

int _g = 23;
static int _i = 1;

#else

int _g;
static int _i = 0;

#endif