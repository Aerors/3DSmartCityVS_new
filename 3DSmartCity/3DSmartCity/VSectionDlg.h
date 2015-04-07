#include "resource.h"

#include "ChartCtrl/ChartCtrl.h"
#include "ChartCtrl/ChartAxis.h"
#include "ChartCtrl/ChartLabel.h"
#include "ChartCtrl/ChartAxisLabel.h"
#include "ChartCtrl/ChartPointsSerie.h"
#include "ChartCtrl/ChartLineSerie.h"


#include<string>
#include <sstream>
#include "ChartCtrl\ChartCtrl.h"

#if defined _UNICODE ||defined UNICODE
typedef std::wstring TChartString;
typedef std::wstringstream TChartStringStream;
#else
typedef std::string TChartString;
typedef std::stringstream TChartStringStream;
#endif

#pragma once


// VSectionDlg 对话框

class VSectionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(VSectionDlg)

public:
	VSectionDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~VSectionDlg();

// 对话框数据
	enum { IDD = IDD_VSECTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	CChartCtrl m_ChartCtrl;
	virtual BOOL OnInitDialog();
};
