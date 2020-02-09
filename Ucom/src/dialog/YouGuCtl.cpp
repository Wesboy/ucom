// F:\MyWork\update_app\Ucom\src\dialog\YouGuCtl.cpp: 实现文件
//

#include "stdafx.h"
#include "Ucom.h"
#include "YouGuCtl.h"
#include "afxdialogex.h"


// YouGuCtl 对话框

IMPLEMENT_DYNAMIC(YouGuCtl, CDialog)

YouGuCtl::YouGuCtl(CWnd *pParent, UcomBase **mbase)
	: CDialog(IDD_YOUGUCTL, pParent)
{
	cuBase = mbase;
}

YouGuCtl::~YouGuCtl()
{
}

void YouGuCtl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(YouGuCtl, CDialog)
	ON_BN_CLICKED(ID_Update, &YouGuCtl::OnBnClickedUpdate)
	ON_BN_CLICKED(IDC_btnLoadFile, &YouGuCtl::OnBnClickedbtnloadfile)
END_MESSAGE_MAP()


BOOL YouGuCtl::OnInitDialog()
{
	b_btnUpdate = FALSE;
	UpdateData(TRUE);

	return TRUE;
}


void YouGuCtl::SendEarphoneCtl(void)
{
	unsigned char cmd[] = { 0xc, 0x10, 0x01, 0x09, 0x2E, 0x2E, 0x00, 0x1F, 0x1F, 0x00, 0x0a, 0x0a, 0x00 };

	SendCmdToDevice(cmd);
}
// YouGuCtl 消息处理程序

void YouGuCtl::StartUpdate(void)
{
	unsigned char cmd[] = { 0x4, 0x80, 0x02, 0x01, 0x02};

	SendCmdToDevice(cmd);
} 


void YouGuCtl::OnBnClickedUpdate()
{
	// TODO: 在此添加控件通知处理程序代码
	//1 start update proc
	//2 send update file 
	//3 send end update
	//SendEarphoneCtl();
	StartUpdate();
}

void YouGuCtl::SendCmdToDevice(unsigned char *buffer)
{
	CString strTmp;
	unsigned char buf[32] = { 0 };
	char iCmdlen = buffer[0];
	unsigned char checkBit = 0;
	unsigned char i;

	if (iCmdlen > 0)
	{
		buf[0] = (char)0xFF;
		buf[1] = (char)0x55;
		buf[2] = iCmdlen + 1;
		checkBit = buf[2];

		for (i = 1; i < iCmdlen+1; i++)
		{
			buf[i + 2] = buffer[i];
			checkBit += buf[i + 2];
		}
		buf[i + 2] = checkBit;
	}

	SendBuf(buf, i + 3);
}

int YouGuCtl::UnblockSend(const CString &dataStr)
{
	if ((*cuBase)->IsRWable() == false)
		return -1;

	return (*cuBase)->AsyncSend(dataStr);
}

int YouGuCtl::SendBuf(unsigned char *buf, unsigned int len)
{
	if ((*cuBase)->IsRWable() == false)
		return -1;

	return (*cuBase)->AsyncSendBuf(buf, len);
}

void YouGuCtl::AppendLog(CString str)
{
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_UpdateLog);
	pEdit->SetSel(-1, -1);
	pEdit->ReplaceSel(str);
}

void YouGuCtl::OnBnClickedbtnloadfile()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fDlg(
		true, // FALSE为存储文件
		NULL, // 默认扩展名
		NULL, // 默认文件名
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // 隐藏只读复选和开启可覆写功能
		_T("文本文件(*.txt)|*.txt|All Files (*.*)|*.*||"), // 后缀过滤
		NULL);

	CProgressCtrl* pProgress = (CProgressCtrl*)GetDlgItem(IDC_UpdateBar);
	pProgress->SetPos(0);

	if (IDOK == fDlg.DoModal())
	{
		strFilePath = fDlg.GetPathName();
		CString strtmp;
		strtmp += ">> " + fDlg.GetFileName() + " 载入成功\r\n";
		AppendLog(strtmp);
	}
}
