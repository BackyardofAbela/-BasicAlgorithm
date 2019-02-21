#include "stdafx.h"
#include "Algorithm.h"


CAlgorithm::CAlgorithm()
{
}


CAlgorithm::~CAlgorithm()
{
}
#pragma region �����㷨
vector<list<int>> graph;//Ҫ�����ͼ�ṹ

vector<string> CAlgorithm::Split(const string src, string separate_character)
{
	vector<string> strs;

	int separate_characterLen = separate_character.size();//�ָ��ַ����ĳ���,�����Ϳ���֧���硰,,�����ַ����ķָ���
	int lastPosition = 0, index = -1;
	while (-1 != (index = src.find(separate_character, lastPosition)))
	{
		strs.push_back(src.substr(lastPosition, index - lastPosition));
		lastPosition = index + separate_characterLen;
	}
	string lastString = src.substr(lastPosition);//��ȡ���һ���ָ����������
	if (!lastString.empty())
		strs.push_back(lastString);//������һ���ָ����������ݾ����
	return strs;
}
//����㷨
vector<int> CAlgorithm::bfs(map<int, vector<int> > link, int top)
{
	queue<int> qe;  //����������¼�ڵ�ı���˳�� ����ʵ����е�˳��Ҳ����bfs���ҵ�˳�� 
	vector<int> order;//bfs���ҵ����˳�� 
	map<int, int> pre; //�ҵ�ÿ���ڵ��ǰһ���ڵ㣬���Ը��������ϵ������������ڵ�����·�� 
	set<int> qeset;  //��Ϊ���в��ʺ��ڲ��ң�������set����¼�������ִ��Ԫ�أ������ж��½ڵ��Ƿ��ڶ����� 
	map<int, int> vis;  //��Ԫ�شӶ����е��������Ѿ����ʹ�����ڵ��ˣ��ͽ���浽map�� 

	qe.push(top);  //�Ƚ���ʼ������� 
	order.push_back(top); //top��bfs���ҵĵ�һ��Ԫ�� 
	qeset.insert(top); //��set����Ӷ����ڵ�Ԫ�أ�set����ж��ı� 
	int head, i = 0;
	while (!qe.empty())  //�����зǿ�ʱһֱ�����ö��� 
	{
		head = qe.front();  //ȡ���е�ͷԪ�� 
		qe.pop();  //����Ԫ�ص��� 
		qeset.erase(head); //set��֮ɾ��headԪ�� 
		vis[head] = 1;  //��ʱheadԪ�ر����ʹ������Ϊ1 
		for (i = 0; i < link[head].size(); i++)  //������head�ڵ����ڵĽڵ� 
		{
			if (qeset.find(link[head][i]) == qeset.end() && vis.find(link[head][i]) == vis.end()) //������㲻�ڶ�����Ҳû�б����ʹ���������� 
			{
				pre[link[head][i]] = head;  //�ڵ�link[head][i]��ǰһ���ڵ�Ϊhead 
				qe.push(link[head][i]);  //���ýڵ������ 
				qeset.insert(top);   //set��Ӧ�����ӦԪ�� 
				order.push_back(link[head][i]);  //bfs����˳����Ӹ�Ԫ�� 
			}
		}

	}

	map<int, int>::iterator it;
	//cout << "preorder:" << endl; 
	//for (it = pre.begin(); it != pre.end(); it++) 
	//{ 
	//    cout << it->first << "->" << it->second << " "; 
	//} 
	//�����top��Զ�Ľڵ��������� 
	head = order[order.size() - 1];
	i = 0;
	while (pre.find(head) != pre.end())
	{
		head = pre[head];
		i++;
	}
	cout << "����top��Զ�Ľڵ��·�������ı���: ";
	cout << i << endl;

	cout << endl;
	return order;
}

//��ΪҪ�õ��ݹ飬�����ں�������г�ʼ��
static vector<int> order;
static map<int, int> vis;
//��������㷨
vector<int> CAlgorithm::dfs(map<int, vector<int> > link, int top)
{
	order.push_back(top);
	//cout <<top << endl;
	vis[top] = 1;
	int i = 0;
	for (i = 0; i < link[top].size(); i++)
	{
		//cout << link[top][i] << endl;
		if (vis.find(link[top][i]) == vis.end())  //�Ҳ����ڵ�link[top][i]����Խڵ�link[top][i]����dfs
		{
			dfs(link, link[top][i]);
		}
	}
	return order;
}
#pragma endregion

#pragma region ����ͼƥ��
#define MAXN 9999

int nx, ny;//nx��ʾ����ͼ��߶���ĸ�����ny��ʾ����ͼ�ұ߶���ĸ���
int m;//m����ߵ�����
int cx[MAXN], cy[MAXN];//�����cx[i]=j�������cy[j]=i��˵��i���j���ܹ�ƥ��
int x, y;//x�㵽y���б�
int e[MAXN][MAXN];//�ڽӾ���
int visited[MAXN];//������飬��ǵ���Զ�Ƕ���ͼ�ұߵĶ����Ƿ񱻷��ʵ�
int ret;//�����
int CAlgorithm::hungary(int u)//���������������Ѱ������·�͸���cx��xy���飬����ҵ�������·����������1���Ҳ�������������0��
{
	for (int v = 1; v <= ny; v++)//���α����ұߵ����ж���
	{
		//����һ����ߵ�u������ұߵ�v��������ͨ�ߣ�
		//���������ұߵ�v������û�б����ʹ�����������������ͬʱ����
		if (e[u][v] && !visited[v])
		{
			visited[v] = 1;//��v������Ϊ���ʹ���
			//����һ���ұߵ�v����û����߶�Ӧ��ƥ��ĵ㣬
			//����������v��������ߵ�ƥ���Ϊ����ܹ��ҵ�һ������·������ܹ�������������˵��v���������һ���ж�Ӧ��ƥ��㣩��
			if (cy[v] == -1 || hungary(cy[v]))
			{
				cx[u] = v;//����cx��cy����
				cy[v] = u;
				return 1;
			}
		}
	}
	return 0;//������򵽴������˵�����ұ����еĶ��㶼�������ˣ�û�����������ġ�
}

void CAlgorithm::runHungary()
{
	m = 7; //����ͼ�ı���
	nx = 4; //����ͼ��ߵĽڵ���
	ny = 4; //����ͼ�ұߵĽڵ���
	memset(cx, -1, sizeof(cx));//��ʼ��cx��cy�����ֵΪ-1
	memset(cy, -1, sizeof(cy));
	memset(e, 0, sizeof(e));//��ʼ���ڽӾ���
	ret = 0;
	//���ڽӾ���ֵ
	e[0][0] = 1;
	e[0][1] = 1;
	e[1][0] = 1;
	e[1][1] = 1;
	e[2][2] = 1;
	e[3][0] = 1;
	e[2][0] = 1;
	e[3][1] = 1;
	for (int i = 0; i <= nx; i++)//�Զ���ͼ��ߵ����ж�����б���
	{
		if (cx[i] == -1)//�����ߵ�i���㻹û��ƥ��ĵ㣬�Ͷ�i�������ƥ��
		{
			memset(visited, 0, sizeof(visited));//ÿ�ν���pointʱ����Ҫ��visited������г�ʼ��
			ret += hungary(i);//point��������Ĳ�����Զ�Ƕ���ͼ��ߵĵ�
		}
	}
}


#pragma endregion

#pragma region ŷ��·�� https://blog.csdn.net/yangkunpengd/article/details/51336453

#pragma endregion

#pragma region ��ά͹������ https://blog.csdn.net/yangkunpengd/article/details/51336453

#pragma endregion

#pragma region ���� https://blog.csdn.net/opooc/article/details/80994353


/*    �����ע��㣺�ڼ��������С��ʱ��
һ��Ҫע�⴫��������Ƿ�Ϊ����ָ�룬
��������������ָ�룬sizeof�������ֵΪ8(64λ��)������Ӧע�⡣
*/
template <class T>
int len(T& arr){
	int length = (int)sizeof(arr) / sizeof(arr[0]);
	return length;
}

//����������
void exchangee(int arr[], int a, int b){
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

//����������С�Ľṹ��
struct arrAndSize{
	int *array;
	int size;
};

//�Ա����������Ƿ���ͬ
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
			//�����ڴ�λ�ã���ӡ������
			//Ҳ���Դ�ӡ��������鿴������
			return false;
		}
	}
	return true;
}

//��������
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

//���������㷨
void quickSort(int arr[])
{
	int length = 11;
	if (length < 2) {
		return;
	}
	quickSort(arr, 0, length - 1);
}


//ð������
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

//��������
void InsertSort(int arr[])
{
	int length = 11;
	for (int i = 1; i < length; i++){
		for (int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j--) {
			exchangee(arr, j, j + 1);
		}
	}
}

//ϣ������
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

//ѡ������
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
�ѵĸ�����ڴ���ѣ��������µ����нڵ㣬
�������Լ����ڵ����ֵΪͷ��㡣
ʱ�临�Ӷ�Ϊ0+log1+log2+������ѧ�Ͽ���֤��
���ֵ������O(N)
*/
//������
void heapInsert(int arr[], int index){
	while (arr[index] > arr[(index - 1) / 2]) {
		exchangee(arr, index, (index - 1) / 2);
		index = (index - 1) / 2;
	}
}
//������
//sizeΪ���ҵı߽磬size��ȡ������.
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

//������
void HeapSort(int arr[])
{
	int length = 11;
	for (int i = 0; i < length; i++){
		heapInsert(arr, i);
	}
	int size = length;
	exchangee(arr, 0, --size);
	while (size > 0){
		//heapifyʱ�临�Ӷ�ΪO(logN)
		heapify(arr, 0, size);
		exchangee(arr, 0, --size);
	}
}

/*
�鲢�����ڲ����淨 ���԰ѿռ临�ӶȽ���O(1)��
�鲢����ԭ�ع鲢�� Ҳ���԰ѿռ临�ӶȽ���O(1)����ʱ�临
�ӶȻ���O(N^2)
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

//�鲢����
void mergeSort(int array[])
{
	int length = 11;
	if (array == nullptr || length<2) {
		return;
	}
	mergeSort(array, 0, length - 1);
}

/*    �����Ԫ���� n �� 0�� k ֮�������
��k���Ǻܴ������бȽϼ���ʱ������������һ������Ч��
�����㷨��
�����㷨������������е���Сֵ���ڵ���0�������
���Ը���������ġ�
*/
//��������
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

//Ͱ������: Ͱ˼������ + һ����ͨ�����򣨳��ÿ�������

/*
ӳ�亯��getGroupCount�ǵõ��ڵڼ���Ͱ�����ܱ�֤��һ
��Ͱ�������������Сֵ�����һ��Ͱ��������������ֵ��
*/
int getGroupCount(long num, long size, long min, long max){
	int count = (int)((size)*(num - min) / (max - min));
	return count;
}
//size  Ϊһ��Ͱ�����������ķ�Χ
void bucketSort(int arr[],  int size)
{
	int length = 11;
	if (length < 2){
		return;
	}
	int len = length;
	//�õ������Сֵ
	long min = arr[0];
	long max = arr[0];
	for (int i = 1; i<len; i++) {
		min = arr[i] < min ? arr[i] : min;
		max = arr[i] > max ? arr[i] : max;
	}
	//�����Сֵ�������ֵ˵�������о�һ����
	if (min == max) {
		return;
	}
	//����Ͱ
	int bucketCount = (int)((max - min) / size + 1);
	vector<vector<int>> bucket(bucketCount);
	int bid = 0;
	//�������е��� �ӽ�Ͱ��
	for (int i = 0; i < len; i++) {

		bid = getGroupCount(arr[i], bucketCount, min, max);
		bucket[bid].push_back(arr[i]);
	}
	for (int i = 0; i< bucketCount; i++) {
		//��Ͱ�ڽ��в������򡣰��������������Ա�֤�������϶����ȶ���
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



//�õ���������λ��
int getRadixCount(int count){
	int num = 1;
	if (count / 10 >0) {
		num++;
	}
	return num;
}
//�õ�10�Ĵ���λ���Ĵη�(10^num)
int getTenRadixCount(int radixCount){
	int tenRadix = 1;
	while (radixCount > 0) {
		tenRadix *= 10;
		radixCount--;
	}
	return tenRadix;
}

//��������
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
			//��Ͱ��գ�׼����һ��ѭ����
			num[j] = 0;
		}
		multiplier *= 10;
	}
}


#pragma endregion


#pragma region ���� http://www.cnblogs.com/yw09041432/p/5908444.html
//˳�����
int SequenceSearch(int a[], int value, int n)
{
	int i;
	for (i = 0; i<n; i++)
		if (a[i] == value)
			return i;
	return -1;
}

//���ֲ��ң��۰���ң����汾1
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

//���ֲ��ң��ݹ�汾
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

//��ֵ����
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

const int max_size = 20;//쳲���������ĳ���

/*����һ��쳲���������*/
void Fibonacci(int * F)
{
	F[0] = 0;
	F[1] = 1;
	for (int i = 2; i<max_size; ++i)
		F[i] = F[i - 1] + F[i - 2];
}

/*����쳲��������ҷ�*/
int FibonacciSearch(int *a, int n, int key)  //aΪҪ���ҵ�����,nΪҪ���ҵ����鳤��,keyΪҪ���ҵĹؼ���
{
	int low = 0;
	int high = n - 1;

	int F[max_size];
	Fibonacci(F);//����һ��쳲���������F 

	int k = 0;
	while (n>F[k] - 1)//����nλ��쳲��������е�λ��
		++k;

	int  * temp;//������a��չ��F[k]-1�ĳ���
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
				return mid; //�������˵��mid��Ϊ���ҵ���λ��
			else
				return n - 1; //��mid>=n��˵������չ����ֵ,����n-1
		}
	}
	delete[] temp;
	return -1;
}



#pragma endregion 




#pragma region ���·���㷨 https://blog.csdn.net/qq_36386435/article/details/77403223 https://blog.csdn.net/Mashiro_ylb/article/details/78289790

#pragma endregion

#pragma region �ַ���ƥ�� https://blog.csdn.net/qq_35644234/article/details/55806885

//pos�Ǵ�1��ʼ��һ���±�(���ش�ƥ���㷨)
int CAlgorithm::index_force(char * s, char * t, int pos)
{

	int i = pos - 1;
	//�ж�pos�Ƿ�Ϸ�
	if (!s[i])
		return 0;
	int j = 0;
	while (s[i] != '\0' && t[j] != '\0')//��������ģʽ���������
	{
		if (s[i] == t[j])//���������ģʽ����Ӧλ�õ�ֵ��ȣ���ȽϺ�����ַ�
		{
			++i;
			++j;
		}
		else    //�������ȣ���ģʽ����Ҫ��˷����һ���ַ��������������һ���ַ���ʼ
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (t[j] == '\0')//���ѭ��������ģʽ���������˶������ģ�˵���ҵ��˶�Ӧ�Ӵ���λ��
	{
		return i - j + 1;
	}
	else        //��������������ģʽ��
	{
		return 0;
	}
}


//next������ʵ��  https://blog.csdn.net/LEE18254290736/article/details/77278769
void CAlgorithm::get_next(char * s, int * next)
{
	int i = 0;  //next������±�
	int j = -1;  //nextֵ
	next[0] = -1;
	while (s[i] != '\0')
	{
		if (j == -1 || s[i] == s[j]) //��������ڻ������������ˣ���ô�Ϳ��Եõ�nextֵ��
		{
			++i; ++j;
			//�޸Ĵ��벿��
			if (s[i] != s[j])//ֻ�����߲���ȵ�ʱ�򣬲���Ҫ����nextֵ
				next[i] = j;
			else
				next[i] = next[j];
		}
		else{
			j = next[j];
		}
	}
}

//KMP�㷨��ʵ��
int CAlgorithm::KMP(char * s, char * t, int pos)
{

	int j = 0;
	while (t[j++] != '\0');
	int * next = new int[j - 1];

	int length = j - 1; //���ĳ���
	//���ú��������ɶ�Ӧ��nextֵ
	get_next(t, next);

	int i = pos - 1;//��������ʼλ��
	j = 0;//ģʽ�����±�
	while (s[i] != '\0' && j<length)
	{
		if (j == -1 || s[i] == t[j]) //���ǵ���һ������ȵ����
		{
			++i; ++j;
		}
		else
		{
			j = next[j];  //�������ȣ����nextֵ��ʼ��һ�αȽϣ�ģʽ�������ƣ�
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

//���Ӵ���������ƥ�䣺**�ַ�������λ��=ʧ���ַ�λ��-ʧ���ַ���һ�γ��ֵ�λ��**
int CAlgorithm::Horspool(char * source, char * pattern)
{
	int source_length = strlen(source);
	int pattern_length = strlen(pattern);
	int i = 0;    //�������±���ƶ�
	int j = 0;    //ģʽ�����±�
	int k = 0;
	char misch;  //��¼δƥ��ɹ�ʱ�������ϵ��ַ�
	int mis_dis = 0;
	for (i = 0; i <= source_length - pattern_length;)//ע����ֹ���������ǵ�ʣ��Ĵ��Ѿ�������ʱ���Ϳ�����ֹ��
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
		//Ѱ��ģʽ�����Ƿ���δƥ����ַ�
		for (k = mis_dis - 1; k >= 0; --k)
		{
			if (pattern[k] == misch)
			{
				i += (mis_dis - k);
				cout << "i=" << i << endl; break;
			}
			if (k == 0)//�����ڵ�ʱ��
			{
				i += (mis_dis + 1);
				cout << "i=" << i << endl;
			}
		}
	}
	return 0;

}


//���ַ��Ĵ�����
/*//Bc������ʵ�֣���Ϊ�����ǰ���ASCII���������д�����Ƶģ��������ǿ�ʼ������256���ռ�
//  ��һ��forѭ���������ַ�δ���Ӵ��У�ֱ�ӽ��Ӵ��ƶ������ַ�����һλ��
//�����ڶ���forѭ����Bc_table[s[j]��s[i]��ʾģʽ���еĵ�i���ַ���
//����Bc_table[s[j]]=len-j-1;Ҳ���Ǽ���s[i]����ַ�����β���ľ��롣
//  Ϊʲô�ڶ���forѭ���У�i��С�����˳������أ����������ɾ�������ˣ�ԭ�����ھͿ�����ͬһ�ַ���γ��ֵ�ʱ������ҵ��Ǹ��ַ���β������Ϊ���յľ��롣��Ȼ�ˣ����û��ģʽ���г��ֵ��ַ�����������len�ˡ�
*/
void CAlgorithm::Bc(char * s, int * Bc_table)
{
	int len = strlen(s);
	int i = 0;
	for (i = 0; i<256; i++)
	{
		*(Bc_table + i) = len;  //�Ȱ�ӳ���ľ���ȫ����ʼ��Ϊģʽ���ĳ���
	}
	int j = 0;
	for (j = 0; j<len - 1; ++j)
	{
		Bc_table[s[j]] = len - j - 1;//��¼ģʽ���У�ÿ���ַ�����Ǹ��ַ���λ��
	}
}

//���ݺú�׺��λ�ã���ȡ�ú�׺��Ӧ�����ģʽ���ĳ���
void CAlgorithm::get_suffix(char * s, int * suffix)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int result;
	int len = strlen(s);  //ģʽ���ĳ���
	suffix[len - 1] = len;  //ģʽ�����һ���ַ���һ������������һ����ȫģʽ����׺�����Գ��Ⱦ���ģʽ���ĳ���
	for (i = len - 2; i >= 0; --i)  //��ģʽ���ĵ����ڶ����ַ���ʼѭ������suffix��ֵ
	{
		k = i;   //������ҪѰ�ҵ��Ǹ��Ӵ��ĵ�һ���ַ�
		j = len - 1; //ģʽ�������һ���ַ�
		result = 0; //��¼�Ǹ��Ӵ��ĳ���
		while (s[k--] == s[j--]) //��ʼ��ǰ�Ƚ�
		{
			++result;
		}
		suffix[i] = result; //�õ����ģʽ���ĺ�׺�ĳ���
	}
}

//Gsӳ������⺯����
void CAlgorithm::Gs(char *s, int * Gs_table)
{
	int len = strlen(s);
	int i;
	int * suffix = new int[len];
	//����suffix����
	get_suffix(s, suffix);
	for (i = 0; i<len; i++)
	{
		Gs_table[i] = len;  //�Ȱ����е��ƶ������ʼ��Ϊģʽ���ĳ���
	}
	int j = 0;
	//�ڶ������
	for (i = len - 2; i >= 0; --i)
	{
		if (suffix[i] == i + 1)//x[i+1-suff[i]��i]����x[m-1-siff[i]��m-1],��suff[i]==i+1������֪��x[i+1-suff[i]��i]=x[0,i],Ҳ����ǰ׺������ڶ��������
		{
			for (; j<len - 1 - i; ++j)  //
			{
				if (Gs_table[j] == len)//��ֻ֤���޸�һ��
				{
					Gs_table[j] = len - 1 - i;
				}
			}
		}
	}
	for (i = 0; i <= len - 2; ++i)   //��Ӧ�ڵ���������������ǰ��ͼ��������
		Gs_table[len - 1 - suffix[i]] = len - 1 - i;
}

int CAlgorithm::BM(char * s, char * t)
{
	int i = 0;
	int j = 0;
	int length_s = strlen(s);  //�����ĳ���
	int length_t = strlen(t);  //ģʽ���ĳ���
	int * B = new int[256];
	int * G = new int[length_t];
	Bc(t, B);
	Gs(t, G);
	while (j <= length_s - length_t)
	{
		for (i = length_t - 1; i >= 0 && s[i + j] == t[i]; --i);//��ǰƥ��
		if (i<0)
		{
			return j + 1;
		}
		else
		{
			int g = G[i];
			int b = B[s[i + j]] - length_t + 1 + i;
			//ѡ������ֵ
			if (g >= b)
				j += g;
			else
				j += b;

		}
	}
	return 0;
}

#pragma endregion



#pragma region �������� https://blog.csdn.net/qq_35644234/article/details/60578189

#pragma endregion


#pragma region ��С������ https://blog.csdn.net/luoshixian099/article/details/51908175

#pragma endregion

#pragma region �㷨���˼�� https://blog.csdn.net/zolalad/article/details/11393915

#pragma endregion