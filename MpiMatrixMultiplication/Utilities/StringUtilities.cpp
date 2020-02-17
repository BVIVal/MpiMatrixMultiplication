#include"StringUtilities.h"

string ReplaceString(const string& subject, string const& search, string const& replace)
{
	auto result = subject;
	size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos) {
		result.replace(pos, search.length(), replace);
		pos += replace.length();
	}
	return result;
}

string ToRawStringPath(const string& text)
{
	return ReplaceString(text, string(1, '\t'), "\\t");
}
