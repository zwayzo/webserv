#include "../headers/mimeTypes.hpp"

std::map<std::string, std::string>	getMimeTypes(void) {
	std::map<std::string, std::string> mimeTypes;

    // Ajout des types MIME courants

	mimeTypes[".aac"] = "audio/aac";
    mimeTypes[".abw"] = "application/x-abiword";
    mimeTypes[".arc"] = "text/html";
    mimeTypes[""] = "application/octet-stream";
    mimeTypes[""] = "text/javascript";
    mimeTypes[""] = "application/json";
    mimeTypes[""] = "application/xml";
    mimeTypes[""] = "application/zip";
    mimeTypes[""] = "application/pdf";
    mimeTypes[""] = "application/msword";
    mimeTypes["x"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    mimeTypes[""] = "application/vnd.ms-excel";
    mimeTypes["x"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    mimeTypes[""] = "application/vnd.ms-powerpoint";
    mimeTypes["x"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
    mimeTypes[""] = "image/gif";
    mimeTypes[""] = "image/jpeg";
    mimeTypes[""] = "image/jpeg";
    mimeTypes[""] = "image/png";
    mimeTypes[""] = "image/svg+xml";
    mimeTypes[""] = "image/x-icon";

    mimeTypes[".css"] = "text/css";
//
    mimeTypes[".doc"] = "application/msword";
    mimeTypes[".docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
//
    mimeTypes[".gif"] = "image/gif";
//
	mimeTypes[".htm"] = "text/html";
	mimeTypes[".html"] = "text/html";
//
    mimeTypes[".ico"] = "image/x-icon";
//
    mimeTypes[".jpeg"] = "image/jpeg";
    mimeTypes[".jpg"] = "image/jpeg";
	mimeTypes[".js"] = "text/javascript";
    mimeTypes[".json"] = "application/json";
//
    mimeTypes[".pdf"] = "application/pdf";
    mimeTypes[".png"] = "image/png";
    mimeTypes[".ppt"] = "application/vnd.ms-powerpoint";
    mimeTypes[".pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
//
    mimeTypes[".svg"] = "image/svg+xml";
//
    mimeTypes[".txt"] = "text/plain";
//
    mimeTypes[".xls"] = "application/vnd.ms-excel";
    mimeTypes[".xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
	mimeTypes[".xml"] = "application/xml";
//
    mimeTypes[".zip"] = "application/zip";

    // Autre types
    mimeTypes[".txt"] = "text/plain";
    mimeTypes[".html"] = "text/html";
    mimeTypes[".htm"] = "text/html";
    mimeTypes[".css"] = "text/css";
    mimeTypes[".js"] = "text/javascript";
    mimeTypes[".json"] = "application/json";
    mimeTypes[".xml"] = "application/xml";
    mimeTypes[".zip"] = "application/zip";
    mimeTypes[".pdf"] = "application/pdf";
    mimeTypes[".doc"] = "application/msword";
    mimeTypes[".docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    mimeTypes[".xls"] = "application/vnd.ms-excel";
    mimeTypes[".xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    mimeTypes[".ppt"] = "application/vnd.ms-powerpoint";
    mimeTypes[".pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
    mimeTypes[".gif"] = "image/gif";
    mimeTypes[".jpg"] = "image/jpeg";
    mimeTypes[".jpeg"] = "image/jpeg";
    mimeTypes[".png"] = "image/png";
    mimeTypes[".svg"] = "image/svg+xml";
    mimeTypes[".ico"] = "image/x-icon";
}
