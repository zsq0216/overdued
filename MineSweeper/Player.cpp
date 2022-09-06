#include "Player.h"
using namespace std;

//默认初始化为0
Player::Player() : row(0), column(0), num(0) {}
//没有要手动释放的内存，和用户礼貌告别就好了
Player::~Player()
{
    cout << "你已经退出游戏啦" << endl;
}
//读口令中的整数
//参数：口令字符串、指定开始读的位置
//返回值：读到的第一个正整数
int Player::read(string &order, size_t &i)
{
    int s = 0;
    char ch = order[i++];
    while (ch > '9' || ch < '0')
    {
        if (i > order.size())
            return s;
        ch = order[i++];
    }
    while (ch >= '0' && ch <= '9')
    {
        if (i > order.size())
            return s;
        s = (s << 1) + (s << 3) + ch - '0';
        ch = order[i++];
    }
    return s;
}
//读第一条口令，完成地雷位置的初始化
void Player::read_first_order()
{
    int tick = 1;
    while (tick)
    {
        string order;
        cout << "请输入口令:" << endl;
        getline(cin, order);
        size_t i = 0;
        for (i; i < order.size(); i++)
        {
            int r = 0, c = 0;
            if (order[i] == 'a' || order[i] == 'A')
            {
                r = read(order, i);
                c = read(order, i);
                if (r == 0 || c == 0 || r > row || c > column)
                {
                    cout << "不合法！";
                    break;
                }
                else
                {
                    --tick;
                    m_Map.createPosition(r, c); //创建地雷位置
                    begin = time(0);
                    leftClick(r, c);
                    m_Map.printMap();
                    break;
                }
            }
            else if (order[i] == 'e' || order[i] == 'E')
            {
                --tick;
                if_end();
                break;
            }
            else if (order[i] == 'r' || order[i] == 'R')
            {
                --tick;
                if_restart();
                break;
            }
            else if (order[i] == 'h' || order[i] == 'H')
            {
                --tick;
                helpPage();
                break;
            }
            else if (i == order.size() - 1)
            {
                cout << "不合法！";
                break;
            }
            else
                continue;
        }
    }
}
//游戏过程中读口令
void Player::read_order()
{
    while (!passGame())
    {
        cout << "请输入口令:" << endl;
        string order;
        getline(cin, order);
        size_t i = 0;
        for (i; i < order.size(); i++)
        {
            int r = 0, c = 0;
            if (order[i] == 'a' || order[i] == 'A')
            {
                r = read(order, i);
                c = read(order, i);
                if (r == 0 || c == 0 || r > row || c > column || m_Map.map[r][c].display == true)
                {
                    cout << "不合法！";
                    break;
                }
                else
                {
                    leftClick(r, c);
                    now = time(0);
                    m_Map.printMap();
                    cout << "计时：" << difftime(now, begin) << "s" << endl;
                    break;
                }
            }
            else if (order[i] == 'd' || order[i] == 'D')
            {
                r = read(order, i);
                c = read(order, i);
                if (r == 0 || c == 0 || r > row || c > column || m_Map.map[r][c].display == true)
                {
                    cout << "不合法！";
                    break;
                }
                else
                {
                    rightClick(r, c);
                    now = time(0);
                    m_Map.printMap();
                    cout << "计时：" << difftime(now, begin) << "s" << endl;
                    break;
                }
            }
            else if (order[i] == 's' || order[i] == 'S')
            {
                r = read(order, i);
                c = read(order, i);
                if (m_Map.map[r][c].display == true && m_Map.map[r][c].correct_mark + m_Map.map[r][c].error_mark == m_Map.map[r][c].val)
                {
                    bothClick(r, c);
                    now = time(0);
                    m_Map.printMap();
                    cout << "计时：" << difftime(now, begin) << "s" << endl;
                    break;
                }
                else
                {
                    cout << "无效双击！";
                    break;
                }
            }
            else if (order[i] == 'e' || order[i] == 'E')
            {
                if_end();
                break;
            }
            else if (order[i] == 'r' || order[i] == 'R')
            {
                if_restart();
                break;
            }
            else if (order[i] == 'h' || order[i] == 'H')
            {
                helpPage();
                break;
            }
            else if (i == order.size() - 1)
            {
                cout << "不合法！";
                break;
            }
            else
                continue;
        }
    }
}
//开始游戏
void Player::startGame()
{
    int row, column, mine;
    cout << "请自定义行数、列数、地雷数：" << endl;
    while ((!(cin >> row >> column >> mine)) || row <= 0 || column <= 0 || mine > row * column || mine <= 0 || row >= 24 || column >= 30)
    { //防恶意输入
        cout << "不合法!请重新自定义行数、列数、地雷数：" << endl;
        cin.clear();
        cin.sync(); //表示清除缓存区的数据流
    }
    this->row = row;
    this->column = column;
    this->num = mine;
    m_Map.iniMap(row, column, mine);
    m_Map.printMap(); //打印地雷图
    cin.ignore();     //跳过键盘缓冲区的一个或多个字符
    read_first_order();
    playGame();
}
//游戏进行
void Player::playGame()
{
    read_order();
    successGame();
}
//左键模拟。只能对隐藏格子操作
//参数：方块的坐标
void Player::leftClick(int i, int j)
{
    if (m_Map.map[i][j].val >= 9)
    {
        failGame();
    }
    m_Map.map[i][j].display = true;
    if (m_Map.map[i][j].val == 0)
        autoExpose(i, j); //如果该点数值为0，自动揭开周围八个位置
    --m_Map.m_hidden;
}
//对符合条件的格子进行类似左键的操作。条件为不是边界、不是雷区、没有揭开。遇到不符合条件的跳过该格
//参数：方块的坐标
void Player::autoDisplay(int i, int j)
{
    if (m_Map.map[i][j].val >= 9)
        return;
    if (i == 0 || j == 0 || i == row + 1 || j == column + 1)
        return;
    if (m_Map.map[i][j].display == true)
        return;
    m_Map.map[i][j].display = true;
    --m_Map.m_hidden;
    if (m_Map.map[i][j].val == 0)
        autoExpose(i, j);
}
//对周围8个符合条件的格子进行类似左键的操作
//参数：方块的坐标
void Player::autoExpose(int i, int j)
{
    if (i == 0 || j == 0 || i == row + 1 || j == column + 1)
        return;
    else
    {
        autoDisplay(i - 1, j);
        autoDisplay(i, j - 1);
        autoDisplay(i + 1, j);
        autoDisplay(i, j + 1);
        autoDisplay(i + 1, j - 1);
        autoDisplay(i - 1, j + 1);
        autoDisplay(i + 1, j + 1);
        autoDisplay(i - 1, j - 1);
    }
}
//右键模拟。只能对隐藏格子或标雷格子操作
//参数：方块的坐标
void Player::rightClick(int i, int j)
{
    if (m_Map.map[i][j].mark == 0) //未标记的
    {
        --m_Map.m_noMark;
        if (m_Map.map[i][j].val >= 9) //雷区
        {
            ++m_Map.m_rightMark;      //增加总的正确标记的个数
            m_Map.map[i][j].mark = 1; // mark==1表示该格是正确标雷的
            ++m_Map.map[i - 1][j - 1].correct_mark;
            ++m_Map.map[i - 1][j + 1].correct_mark;
            ++m_Map.map[i + 1][j - 1].correct_mark;
            ++m_Map.map[i + 1][j + 1].correct_mark;
            ++m_Map.map[i - 1][j].correct_mark;
            ++m_Map.map[i][j - 1].correct_mark;
            ++m_Map.map[i + 1][j].correct_mark;
            ++m_Map.map[i][j + 1].correct_mark;
        }
        else
        {
            m_Map.map[i][j].mark = 2; // mark==2表示该格无雷，被错误标记
            ++m_Map.map[i - 1][j - 1].error_mark;
            ++m_Map.map[i - 1][j + 1].error_mark;
            ++m_Map.map[i + 1][j - 1].error_mark;
            ++m_Map.map[i + 1][j + 1].error_mark;
            ++m_Map.map[i - 1][j].error_mark;
            ++m_Map.map[i][j - 1].error_mark;
            ++m_Map.map[i + 1][j].error_mark;
            ++m_Map.map[i][j + 1].error_mark;
        }
    }
    else if (m_Map.map[i][j].mark == 1) //对已标记的，再次右键即撤回标记
    {
        ++m_Map.m_noMark;
        --m_Map.m_rightMark;
        m_Map.map[i][j].mark = 0;
        --m_Map.map[i - 1][j - 1].correct_mark;
        --m_Map.map[i - 1][j + 1].correct_mark;
        --m_Map.map[i + 1][j - 1].correct_mark;
        --m_Map.map[i + 1][j + 1].correct_mark;
        --m_Map.map[i - 1][j].correct_mark;
        --m_Map.map[i][j - 1].correct_mark;
        --m_Map.map[i + 1][j].correct_mark;
        --m_Map.map[i][j + 1].correct_mark;
    }
    else if (m_Map.map[i][j].mark == 2) //对已标记的，再次右键即撤回标记
    {
        ++m_Map.m_noMark;
        m_Map.map[i][j].mark = 0;
        --m_Map.map[i - 1][j - 1].error_mark;
        --m_Map.map[i - 1][j + 1].error_mark;
        --m_Map.map[i + 1][j - 1].error_mark;
        --m_Map.map[i + 1][j + 1].error_mark;
        --m_Map.map[i - 1][j].error_mark;
        --m_Map.map[i][j - 1].error_mark;
        --m_Map.map[i + 1][j].error_mark;
        --m_Map.map[i][j + 1].error_mark;
    }
    else
        return;
}
//双击模拟。条件为该格已被揭开，且该格周围地雷被正确标记。若该格子揭开且周围有错误标记，判游戏失败
//参数：方块的坐标
void Player::bothClick(int i, int j)
{
    if (!m_Map.map[i][j].error_mark)
    {
        autoDisplay(i + 1, j + 1);
        autoDisplay(i + 1, j - 1);
        autoDisplay(i - 1, j + 1);
        autoDisplay(i - 1, j - 1);
        autoDisplay(i + 1, j);
        autoDisplay(i, j + 1);
        autoDisplay(i - 1, j);
        autoDisplay(i, j - 1);
    }
    else
    {
        failGame();
    }
}
//帮助界面
void Player::helpPage()
{
    system("cls");
    cout << "|口令          |"
         << "提示" << endl;
    cout << "****************" << endl;
    cout << "|a/A 左键模拟  |"
         << "先输入字符再输入坐标。口令须在一行内完成输入，可用空格或其他有意义的字符间隔" << endl;
    cout << "****************" << endl;
    cout << "|d/D 右键模拟  |"
         << "先输入字符再输入坐标。口令须在一行内完成输入，可用空格或其他有意义的字符间隔。右键两次可取消标记" << endl;
    cout << "****************" << endl;
    cout << "|s/S 双击模拟  |"
         << "先输入字符再输入坐标。口令须在一行内完成输入，可用空格或其他有意义的字符间隔。不可对未翻开的位置进行操作" << endl;
    cout << "****************" << endl;
    cout << "|r/R 重开游戏  |"
         << "不需要输入坐标" << endl;
    cout << "****************" << endl;
    cout << "|e/E 结束游戏  |"
         << "不需要输入坐标" << endl;
    cout << "****************" << endl;
    cout << "|f/F 返回游戏界面" << endl;
    cout << "****************" << endl;
    char choice;
    while (true)
    {
        cin >> choice;
        if (choice == 'F' || choice == 'f')
        {
            returnGame();
            break;
        }
        else if (choice == 'e' || choice == 'E')
        {
            if_end();
            break;
        }
        else if (choice == 'r' || choice == 'R')
        {
            if_restart();
            break;
        }
        else
        {
            cout << "无效输入,请重新输入:" << endl;
            cin.clear();
            cin.sync();
            continue;
        }
    }
}
//重新设置。清空动态数组，未初始化，重新开始游戏
void Player::resetGame()
{
    m_Map.map.clear();
    m_Map.if_iniMine = false;
    startGame();
}
//判断扫雷是否成功。条件为揭开所有不是地雷的格子
bool Player::passGame()
{
    if (m_Map.m_hidden == num)
        return true;
    else
        return false;
}
//扫雷成功。提示玩家判断是否开始新一轮扫雷
void Player::successGame()
{
    cout << "扫雷成功！真不愧是你呀~" << endl;
    if_reset();
}
//结束游戏。用exit终止程序
void Player::endGame()
{
    cout << "欢迎下次使用,bye~" << endl;
    system("pause");
    exit(0);
}
//返回进行中的游戏
void Player::returnGame()
{
    cin.ignore();
    system("cls");
    if (m_Map.if_iniMine)
    {
        now = time(0);
        m_Map.printMap();
        cout << "计时：" << difftime(now, begin) << "s" << endl;
        playGame();
    }
    else
    {
        m_Map.printMap();
        read_first_order();
    }
}
//踩到地雷扫雷失败。提示玩家判断是否开始新一轮扫雷
void Player::failGame()
{
    m_Map.printAll();
    cout << "BOOM!是意外啦,才不会轻易狗带呢!" << endl;
    if_reset();
}
//是否重新开始游戏。若是，则重新开始；若不是，则返回进行中的游戏
void Player::if_restart()
{
    cout << "是否重新开始游戏?" << endl
         << "Y/N" << endl;
    char choice;
    while (true)
    {
        cin >> choice;
        if (choice == 'Y' || choice == 'y')
        {
            system("cls");
            resetGame();
            break;
        }
        else if (choice == 'N' || choice == 'n')
        {
            returnGame();
            break;
        }
        else
        {
            cout << "无效输入,请重新输入:Y/N" << endl;
            cin.clear();
            cin.sync();
            continue;
        }
    }
}
//是否重置游戏。若是，则重置游戏；若否，则结束程序
void Player::if_reset()
{
    cout << "是否重新开始游戏?" << endl
         << "Y/N" << endl;
    char choice;
    while (true)
    {
        cin >> choice;
        if (choice == 'Y' || choice == 'y')
        {
            system("cls");
            cin.ignore();
            resetGame();
            break;
        }
        else if (choice == 'N' || choice == 'n')
        {
            endGame();
            break;
        }
        else
        {
            cout << "无效输入,请重新输入:Y/N" << endl;
            cin.clear();
            cin.sync();
            continue;
        }
    }
}
//是否结束程序。若是，则结束程序；若否，则返回进行中的游戏
void Player::if_end()
{
    cout << "是否结束游戏?" << endl
         << "Y/N" << endl;
    char choice;
    while (true)
    {
        cin >> choice;
        if (choice == 'Y' || choice == 'y')
        {
            endGame();
            break;
        }
        else if (choice == 'N' || choice == 'n')
        {
            returnGame();
            break;
        }
        else
        {
            cout << "无效输入,请重新输入:Y/N" << endl;
            cin.clear();
            cin.sync();
            continue;
        }
    }
}