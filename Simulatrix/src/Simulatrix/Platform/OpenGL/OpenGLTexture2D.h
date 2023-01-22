#pragma once
#include "Simulatrix/Renderer/Texture.h"
#include "Simulatrix/Core/IOWrapper.h"

#include <glad/glad.h>

namespace Simulatrix {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const Path& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual uint32_t GetRendererID() const override { return m_RendererID; }

		virtual const Path& GetPath() const override { return m_Path; }

		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;

		virtual UUID GetID() const override {
			return m_ID;
		}
		virtual void SetID(UUID& id) override {
			m_ID = id;
		}

		virtual bool IsLoaded() const override { return m_IsLoaded; }
	private:
		Path m_Path;
		bool m_IsLoaded = false;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		UUID m_ID;
		GLenum m_InternalFormat, m_DataFormat;
	};

}