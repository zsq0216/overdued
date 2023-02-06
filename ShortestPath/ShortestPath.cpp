#include "ShortestPath.h"

using namespace std;

//构造函数:初始化邻接矩阵
SHANGHAI::SHANGHAI()
{
    int i;
    walkCost.resize(size);//步行边
    subwayCost.resize(size);//地铁边
    for (i = Natural_Museum; i <= Pearl_Tower; ++i)
    {
        walkCost[i].resize(size, NONE);
        subwayCost[i].resize(size, NONE);
    }
    for (i = Natural_Museum; i <= Pearl_Tower; ++i)
    {
        walkCost[i][i] = 0;
        subwayCost[i][i] = 0;
    }
    walkCost[Natural_Museum][Nanjing_WestRoad] = 14;
    walkCost[Nanjing_WestRoad][Natural_Museum] = 14;

    walkCost[Xinzha_Road][Natural_Museum] = 12;
    walkCost[Natural_Museum][Xinzha_Road] = 12;

    walkCost[Nanjing_WestRoad][SouthNorth_Viaduct] = 7;
    walkCost[SouthNorth_Viaduct][Nanjing_WestRoad] = 7;

    walkCost[SouthNorth_Viaduct][PS_station] = 12;
    walkCost[PS_station][SouthNorth_Viaduct] = 12;

    walkCost[Xinzha_Road][PS_station] = 8;
    walkCost[PS_station][Xinzha_Road] = 8;

    walkCost[SouthNorth_Viaduct][Yanan_Flyover] = 10;
    walkCost[Yanan_Flyover][SouthNorth_Viaduct] = 10;

    walkCost[Yanan_Flyover][PeopleSquare] = 15;
    walkCost[PeopleSquare][Yanan_Flyover] = 15;

    walkCost[PeopleSquare][PS_station] = 6;
    walkCost[PS_station][PeopleSquare] = 6;

    walkCost[Yanan_Flyover][Memorial] = 5;
    walkCost[Memorial][Yanan_Flyover] = 5;

    walkCost[Memorial][BigWorld] = 7;
    walkCost[BigWorld][Memorial] = 7;

    walkCost[BigWorld][PeopleSquare] = 4;
    walkCost[PeopleSquare][BigWorld] = 4;

    walkCost[PS_station][Qufu_Road] = 15;
    walkCost[Qufu_Road][PS_station] = 15;

    walkCost[Qufu_Road][Jingan_Joy] = 3;
    walkCost[Jingan_Joy][Qufu_Road] = 3;

    walkCost[Qufu_Road][Tiantong_Road] = 12;
    walkCost[Tiantong_Road][Qufu_Road] = 12;

    walkCost[Tiantong_Road][Nanjing_EestRoad] = 10;
    walkCost[Nanjing_EestRoad][Tiantong_Road] = 10;

    walkCost[Nanjing_EestRoad][PS_station] = 13;
    walkCost[PS_station][Nanjing_EestRoad] = 13;

    walkCost[PeopleSquare][Fuzhou_Road] = 6;
    walkCost[Fuzhou_Road][PeopleSquare] = 6;

    walkCost[Fuzhou_Road][Henan_MidRoad] = 5;
    walkCost[Henan_MidRoad][Fuzhou_Road] = 5;

    walkCost[Henan_MidRoad][Nanjing_EestRoad] = 4;
    walkCost[Nanjing_EestRoad][Henan_MidRoad] = 4;

    walkCost[Henan_MidRoad][Yanan_EastRoad] = 5;
    walkCost[Yanan_EastRoad][Henan_MidRoad] = 5;

    walkCost[PeopleSquare][Yanan_EastRoad] = 10;
    walkCost[Yanan_EastRoad][PeopleSquare] = 10;

    walkCost[BigWorld][Yu_Garden] = 9;
    walkCost[Yu_Garden][BigWorld] = 9;

    walkCost[Yu_Garden][Yanan_EastRoad] = 3;
    walkCost[Yanan_EastRoad][Yu_Garden] = 3;

    walkCost[Yu_Garden][City_Temple] = 11;
    walkCost[City_Temple][Yu_Garden] = 11;

    walkCost[City_Temple][People_Tunnel] = 11;
    walkCost[People_Tunnel][City_Temple] = 11;

    walkCost[Yu_Garden][People_Tunnel] = 10;
    walkCost[People_Tunnel][Yu_Garden] = 10;

    walkCost[Nanjing_EestRoad][Peace_Hotel] = 7;
    walkCost[Peace_Hotel][Nanjing_EestRoad] = 7;

    walkCost[Peace_Hotel][Bund] = 13;
    walkCost[Bund][Peace_Hotel] = 13;

    walkCost[Bund][Yanan_EastRoad] = 6;
    walkCost[Yanan_EastRoad][Bund] = 6;

    walkCost[Bund][People_Tunnel] = 8;
    walkCost[People_Tunnel][Bund] = 8;

    walkCost[People_Tunnel][Lujiazui] = 20;
    walkCost[Lujiazui][People_Tunnel] = 20;

    walkCost[Lujiazui][Pearl_Tower] = 9;
    walkCost[Pearl_Tower][Lujiazui] = 9;

    subwayCost[Natural_Museum][Nanjing_WestRoad] = 7;
    subwayCost[Nanjing_WestRoad][Natural_Museum] = 7;

    subwayCost[Nanjing_WestRoad][PS_station] = 3;
    subwayCost[PS_station][Nanjing_WestRoad] = 3;

    subwayCost[PS_station][Xinzha_Road] = 6;
    subwayCost[Xinzha_Road][PS_station] = 6;

    subwayCost[PS_station][Nanjing_EestRoad] = 3;
    subwayCost[Nanjing_EestRoad][PS_station] = 3;

    subwayCost[PS_station][BigWorld] = 3;
    subwayCost[BigWorld][PS_station] = 3;

    subwayCost[PS_station][Memorial] = 7;
    subwayCost[Memorial][PS_station] = 7;

    subwayCost[PS_station][Qufu_Road] = 3;
    subwayCost[Qufu_Road][PS_station] = 3;

    subwayCost[Qufu_Road][Tiantong_Road] = 7;
    subwayCost[Tiantong_Road][Qufu_Road] = 7;

    subwayCost[Tiantong_Road][Nanjing_EestRoad] = 4;
    subwayCost[Nanjing_EestRoad][Tiantong_Road] = 4;

    subwayCost[BigWorld][Memorial] = 6;
    subwayCost[Memorial][BigWorld] = 6;

    subwayCost[BigWorld][Yu_Garden] = 6;
    subwayCost[Yu_Garden][BigWorld] = 6;

    subwayCost[Yu_Garden][Nanjing_EestRoad] = 5;
    subwayCost[Nanjing_EestRoad][Yu_Garden] = 5;

    subwayCost[Nanjing_EestRoad][Lujiazui] = 4;
    subwayCost[Lujiazui][Nanjing_EestRoad] = 4;

    subwayCost[Yu_Garden][Lujiazui] = 7;
    subwayCost[Lujiazui][Yu_Garden] = 7;
}
SHANGHAI::~SHANGHAI() {}

//单一步行路径
void SHANGHAI::DIJKSTRA(int start, int end)
{
    vector<int> res(size, NONE);//单源到达某点的最短时间
    vector<int> pre(size, NIL);//路径上某点的先驱结点
    vector<bool> vis(size, false); //是否访问过该结点

    priority_queue<vertice> cur_q;//优先队列
    res[start] = 0;

    cur_q.push({start, 0});//入队操作

    while (!cur_q.empty())//退出循环条件——队列为空
    {
        int cur_v = cur_q.top().num;
        cur_q.pop();

        if (vis[cur_v])
            continue;
        vis[cur_v] = true;
        for (int i = 0; i <= Pearl_Tower; ++i)
        {
            if (walkCost[cur_v][i] != NONE)
            {
                if (!vis[i] && res[i] > res[cur_v] + walkCost[cur_v][i])
                {
                    res[i] = res[cur_v] + walkCost[cur_v][i];
                    pre[i] = cur_v;
                    cur_q.push({i, res[i]});
                }
            }
        }
    }
    //算法主体部分到此结束
    //接下来是输出操作
    int u = end;
    string output;
    while (u != NIL)
    {
        output = strSite[u] + output;
        if (pre[u] != NIL)
        {
            output = "min >>\n" + output;
            output = intTOstr(walkCost[pre[u]][u]) + output;
            output = "\n>> walk " + output;
        }
        u = pre[u];
    }
    output+="\nTOTAL TIME: ";
    output+=intTOstr(res[end]);
    output+=" min";
    cout << output;
}

//地铁优先——复合路径
void SHANGHAI::subDIJKSTRA(int start, int end)
{
    vector<int> res(size, NONE);
    vector<int> pre(size, NIL);
    vector<bool> vis(size, false); 

    priority_queue<vertice> cur_q;
    res[start] = 0;

    cur_q.push({start, 0});
    while (!cur_q.empty())
    {
        int cur_v = cur_q.top().num;
        cur_q.pop();

        if (vis[cur_v])
            continue;
        vis[cur_v] = true;
        if (!isMetro[cur_v])//若地铁不可达，找步行边
        {
            for (int i = 0; i <= Pearl_Tower; ++i)
            {
                if (walkCost[cur_v][i] != NONE)
                {
                    if (!vis[i] && res[i] > res[cur_v] + walkCost[cur_v][i]) // vis可以给算法加速
                    {
                        res[i] = res[cur_v] + walkCost[cur_v][i];
                        pre[i] = cur_v;
                        cur_q.push({i, res[i]});
                    }
                }
            }
        }
        else//若地铁可达，找地铁边
        {
            for (int i = 0; i <= Pearl_Tower; ++i)
            {
                if (subwayCost[cur_v][i] != NONE && cur_v != i)
                {
                    if (!vis[i] && res[i] > res[cur_v] + subwayCost[cur_v][i])
                    {
                        res[i] = res[cur_v] + subwayCost[cur_v][i];
                        pre[i] = cur_v;
                        cur_q.push({i, res[i]});
                    }
                }
            }
        }
    }
    if (!isMetro[end]) //若终点不是地铁站，则还要另外寻找从某一个地铁站到终点的最短路径
    {
        vector<int> backres(size, NONE);
        vector<bool> revis(size, false);
        vector<int> next(size, NIL);
        backres[end] = 0;
        int internal = -1;
        cur_q.push({end, 0});

        while (!cur_q.empty())
        {
            int cur_v = cur_q.top().num;
            cur_q.pop();

            if (revis[cur_v] && isMetro[cur_v])
                continue;
            revis[cur_v] = true;
            for (int i = 0; i <= Pearl_Tower; ++i)
            {
                if (walkCost[cur_v][i] != NONE)
                {
                    if (!revis[i] && backres[i] > backres[cur_v] + walkCost[cur_v][i])
                    {
                        backres[i] = backres[cur_v] + walkCost[cur_v][i];
                        next[i] = cur_v;
                        // next[i]=cur_v;
                        cur_q.push({i, backres[i]});
                    }
                }
            }
            for (int i = 0; i <= Pearl_Tower; ++i)
            {
                if (isMetro[i] && res[i] + backres[i] < res[end])
                {
                    internal = i;
                    res[end] = res[i] + backres[i]; // pre[i]还没改
                }
            }
        }
        //算法主体部分到此结束
        //接下来是输出操作
        string output;
        int u = internal;
        while (u != NIL)
        {
            output += strSite[u];
            if (next[u] != NIL)
            {
                output += "\n>> walk ";
                output += intTOstr(walkCost[u][next[u]]);
                output += "min >>\n";
            }
            u = next[u];
        }
        u = internal;
        while (pre[u] != NIL)
        {
            if (isMetro[pre[u]])
            {
                output = "min >>\n" + output;
                output = intTOstr(subwayCost[pre[u]][u]) + output;
                output = "\n>> subway " + output;
            }
            else
            {
                output = "min >>\n" + output;
                output = intTOstr(walkCost[pre[u]][u]) + output;
                output = "\n>> walk " + output;
            }
            u = pre[u];
            output = strSite[u] + output;
        }
        output += "\nTOTAL TIME: ";
        output += intTOstr(res[end]);
        output += " min";
        cout << output;
        return;
    }
    //算法主体部分到此结束
    //接下来是输出操作
    int u = end;
    string output;
    while (u != NIL)
    {
        output = strSite[u] + output;
        if (pre[u] != NIL)
        {
            output = "min >>\n" + output;
            if (isMetro[pre[u]])
            {
                output = intTOstr(subwayCost[pre[u]][u]) + output;
                output = "\n>> subway " + output;
            }
            else
            {
                output = intTOstr(walkCost[pre[u]][u]) + output;
                output = "\n>> walk " + output;
            }
        }
        u = pre[u];
    }
    output += "\nTOTAL TIME: ";
    output += intTOstr(res[end]);
    output += " min";
    cout << output;
}
//转整型为字符串
string SHANGHAI::intTOstr(int a)
{
    char a1, a2;
    string ans;
    a1 = a % 10 + '0';
    if (a / 10)
    {
        a2 = a / 10 + '0';
        ans += a2;
        ans += a1;
        return ans;
    }
    ans += a1;
    return ans;
}