/**
 * @file reg_sequence.cpp
 * @author avert-win (avert@hnu.edu.cn)
 * @brief 将一个n个数的序列变为正则序列（内含数字1到n的全部），每次可将一个数加一或减一，求最少操作次数。
 *  O(n)时间复杂度的关键在于，对数据进行预处理，将不在正则区间[1, n]的数字全部修改到其中，从而能够使用数组达到类似哈希表的计数效果，同时又有序。
 * @version 0.1
 * @date 2023-03-16
 * @complexity: 要求时空复杂度皆为O(n)。
 */

/**
 * @brief 排序显然不行，需要用到哈希表，以完成占坑的记录。可能需要多次遍历，但是固定次数，与n无关。
 *  生成一个坑位表和输入计数表；
 *  对计数表进行一次遍历，将对应坑填上，并将占了一个坑的数字计数减一；
 *  重新生成一个坑位表，仅存储尚未有主的坑；
 *  然后再次遍历数字表，不断用剩下最小的数字填最小的坑，累计操作数量。
 * !取最小的数字，要求有序! 预先把所有小于1的改到1，大于n的改到n，就能使用数组来充当计数表，同时实现有序和O(1)时间索引!!
 * 
 * 由于最终是要利用所有数字、填满所有坑，因此直接使用最小的数字填最小的坑是没有错的；
 * 由于索引（输入数字）和计数都是数字，可以使用哈希表，也可以直接使用数组。
 * 输入的最大值不确定，可能超过n，但是用哈希表又无法保证有序，所以预处理一遍（见上三行）
 */

#include<bits/stdc++.h>
using namespace std;

int* getInput(int n){
    int *arr = new int[n];
    for(int i=0; i<n; i++){
        cin>>arr[i];
    }
    return arr;
}

int run(int n, int *arr){
    // 最终操作次数
    int result = 0;

    bool *hole = new bool[n+1];     // 坑位，空为true
    int *table = new int[n+1];      // 计数表，先经过预处理再填入

    memset(hole, 1, sizeof(bool)*(n+1));
    memset(table, 0, sizeof(int)*(n+1));
    // 计数（预处理），同时进行初次填坑；
    for(int i=0; i<n; i++){
        // 数据不在合理区间内，必须先处理；预处理时不要计数，统一在后面完成！
        if(arr[i] > n){         // 大于n的转为n
            result += arr[i] - n;
            arr[i] = n;
        }
        else if(arr[i] < 1){    // 小于1的转为1
            result += 1 - arr[i];
            arr[i] = 1;
        }
        // 完成预处理，开始填坑或计数
        if(hole[arr[i]]){      // 若对应坑空，则填坑
            hole[arr[i]] = false;
        }
        else        // 非第一次出现，则更新计数
            table[arr[i]] ++;
    }

    int j = 1;      // 
    for(int i=1; i<n+1; i++){       // 坑，当坑为空时找数字
        if(!hole[i])         // 坑已被占，直接下一个坑
            continue;       
        // 找到下一个仍有剩余的数字，进行差计算、更新数字、更新坑的状态（非必要）。
        while(table[j] == 0)  
            j++;      
        result += abs(j - i);
        table[j] --;
        hole[i] = false;        // 坑刚被占，更新
    }

    return result;
}

int main(){
    int n; cin>>n;
    int* arr = getInput(n);
    cout<<run(n, arr);
}