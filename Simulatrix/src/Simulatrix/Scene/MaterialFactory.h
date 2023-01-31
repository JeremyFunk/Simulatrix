#pragma once
#include "Simulatrix/Renderer/MaterialInstance.h"
#include <glm/glm.hpp>
#include <variant>
#include <Simulatrix/Renderer/Texture.h>
namespace Simulatrix {
    struct MaterialAttribute {
        std::variant<Ref<Texture2D>, float, uint32_t, int, bool, glm::mat3, glm::mat4, glm::vec2, glm::vec3, glm::vec4, glm::ivec2, glm::ivec3, glm::ivec4> Value;
        std::string Name;
    };
    
    struct MaterialBlueprint {
        std::unordered_map<std::string, float> FloatUniform;
        std::unordered_map<std::string, uint32_t> UIntUniform;
        std::unordered_map<std::string, int> IntUniform;
        std::unordered_map<std::string, bool> BoolUniform;
        std::unordered_map<std::string, glm::mat3> Mat3Uniform;
        std::unordered_map<std::string, glm::mat4> Mat4Uniform;
        std::unordered_map<std::string, glm::vec2> Vec2Uniform;
        std::unordered_map<std::string, glm::vec3> Vec3Uniform;
        std::unordered_map<std::string, glm::vec4> Vec4Uniform;
        std::unordered_map<std::string, glm::ivec2> IVec2Uniform;
        std::unordered_map<std::string, glm::ivec3> IVec3Uniform;
        std::unordered_map<std::string, glm::ivec4> IVec4Uniform;
        std::unordered_map<std::string, Ref<Texture2D>> Textures;
        std::string Name;
    };

    class MaterialFactory
    {
    public:
        static void AddMaterial(std::string materialName, std::initializer_list<MaterialAttribute> attributes) {
            MaterialBlueprint blueprint;
            for (auto& attr : attributes) {
                if(std::holds_alternative<float>(attr.Value))
                    blueprint.FloatUniform.emplace(attr.Name, std::get<float>(attr.Value));
                if (std::holds_alternative<uint32_t>(attr.Value))
                    blueprint.IntUniform.emplace(attr.Name, std::get<uint32_t>(attr.Value));
                if (std::holds_alternative<int>(attr.Value))
                    blueprint.IntUniform.emplace(attr.Name, std::get<int>(attr.Value));
                if (std::holds_alternative<bool>(attr.Value))
                    blueprint.IntUniform.emplace(attr.Name, std::get<bool>(attr.Value));
                if (std::holds_alternative<glm::vec2>(attr.Value))
                    blueprint.Vec2Uniform.emplace(attr.Name, std::get<glm::vec2>(attr.Value));
                if (std::holds_alternative<glm::vec3>(attr.Value))
                    blueprint.Vec3Uniform.emplace(attr.Name, std::get<glm::vec3>(attr.Value));
                if (std::holds_alternative<glm::vec4>(attr.Value))
                    blueprint.Vec4Uniform.emplace(attr.Name, std::get<glm::vec4>(attr.Value));
                if (std::holds_alternative<glm::mat3>(attr.Value))
                    blueprint.Mat3Uniform.emplace(attr.Name, std::get<glm::mat3>(attr.Value));
                if (std::holds_alternative<glm::mat4>(attr.Value))
                    blueprint.Mat4Uniform.emplace(attr.Name, std::get<glm::mat4>(attr.Value));
                if (std::holds_alternative<glm::ivec2>(attr.Value))
                    blueprint.IVec2Uniform.emplace(attr.Name, std::get<glm::ivec2>(attr.Value));
                if (std::holds_alternative<glm::ivec3>(attr.Value))
                    blueprint.IVec3Uniform.emplace(attr.Name, std::get<glm::ivec3>(attr.Value));
                if (std::holds_alternative<glm::ivec4>(attr.Value))
                    blueprint.IVec4Uniform.emplace(attr.Name, std::get<glm::ivec4>(attr.Value));
                if (std::holds_alternative<Ref<Texture2D>>(attr.Value))
                    blueprint.Textures.emplace(attr.Name, std::get<Ref<Texture2D>>(attr.Value));
            }
            blueprint.Name = materialName;
            s_Materials.push_back(blueprint);
        }

        static MaterialInstance* CreateMaterialInstance(const std::string& name) {
            for (auto& material : s_Materials) {
                if (material.Name == name) {
                    MaterialInstance* i = new MaterialInstance();
                    for (auto& floatUniform : material.FloatUniform)
                        i->SetUniform(floatUniform.first, floatUniform.second);
                    for (auto& uintUniform : material.UIntUniform)
                        i->SetUniform(uintUniform.first, uintUniform.second);
                    for (auto& intUniform : material.IntUniform)
                        i->SetUniform(intUniform.first, intUniform.second);
                    for (auto& boolUniform : material.BoolUniform)
                        i->SetUniform(boolUniform.first, boolUniform.second);
                    for (auto& mat3Uniform : material.Mat3Uniform)
                        i->SetUniform(mat3Uniform.first, mat3Uniform.second);
                    for (auto& mat4Uniform : material.Mat4Uniform)
                        i->SetUniform(mat4Uniform.first, mat4Uniform.second);
                    for (auto& vec2Uniform : material.Vec2Uniform)
                        i->SetUniform(vec2Uniform.first, vec2Uniform.second);
                    for (auto& vec3Uniform : material.Vec3Uniform)
                        i->SetUniform(vec3Uniform.first, vec3Uniform.second);
                    for (auto& vec4Uniform : material.Vec4Uniform)
                        i->SetUniform(vec4Uniform.first, vec4Uniform.second);
                    for (auto& ivec2Uniform : material.IVec2Uniform)
                        i->SetUniform(ivec2Uniform.first, ivec2Uniform.second);
                    for (auto& ivec3Uniform : material.IVec3Uniform)
                        i->SetUniform(ivec3Uniform.first, ivec3Uniform.second);
                    for (auto& ivec4Uniform : material.IVec4Uniform)
                        i->SetUniform(ivec4Uniform.first, ivec4Uniform.second);
                    for (auto& texturesUniform : material.Textures)
                        i->SetUniform(texturesUniform.first, texturesUniform.second);
                    return i;
                    
                }
            }
            return nullptr;
        }

        static std::vector<std::string> GetMaterialNames() {
            std::vector<std::string> names;
            for (auto& material : s_Materials)
                names.push_back(material.Name);
            return names;
        }
    private:
        static std::vector<MaterialBlueprint> s_Materials;
    };
}