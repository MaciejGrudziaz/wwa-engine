#include "ApplicationWindow.h"

#include <stdexcept>
#include <iostream>
#include <algorithm>

namespace graphics {

ApplicationWindow::ApplicationWindow(std::string name, uint32_t width, uint32_t height): width(width), height(height) {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

    createInstance(name);
}

void ApplicationWindow::createInstance(const std::string& name) {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = name.c_str();
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0,0 );
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    auto glfwExtensions = getRequiredGlfwExtensions();

    createInfo.enabledExtensionCount = glfwExtensions.size();
    createInfo.ppEnabledExtensionNames = glfwExtensions.data();
    createInfo.enabledLayerCount = 0;

    auto vulkanExtensions = getAvailableVulkanExtensions();

    listExtensions(glfwExtensions, vulkanExtensions);
    if(!areNeccessaryExtAvailable(glfwExtensions, vulkanExtensions)) {
        throw std::runtime_error("neccessary extensions are not available");
    }
    std::cout << "All neccessary extensions available. Creating instance...\n";

    if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }
    std::cout << "Vulkan instance created\n";
}

std::vector<const char*> ApplicationWindow::getRequiredGlfwExtensions() const {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> result(glfwExtensionCount);
    for(uint32_t i = 0; i < glfwExtensionCount; ++i) {
        result[i] = glfwExtensions[i];
    }

    return result;
}

std::vector<VkExtensionProperties> ApplicationWindow::getAvailableVulkanExtensions() const {
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    return extensions;
}

void ApplicationWindow::listExtensions(const std::vector<const char*> &glfwExt, const std::vector<VkExtensionProperties>& vkExt) const {
    std::cout << "GLFW required extensions:\n";
    for(const char* ext: glfwExt) {
        std::cout << "\t" << ext << "\n";
    }

    std::cout << "Vulkan available extensions:\n";
    for(const auto& ext : vkExt) {
        std::cout << "\t" << ext.extensionName << "\n";
    }
}

bool ApplicationWindow::areNeccessaryExtAvailable(const std::vector<const char*>& glfwExt, const std::vector<VkExtensionProperties>& vkExt) const {
    for(const char* ext : glfwExt) {
        if(std::find_if(vkExt.begin(), vkExt.end(), [&](const VkExtensionProperties& vk) { return std::string(vk.extensionName) == std::string(ext); }) == vkExt.end()) {
            std::cout << "Extension " << ext << " not available for Vulkan\n";
            return false;
        }
    }
    return true;
}

ApplicationWindow::~ApplicationWindow() {
    vkDestroyInstance(instance, nullptr);
    glfwDestroyWindow(window);
    glfwTerminate();
}

void ApplicationWindow::run() const {
    while(!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

ApplicationWindow::operator GLFWwindow *() const {
    return window;
}

}
