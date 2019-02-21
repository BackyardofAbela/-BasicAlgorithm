
// DataStructDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CDataStructDlg �Ի���



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


// CDataStructDlg ��Ϣ�������

BOOL CDataStructDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDataStructDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDataStructDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//ŷ����·
void CDataStructDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

}


//�������
void CDataStructDlg::OnBnClickedBtnbfs()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int x, top, m, n, i = 0;
	map<int, vector<int> > link;//ͼ���ڽӱ�
	ifstream fin;
	fin.open("F:\\01.ѧϰ����\\08_���ݽṹ\\code\\graph.txt");
	CAlgorithm alg;
	string str;
	while (!fin.eof())
	{
		getline(fin, str);
		vector<string> ss = alg.Split(str," ");
		m = stoi(ss[0]);
		n = stoi(ss[1]);
		link[m].push_back(n);
		link[n].push_back(m);//����ͼ�������߶����ڽӹ�ϵ

	}
	fin.close();
	vector<int> order;
	order = alg.bfs(link, 2);
}


//�������
void CDataStructDlg::OnBnClickedBtndfs()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int x, top, m, n, i = 0;
	map<int, vector<int> > link;//ͼ���ڽӱ�
	ifstream fin;
	fin.open("F:\\01.ѧϰ����\\08_���ݽṹ\\code\\graph.txt");
	CAlgorithm alg;
	string str;
	while (!fin.eof())
	{
		getline(fin, str);
		vector<string> ss = alg.Split(str, " ");
		m = stoi(ss[0]);
		n = stoi(ss[1]);
		link[m].push_back(n);
		link[n].push_back(m);//����ͼ�������߶����ڽӹ�ϵ

	}
	fin.close();
	vector<int> order;
	order = alg.dfs(link, 2);
}


void CDataStructDlg::OnBnClickedBtnhangary()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CAlgorithm alg;
	alg.runHungary();
}

#pragma region �ַ���ƥ��
char* sub = "ooooa";
char* host = "oooocooooa";
//����ƥ��
void CDataStructDlg::OnBnClickedButton39()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CAlgorithm alg;
	alg.index_force(host, sub, 0);
}

//KMP�㷨
void CDataStructDlg::OnBnClickedButton40()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CAlgorithm alg;
	alg.KMP(host, sub, 0);
}

//BM�㷨
void CDataStructDlg::OnBnClickedButton41()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CAlgorithm alg;
	alg.BM(host, sub);
}



//horspool�㷨
void CDataStructDlg::OnBnClickedButton42()
{
	// TODO:  
	CAlgorithm alg;
	alg.Horspool(host, sub);
}
#pragma endregion

//Լɪ�򻷣��õݹ������ķ�ʽ��ɣ�https://blog.csdn.net/tingyun_say/article/details/52343897
void CDataStructDlg::OnBnClickedButton18()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

int arr[11] = {102,8,5,4,7,9,12,23,34,6,87};
//ð������
void CDataStructDlg::OnBnClickedButton8()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	BubbleSort(arr);
}

//ѡ������
void CDataStructDlg::OnBnClickedButton9()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SelectSort(arr);
}

//��������
void CDataStructDlg::OnBnClickedButton10()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	InsertSort(arr);
}

//ϣ������
void CDataStructDlg::OnBnClickedButton11()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	ShellSort(arr);
}


//�鲢����
void CDataStructDlg::OnBnClickedButton12()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	mergeSort(arr);
}

//��������
void CDataStructDlg::OnBnClickedButton13()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	quickSort(arr);
}

//������
void CDataStructDlg::OnBnClickedButton14()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	HeapSort(arr);
}

//��������
void CDataStructDlg::OnBnClickedButton15()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	countSort(arr);
}

//Ͱ����
void CDataStructDlg::OnBnClickedButton16()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	bucketSort(arr,4);
}

//��������
void CDataStructDlg::OnBnClickedButton17()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	radixSort(arr);
}


//˳�����
void CDataStructDlg::OnBnClickedButton21()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	SequenceSearch(arr, 5, 11);
}



//���ֲ���
void CDataStructDlg::OnBnClickedButton22()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	BinarySearch1(arr, 5, 11);
	BinarySearch2(arr, 5, 0, 10);
}


//��ֵ����
void CDataStructDlg::OnBnClickedButton23()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	InsertionSearch(arr, 5, 0, 10);
}

//�ֿ����
void CDataStructDlg::OnBnClickedButton24()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

}

//쳲���������
void CDataStructDlg::OnBnClickedButton25()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	FibonacciSearch(arr, 11, 5);
}
