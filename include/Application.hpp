/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/


#pragma once
#include <vulkan/vulkan.hpp>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <optional>
#include "Camera.hpp"
#include "Scene.hpp"

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

struct Vertex {
    glm::vec2 pos;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 1> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 1> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        return attributeDescriptions;
    }
};

// Gives the info about the camera and the view plane
struct ViewUBO {
    alignas(8) glm::vec2 iResolution;
    alignas(16) glm::vec3 iViewPlaneParams;
    alignas(16) glm::vec3 iCameraPosition;
    alignas(16) glm::mat4 iCameraMatrix;
};

// Gives the info about the scene (number of triangles and meshes)
struct SceneUBO {
    alignas(4) unsigned int iNumMeshes;
    alignas(4) unsigned int iNumTriangles;
};

// Array of triangles given to the shader
struct TrianglesUBO {
    Triangle *triangles;
};

// Array of meshes given to the shader
struct MeshesUBO {
    Mesh *meshes;
};

class Application {
protected:
    std::string _appName;
    glm::vec2 _windowSize{100, 100};
    GLFWwindow *_window;
    VkInstance _instance;
    VkPhysicalDevice _physicalDevice = VK_NULL_HANDLE;
    VkDevice _device = VK_NULL_HANDLE;
    const std::vector<const char*> _validationLayers = {
            "VK_LAYER_KHRONOS_validation"
    };
    VkDebugUtilsMessengerEXT _debugMessenger;
    VkQueue _graphicsQueue;
    VkSurfaceKHR _surface;
    VkQueue _presentQueue;
    const std::vector<const char*> _deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
    VkSwapchainKHR _swapChain;
    std::vector<VkImage> _swapChainImages;
    VkFormat _swapChainImageFormat;
    VkExtent2D _swapChainExtent{};
    std::vector<VkImageView> _swapChainImageViews;
    VkDescriptorSetLayout _descriptorSetLayout;
    VkPipelineLayout _pipelineLayout;
    VkRenderPass _renderPass;
    VkPipeline _graphicsPipeline;
    std::vector<VkFramebuffer> _swapChainFrameBuffers;
    VkCommandPool _commandPool;
    std::vector<VkCommandBuffer> _commandBuffers;
    const int _MAX_FRAMES_IN_FLIGHT = 2;
    std::vector<VkSemaphore> _imageAvailableSemaphores;
    std::vector<VkSemaphore> _renderFinishedSemaphores;
    std::vector<VkFence> _inFlightFences;
    uint32_t _currentFrame = 0;
    VkDescriptorPool _descriptorPool;
    std::vector<VkDescriptorSet> _descriptorSets;
    VkBuffer _vertexBuffer;
    VkDeviceMemory _vertexBufferMemory;
    VkBuffer _indexBuffer;
    VkDeviceMemory _indexBufferMemory;
    std::vector<VkBuffer> _uniformBuffers;
    std::vector<VkDeviceMemory> _uniformBuffersMemory;
    std::vector<void*> _uniformBuffersMapped;

    std::vector<VkBuffer> _sceneBuffers;
    std::vector<VkDeviceMemory> _sceneBuffersMemory;
    std::vector<void*> _sceneBuffersMapped;

    uint32_t _numTriangles = 1;
    std::vector<VkBuffer> _triangleBuffers;
    std::vector<VkDeviceMemory> _triangleBuffersMemory;
    std::vector<void*> _triangleBuffersMapped;

    uint32_t _numMeshes = 1;
    std::vector<VkBuffer> _meshBuffers;
    std::vector<VkDeviceMemory> _meshBuffersMemory;
    std::vector<void*> _meshBuffersMapped;

    // Screen
    const std::vector<Vertex> _screenVertices = {
            {{-1.f, -1.f}},
            {{1.f, -1.f}},
            {{1.f, 1.f}} ,
            {{-1.f, 1.f}}
    };
    const std::vector<uint16_t> _screenIndices = {
            0, 1, 2,
            2, 3, 0
    };
    // Scene
    Scene *_scene = nullptr;
    // Camera
    const Camera *_camera;

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif
public:
    Application(glm::vec2 windowSize, const std::string &appName, Scene *scene);
    Application(unsigned int width, unsigned int height, const std::string &appName, Scene *scene);
    ~Application();
    void run(std::function<void()> update = nullptr);

    void useCamera(std::size_t idx);
protected:
    void initWindow();
    void initVulkan();
    void createInstance();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSurface();
    void loop(std::function<void()> update);
    void cleanup();
    bool checkValidationLayerSupport();
    void setupDebugMessenger();
    void createSwapChain();
    void createImageViews();
    void createRenderPass();
    void createFrameBuffers();
    void createGraphicsPipeline();
    void createCommandPool();
    void createCommandBuffer();
    void createSyncObjects();
    void createVertexBuffer();
    void createIndexBuffer();
    void createDescriptorSetLayout();
    void createUniformBuffers();
    void updateUniformBuffer(uint32_t currentImage);
    void createDescriptorPool();
    void createDescriptorSets();
    void recreateSwapChain();
    void cleanupSwapChain();
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    [[nodiscard]] std::vector<const char*> getRequiredExtensions() const;
    bool isDeviceSuitable(VkPhysicalDevice device);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    VkShaderModule createShaderModule(const std::vector<char>& code);
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void drawFrame();
};
