/////////////////////////////////////////////////////////////////////////////////
//
// SourceFile: WebConfigServer.h
//
// Marlin Component: Internet server/client
// 
// Copyright (c) 2015-2018 ir. W.E. Huisman
// All rights reserved
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
#pragma once
#include "SecureClientDlg.h"
#include "ServerHeadersDlg.h"

class WebConfig;

// WebConfigDlg dialog

class WebConfigServer : public CDialog
{
  DECLARE_DYNAMIC(WebConfigServer)

public:
  WebConfigServer(bool p_iis,CWnd* pParent = NULL);   // standard constructor
 ~WebConfigServer();
  BOOL OnInitDialog();
  void SetSiteConfig(CString p_urlPrefix,CString m_fileName);
  void ReadWebConfig(WebConfig& p_config);
  void WriteWebConfig(WebConfig& p_config);

// Dialog Data
  enum { IDD = IDD_WC_SERVER};

protected:
  void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  void InitComboboxes();
  void InitIIS();

  DECLARE_MESSAGE_MAP()

  // Sub dialogs that make use of the members of this dialog
  friend      SecureClientDlg;
  friend      ServerHeadersDlg;

  // Special config to edit
  CString     m_url;
  CString     m_siteConfigFile;

  bool        m_iis;
  // SERVER OVERRIDES
  bool        m_useWebroot;
  bool        m_useBaseURL;
  bool        m_useProtocol;
  bool        m_useBinding;
  bool        m_usePort;
  bool        m_useBacklog;
  bool        m_useTunneling;
  bool        m_useMinThreads;
  bool        m_useMaxThreads;
  bool        m_useStacksize;
  bool        m_useServerUnicode;
  bool        m_useGzip;
  bool        m_useStreamingLimit;
  bool        m_useCompressLimit;
  bool        m_useThrotteling;
  // Server headers
  bool        m_useXFrameOpt;
  bool        m_useXFrameAllow;
  bool        m_useHstsMaxAge;
  bool        m_useHstsDomain;
  bool        m_useNoSniff;
  bool        m_useXssProtect;
  bool        m_useXssBlock;
  bool        m_useNoCache;
  bool        m_useCORS;

  CString     m_webroot;
  CString     m_baseURL;
  bool        m_secureProtocol;
  CString     m_binding;
  int         m_port;
  int         m_backlogQueue;
  bool        m_tunneling;
  int         m_minThreads;
  int         m_maxThreads;
  int         m_stackSize;
  bool        m_serverUnicode;
  bool        m_gzip;
  unsigned    m_streamingLimit;
  unsigned    m_compressLimit;
  bool        m_throtteling;
  // Server headers
  CString     m_xFrameOption;
  CString     m_xFrameAllowed;
  unsigned    m_hstsMaxAge;
  bool        m_hstsSubDomain;
  bool        m_xNoSniff;
  bool        m_XSSProtection;
  bool        m_XSSBlockMode;
  bool        m_noCacheControl;
  bool        m_cors;
  CString     m_allowOrigin;
  CString     m_allowHeaders;
  int         m_allowMaxAge;
  bool        m_corsCredentials;

  // Interface items
  HICON       m_hIcon;
  CComboBox   m_comboProtocol;
  CComboBox   m_comboBinding;
  CComboBox   m_comboStack;
  CComboBox   m_comboUseProxy;
  CButton     m_buttonTunneling;
  CButton     m_buttonServerUnicode;
  CButton     m_buttonGzip;
  CButton     m_buttonThrotteling;

  CButton     m_buttonUseWebroot;
  CButton     m_buttonUseBaseURL;
  CButton     m_buttonUseProtocol;
  CButton     m_buttonUseBinding;
  CButton     m_buttonUsePort;
  CButton     m_buttonUseBacklog;
  CButton     m_buttonUseTunneling;
  CButton     m_buttonUseMinThreads;
  CButton     m_buttonUseMaxThreads;
  CButton     m_buttonUseStacksize;
  CButton     m_buttonUseServerUnicode;
  CButton     m_buttonUseGzip;
  CButton     m_buttonUseStreamingLimit;
  CButton     m_buttonUseCompressLimit;
  CButton     m_buttonUseThrotteling;
  
public:
  afx_msg void OnEnChangeWebroot();
  afx_msg void OnBnClickedButtWebroot();
  afx_msg void OnEnChangeBaseUrl();
  afx_msg void OnCbnSelchangeProtocol();
  afx_msg void OnCbnSelchangeBinding();
  afx_msg void OnEnChangePort();
  afx_msg void OnEnChangeBacklogQueue();
  afx_msg void OnBnClickedTunneling();
  afx_msg void OnEnChangeMinThreads();
  afx_msg void OnEnChangeMaxThreads();
  afx_msg void OnEnChangeStacksize();
  afx_msg void OnCbnSelchangeStacksize();
  afx_msg void OnBnClickedServerUnicode();
  afx_msg void OnBnClickedGzip();
  afx_msg void OnBnClickedHeaders();
  afx_msg void OnEnChangeStreamingLimit();
  afx_msg void OnEnChangeCompressLimit();
  afx_msg void OnBnClickedThrotteling();

  afx_msg void OnBnClickedUseWebroot();
  afx_msg void OnBnClickedUseUrl();
  afx_msg void OnBnClickedUseProtocol();
  afx_msg void OnBnClickedUseBinding();
  afx_msg void OnBnClickedUsePort();
  afx_msg void OnBnClickedUseBacklog();
  afx_msg void OnBnClickedUseTunneling();
  afx_msg void OnBnClickedUseMinThreads();
  afx_msg void OnBnClickedUseMaxThreads();
  afx_msg void OnBnClickedUseStacksize();
  afx_msg void OnBnClickedUseServerUnicode();
  afx_msg void OnBnClickedUseGzip();
  afx_msg void OnBnClickedUseStreamingLimit();
  afx_msg void OnBnClickedUseCompressLimit();
  afx_msg void OnBnClickedUseThrotteling();
};
