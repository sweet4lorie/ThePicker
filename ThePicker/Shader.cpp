//
//  ThePicker
//  Shader.cpp
//
//  Helps handle setting up, editing, and calling shader
//
//  Emily Chiang
//  emily.mchiang@gmail.com
//

#include "Shader.h"

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string & errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string & text, GLenum shaderType);

Shader::Shader(const std::string & file)
{
    _program = glCreateProgram();
    _shaders[0] = CreateShader(LoadShader(file + ".vs"), GL_VERTEX_SHADER);
    _shaders[1] = CreateShader(LoadShader(file + ".fs"), GL_FRAGMENT_SHADER);
    
    for(unsigned int i = 0; i < NUM_SHADERS; i++)
    {
        glAttachShader(_program, _shaders[i]);
    }
    
    // what part to read in from what variable
    glBindFragDataLocation(_program, 0, "fragData");
    
    // link and validate
    glLinkProgram(_program);
    CheckShaderError(_program, GL_LINK_STATUS, true, "Error: Program Link Failed");

    glValidateProgram(_program);
    CheckShaderError(_program, GL_VALIDATE_STATUS, true, "Error: Program Link Failed");
    
    // uniform variables
    _uniforms[0] = glGetUniformLocation(_program, "ModelViewMatrix");
    _uniforms[1] = glGetUniformLocation(_program, "ProjectionMatrix");
    _uniforms[2] = glGetUniformLocation(_program, "texture");
}

Shader::~Shader()
{
    for(unsigned int i = 0; i < NUM_SHADERS; i++)
    {
        glDetachShader(_program, _shaders[i]);
        glDeleteShader(_shaders[i]);
    }
    glDeleteProgram(_program);
}

void Shader::bind()
{
    glUseProgram(_program);

}

void Shader::bindFixed()
{
    glUseProgram(0);
}

void Shader::update(const Camera & camera, Object & obj)
{
    Mat4 MV = camera.myModelView * obj.getModelMatrix();
    Mat4 P = camera.myProjection;
    
    glUniformMatrix4fv(_uniforms[0], 1, GL_FALSE, &MV[0]);
    glUniformMatrix4fv(_uniforms[1], 1, GL_FALSE, &P[0]);
    glUniform1i(_uniforms[2], 0);
}

void Shader::setColor(float r, float g, float b, float a)
{
    
    float colorVec4[] = {r, g, b, a};
    GLint myColor = glGetUniformLocation(_program, "color");
    glUniform4fv(myColor, 1, colorVec4);
}

static GLuint CreateShader(const std::string & text, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);
    
    if (shader == 0)
    {
        std::cerr << "Error: Shader Creation failed" << std::endl;
    }
    
    const GLchar* shaderString[1];
    GLint shaderStringLength[1];
    shaderString[0] = text.c_str();
    shaderStringLength[0] = (int)text.length();
    
    glShaderSource(shader, 1, shaderString, shaderStringLength);
    glCompileShader(shader);

	GLint compileStatus;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

	if (compileStatus != GL_TRUE){

		std::cout << "Shader Failed to Compile: " << "!" << std::endl;
		
		GLint infoLogLength;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* infoLog = new GLchar[infoLogLength + 1];

		glGetShaderInfoLog(shader, infoLogLength + 1, NULL, infoLog);

		std::cout << infoLog << std::endl;

		delete infoLog;

	}
    
    //CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Compile Failed");
    
    return shader;
}


static std::string LoadShader(const std::string& fileName)
{
    std::ifstream file;
    file.open((fileName).c_str());
    
    std::string output;
    std::string line;
    
    if(!file.is_open()){
        std::cerr << "no :" << fileName << " exists" << std::endl;
    }
    
    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
            output.append(line + "\n");
        }
    }
    return output;
}


static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string & errorMessage)
{
    GLint success;
    GLchar error[1024] = { 0 };
    
    if(isProgram)
    {
        glGetProgramiv(shader, flag, &success);
    }
    else
    {
        glGetProgramiv(shader, flag, &success);
    }
    
    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        std::cerr << errorMessage << ": " << error << std::endl;
    }
}


