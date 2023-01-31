#pragma once
#include "Shader.h"
#include "Simulatrix/Renderer/Texture.h"
namespace Simulatrix {
    class MaterialInstance
    {
	public:
        MaterialInstance() = default;
        ~MaterialInstance() = default;
        void Bind(Ref<Shader> shader);
        
        void SetUniform(std::string name, float value) {
            m_FloatUniform[name] = value;
        }
        void SetUniform(std::string name, uint32_t value){
            m_UIntUniform[name] = value;
        }
        void SetUniform(std::string name, int value){
            m_IntUniform[name] = value;
        }
        void SetUniform(std::string name, bool value) {
            m_BoolUniform[name] = value;
        }
        void SetUniform(std::string name, const glm::mat3& value) {
            m_Mat3Uniform[name] = value;
        }
        void SetUniform(std::string name, const glm::mat4& value) {
            m_Mat4Uniform[name] = value;
        }
        void SetUniform(std::string name, const glm::vec2& value) {
            m_Vec2Uniform[name] = value;
        }
        void SetUniform(std::string name, const glm::vec3& value) {
            m_Vec3Uniform[name] = value;
        }
        void SetUniform(std::string name, const glm::vec4& value) {
            m_Vec4Uniform[name] = value;
        }
        void SetUniform(std::string name, const glm::ivec2& value) {
            m_IVec2Uniform[name] = value;
        }
        void SetUniform(std::string name, const glm::ivec3& value) {
            m_IVec3Uniform[name] = value;
        }
        void SetUniform(std::string name, const glm::ivec4& value) {
            m_IVec4Uniform[name] = value;
        }
        void SetUniform(std::string name, Ref<Texture2D> texture) {
            m_TextureUniform[name] = texture;
        }
        
		std::string GetName() {
			return m_Name;
		}

        std::unordered_map<std::string, float>* GetFloatUniforms() {
            return &m_FloatUniform;
        }
        std::unordered_map<std::string, uint32_t>* GetUIntUniforms() {
            return &m_UIntUniform;
        }
        std::unordered_map<std::string, int>* GetIntUniforms() {
            return &m_IntUniform;
        }
        std::unordered_map<std::string, bool>* GetBoolUniforms() {
            return &m_BoolUniform;
        }
        std::unordered_map<std::string, glm::mat3>* GetMat3Uniforms() {
            return &m_Mat3Uniform;
        }
        std::unordered_map<std::string, glm::mat4>* GetMat4Uniforms() {
            return &m_Mat4Uniform;
        }
        std::unordered_map<std::string, glm::vec2>* GetVec2Uniforms() {
            return &m_Vec2Uniform;
        }
        std::unordered_map<std::string, glm::vec3>* GetVec3Uniforms() {
            return &m_Vec3Uniform;
        }
        std::unordered_map<std::string, glm::vec4>* GetVec4Uniforms() {
            return &m_Vec4Uniform;
        }
        std::unordered_map<std::string, glm::ivec2>* GetIVec2Uniforms() {
            return &m_IVec2Uniform;
        }
        std::unordered_map<std::string, glm::ivec3>* GetIVec3Uniforms() {
            return &m_IVec3Uniform;
        }
        std::unordered_map<std::string, glm::ivec4>* GetIVec4Uniforms() {
            return &m_IVec4Uniform;
        }
        std::unordered_map<std::string, Ref<Texture2D>>* GetTextureUniforms() {
            return &m_TextureUniform;
        }
        
	protected:
        void SetInitial(std::string name, float value) {
            m_FloatUniform.emplace(name, value);
        }
        void SetInitial(std::string name, uint32_t value) {
            m_UIntUniform.emplace(name, value);
        }
        void SetInitial(std::string name, int value) {
            m_IntUniform.emplace(name, value);
        }
        void SetInitial(std::string name, bool value) {
            m_BoolUniform.emplace(name, value);
        }
        void SetInitial(std::string name, const glm::mat3& value) {
            m_Mat3Uniform.emplace(name, value);
        }
        void SetInitial(std::string name, const glm::mat4& value) {
            m_Mat4Uniform.emplace(name, value);
        }
        void SetInitial(std::string name, const glm::vec2& value) {
            m_Vec2Uniform.emplace(name, value);
        }
        void SetInitial(std::string name, const glm::vec3& value) {
            m_Vec3Uniform.emplace(name, value);
        }
        void SetInitial(std::string name, const glm::vec4& value) {
            m_Vec4Uniform.emplace(name, value);
        }
        void SetInitial(std::string name, const glm::ivec2& value) {
            m_IVec2Uniform.emplace(name, value);
        }
        void SetInitial(std::string name, const glm::ivec3& value) {
            m_IVec3Uniform.emplace(name, value);
        }
        void SetInitial(std::string name, const glm::ivec4& value) {
            m_IVec4Uniform.emplace(name, value);
        }
        void SetInitial(std::string name, Ref<Texture2D> texture) {
            m_TextureUniform.emplace(name, texture);
        }
        std::unordered_map<std::string, float> m_FloatUniform;
        std::unordered_map<std::string, uint32_t> m_UIntUniform;
        std::unordered_map<std::string, int> m_IntUniform;
        std::unordered_map<std::string, bool> m_BoolUniform;
        std::unordered_map<std::string, glm::mat3> m_Mat3Uniform;
        std::unordered_map<std::string, glm::mat4> m_Mat4Uniform;
        std::unordered_map<std::string, glm::vec2> m_Vec2Uniform;
        std::unordered_map<std::string, glm::vec3> m_Vec3Uniform;
        std::unordered_map<std::string, glm::vec4> m_Vec4Uniform;
        std::unordered_map<std::string, glm::ivec2> m_IVec2Uniform;
        std::unordered_map<std::string, glm::ivec3> m_IVec3Uniform;
        std::unordered_map<std::string, glm::ivec4> m_IVec4Uniform;
        std::unordered_map<std::string, Ref<Texture2D>> m_TextureUniform;
		std::string m_Name;
    };
}
