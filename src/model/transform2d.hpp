#pragma once

struct transform2D{

	public:
	const static float X_DEFAULT = 0.0f;
	const static float Y_DEFAULT = 0.0f;
	const static float ZROT_DEG_DEFAULT = 0.0f;
	const static float WIDTH_DEFAULT = 1.0f;
	const static float HEIGHT_DEFAULT = 1.0f;
	const static float XVELOCITY_DEFAULT = 0.0f;
	const static float YVELOCITY_DEFAULT = 0.0f;

	float x;
	float y;
	float zrot_deg;
	float width;
	float height;
	float xvelocity;
	float yvelocity;
	
	transform2D(float x = X_DEFAULT, float y = Y_DEFAULT, float zrot_deg = ZROT_DEG_DEFAULT, float width = WIDTH_DEFAULT, float height = HEIGHT_DEFAULT, float xvelocity = XVELOCITY_DEFAULT, float yvelocity = YVELOCITY_DEFAULT) : x(x), y(y), zrot_deg(zrot_deg), width(width), height(height), xvelocity(xvelocity), yvelocity(yvelocity) {}
	
};