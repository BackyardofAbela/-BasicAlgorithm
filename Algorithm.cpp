#include "stdafx.h"
#include "Algorithm.h"


CAlgorithm::CAlgorithm()
{
}


CAlgorithm::~CAlgorithm()
{
}
#pragma region 遍历算法
vector<list<int>> graph;//要处理的图结构

vector<string> CAlgorithm::Split(const string src, string separate_character)
{
	vector<string> strs;

	int separate_characterLen = separate_character.size();//分割字符串的长度,这样就可以支持如“,,”多字符串的分隔符
	int lastPosition = 0, index = -1;
	while (-1 != (index = src.find(separate_character, lastPosition)))
	{
		strs.push_back(src.substr(lastPosition, index - lastPosition));
		lastPosition = index + separate_characterLen;
	}
	string lastString = src.substr(lastPosition);//截取最后一个分隔符后的内容
	if (!lastString.empty())
		strs.push_back(lastString);//如果最后一个分隔符后还有内容就入队
	return strs;
}
//广度算法
vector<int> CAlgorithm::bfs(map<int, vector<int> > link, int top)
{
	queue<int> qe;  //队列用来记录节点的遍历顺序 ，其实入队列的顺序也就是bfs查找的顺序 
	vector<int> order;//bfs查找的最后顺序 
	map<int, int> pre; //找到每个节点的前一个节点，可以根据这个关系算出任意两个节点的最短路径 
	set<int> qeset;  //因为队列不适合于查找，所以用set来记录队列中现存的元素，用于判断新节点是否在队列里 
	map<int, int> vis;  //当元素从队列中弹出，即已经访问过这个节点了，就将其存到map里 

	qe.push(top);  //先将起始点入队列 
	order.push_back(top); //top是bfs查找的第一个元素 
	qeset.insert(top); //给set里添加队列内的元素，set随队列而改变 
	int head, i = 0;
	while (!qe.empty())  //当队列非空时一直遍历该队列 
	{
		head = qe.front();  //取队列的头元素 
		qe.pop();  //将该元素弹出 
		qeset.erase(head); //set随之删除head元素 
		vis[head] = 1;  //此时head元素被访问过，标记为1 
		for (i = 0; i < link[head].size(); i++)  //遍历与head节点相邻的节点 
		{
			if (qeset.find(link[head][i]) == qeset.end() && vis.find(link[head][i]) == vis.end()) //当这个点不在队列里也没有被访问过，则入队列 
			{
				pre[link[head][i]] = head;  //节点link[head][i]的前一个节点为head 
				qe.push(link[head][i]);  //将该节点入队列 
				qeset.insert(top);   //set相应插入对应元素 
				order.push_back(link[head][i]);  //bfs查找顺序添加该元素 
			}
		}

	}

	map<int, int>::iterator it;
	//cout << "preorder:" << endl; 
	//for (it = pre.begin(); it != pre.end(); it++) 
	//{ 
	//    cout << it->first << "->" << it->second << " "; 
	//} 
	//求距离top最远的节点的最大条数 
	head = order[order.size() - 1];
	i = 0;
	while (pre.find(head) != pre.end())
	{
		head = pre[head];
		i++;
	}
	cout << "距离top最远的节点的路径包含的边数: ";
	cout << i << endl;

	cout << endl;
	return order;
}

//因为要用到递归，所以在函数外进行初始化
static vector<int> order;
static map<int, int> vis;
//深度优先算法
vector<int> CAlgorithm::dfs(map<int, vector<int> > link, int top)
{
	order.push_back(top);
	//cout <<top << endl;
	vis[top] = 1;
	int i = 0;
	for (i = 0; i < link[top].size(); i++)
	{
		//cout << link[top][i] << endl;
		if (vis.find(link[top][i]) == vis.end())  //找不到节点link[top][i]，则对节点link[top][i]进行dfs
		{
			dfs(link, link[top][i]);
		}
	}
	return order;
}
#pragma endregion

#pragma region 二分图匹配
#define MAXN 9999

int nx, ny;//nx表示二分图左边顶点的个数，ny表示二分图右边顶点的个数
int m;//m代表边的条数
int cx[MAXN], cy[MAXN];//如果有cx[i]=j，则必有cy[j]=i，说明i点和j点能够匹配
int x, y;//x点到y点有边
int e[MAXN][MAXN];//邻接矩阵
int visited[MAXN];//标记数组，标记的永远是二分图右边的顶点是否被访问到
int ret;//最后结果
int CAlgorithm::hungary(int u)//这个函数的作用是寻找增广路和更新cx，xy数组，如果找到了增广路，函数返回1，找不到，函数返回0。
{
	for (int v = 1; v <= ny; v++)//依次遍历右边的所有顶点
	{
		//条件一：左边的u顶点和右边的v顶点有连通边，
		//条件二：右边的v顶点在没有被访问过，这两个条件必须同时满足
		if (e[u][v] && !visited[v])
		{
			visited[v] = 1;//将v顶点标记为访问过的
			//条件一：右边的v顶点没有左边对应的匹配的点，
			//条件二：以v顶点在左边的匹配点为起点能够找到一条增广路（如果能够到达条件二，说明v顶点在左边一定有对应的匹配点）。
			if (cy[v] == -1 || hungary(cy[v]))
			{
				cx[u] = v;//更新cx，cy数组
				cy[v] = u;
				return 1;
			}
		}
	}
	return 0;//如果程序到达了这里，说明对右边所有的顶点都访问完了，没有满足条件的。
}

void CAlgorithm::runHungary()
{
	m = 7; //二分图的变数
	nx = 4; //二分图左边的节点数
	ny = 4; //二分图右边的节点数
	memset(cx, -1, sizeof(cx));//初始化cx，cy数组的值为-1
	memset(cy, -1, sizeof(cy));
	memset(e, 0, sizeof(e));//初始化邻接矩阵
	ret = 0;
	//对邻接矩阵赋值
	e[0][0] = 1;
	e[0][1] = 1;
	e[1][0] = 1;
	e[1][1] = 1;
	e[2][2] = 1;
	e[3][0] = 1;
	e[2][0] = 1;
	e[3][1] = 1;
	for (int i = 0; i <= nx; i++)//对二分图左边的所有顶点进行遍历
	{
		if (cx[i] == -1)//如果左边的i顶点还没有匹配的点，就对i顶点进行匹配
		{
			memset(visited, 0, sizeof(visited));//每次进行point时，都要对visited数组进行初始化
			ret += hungary(i);//point函数传入的参数永远是二分图左边的点
		}
	}
}


#pragma endregion

#pragma region 欧拉路径 https://blog.csdn.net/yangkunpengd/article/details/51336453

#pragma endregion

#pragma region 二维凸包问题 https://blog.csdn.net/yangkunpengd/article/details/51336453

#pragma endregion

#pragma region 排序 https://blog.csdn.net/opooc/article/details/80994353


/*    这里的注意点：在计算数组大小的时候，
一定要注意传入的数组是否为数组指针，
如果传入的是数组指针，sizeof后出来的值为8(64位下)，读者应注意。
*/
template <class T>
int len(T& arr){
	int length = (int)sizeof(arr) / sizeof(arr[0]);
	return length;
}

//交换两个数
void exchangee(int arr[], int a, int b){
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

//数组和数组大小的结构体
struct arrAndSize{
	int *array;
	int size;
};

//对比两个数组是否相同
bool isEqual(int firstArr[], int Second[]){
	if ((firstArr == nullptr && Second != nullptr) || (firstArr != nullptr && Second == nullptr)) {
		return false;
	}
	if (firstArr == nullptr && Second == nullptr) {
		return  true;
	}
	if (len(firstArr) != len(Second)) {
		return false;
	}
	for (int i = 0; i< len(firstArr); i++) {
		if (firstArr[i] != Second[i]) {
			//可以在此位置，打印错误项
			//也可以打印整个数组查看错误项
			return false;
		}
	}
	return true;
}

//复制数组
int* arrayCopy(int oldArray[], int length){
	if (oldArray == nullptr) {
		return nullptr;
	}

	int* newArray = new int[length];
	for (int i = 0; i<length; i++) {
		newArray[i] = oldArray[i];
	}
	return newArray;
}


int* separate(int arr[], int left, int right){
	int first = left - 1;
	int Second = right;
	while (left < Second) {
		if (arr[left]<arr[right]){
			exchangee(arr, ++first, left++);
		}
		else if (arr[left]>arr[right]){
			exchangee(arr, --Second, left);
		}
		else if (arr[left] == arr[right]){
			left++;
		}
	}
	exchangee(arr, Second, right);
	int firstAndSecond[2] = { first + 1, Second };

	return firstAndSecond;
}

void quickSort(int arr[], int left, int right){
	if (left<right) {
		int randomC = (int)((rand() % 100 / (double)100) * (right - left + 1));
		exchangee(arr, left + randomC, right);
		int* curArr = separate(arr, left, right);
		quickSort(arr, left, curArr[0] - 1);
		quickSort(arr, curArr[1] + 1, right);
	}
}

//快速排序算法
void quickSort(int arr[])
{
	int length = 11;
	if (length < 2) {
		return;
	}
	quickSort(arr, 0, length - 1);
}


//冒泡排序
void BubbleSort(int arr[])
{
	int n = 11;
	for (int i = 0; i < n - 1; i++) 
	{
		for (int j = 0; j < n - i - 1; j++) 
		{
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

//插入排序
void InsertSort(int arr[])
{
	int length = 11;
	for (int i = 1; i < length; i++){
		for (int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j--) {
			exchangee(arr, j, j + 1);
		}
	}
}

//希尔排序
void ShellSort(int arr[])
{
	int length =11;
	int gap = length;
	while (gap > 1){
		gap = gap / 3 + 1;
		for (int i = gap; i < length; i += gap) {
			int current = arr[i];
			int preIndex = i - gap;
			while (preIndex >= 0 && arr[preIndex] > current) {
				arr[i] = arr[preIndex];
				preIndex -= gap;
			}
			arr[preIndex + gap] = current;
		}
	}
}

//选择排序
void SelectSort(int arr[])
{
	int length = 11;
	for (int i = 0; i < length - 1; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j<length; j++){

			if (arr[minIndex]>arr[j]){
				minIndex = j;
			}
		}
		exchangee(arr, minIndex, i);
	}
}

/*
堆的概念：对于大根堆，其子树下的所有节点，
包括它自己在内的最大值为头结点。
时间复杂度为0+log1+log2+……数学上可以证明
这个值收敛于O(N)
*/
//向上走
void heapInsert(int arr[], int index){
	while (arr[index] > arr[(index - 1) / 2]) {
		exchangee(arr, index, (index - 1) / 2);
		index = (index - 1) / 2;
	}
}
//向下走
//size为最右的边界，size是取不到的.
void heapify(int arr[], int index, int size){
	int leftChild = index * 2 + 1;
	while (leftChild < size) {
		int maxChild = leftChild + 1 < size && arr[leftChild + 1] >arr[leftChild] ? leftChild + 1 : leftChild;
		int maxAll = arr[maxChild] > arr[index] ? maxChild : index;
		if (maxAll == index) {
			break;
		}
		exchangee(arr, maxAll, index);
		index = maxAll;
		leftChild = index * 2 + 1;
	}
}

//堆排序
void HeapSort(int arr[])
{
	int length = 11;
	for (int i = 0; i < length; i++){
		heapInsert(arr, i);
	}
	int size = length;
	exchangee(arr, 0, --size);
	while (size > 0){
		//heapify时间复杂度为O(logN)
		heapify(arr, 0, size);
		exchangee(arr, 0, --size);
	}
}

/*
归并排序内部缓存法 可以把空间复杂度降到O(1)；
归并排序原地归并法 也可以把空间复杂度降到O(1)但是时间复
杂度会变成O(N^2)
*/
void merge(int arr[], int L, int M, int R){
	int* cent = new int[R - L + 1];
	int i = 0;
	int pFirst = L;
	int pSecond = M + 1;
	while (pFirst <= M && pSecond <= R) {
		cent[i++] = arr[pFirst] < arr[pSecond] ? arr[pFirst++] : arr[pSecond++];
	}
	while (pFirst <= M) {
		cent[i++] = arr[pFirst++];
	}
	while (pSecond <= R) {
		cent[i++] = arr[pSecond++];
	}
	for (int j = 0; j < (R - L + 1); j++) {
		arr[L + j] = cent[j];
	}

}
void mergeSort(int arr[], int L, int R){
	if (L == R){
		return;
	}
	int mid = (L + R) / 2;
	mergeSort(arr, L, mid);
	mergeSort(arr, mid + 1, R);
	merge(arr, L, mid, R);
}

//归并排序
void mergeSort(int array[])
{
	int length = 11;
	if (array == nullptr || length<2) {
		return;
	}
	mergeSort(array, 0, length - 1);
}

/*    输入的元素是 n 个 0到 k 之间的整数
当k不是很大并且序列比较集中时，计数排序是一个很有效的
排序算法。
下面算法是输入的数组中的最小值大于等于0的情况，
可以根据需求更改。
*/
//计数排序
void countSort(int arr[])
{
	int length = 11;
	int max = arr[0];
	int lastIndex = 0;
	for (int i = 1; i<length; i++) {
		max = arr[i]>max ? arr[i] : max;
	}
	int* sortArr = new int[max + 1]();
	for (int j = 0; j< length; j++) {
		sortArr[arr[j]]++;
	}
	for (int k = 0; k<max + 1; k++) {
		while (sortArr[k]>0) {
			arr[lastIndex++] = k;
			sortArr[k]--;
		}
	}
}

//桶排序是: 桶思想排序 + 一个普通的排序（常用快速排序）

/*
映射函数getGroupCount是得到在第几个桶，其能保证第一
个桶有整个数组的最小值和最后一个桶有整个数组的最大值。
*/
int getGroupCount(long num, long size, long min, long max){
	int count = (int)((size)*(num - min) / (max - min));
	return count;
}
//size  为一个桶的囊括的数的范围
void bucketSort(int arr[],  int size)
{
	int length = 11;
	if (length < 2){
		return;
	}
	int len = length;
	//拿到最大最小值
	long min = arr[0];
	long max = arr[0];
	for (int i = 1; i<len; i++) {
		min = arr[i] < min ? arr[i] : min;
		max = arr[i] > max ? arr[i] : max;
	}
	//如果最小值等于最大值说明数组中就一种数
	if (min == max) {
		return;
	}
	//创建桶
	int bucketCount = (int)((max - min) / size + 1);
	vector<vector<int>> bucket(bucketCount);
	int bid = 0;
	//把数组中的数 扔进桶里
	for (int i = 0; i < len; i++) {

		bid = getGroupCount(arr[i], bucketCount, min, max);
		bucket[bid].push_back(arr[i]);
	}
	for (int i = 0; i< bucketCount; i++) {
		//对桶内进行插入排序。按照升序，这样可以保证从下往上读的稳定性
		for (int j = 1; j<bucket[i].size(); j++) {
			if (bucket[i][j] < bucket[i][j - 1]) {
				swap(bucket[i][j], bucket[i][j - 1]);
			}
		}
		for (int t = 0; t< bucket[i].size(); t++) {
			cout << bucket[i][t] << ' ';
		}

	}
	//    int *newArr = new int[len];
	int index = 0;
	for (int i = 0; i<bucketCount; i++){
		for (int j = 0; j<bucket[i].size(); j++) {
			arr[index++] = bucket[i][j];
		}
	}
}



//拿到传入数的位数
int getRadixCount(int count){
	int num = 1;
	if (count / 10 >0) {
		num++;
	}
	return num;
}
//拿到10的传入位数的次方(10^num)
int getTenRadixCount(int radixCount){
	int tenRadix = 1;
	while (radixCount > 0) {
		tenRadix *= 10;
		radixCount--;
	}
	return tenRadix;
}

//基数排序
void radixSort(int arr[])
{
	int length = 11;
	int len = length;
	int max = arr[0];
	for (int i = 1; i< length; i++) {
		max = arr[i]>max ? arr[i] : max;
	}
	int radixCount = getRadixCount(max);
	int tenRadixCount = getTenRadixCount(radixCount);
	int(*bucket)[10] = new int[10][10];
	int* num = new int[10]();
	int multiplier = 1;
	while (multiplier < tenRadixCount) {
		for (int i = 0; i< len; i++) {
			int curCount = arr[i] / multiplier % 10;
			int k = num[curCount];
			bucket[curCount][k] = arr[i];
			num[curCount]++;
		}
		int index = 0;
		for (int j = 0; j < 10; j++) {
			if (num[j] != 0) {
				for (int k = 0; k<num[j]; k++) {
					arr[index++] = bucket[j][k];
				}
			}
			//把桶清空，准备下一次循环。
			num[j] = 0;
		}
		multiplier *= 10;
	}
}


#pragma endregion


#pragma region 查找 http://www.cnblogs.com/yw09041432/p/5908444.html
//顺序查找
int SequenceSearch(int a[], int value, int n)
{
	int i;
	for (i = 0; i<n; i++)
		if (a[i] == value)
			return i;
	return -1;
}

//二分查找（折半查找），版本1
int BinarySearch1(int a[], int value, int n)
{
	int low, high, mid;
	low = 0;
	high = n - 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (a[mid] == value)
			return mid;
		if (a[mid]>value)
			high = mid - 1;
		if (a[mid]<value)
			low = mid + 1;
	}
	return -1;
}

//二分查找，递归版本
int BinarySearch2(int a[], int value, int low, int high)
{
	int mid = low + (high - low) / 2;
	if (a[mid] == value)
		return mid;
	if (a[mid]>value)
		return BinarySearch2(a, value, low, mid - 1);
	if (a[mid]<value)
		return BinarySearch2(a, value, mid + 1, high);
}

//插值查找
int InsertionSearch(int a[], int value, int low, int high)
{
	int mid = low + (value - a[low]) / (a[high] - a[low])*(high - low);
	if (a[mid] == value)
		return mid;
	if (a[mid]>value)
		return InsertionSearch(a, value, low, mid - 1);
	if (a[mid]<value)
		return InsertionSearch(a, value, mid + 1, high);
}

const int max_size = 20;//斐波那契数组的长度

/*构造一个斐波那契数组*/
void Fibonacci(int * F)
{
	F[0] = 0;
	F[1] = 1;
	for (int i = 2; i<max_size; ++i)
		F[i] = F[i - 1] + F[i - 2];
}

/*定义斐波那契查找法*/
int FibonacciSearch(int *a, int n, int key)  //a为要查找的数组,n为要查找的数组长度,key为要查找的关键字
{
	int low = 0;
	int high = n - 1;

	int F[max_size];
	Fibonacci(F);//构造一个斐波那契数组F 

	int k = 0;
	while (n>F[k] - 1)//计算n位于斐波那契数列的位置
		++k;

	int  * temp;//将数组a扩展到F[k]-1的长度
	temp = new int[F[k] - 1];
	memcpy(temp, a, n*sizeof(int));

	for (int i = n; i<F[k] - 1; ++i)
		temp[i] = a[n - 1];

	while (low <= high)
	{
		int mid = low + F[k - 1] - 1;
		if (key<temp[mid])
		{
			high = mid - 1;
			k -= 1;
		}
		else if (key>temp[mid])
		{
			low = mid + 1;
			k -= 2;
		}
		else
		{
			if (mid<n)
				return mid; //若相等则说明mid即为查找到的位置
			else
				return n - 1; //若mid>=n则说明是扩展的数值,返回n-1
		}
	}
	delete[] temp;
	return -1;
}



#pragma endregion 




#pragma region 最短路径算法 https://blog.csdn.net/qq_36386435/article/details/77403223 https://blog.csdn.net/Mashiro_ylb/article/details/78289790

#pragma endregion

#pragma region 字符串匹配 https://blog.csdn.net/qq_35644234/article/details/55806885

//pos是从1开始的一个下标(朴素串匹配算法)
int CAlgorithm::index_force(char * s, char * t, int pos)
{

	int i = pos - 1;
	//判断pos是否合法
	if (!s[i])
		return 0;
	int j = 0;
	while (s[i] != '\0' && t[j] != '\0')//主串或者模式串遍历完成
	{
		if (s[i] == t[j])//如果主串和模式串对应位置的值相等，则比较后面的字符
		{
			++i;
			++j;
		}
		else    //如果不相等，则模式串需要回朔到第一个字符，而主串则从下一个字符开始
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (t[j] == '\0')//如果循环是由于模式串遍历完了而结束的，说明找到了对应子串的位置
	{
		return i - j + 1;
	}
	else        //否则，主串不包含模式串
	{
		return 0;
	}
}


//next函数的实现  https://blog.csdn.net/LEE18254290736/article/details/77278769
void CAlgorithm::get_next(char * s, int * next)
{
	int i = 0;  //next数组的下标
	int j = -1;  //next值
	next[0] = -1;
	while (s[i] != '\0')
	{
		if (j == -1 || s[i] == s[j]) //如果不存在或这条件符合了，那么就可以得到next值了
		{
			++i; ++j;
			//修改代码部分
			if (s[i] != s[j])//只有两者不相等的时候，才需要更换next值
				next[i] = j;
			else
				next[i] = next[j];
		}
		else{
			j = next[j];
		}
	}
}

//KMP算法的实现
int CAlgorithm::KMP(char * s, char * t, int pos)
{

	int j = 0;
	while (t[j++] != '\0');
	int * next = new int[j - 1];

	int length = j - 1; //串的长度
	//调用函数，生成对应的next值
	get_next(t, next);

	int i = pos - 1;//主串的起始位置
	j = 0;//模式串的下标
	while (s[i] != '\0' && j<length)
	{
		if (j == -1 || s[i] == t[j]) //考虑到第一个不相等的情况
		{
			++i; ++j;
		}
		else
		{
			j = next[j];  //如果不相等，则从next值开始下一次比较（模式串的右移）
		}
	}

	if (t[j] == '\0' && j != -1)
	{
		return i - j + 1;
	}
	else
	{
		return 0;
	}
}

//从子串的右向左匹配：**字符串后移位数=失配字符位置-失配字符上一次出现的位置**
int CAlgorithm::Horspool(char * source, char * pattern)
{
	int source_length = strlen(source);
	int pattern_length = strlen(pattern);
	int i = 0;    //主串的下标的移动
	int j = 0;    //模式串的下标
	int k = 0;
	char misch;  //记录未匹配成功时，主串上的字符
	int mis_dis = 0;
	for (i = 0; i <= source_length - pattern_length;)//注意终止条件，就是当剩余的串已经不够长时，就可以终止了
	{
		for (j = pattern_length - 1; j >= 0; --j)
		{
			if (source[i + j] != pattern[j])
			{
				misch = source[i + j];
				mis_dis = j;
				break;
			}
			if (j == 0)
				return i + 1;
		}
		//寻找模式串中是否有未匹配的字符
		for (k = mis_dis - 1; k >= 0; --k)
		{
			if (pattern[k] == misch)
			{
				i += (mis_dis - k);
				cout << "i=" << i << endl; break;
			}
			if (k == 0)//不存在的时候
			{
				i += (mis_dis + 1);
				cout << "i=" << i << endl;
			}
		}
	}
	return 0;

}


//坏字符的处理方法
/*//Bc函数的实现，因为我们是按照ASCII编码规则进行代码设计的，所以我们开始就申请256个空间
//  第一个for循环处理：坏字符未在子串中，直接将子串移动到坏字符的下一位置
//　　第二个for循环，Bc_table[s[j]中s[i]表示模式串中的第i个字符。
//　　Bc_table[s[j]]=len-j-1;也就是计算s[i]这个字符到串尾部的距离。
//  为什么第二个for循环中，i从小到大的顺序计算呢？哈哈，技巧就在这儿了，原因在于就可以在同一字符多次出现的时候以最靠右的那个字符到尾部距离为最终的距离。当然了，如果没在模式串中出现的字符，其距离就是len了。
*/
void CAlgorithm::Bc(char * s, int * Bc_table)
{
	int len = strlen(s);
	int i = 0;
	for (i = 0; i<256; i++)
	{
		*(Bc_table + i) = len;  //先把映射表的距离全部初始化为模式串的长度
	}
	int j = 0;
	for (j = 0; j<len - 1; ++j)
	{
		Bc_table[s[j]] = len - j - 1;//记录模式串中，每个字符最靠右那个字符的位置
	}
}

//根据好后缀的位置，获取好后缀对应的最大模式串的长度
void CAlgorithm::get_suffix(char * s, int * suffix)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int result;
	int len = strlen(s);  //模式串的长度
	suffix[len - 1] = len;  //模式串最后一个字符是一个特例，它是一个完全模式串后缀，所以长度就是模式串的长度
	for (i = len - 2; i >= 0; --i)  //从模式串的倒数第二个字符开始循环，求suffix的值
	{
		k = i;   //我们想要寻找的那个子串的第一个字符
		j = len - 1; //模式串的最后一个字符
		result = 0; //记录那个子串的长度
		while (s[k--] == s[j--]) //开始往前比较
		{
			++result;
		}
		suffix[i] = result; //得到最大模式串的后缀的长度
	}
}

//Gs映射表的求解函数，
void CAlgorithm::Gs(char *s, int * Gs_table)
{
	int len = strlen(s);
	int i;
	int * suffix = new int[len];
	//生成suffix数组
	get_suffix(s, suffix);
	for (i = 0; i<len; i++)
	{
		Gs_table[i] = len;  //先把所有的移动距离初始化为模式串的长度
	}
	int j = 0;
	//第二种情况
	for (i = len - 2; i >= 0; --i)
	{
		if (suffix[i] == i + 1)//x[i+1-suff[i]…i]＝＝x[m-1-siff[i]…m-1],而suff[i]==i+1，我们知道x[i+1-suff[i]…i]=x[0,i],也就是前缀，满足第二种情况。
		{
			for (; j<len - 1 - i; ++j)  //
			{
				if (Gs_table[j] == len)//保证只被修改一次
				{
					Gs_table[j] = len - 1 - i;
				}
			}
		}
	}
	for (i = 0; i <= len - 2; ++i)   //对应于第三种情况，结合着前面图来理解代码
		Gs_table[len - 1 - suffix[i]] = len - 1 - i;
}

int CAlgorithm::BM(char * s, char * t)
{
	int i = 0;
	int j = 0;
	int length_s = strlen(s);  //主串的长度
	int length_t = strlen(t);  //模式串的长度
	int * B = new int[256];
	int * G = new int[length_t];
	Bc(t, B);
	Gs(t, G);
	while (j <= length_s - length_t)
	{
		for (i = length_t - 1; i >= 0 && s[i + j] == t[i]; --i);//往前匹配
		if (i<0)
		{
			return j + 1;
		}
		else
		{
			int g = G[i];
			int b = B[s[i + j]] - length_t + 1 + i;
			//选择最大的值
			if (g >= b)
				j += g;
			else
				j += b;

		}
	}
	return 0;
}

#pragma endregion



#pragma region 拓扑排序 https://blog.csdn.net/qq_35644234/article/details/60578189

#pragma endregion


#pragma region 最小生成树 https://blog.csdn.net/luoshixian099/article/details/51908175

#pragma endregion

#pragma region 算法设计思想 https://blog.csdn.net/zolalad/article/details/11393915

#pragma endregion