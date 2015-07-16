#include <glraw/filter/Erosion.h>

#include <QOpenGLShaderProgram>

#include <glraw/Canvas.h>

namespace
{
	const char * const source =
		R"(#version 150

		uniform sampler2D src;
		uniform unsigned int size;

		in vec2 v_uv;
		out vec4 dst;

		void main()
		{   
			vec2 img_size = vec2(1.0f)/textureSize(src, 0);
			dst = vec4(1.0f);

			for(int i=-size; i<= size;++i)
			{
				dst = min(dst, texture(src, v_uv+img_size*i));
			}
		} )";

	const unsigned int DefaultSize = 1;
}

namespace glraw
{

Erosion::Erosion(unsigned int size = DefaultSize)
	: m_size(VerifySize(size))
{
}

Erosion::Erosion(const QVariantMap& cfg)
	: Erosion(SizeFromVariant(cfg, DefaultSize))
{
}

bool Erosion::process(std::unique_ptr<Canvas> & imageData, AssetInformation & info)
{
	return renderShader(imageData, source);
}

void Erosion::setUniforms(QOpenGLShaderProgram& program)
{
	program.setUniformValue("size", m_size);
}
}
