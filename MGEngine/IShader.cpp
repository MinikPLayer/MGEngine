#include "IShader.hpp"
#include "File.hpp"
#include "Engine.hpp"

std::shared_ptr<IShader> IShader::create_default() {
    return Engine::get_renderer().lock()->_create_default_shader_();
}

std::shared_ptr<IShader> IShader::create(std::string vertexPath, std::string fragmentPath) {
    auto newShader = Engine::get_renderer().lock()->_create_shader_(vertexPath, fragmentPath);

    return newShader;
}

bool IShader::load(std::string vertexPath, std::string fragmentPath) {
    auto vSource = File::LoadAllText(vertexPath);
    auto fSource = File::LoadAllText(fragmentPath);

    good = _init_(vSource, fSource);
    return good;
}
