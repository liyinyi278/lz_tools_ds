#include <algorithm>
#include <cctype>
#include <climits>
#include <codecvt>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// 函数声明
void displayWelcomeScreen();
void mainMenu();
void lotteryTool();
void smallLottery();
void bigLottery();
void runLottery(bool isBig);
void guessNumberGame();
void endgameTraining();
void clearScreen();
void pressAnyKeyToContinue();
bool isValidNumberInput(const string& input, int min, int max);
int getValidNumberInput(const string& prompt, int min, int max);
string getValidChineseNameInput(const string& prompt);
string centerText(const string& text, int width = 70);

// 全局常量
const string SOFTWARE_NAME = "隆回弈智棋院-小工具";
const string AUTHOR = "李泉成";
const string CONTACT = "15869861648";  // 可随时修改的联系方式

// 设置控制台编码（Windows专用）
void setConsoleEncoding() {
#ifdef _WIN32
    system("chcp 65001 > nul");  // 设置为UTF-8编码
#endif
}

int main() {
    // 设置控制台编码
    setConsoleEncoding();

    // 设置随机数种子
    srand(static_cast<unsigned int>(time(0)));

    // 显示欢迎界面
    displayWelcomeScreen();

    // 进入主菜单
    mainMenu();

    return 0;
}

void displayWelcomeScreen() {
    clearScreen();

    // 绘制顶部装饰
    cout << string(70, '*') << endl;
    cout << centerText("") << endl;
    cout << centerText("欢迎使用") << endl;
    cout << centerText(SOFTWARE_NAME) << endl;
    cout << centerText("") << endl;
    cout << centerText("棋道精深，智慧无限") << endl;
    cout << centerText("") << endl;
    cout << string(70, '*') << endl;
    cout << centerText("") << endl;
    cout << centerText("软件作者: " + AUTHOR) << endl;
    cout << centerText("联系方式: " + CONTACT) << endl;
    cout << centerText("") << endl;
    cout << string(70, '*') << endl;
    cout << centerText("") << endl;

    pressAnyKeyToContinue();
}

void mainMenu() {
    int choice = 0;

    while (true) {
        clearScreen();

        // 绘制主菜单界面
        cout << string(70, '=') << endl;
        cout << centerText(SOFTWARE_NAME) << endl;
        cout << centerText("主菜单") << endl;
        cout << string(70, '=') << endl;
        cout << centerText("1. 抽奖小工具") << endl;
        cout << centerText("2. 猜数小游戏") << endl;
        cout << centerText("3. 官子计算训练") << endl;
        cout << centerText("4. 退出程序") << endl;
        cout << string(70, '-') << endl;
        cout << centerText("提示: 输入选项编号进入相应功能") << endl;
        cout << centerText("输入 -1 可随时退出程序") << endl;
        cout << string(70, '=') << endl;

        // 获取用户输入
        cout << "请选择功能 (1-4): ";
        string input;
        getline(cin, input);

        // 检查是否退出
        if (input == "-1") {
            cout << "\n感谢使用 " << SOFTWARE_NAME << "，再见！" << endl;
            exit(0);
        }

        // 验证输入
        if (!isValidNumberInput(input, 1, 4)) {
            cout << "\n无效输入，请输入1-4之间的数字！" << endl;
            pressAnyKeyToContinue();
            continue;
        }

        choice = stoi(input);

        // 根据选择调用功能
        switch (choice) {
            case 1:
                lotteryTool();
                break;
            case 2:
                guessNumberGame();
                break;
            case 3:
                endgameTraining();
                break;
            case 4:
                cout << "\n感谢使用 " << SOFTWARE_NAME << "，再见！" << endl;
                exit(0);
        }
    }
}

void lotteryTool() {
    int choice = 0;

    while (true) {
        clearScreen();

        // 绘制抽奖工具菜单
        cout << string(70, '=') << endl;
        cout << centerText("抽奖小工具") << endl;
        cout << string(70, '=') << endl;
        cout << centerText("1. 小抽奖 (奖励1-100分)") << endl;
        cout << centerText("2. 大抽奖 (奖励10-1000分)") << endl;
        cout << centerText("0. 返回主菜单") << endl;
        cout << string(70, '-') << endl;
        cout << centerText("提示: 输入 -1 可随时退出程序") << endl;
        cout << string(70, '=') << endl;

        // 获取用户输入
        cout << "请选择抽奖类型 (0-2): ";
        string input;
        getline(cin, input);

        // 检查是否退出
        if (input == "-1") {
            cout << "\n感谢使用 " << SOFTWARE_NAME << "，再见！" << endl;
            exit(0);
        }

        // 验证输入
        if (!isValidNumberInput(input, 0, 2)) {
            cout << "\n无效输入，请输入0-2之间的数字！" << endl;
            pressAnyKeyToContinue();
            continue;
        }

        choice = stoi(input);

        // 根据选择调用功能
        switch (choice) {
            case 0:
                return;  // 返回主菜单
            case 1:
                smallLottery();
                break;
            case 2:
                bigLottery();
                break;
        }
    }
}

void smallLottery() {
    runLottery(false);  // false表示小抽奖
}

void bigLottery() {
    runLottery(true);  // true表示大抽奖
}

void runLottery(bool isBig) {
    string lotteryName = isBig ? "大抽奖" : "小抽奖";
    int multiplier = isBig ? 10 : 1;

    while (true) {
        clearScreen();

        // 显示抽奖标题
        cout << string(70, '=') << endl;
        cout << centerText(lotteryName + " - " + SOFTWARE_NAME) << endl;
        cout << string(70, '=') << endl;

        // 获取抽奖人姓名
        string name = getValidChineseNameInput("请输入抽奖人姓名: ");

        // 获取抽奖次数
        int times = getValidNumberInput("请输入抽奖次数 (1-10): ", 1, 10);

        // 抽奖结果统计
        int totalScore = 0;
        vector<string> results;

        cout << "\n" << centerText(name + "的抽奖结果") << endl;
        cout << string(70, '-') << endl;

        // 进行抽奖
        for (int i = 1; i <= times; i++) {
            int randomNum = rand() % 100 + 1;
            int score = 0;
            string prize;

            if (randomNum == 1) {
                prize = "一等奖";
                score = 100;
            } else if (randomNum == 2) {
                prize = "二等奖";
                score = 80;
            } else if (randomNum == 3) {
                prize = "三等奖";
                score = 50;
            } else if (randomNum >= 4 && randomNum <= 50) {
                prize = "鼓励奖";
                score = 20;
            } else {
                prize = "参与奖";
                score = 10;
            }

            // 应用倍数
            score *= multiplier;

            // 保存结果
            stringstream ss;
            ss << "第" << setw(2) << i << "次抽奖: " << setw(10) << prize
               << " 获得 " << setw(4) << score << " 分";
            results.push_back(ss.str());

            totalScore += score;
        }

        // 显示结果
        for (const auto& res : results) {
            cout << centerText(res) << endl;
        }

        cout << string(70, '-') << endl;
        cout << centerText("总得分: " + to_string(totalScore) + " 分") << endl;
        cout << string(70, '=') << endl;

        // 询问是否继续抽奖
        cout << "\n是否继续抽奖? (Y/N): ";
        string choice;
        getline(cin, choice);

        // 转换为大写
        transform(choice.begin(), choice.end(), choice.begin(), ::toupper);

        if (choice != "Y" && choice != "YES") {
            break;
        }
    }
}

void guessNumberGame() {
    while (true) {
        clearScreen();

        // 显示游戏标题
        cout << string(70, '=') << endl;
        cout << centerText("猜数小游戏 - " + SOFTWARE_NAME) << endl;
        cout << string(70, '=') << endl;
        cout << centerText("我已想好一个1-100之间的整数，来猜猜是多少吧！")
             << endl;
        cout << string(70, '-') << endl;

        // 生成随机数
        int secretNumber = rand() % 100 + 1;
        int attempts = 0;
        bool guessed = false;

        while (!guessed) {
            // 获取用户猜测
            int guess = getValidNumberInput("请输入你的猜测 (1-100): ", 1, 100);
            attempts++;

            // 检查猜测结果
            if (guess == secretNumber) {
                cout << "\n" << centerText("恭喜你！猜对了！") << endl;
                cout << centerText("你用了 " + to_string(attempts) +
                                   " 次猜中数字 " + to_string(secretNumber))
                     << endl;
                guessed = true;
            } else if (guess < secretNumber) {
                cout << centerText("猜小了，再试试！") << endl;
            } else {
                cout << centerText("猜大了，再试试！") << endl;
            }

            // 提供退出选项
            if (!guessed) {
                cout << "\n提示: 输入 -1 退出游戏，输入 0 返回主菜单" << endl;
            }
        }

        cout << string(70, '=') << endl;

        // 询问是否继续游戏
        cout << "\n是否继续玩猜数游戏? (Y/N): ";
        string choice;
        getline(cin, choice);

        // 转换为大写
        transform(choice.begin(), choice.end(), choice.begin(), ::toupper);

        if (choice != "Y" && choice != "YES") {
            break;
        }
    }
}

void endgameTraining() {
    while (true) {
        clearScreen();

        // 显示训练标题
        cout << string(70, '=') << endl;
        cout << centerText("官子计算训练 - " + SOFTWARE_NAME) << endl;
        cout << string(70, '=') << endl;
        cout << centerText("围棋官子计算训练，提升你的计算能力！") << endl;
        cout << string(70, '-') << endl;

        // 生成两个随机数和运算符
        int num1 = rand() % 100 + 1;
        int num2 = rand() % 100 + 1;
        char op = (rand() % 2 == 0) ? '+' : '-';

        // 确保减法结果为正数
        if (op == '-' && num1 < num2) {
            swap(num1, num2);
        }

        // 计算正确答案
        int correctAnswer = (op == '+') ? (num1 + num2) : (num1 - num2);

        // 显示问题
        string problem =
            to_string(num1) + " " + op + " " + to_string(num2) + " = ?";
        cout << centerText("问题: " + problem) << endl;

        // 获取用户答案
        int userAnswer =
            getValidNumberInput("请输入你的答案: ", INT_MIN, INT_MAX);

        // 检查答案
        if (userAnswer == correctAnswer) {
            cout << "\n" << centerText("恭喜你！答对了！") << endl;
            cout << centerText(to_string(num1) + " " + op + " " +
                               to_string(num2) + " = " +
                               to_string(correctAnswer))
                 << endl;
        } else {
            cout << "\n" << centerText("很遗憾，答错了！") << endl;
            cout << centerText("正确答案是: " + to_string(correctAnswer))
                 << endl;
            cout << centerText("你的答案是: " + to_string(userAnswer)) << endl;

            // 显示错误原因
            string reason;
            if (op == '+') {
                reason = "加法计算错误，请仔细检查";
            } else {
                reason = "减法计算错误，注意借位";
            }
            cout << centerText("错误原因: " + reason) << endl;
        }

        cout << string(70, '=') << endl;

        // 询问是否继续训练
        cout << "\n是否继续官子计算训练? (Y/N): ";
        string choice;
        getline(cin, choice);

        // 转换为大写
        transform(choice.begin(), choice.end(), choice.begin(), ::toupper);

        if (choice != "Y" && choice != "YES") {
            break;
        }
    }
}

// 辅助函数
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pressAnyKeyToContinue() {
    cout << "\n" << centerText("按回车键继续...") << endl;
    cin.ignore();
    string temp;
    getline(cin, temp);
}

bool isValidNumberInput(const string& input, int min, int max) {
    if (input.empty()) return false;

    // 检查每个字符是否为数字或负号（仅允许在开头）
    for (size_t i = 0; i < input.length(); i++) {
        if (i == 0 && input[i] == '-' && input.length() > 1) {
            continue;
        }
        if (!isdigit(input[i])) {
            return false;
        }
    }

    try {
        int num = stoi(input);
        return num >= min && num <= max;
    } catch (...) {
        return false;
    }
}

int getValidNumberInput(const string& prompt, int min, int max) {
    string input;
    int number;

    while (true) {
        cout << prompt;
        getline(cin, input);

        // 检查退出命令
        if (input == "-1") {
            cout << "\n感谢使用 " << SOFTWARE_NAME << "，再见！" << endl;
            exit(0);
        }

        // 检查返回主菜单命令
        if (input == "0") {
            mainMenu();
            return 0;
        }

        // 验证输入
        if (isValidNumberInput(input, min, max)) {
            number = stoi(input);
            return number;
        }

        cout << "无效输入，请输入 " << min << " 到 " << max << " 之间的整数！"
             << endl;
    }
}

string getValidChineseNameInput(const string& prompt) {
    string name;

    while (true) {
        cout << prompt;
        getline(cin, name);

        // 检查退出命令
        if (name == "-1") {
            cout << "\n感谢使用 " << SOFTWARE_NAME << "，再见！" << endl;
            exit(0);
        }

        // 检查返回主菜单命令
        if (name == "0") {
            mainMenu();
            return "";
        }

        // 验证输入（简单验证非空）
        if (!name.empty()) {
            return name;
        }

        cout << "姓名不能为空，请重新输入！" << endl;
    }
}

string centerText(const string& text, int width) {
    if (text.length() >= width) {
        return text;
    }

    int padding = (width - text.length()) / 2;
    return string(padding, ' ') + text;
}