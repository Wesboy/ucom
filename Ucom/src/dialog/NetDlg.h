#pragma once


#include "UBase.h"
#include "iSocket.h"

// CNetDlg �Ի���
enum NetDlg_Type
{
	netdlg_tcpserver = 0,
	netdlg_tcpclient = 1,
	netdlg_udp = 2
};
#define NETDLG_TCP_CLIENT 0
#define NETDLG_TCP_SERVER 1
#define NETDLG_UDP		  2

class CNetDlg : public CDialog, public UcomBase
{
	DECLARE_DYNAMIC(CNetDlg)

private:
	//�����߳̾��
	HANDLE hRxThread;
	iSocket mSocket;
	bool isWorking;
	int curSender;	// ��ǰ���͵Ŀͻ���
	int typeSel;
	CString infoServer, infoLocal;
	HWND hwTopParent;
public:
	CNetDlg(CWnd* pParent = NULL);
	virtual ~CNetDlg();
	void SethwTopParent(HWND pTopParent) {
		hwTopParent = pTopParent;
	}

	void InitPanel(void);
	void SwPanel(bool choose);
	void EnableIPIn(int type);
	void ChangeBmpPic(int PicCtrlID, unsigned short nPicID);
	void SetTips(CString tips);
	void GetDstIPStr(CString &str);

	void LoadRegConfig();
	// �����ڹر�ʱ��OnClose��Ҫ���ñ���һ����Ϣ
	void WriteRegData(void);

	//client�б���
	void DelClient(nSocketPara *nPara);
	void AddClient(nSocketPara *nPara);
	void CleanClient(void);
	
	void OpenSocket(void);

	int AsyncSend(const CString &dataStr);
	int AsyncSendBuf(unsigned char *buf, unsigned int len);
	int AsyncRead(CString &dataStr, CString & infoStr, WPARAM wParam, LPARAM lParam);
	bool IsRWable(void) {
		return mSocket.IsScoketOpen();
	}

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBtnConnect();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnEditPortSendComplete();
	afx_msg LRESULT CNetDlg::OnMyReceiveMsg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSelNetType();
	afx_msg void OnSelChangeCient();
	afx_msg void OnEditPortRecvComplete();
	afx_msg void OnClickedNpicuartstatus();
};
