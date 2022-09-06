#include"MineMap.h"
using namespace std;

//默认初始化为0，再经玩家自定义后再按需求更改数值
MineMap::MineMap() : if_iniMine(false), m_row(0), m_column(0), m_mine(0), m_hidden(0), m_noMark(0), m_rightMark(0) {}
//没有需要手动释放的内存，和用户礼貌告别就好了
MineMap::~MineMap()
{
    cout << "下次再见,bye~" << endl;
}
//按需求更改地雷图
void MineMap::iniMap(int row, int column, int num)
{
    m_row = row;
    m_column = column;
    m_mine = num;
    m_hidden = row * column;
    m_rightMark = 0;
    m_noMark = num;
    map.resize(row + 2); //哨兵算法，在实际打印地雷区外再扩充一圈，解决边缘问题
    for (int i = 0; i < map.size(); i++)
    {
        map[i].resize(column + 2);
        for (int j = 0; j < map[i].size(); j++)
        {
            map[i][j].val = 0;          //此时未初始化地雷位置
            map[i][j].display = false;  //隐藏状态
            map[i][j].mark = 0;         //未标记为雷
            map[i][j].correct_mark = 0; //没有正确标记
            map[i][j].error_mark = 0;   //没有错误标记
        }
    }
}
//创建地雷位置
void MineMap::createPosition(int i, int j)
{
    if_iniMine = true; //地雷位置已初始化
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
//自定义函根据参数改变颜色
void color(const unsigned short textColor) 
{
    if (textColor >= 0 && textColor <= 15)                                   //参数在0-15的范围颜色
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor); //用一个参数，改变字体颜色
    else                                                                     //默认的字体颜色是白色
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
//打印带有隐藏和标记的地雷图
void MineMap::printMap() const
{
    system("cls");
    cout << "Made by 21302010069 ZSQ" << endl;
    cout << "||e/E 退出||h/H 帮助||r/R 重开" << endl;
    cout << "||a/A 左键||d/D 右键||s/S 双击" << endl;
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
    cout << "待标记雷数：" << m_noMark << endl;
}
//打印完整地雷图
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