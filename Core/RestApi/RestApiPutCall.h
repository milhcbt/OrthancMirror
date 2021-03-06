/**
 * Orthanc - A Lightweight, RESTful DICOM Store
 * Copyright (C) 2012-2015 Sebastien Jodogne, Medical Physics
 * Department, University Hospital of Liege, Belgium
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * In addition, as a special exception, the copyright holders of this
 * program give permission to link the code of its release with the
 * OpenSSL project's "OpenSSL" library (or with modified versions of it
 * that use the same license as the "OpenSSL" library), and distribute
 * the linked executables. You must obey the GNU General Public License
 * in all respects for all of the code used other than "OpenSSL". If you
 * modify file(s) with this exception, you may extend this exception to
 * your version of the file(s), but you are not obligated to do so. If
 * you do not wish to do so, delete this exception statement from your
 * version. If you delete this exception statement from all source files
 * in the program, then also delete it here.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 **/


#pragma once

#include "RestApiCall.h"

namespace Orthanc
{
  class RestApiPutCall : public RestApiCall
  {
  private:
    const char* bodyData_;
    size_t bodySize_;

  public:
    typedef void (*Handler) (RestApiPutCall& call);
    
    RestApiPutCall(RestApiOutput& output,
                   RestApi& context,
                   RequestOrigin origin,
                   const char* remoteIp,
                   const char* username,
                   const IHttpHandler::Arguments& httpHeaders,
                   const IHttpHandler::Arguments& uriComponents,
                   const UriComponents& trailing,
                   const UriComponents& fullUri,
                   const char* bodyData,
                   size_t bodySize) :
      RestApiCall(output, context, origin, remoteIp, username,
                  httpHeaders, uriComponents, trailing, fullUri),
      bodyData_(bodyData),
      bodySize_(bodySize)
    {
    }

    const char* GetBodyData() const
    {
      return bodyData_;
    }

    size_t GetBodySize() const
    {
      return bodySize_;
    }

    void BodyToString(std::string& result) const
    {
      result.assign(bodyData_, bodySize_);
    }

    virtual bool ParseJsonRequest(Json::Value& result) const
    {
      return ParseJsonRequestInternal(result, bodyData_);
    }      
  };
}
