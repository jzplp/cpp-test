# cpp-test
刷题暂存

## Windows环境信息
Windows11, 代码编辑器VSCode，命令行PowerShell，使用MinGW，G++编译器。
```sh
# 编译，生成a.exe
g++ 1.cpp
# 执行 输入重定向到1.txt
Get-Content 1.txt | ./a.exe
# 执行 输入重定向到1.txt 输出重定向到 out.txt
Get-Content 1.txt | ./a.exe | Out-File out.txt
```

## MacOS环境信息
M系列芯片，代码编辑器VSCode，操作系统自带编译器。

```sh
# 编译，生成a.out
g++ 1.cpp -o a.out
# 执行 输入重定向到1.txt
./a.out < 1.txt
# 执行 输入重定向到1.txt 输出重定向到 out.txt
./a.out < 1.txt > out.txt
```
