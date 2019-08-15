#pragma once

#include "UBase.h"
// CmdCtl 对话框

class CmdCtl : public CDialog
{
	DECLARE_DYNAMIC(CmdCtl)

public:
	CmdCtl::CmdCtl(CWnd *pParent, UcomBase **mbase); // 标准构造函数
	virtual ~CmdCtl();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CMDCTL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	bool b_btnRedOpen;
	bool b_btnGreenOpen;
	bool b_btnBlueOpen;

	enum {
		I_RED,
		I_GREEN,
		I_BLUE,
	};

	CSliderCtrl m_redPwm;
	CSliderCtrl m_GreenPwm;
	CSliderCtrl m_BluePwm;
	UcomBase *cuBase;

	virtual BOOL OnInitDialog();
	void ChangeBmpPic(int PicCtrlID, unsigned short nPicID);
	void SendCmdToDevice(char *buffer);
	void SetLedOn(unsigned short iColor, bool bOn);
	int UnblockSend(const CString &dataStr);

	afx_msg void OnBnClickedBtnRedOpen();
	afx_msg void OnBnClickedBtnGreenOpen();
	afx_msg void OnBnClickedBtnBlueOpen();
	afx_msg void OnNMCustomRedPwmDraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomGreenPwmDraw(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomBluePwmDraw(NMHDR *pNMHDR, LRESULT *pResult);
};
