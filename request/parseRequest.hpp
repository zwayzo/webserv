#ifndef PARSEREQUEST_HPP
#define PARSEREQUEST_HPP

#include <string>
#include <map>

class HttpRequest {
public:
    enum RequestStatus {
        ParsingHeaders,
    };

    enum ContentDisposition {
        NoContent
    };

private:
    std::string Http;
    std::string protocol;
    std::string path;
    std::map<std::string, std::string> headerFields;
    std::string bodyPath;
    std::string queryString;
    RequestStatus status;
    ContentDisposition contentMode;
    std::string buffer;
    size_t contentLength;

public:
    HttpRequest();
    HttpRequest(const HttpRequest&);
    HttpRequest& operator=(const HttpRequest&);
    ~HttpRequest();

    // Getters
    std::string getHttp() const;
    std::string getProtocol() const;
    std::string getPath() const;
    std::map<std::string, std::string> getHeaderFields() const;
    std::string getBodyPath() const;
    std::string getQueryString() const;
    RequestStatus getStatus() const;
    ContentDisposition getContentMode() const;
    std::string getBuffer() const;
    size_t getContentLength() const;

    // Setters
    void setHttp(const std::string& val);
    void setProtocol(const std::string& val);
    void setPath(const std::string& val);
    void setHeaderFields(const std::map<std::string, std::string>& val);
    void setBodyPath(const std::string& val);
    void setQueryString(const std::string& val);
    void setStatus(RequestStatus val);
    void setContentMode(ContentDisposition val);
    void setBuffer(const std::string& val);
    void setContentLength(size_t val);

    // Other 
    static std::string toLower(const std::string& str);
    bool is_body(int& contentLength, bool& isChunked) const;
    void parseHeaders(const std::string& headersPart);
    void printHeaders() const;
    void request(const std::string& requestLine);
    void parseRequestLine(const std::string& requestLine);
    void parseHttpRequest(const char* buf, int nbytes);
    bool isSupportedMethod(const std::string& method) const;
    bool needBodyFile() const;
    static std::string generateTempFileName();
    void handleChunkedBody(std::istringstream& stream, std::string& body);
};

#endif