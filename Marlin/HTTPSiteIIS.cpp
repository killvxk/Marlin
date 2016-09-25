/////////////////////////////////////////////////////////////////////////////////
//
// SourceFile: HTTPSiteIIS.cpp
//
// Marlin Server: Internet server/client
// 
// Copyright (c) 2016 ir. W.E. Huisman
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
#include "stdafx.h"
#include "HTTPSiteIIS.h"
#include "HTTPServerIIS.h"
#include "HTTPURLGroup.h"
#include "EnsureFile.h"

// Logging via the server
#define DETAILLOG1(text)        m_server->DetailLog (__FUNCTION__,LogType::LOG_INFO,text)
#define DETAILLOGS(text,extra)  m_server->DetailLogS(__FUNCTION__,LogType::LOG_INFO,text,extra)
#define DETAILLOGV(text,...)    m_server->DetailLogV(__FUNCTION__,LogType::LOG_INFO,text,__VA_ARGS__)
#define WARNINGLOG(text,...)    m_server->DetailLogV(__FUNCTION__,LogType::LOG_WARN,text,__VA_ARGS__)
#define ERRORLOG(code,text)     m_server->ErrorLog  (__FUNCTION__,code,text)
#define CRASHLOG(code,text)     if(m_server->GetLogfile())\
                                {\
                                  m_server->GetLogfile()->AnalysisLog(__FUNCTION__,LogType::LOG_ERROR,false,text); \
                                  m_server->GetLogfile()->AnalysisLog(__FUNCTION__,LogType::LOG_ERROR,true,"Error code: %d",code); \
                                }

HTTPSiteIIS::HTTPSiteIIS(HTTPServerIIS* p_server
                        ,int            p_port
                        ,CString        p_site
                        ,CString        p_prefix
                        ,HTTPSite*      p_mainSite /*=nullptr*/
                        ,LPFN_CALLBACK  p_callback /*=nullptr*/)
            :HTTPSite(p_server,p_port,p_site,p_prefix,p_mainSite,p_callback)
{
}

bool
HTTPSiteIIS::StartSite()
{
  DETAILLOGS("Starting website. URL: ",m_site);

//   // Getting the global settings
//   InitSite(m_server->GetWebConfig());
// 
//   // If we have a site web.config file: read it
//   // Overrides the programmatical settings between HTTPServer::CreateSite and HTTPSite::StartSite
//   CString siteConfigFile = WebConfig::GetSiteConfig(m_prefixURL);
//   if(!siteConfigFile.IsEmpty())
//   {
//     WebConfig config(siteConfigFile);
//     if(config.IsFilled())
//     {
//       InitSite(config);
//     }
//   }
// 
//   // Now log the settings, once we read all web.config files
//   LogSettings();

  // See if we have a reliable messaging WITH authentication
  CheckReliable();

  // Checking our webroot
  if(!SetWebroot(m_webroot))
  {
    ERRORLOG(ERROR_INVALID_NAME,"Cannot start site: invalid webroot");
    return false;
  }

  // Call all filters 'OnStartSite' methods
  for(auto& filter : m_filters)
  {
    filter.second->OnStartSite();
  }

  // Call all site handlers 'OnStartSite' methods
  for(auto& handler : m_handlers)
  {
    SiteHandler* shand = handler.second.m_handler;
    while(shand)
    {
      shand->OnStartSite();
      shand = shand->GetNextHandler();
    }
  }

  // Register the site with an URL group for the stand-alone server
  DETAILLOGS("Site started for the IIS server: ",m_site);
  // Return the fact that we started successfully or not
  return (m_isStarted = true);
}

bool
HTTPSiteIIS::SetWebroot(CString p_webroot)
{
  UNREFERENCED_PARAMETER(p_webroot);

  // Getting the IIS server root
  CString root = m_server->GetWebroot();
  root.TrimRight('\\');

  // IIS now expects you to add the site name
  m_webroot = root + GetIISSiteDir();

  // Make sure the directory is there
  EnsureFile ensure(m_webroot);
  int error = ensure.CheckCreateDirectory();
  if(error)
  {
    ERRORLOG(error,"Website's root directory does not exist and cannot create it");
    return false;
  }
  return true;
}

// Getting the sites directory within the IIS rootdir
// /Site/         -> "\\Site\\"
// /Site/Subsite/ -> "\\Site\\Site\\Subsite\\"
CString 
HTTPSiteIIS::GetIISSiteDir()
{
  CString dir(m_site);

  int pos1 = dir.Find('/',1);
  if(pos1 < dir.GetLength() - 1)
  {
    dir = dir.Left(pos1) + dir;
  }
  dir.Replace("/","\\");
  return dir;
}


//////////////////////////////////////////////////////////////////////////
//
// HEADER SECTION DOES NOTHING FOR IIS
// USE THE RESPONSE HEADER REGISTRATION OF IIS !!
//
//////////////////////////////////////////////////////////////////////////

void 
HTTPSiteIIS::SetXFrameOptions(XFrameOption p_option,CString p_uri)
{
  UNREFERENCED_PARAMETER(p_option);
  UNREFERENCED_PARAMETER(p_uri);
}

void
HTTPSiteIIS::SetStrictTransportSecurity(unsigned p_maxAge,bool p_subDomains)
{
  UNREFERENCED_PARAMETER(p_maxAge);
  UNREFERENCED_PARAMETER(p_subDomains);
}

void
HTTPSiteIIS::SetXContentTypeOptions(bool p_nosniff)
{
  UNREFERENCED_PARAMETER(p_nosniff);
}

void
HTTPSiteIIS::SetXSSProtection(bool p_on,bool p_block)
{
  UNREFERENCED_PARAMETER(p_on);
  UNREFERENCED_PARAMETER(p_block);
}

void
HTTPSiteIIS::SetBlockCacheControl(bool p_block)
{
  UNREFERENCED_PARAMETER(p_block);
}

// Add all necessary extra headers to the response
void
HTTPSiteIIS::AddSiteOptionalHeaders(UKHeaders& p_headers)
{
  UNREFERENCED_PARAMETER(p_headers);
}
