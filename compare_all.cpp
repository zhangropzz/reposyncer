#include <bits/stdc++.h>

using namespace std;

int main()
{
    double count1 = 0;    // 查表次数
    double sum_time1 = 0; // 总耗时
    double count2 = 0;    // 查表次数
    double sum_time2 = 0; // 总耗时
    double count3 = 0;    // 查表次数
    double sum_time3 = 0; // 总耗时

    int n = 500;     // 物品数量
    int repeat = 50; // 重复实验的次数
    srand(time(0));
    for (int m = 0; m < repeat; m++)
    {
        vector<int> val(n);
        for (int j = 0; j < n; j++)
        {
            val[j] = rand() % 20 + 1; // 不能为0
        }

        vector<int> wt(n);
        for (int j = 0; j < n; j++)
        {
            wt[j] = rand() % 20 + 1; // 不能为0
        }

        int W = 1000; // 背包总容量

        // 二维带循环
        clock_t start_time1, end_time1;
        start_time1 = clock(); // 开始记时
        vector<vector<int>> dp1(n + 1, vector<int>(W + 1, 0));
        for (int i = 1; i <= n; ++i)
        {
            for (int w = 1; w <= W; ++w)
            {
                for (int k = 0; k <= w / wt[i - 1]; ++k)
                {
                    dp1[i][w] = max(dp1[i][w], dp1[i - 1][w - k * wt[i - 1]] + k * val[i - 1]);
                    count1 += 2;
                }
            }
        }
        end_time1 = clock(); // 结束计时
        sum_time1 += (double)(end_time1 - start_time1) / CLOCKS_PER_SEC;
        int anwser1 = dp1[n][W];
        // cout << anwser1 << ' ' << count1 << endl;  //验证结果是否正确

        // 二维不带循环
        clock_t start_time2, end_time2;
        start_time2 = clock();                                 // 开始记时
        vector<vector<int>> dp2(n + 1, vector<int>(W + 1, 0)); // 记录情况的二维数组
        for (int i = 1; i <= n; ++i)                           // 遍历物品
        {
            for (int w = 1; w <= W; ++w) // 遍历容量
            {
                if (wt[i - 1] <= w)
                {
                    dp2[i][w] = max(dp2[i - 1][w], dp2[i][w - wt[i - 1]] + val[i - 1]);
                    count2 += 2;
                }
                else
                {
                    dp2[i][w] = dp2[i - 1][w];
                    count2++;
                }
            }
        }
        end_time2 = clock(); // 结束计时
        sum_time2 += (double)(end_time2 - start_time2) / CLOCKS_PER_SEC;
        int anwser2 = dp2[n][W];
        // cout << anwser2 << ' ' << count2 << endl;  //验证结果是否正确

        // 一维数组优化
        clock_t start_time3, end_time3;
        start_time3 = clock();     // 开始记时
        vector<int> dp3(W + 1, 0); // 使用一维数组进行动态规划

        for (int i = 0; i < n; ++i) // 遍历物品
        {
            for (int w = wt[i]; w <= W; ++w) // 遍历单个重量
            {
                dp3[w] = max(dp3[w], dp3[w - wt[i]] + val[i]);
                count3 += 2;
            }
        }
        end_time3 = clock(); // 结束计时
        sum_time3 += (double)(end_time3 - start_time3) / CLOCKS_PER_SEC;
        int anwser3 = dp3[W];
        // cout << anwser3 << ' ' << count3 << endl;  //验证结果是否正确
    }

    cout << endl;
    cout << "————————二维数组带循环的推导式————————" << endl;
    cout << "递推公式为：dp[i][j] = max(dp[i][j], dp[i-1][j-k*wt[i]] + k*val[i]) k>=0&&k<=(W/wt[i])" << endl;
    cout << "实验次数：" << repeat << "次" << endl;
    cout << "物品种类：" << n << endl;
    cout << "背包容量：1000" << endl;
    cout << "平均时间：" << sum_time1 / repeat << "秒" << endl;
    cout << "平均查表：" << count1 / repeat << "次" << endl;

    cout << endl;
    cout << "————————二维数组不带循环的推导式————————" << endl;
    cout << "递推公式为：dp[i][j] = max(dp[i-1][j], dp[i][j-wt[i]] + val[i])" << endl;
    cout << "实验次数：" << repeat << "次" << endl;
    cout << "物品种类：" << n << endl;
    cout << "背包容量：1000" << endl;
    cout << "平均时间：" << sum_time2 / repeat << "秒" << endl;
    cout << "平均查表：" << count2 / repeat << "次" << endl;

    cout << endl;
    cout << "————————一维数组优化————————" << endl;
    cout << "递推公式为：dp[j] = max(dp[j], dp[j-w[i]] + v[i])" << endl;
    cout << "实验次数：" << repeat << "次" << endl;
    cout << "物品种类：" << n << endl;
    cout << "背包容量：1000" << endl;
    cout << "平均时间：" << sum_time3 / repeat << "秒" << endl;
    cout << "平均查表：" << count3 / repeat << "次" << endl;

    return 0;
}
