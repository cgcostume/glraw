
#include <glraw/CompressionConverter.h>

#include <glraw/AssetInformation.h>


namespace glraw
{

CompressionConverter::CompressionConverter()
:   m_compressedFormat(GL_COMPRESSED_RGBA)
{
}

CompressionConverter::~CompressionConverter()
{
}

QByteArray CompressionConverter::convert(Canvas & image, AssetInformation & info)
{   
    if (hasFragmentShader() && !image.process(m_fragmentShader, m_uniforms))
        return QByteArray();
    
    QByteArray imageData = image.compressedImageFromTexture(m_compressedFormat);
    
    info.setProperty("compressedFormat", QVariant(static_cast<int>(m_compressedFormat)));
    info.setProperty("size", QVariant(imageData.size()));
    
    return imageData;
}

void CompressionConverter::setCompressedFormat(GLint compressedFormat)
{
    m_compressedFormat = compressedFormat;
}

} // namespace glraw
