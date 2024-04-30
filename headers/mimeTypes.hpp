#ifndef MIMETYPES_HPP
# define MIMETYPES_HPP

#include <map>
#include <string>

extern std::map<std::string, std::string> mimeTypes;

std::map<std::string, std::string>	getMimeTypes(void);

#endif
