/**
 * @file sig.cpp
 * @author avert-win (avert@hnu.edu.cn)
 * @brief 信号处理示例
 * @version 0.1
 * @date 2023-03-11
 * @complexity:
 */
#include <iostream>
#include <signal.h>
#include <unistd.h>

using namespace std;

/**
 * @brief 
 * 
 * @param signum 
 * @param siginfo 信号相关信息，包括PID、UID等。
 * @param context ucontext_t结构体指针，包括当前进程的上下文信息。一般不使用。
 */
void signalHandler(int signum, siginfo_t* siginfo, void* context) {
    // 输出信号相关信息
    cout << "Interrupt signal (" << signum << ") received." << endl;
    cout << "Signal code: " << siginfo->si_code << endl;
    cout << "Signal sender PID: " << siginfo->si_pid << endl;
    cout << "Signal sender UID: " << siginfo->si_uid << endl;
}

int main() {
    // 注册信号 SIGINT 和信号处理程序
    struct sigaction sa;
    sa.sa_sigaction = signalHandler;   
    // 初始化信号掩码
    sigemptyset(&sa.sa_mask);          
    sa.sa_flags = SA_SIGINFO;          // 设置SA_SIGINFO标志
    if (sigaction(SIGINT, &sa, NULL) == -1) {   // 注册信号处理程序
        cerr << "Error: failed to register signal handler." << endl;
        return 1;
    }

    // 进入循环等待信号
    while (1) {
        cout << "Going to sleep...." << endl;
        sleep(1);
    }

    return 0;
}
