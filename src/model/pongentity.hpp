#ifndef PONGENTITY_HPP
#define PONGENTITY_HPP

#include <string>
#include "transform2d.hpp"

class pongentity{

	public:
		std::string name;
		transform2D transform;

	public:
		pongentity(std::string name = "", transform2D transform = transform2D()) : name(name), transform(transform) {}
		
};

#endif // PONGENTITY_HPP