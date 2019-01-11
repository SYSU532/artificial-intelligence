./bin内部包含可执行文件，结合Qt5的打包工具以及Engine Virtual Box，将所有依赖资源以及dll文件全部打包成为一个可执行文件：Chess.exe，可直接启动象棋程序。

./src内部分为codes与project，codes文件夹仅包含项目中的重要代码文件，project文件夹包括整个Qt项目，可通过打开project/Chess/Chess.pro启动Qt项目。

./tc包含象棋程序的测试视频。