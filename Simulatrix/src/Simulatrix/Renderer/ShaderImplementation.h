#pragma once
//#include <Simulatrix/Core/IOWrapper.h>
//#include <Simulatrix/Core/Core.h>
//#include <Simulatrix/Renderer/Shader.h>
//namespace Simulatrix {
//    template <typename... T>
//    class ShaderImplementation {
//    public:
//        ShaderImplementation(Path& vs, Path& fs, std::string name, ShaderUniforms uniforms) {
//            auto vsFile = ResourceManager::GetIO()->ReadText(vs);
//            auto fsFile = ResourceManager::GetIO()->ReadText(fs);
//
//            m_Shader.reset(Shader::Create(vsFile, fsFile));
//            m_Shader->AddUniforms(uniforms);
//        }
//        
//        template<typename F>
//        void LoadUniforms(F material) {
//            static_assert(is_one_of<F, T...>::value, "F is not one of the types in T...");
//            LoadUniformsImpl(material);
//        }
//    private:
//        Ref<Shader> m_Shader;
//        template<typename F>
//        virtual void LoadUniformsImpl(F material) = 0;
//    };
//}