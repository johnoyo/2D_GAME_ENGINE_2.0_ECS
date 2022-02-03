#include "RenderingSystem.h"

void RenderingSystem::Initialize(glm::mat4 m_Camera_vp)
{
	GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

	/* vertex array object */
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	/* vertex buffer */
	GLCall(glGenBuffers(1, &vb));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vb));
	GLCall(glBufferData(GL_ARRAY_BUFFER, vbuffer.Get_Total_Size() * sizeof(struct Vertex_Array), nullptr, GL_DYNAMIC_DRAW));

	/* vertex attrib positions*/
	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(struct Vertex_Array), (const void*)offsetof(Vertex_Array, position)));

	/* vertex attrib colors*/
	GLCall(glEnableVertexAttribArray(1));
	GLCall(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(struct Vertex_Array), (const void*)offsetof(Vertex_Array, color)));

	/* vertex attrib texture coordinates*/
	GLCall(glEnableVertexAttribArray(2));
	GLCall(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(struct Vertex_Array), (const void*)offsetof(Vertex_Array, tex_coord)));

	/* vertex attrib texture id*/
	GLCall(glEnableVertexAttribArray(3));
	GLCall(glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(struct Vertex_Array), (const void*)offsetof(Vertex_Array, tex_id)));

	/* index buffer */
	GLCall(glGenBuffers(1, &ib));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, (vbuffer.Get_Size() / 4) * 6 * sizeof(unsigned int), ibuffer.Get_Index_Buffer(), GL_STATIC_DRAW));

	/* shaders */
	ShaderProgramSource shaderSource = ParseShader("res/shaders/Basic.shader");
	shader = CreateShader(shaderSource.VertexSource, shaderSource.FragmentSource);
	GLCall(glUseProgram(shader));

	GLCall(auto loc = glGetUniformLocation(shader, "u_textures"));
	int samplers[32];
	for (unsigned int i = 0; i < 32; i++)
		samplers[i] = i;
	GLCall(glUniform1iv(loc, 32, samplers));

	GLCall(int location1 = glGetUniformLocation(shader, "u_VP"));
	if (location1 == -1) {
		std::cout << "Uniform not found!!!\n";
	}
	GLCall(glUniformMatrix4fv(location1, 1, GL_FALSE, glm::value_ptr(m_Camera_vp)));
}

void RenderingSystem::Render(glm::mat4 m_Camera_vp)
{
	Update_Camera_Uniform(m_Camera_vp);

	/* set dynamic vertex buffer */
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vb));
	GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, vbuffer.Get_Size() * sizeof(Vertex_Array), vbuffer.Get_Buffer()));

	/* Render here */
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	GLCall(glDrawElements(GL_TRIANGLES, (vbuffer.Get_Size() / 4) * 6, GL_UNSIGNED_INT, NULL));
}

void RenderingSystem::Clear()
{
	GLCall(glDeleteBuffers(1, &vb));
	GLCall(glDeleteBuffers(1, &ib));
	GLCall(glDeleteProgram(shader));
	GLCall(glDeleteVertexArrays(1, &vao));

	vbuffer.Clean();
	ibuffer.Clean();
}

void RenderingSystem::Upadte_Index_Buffer(unsigned int size)
{
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, (size / 4) * 6 * sizeof(unsigned int), ibuffer.Get_Index_Buffer(), GL_STATIC_DRAW));
}

void RenderingSystem::Init_Vertex_Buffer()
{
	vbuffer.Reset();
	std::cout << "Transform size: " << transforms.size() << "\n";
	for (unsigned int i = 0; i < entities.size(); i++) {
		int j = entities.at(i).transform;
		int k = entities.at(i).attributes;
		if (entities.at(i).transform != -1 && entities.at(i).attributes != -1) {
			if (attributes.at(k).Enabled) {
				attributes.at(k).bufferIndex = vbuffer.index;
				vbuffer.Fill_Buffer({ transforms.at(j).position.x, transforms.at(j).position.y + transforms.at(j).scale.y }, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), 0);
				vbuffer.Fill_Buffer({ transforms.at(j).position.x + transforms.at(j).scale.x, transforms.at(j).position.y + transforms.at(j).scale.y }, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), 0);
				vbuffer.Fill_Buffer({ transforms.at(j).position.x + transforms.at(j).scale.x , transforms.at(j).position.y }, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f), 0);
				vbuffer.Fill_Buffer({ transforms.at(j).position.x, transforms.at(j).position.y }, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), 0);
			}
		}
	}
	std::cout << "Vertex buffer size: " << vbuffer.Get_Size() / 4 << "\n";
	ibuffer.Clean();
	ibuffer.Make_Indecies(vbuffer.Get_Size());
	Upadte_Index_Buffer(vbuffer.Get_Size());
}

void RenderingSystem::Update_Vertex_Buffer_Positions(int playerTransformID)
{
	unsigned int indx = 0;
	for (unsigned int i = 0; i < transforms.size() - 1; i++) {
		if(i != playerTransformID && attributes.at(i).Enabled) vbuffer.Update_Position_On_Quad(indx, transforms.at(i));
		indx += 4;
	}
}

void RenderingSystem::Update_Camera_Uniform(glm::mat4 m_Camera_vp)
{
	GLCall(int location1 = glGetUniformLocation(shader, "u_VP"));
	if (location1 == -1) {
		std::cout << "Uniform not found!!!\n";
	}
	GLCall(glUniformMatrix4fv(location1, 1, GL_FALSE, glm::value_ptr(m_Camera_vp)));
}

void RenderingSystem::Draw_Lone_Quad(Entity::BaseEntity entt)
{
	vbuffer.Reset();

	vbuffer.Fill_Buffer({ transforms.at(entt.transform).position.x, transforms.at(entt.transform).position.y + transforms.at(entt.transform).scale.y }, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), 0);
	vbuffer.Fill_Buffer({ transforms.at(entt.transform).position.x + transforms.at(entt.transform).scale.x, transforms.at(entt.transform).position.y + transforms.at(entt.transform).scale.y }, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), 0);
	vbuffer.Fill_Buffer({ transforms.at(entt.transform).position.x + transforms.at(entt.transform).scale.x , transforms.at(entt.transform).position.y }, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f), 0);
	vbuffer.Fill_Buffer({ transforms.at(entt.transform).position.x, transforms.at(entt.transform).position.y }, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), 0);

	std::cout << vbuffer.Get_Size() / 4 << "\n";

	ibuffer.Clean();
	ibuffer.Make_Indecies(vbuffer.Get_Size());
	Upadte_Index_Buffer(vbuffer.Get_Size());
}

ShaderProgramSource RenderingSystem::ParseShader(const std::string& filepath)
{
	std::fstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str() };
}

unsigned int RenderingSystem::CompileShader(unsigned int type, const std::string& source)
{
	GLCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE)
	{
		int lenght;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght));
		char* message = (char*)alloca(lenght * sizeof(char));
		GLCall(glGetShaderInfoLog(id, lenght, &lenght, message));
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader!" << "\n";
		std::cout << message << "\n";
		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

unsigned int RenderingSystem::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLCall(unsigned int program = glCreateProgram());
	GLCall(unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader));
	GLCall(unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader));

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}


void RenderingSystem::Start(glm::mat4 vpMatrix)
{
	std::cout << "Starting rendering system ...\n";
	vbuffer.total_size = (100 * 100) * 4;

	vbuffer.Initialize(vbuffer.total_size);
	ibuffer.Make_Indecies(vbuffer.Get_Size());
	Initialize(vpMatrix);

	Init_Vertex_Buffer();
}

void RenderingSystem::Run(int playerTransformID)
{
	Update_Vertex_Buffer_Positions(playerTransformID);
}

/* ------------------------------------------------------------------------ Vertex Buffer --------------------------------------------------------------------------- */

void VertexBuffer::Initialize(int total_buffer_size)
{
	total_size = total_buffer_size;
	buffer = (struct Vertex_Array*)malloc(total_buffer_size * sizeof(struct Vertex_Array));
}

void VertexBuffer::Fill_Buffer(glm::vec2 position, glm::vec4 color, glm::vec2 tex_coords, float tex_id)
{
	buffer[index].position = position;
	buffer[index].color = color;
	buffer[index].tex_coord = tex_coords;
	buffer[index].tex_id = tex_id;
	index++;
}

void VertexBuffer::Update_Position_On_Quad(unsigned int indx, Component::Transform tr)
{
	buffer[indx].position.x = tr.position.x;
	buffer[indx].position.y = tr.position.y + tr.scale.y;
	indx++;
	buffer[indx].position.x = tr.position.x + tr.scale.x;
	buffer[indx].position.y = tr.position.y + tr.scale.y;
	indx++;
	buffer[indx].position.x = tr.position.x + tr.scale.x;
	buffer[indx].position.y = tr.position.y;
	indx++;
	buffer[indx].position.x = tr.position.x;
	buffer[indx].position.y = tr.position.y;
	indx++;
}

void VertexBuffer::Update_PositionX_On_Quad(unsigned int indx, Component::Transform tr)
{
	buffer[indx].position.x = tr.position.x;
	indx++;
	buffer[indx].position.x = tr.position.x + tr.scale.x;
	indx++;
	buffer[indx].position.x = tr.position.x + tr.scale.x;
	indx++;
	buffer[indx].position.x = tr.position.x;
	indx++;
}

void VertexBuffer::Update_PositionY_On_Quad(unsigned int indx, Component::Transform tr)
{
	buffer[indx].position.y = tr.position.y + tr.scale.y;
	indx++;
	buffer[indx].position.y = tr.position.y + tr.scale.y;
	indx++;
	buffer[indx].position.y = tr.position.y;
	indx++;
	buffer[indx].position.y = tr.position.y;
	indx++;
}

void VertexBuffer::Update_Material_On_Quad(unsigned int indx, glm::vec4 color, float tex_id)
{
	buffer[indx].color = color;
	buffer[indx].tex_coord = { 0.0f, 1.0f };
	buffer[indx].tex_id = tex_id;
	indx++;
	buffer[indx].color = color;
	buffer[indx].tex_coord = { 1.0f, 1.0f };
	buffer[indx].tex_id = tex_id;
	indx++;
	buffer[indx].color = color;
	buffer[indx].tex_coord = { 1.0f, 0.0f };
	buffer[indx].tex_id = tex_id;
	indx++;
	buffer[indx].color = color;
	buffer[indx].tex_coord = { 0.0f, 0.0f };
	buffer[indx].tex_id = tex_id;
	indx++;
}

void VertexBuffer::Update_Material_On_Quad(unsigned int indx, glm::vec4 color, float tex_id, glm::vec2 coords, glm::vec2 sheet_size, glm::vec2 sp_size)
{
	buffer[indx].color = color;
	buffer[indx].tex_coord = { (coords.x * sp_size.x) / sheet_size.x, ((coords.y + 1) * sp_size.y) / sheet_size.y };
	buffer[indx].tex_id = tex_id;
	indx++;
	buffer[indx].color = color;
	buffer[indx].tex_coord = { ((coords.x + 1) * sp_size.x) / sheet_size.x, ((coords.y + 1) * sp_size.y) / sheet_size.y };
	buffer[indx].tex_id = tex_id;
	indx++;
	buffer[indx].color = color;
	buffer[indx].tex_coord = { ((coords.x + 1) * sp_size.x) / sheet_size.x, (coords.y * sp_size.y) / sheet_size.y };
	buffer[indx].tex_id = tex_id;
	indx++;
	buffer[indx].color = color;
	buffer[indx].tex_coord = { (coords.x * sp_size.x) / sheet_size.x, (coords.y * sp_size.y) / sheet_size.y };
	buffer[indx].tex_id = tex_id;
	indx++;
}

Vertex_Array* VertexBuffer::Get_Buffer()
{
	return buffer;
}

void VertexBuffer::Set_Buffer(Vertex_Array* new_buffer)
{
	buffer = new_buffer;
}

unsigned int VertexBuffer::Get_Size()
{
	return index;
}

void VertexBuffer::Set_Size(unsigned int size)
{
	index = size;
}

unsigned int VertexBuffer::Get_Total_Size()
{
	return total_size;
}

void VertexBuffer::Reset()
{
	index = 0;
}

void VertexBuffer::Clean()
{
	if (buffer != NULL) free(buffer);
	total_size = 0;
	index = 0;
}

/* ------------------------------------------------------------------- Index Buffer ---------------------------------------------------------------------- */

void IndexBuffer::Make_Indecies(unsigned int size)
{
	index_buffer = (unsigned int*)malloc((size / 4) * 6 * sizeof(unsigned int));
	int w = 0;
	for (int k = 0; k < (size / 4) * 6; k += 6) {
		index_buffer[index++] = 0 + w;
		index_buffer[index++] = 3 + w;
		index_buffer[index++] = 2 + w;
		index_buffer[index++] = 2 + w;
		index_buffer[index++] = 1 + w;
		index_buffer[index++] = 0 + w;
		w += 4;
	}

}

void IndexBuffer::Clean()
{
	if (index_buffer != NULL) free(index_buffer);
	index = 0;
}

unsigned int* IndexBuffer::Get_Index_Buffer()
{
	return index_buffer;
}