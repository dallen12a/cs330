/* Module 7 Assignment */

// Include statements
#include "ShapeBuilder.h"
#include "Mesh.h"
#include "SceneBuilder.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


// Shader program
#ifndef GLSL
#define GLSL(Version, Source) "#version " #Version " core \n" #Source
#endif


using namespace std;

// Window name and dimensions
const char* const WINDOW_TITLE = "Module 7 Project";
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

// Initialization of variables
struct GLightMesh
{
	GLuint vao;         // Handle for the vertex array object
	GLuint vbo;         // Handle for the vertex buffer object
	GLuint nVertices;    // Number of indices of the mesh
};

GLightMesh spotLightMesh;
GLightMesh keyLightMesh;
ShapeBuilder builder;

// Main window
GLFWwindow* gWindow = nullptr;

// Shader program
GLuint gShaderProgram;
GLuint gLightProgramId;

// Vector for scene
vector<GLMesh> scene;

// Perspective boolean
bool perspective = false;


// Camera setup
Camera gCamera(glm::vec3(-6.0f, 6.0f, -7.0f), glm::vec3(0.0f, 1.0f, 0.0f), 53.0f, -23.0f);
//Camera gCamera(glm::vec3(0.0f, 4.0f, 8.0f));




float gLastX = WINDOW_WIDTH / 2.0f;
float gLastY = WINDOW_HEIGHT / 2.0f;
bool gFirstMouse = true;


// Delta and Last Frame
float gDeltaTime = 0.0f;
float gLastFrame = 0.0f;


// Spotlight setup
glm::vec3 gSpotLightColor(1.0f, 1.0f, 1.0f);
glm::vec3 gSpotLightPosition(2.5f, 6.0f, -1.5f);
glm::vec3 gSpotLightScale(0.1f);

// Color, postition, and scale for light
glm::vec3 gKeyLightColor(1.0f, 0.0f, 1.0f);
glm::vec3 gKeyLightPosition(-2.5f, 4.0f, -1.5f);
glm::vec3 gKeyLightScale(0.0f);

bool gSpotLightOrbit = true;

// Initialization for window and input
bool UInitialize(int, char* [], GLFWwindow** window);
void UResizeWindow(GLFWwindow* window, int width, int height);
void UProcessInput(GLFWwindow* window);
void URender(vector<GLMesh> scene);
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource,
	GLuint& programId);

// Destroys to free up memory
void UDestroyMesh(GLMesh& mesh);
void UDestroyShaderProgram(GLuint programId);
void UDestroyTexture(GLuint textureId);

// Functions to build shapes
void UBuildCylinder(GLMesh& mesh, vector<float> properties, float radius, float length);
void UBuildCone(GLMesh& mesh, vector<float> properties, float radius, float length);
void UBuildPlane(GLMesh& mesh, vector<float> properties);
void UBuildCircle(GLMesh& mesh, vector<float> properties, float radius);


// Input functions
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos);
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

// Texture and mesh
bool UCreateTexture(const char* filename, GLuint& textureId);
void UCreateLightMesh(GLightMesh& lightMesh);





// Vertex Shader Source Code
const GLchar* vertex_shader_source = GLSL(440,
	layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 textureCoordinate;

out vec3 vertexNormal;
out vec3 vertexFragmentPos;
out vec2 vertexTextureCoordinate;

// mat4 variables
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
	vertexFragmentPos = vec3(model * vec4(position, 1.0f));
	vertexNormal = mat3(transpose(inverse(model))) * normal;
	vertexTextureCoordinate = textureCoordinate;
}
);

// Fragment Shader Source Code
const GLchar* fragment_shader_source = GLSL(440,

	in vec3 vertexFragmentPos;
in vec3 vertexNormal;
in vec2 vertexTextureCoordinate;

out vec4 fragmentColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 keyLightColor;
uniform vec3 lightPos;
uniform vec3 keyLightPos;
uniform vec3 viewPosition;

uniform sampler2D uTexture;
uniform vec2 uvScale;

void main()
{
	// Ambient light setup
	float spotStrength = 0.2f;
	float keyStrength = 0.1f;
	vec3 spot = spotStrength * lightColor;
	vec3 key = keyStrength * keyLightColor;

	// Diffuse lighting setup
	vec3 norm = normalize(vertexNormal);
	vec3 lightDirection = normalize(lightPos - vertexFragmentPos);
	vec3 keyLightDirection = normalize(keyLightPos - vertexFragmentPos);

	float impact = max(dot(norm, lightDirection), 0.0);
	float keyImpact = max(dot(norm, keyLightDirection), 0.0);

	vec3 diffuse = impact * lightColor;
	vec3 keyDiffuse = keyImpact * keyLightColor;

	// Specular light setup
	float specularIntensity = 0.4f;
	float highlightSize = 16.0f;
	vec3 viewDir = normalize(viewPosition - vertexFragmentPos);
	vec3 reflectDir = reflect(-lightDirection, norm);
	float specularComponent = pow(max(dot(viewDir, reflectDir), 0.0), highlightSize);
	vec3 specular = specularIntensity * specularComponent * lightColor;
	vec3 keySpecular = specularIntensity * specularComponent * keyLightColor;

	// Texture color
	vec4 textureColor = texture(uTexture, vertexTextureCoordinate * uvScale);

	// Phong light setup
	vec3 phong = (spot + key + diffuse + keyDiffuse + specular) * textureColor.xyz;

	fragmentColor = vec4(phong, 1.0);

}
);






// Shader Source Code
const GLchar* lampVertexShaderSource = GLSL(440,

	layout(location = 0) in vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0f);
}
);

// Fragment Shader Source Code
const GLchar* lampFragmentShaderSource = GLSL(440,

	out vec4 fragmentColor;

void main()
{
	fragmentColor = vec4(1.0f);
}
);








void flipImageVertically(unsigned char* image, int width, int height, int channels)
{
	for (int j = 0; j < height / 2; ++j)
	{
		int index1 = j * width * channels;
		int index2 = (height - 1 - j) * width * channels;

		for (int i = width * channels; i > 0; --i)
		{
			unsigned char tmp = image[index1];
			image[index1] = image[index2];
			image[index2] = tmp;
			++index1;
			++index2;
		}
	}
}



// Main
int main(int argc, char* argv[])
{
	if (!UInitialize(argc, argv, &gWindow))
		return EXIT_FAILURE;


	SceneBuilder::UBuildScene(scene);

	// Shader build 

	for (auto& m : scene)
	{
		if (!UCreateTexture(m.texFilename, m.textureId))
		{
			cout << "Failed to load texture " << m.texFilename << endl;
			return EXIT_FAILURE;

		}

		if (!UCreateShaderProgram(vertex_shader_source, fragment_shader_source,
			gShaderProgram))
			return EXIT_FAILURE;


	}

	if (!UCreateShaderProgram(lampVertexShaderSource, lampFragmentShaderSource, gLightProgramId))
		return EXIT_FAILURE;

	// Light mesh setup
	UCreateLightMesh(spotLightMesh);
	UCreateLightMesh(keyLightMesh);



	glUseProgram(gShaderProgram);
	glUniform1i(glGetUniformLocation(gShaderProgram, "uTexture"), 0);

	// Render loop
	while (!glfwWindowShouldClose(gWindow))
	{
		// Background color
		glClearColor(1.0f, 0.5f, 0.0f, 1.0f);


		float currentFrame = glfwGetTime();
		gDeltaTime = currentFrame - gLastFrame;
		gLastFrame = currentFrame;

		UProcessInput(gWindow);

		// Render scene
		URender(scene);

		glfwPollEvents();
	}

	for (auto& m : scene)
	{
		UDestroyMesh(m);
	}

	scene.clear();

	UDestroyShaderProgram(gShaderProgram);
	UDestroyShaderProgram(gLightProgramId);

	exit(EXIT_SUCCESS);

}






// Initialize
bool UInitialize(int argc, char* argv[], GLFWwindow** window)
{
	// Initialize GLFW, GLEW, create window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creates window
	*window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

	if (*window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(*window);
	glfwSetFramebufferSizeCallback(*window, UResizeWindow);
	glfwSetCursorPosCallback(*window, UMousePositionCallback);
	glfwSetScrollCallback(*window, UMouseScrollCallback);
	glfwSetMouseButtonCallback(*window, UMouseButtonCallback);
	glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Initializes GLEW
	glewExperimental = GL_TRUE;
	GLenum GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult)
	{
		std::cerr << glewGetErrorString(GlewInitResult) << std::endl;
		return false;
	}

	return true;
}
bool UCreateShaderProgram(const char* vtxShaderSource, const char* fragShaderSource, GLuint& programId)
{

	int success = 0;
	char infoLog[512];

	// Shader program object
	programId = glCreateProgram();

	// Vertex and fragment shader
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	// Shader source
	glShaderSource(vertexShaderId, 1, &vtxShaderSource, NULL);
	glShaderSource(fragmentShaderId, 1, &fragShaderSource, NULL);

	// Compiles vertex shader
	glCompileShader(vertexShaderId);

	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShaderId, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

		return false;
	}

	// Compiles fragment shader
	glCompileShader(fragmentShaderId);

	glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderId, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

		return false;
	}

	// Attaches shader
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);

	// Links the program
	glLinkProgram(programId);

	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programId, sizeof(infoLog), NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

		return false;
	}

	glUseProgram(programId);

	return true;
}

// Processes input
void UProcessInput(GLFWwindow* window)
{

	// Escapes
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// Lines
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Shapes
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Moves camera
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		gCamera.ProcessKeyboard(FORWARD, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		gCamera.ProcessKeyboard(BACKWARD, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		gCamera.ProcessKeyboard(LEFT, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		gCamera.ProcessKeyboard(RIGHT, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		gCamera.ProcessKeyboard(UP, gDeltaTime);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		gCamera.ProcessKeyboard(DOWN, gDeltaTime);

	// Moves light
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		gSpotLightPosition.x -= 0.05f;
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		gSpotLightPosition.x += 0.05f;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		gSpotLightPosition.z -= 0.05f;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		gSpotLightPosition.z += 0.05f;
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
		gSpotLightPosition.y -= 0.05f;
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		gSpotLightPosition.y += 0.05f;


	// Modifies color of light
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		gKeyLightColor.r += 0.001f;
		if (gKeyLightColor.r > 1.0f)
		{
			gKeyLightColor.r = 0.0f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		gKeyLightColor.g += 0.001f;
		if (gKeyLightColor.g > 1.0f)
		{
			gKeyLightColor.g = 0.0f;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		gKeyLightColor.b += 0.001f;
		if (gKeyLightColor.b > 1.0f)
		{
			gKeyLightColor.b = 0.0f;
		}
	}

	// Turns off light "["
	if (glfwGetKey(window, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS)
	{
		gKeyLightColor.r = 0.0f;
		gKeyLightColor.g = 0.0f;
		gKeyLightColor.b = 0.0f;

	}

	// Turns off key light "]"
	if (glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS)
	{
		gKeyLightColor.r = 1.0f;
		gKeyLightColor.g = 0.0f;
		gKeyLightColor.b = 1.0f;

	}



	// Switches view from perspective to ortho "V" and "B"
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		perspective = false;
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		perspective = true;


	// Light orbit (T/F)
	static bool isLKeyDown = false;
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS && !gSpotLightOrbit)
		gSpotLightOrbit = true;
	else if (glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS && gSpotLightOrbit)
		gSpotLightOrbit = false;





}
void UResizeWindow(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void UMousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (gFirstMouse)
	{
		gLastX = xpos;
		gLastY = ypos;
		gFirstMouse = false;
	}

	float xoffset = xpos - gLastX;
	float yoffset = gLastY - ypos; // reversed since y-coordinates go from bottom to top

	gLastX = xpos;
	gLastY = ypos;

	gCamera.ProcessMouseMovement(xoffset, yoffset);
}
void UMouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	// Camera speed
	gCamera.ProcessMouseScroll(yoffset);
}
void UMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{

	switch (button)
	{
	case GLFW_MOUSE_BUTTON_LEFT:
	{
		if (action == GLFW_PRESS)
			cout << "LP" << endl;
		else
			cout << "LR" << endl;
	}
	break;

	case GLFW_MOUSE_BUTTON_MIDDLE:
	{
		if (action == GLFW_PRESS)
			cout << "MP" << endl;
		else
			cout << "MR" << endl;
	}
	break;

	case GLFW_MOUSE_BUTTON_RIGHT:
	{
		if (action == GLFW_PRESS)
			cout << "RP" << endl;
		else
			cout << "RR" << endl;
	}
	break;

	default:
		cout << "Unhandled mouse button event" << endl;
		break;
	}
}

// Renders scene
void URender(vector<GLMesh> scene)
{
	// Light circles
	constexpr float angularVelocity = glm::radians(45.0f);
	if (gSpotLightOrbit)
	{
		glm::vec4 newPosition = glm::rotate(angularVelocity * gDeltaTime, glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(gSpotLightPosition, 1.0f);
		gSpotLightPosition.x = newPosition.x;
		gSpotLightPosition.y = newPosition.y;
		gSpotLightPosition.z = newPosition.z;
	}

	// Z-Depth
	glEnable(GL_DEPTH_TEST);

	// Sets background
	glClearColor(0.035f, 0.144f, 0.220f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glm::mat4 view = gCamera.GetViewMatrix();

	// Perspective projection
	glm::mat4 projection;
	if (!perspective)
	{
		// Perspective
		projection = glm::perspective(glm::radians(gCamera.Zoom), (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);
	}
	else
		// Ortho
		projection = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 100.0f);



	// Draw loop
	for (auto i = 0; i < scene.size(); ++i)
	{
		auto mesh = scene[i];

		// Activate VBO
		glBindVertexArray(mesh.vao);

		// Use shader
		glUseProgram(gShaderProgram);

		GLint modelLocation = glGetUniformLocation(gShaderProgram, "model");
		GLint viewLocation = glGetUniformLocation(gShaderProgram, "view");
		GLint projLocation = glGetUniformLocation(gShaderProgram, "projection");

		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(mesh.model));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));

		// Reference to shape color, light color, light position, and camera position
		GLint objectColorLoc = glGetUniformLocation(gShaderProgram, "objectColor");

		// Spot light
		GLint lightColorLoc = glGetUniformLocation(gShaderProgram, "lightColor");
		GLint lightPositionLoc = glGetUniformLocation(gShaderProgram, "lightPos");

		// Key light
		GLint keyLightColorLoc = glGetUniformLocation(gShaderProgram, "keyLightColor");
		GLint keyLightPositionLoc = glGetUniformLocation(gShaderProgram, "keyLightPos");

		// Camera view
		GLint viewPositionLoc = glGetUniformLocation(gShaderProgram, "viewPosition");

		// Data to the shape shader 
		glUniform3f(objectColorLoc, mesh.p[0], mesh.p[1], mesh.p[2]);

		// Spot light
		glUniform3f(lightColorLoc, gSpotLightColor.r, gSpotLightColor.g, gSpotLightColor.b);
		glUniform3f(lightPositionLoc, gSpotLightPosition.x, gSpotLightPosition.y, gSpotLightPosition.z);

		// Key light
		glUniform3f(keyLightColorLoc, gKeyLightColor.r, gKeyLightColor.g, gKeyLightColor.b);
		glUniform3f(keyLightPositionLoc, gKeyLightPosition.x, gKeyLightPosition.y, gKeyLightPosition.z);


		const glm::vec3 cameraPosition = gCamera.Position;
		glUniform3f(viewPositionLoc, cameraPosition.x, cameraPosition.y, cameraPosition.z);


		GLint UVScaleLoc = glGetUniformLocation(gShaderProgram, "uvScale");
		glUniform2fv(UVScaleLoc, 1, glm::value_ptr(mesh.gUVScale));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh.textureId);

		// Draws the shape
		glDrawArrays(GL_TRIANGLES, 0, mesh.nIndices);


	}
	// Variables for light
	glm::mat4 model;
	GLint modelLoc;
	GLint viewLoc;
	GLint projLoc;

	// --------------------
	// Draws the spot light
	glUseProgram(gLightProgramId);
	glBindVertexArray(spotLightMesh.vao);

	// Sets location and scale for spot light
	model = glm::translate(gSpotLightPosition) * glm::scale(gSpotLightScale);

	modelLoc = glGetUniformLocation(gLightProgramId, "model");
	viewLoc = glGetUniformLocation(gLightProgramId, "view");
	projLoc = glGetUniformLocation(gLightProgramId, "projection");

	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Draws the light
	glDrawArrays(GL_TRIANGLES, 0, spotLightMesh.nVertices);

	// Draws the Key Light
	glUseProgram(gLightProgramId);
	glBindVertexArray(keyLightMesh.vao);

	// Sets key light location and Scale
	model = glm::translate(gKeyLightPosition) * glm::scale(gKeyLightScale);

	modelLoc = glGetUniformLocation(gLightProgramId, "model");
	viewLoc = glGetUniformLocation(gLightProgramId, "view");
	projLoc = glGetUniformLocation(gLightProgramId, "projection");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// Draws the key light
	glDrawArrays(GL_TRIANGLES, 0, keyLightMesh.nVertices);

	// Deactivates the VAO
	glBindVertexArray(0);
	glUseProgram(0);

	// Swaps the front and back buffers
	glfwSwapBuffers(gWindow);
}

// Destroy the clean up memory
void UDestroyMesh(GLMesh& mesh)
{
	glDeleteVertexArrays(1, &mesh.vao);
	glDeleteBuffers(1, &mesh.vbo);
}
void UDestroyShaderProgram(GLuint programId)
{
	glDeleteProgram(programId);
}

// Boolean function for texture
bool UCreateTexture(const char* filename, GLuint& textureId)
{
	int width, height, channels;
	unsigned char* image = stbi_load(filename, &width, &height, &channels, 0);
	if (image)
	{
		flipImageVertically(image, width, height, channels);

		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);



		// Texture parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (channels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		else if (channels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		else
		{
			cout << "Not implemented to handle image with " << channels << " channels" << endl;
			return false;
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(image);
		glBindTexture(GL_TEXTURE_2D, 0);

		return true;
	}

	return false;
}
void UDestroyTexture(GLuint textureId)
{
	glGenTextures(1, &textureId);
}





// Light cube setup
void UCreateLightMesh(GLightMesh& lightMesh)
{
	// Position and Color data
	GLfloat verts[] = {
		//Positions          //Normals
		// ------------------------------------------------------
		//Back Face          //Negative Z Normal  Texture Coords.
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		//Front Face         //Positive Z Normal
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f, 0.0f,

		//Left Face          //Negative X Normal
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		//Right Face         //Positive X Normal
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		//Bottom Face        //Negative Y Normal
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		//Top Face           //Positive Y Normal
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	const GLuint floatsPerVertex = 3;
	const GLuint floatsPerNormal = 3;
	const GLuint floatsPerUV = 2;

	lightMesh.nVertices = sizeof(verts) / (sizeof(verts[0]) * (floatsPerVertex + floatsPerNormal + floatsPerUV));

	glGenVertexArrays(1, &lightMesh.vao);
	glBindVertexArray(lightMesh.vao);

	// Buffer generators and activators
	glGenBuffers(1, &lightMesh.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, lightMesh.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

	// Strides
	GLint stride = sizeof(float) * (floatsPerVertex + floatsPerNormal + floatsPerUV);

	// Vertex pointers
	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, floatsPerNormal, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * floatsPerVertex));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(sizeof(float) * (floatsPerVertex + floatsPerNormal)));
	glEnableVertexAttribArray(2);
}





