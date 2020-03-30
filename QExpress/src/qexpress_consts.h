/*
 Copyright 2020 Mauro Marssola
 Distributed under MIT license, or public domain if desired and
 recognized in your jurisdiction.
 See file LICENSE for detail.
*/

/*
 * Based on CPPWebFramework
 * https://github.com/HerikLyma/CPPWebFramework/blob/master/CPPWebFramework/cwf/constants.h
 */

#ifndef QEXPRESS_CONSTS_H
#define QEXPRESS_CONSTS_H

#include <QString>
#include <QByteArray>
#include "qexpress_global.h"

QEX_BEGIN_NAMESPACE


//XML CONSTANTS
namespace XML
{
    const QByteArray HEADER = "<?xml version=\"1.0\" encoding=\"iso-8859-1\" ?>\n";
}

//GETTER AND SETTER CONSTANTS
namespace GET_SET
{
    const QString GET_LOWER = "get";
    const QString SET_LOWER = "set";
    const QString GET_UPPER = "GET";
    const QString SET_UPPER = "SET";
}


//CONTENT TYPE CONSTANTS
namespace HTTP
{
    const QByteArray SERVER                           = "QExpress";
    const QByteArray VERSION                          = "1.0";
    const QByteArray SERVER_VERSION                   = "QExpress/1.0";
    const QByteArray DATA                             = "Data";
    const QByteArray DATE                             = "Date";
    const QByteArray TRANSFER_ENCODING                = "Transfer-Encoding";
    const QByteArray CHUNKED                          = "chunked";
    const QByteArray END_LINE                         = "\r\n";
    const QByteArray SEPARATOR                        = ": ";
    const QByteArray HTTP_1_1                         = "HTTP/1.1 ";
    const QByteArray END_OF_MESSAGE                   = "\r\n\r\n";
    const QByteArray END_OF_MESSAGE_WITH_ZERO         = "0\r\n\r\n";
    const QByteArray CONTENT_TYPE                     = "Content-Type";
    const QByteArray CONTENT_TYPE_COLON_SPACE         = "Content-Type: ";
    const QByteArray CONTENT_LENGTH                   = "Content-Length";
    const QByteArray CONTENT_ENCODING                 = "Content-Encoding";
    const QByteArray CONTENT_DISPOSITION              = "Content-Disposition";
    const QByteArray CONTENT_DISPOSITION_COLON        = "Content-Disposition:";
    const QByteArray CONTENT_DISPOSITION_COLON_SPACE  = "Content-Disposition: ";
    const QByteArray MULTIPART                        = "multipart";
    const QByteArray BOUNDARY                         = "boundary";
    const QByteArray URLENCODED                       = "urlencoded";
    const QByteArray COOKIE                           = "Cookie";
    const QByteArray SET_COOKIE                       = "Set-Cookie: ";
    const QByteArray SESSION_ID                       = "sessionId";
    const QByteArray FILENAME                         = "filename";
    const QByteArray FILENAME_EQUAL                   = "filename=";
    const QByteArray FORM_DATA_COLON_SPACE            = "form-data; ";
    const QByteArray FORM_DATA_NAME_EQUAL             = "name=";
    const QByteArray FORM_DATA_SEPARATOR              = "\r\n\r\n";
    const QByteArray WEBKIT                           = "WebKit";
    const QByteArray LOCATION                         = "Location";
    const QByteArray REDIRECT                         = "Redirect";
    const QByteArray SEE_OTHER                        = "See Other";
    const QByteArray ACCEPT_ENCODING                  = "Accept-Encoding";
    const QByteArray ACCEPT_LANGUAGE                  = "Accept-Language";
    const QByteArray HOST                             = "Host";
    const QByteArray USER_AGENT                       = "User-Agent";
    const QByteArray OK                               = "OK";
    /*
    const QByteArray            = "";
    const QByteArray            = "";
    */

    //IMAGE
    const QByteArray IMAGE_MICROSOFT_ICO    = "image/vnd.microsoft.icon";
    const QByteArray IMAGE_JPEG             = "image/jpeg";
    const QByteArray IMAGE_TIFF             = "image/tiff";
    const QByteArray IMAGE_SVG_XML          = "image/svg+xml";

    //AUDIO
    const QByteArray AUDIO_MP3              = "image/mpeg";
    const QByteArray AUDIO_MP4              = "image/mp4";
    const QByteArray APPLICATION_PHOTOSHOP  = "image/vnd.adobe.photoshop";

    //VIDEO
    const QByteArray VIDEO_FLV              = "video/x-flv";

    //APPLICATION
    const QByteArray APPLICATION_MSWORD                      = "application/msword";
    const QByteArray APPLICATION_RTF                         = "application/rtf";
    const QByteArray APPLICATION_EXCEL                       = "application/vnd.ms-excel";
    const QByteArray APPLICATION_JSON                        = "application/json";
    const QByteArray APPLICATION_POWER_POINT                 = "application/vnd.ms-powerpoint";
    const QByteArray APPLICATION_JAVASCRIPT                  = "application/javascript";
    const QByteArray APPLICATION_OPEN_DOCUMENT_TEXT          = "application/vnd.oasis.opendocument.text";
    const QByteArray APPLICATION_OPEN_DOCUMENT_SPREADSHEET   = "application/vnd.oasis.opendocument.spreadsheet";
    const QByteArray APPLICATION_SHOCKWAVE_FLASH             = "application/x-shockwave-flash";
    const QByteArray APPLICATION_RAR_COMPRESSED              = "application/x-rar-compressed";
    const QByteArray APPLICATION_MS_DOWNLOAD                 = "application/x-msdownload";
    const QByteArray APPLICATION_CAB_COMPRESSED              = "application/vnd.ms-cab-compressed";
    const QByteArray APPLICATION_POSTSCRIPT                  = "application/postscript";
    const QByteArray APPLICATION_WWW_FORM_URLENCODED         = "application/x-www-form-urlencoded";
    const QByteArray APPLICATION_FONT_WOFF                   = "application/x-font-woff";
    const QByteArray APPLICATION_FONT_TTF                    = "application/octet-stream";

    //HTTP METHODS CONSTANTS
    namespace METHOD
    {
        const QByteArray GET     = "GET";
        const QByteArray PUT     = "PUT";
        const QByteArray POST    = "POST";
        const QByteArray PATCH   = "PATCH";
        const QByteArray DELETE  = "DELETE";
        const QByteArray OPTIONS = "OPTIONS";
        const QByteArray HEAD    = "HEAD";
        const QByteArray TRACE   = "TRACE";
    }

//    namespace CONTENT_TYPE
//    {
//        const QByteArray TEXT_HTML_UTF8 = "text/html; charset=UTF-8";
//    };

    namespace RESPONSE
    {
        namespace CONTENT_TYPE
        {
            const QByteArray TEXT_HTML_UTF8             = "text/html; charset=UTF-8";
            const QByteArray TEXT_PLAIN_UTF8            = "text/plain; charset=UTF-8";
            const QByteArray APPLICATION_JSON_UTF8      = "application/json; charset=UTF-8";
        }
    }

    struct STATUS
    {
        enum CODE: int {
            // 1xx: Informational
            Continue = 100,
            SwitchingProtocols,
            Processing,
            // 2xx: Success
            Ok = 200,
            Created,
            Accepted,
            NonAuthoritativeInformation,
            NoContent,
            ResetContent,
            PartialContent,
            MultiStatus,
            AlreadyReported,
            IMUsed = 226,
            // 3xx: Redirection
            MultipleChoices = 300,
            MovedPermanently,
            Found,
            SeeOther,
            NotModified,
            UseProxy,
            // 306: not used, was proposed as "Switch Proxy" but never standardized
            TemporaryRedirect = 307,
            PermanentRedirect,
            // 4xx: Client Error
            BadRequest = 400,
            Unauthorized,
            PaymentRequired,
            Forbidden,
            NotFound,
            MethodNotAllowed,
            NotAcceptable,
            ProxyAuthenticationRequired,
            RequestTimeout,
            Conflict,
            Gone,
            LengthRequired,
            PreconditionFailed,
            PayloadTooLarge,
            UriTooLong,
            UnsupportedMediaType,
            RequestRangeNotSatisfiable,
            ExpectationFailed,
            ImATeapot,
            MisdirectedRequest = 421,
            UnprocessableEntity,
            Locked,
            FailedDependency,
            UpgradeRequired = 426,
            PreconditionRequired = 428,
            TooManyRequests,
            RequestHeaderFieldsTooLarge = 431,
            UnavailableForLegalReasons = 451,
            // 5xx: Server Error
            InternalServerError = 500,
            NotImplemented,
            BadGateway,
            ServiceUnavailable,
            GatewayTimeout,
            HttpVersionNotSupported,
            VariantAlsoNegotiates,
            InsufficientStorage,
            LoopDetected,
            NotExtended = 510,
            NetworkAuthenticationRequired,
            NetworkConnectTimeoutError = 599,
        };

        template<typename T>
        static QByteArray TEXT(T code) {
            switch (code) {
            case CODE::Continue: return "Continue";
            case CODE::SwitchingProtocols: return "Switching Protocols";
            case CODE::Processing: return "Processing";
            //2xx: Succes
            case CODE::Ok: return "Ok";
            case CODE::Created: return "Created";
            case CODE::Accepted: return "Accepted";
            case CODE::NonAuthoritativeInformation: return "Non-Authoritative Information";
            case CODE::NoContent: return "No Content";
            case CODE::ResetContent: return "Reset Content";
            case CODE::PartialContent: return "Partial Content";
            case CODE::MultiStatus: return "Multi Status";
            case CODE::AlreadyReported: return "Already Reported";
            case CODE::IMUsed: return "IM Used";
            // 3xx: Redirectio
            case CODE::MultipleChoices: return "Multiple Choices";
            case CODE::MovedPermanently: return "Moved Permanently";
            case CODE::Found: return "Found";
            case CODE::SeeOther: return "See Other";
            case CODE::NotModified: return "Not Modified";
            case CODE::UseProxy: return "Use Proxy";
            // 306: not used, was proposed as "Switch Pr
            case CODE::TemporaryRedirect: return "Temporary Redirect";
            case CODE::PermanentRedirect: return "Permanent Redirect";
            // 4xx: Client Erro
            case CODE::BadRequest: return "Bad Request";
            case CODE::Unauthorized: return "Unauthorized";
            case CODE::PaymentRequired: return "Payment Required";
            case CODE::Forbidden: return "Forbidden";
            case CODE::NotFound: return "Not Found";
            case CODE::MethodNotAllowed: return "Method Not Allowed";
            case CODE::NotAcceptable: return "Not Acceptable";
            case CODE::ProxyAuthenticationRequired: return "Proxy Authentication Required";
            case CODE::RequestTimeout: return "Request Timeout";
            case CODE::Conflict: return "Conflict";
            case CODE::Gone: return "Gone";
            case CODE::LengthRequired: return "Length Required";
            case CODE::PreconditionFailed: return "Precondition Failed";
            case CODE::PayloadTooLarge: return "Payload Too Large";
            case CODE::UriTooLong: return "Uri Too Long";
            case CODE::UnsupportedMediaType: return "Unsupported Media Type";
            case CODE::RequestRangeNotSatisfiable: return "Request Range Not Satisfiable";
            case CODE::ExpectationFailed: return "Expectation Failed";
            case CODE::ImATeapot: return "ImA Teapot";
            case CODE::MisdirectedRequest: return "Misdirected Request";
            case CODE::UnprocessableEntity: return "Unprocessable Entity";
            case CODE::Locked: return "Locked";
            case CODE::FailedDependency: return "Failed Dependency";
            case CODE::UpgradeRequired: return "Upgrade Required";
            case CODE::PreconditionRequired: return "Precondition Required";
            case CODE::TooManyRequests: return "Too Many Requests";
            case CODE::RequestHeaderFieldsTooLarge: return "Request Header Fields Too Large";
            case CODE::UnavailableForLegalReasons: return "Unavailable For Legal Reasons";
            // 5xx: Server Erro
            case CODE::InternalServerError: return "Internal Server Error";
            case CODE::NotImplemented: return "Not Implemented";
            case CODE::BadGateway: return "Bad Gateway";
            case CODE::ServiceUnavailable: return "Service Unavailable";
            case CODE::GatewayTimeout: return "Gateway Timeout";
            case CODE::HttpVersionNotSupported: return "Http Version Not Supported";
            case CODE::VariantAlsoNegotiates: return "Variant Also Negotiates";
            case CODE::InsufficientStorage: return "Insufficient Storage";
            case CODE::LoopDetected: return "Loop Detected";
            case CODE::NotExtended: return "Not Extended";
            case CODE::NetworkAuthenticationRequired: return "Network Authentication Required";
            case CODE::NetworkConnectTimeoutError: return "Network Connect Timeout Error";
            }
            return "";
        }
    };
}

namespace COOKIE
{
    const QByteArray COMMENT        = "Comment";
    const QByteArray DOMAIN_COOKIE  = "Domain";
    const QByteArray MAX_AGE        = "Max-Age";
    const QByteArray PATH           = "Path";
    const QByteArray SECURE         = "Secure";
    const QByteArray VERSION        = "Version";
}

//FILE EXTENTIONS CONSTANTS
namespace FILE_EXTENTION
{
    const QByteArray BAR  = "/";
    const QByteArray HTML = "html";
    const QByteArray HTM  = "htm";
    const QByteArray CSS  = "css";
    const QByteArray TXT  = "txt";
    const QByteArray PHP  = "php";
    const QByteArray ICO  = "ico";
    const QByteArray PNG  = "png";
    const QByteArray GIF  = "gif";
    const QByteArray BMP  = "bmp";
    const QByteArray JPE  = "jpe";
    const QByteArray JPG  = "jpg";
    const QByteArray TIF  = "TIF";
    const QByteArray TIFF = "TIFF";
    const QByteArray SVG  = "svg";
    const QByteArray SVGZ = "svgz";
    const QByteArray PDF  = "pdf";
    const QByteArray XML  = "xml";
    const QByteArray JSON = "json";
    const QByteArray ZIP  = "zip";
    const QByteArray MP3  = "mp3";
    const QByteArray MP4  = "mp4";
    const QByteArray FLV  = "flv";
    const QByteArray DOC  = "doc";
    const QByteArray RTF  = "rtf";
    const QByteArray XLS  = "xls";
    const QByteArray PPT  = "ppt";
    const QByteArray JS   = "js";
    const QByteArray ODT  = "odt";
    const QByteArray ODS  = "ods";
    const QByteArray SWF  = "swf";
    const QByteArray RAR  = "rar";
    const QByteArray EXE  = "exe";
    const QByteArray MSI  = "msi";
    const QByteArray CAB  = "cab";
    const QByteArray PSD  = "psd";
    const QByteArray AI   = "ai";
    const QByteArray EPS  = "eps";
    const QByteArray PS   = "ps";
    const QByteArray INI  = "ini";
    const QByteArray EOT  = "eot";
    const QByteArray TTF  = "ttf";
    const QByteArray WOFF = "woff";
    const QByteArray WOFF2= "woff2";
}

QEX_END_NAMESPACE

#endif // QEXPRESS_CONSTS_H
