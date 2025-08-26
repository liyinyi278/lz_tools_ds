配置文件复制后需要修改的地方：

1、CMakeLists.txt文件中：“project”里的“vscode-config-template”需要改为你自己的“项目名”。

2、launch.json文件中：将所有的vscode-config-template.exe，改为你自己的：“可执行文件名”.exe

比如：“configurations”-"program": "${workspaceFolder}/build/bin/vscode-config-template.exe"里的“vscode-config-template.exe”，改为：my_execute.exe。

3、修复后执行流程：

    1）删除旧 build 目录（清除错误缓存）；

    2）按 Ctrl+Shift+B 执行 Build my project：CMake 正确解析，生成 build/bin/vscode-config-template.exe；

    3）按 F5 调试：自动触发构建（若文件更新），加载 vscode-config-template.exe 调试。


注意：

CMakeLists.txt里的：

set(TARGET_NAME vscode-config-template)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

应该放在：add_executable(${TARGET_NAME} ${SOURCES})之前。

备份（原来需要的操作）：

1、CMakeLists.txt文件中：set(TARGET_NAME vscode-config-template)，若后续修改 CMake 中的TARGET_NAME，需同步更新此处的文件名：set(TARGET_NAME “你的新执行文件名”)。

已解决：后来设置：set(TARGET_NAME ${PROJECT_NAME})，由于PROJECT_NAME自动检测项目名，所以不需要修改了。