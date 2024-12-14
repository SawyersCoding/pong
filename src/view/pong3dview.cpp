#include "pong3dview.hpp"

pong3dview::pong3dview(int width, int height, int score_height, float paddle_width_left, float paddle_height_left, float paddle_width_right, float paddle_height_right, float ball_size)
{
	px_width = width * PX_PER_UNIT;
	px_height = height * PX_PER_UNIT;

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
	glfwSetFramebufferSizeCallback(window, pong3dview::framebuffer_size_callback);

	// Load OpenGL function pointers
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cerr << "Failed to initialize GLAD" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Set viewport
	glViewport(0, 0, px_width, px_height);

	glEnable(GL_DEPTH_TEST);

	// Initialize shader
	pong_shader = new shader("src/view/shader/vertexshader.glsl", "src/view/shader/fragmentshader.glsl");
	digit_shader = new shader("src/view/shader/digitvertexshader.glsl", "src/view/shader/digitfragmentshader.glsl");	

	// Initialize views
	pview = new paddle3dview(paddle_width_left, paddle_height_left);
	bview = new ball3dview(ball_size);
	dview = new digitview(score_height * DIGIT_HEIGHT_FACTOR);

	camera_pos = glm::vec3(-0.4f * width, width / 4.0f, 10.0f);
	camera_target = glm::vec3(width, height / 2.0f, 0.0f);
	view = glm::lookAt(camera_pos, camera_target, CAMERA_UP);
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 2.0f * width);

	pong_shader->use();
	pong_shader->set_mat4("projection", projection);
	pong_shader->set_mat4("view", view);

	ui_projection = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.1f, 100.0f);
	ui_view = glm::lookAt(UI_CAMERA_POS, UI_CAMERA_TARGET, UI_CAMERA_UP);

	digit_shader->use();
	digit_shader->set_mat4("projection", ui_projection);
	digit_shader->set_mat4("view", ui_view);
}

pong3dview::~pong3dview()
{
	delete pong_shader;
	delete pview;
	delete bview;
	glfwTerminate();
}

void pong3dview::render_pong(int score_left, int score_right, float bx, float by, float lx, float ly, float rx, float ry)
{
	// Clear screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	pview->render_paddle(pong_shader, lx, ly);
	pview->render_paddle(pong_shader, rx, ry);
	bview->render_ball(pong_shader, bx, by);

	dview->render_digit(digit_shader, score_left, dx_left, dy);
	dview->render_digit(digit_shader, score_right, dx_right, dy);

	glfwSwapBuffers(window);
}

GLFWwindow *pong3dview::get_window()
{
	return window;
}

void pong3dview::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}