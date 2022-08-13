#pragma once
#include <string_view>
#include <array>
#include <memory>
#include <vector>
#include <string>
#include <unordered_map>
#include <glm/mat4x4.hpp>

#include "vbo.hpp"

namespace QE::GL {

class Shader {
    struct AttribInfo {
        uint32_t index;
        uint32_t location;
        uint32_t type;
        uint32_t size;
    };
    struct UniformInfo : Shader::AttribInfo {};
    inline static std::vector<Shader*> list;

    std::unordered_map<std::string, AttribInfo> attribs;
    std::unordered_map<std::string, UniformInfo> uniforms;

    uint32_t vs;
    uint32_t fs;
    uint32_t program {};
    bool compiled {};
    const char* vSource;
    const char* fSource;
public: 
    Shader(const char* vSource_, const char* fSource_);

    void use();

    void setAttribute(std::initializer_list<const char*> arr, VBO&);

    void uniform(const char*, const int);
    void uniform(const char*, const glm::vec2&);
    void uniform(const char*, const glm::vec3&);
    void uniform(const char*, const glm::mat4&);
    void uniform(const char*, const glm::uvec2&);
    void uniform(const char*, const float);

    const AttribInfo& getAttribInfo(const char*) const;
    uint32_t getProgram() const;
    uint32_t getAttrib(const char*) const;
    void destroy();
    ~Shader();
};

extern Shader* current_shader;

};