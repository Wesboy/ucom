
// UcomDlg.h : ͷ�ļ�
//

#pragma once

#include "Text.h"
#include "iUart.h"
#include "GraphDlg.h"
#include "Encoder.h"
#include "DataWatch.h"
#include "MultiSend.h"
#include "SendFile.h"

#include "UBase.h"
#include "UartDlg.h"
#include "NetDlg.h"
#include "CmdCtl.h"


//typedef  AsyncSendX* AsyncSendX;
//typedef  IsOpenX* IsOpenX;

#define AUTO_SEND_TIMER_ID 100
#define FLASH_RX_EDITBOX_TIMER_ID 101
// CUcomDlg �Ի���
//class CUcomDlg : public CDialogEx
class CUcomDlg : public CDialog
{
// ����
public:
	CUcomDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UCOM_DIALOG };
	
public:
	const int rxFlashPeriod = 40;

	bool isNewLineSend;
	bool bSizeChange;
	bool isDispHex, isSendHex, isDispRx, isRxFullClc,isCmdMode;
	UINT rxCnt, txCnt;
	int limitBytes;
	long iHeight, iWight;
	int m_nWidth, m_nHeight;
	float m_Multiple_width,m_Mutiple_heith;


	void LoadRegConfig();
	void WriteRegData(void);

	void ReflashRecvEdit(void);
	void SendEditBoxData();
	void SetDelaySend(void);

	TextBank DataRx, DataTx;

	void SetRichLineSpace(void);
	void SetFullBytes(int nbytes = -1);

	DWORD backgroudColor;
	void InitTabEx(void);
	void InitTabSrc(void);

	int encoderMode;

	UINT curDataSrc;
	UcomBase *uBase;
	void SwitchCurDataSrc(UINT dataSrc);
private:
	#define MAX_CMD_HISTORY 10
	BOOL PreTranslateMessage(MSG* pMsg);
	int cmdNextPointer, cmdDispPointer;
	CString cmdHistory[MAX_CMD_HISTORY];
	CString lastInfo;
	int LargerMode;
	bool isLarge;
	//����Ƿ��ڹ���״̬
	bool isWorking;
	void ChangeItemSize(int nID, int x, int y, int isEnlarge);
	int MaxWndHeight;

	CGraphDlg GraphDlg;
	CEncoder EncoderDlg;
	CDataWatch DataWatchDlg;
	CMultiSend MultiSendDlg;

	CUartDlg UartDlg;
	CNetDlg NetDlg;
	CmdCtl CmdDlg;

	UINT widthEx, heightDlgMin, widthDlgMin;	//������չ���Ŀ��
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnSend();
	afx_msg void OnBtnClearRecv();
	afx_msg void OnBtnClearSend();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCkbSendOnTime();
	afx_msg void OnChangeEdbSendDelay();
	afx_msg void OnCkbFrameNewLine();
	afx_msg void OnBtnClearnCnt();
	afx_msg void OnCkbDispHex();
	afx_msg void OnChangeEditTxData();
	afx_msg void OnCkbSendHex();
	afx_msg void OnBnClickedBtnisdisprx();
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtntoolbox();
	afx_msg void OnMeudevmanger();
	afx_msg void OnMeucalc();
	afx_msg void OnMeunotepad();
	afx_msg void OnMenureg();
	afx_msg void OnMenucmd();
	afx_msg void OnMenuserv();
	afx_msg void OnBnClickedBtnwinsize();
	afx_msg void OnBnClickedBtnbackcolor();
	afx_msg void OnBnClickedBtnfontcolor();
	afx_msg void OnBnClickedBtnfont();
	afx_msg void OnBnClickedCkbrxfullclc();
	afx_msg void OnChangeEdbfullbytes();
	afx_msg void OnBnClickedBtnsaverx();
	afx_msg void OnBnClickedBtnclearall();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnhelp();
	afx_msg void OnSelchangeTabex(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnencoder();
	virtual void OnOK();
	afx_msg void OnBnClickedBtnsendfile();
	afx_msg void OnBnClickedCkbcmd();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void ReSize(int nID);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg LRESULT OnMyReceiveMsg(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSelchangeTabsrc(NMHDR *pNMHDR, LRESULT *pResult);
};
