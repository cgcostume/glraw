
#include <glraw/Converter.h>

#include <glraw/AssetInformation.h>


namespace glraw
{

Converter::Converter()
:   m_format(GL_RGBA)
,   m_type(GL_UNSIGNED_BYTE)
{
}

Converter::~Converter()
{
}

QByteArray Converter::convert(Canvas & image, AssetInformation & info)
{
    if (hasFragmentShader() && !image.process(m_fragmentShader, m_uniforms))
        return QByteArray();
    
    info.setProperty("format", QVariant(static_cast<int>(m_format)));
    info.setProperty("type", QVariant(static_cast<int>(m_type)));
    
    return image.imageFromTexture(m_format, m_type);
}

void Converter::setFormat(GLenum format)
{
    m_format = format;
}
    
void Converter::setType(GLenum type)
{
    m_type = type;
}

} // namespace glraw
