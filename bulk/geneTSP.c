#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#define cityNum 10
#define popSize 10
#define croRate 0.85
#define mutRate 0.1
#define MAX 999

//定义染色体的结构
struct Chrom
{
    int cityArr[cityNum]; // 城市下标序列
    char name;            // 城市名
    float adapt;          // 适应度
    int dis;
};
struct Chrom genes[popSize];
struct Chrom genesNew[popSize];
struct Chrom temp;

char names[cityNum] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

int distance[cityNum][cityNum] = {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
                                  {1, 0, 1, 2, 3, 4, 5, 6, 7, 8},
                                  {2, 1, 0, 1, 2, 3, 4, 5, 6, 7},
                                  {3, 2, 1, 0, 1, 2, 3, 4, 5, 6},
                                  {4, 3, 2, 1, 0, 1, 2, 3, 4, 5},
                                  {5, 4, 3, 2, 1, 0, 1, 2, 3, 4},
                                  {6, 5, 4, 3, 2, 1, 0, 1, 2, 3},
                                  {7, 6, 5, 4, 3, 2, 1, 0, 1, 2},
                                  {8, 7, 6, 5, 4, 3, 2, 1, 0, 1},
                                  {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}};

// 初始化全部染色体
void initGroup()
{
    int i, j, k;
    int t = 0;
    int flag = 0;
    srand(time(NULL));
    for (i = 0; i < popSize; i++)
    {

        temp.name = names[i];
        temp.adapt = 0.0f;
        temp.dis = 0;

        // 随机生成一个对应城市下标的数，塞入染色体中
        for (j = 0; j < cityNum;)
        {
            t = rand() % cityNum;
            flag = 1;
            for (k = 0; k < j; k++)
            {
                if (genes[i].cityArr[k] == t)
                {
                    flag = 0;
                    break;
                }
            }
            if (flag)
            {
                temp.cityArr[j] = t;
                genes[i] = temp;
                j++;
            }
        }
    }
}

// 计算每个染色体内距离，计算适应度 adapt = 1 / dis
void popFitness()
{
    int i, n1, n2;
    for (i = 0; i < popSize; i++)
    {
        genes[i].dis = 0;
        for (int j = 1; j < cityNum; j++)
        {
            n1 = genes[i].cityArr[j - 1];
            n2 = genes[i].cityArr[j];
            genes[i].dis += distance[n1][n2];
        }
        genes[i].dis += distance[genes[i].cityArr[0]][genes[i].cityArr[cityNum - 1]];
        genes[i].adapt = (float)1 / genes[i].dis;
    }
}

// 返回适应度最小的染色体下标
int chooseBest()
{
    int choose = 0;
    float best = 0.0f;
    best = genes[0].adapt;
    for (int i = 0; i < popSize; i++)
    {
        if (genes[i].adapt < best)
        {
            best = genes[i].adapt;
            choose = i;
        }
    }
    return choose;
}

// 选择稍后进行杂交的基因，未被选中的将被遗忘。
void select()
{
    float biggestSum = 0.0f;
    float adapt_pro[popSize];
    float pick = 0.0f;
    int i;
    // 计算全部适应度之和，然后按适应度占比计算杂交概率存储在adapt_pro[]中。
    for (i = 0; i < popSize; i++)
    {
        biggestSum += genes[i].adapt;
    }
    for (i = 0; i < popSize; i++)
    {
        adapt_pro[i] = genes[i].adapt / biggestSum;
    }
    // 随机选择稍后进行杂交的基因，存储在genesNew[]中。
    for (i = 0; i < popSize; i++)
    {
        pick = (float)rand() / RAND_MAX;
        /********** Begin **********/
        int flag = 0;
        int pro = 0;
        for (int j = 0; j < popSize; j++)
        {
            pick = pick - adapt_pro[j]; // pick 越来越小，因adapt_pro[]之和为1，到最后必然有一个被选中
            if (pick <= 0)
            {
                genesNew[i] = genes[j];
                break;
            }
            /* 随机方式2，可行，但为了避免genesNew[]中空基因的存在，需要增加flag。*/
            // if(pick <= adapt_pro[j])
            // {
            //     genesNew[i] = genes[j];
            //     flag = 1;
            //     break;
            // }
            /* 随机方式3，可行，充分利用了概率相加等于1、概率与适应度正相关的特性。*/
            // todo: 为什么错误？
            // pro = pro + adapt_pro[j];
            // if(pick <= pro)
            // {
            //     genesNew[i] = genes[j];
            //     break;
            // }
        }
        /* 随机方式4，不可行，设置不同的种子会有不同的结果，可能是因为破坏了选取概率与适应度的相关性，导致选取过程成了完全无信息的随机选取。*/
        /*
        srand(i+1);
        genesNew[i] = genes[rand()%popSize];
        */
        /* 随机方式2，可行 */
        // if(!flag)
        //     genesNew[i] = genes[rand()%popSize];

        /********** End **********/
    }
    for (i = 0; i < popSize; i++)
    {
        genes[i] = genesNew[i];
    }
}

// 相邻两两配对杂交
void cross()
{
    float pick;
    int choice1, choice2;
    int pos1, pos2;
    int temp;
    int conflict1[popSize];
    int conflict2[popSize];
    int num1, num2;
    int index1, index2;
    int move = 0;
    while (move < popSize - 1)
    {
        pick = (float)rand() / RAND_MAX;
        // 根据生成随机数及设定概率确定相邻两染色体是否杂交。
        if (pick > croRate)
        {
            move += 2;
            continue;
        }
        choice1 = move;
        choice2 = move + 1;
        pos1 = rand() % popSize;
        pos2 = rand() % popSize;
        while (pos1 > popSize - 2 || pos1 < 1) // 开头与结尾不交换
        {
            pos1 = rand() % popSize;
        }
        while (pos2 > popSize - 2 || pos2 < 1)
        {
            pos2 = rand() % popSize;
        }
        if (pos1 > pos2) // 令pos2 >= pos1
        {
            temp = pos1;
            pos1 = pos2;
            pos2 = temp;
        }
        // 将染色体choice1和choice2上，处于pos1到pos2（左闭右闭）之间的基因交换
        for (int j = pos1; j <= pos2; j++)
        {
            temp = genes[choice1].cityArr[j];
            genes[choice1].cityArr[j] = genes[choice2].cityArr[j];
            genes[choice2].cityArr[j] = temp;
        }

        num1 = 0;
        num2 = 0;
        // 判断必过
        if (pos1 > 0 && pos2 < popSize - 1)
        {
            // 因为每个因子只有两份，倘若染色体一已有两份，则染色体二不可能再有，反之亦然，因此互相给予自己重复的基因。
            /********** Begin **********/
            for (int j = 0; j < pos1; j++)
            {
                for (int k = pos1; k <= pos2; k++)
                {
                    if (genes[choice1].cityArr[j] == genes[choice1].cityArr[k])
                    {
                        conflict1[num1] = j;
                        num1++;
                    }
                    if (genes[choice2].cityArr[j] == genes[choice2].cityArr[k])
                    {
                        conflict2[num2] = j;
                        num2++;
                    }
                }
            }

            /********** End **********/
            // 记录pos2之后的冲突位置
            for (int j = pos2 + 1; j < popSize; j++)
            {
                for (int k = pos1; k <= pos2; k++)
                {
                    /********** Begin **********/
                    if (genes[choice1].cityArr[j] == genes[choice1].cityArr[k])
                    {
                        conflict1[num1] = j;
                        num1++;
                    }
                    if (genes[choice2].cityArr[j] == genes[choice2].cityArr[k])
                    {
                        conflict2[num2] = j;
                        num2++;
                    }
                    /********** End **********/
                }
            }
        }
        // 将存在冲突的基因交换回来（此前存储在conflict[]中）
        // 交换的方式有三种，一是在刚刚进行过交换的部分中再换回来，二是找到除此以外的部分进行交换，三是交叉进行
        if ((num1 == num2) && num1 > 0)
        {
            for (int j = 0; j < num1; j++)
            {
                index1 = conflict1[j];
                index2 = conflict2[j];
                temp = genes[choice1].cityArr[index1];
                genes[choice1].cityArr[index1] = genes[choice2].cityArr[index2];
                genes[choice2].cityArr[index2] = temp;
            }
        }
        move += 2;
    }
}

// 基因变异。因不能重复，只能是染色体内部交换(同时变异)。
void mutation()
{
    double pick;
    int pos1, pos2, temp;
    for (int i = 0; i < popSize; i++)
    {
        pick = (float)rand() / RAND_MAX;
        if (pick > mutRate)
        {
            continue;
        }
        pos1 = rand() % popSize;
        pos2 = rand() % popSize;
        while (pos1 > popSize - 1) // 不可能进入以下两个循环？
        {
            pos1 = rand() % popSize;
        }
        while (pos2 > popSize - 1)
        {
            pos2 = rand() % popSize;
        }

        // 交换pos1与pos2位置的城市
        int a = genes[i].dis;
        temp = genes[i].cityArr[pos1];
        genes[i].cityArr[pos1] = genes[i].cityArr[pos2];
        genes[i].cityArr[pos2] = temp;

        // 计算交换后的距离和适应度，如果结果更差了，则不保留（再换回去）
        popFitness();
        if (genes[i].dis > a)
        {
            temp = genes[i].cityArr[pos1];
            genes[i].cityArr[pos1] = genes[i].cityArr[pos2];
            genes[i].cityArr[pos2] = temp;
        }
    }
}