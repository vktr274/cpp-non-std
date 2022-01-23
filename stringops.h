#pragma once

#include <string>
#include <vector>
#include <algorithm>

/*
* Custom non-standard namespace for functions
* not included in the standard namespace.
*/
namespace nonstd {
    /*
    * Function that gets rid of unnecesarry whitespaces in a string.
    * Returns: string cleared of unnecessary whitespaces.
    */
    std::string clear_whitespace(const std::string&);

    /*
    * Python-esque split function that can split a string by a delimiter.
    * Returns: vector of strings.
    */
    std::vector<std::string> split(const std::string&, const std::string&);

    /*
    * Function that replaces all occurences of a substring in a strng by another string.
    * Returns: new string with replaced substrings.
    */
    std::string replace_substr_all(const std::string&, const std::string&, const std::string&);

    std::string replace_substr_all(const std::string& string, const std::string& what, const std::string& by) {
        std::string stringCopy(string);
        size_t start_pos = 0;

        while ((start_pos = stringCopy.find(what, start_pos)) != std::string::npos) {
            stringCopy.replace(start_pos, what.length(), by);
            start_pos += by.length();
        }

        return stringCopy;
    }

    std::string clear_whitespace(const std::string& string) {
        std::string cleanString(string);
        cleanString.erase(
            std::unique(
                cleanString.begin(),
                cleanString.end(),
                [](char a, char b) {
                    return std::isspace(a) && std::isspace(b);
                }
            ),
            cleanString.end()
                    );

        if (cleanString.size() && std::isspace(cleanString.front())) {
            cleanString.erase(0, 1);
        }

        if (cleanString.size() && std::isspace(cleanString.back())) {
            cleanString.pop_back();
        }

        return cleanString;
    }

    std::vector<std::string> split(const std::string& string, const std::string& delimiter) {
        size_t position = 0;
        std::string tempString(string);
        std::vector<std::string> stringParts;

        while ((position = tempString.find(delimiter)) != std::string::npos) {
            stringParts.push_back(tempString.substr(0, position));
            tempString.erase(0, position + delimiter.length());
        }
        stringParts.push_back(tempString);
        return stringParts;
    }
}