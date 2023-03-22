#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>

int main() {
    fd_set read_fds;        // 读文件描述符集合
    FD_ZERO(&read_fds);     // 初始化为空集合

    int fd1 = STDIN_FILENO; // 标准输入
    int fd2 = fileno(popen("ls", "r")); // 执行命令ls，并读取输出
    int max_fd = fd2 + 1;   // 最大文件描述符数加1

    // 用于返回可读文件描述符数目
    int ready_fds;

    while (1) {
        // 每次循环重新设置读文件描述符集合
        FD_SET(fd1, &read_fds);  // 添加fd1到集合
        FD_SET(fd2, &read_fds);  // 添加fd2到集合

        // 调用select函数阻塞等待
        ready_fds = select(max_fd, &read_fds, NULL, NULL, NULL);
        if (ready_fds == -1) {
            perror("select");
            exit(EXIT_FAILURE);
        }

        // 遍历读文件描述符集合，使用`FD_ISSET`判断哪些就绪了
        for (int fd = 0; fd < max_fd; fd++) {
            if (FD_ISSET(fd, &read_fds)) {
                if (fd == fd1) {
                    // 标准输入就绪
                    printf("fd1 is ready\n");
                    char buf[1024];
                    fgets(buf, sizeof(buf), stdin);
                    printf("You input: %s", buf);
                } else if (fd == fd2) {
                    // 命令输出就绪
                    printf("fd2 is ready\n");
                    char buf[1024];
                    fgets(buf, sizeof(buf), popen("ls", "r"));
                    printf("Command output: %s", buf);
                }
            }
        }
    }

    return 0;
}
