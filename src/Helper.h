#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>

std::string convertToNonAccentVN(std::string str);

// returns a string which convert uppercase letters to lowercase letters
std::string normalize(std::string str);

std::vector<std::string> split(const std::string& str, char delimiter);

#endif // HELPER_H
