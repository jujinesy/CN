
// CNDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "CN.h"
#include "CNDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <math.h>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_IPADDRESS1, E_IPv);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCNDlg 대화 상자



CCNDlg::CCNDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCNDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCNDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, E_IPv);
	DDX_Control(pDX, IDC_IPADDRESS2, E_IPv2);
}

BEGIN_MESSAGE_MAP(CCNDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCNDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCNDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCNDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CCNDlg 메시지 처리기

BOOL CCNDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCNDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCNDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCNDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int getOctetsIP(string ip, vector<int> &octetsIP) {		// Define vector<int> octets, using reference from main
	stringstream sip(ip);								// use stringstream named ss and populate with ip
	string temp;
	octetsIP.clear();									// Clears the octetsMask vector, in case main function re-runs this function
	vector<bool> ipInRange;
	while (getline(sip, temp, '.'))						// Every time getline recieves new stream element from ss, save to temp
		octetsIP.push_back(atoi(temp.c_str()));			//... until reaches '.' delimiter, then push_back octet with new element.
	if (octetsIP.size() == 4) {
		for (int i = 0; i < octetsIP.size(); i++){
			if (octetsIP[i] >= 0 && octetsIP[i] <= 255)
				ipInRange.push_back(true);
			else
				ipInRange.push_back(false);
		}
		if (ipInRange[0] == true && ipInRange[1] == true && ipInRange[2] == true && ipInRange[3] == true){
			return 0;
		}
		else{
			cout << endl << "There are only 255 bits per octet. Please re-enter IP." << endl << endl;
			return 1;
		}
	}
	else{
		cout << endl << "Please enter four octets in dot notation." << endl << endl;
		return 1;
	}
}




int getOctetsMask(string mask, vector<int> &octetsMask) {
	stringstream smask(mask);
	string temp;
	octetsMask.clear();		// Clears the octetsMask vector, in case main function re-runs this function
	vector<bool> maskInRange;
	while (getline(smask, temp, '.'))
		octetsMask.push_back(atoi(temp.c_str()));
	if (octetsMask.size() == 4){
		for (int i = 0; i < octetsMask.size(); i++){
			if (octetsMask[i] == 0 || octetsMask[i] == 128 || octetsMask[i] == 192 || octetsMask[i] == 224 || octetsMask[i] == 240 || octetsMask[i] == 248 || octetsMask[i] == 252 || octetsMask[i] == 254 || octetsMask[i] == 255)
				maskInRange.push_back(true);
			else
				maskInRange.push_back(false);
		}
		if (maskInRange[0] == true && maskInRange[1] == true && maskInRange[2] == true && maskInRange[3] == true){
			return 0;
		}
		else{
			cout << endl << "Subnet masks only use 2^[0-7]. Please re-enter mask." << endl << endl;
			return 1;
		}
	}
	else{
		cout << endl << "Please enter four octets in dot notation." << endl << endl;
		return 1;
	}
}




int calcClass(vector<int> &octetsIP) {
	if (octetsIP[0] == 10) {
		return 1;	// Class A Private address blocks //
	}
	else if (octetsIP[0] == 172 && octetsIP[1] >= 16 && octetsIP[1] <= 31) {
		return 2;	// Class B Private address blocks //
	}
	else if (octetsIP[0] == 192 && octetsIP[1] == 168) {
		return 3;	// Class C Private address blocks //
	}
	else if (octetsIP[0] == 127) {
		return 4;	// Loopback Address Reserved address blocks //
	}
	else if (octetsIP[0] >= 0 && octetsIP[0] < 127) {
		return 5;
	}
	else if (octetsIP[0] > 127 && octetsIP[0] < 192) {
		return 6;
	}
	else if (octetsIP[0] > 191 && octetsIP[0] < 224) {
		return 7;
	}
	else if (octetsIP[0] > 223 && octetsIP[0] < 240) {
		return 8;
	}
	else if (octetsIP[0] > 239 && octetsIP[0] <= 255) {
		return 9;
	}
	else{
		return 0;	// Out of Range //
	}
}




// Determine Binary /--
int getNHBits(vector<int> &octetsIP, vector<int> &octetsMask, vector<int> &octetsIPBits, vector<int> &octetsMaskBits){

	// Get IP binary rep. // 
	cout << "------------------------------------------" << endl;
	cout << "///////// Binary Representation //////////" << endl;
	cout << "------------------------------------------" << endl;
	for (int j = 0; j < octetsIP.size(); j++)
	{
		if (j>0)
			cout << ".";

		int mask = 128;
		while (mask)
		{
			octetsIPBits.push_back((octetsIP[j] & mask) != 0);
			cout << ((octetsIP[j] & mask) != 0);
			mask >>= 1;
		}
	}
	cout << "  : IP Address" << endl;

	// Get SUBNET binary rep. // 
	for (int j = 0; j < octetsMask.size(); j++)
	{
		if (j>0)
			cout << ".";
		int mask = 128;
		while (mask)
		{
			octetsMaskBits.push_back((octetsMask[j] & mask) != 0);
			cout << ((octetsMask[j] & mask) != 0);
			mask >>= 1;
		}
	}
	cout << "  : Subnet Mask" << endl;
	cout << "-----------------------------------------" << endl;

	return 0;
}



// Perform ANDing of IP and Subnet Mask to generate Network ID range //
vector<int> getNetID(vector<int> &octetsIPBits, vector<int> &octetsMaskBits){
	vector<int> netID;
	for (int j = 0; j < octetsIPBits.size(); j++)
	{
		if ((j > 0) && (j % 8 == 0))
			cout << ".";

		netID.push_back(octetsIPBits[j] & octetsMaskBits[j]);
	}
	return netID;
}


// Turn Binary back to Decimal
string toString(vector<int> octets){
	ostringstream octStrm;

	for (int j = 0; j < octets.size(); j++)
	{
		if (j>0)
			octStrm << '.';

		octStrm << octets[j];
	}

	return octStrm.str();
}


// Turn Binary back to Decimal
vector<int> toDecimal(vector<int> octets, vector<int> &decimals){
	stringstream octStrm;
	decimals.clear();
	for (int j = 0; j < octets.size(); j++)
	{
		if (j>0)
			octStrm << '.';

		octStrm << octets[j];
	}

	string temp;
	while (getline(octStrm, temp, '.'))
		decimals.push_back(atoi(temp.c_str()));

	return decimals;
}

// Get the network increment //
int getIncrement(vector<int> decimalMask, vector<int> decimalNetID){
	int increment = 0;
	for (int i = 0; i<decimalMask.size(); i++){
		if (decimalMask[i] == 255){
			increment = 1;
		}
		else if (decimalMask[i] == 254){
			increment = 2;
			break;
		}
		else if (decimalMask[i] == 252){
			increment = 4;
			break;
		}
		else if (decimalMask[i] == 248){
			increment = 8;
			break;
		}
		else if (decimalMask[i] == 240){
			increment = 16;
			break;
		}
		else if (decimalMask[i] == 224){
			increment = 32;
			break;
		}
		else if (decimalMask[i] == 192){
			increment = 64;
			break;
		}
		else if (decimalMask[i] == 128){
			increment = 128;
			break;
		}
	}
	return increment;
}

// get network id range
vector<int> getNetIDRange(vector<int> &decimalNetID, int &netInc, vector<int> &decimalMask) {
	vector<int> netIDEnd;
	for (int i = 0; i<decimalNetID.size(); i++){
		if (decimalMask[i] == 255){
			netIDEnd.push_back(decimalNetID[i]);
		}
		else if (decimalMask[i] < 255 && decimalMask[i] > 0){
			netIDEnd.push_back((decimalNetID[i] + netInc) - 1);
		}
		else{
			netIDEnd.push_back(255);
		}
	}
	return netIDEnd;
}



// Get subnets
int getSubnets(vector<int> &decimalMask, int &ipClass, vector<int> &subClassMask){
	int netBits = 0;
	subClassMask.clear();
	if (ipClass == 1){
		subClassMask.push_back(255);
		subClassMask.push_back(0);
		subClassMask.push_back(0);
		subClassMask.push_back(0);
	}
	else if (ipClass == 2){
		subClassMask.push_back(255);
		subClassMask.push_back(255);
		subClassMask.push_back(0);
		subClassMask.push_back(0);
	}
	else if (ipClass == 3){
		subClassMask.push_back(255);
		subClassMask.push_back(255);
		subClassMask.push_back(255);
		subClassMask.push_back(0);
	}
	else if (ipClass == 4 || ipClass == 5){
		subClassMask.push_back(decimalMask[0]);
		subClassMask.push_back(decimalMask[1]);
		subClassMask.push_back(decimalMask[2]);
		subClassMask.push_back(decimalMask[3]);
	}

	for (int i = 0; i<decimalMask.size(); i++){
		if (decimalMask[i] != subClassMask[i]){
			if (decimalMask[i] == 255){
				netBits += 8;
				continue;
			}
			else if (decimalMask[i] == 254){
				netBits += 7;
				continue;
			}
			else if (decimalMask[i] == 252){
				netBits += 6;
				continue;
			}
			else if (decimalMask[i] == 248){
				netBits += 5;
				continue;
			}
			else if (decimalMask[i] == 240){
				netBits += 4;
				continue;
			}
			else if (decimalMask[i] == 224){
				netBits += 3;
				continue;
			}
			else if (decimalMask[i] == 192){
				netBits += 2;
				continue;
			}
			else if (decimalMask[i] == 128){
				netBits += 1;
				continue;
			}
			else if (decimalMask[i] == 0){
				netBits += 0;
				continue;
			}
			else{
				netBits += 0;
			}
		}
	}
	int subnets = pow(2.0, netBits);
	return subnets;
}



// Get hosts per subnet
int getHostsPerSubnet(vector<int> &decimalMask){
	int hostBits = 0;
	for (int i = 0; i<decimalMask.size(); i++){
		if (decimalMask[i] == 255){
			hostBits += 0;
			continue;
		}
		else if (decimalMask[i] == 254){
			hostBits += 1;
			continue;
		}
		else if (decimalMask[i] == 252){
			hostBits += 2;
			continue;
		}
		else if (decimalMask[i] == 248){
			hostBits += 3;
			continue;
		}
		else if (decimalMask[i] == 240){
			hostBits += 4;
			continue;
		}
		else if (decimalMask[i] == 224){
			hostBits += 5;
			continue;
		}
		else if (decimalMask[i] == 192){
			hostBits += 6;
			continue;
		}
		else if (decimalMask[i] == 128){
			hostBits += 7;
			continue;
		}
		else if (decimalMask[i] == 0){
			hostBits += 8;
			continue;
		}
		else{
			hostBits = 0;
			break;
		}
	}
	int hostsPerSubnet = pow(2.0, hostBits) - 2;
	return hostsPerSubnet;
}


void CCNDlg::OnBnClickedButton1()
{
	CString Temp, Temp2;
	BYTE IP_a, IP_b, IP_c, IP_d;

	E_IPv.GetAddress(IP_a, IP_b, IP_c, IP_d);
	Temp.Format(_T("%o.%o.%o.%o"), IP_a, IP_b, IP_c, IP_d);
	Temp2.Format(_T("%x.%x.%x.%x"), IP_a, IP_b, IP_c, IP_d);

	if (IP_a == NULL || IP_b == NULL || IP_c == NULL || IP_d == NULL)
	{
		MessageBox(_T("Wrong IP Address! Plz Check your Input."), MB_OK);
	}
	else {
		MessageBox(_T(" 8진수 : ") + Temp + _T("\n16진수 : ") + Temp2, MB_OK);
	}
}


void CCNDlg::OnBnClickedButton2()
{
	CString Temp;
	BYTE IP_a, IP_b, IP_c, IP_d;

	E_IPv.GetAddress(IP_a, IP_b, IP_c, IP_d);
	
	if (IP_a <= 127){
		Temp = "A";
	}
	else if (IP_a <= 191){
		Temp = "B";
	}
	else if (IP_a <= 223){
		Temp = "C";
	}
	else if (IP_a <= 239){
		Temp = "D";
	}
	else if (IP_a <= 254){
		Temp = "E";
	}

	if (IP_a == NULL || IP_b == NULL || IP_c == NULL || IP_d == NULL)
	{
		MessageBox(_T("Wrong IP Address! Plz Check your Input."), MB_OK);
	}
	else {
		MessageBox( Temp + _T(" 클래스"), MB_OK);
	}
}


void CCNDlg::OnBnClickedButton3()
{
	CString Temp;
	BYTE IP_a, IP_b, IP_c, IP_d;

	E_IPv.GetAddress(IP_a, IP_b, IP_c, IP_d);
	Temp.Format(_T("%d.%d.%d.%d"), IP_a, IP_b, IP_c, IP_d);
	string ip;
	vector<int> octetsIP;

	ip = std::string(CT2CA(Temp.operator LPCWSTR()));
	octetsIP.push_back(IP_a);
	octetsIP.push_back(IP_b);
	octetsIP.push_back(IP_c);
	octetsIP.push_back(IP_d);

	E_IPv2.GetAddress(IP_a, IP_b, IP_c, IP_d);
	Temp.Format(_T("%d.%d.%d.%d"), IP_a, IP_b, IP_c, IP_d);

	string mask;
	vector<int> octetsMask;

	mask = std::string(CT2CA(Temp.operator LPCWSTR()));
	octetsMask.push_back(IP_a);
	octetsMask.push_back(IP_b);
	octetsMask.push_back(IP_c);
	octetsMask.push_back(IP_d);
	cout << endl << endl << endl << endl << endl;

	vector<int> decimals;
	vector<int> decimalMask = toDecimal(octetsMask, decimals);

	vector<int> octetsIPBits;
	vector<int> octetsMaskBits;
	getNHBits(octetsIP, octetsMask, octetsIPBits, octetsMaskBits);
	vector<int> netID = getNetID(octetsIP, octetsMask);
	vector<int> decimalNetID = toDecimal(netID, decimals);
	int netInc = getIncrement(decimalMask, decimalNetID);
	cout << endl;
	int classResult = calcClass(octetsIP);
	int ipClass = 0;
	switch (classResult){
	case 1:
		ipClass = 1;
		break;
	case 2:
		ipClass = 2;
		break;
	case 3:
		ipClass = 3;
		break;
	case 4:
		ipClass = 1;
		break;
	case 5:
		ipClass = 1;
		break;
	case 6:
		ipClass = 2;
		break;
	case 7:
		ipClass = 3;
		break;
	case 8:
		ipClass = 4;
		break;
	case 9:
		ipClass = 5;
		break;
	default:
		break;
	}
	vector<int> subClassMask;
	getSubnets(decimalMask, ipClass, subClassMask);
	vector<int> netIDRange = getNetIDRange(decimalNetID, netInc, decimalMask);
	MessageBox(CString::CStringT(CA2CT(toString(netID).c_str())) + _T(" ~ ") + CString::CStringT(CA2CT(toString(netIDRange).c_str())), MB_OK);
}
