#ifndef WWA_ENGINE_APPLICATION_WINDOW_H
#define WWA_ENGINE_APPLICATION_WINDOW_H

#include <GLFW/glfw3.h>
#include <vulkan/vulkan.h>

#include <string>
#include <vector>

namespace graphics {

class ApplicationWindow {
public:
    ApplicationWindow(std::string name, uint32_t width, uint32_t height);
    ~ApplicationWindow();

    void run() const;

    operator GLFWwindow *() const;

private:
    void createInstance(const std::string& name);
    std::vector<const char*> getRequiredGlfwExtensions() const;
    std::vector<VkExtensionProperties> getAvailableVulkanExtensions() const;
    void listExtensions(const std::vector<const char*>& glfwExt, const std::vector<VkExtensionProperties>& vkExt) const;
    bool areNeccessaryExtAvailable(const std::vector<const char*>& glfwExt, const std::vector<VkExtensionProperties>& vkExt) const;

    uint32_t width, height;
    GLFWwindow *window;
    VkInstance instance;
};

}

#endif //WWA_ENGINE_APPLICATION_WINDOW_H
