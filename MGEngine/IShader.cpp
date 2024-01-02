#include "IShader.hpp"
#include "File.hpp"

bool IShader::load(std::string vertexPath, std::string fragmentPath) {
    auto vSource = File::LoadAllText(vertexPath);
    auto fSource = File::LoadAllText(fragmentPath);

    good = _init_(vSource, fSource);
    return good;
}
