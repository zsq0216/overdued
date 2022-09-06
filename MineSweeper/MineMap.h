#ifndef MINE_MAP_H
#define MINE_MAP_H
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <windows.h>
using namespace std;

///地雷图每格都是一个Unit结构
struct Unit
{
    int val;          //记录每格数值
    bool display;     //记录是否揭开
    int mark;         //记录是否被标为雷，且是否标记正确
    int correct_mark; //记录周围8格正确标记的个数
    int error_mark;   //记录周围8格错误标记的个数
};

/**
 * author: Zhong Siqi
 * createData: 2022/4/22
 * description: 地雷图类。主要用于初始化地雷图结构，以及打印地雷图
 **/
class MineMap
{
public:
    MineMap();                                 //构造函数
    ~MineMap();                                //析构函数
    vector<vector<Unit>> map;                  //存放Unit类的动态数组
    int m_hidden;                              //未揭开的格子数
    int m_rightMark;                           //地雷被用户正确标记的数目
    int m_noMark;                              //未被用户标记的地雷数
    bool if_iniMine;                           //地雷位置是否初始化
    void iniMap(int row, int column, int num); //初始化地雷图大小和地雷数
    void createPosition(int i, int j);         //初始化地雷位置
    void printMap() const;                     //打印带隐藏和标记的地雷图
    void printAll() const;                     //打印完整地雷图

private:
    int m_row;    //行数
    int m_column; //列数
    int m_mine;   //地雷数
};

#endif