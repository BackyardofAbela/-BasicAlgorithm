#pragma once
#include <iostream>
#include <cstdio>
#include <list>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;
class CAlgorithm
{
public:
	CAlgorithm();
	~CAlgorithm();
	vector<int> CAlgorithm::bfs(map<int, vector<int> > link, int top);
	vector<string> CAlgorithm::Split(const string src, string separate_character);
	vector<int> CAlgorithm::dfs(map<int, vector<int>> link, int top);
	int CAlgorithm::hungary(int u);
	void CAlgorithm::runHungary();
	int CAlgorithm::index_force(char * s, char * t, int pos);
	void CAlgorithm::get_next(char * s, int * next);
	int CAlgorithm::KMP(char * s, char * t, int pos);
	int CAlgorithm::Horspool(char * source, char * pattern);
	void CAlgorithm::Bc(char * s, int * Bc_table);
	void CAlgorithm::get_suffix(char * s, int * suffix);
	void CAlgorithm::Gs(char *s, int * Gs_table);
	int CAlgorithm::BM(char * s, char * t);
};

void quickSort(int arr[]);
void BubbleSort(int arr[]);
void InsertSort(int arr[]);
void ShellSort(int arr[]);
void SelectSort(int arr[]);
void HeapSort(int arr[]);
void mergeSort(int array[]);
void countSort(int arr[]);
void bucketSort(int arr[], int size);
void radixSort(int arr[]);
int SequenceSearch(int a[], int value, int n);
int BinarySearch1(int a[], int value, int n);
int BinarySearch2(int a[], int value, int low, int high);
int InsertionSearch(int a[], int value, int low, int high);
int FibonacciSearch(int *a, int n, int key);