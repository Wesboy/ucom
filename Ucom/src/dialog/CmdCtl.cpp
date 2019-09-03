// CmdCtl.cpp : 实现文件
//

#include "stdafx.h"
#include "Ucom.h"
#include "CmdCtl.h"
#include "afxdialogex.h"

// CmdCtl 对话框

IMPLEMENT_DYNAMIC(CmdCtl, CDialog)
//IDD_CMDCTL
CmdCtl::CmdCtl(CWnd *pParent, UcomBase **mbase)
	: CDialog(CmdCtl::IDD, pParent)
{
	cuBase = mbase;
}

CmdCtl::~CmdCtl()
{
}

void CmdCtl::DoDataExchange(CDataExchange *pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SlidRedPwm, m_redPwm);
	DDX_Control(pDX, IDC_SlidGreenPwm, m_GreenPwm);
	DDX_Control(pDX, IDC_SlidBluePwm, m_BluePwm);
}

BEGIN_MESSAGE_MAP(CmdCtl, CDialog)
	ON_BN_CLICKED(ID_BtnRedOpen, &CmdCtl::OnBnClickedBtnRedOpen)
	ON_BN_CLICKED(ID_BtnGreenOpen, &CmdCtl::OnBnClickedBtnGreenOpen)
	ON_BN_CLICKED(ID_BtnBlueOpen, &CmdCtl::OnBnClickedBtnBlueOpen)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SlidRedPwm, &CmdCtl::OnNMCustomRedPwmDraw)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SlidGreenPwm, &CmdCtl::OnNMCustomGreenPwmDraw)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SlidBluePwm, &CmdCtl::OnNMCustomBluePwmDraw)
END_MESSAGE_MAP()

// CmdCtl 消息处理程序

BOOL CmdCtl::OnInitDialog()
{
	b_btnRedOpen = FALSE;

	m_redPwm.SetRange(0, 255); //设置范围
	m_redPwm.SetTicFreq(10);   //设置显示刻度的间隔

	m_GreenPwm.SetRange(0, 255); //设置范围
	m_GreenPwm.SetTicFreq(10);   //设置显示刻度的间隔

	m_BluePwm.SetRange(0, 255); //设置范围
	m_BluePwm.SetTicFreq(10);   //设置显示刻度的间隔

	UpdateData(TRUE);

	return TRUE;
}

void CmdCtl::OnBnClickedBtnRedOpen()
{
	if (b_btnRedOpen)
	{
		b_btnRedOpen = FALSE;

		ChangeBmpPic(IDC_PicRedState, IDB_SwOff);
		SetDlgItemText(ID_BtnRedOpen, "Open");
	}
	else
	{
		b_btnRedOpen = TRUE;
		ChangeBmpPic(IDC_PicRedState, IDB_SwRedOn);
		SetDlgItemText(ID_BtnRedOpen, "Close");
	}
	SetLedOn(I_RED, b_btnRedOpen);
}

void CmdCtl::OnBnClickedBtnGreenOpen()
{
	if (b_btnGreenOpen)
	{
		b_btnGreenOpen = FALSE;
		ChangeBmpPic(IDC_PicGreenState, IDB_SwOff);
		SetDlgItemText(ID_BtnGreenOpen, "Open");
	}
	else
	{
		b_btnGreenOpen = TRUE;
		ChangeBmpPic(IDC_PicGreenState, IDB_SwOn);
		SetDlgItemText(ID_BtnGreenOpen, "Close");
	}
	SetLedOn(I_GREEN, b_btnGreenOpen);
}

void CmdCtl::OnBnClickedBtnBlueOpen()
{
	if (b_btnBlueOpen)
	{
		b_btnBlueOpen = FALSE;
		ChangeBmpPic(IDC_PicBlueState, IDB_SwOff);
		SetDlgItemText(ID_BtnBlueOpen, "Open");
	}
	else
	{
		b_btnBlueOpen = TRUE;
		ChangeBmpPic(IDC_PicBlueState, IDB_SwBlueOn);
		SetDlgItemText(ID_BtnBlueOpen, "Close");
	}
	SetLedOn(I_BLUE, b_btnBlueOpen);
}

void CmdCtl::OnNMCustomRedPwmDraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nPos = m_redPwm.GetPos();
	nPos = (nPos * 1024) / 100;
	CString str;

	str.Format("%d", nPos);
	SetLedPWM(I_RED, nPos);
	SetDlgItemText(IDC_ShowRed, str);
}

void CmdCtl::OnNMCustomGreenPwmDraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nPos = m_GreenPwm.GetPos();
	nPos = (nPos * 1024) / 100;
	CString str;

	str.Format("%d", nPos);
	SetLedPWM(I_GREEN, nPos);
	SetDlgItemText(IDC_ShowGreen, str);
}

void CmdCtl::OnNMCustomBluePwmDraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nPos = m_BluePwm.GetPos();
	nPos = (nPos * 1024) / 100;
	CString str;

	str.Format("%d", nPos);
	SetLedPWM(I_BLUE, nPos);
	SetDlgItemText(IDC_ShowBlue, str);
}

void CmdCtl::ChangeBmpPic(int PicCtrlID, unsigned short nPicID)
{
	CBitmap bitmap;
	HBITMAP hBmp;
	CStatic *pStatic = (CStatic *)GetDlgItem(PicCtrlID);

	bitmap.LoadBitmap(nPicID);				// 将位图IDB_BITMAP1加载到bitmap
	hBmp = (HBITMAP)bitmap.GetSafeHandle(); // 获取bitmap加载位图的句柄

	pStatic->SetBitmap(hBmp); // 设置图片控件
}

void CmdCtl::SetLedOn(unsigned short iColor, bool bOn)
{
	unsigned char buf[8] = {0};

	switch (iColor)
	{
	case I_RED:
		buf[1] = (unsigned char)0xB1;
		break;
	case I_GREEN:
		buf[1] = (unsigned char)0xB2;
		break;
	case I_BLUE:
		buf[1] = (unsigned char)0xB3;
		break;
	default:
		return;
	}

	if (bOn)
		buf[2] = 0x01;

	buf[0] = 3; //cmdlen
	SendCmdToDevice(buf);
}

void CmdCtl::SetLedPWM(unsigned short iColor, unsigned int iPwmVal)
{
	unsigned char buf[8] = {0};

	switch (iColor)
	{
	case I_RED:
		buf[1] = (unsigned char)0xB4;
		break;
	case I_GREEN:
		buf[1] = (unsigned char)0xB5;
		break;
	case I_BLUE:
		buf[1] = (unsigned char)0xB6;
		break;
	default:
		return;
	}
	buf[2] = iPwmVal&0xFF;
	buf[3] = iPwmVal >> 8;
	buf[0] = 4; //cmdlen
	SendCmdToDevice(buf);
}

void CmdCtl::SendCmdToDevice(unsigned char *buffer)
{
	CString strTmp;
	unsigned char buf[16] = {0};
	char iCmdlen = buffer[0];
	unsigned char checkBit = 0;
	unsigned char i;

	if(iCmdlen > 0 && iCmdlen < 14)
	{
		buf[0] = (char)0x55;
		buf[1] = (char)0xaa;
		//checkBit = buf[0] + buf[1];

		for(i = 0; i < iCmdlen; i++)
		{
			buf[i+2] = buffer[i];
			checkBit += buf[i+2];
		}
		buf[i+2] = checkBit;
	}

	SendBuf(buf, i+3);
}

int CmdCtl::UnblockSend(const CString &dataStr)
{
	if ((*cuBase)->IsRWable() == false)
		return -1;

	return (*cuBase)->AsyncSend(dataStr);
}

int CmdCtl::SendBuf(unsigned char *buf, unsigned int len)
{
	if ((*cuBase)->IsRWable() == false)
		return -1;

	return (*cuBase)->AsyncSendBuf(buf, len);
}
