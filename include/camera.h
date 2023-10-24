#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <shader.h>

class Camera {
public:
	// Camera constructor to set up initial values
	Camera(int width, int height, glm::vec3 position);

	// Updates and exports the camera matrix to the Vertex Shader
	void UpdateMatrix(float fov, float near_plane, float far_plane, Shader& shader, const char* uniform);
	
    // Handles camera inputs
	void Inputs(GLFWwindow* window);

private:
    // Stores the main vectors of the camera
	glm::vec3 position_;
	glm::vec3 orientation_ = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up_vector_ = glm::vec3(0.0f, 1.0f, 0.0f);

	// Prevents the camera from jumping around when first clicking left click
	bool first_click_ = true;

	// Stores the width and height of the window
	int width_;
	int height_;

	// Adjust the speed of the camera and it's sensitivity when looking around
	float camera_speed_ = 0.1f;
	float camrea_sensitivity_ = 100.0f;
};
