
// DataStructDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DataStruct.h"
#include "DataStructDlg.h"
#include "afxdialogex.h"
#include  <iostream>
#include  <fstream>
#include  <string>
#include <map>
#include <vector>
#include "Algorithm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDataStructDlg 对话框



CDataStructDlg::CDataStructDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDataStructDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDataStructDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDataStructDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &CDataStructDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BTNBFS, &CDataStructDlg::OnBnClickedBtnbfs)
	ON_BN_CLICKED(IDC_BTNDFS, &CDataStructDlg::OnBnClickedBtndfs)
	ON_BN_CLICKED(IDC_BTNHangary, &CDataStructDlg::OnBnClickedBtnhangary)
	ON_BN_CLICKED(IDC_BUTTON39, &CDataStructDlg::OnBnClickedButton39)
	ON_BN_CLICKED(IDC_BUTTON40, &CDataStructDlg::OnBnClickedButton40)
	ON_BN_CLICKED(IDC_BUTTON41, &CDataStructDlg::OnBnClickedButton41)
	ON_BN_CLICKED(IDC_BUTTON42, &CDataStructDlg::OnBnClickedButton42)
	ON_BN_CLICKED(IDC_BUTTON18, &CDataStructDlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTON8, &CDataStructDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CDataStructDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CDataStructDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CDataStructDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CDataStructDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CDataStructDlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON14, &CDataStructDlg::OnBnClickedButton14)
	ON_BN_CLICKED(IDC_BUTTON15, &CDataStructDlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &CDataStructDlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTON17, &CDataStructDlg::OnBnClickedButton17)
	ON_BN_CLICKED(IDC_BUTTON21, &CDataStructDlg::OnBnClickedButton21)
	ON_BN_CLICKED(IDC_BUTTON22, &CDataStructDlg::OnBnClickedButton22)
	ON_BN_CLICKED(IDC_BUTTON23, &CDataStructDlg::OnBnClickedButton23)
	ON_BN_CLICKED(IDC_BUTTON24, &CDataStructDlg::OnBnClickedButton24)
	ON_BN_CLICKED(IDC_BUTTON25, &CDataStructDlg::OnBnClickedButton25)
END_MESSAGE_MAP()


// CDataStructDlg 消息处理程序

BOOL CDataStructDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDataStructDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDataStructDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDataStructDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//欧拉回路
void CDataStructDlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码

}


//广度搜索
void CDataStructDlg::OnBnClickedBtnbfs()
{
	// TODO:  在此添加控件通知处理程序代码
	int x, top, m, n, i = 0;
	map<int, vector<int> > link;//图的邻接表
	ifstream fin;
	fin.open("F:\\01.学习资料\\08_数据结构\\code\\graph.txt");
	CAlgorithm alg;
	string str;
	while (!fin.eof())
	{
		getline(fin, str);
		vector<string> ss = alg.Split(str," ");
		m = stoi(ss[0]);
		n = stoi(ss[1]);
		link[m].push_back(n);
		link[n].push_back(m);//无向图所以两边都有邻接关系

	}
	fin.close();
	vector<int> order;
	order = alg.bfs(link, 2);
}


//深度搜索
void CDataStructDlg::OnBnClickedBtndfs()
{
	// TODO:  在此添加控件通知处理程序代码
	int x, top, m, n, i = 0;
	map<int, vector<int> > link;//图的邻接表
	ifstream fin;
	fin.open("F:\\01.学习资料\\08_数据结构\\code\\graph.txt");
	CAlgorithm alg;
	string str;
	while (!fin.eof())
	{
		getline(fin, str);
		vector<string> ss = alg.Split(str, " ");
		m = stoi(ss[0]);
		n = stoi(ss[1]);
		link[m].push_back(n);
		link[n].push_back(m);//无向图所以两边都有邻接关系

	}
	fin.close();
	vector<int> order;
	order = alg.dfs(link, 2);
}


void CDataStructDlg::OnBnClickedBtnhangary()
{
	// TODO:  在此添加控件通知处理程序代码
	CAlgorithm alg;
	alg.runHungary();
}

#pragma region 字符串匹配
char* sub = "ooooa";
char* host = "oooocooooa";
//朴素匹配
void CDataStructDlg::OnBnClickedButton39()
{
	// TODO:  在此添加控件通知处理程序代码
	CAlgorithm alg;
	alg.index_force(host, sub, 0);
}

//KMP算法
void CDataStructDlg::OnBnClickedButton40()
{
	// TODO:  在此添加控件通知处理程序代码
	CAlgorithm alg;
	alg.KMP(host, sub, 0);
}

//BM算法
void CDataStructDlg::OnBnClickedButton41()
{
	// TODO:  在此添加控件通知处理程序代码
	CAlgorithm alg;
	alg.BM(host, sub);
}



//horspool算法
void CDataStructDlg::OnBnClickedButton42()
{
	// TODO:  
	CAlgorithm alg;
	alg.Horspool(host, sub);
}
#pragma endregion

//约瑟夫环（用递归或迭代的方式完成）https://blog.csdn.net/tingyun_say/article/details/52343897
void CDataStructDlg::OnBnClickedButton18()
{
	// TODO:  在此添加控件通知处理程序代码
}

int arr[11] = {102,8,5,4,7,9,12,23,34,6,87};
//冒泡排序
void CDataStructDlg::OnBnClickedButton8()
{
	// TODO:  在此添加控件通知处理程序代码
	BubbleSort(arr);
}

//选择排序
void CDataStructDlg::OnBnClickedButton9()
{
	// TODO:  在此添加控件通知处理程序代码
	SelectSort(arr);
}

//插入排序
void CDataStructDlg::OnBnClickedButton10()
{
	// TODO:  在此添加控件通知处理程序代码
	InsertSort(arr);
}

//希尔排序
void CDataStructDlg::OnBnClickedButton11()
{
	// TODO:  在此添加控件通知处理程序代码
	ShellSort(arr);
}


//归并排序
void CDataStructDlg::OnBnClickedButton12()
{
	// TODO:  在此添加控件通知处理程序代码
	mergeSort(arr);
}

//快速排序
void CDataStructDlg::OnBnClickedButton13()
{
	// TODO:  在此添加控件通知处理程序代码
	quickSort(arr);
}

//堆排序
void CDataStructDlg::OnBnClickedButton14()
{
	// TODO:  在此添加控件通知处理程序代码
	HeapSort(arr);
}

//计数排序
void CDataStructDlg::OnBnClickedButton15()
{
	// TODO:  在此添加控件通知处理程序代码
	countSort(arr);
}

//桶排序
void CDataStructDlg::OnBnClickedButton16()
{
	// TODO:  在此添加控件通知处理程序代码
	bucketSort(arr,4);
}

//基数排序
void CDataStructDlg::OnBnClickedButton17()
{
	// TODO:  在此添加控件通知处理程序代码
	radixSort(arr);
}


//顺序查找
void CDataStructDlg::OnBnClickedButton21()
{
	// TODO:  在此添加控件通知处理程序代码
	SequenceSearch(arr, 5, 11);
}



//二分查找
void CDataStructDlg::OnBnClickedButton22()
{
	// TODO:  在此添加控件通知处理程序代码
	BinarySearch1(arr, 5, 11);
	BinarySearch2(arr, 5, 0, 10);
}


//插值查找
void CDataStructDlg::OnBnClickedButton23()
{
	// TODO:  在此添加控件通知处理程序代码
	InsertionSearch(arr, 5, 0, 10);
}

//分块查找
void CDataStructDlg::OnBnClickedButton24()
{
	// TODO:  在此添加控件通知处理程序代码

}

//斐波那契查找
void CDataStructDlg::OnBnClickedButton25()
{
	// TODO:  在此添加控件通知处理程序代码
	FibonacciSearch(arr, 11, 5);
}
