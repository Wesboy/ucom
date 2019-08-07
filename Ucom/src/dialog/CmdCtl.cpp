// CmdCtl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Ucom.h"
#include "CmdCtl.h"
#include "afxdialogex.h"

// CmdCtl �Ի���

IMPLEMENT_DYNAMIC(CmdCtl, CDialog)

CmdCtl::CmdCtl(CWnd *pParent /*=NULL*/)
	: CDialog(IDD_CMDCTL, pParent)
{
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

// CmdCtl ��Ϣ�������

BOOL CmdCtl::OnInitDialog()
{
	b_btnRedOpen = FALSE;

	m_redPwm.SetRange(0, 255); //���÷�Χ
	m_redPwm.SetTicFreq(10);   //������ʾ�̶ȵļ��

	m_GreenPwm.SetRange(0, 255); //���÷�Χ
	m_GreenPwm.SetTicFreq(10);   //������ʾ�̶ȵļ��

	m_BluePwm.SetRange(0, 255); //���÷�Χ
	m_BluePwm.SetTicFreq(10);   //������ʾ�̶ȵļ��

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
		ChangeBmpPic(IDC_PicRedState, IDB_SwOn);
		SetDlgItemText(ID_BtnRedOpen, "Close");
	}
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
		ChangeBmpPic(IDC_PicBlueState, IDB_SwOn);
		SetDlgItemText(ID_BtnBlueOpen, "Close");
	}
}

void CmdCtl::OnNMCustomRedPwmDraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nPos = m_redPwm.GetPos();
	CString str;

	str.Format("%d", nPos);
	SetDlgItemText(IDC_ShowRed, str);
}

void CmdCtl::OnNMCustomGreenPwmDraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nPos = m_GreenPwm.GetPos();
	CString str;

	str.Format("%d", nPos);
	SetDlgItemText(IDC_ShowGreen, str);
}

void CmdCtl::OnNMCustomBluePwmDraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	int nPos = m_BluePwm.GetPos();
	CString str;

	str.Format("%d", nPos);
	SetDlgItemText(IDC_ShowBlue, str);
}

void CmdCtl::ChangeBmpPic(int PicCtrlID, unsigned short nPicID)
{
	CBitmap bitmap;
	HBITMAP hBmp;
	CStatic *pStatic = (CStatic *)GetDlgItem(PicCtrlID);

	bitmap.LoadBitmap(nPicID);				// ��λͼIDB_BITMAP1���ص�bitmap
	hBmp = (HBITMAP)bitmap.GetSafeHandle(); // ��ȡbitmap����λͼ�ľ��

	pStatic->SetBitmap(hBmp); // ����ͼƬ�ؼ�
}