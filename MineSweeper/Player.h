#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <iomanip>
#include <vector>
#include "MineMap.h"
using namespace std;

/**
 * author: Zhong Siqi
 * createData: 2022/4/22
 * description: 玩家类。主要用于读取命令行口令，实现人机交互
 **/
class Player
{
public:
    Player();         //构造函数
    ~Player();        //析构函数
    time_t begin;     //记录一局开始时的时间
    time_t now;       //记录实时用时
    MineMap m_Map;    //地雷图类作为玩家类的成员
    void startGame(); //开始游戏

private:
    int row;                            //行数
    int column;                         //列数
    int num;                            //地雷数
    bool passGame();                    //判断游戏是否通过
    int read(string &order, size_t &i); //从口令中读取整数
    void read_first_order();            //读取第一条口令
    void read_order();                  //读取口令
    void playGame();                    //游戏进行
    void leftClick(int i, int j);       //左键模拟
    void rightClick(int i, int j);      //右键模拟
    void bothClick(int i, int j);       //双击模拟
    void autoDisplay(int i, int j);     //自动揭开该格子
    void autoExpose(int i, int j);      //自动揭开周围8个格子
    void helpPage();                    //帮助界面，帮助玩家熟入口令规则
    void resetGame();                   //重置游戏参数
    void endGame();                     //结束游戏并结束程序
    void returnGame();                  //返回当前游戏
    void failGame();                    //游戏失败
    void successGame();                 //游戏成功
    void if_restart();                  //游戏未结束，玩家选择是否重新开始新的一局
    void if_reset();                    //游戏已结束，成功或失败，玩家选择是否重新开始新的一局
    void if_end();                      //游戏未结束，玩家选择是否终止游戏
};
#endif