# BP神经网络实验报告

 

1. 网络结构

   实现的神经网络中包含了一个输入层，一个隐层以及一个输出层，其中输入层包含784个神经元节点，代表输入手写数字图像归一化后的的784个像素点；隐层包含30个神经元节点；输出层包含10个神经元节点，代表0-9的10个数字。使用的神经元激励函数为 sigmoid 函数，即$S(t)=\frac{1}{1+e^-t}$ .

2. 网络训练过程

   网络训练过程中使用的学习速率为0.04。实现中构建神经网络对象时首先根据网络层数与节点数按正态分布随机生成初始的权值矩阵。训练过程中以4000个样本为一批以顺序方式进行训练。对每个输入样本训练运算过程如下：

   ​	设$W_1, W_2$分别代表神经网络中输入层与隐层和隐层与输出层的权值矩阵, $I$为大小为$784\times1$的输入数据矩阵，$L$为大小为$10\times1$的样本期望输出，$J$代表输出层与隐层间的索引号。

   1. 前向计算

      使用权值矩阵计算获得各层神经元的输入信号$U$与输出信号$V$，以矩阵形式表示：

      $$V_1=I$$

      $$U_i = W_{i-1} \cdot V_{i-1},\space i=2,3...$$

      $$V_i=sigmoid(U_i),\space  i=2,3...$$

   2.  反向传播

      首先计算梯度$\delta$：

      $$\delta_J=V_J*(1-V_J)*(L-V_J)$$

      $\delta_i=sigmoid'(U_i)+W_i^T\cdot \delta_{i+1}, \space i=1,2...,J-1$

      然后计算对权值的修正量

      $$\Delta W_i=\delta_i\cdot V_i^T*\eta, \space i=1,2...,J$$

      最后计算权值的更新值：

      $$W_i=W_i+\Delta W_i, \space i=1,2...,J$$

3. 程序简述：

   程序使用 C++语言实现，使用 CMake 工具进行构建，在 macOS 10.14，Windows 10以及 Ubuntu18.04下可进行编译。程序依赖于 CImg 库进行图像处理与矩阵运算。进行训练和测试的数据集为[MNIST数据集](http://yann.lecun.com/exdb/mnist/)，数据集数据与训练后的模型将放于 mnist 文件夹下。代码位于src 文件夹下，主要包含如下类：

   - CImgMNistData 类，用于根据MNIST 数据文件的结构对数据进行读取，并提供将图像以 CImg 图片对象的形式获取或以字节列表的形式读取的接口。
   - NeuralNetwork 类，包含 BP 神经网络的主要代码，可通过一个代表各层的神经元数量的 vector 创建，或通过已经训练好的模型文件创建，通过`train`方法对神经网络进行训练，需指定迭代次数与学习速率，通过`predict`方法使用网络模型对输入的数据进行预测分类，返回一个10个元素的数组代表对10个数字的预测值，最大的即为预测的数字。通过`save`方法可将模型保存在指定的文件中。

   程序的主函数若未从命令行指定参数，则默认从`../mnist`文件夹下读取训练数据进行训练，训练后的模型保存在`../mnist/network.txt`文件中。若指定了`test`参数，则将从`../mnist`文件夹下读取训练好的模型与测试文件进行测试并输出测试结果与正确率。

4. 测试结果

   训练完成后进行测试的结果如下：

   ![result](screenshoot/result.png)

   准确率为82.31%。

   隐层数量为30时训练过程中随批次的准确率变化图表如下（横坐标为 Batch，纵坐标为准确率）：

   ![图表](screenshoot/图表.png)

   调整参数（隐层节点数量、学习速率）对结果的影响如下：

   隐层神经元节点数量为30时训练过程中随批次的准确率变化图表如下(最终准确率75.24%)：

   ![图表20](screenshoot/图表20.png)

   隐层神经元节点数量为30，学习速率为0.5时训练过程中随批次的准确率变化图表如下(最终准确率78.95%)：

   ![图表20](screenshoot/图表0.5.png)

可看到相对于学习速率较高时，网络收敛速度快，但是会造成网络的不稳定，而较小的速率虽然收敛速度慢，但可以避免不稳定，获得更高的准确率。