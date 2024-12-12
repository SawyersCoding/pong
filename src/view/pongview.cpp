#include "pongview.hpp"
#include <glm/gtx/string_cast.hpp>

pongview::pongview(int width, int height, int score_height, float paddle_width_left, float paddle_height_left, float paddle_width_right, float paddle_height_right, float ball_size)
{
	px_width = width * px_per_unit;
	px_height = height * px_per_unit;
	px_score_height = score_height * px_per_unit;

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

	bview = new ballview(ball_size);
	pview = new paddleview(paddle_width_left, paddle_height_left);

	glEnable(GL_DEPTH_TEST);

	view = glm::lookAt(camera_pos, camera_target, camera_up);
	projection = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.1f, 100.0f);
	// projection = glm::mat4(1.0f);

	pong_shader->use();
	pong_shader->set_mat4("view", view);
	pong_shader->set_mat4("projection", projection);
}

pongview::~pongview()
{
	delete bview;
	delete pview;
	delete pong_shader;
	glfwTerminate();
}

void pongview::render_pong(int score_left, int score_right, float bx, float by, float lx, float ly, float rx, float ry)
{
	// Clear screen
	glClearColor(0.15f, 0.15f, 0.15f, 1.0f); // black background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
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
