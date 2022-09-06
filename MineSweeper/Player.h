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
 * description: ����ࡣ��Ҫ���ڶ�ȡ�����п��ʵ���˻�����
 **/
class Player
{
public:
    Player();         //���캯��
    ~Player();        //��������
    time_t begin;     //��¼һ�ֿ�ʼʱ��ʱ��
    time_t now;       //��¼ʵʱ��ʱ
    MineMap m_Map;    //����ͼ����Ϊ�����ĳ�Ա
    void startGame(); //��ʼ��Ϸ

private:
    int row;                            //����
    int column;                         //����
    int num;                            //������
    bool passGame();                    //�ж���Ϸ�Ƿ�ͨ��
    int read(string &order, size_t &i); //�ӿ����ж�ȡ����
    void read_first_order();            //��ȡ��һ������
    void read_order();                  //��ȡ����
    void playGame();                    //��Ϸ����
    void leftClick(int i, int j);       //���ģ��
    void rightClick(int i, int j);      //�Ҽ�ģ��
    void bothClick(int i, int j);       //˫��ģ��
    void autoDisplay(int i, int j);     //�Զ��ҿ��ø���
    void autoExpose(int i, int j);      //�Զ��ҿ���Χ8������
    void helpPage();                    //�������棬�����������������
    void resetGame();                   //������Ϸ����
    void endGame();                     //������Ϸ����������
    void returnGame();                  //���ص�ǰ��Ϸ
    void failGame();                    //��Ϸʧ��
    void successGame();                 //��Ϸ�ɹ�
    void if_restart();                  //��Ϸδ���������ѡ���Ƿ����¿�ʼ�µ�һ��
    void if_reset();                    //��Ϸ�ѽ������ɹ���ʧ�ܣ����ѡ���Ƿ����¿�ʼ�µ�һ��
    void if_end();                      //��Ϸδ���������ѡ���Ƿ���ֹ��Ϸ
};
#endif