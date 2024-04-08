#include "../headers/mimeTypes.hpp"

std::map<std::string, std::string>	getMimeTypes(void) {
	std::map<std::string, std::string> mimeTypes;

    // Ajout des types MIME courants

	mimeTypes[".aac"] = "audio/aac";
    mimeTypes[".abw"] = "application/x-abiword";
    mimeTypes[".arc"] = "application/octet-stream";
    mimeTypes[".avi"] = "video/x-msvideo";
    mimeTypes[".azw"] = "application/vnd.amazon.ebook";
    mimeTypes[".bin"] = "application/octet-stream";
    mimeTypes[".bmp	"] = "image/bmp";
    mimeTypes[".bz"] = "application/x-bzip";
    mimeTypes[".csh"] = "application/x-csh";
    mimeTypes[".css"] = "text/css";
    mimeTypes[".csv	"] = "text/csv";
    mimeTypes[".doc"] = "application/msword";
    mimeTypes[".docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    mimeTypes[".eot"] = "application/vnd.ms-fontobject";
    mimeTypes[".epub"] = "application/epub+zip";
    mimeTypes[".gif"] = "image/gif";
	mimeTypes[".htm"] = "text/html";
	mimeTypes[".html"] = "text/html";
    mimeTypes[".ico"] = "image/x-icon";
    mimeTypes[".ics"] = "text/calendar";
    mimeTypes[".jar"] = "application/java-archive";
    mimeTypes[".jpeg"] = "image/jpeg";
    mimeTypes[".jpg"] = "image/jpeg";
	mimeTypes[".js"] = "text/javascript";
    mimeTypes[".json"] = "application/json";
    mimeTypes[".mid"] = "audio/midi";
    mimeTypes[".midi"] = "audio/midi";
    mimeTypes[".mpeg"] = "video/mpeg";
    mimeTypes[".mpkg"] = "application/vnd.apple.installer+xml";
    mimeTypes[".odp"] = "application/vnd.oasis.opendocument.presentation";
    mimeTypes[".ods"] = "application/vnd.oasis.opendocument.spreadsheet";
    mimeTypes[".odt"] = "application/vnd.oasis.opendocument.text";
    mimeTypes[".oga"] = "audio/ogg";
    mimeTypes[".ogv"] = "video/ogg";
    mimeTypes[".ogx"] = "application/ogg";
	mimeTypes[".otf"] = "font/otf";
	mimeTypes[".otf"] = "font/otf";
    mimeTypes[".pdf"] = "application/pdf";
    mimeTypes[".png"] = "image/png";
    mimeTypes[".ppt"] = "application/vnd.ms-powerpoint";
    mimeTypes[".pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
	mimeTypes[".rar"] = "application/x-rar-compressed";
	mimeTypes[".rtf"] = "application/rtf";
	mimeTypes[".sh"] = "application/x-sh";
    mimeTypes[".svg"] = "image/svg+xml";
	mimeTypes[".swf"] = "application/x-shockwave-flash";
	mimeTypes[".tar"] = "application/x-tar";
	mimeTypes[".ts"] = "application/typescript";
    mimeTypes[".txt"] = "text/plain";
    mimeTypes[".vsd"] = "application/vnd.visio";
    mimeTypes[".weba"] = "audio/webm";
    mimeTypes[".webm"] = "video/webm";
    mimeTypes[".webp"] = "image/webp";
    mimeTypes[".woff"] = "font/woff";
    mimeTypes[".xhtml"] = "application/xhtml+xml";
    mimeTypes[".xls"] = "application/vnd.ms-excel";
    mimeTypes[".xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
	mimeTypes[".xml"] = "application/xml";
    mimeTypes[".xul"] = "application/vnd.mozilla.xul+xml";
    mimeTypes[".zip"] = "application/zip";
    mimeTypes[".7z"] = "application/x-7z-compressed";

	return mimeTypes;
}
