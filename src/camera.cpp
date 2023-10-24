#include <camera.h>

Camera::Camera(int width, int height, glm::vec3 position) {
	width_ = width;
	height_ = height;
	position_ = position;
}

void Camera::UpdateMatrix(float fov, float near_plane, float far_plane, Shader& shader, 
                            const char* uniform) {
	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	view = glm::lookAt(position_, position_ + orientation_, up_vector_);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(fov), (float) (width_ / height_), near_plane, 
                                  far_plane);

	// Exports the camera matrix to the Vertex Shader
	glUniformMatrix4fv(glGetUniformLocation(shader.id, uniform), 1, GL_FALSE, 
                        glm::value_ptr(projection * view));
}

void Camera::Inputs(GLFWwindow* window) {
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position_ += camera_speed_ * orientation_;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position_ += camera_speed_ * -glm::normalize(glm::cross(orientation_, up_vector_));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position_ += camera_speed_ * -orientation_;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position_ += camera_speed_ * glm::normalize(glm::cross(orientation_, up_vector_));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		position_ += camera_speed_ * up_vector_;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		position_ += camera_speed_ * -up_vector_;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		camera_speed_ = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE) {
		camera_speed_ = 0.1f;
	}

	// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (first_click_) {
			glfwSetCursorPos(window, (width_ / 2), (height_ / 2));
			first_click_ = false;
		}

		// Stores the coordinates of the cursor
		double mouse_x;
		double mouse_y;
        
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouse_x, &mouse_y);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle 
        // of the screen and then "transforms" them into degrees 
		float rot_x = camrea_sensitivity_ * (float)(mouse_y - (height_ / 2)) / height_;
		float rot_y = camrea_sensitivity_ * (float)(mouse_x - (width_ / 2)) / width_;

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 new_orientation = glm::rotate(orientation_, glm::radians(-rot_x), 
                                    glm::normalize(glm::cross(orientation_, up_vector_)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(new_orientation, up_vector_) - glm::radians(90.0f)) 
            <= glm::radians(85.0f)) {
			orientation_ = new_orientation;
		}

		// Rotates the Orientation left and right
		orientation_ = glm::rotate(orientation_, glm::radians(-rot_y), up_vector_);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		glfwSetCursorPos(window, (width_ / 2), (height_ / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		first_click_ = true;
	}
}
