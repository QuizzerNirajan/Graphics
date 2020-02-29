#pragma once
#include "includes.h"


class Texture
{
private:
	unsigned int m_RendereID, m_ID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
	std::string m_type;
public:
	Texture(const std::string& path);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }
	inline int GetID() const { return m_ID; }
	inline std::string GetType() const { return m_type; }
};