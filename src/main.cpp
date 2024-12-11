#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include "model/pong.hpp"
#include "model/pongsettings.hpp"

int main(){
	
	// Initialize pong model
	int score_left, score_right;
	float bx, by, lx, ly, rx, ry;
	float dt = 0.01f;
	pongsettings settings;
	pong p(settings);

	std::cout << "Pong game started!" << std::endl;
	while(p.get_state() != pong::GAMEOVER){
		// Print everything about the game
		p.get_positions(bx, by, lx, ly, rx, ry);
		score_left = p.get_score_left();
		score_right = p.get_score_right();
		std::cout << "Ball: (" << bx << ", " << by << ")" << std::endl;
		std::cout << "Paddle left: (" << lx << ", " << ly << ")" << std::endl;
		std::cout << "Paddle right: (" << rx << ", " << ry << ")" << std::endl;
		std::cout << "Score: " << score_left << " - " << score_right << std::endl;
		std::cout << std::endl;

		// Sleep for 1 second before next update
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		p.update(dt);
	}

	// Initialize pong controller

	// Initialize pong view

	// Game loop

	// Clean up

	return 0;
}