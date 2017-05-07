/////////////////////////////////////////////////////////////////////////////////
//
// SourceFile: ServerApp.h
//
// Marlin Server: Internet server/client
// 
// Copyright (c) 2017 ir. W.E. Huisman
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
#include "HTTPServerIIS.h"
#include "IISSiteConfig.h"
#include "ThreadPool.h"
#include "Analysis.h"
#include "ErrorReport.h"

// To prevent bug report from the Windows 8.1 SDK
#pragma warning (disable:4091)
#include <httpserv.h>
#pragma warning (error:4091)

class ServerApp
{
public:
  ServerApp();
  virtual ~ServerApp();

  // Starting and stopping the server
  virtual void InitInstance() = 0;
  virtual void ExitInstance() = 0;
  virtual bool LoadSite(IISSiteConfig& p_config) = 0;

  // Connecting the application to the IIS and Marlin server
  void ConnectServerApp(IHttpServer*   p_iis
                       ,HTTPServerIIS* p_server
                       ,ThreadPool*    p_pool
                       ,LogAnalysis*   p_logfile
                       ,ErrorReport*   p_report);

  // Start our sites from the IIS configuration
  void LoadSites(IHttpApplication* p_app,CString p_physicalPath);

  // Server app was correctly started by MarlinIISModule
  bool CorrectlyStarted();

  // GETTERS

  HTTPServer*    GetHTTPServer() { return m_appServer; };
  ThreadPool*    GetThreadPool() { return m_appPool;   };

protected:
  // Read the site's configuration from the IIS internal structures
  bool  ReadSite   (IAppHostElementCollection* p_sites,CString p_site,int p_num,IISSiteConfig& p_config);
  bool  ReadBinding(IAppHostElementCollection* p_bindings,int p_item,IISBinding& p_binding);

  // General way to read a property
  CString GetProperty(IAppHostElement* p_elem,CString p_property);

  bool           m_correctInit;
  IHttpServer*   m_iis;
  HTTPServerIIS* m_appServer;
  ThreadPool*    m_appPool;
  LogAnalysis*   m_appLogfile;
  ErrorReport*   m_appReport;
};

// Declare your own server app as a derived class!
// This pointer will then point to the one-and-only instance
extern ServerApp* g_server;
