#ifndef MINE_MAP_H
#define MINE_MAP_H
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <windows.h>
using namespace std;

///����ͼÿ����һ��Unit�ṹ
struct Unit
{
    int val;          //��¼ÿ����ֵ
    bool display;     //��¼�Ƿ�ҿ�
    int mark;         //��¼�Ƿ񱻱�Ϊ�ף����Ƿ�����ȷ
    int correct_mark; //��¼��Χ8����ȷ��ǵĸ���
    int error_mark;   //��¼��Χ8������ǵĸ���
};

/**
 * author: Zhong Siqi
 * createData: 2022/4/22
 * description: ����ͼ�ࡣ��Ҫ���ڳ�ʼ������ͼ�ṹ���Լ���ӡ����ͼ
 **/
class MineMap
{
public:
    MineMap();                                 //���캯��
    ~MineMap();                                //��������
    vector<vector<Unit>> map;                  //���Unit��Ķ�̬����
    int m_hidden;                              //δ�ҿ��ĸ�����
    int m_rightMark;                           //���ױ��û���ȷ��ǵ���Ŀ
    int m_noMark;                              //δ���û���ǵĵ�����
    bool if_iniMine;                           //����λ���Ƿ��ʼ��
    void iniMap(int row, int column, int num); //��ʼ������ͼ��С�͵�����
    void createPosition(int i, int j);         //��ʼ������λ��
    void printMap() const;                     //��ӡ�����غͱ�ǵĵ���ͼ
    void printAll() const;                     //��ӡ��������ͼ

private:
    int m_row;    //����
    int m_column; //����
    int m_mine;   //������
};

#endif