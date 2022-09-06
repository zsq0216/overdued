#include "Player.h"
using namespace std;

//Ĭ�ϳ�ʼ��Ϊ0
Player::Player() : row(0), column(0), num(0) {}
//û��Ҫ�ֶ��ͷŵ��ڴ棬���û���ò���ͺ���
Player::~Player()
{
    cout << "���Ѿ��˳���Ϸ��" << endl;
}
//�������е�����
//�����������ַ�����ָ����ʼ����λ��
//����ֵ�������ĵ�һ��������
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
//����һ�������ɵ���λ�õĳ�ʼ��
void Player::read_first_order()
{
    int tick = 1;
    while (tick)
    {
        string order;
        cout << "���������:" << endl;
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
                    cout << "���Ϸ���";
                    break;
                }
                else
                {
                    --tick;
                    m_Map.createPosition(r, c); //��������λ��
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
                cout << "���Ϸ���";
                break;
            }
            else
                continue;
        }
    }
}
//��Ϸ�����ж�����
void Player::read_order()
{
    while (!passGame())
    {
        cout << "���������:" << endl;
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
                    cout << "���Ϸ���";
                    break;
                }
                else
                {
                    leftClick(r, c);
                    now = time(0);
                    m_Map.printMap();
                    cout << "��ʱ��" << difftime(now, begin) << "s" << endl;
                    break;
                }
            }
            else if (order[i] == 'd' || order[i] == 'D')
            {
                r = read(order, i);
                c = read(order, i);
                if (r == 0 || c == 0 || r > row || c > column || m_Map.map[r][c].display == true)
                {
                    cout << "���Ϸ���";
                    break;
                }
                else
                {
                    rightClick(r, c);
                    now = time(0);
                    m_Map.printMap();
                    cout << "��ʱ��" << difftime(now, begin) << "s" << endl;
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
                    cout << "��ʱ��" << difftime(now, begin) << "s" << endl;
                    break;
                }
                else
                {
                    cout << "��Ч˫����";
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
                cout << "���Ϸ���";
                break;
            }
            else
                continue;
        }
    }
}
//��ʼ��Ϸ
void Player::startGame()
{
    int row, column, mine;
    cout << "���Զ�����������������������" << endl;
    while ((!(cin >> row >> column >> mine)) || row <= 0 || column <= 0 || mine > row * column || mine <= 0 || row >= 24 || column >= 30)
    { //����������
        cout << "���Ϸ�!�������Զ�����������������������" << endl;
        cin.clear();
        cin.sync(); //��ʾ�����������������
    }
    this->row = row;
    this->column = column;
    this->num = mine;
    m_Map.iniMap(row, column, mine);
    m_Map.printMap(); //��ӡ����ͼ
    cin.ignore();     //�������̻�������һ�������ַ�
    read_first_order();
    playGame();
}
//��Ϸ����
void Player::playGame()
{
    read_order();
    successGame();
}
//���ģ�⡣ֻ�ܶ����ظ��Ӳ���
//���������������
void Player::leftClick(int i, int j)
{
    if (m_Map.map[i][j].val >= 9)
    {
        failGame();
    }
    m_Map.map[i][j].display = true;
    if (m_Map.map[i][j].val == 0)
        autoExpose(i, j); //����õ���ֵΪ0���Զ��ҿ���Χ�˸�λ��
    --m_Map.m_hidden;
}
//�Է��������ĸ��ӽ�����������Ĳ���������Ϊ���Ǳ߽硢����������û�нҿ������������������������ø�
//���������������
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
//����Χ8�����������ĸ��ӽ�����������Ĳ���
//���������������
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
//�Ҽ�ģ�⡣ֻ�ܶ����ظ��ӻ���׸��Ӳ���
//���������������
void Player::rightClick(int i, int j)
{
    if (m_Map.map[i][j].mark == 0) //δ��ǵ�
    {
        --m_Map.m_noMark;
        if (m_Map.map[i][j].val >= 9) //����
        {
            ++m_Map.m_rightMark;      //�����ܵ���ȷ��ǵĸ���
            m_Map.map[i][j].mark = 1; // mark==1��ʾ�ø�����ȷ���׵�
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
            m_Map.map[i][j].mark = 2; // mark==2��ʾ�ø����ף���������
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
    else if (m_Map.map[i][j].mark == 1) //���ѱ�ǵģ��ٴ��Ҽ������ر��
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
    else if (m_Map.map[i][j].mark == 2) //���ѱ�ǵģ��ٴ��Ҽ������ر��
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
//˫��ģ�⡣����Ϊ�ø��ѱ��ҿ����Ҹø���Χ���ױ���ȷ��ǡ����ø��ӽҿ�����Χ�д����ǣ�����Ϸʧ��
//���������������
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
//��������
void Player::helpPage()
{
    system("cls");
    cout << "|����          |"
         << "��ʾ" << endl;
    cout << "****************" << endl;
    cout << "|a/A ���ģ��  |"
         << "�������ַ����������ꡣ��������һ����������룬���ÿո��������������ַ����" << endl;
    cout << "****************" << endl;
    cout << "|d/D �Ҽ�ģ��  |"
         << "�������ַ����������ꡣ��������һ����������룬���ÿո��������������ַ�������Ҽ����ο�ȡ�����" << endl;
    cout << "****************" << endl;
    cout << "|s/S ˫��ģ��  |"
         << "�������ַ����������ꡣ��������һ����������룬���ÿո��������������ַ���������ɶ�δ������λ�ý��в���" << endl;
    cout << "****************" << endl;
    cout << "|r/R �ؿ���Ϸ  |"
         << "����Ҫ��������" << endl;
    cout << "****************" << endl;
    cout << "|e/E ������Ϸ  |"
         << "����Ҫ��������" << endl;
    cout << "****************" << endl;
    cout << "|f/F ������Ϸ����" << endl;
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
            cout << "��Ч����,����������:" << endl;
            cin.clear();
            cin.sync();
            continue;
        }
    }
}
//�������á���ն�̬���飬δ��ʼ�������¿�ʼ��Ϸ
void Player::resetGame()
{
    m_Map.map.clear();
    m_Map.if_iniMine = false;
    startGame();
}
//�ж�ɨ���Ƿ�ɹ�������Ϊ�ҿ����в��ǵ��׵ĸ���
bool Player::passGame()
{
    if (m_Map.m_hidden == num)
        return true;
    else
        return false;
}
//ɨ�׳ɹ�����ʾ����ж��Ƿ�ʼ��һ��ɨ��
void Player::successGame()
{
    cout << "ɨ�׳ɹ����治������ѽ~" << endl;
    if_reset();
}
//������Ϸ����exit��ֹ����
void Player::endGame()
{
    cout << "��ӭ�´�ʹ��,bye~" << endl;
    system("pause");
    exit(0);
}
//���ؽ����е���Ϸ
void Player::returnGame()
{
    cin.ignore();
    system("cls");
    if (m_Map.if_iniMine)
    {
        now = time(0);
        m_Map.printMap();
        cout << "��ʱ��" << difftime(now, begin) << "s" << endl;
        playGame();
    }
    else
    {
        m_Map.printMap();
        read_first_order();
    }
}
//�ȵ�����ɨ��ʧ�ܡ���ʾ����ж��Ƿ�ʼ��һ��ɨ��
void Player::failGame()
{
    m_Map.printAll();
    cout << "BOOM!��������,�Ų������׹�����!" << endl;
    if_reset();
}
//�Ƿ����¿�ʼ��Ϸ�����ǣ������¿�ʼ�������ǣ��򷵻ؽ����е���Ϸ
void Player::if_restart()
{
    cout << "�Ƿ����¿�ʼ��Ϸ?" << endl
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
            cout << "��Ч����,����������:Y/N" << endl;
            cin.clear();
            cin.sync();
            continue;
        }
    }
}
//�Ƿ�������Ϸ�����ǣ���������Ϸ���������������
void Player::if_reset()
{
    cout << "�Ƿ����¿�ʼ��Ϸ?" << endl
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
            cout << "��Ч����,����������:Y/N" << endl;
            cin.clear();
            cin.sync();
            continue;
        }
    }
}
//�Ƿ�����������ǣ���������������򷵻ؽ����е���Ϸ
void Player::if_end()
{
    cout << "�Ƿ������Ϸ?" << endl
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
            cout << "��Ч����,����������:Y/N" << endl;
            cin.clear();
            cin.sync();
            continue;
        }
    }
}