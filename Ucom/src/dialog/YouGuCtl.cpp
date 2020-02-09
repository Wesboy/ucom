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


void YouGuCtl::OnBnClickedUpdate()
{
	// TODO: 在此添加控件通知处理程序代码
	if (b_btnUpdate)
	{
		b_btnUpdate = FALSE;
	}
	else
	{
		b_btnUpdate = TRUE;
		SendEarphoneCtl();
	}
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

		for (i = 1; i < iCmdlen; i++)
		{
			buf[i + 3] = buffer[i];
			checkBit += buf[i + 3];
		}
		buf[i + 3] = checkBit;
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