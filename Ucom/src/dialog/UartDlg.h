#pragma once

#include "iUart.h"


// CUartDlg �Ի���
class CUartDlg : public CDialog, public UcomBase
{
	DECLARE_DYNAMIC(CUartDlg)

private:
	HANDLE hRxThread;	// �����߳̾��
	HWND hwTopParent;	// ���㴰�ھ��
	bool IsUartPortAvailable(void);
	//����Ƿ��ڹ���״̬
	bool isWorking;
	iUart mUart;
	void ClearFlowCtrlStats(void);
public:

	void InitPanel(void);
	void SwPanel(bool choose);
	void ChangeBmpPic(int PicCtrlID, unsigned short nPicID);

	void OpenUart();

	void OnDropdownCbUartPort();
	void OnSelendokCbUartPort();

	DCB GetUartConfigDCB(void);
	void LoadRegConfig();
	void GetRegData(CString &comName, CString &dcbConfig);
	// �����ڹر�ʱ��OnClose��Ҫ���ñ���һ����Ϣ
	void WriteRegData(void);

	void SethwTopParent(HWND pTopParent) {
		hwTopParent = pTopParent;
	}
	int AsyncSend(const CString &dataStr) {
		if (!isWorking)
			return -1;
		return mUart.UnblockSend(dataStr);
	}
	int AsyncSendBuf(unsigned char *buf, unsigned int len)
	{
		if (!isWorking)
			return -1;
		return mUart.UnblockSendBuf(buf, len);
	}
	int AsyncRead(CString &dataStr, CString & infoStr, WPARAM wParam, LPARAM lParam) {
		if (!isWorking)
			return -1;
		return mUart.UnblockRead(dataStr);
	}
	bool IsRWable(void) {
		return isWorking;
	}
public:
	CUartDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUartDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UART };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBtnOpen();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnStnClickedPicuartstatus();
	afx_msg void OnBnClickedCkbdtr();
	afx_msg void OnBnClickedCkbrts();
	afx_msg LRESULT OnMyReceiveMsg(WPARAM wParam, LPARAM lParam);
};
