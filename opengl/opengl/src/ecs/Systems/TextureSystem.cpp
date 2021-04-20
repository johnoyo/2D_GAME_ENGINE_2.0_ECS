#include "TextureSystem.h"

void TextureSystem::Init_Transparent_Texture()
{
	unsigned int white_texture_id;

	GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &white_texture_id));
	GLCall(glBindTexture(GL_TEXTURE_2D, white_texture_id));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	uint32_t color = 0xffffffff;
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color));

	std::string str = "-";
	map.push_back(str);
	texture_slot[current_index++] = white_texture_id;
}

void TextureSystem::Load_Texture(const std::string& path)
{
	int w, h, bits;

	stbi_set_flip_vertically_on_load(1);
	auto* pixels = stbi_load(path.c_str(), &w, &h, &bits, STBI_rgb_alpha);
	assert(pixels);
	unsigned int tex_id;

	GLCall(glCreateTextures(GL_TEXTURE_2D, 1, &tex_id));
	GLCall(glBindTexture(GL_TEXTURE_2D, tex_id));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels));

	stbi_image_free(pixels);

	map.push_back(path);
	texture_slot[current_index++] = tex_id;
	if (current_index == 31) std::cout << "NOTE: You have reached the max amount of textures(32)\n";
	assert(current_index < 32);
}

float TextureSystem::Find(const std::string& path)
{
	for (int i = 0; i < map.size(); i++) {
		if (path == map.at(i)) return (float)i;
	}
	std::cerr << "Error! Could not find the file specified. Loading it from scratch!" << "\n";
	Load_Texture(path);
	return (float)map.size() - 1;
}

void TextureSystem::Start()
{
	Init_Transparent_Texture();

	for (unsigned int i = 0; i < materials.size(); i++) {
		if (materials.at(i).texture != "-") Load_Texture(materials.at(i).texture);
	}

	for (int i = 0; i < map.size(); i++) {
		std::cout << map.at(i) << "\n";
	}
}

void TextureSystem::Run(RenderingSystem& rend)
{
	unsigned int i = 0;
	unsigned int indx = 0;
	for (unsigned int i = 0; i < materials.size(); i++) {
		rend.Get_Vertex_Buffer().Update_Material_On_Quad(indx, materials.at(i).color, Find(materials.at(i).texture));
		indx += 4;
	}

	for (i = 0; i < current_index; i++) {
		GLCall(glBindTextureUnit(i, texture_slot[i]));
	}
}

void TextureSystem::Clear()
{
	GLCall(glDeleteTextures(32, texture_slot));
}

