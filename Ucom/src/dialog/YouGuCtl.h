#pragma once

#include "UBase.h"
// YouGuCtl 对话框

class YouGuCtl : public CDialog
{
	DECLARE_DYNAMIC(YouGuCtl)

public:
	YouGuCtl::YouGuCtl(CWnd *pParent, UcomBase **mbase);    // 标准构造函数
	virtual ~YouGuCtl();

	enum { IDD = IDD_YOUGUCTL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	CString strFilePath;
	bool b_btnUpdate;

	UcomBase **cuBase;
	void AppendLog(CString str);

	virtual BOOL OnInitDialog();
	void SendEarphoneCtl(void);
	void StartUpdate(void);
	void SendCmdToDevice(unsigned char *buffer);
	int UnblockSend(const CString &dataStr);
	int SendBuf(unsigned char *buf, unsigned int len);

	afx_msg void OnBnClickedUpdate();
	afx_msg void OnBnClickedbtnloadfile();
};
