#include"MineMap.h"
using namespace std;

//Ĭ�ϳ�ʼ��Ϊ0���پ�����Զ�����ٰ����������ֵ
MineMap::MineMap() : if_iniMine(false), m_row(0), m_column(0), m_mine(0), m_hidden(0), m_noMark(0), m_rightMark(0) {}
//û����Ҫ�ֶ��ͷŵ��ڴ棬���û���ò���ͺ���
MineMap::~MineMap()
{
    cout << "�´��ټ�,bye~" << endl;
}
//��������ĵ���ͼ
void MineMap::iniMap(int row, int column, int num)
{
    m_row = row;
    m_column = column;
    m_mine = num;
    m_hidden = row * column;
    m_rightMark = 0;
    m_noMark = num;
    map.resize(row + 2); //�ڱ��㷨����ʵ�ʴ�ӡ��������������һȦ�������Ե����
    for (int i = 0; i < map.size(); i++)
    {
        map[i].resize(column + 2);
        for (int j = 0; j < map[i].size(); j++)
        {
            map[i][j].val = 0;          //��ʱδ��ʼ������λ��
            map[i][j].display = false;  //����״̬
            map[i][j].mark = 0;         //δ���Ϊ��
            map[i][j].correct_mark = 0; //û����ȷ���
            map[i][j].error_mark = 0;   //û�д�����
        }
    }
}
//��������λ��
void MineMap::createPosition(int i, int j)
{
    if_iniMine = true; //����λ���ѳ�ʼ��
    srand((unsigned)time(NULL));
    int mineNum = m_mine;
    while (mineNum)
    {
        int rr = rand() % m_row + 1;
        int rc = rand() % m_column + 1;
        if (map[rr][rc].val < 9 && (rr != i || rc != j))
        {
            map[rr][rc].val = 9;
            ++map[rr - 1][rc].val;
            ++map[rr][rc - 1].val;
            ++map[rr - 1][rc - 1].val;
            ++map[rr - 1][rc + 1].val;
            ++map[rr][rc + 1].val;
            ++map[rr + 1][rc].val;
            ++map[rr + 1][rc + 1].val;
            ++map[rr + 1][rc - 1].val;
            mineNum--;
        }
    }
}
//�Զ��庯���ݲ����ı���ɫ
void color(const unsigned short textColor) 
{
    if (textColor >= 0 && textColor <= 15)                                   //������0-15�ķ�Χ��ɫ
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor); //��һ���������ı�������ɫ
    else                                                                     //Ĭ�ϵ�������ɫ�ǰ�ɫ
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
//��ӡ�������غͱ�ǵĵ���ͼ
void MineMap::printMap() const
{
    system("cls");
    cout << "Made by 21302010069 ZSQ" << endl;
    cout << "||e/E �˳�||h/H ����||r/R �ؿ�" << endl;
    cout << "||a/A ���||d/D �Ҽ�||s/S ˫��" << endl;
    color(11);
    cout << setiosflags(ios::right) << setw(3) << 0 << "|";
    for (int i = 1; i <= m_column; i++)
        cout << setiosflags(ios::right) << setw(3) << i;
    cout << endl;
    for (int i = 1; i <= m_row; i++)
    {
        color(11);
        cout << setiosflags(ios::right) << setw(3) << i << "|";
        color(16);
        for (int j = 1; j <= m_column; j++)
        {
            if (map[i][j].display == false)
            {
                if (map[i][j].mark == 0)
                    cout << setw(3) << "#";
                else
                {
                    color(4);
                    cout << setw(3) << "M";
                    color(16);
                }
            }
            else
            {
                if (map[i][j].val >= 9)
                    cout << setw(3) << "*";
                else if (map[i][j].val == 0)
                    cout << setw(3) << "_";
                else
                    cout << setw(3) << map[i][j].val;
            }
        }
        cout << endl;
    }
    cout << "�����������" << m_noMark << endl;
}
//��ӡ��������ͼ
void MineMap::printAll() const
{
    system("cls");
    cout << "Made by 21302010069 ZSQ" << endl;
    color(11);
    cout << setiosflags(ios::right) << setw(3) << 0 << "|";
    for (int i = 1; i <= m_column; i++)
        cout << setiosflags(ios::right) << setw(3) << i;
    cout << endl;
    for (int i = 1; i <= m_row; i++)
    {
        color(11);
        cout << setiosflags(ios::right) << setw(3) << i << "|";
        color(16);
        for (int j = 1; j <= m_column; j++)
        {
            if (map[i][j].val >= 9)
            {
                color(4);
                cout << setw(3) << "*";
                color(16);
            }

            else if (map[i][j].mark == 2)
            {
                color(14);
                cout << setw(3) << "X";
                color(16);
            }
            else if (map[i][j].val == 0)
                cout << setw(3) << "_";
            else
                cout << setw(3) << map[i][j].val;
        }
        cout << endl;
    }
}