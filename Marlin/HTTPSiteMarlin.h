/////////////////////////////////////////////////////////////////////////////////
//
// SourceFile: HTTPSiteMarlin.h
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
#include "HTTPSite.h"

class HTTPServerMarlin;

class HTTPSiteMarlin : public HTTPSite
{
public:
  HTTPSiteMarlin(HTTPServerMarlin*  p_server
                ,int                p_port
                ,CString            p_site
                ,CString            p_prefix
                ,HTTPSite*          p_mainSite = nullptr
                ,LPFN_CALLBACK      p_callback = nullptr);

  // MANDATORY: Explicitly starting after configuration of the site
  virtual bool StartSite();

  // OPTIONAL: Set the webroot of the site
  virtual bool SetWebroot(CString p_webroot);

private:
  // Initialize the site from automatic settings in the config
  void         InitSite(WebConfig& p_config);
  void         LogSettings();
  // Set automatic headers upon starting site
  void         SetAutomaticHeaders(WebConfig& p_config);
};