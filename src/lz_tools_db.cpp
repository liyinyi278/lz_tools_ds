#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

// 函数声明
void showWelcome();
void showMainMenu();
int getValidInput(int min, int max);
void lotteryTool();
void smallLottery(const string& name, int times);
void bigLottery(const string& name, int times);
void numberGuessingGame();
void calculationTraining();
string getChineseName();

int main() {
    // 设置随机数种子
    srand(time(0));

    showWelcome();

    bool running = true;
    while (running) {
        showMainMenu();
        int choice = getValidInput(1, 4);

        switch (choice) {
            case 1:
                lotteryTool();
                break;
            case 2:
                numberGuessingGame();
                break;
            case 3:
                calculationTraining();
                break;
            case 4:
                running = false;
                cout << "感谢使用隆回弈智棋院-小工具，再见！" << endl;
                break;
        }
    }

    return 0;
}

// 显示欢迎界面
void showWelcome() {
    system("cls");  // 清屏，Windows系统使用cls，Linux/Mac使用clear
    cout << "=========================================" << endl;
    cout << "             隆回弈智棋院-小工具          " << endl;
    cout << "=========================================" << endl;
    cout << "              软件作者：李泉成            " << endl;
    cout << "              联系方式：15869861648        " << endl;
    cout << "=========================================" << endl;
    cout << "          按任意键进入主菜单...          " << endl;
    cin.get();                                            // 等待用户按键
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 清除输入缓冲区
}

// 显示主菜单
void showMainMenu() {
    system("cls");
    cout << "=========================================" << endl;
    cout << "              主功能菜单                  " << endl;
    cout << "=========================================" << endl;
    cout << "1、抽奖小工具" << endl;
    cout << "2、猜数小游戏" << endl;
    cout << "3、官子计算训练" << endl;
    cout << "4、退出" << endl;
    cout << "=========================================" << endl;
    cout << "请输入功能编号(1-4)：";
}

// 获取合法的整数输入
int getValidInput(int min, int max) {
    int input;
    while (true) {
        if (cin >> input) {
            if (input >= min && input <= max) {
                cin.ignore(numeric_limits<streamsize>::max(),
                           '\n');  // 清除输入缓冲区
                return input;
            } else {
                cout << "输入错误！请输入" << min << "到" << max
                     << "之间的数字：";
            }
        } else {
            cout << "输入无效！请输入一个整数：";
            cin.clear();  // 清除错误状态
            cin.ignore(numeric_limits<streamsize>::max(),
                       '\n');  // 清除输入缓冲区
        }
    }
}

// 获取中文姓名输入
string getChineseName() {
    string name;
    while (true) {
        cout << "请输入抽奖人姓名：";
        cin >> name;

        // 简单检查是否可能为中文（中文通常在Unicode的特定范围内）
        bool hasChinese = false;
        for (char c : name) {
            if (static_cast<unsigned char>(c) > 127) {
                hasChinese = true;
                break;
            }
        }

        if (hasChinese && name.length() >= 2) {
            return name;
        } else {
            cout << "姓名输入无效！请输入有效的中文姓名：" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// 抽奖小工具
void lotteryTool() {
    bool backToMain = false;
    while (!backToMain) {
        system("cls");
        cout << "=========================================" << endl;
        cout << "              抽奖小工具                  " << endl;
        cout << "=========================================" << endl;
        cout << "1、小抽奖" << endl;
        cout << "2、大抽奖" << endl;
        cout << "3、返回主菜单" << endl;
        cout << "4、退出程序" << endl;
        cout << "=========================================" << endl;
        cout << "请选择功能(1-4)：";

        int choice = getValidInput(1, 4);

        if (choice == 3) {
            backToMain = true;
            continue;
        } else if (choice == 4) {
            cout << "感谢使用隆回弈智棋院-小工具，再见！" << endl;
            exit(0);
        }

        string name = getChineseName();
        cout << "请输入抽奖次数(1-100)：";
        int times = getValidInput(1, 100);

        if (choice == 1) {
            smallLottery(name, times);
        } else {
            bigLottery(name, times);
        }

        cout << "是否继续抽奖？(1-是，2-返回抽奖菜单)：";
        int continueChoice = getValidInput(1, 2);
        if (continueChoice == 2) {
            backToMain = false;
        }
    }
}

// 小抽奖实现
void smallLottery(const string& name, int times) {
    system("cls");
    cout << "=========================================" << endl;
    cout << "              小抽奖结果                  " << endl;
    cout << "=========================================" << endl;
    cout << "抽奖人：" << name << endl;
    cout << "抽奖次数：" << times << endl;
    cout << "-----------------------------------------" << endl;

    int totalScore = 0;

    for (int i = 1; i <= times; ++i) {
        int randomNum = rand() % 100 + 1;  // 生成1-100的随机数
        string award;
        int score;

        if (randomNum == 1) {
            award = "一等奖";
            score = 100;
        } else if (randomNum == 2) {
            award = "二等奖";
            score = 80;
        } else if (randomNum == 3) {
            award = "三等奖";
            score = 50;
        } else if (randomNum >= 4 && randomNum <= 50) {
            award = "鼓励奖";
            score = 20;
        } else {  // 51-100
            award = "参与奖";
            score = 10;
        }

        totalScore += score;
        cout << "第" << i << "次：" << award << "，得分：" << score << endl;
    }

    cout << "-----------------------------------------" << endl;
    cout << "总得分：" << totalScore << endl;
    cout << "=========================================" << endl;
}

// 大抽奖实现
void bigLottery(const string& name, int times) {
    system("cls");
    cout << "=========================================" << endl;
    cout << "              大抽奖结果                  " << endl;
    cout << "=========================================" << endl;
    cout << "抽奖人：" << name << endl;
    cout << "抽奖次数：" << times << endl;
    cout << "-----------------------------------------" << endl;

    int totalScore = 0;

    for (int i = 1; i <= times; ++i) {
        int randomNum = rand() % 100 + 1;  // 生成1-100的随机数
        string award;
        int score;

        if (randomNum == 1) {
            award = "一等奖";
            score = 1000;  // 小抽奖的10倍
        } else if (randomNum == 2) {
            award = "二等奖";
            score = 800;
        } else if (randomNum == 3) {
            award = "三等奖";
            score = 500;
        } else if (randomNum >= 4 && randomNum <= 50) {
            award = "鼓励奖";
            score = 200;
        } else {  // 51-100
            award = "参与奖";
            score = 100;
        }

        totalScore += score;
        cout << "第" << i << "次：" << award << "，得分：" << score << endl;
    }

    cout << "-----------------------------------------" << endl;
    cout << "总得分：" << totalScore << endl;
    cout << "=========================================" << endl;
}

// 猜数小游戏
void numberGuessingGame() {
    bool backToMain = false;
    while (!backToMain) {
        system("cls");
        cout << "=========================================" << endl;
        cout << "              猜数小游戏                  " << endl;
        cout << "=========================================" << endl;
        cout << "1、开始游戏" << endl;
        cout << "2、返回主菜单" << endl;
        cout << "3、退出程序" << endl;
        cout << "=========================================" << endl;
        cout << "请选择功能(1-3)：";

        int choice = getValidInput(1, 3);

        if (choice == 2) {
            backToMain = true;
            continue;
        } else if (choice == 3) {
            cout << "感谢使用隆回弈智棋院-小工具，再见！" << endl;
            exit(0);
        }

        bool playing = true;
        while (playing) {
            system("cls");
            cout << "=========================================" << endl;
            cout << "              猜数游戏 - 开始             " << endl;
            cout << "=========================================" << endl;
            cout << "我已经想好了一个1到100之间的整数，" << endl;
            cout << "请你来猜猜看是什么数字？" << endl;
            cout << "输入0可以返回上一级菜单" << endl;
            cout << "=========================================" << endl;

            int targetNumber = rand() % 100 + 1;
            int guess;
            int attempts = 0;

            while (true) {
                cout << "请输入你的猜测：";
                if (!(cin >> guess)) {
                    cout << "输入无效！请输入一个整数。" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }

                if (guess == 0) {
                    playing = false;
                    break;
                }

                attempts++;

                if (guess < 1 || guess > 100) {
                    cout << "请输入1到100之间的数字！" << endl;
                } else if (guess < targetNumber) {
                    cout << "猜小了！再试一次。" << endl;
                } else if (guess > targetNumber) {
                    cout << "猜大了！再试一次。" << endl;
                } else {
                    cout << "恭喜你猜对了！答案就是" << targetNumber << "。"
                         << endl;
                    cout << "你一共猜了" << attempts << "次。" << endl;

                    cout << "是否再玩一次？(1-是，2-否)：";
                    int continueChoice = getValidInput(1, 2);
                    if (continueChoice == 2) {
                        playing = false;
                    }
                    break;
                }
            }
        }
    }
}

// 官子计算训练
void calculationTraining() {
    bool backToMain = false;
    while (!backToMain) {
        system("cls");
        cout << "=========================================" << endl;
        cout << "              官子计算训练                " << endl;
        cout << "=========================================" << endl;
        cout << "1、开始训练" << endl;
        cout << "2、返回主菜单" << endl;
        cout << "3、退出程序" << endl;
        cout << "=========================================" << endl;
        cout << "请选择功能(1-3)：";

        int choice = getValidInput(1, 3);

        if (choice == 2) {
            backToMain = true;
            continue;
        } else if (choice == 3) {
            cout << "感谢使用隆回弈智棋院-小工具，再见！" << endl;
            exit(0);
        }

        bool training = true;
        while (training) {
            system("cls");
            cout << "=========================================" << endl;
            cout << "              计算训练 - 开始             " << endl;
            cout << "=========================================" << endl;
            cout << "请解答下面的计算题，" << endl;
            cout << "输入0可以返回上一级菜单" << endl;
            cout << "=========================================" << endl;

            // 生成两个1-100的随机数
            int num1 = rand() % 100 + 1;
            int num2 = rand() % 100 + 1;

            // 随机选择加法或减法
            bool isAddition = (rand() % 2 == 0);

            // 确保减法结果不为负数
            if (!isAddition && num1 < num2) {
                swap(num1, num2);
            }

            int result;
            if (isAddition) {
                result = num1 + num2;
                cout << num1 << " + " << num2 << " = ?" << endl;
            } else {
                result = num1 - num2;
                cout << num1 << " - " << num2 << " = ?" << endl;
            }

            int answer;
            cout << "请输入你的答案：";

            while (true) {
                if (!(cin >> answer)) {
                    cout << "输入无效！请输入一个整数。" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "请重新输入答案：";
                    continue;
                }

                if (answer == 0) {
                    training = false;
                    break;
                }

                if (answer == result) {
                    cout << "恭喜你，答对了！" << endl;
                } else {
                    cout << "答错了。正确答案是：" << result << endl;
                    if (isAddition) {
                        cout << "错误原因：" << num1 << " + " << num2
                             << " 不等于 " << answer << endl;
                    } else {
                        cout << "错误原因：" << num1 << " - " << num2
                             << " 不等于 " << answer << endl;
                    }
                }

                cout << "是否继续训练？(1-是，2-否)：";
                int continueChoice = getValidInput(1, 2);
                if (continueChoice == 2) {
                    training = false;
                }
                break;
            }
        }
    }
}
