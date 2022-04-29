# signalprocessingtest
研究生入学小题
# 

# 第一题 生成正弦波
## 理论与实际
### 误差来自哪里
 π是无限不循环，但计算机无法表达   π＋∆π
n也是无限的，但也无法表达
### 引用pha变量
if (pha > fs)  pha -= fs;
### 浮点型和整型
浮点型有误差，所以在循环里面不能出现浮点型，只能是整型
字符也是整型，ASCII码表示，可以直接加减
## 编程习惯
变量命名规范
define 大写
## 判断小数点位数
运用字符串的ASCII码来判断小数点，用字符形式存放浮点数,避免定义为double产生的误差。
## 思想
理论与实际不太一样
举一反三
有用户限制该怎么办
# 第二题 生成方波，求占空比的临界点

- 功率信号总功率的90%，在信号书上3.9 1-12次谐波功率占总功率的90%
- 傅里叶级数展开，累加到第12个后发现大于90%
- 总功率还有累加的功率都不带直流分量，将直流分量减去
- 二分法，两边把结果夹出来
- 思考，如何生成锯齿波，也有临界点。
- 锯齿波三要素：周期，振幅，上下行的时间占比
- 梯形波三要素：上升个数，赋值，频率
## 思想
抓主要矛盾 抓大放小
复杂信号用于线性系统，通过傅里叶级数分解成多个简单分量，通过系统求响应时，可以讲简单信号通过系统求响应，再相加得到总响应
二分法查找，效率高

# 第三题 不用math.h生成正弦波

- 自己编写函数，用展开式展开
- 但n肯定不能取到无穷，所以自己设置界限M，那M后面的没编写的展开式可以当成误差，或者是噪声
- SNR信噪比 信噪比的计量单位是dB，其计算方法是10lg(Ps/Pn)，其中Ps和Pn分别代表信号和噪声的有效功率
- 本题要求M多少时SNR大于40dB
- 编写泰勒展开式，先在外面for循环编写和之前一样的pha函数。内部循环也分两层
- 第一层是M每次加2
- 里层循环是各个余项的阶乘，泰勒公式分子是2M+1次方，分母是阶乘。for (term = 1, j = i; j > 0; j--) term *= processingTime / j; 
- 最后还有-1的n次方，定义变量symbol，每次循环*= -1 ，最后再将每个项相加：sinx += symbol * term;
- 计算M的临界值时，分母用sinx的平均功率为1/2，下面因为x是变化的，但sinx具有周期性，无论多大，最后都能回到0到2Π，因为为了计算它的最小值大于40db，转换成为大于10的4次方，所以再通过诱导公式，将0到2Π压缩到-Π/2到+Π/2，最后因为是功率求的是平方，所以带入pi/2，再while循环累加M，直到成立停止循环。
## 思想
实际产品尽量成本有限，用最简单的加减乘除完成。 
多快好省
# 第四题 生成方波滤出正弦波
## 运用matlab设计低通滤波器

- matlab的filter design可以设计滤波器
- ![true.png](https://cdn.nlark.com/yuque/0/2021/png/25423199/1639813700397-eef0463a-f36f-4120-a49b-51a597deb8ec.png#clientId=ub1289d44-58e7-4&crop=0&crop=0&crop=1&crop=1&from=ui&id=u475038a2&margin=%5Bobject%20Object%5D&name=true.png&originHeight=756&originWidth=924&originalType=binary&ratio=1&rotation=0&showTitle=false&size=76047&status=done&style=none&taskId=ufb59ce31-a0a8-42d3-87cf-f1b2e38e47b&title=)
- 低通 IIR minimum order 最小阶数 FS 采样频率本题为8000hz 本题方波330hz，滤出330hz正弦波，Fpass就是设置为330，第二题知道方波的傅里叶级数，1 3 5 7 9这种，所以Fstop设置为990hz 
- 生成头文件 target的第一个选项 
- 采用IIR滤波器，其中使用椭圆滤波器(elliptic)，这样它的阶数少。Apass一般设置为1db，Astop通过计算原始的信噪比，再通过40db减去它得到数值为33.6866.
- 之后在edit菜单里的convert to single section 改为一维数组
- 之后在edit的convert structure 更改为椭圆型。
- ![QQ截图20211123155605.png](https://cdn.nlark.com/yuque/0/2021/png/25423199/1637655642656-c07d9a0a-180e-457b-b7af-7e0917605fc2.png#clientId=u380a1a93-907e-4&crop=0&crop=0&crop=1&crop=1&from=ui&id=u73ad1683&margin=%5Bobject%20Object%5D&name=QQ%E6%88%AA%E5%9B%BE20211123155605.png&originHeight=382&originWidth=526&originalType=binary&ratio=1&rotation=0&showTitle=false&size=16859&status=done&style=none&taskId=u804431f7-c43b-4f3f-b89e-af2849c3c1b&title=)
- 生成头文件后，再在matlab中找到tmwtypes.h文件 F:\MATLAB\extern\include\tmwtypes.h
- 将两个头文件放在工程中

![QQ图片20211216145116.jpg](https://cdn.nlark.com/yuque/0/2021/jpeg/25423199/1639637435504-c44b24e8-2931-4e40-9794-67fd8a210c99.jpeg#clientId=uf07b52a7-d216-4&crop=0&crop=0&crop=1&crop=1&from=ui&id=u1a01c1f0&margin=%5Bobject%20Object%5D&name=QQ%E5%9B%BE%E7%89%8720211216145116.jpg&originHeight=960&originWidth=768&originalType=binary&ratio=1&rotation=0&showTitle=false&size=62731&status=done&style=none&taskId=u80b83bf2-47d5-4a95-8ed9-1ec1cf671fc&title=)
[参考资料1](https://www.cnblogs.com/geek-wireless/p/IIR.html)
[参考资料2](https://www.cnblogs.com/98Joseph/p/9005409.html)
IIR滤波器代码，其中变的是define的阶数，和系数矩阵
```cpp
#define PI 3.1415926535
#define ORD2 4
#define NUM 20000
//b是分母，a是分子系数
const double b[ORD2] = { 0.01379348564724,-0.009563608593466,-0.009563608593466,  0.01379348564724 };
const double a[ORD2] = { 1,   -2.699286943033,    2.484870605052,  -0.7771239079117 };
long i, k;
	double vv, x[ORD2], y[ORD2];
	FILE* fq, * fr;

	for (k = 0; k < ORD2; k++) x[k] = y[k] = 0;

	fopen_s(&fq, "work1.txt", "r");//读方波 100000点数，幅值为10000
	fopen_s(&fr, "work2.txt", "w");//写滤出的正弦波
	//IIR滤波器
	for (i = 0; i < NUM; i++)
	{
		for (k = ORD2 - 1; k > 0; k--) y[k] = y[k - 1];
		for (k = ORD2 - 1; k > 0; k--) x[k] = x[k - 1];
		fscanf_s(fq, "%lf", &x[0]);
		for (vv = x[0] * b[0], k = 1; k < ORD2; k++) vv += x[k] * b[k] - y[k] * a[k];
		y[0] = vv;

		fprintf(fr, "%d\n", (short)vv);
	}
	fclose(fr);
	fclose(fq);
```
由于滤波器有相位地偏差，所以需要计算Asin(wn + pha)，拆开求Asinpha 和 Acospha，其中选取整数周期
所以点数选择800点，这样coswn在一个周期内求和为0.方便计算。再利用正交性，fn×基波频率的正弦和余弦。
![IMG_2846.JPG](https://cdn.nlark.com/yuque/0/2022/jpeg/25423199/1647767368969-bc6ca1d6-c48a-42cb-b47b-a5400057f731.jpeg#clientId=u06484cc1-32c7-4&crop=0&crop=0&crop=0.9973&crop=0.6122&from=drop&height=3016&id=u69609d16&margin=%5Bobject%20Object%5D&name=IMG_2846.JPG&originHeight=3024&originWidth=4032&originalType=binary&ratio=1&rotation=0&showTitle=false&size=3278246&status=done&style=none&taskId=u601f6a2d-8f44-4ffd-980a-263601cf536&title=&width=4021)
```cpp
w = 2 * PI * 330 / 8000;
	fopen_s(&fr, "work2.txt", "r");
	for (i = 0; i < 10 * N; i++) fscanf_s(fr, "%lf", &xn);
	for (Asin = Acos = i = 0; i < N; i++) {
		fscanf_s(fr, "%lf", &xn);
		Asin += xn * cos(w * i);
		Acos += xn * sin(w * i);
	}
	fclose(fr);
	Asin = Asin * 2 / N;
	Acos = Acos * 2 / N;

	fopen_s(&fr, "work2.txt", "r");
	for (i = 0; i < 10 * N; i++) fscanf_s(fr, "%lf", &xn);
	for (Ps = Pn = i = 0; i < N; i++) {
		xn2 = Asin * cos(w * i) + Acos * sin(w * i);
		Ps += xn2 * xn2;
		fscanf_s(fr, "%lf", &xn);
		Pn += (xn - xn2) * (xn - xn2);
	}
	fclose(fr);
	SNR = 10 * log10(Ps / Pn);
	printf("SNR = %lf\n", SNR);
```
求噪声功率不能用总功率直接减去信号功率，虽然这道题可以，因为是不相关的。功率为二阶统计量，不能直接相加减，应该把点数对应的幅值减去信号幅值，得到噪声的幅值，再进行功率计算。算信噪比。
发现数还不对，因为从0到800点的数据有零输入相应，对信号有影响，看时域能看出来。所以先读800点数据，再从801点计算，最后发现还是不够，频谱发现在330hz以外，250hz和410hz处仍有较大的频域分量。因为比如6000hz用8000hz采样，得到的结果等效于对2000hz采样，所以程序如下。
```cpp
double f0; //等效的频率
	for (low = 0, high = 4000, i = 6; i < 100; i++) {
		f0 = (330 * (2 * i + 1)) % 8000;
		if (f0 > 4000) f0 = 8000 - f0;  //4000翻折
		if (f0 < 330)
		{
			if (low < f0) low = f0;  //250
		}
		else if (f0 > 330)
		{
			if (high > f0) high = f0;  //410
		}
		printf("%d %d\n", low, high);
```
最后采用带通滤波器，算250hz和410hz的信噪比，再用40减去，得到的结果还是不对，这是因为没理解**阻带最小衰减，将410hz衰减12db，但对后面所有频率都衰减12db，这显然是不够的。**比如之前算的990hz需要衰减32db，所以需要算所有的谐波分量衰减多少才能够40db。

## 思想
左与右 明明做的是对的，但测试结果却不对。指标
波形好但信噪比低，需要设计，不能随意试
理论与实际的偏差
用户约束 需有主观评价 主观和客观，要通过指标说服客户
二阶统计量不能直接相加减
低通滤波器的代码要简洁，不止低通滤波器，其他代码也是，能减少计算量就应该尽量减少

# 第五题 信号通过系统生成任意频率正弦波
![7E375F338ABA24E490A86B29AFC259E3.png](https://cdn.nlark.com/yuque/0/2022/png/25423199/1647767669340-9bb63df2-ee42-43c6-ae05-987f3efd8a3a.png#clientId=u06484cc1-32c7-4&crop=0&crop=0&crop=0.9826&crop=0.5139&from=drop&height=2972&id=ub07707fe&margin=%5Bobject%20Object%5D&name=7E375F338ABA24E490A86B29AFC259E3.png&originHeight=3024&originWidth=4032&originalType=binary&ratio=1&rotation=0&showTitle=false&size=3327931&status=done&style=none&taskId=u53b9562f-9e92-476f-af31-037597f17f6&title=&width=3962)
选择线性系统，因为没有产生多余频率分量。
代码运用了leetcode中动态规划的算法，最后算信噪比，跟上一道题一样，有相位偏差。
如果不用double类型，用short类型，该怎么编程，用定点化。
定点化：[链接1](https://www.cnblogs.com/xianyufpga/p/13518872.html) [链接](https://www.cnblogs.com/MAQI/p/7489029.html) [链接](https://zhuanlan.zhihu.com/p/366412841) 
## 调试快捷键
![image.png](https://cdn.nlark.com/yuque/0/2022/png/25423199/1641714055181-56064493-df76-4ef3-ae07-c18869d52901.png#clientId=u5b023ac2-e00c-4&crop=0&crop=0&crop=1&crop=1&from=paste&height=259&id=udb124d41&margin=%5Bobject%20Object%5D&name=image.png&originHeight=518&originWidth=996&originalType=binary&ratio=1&rotation=0&showTitle=false&size=226877&status=done&style=none&taskId=ua224114b-3ab2-4c75-aaf0-ea4cd35ff70&title=&width=498)
## 定点化
首先采用16bit定点化，1位整数，1位符号位，14位小数，所以×2的14次方。2*cos(2*pi*330/8000)*2^14=31673.552142336.四舍五入31674，同理sin也带入。
求偏移的频率误差，首先明白y(1)的值不影响频率，影响的是幅值，所以2*cos(2*pi*330/8000)影响频率，将
b=2*cos(2*pi*f0/8000)对f0求微分。db=-4*pi*sin(2*pi*330/8000)/8000 df0.
将db=(1-0.55214236)/2^14代入求得df0=-0.0006.
那么如果控制在便宜1hz，需要至少多少bit量化呢。求相对误差-4.07*10^-4/1.9332,再对它取倒数，看是多少bit。
## 思想
由问题推出需要的过程，比如本题为什么采用冲激信号，是怎么推出来的，是由问题一步步反推出来的
定点化的实际应用，微分
# 第六题 山谷回声
考察系统建模
pcm格式读写
```cpp
fopen_s(&fq, "demo1.pcm", "rb");
for (i = 0; i < 8000; i++) {
		fread(&xn, sizeof(short), 1L, fq);
		y[i] = xn;
		yn = xn;
		fwrite(&yn, sizeof(short), 1L, fr);

	}
fclose(fr);
```
## 思想
解决实际问题，如何通过物理规律来寻找想要的公式
数学建模，模型的表达式
# 第七题 牛追人
变分 得到的结果是函数
![image002.jpg](https://cdn.nlark.com/yuque/0/2022/jpeg/25423199/1646829242250-0b442fae-3a86-4053-b85d-ec5863948efc.jpeg#clientId=ua8d0a5dc-3118-4&crop=0&crop=0&crop=1&crop=1&from=drop&id=u9b219e16&margin=%5Bobject%20Object%5D&name=image002.jpg&originHeight=331&originWidth=563&originalType=binary&ratio=1&rotation=0&showTitle=false&size=20785&status=done&style=none&taskId=u71d7cd05-dfa1-4472-8def-8108cda0954&title=)
![IMG_2792.JPG](https://cdn.nlark.com/yuque/0/2022/jpeg/25423199/1646829347599-cd8a254f-f45d-446b-8879-0c4724cda6f4.jpeg#clientId=ua8d0a5dc-3118-4&crop=0&crop=0&crop=1&crop=0.5737&from=drop&height=4032&id=u1dde5d55&margin=%5Bobject%20Object%5D&name=IMG_2792.JPG&originHeight=4032&originWidth=3024&originalType=binary&ratio=1&rotation=0&showTitle=false&size=2758841&status=done&style=none&taskId=u078fa8e4-e374-4281-930a-5c5fe1448c3&title=&width=3024)
c++绘图，简单绘图easyx 复杂opencv
计算机图形学
## 思想
变分法，得到的结果是一个函数，而不是具体的数
数学建模
# 第八题 生成随机信号并求统计量
生成均匀分布的随机数，高斯分布的随机数，并求统计量，中位数，众数，分布直方图
生成均匀分布运用混合同余法，高斯分布也是通过数学推导运用均匀分布生成，百度都有
众数采用数组下标，中位数就是查找N/2
## 思想
不止编程，更在乎能力，编程的时间长短，效率
转化为数学问题，并举一反三，比如指数分布？都可以从均匀分布推导出
# 第九题 吉他声音

![IMG_2834.JPG](https://cdn.nlark.com/yuque/0/2022/jpeg/25423199/1647765083878-bf19c598-8858-4b1c-b667-06664a2f008f.jpeg#clientId=u06484cc1-32c7-4&crop=0&crop=0&crop=1&crop=1&from=drop&id=u5a12cb9a&margin=%5Bobject%20Object%5D&name=IMG_2834.JPG&originHeight=3024&originWidth=4032&originalType=binary&ratio=1&rotation=0&showTitle=false&size=3559313&status=done&style=none&taskId=u00b7e87d-2927-4fa7-a879-74dd5b8e7ad&title=)
## 思想
在查看别人写的文档时，大多数情况下是不全的，需要自己在有限的文字中实现
又根据的调节参数，不能随便无理由的尝试。
