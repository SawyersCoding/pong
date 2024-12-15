#include "pongview.hpp"
#include <glm/gtx/string_cast.hpp>

pongview::pongview(int width, int height, int score_height, float paddle_width_left, float paddle_height_left, float paddle_width_right, float paddle_height_right, float ball_size)
{
	px_width = width * PX_PER_UNIT;
	px_height = height * PX_PER_UNIT;
	px_score_height = score_height * PX_PER_UNIT;

	dy = (float)height - score_height / 2.0f;
	dx_left = width / 3.0f;
	dx_right = 2.0f * width / 3.0f;

	// Initialize GLFW
	if(!glfwInit()){
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Set OpenGL version to 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	window = glfwCreateWindow(px_width, px_height, "Pong", NULL, NULL);
	if(window == NULL){
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);
    // Ensure the window is focused
    glfwFocusWindow(window);
	// Set callback functions
	glfwSetFramebufferSizeCallback(window, pongview::framebuffer_size_callback);

	// Load OpenGL function pointers
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cerr << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Set viewport
	glViewport(0, 0, px_width, px_height);

	// Initialize shader
	pong_shader = new shader("src/view/shader/vertexshader.glsl", "src/view/shader/fragmentshader.glsl");
	single_texture_shader = new shader("src/view/shader/singletexturevertexshader.glsl", "src/view/shader/singletexturefragmentshader.glsl");

	dview = new digitview(score_height * DIGIT_HEIGHT_FACTOR);
	bview = new ballview(ball_size);
	pview = new paddleview(paddle_width_left, paddle_height_left);

	view = glm::lookAt(CAMERA_POS, CAMERA_TARGET, CAMERA_UP);
	projection = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.1f, 100.0f);

	pong_shader->use();
	pong_shader->set_mat4("view", view);
	pong_shader->set_mat4("projection", projection);
	single_texture_shader->use();
	single_texture_shader->set_mat4("view", view);
	single_texture_shader->set_mat4("projection", projection);
}

pongview::~pongview()
{
	delete dview;
	delete bview;
	delete pview;
	delete pong_shader;
	delete single_texture_shader;
	glfwTerminate();
}

void pongview::render_pong(int score_left, int score_right, float bx, float by, float lx, float ly, float rx, float ry)
{
	// Clear screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	dview->render_digit(single_texture_shader, score_left, dx_left, dy);
	dview->render_digit(single_texture_shader, score_right, dx_right, dy);
	bview->render_ball(pong_shader, bx, by);
	pview->render_paddle(pong_shader, lx, ly);
	pview->render_paddle(pong_shader, rx, ry);

	// Swap buffers
	glfwSwapBuffers(window);
}

GLFWwindow *pongview::get_window()
{
	return window;
}

void pongview::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}
