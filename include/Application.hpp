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
#include <chrono>
#include <functional>

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    vk::SurfaceCapabilitiesKHR capabilities;
    std::vector<vk::SurfaceFormatKHR> formats;
    std::vector<vk::PresentModeKHR> presentModes;
};

struct Vertex {
    glm::vec2 pos;

    static vk::VertexInputBindingDescription getBindingDescription() {
        vk::VertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = vk::VertexInputRate::eVertex;

        return bindingDescription;
    }

    static std::array<vk::VertexInputAttributeDescription, 1> getAttributeDescriptions() {
        std::array<vk::VertexInputAttributeDescription, 1> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = vk::Format::eR32G32Sfloat;
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

// Gives the info about the scene (number of triangles and meshes and bool if scene dirty)
struct SceneUBO {
    alignas(4) unsigned int iNumMeshes;
    alignas(4) unsigned int iNumTriangles;
    alignas(4) unsigned int iSceneChanged;
    alignas(4) unsigned int iSkyboxEnabled;
    alignas(4) unsigned int iFrameIndex;
};

class Application {
protected:
    std::string _appName;
    glm::vec2 _windowSize{100, 100};
    GLFWwindow *_window;
    vk::Instance _instance;
    vk::PhysicalDevice _physicalDevice = VK_NULL_HANDLE;
    vk::Device _device = VK_NULL_HANDLE;
    const std::vector<const char*> _validationLayers = {
            "VK_LAYER_KHRONOS_validation"
    };
    vk::DebugUtilsMessengerEXT _debugMessenger;
    vk::Queue _graphicsQueue;
    vk::SurfaceKHR _surface;
    vk::Queue _presentQueue;
    const std::vector<const char*> _deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
    vk::SwapchainKHR _swapChain;
    std::vector<vk::Image> _swapChainImages;
    vk::Format _swapChainImageFormat;
    vk::Extent2D _swapChainExtent{};
    std::vector<vk::ImageView> _swapChainImageViews;
    vk::DescriptorSetLayout _descriptorSetLayout;
    vk::PipelineLayout _pipelineLayout;
    vk::Sampler _textureSampler;
    vk::RenderPass _renderPass;
    vk::Pipeline _graphicsPipeline;
    std::vector<vk::Framebuffer> _swapChainFrameBuffers;
    vk::CommandPool _commandPool;
    std::vector<vk::CommandBuffer> _commandBuffers;
    const std::size_t MAX_FRAMES_IN_FLIGHT = 1;
    std::vector<vk::Semaphore> _imageAvailableSemaphores;
    std::vector<vk::Semaphore> _renderFinishedSemaphores;
    std::vector<vk::Fence> _inFlightFences;
    uint32_t _currentFrame = 0;
    std::size_t _frameIndex = 0;
    vk::DescriptorPool _descriptorPool;
    std::vector<vk::DescriptorSet> _descriptorSets;
    std::size_t _lastFrameTime = 0;
    vk::Buffer _screenVertexBuffer;
    vk::DeviceMemory _screenVertexBufferMemory;
    vk::Buffer _screenIndexBuffer;
    vk::DeviceMemory _screenIndexBufferMemory;
    std::vector<vk::Buffer> _uniformBuffers;
    std::vector<vk::DeviceMemory> _uniformBuffersMemory;
    std::vector<void*> _uniformBuffersMapped;

    std::vector<vk::Buffer> _sceneBuffers;
    std::vector<vk::DeviceMemory> _sceneBuffersMemory;
    std::vector<void*> _sceneBuffersMapped;

    std::size_t _numTriangles = 1;
    std::vector<vk::Buffer> _triangleBuffers;
    std::vector<vk::DeviceMemory> _triangleBuffersMemory;
    std::vector<void*> _triangleBuffersMapped;

    std::size_t _numMeshes = 1;
    std::vector<vk::Buffer> _meshBuffers;
    std::vector<vk::DeviceMemory> _meshBuffersMemory;
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

    std::vector<Triangle> _triangles;
    std::vector<Mesh> _meshes;

    bool _sceneChanged = true;
public:
    Application(glm::vec2 windowSize, const std::string &appName, Scene *scene);
    Application(unsigned int width, unsigned int height, const std::string &appName, Scene *scene);
    ~Application();
    void run(const std::function<void()>& update = nullptr);

    void useCamera(std::size_t idx);
    void updateScene();
protected:
    void initWindow();
    void initVulkan();
    void createInstance();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSurface();
    void loop(const std::function<void()>& update);
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
    QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice device);
    [[nodiscard]] std::vector<const char*> getRequiredExtensions() const;
    bool isDeviceSuitable(vk::PhysicalDevice device);
    bool checkDeviceExtensionSupport(vk::PhysicalDevice device);
    SwapChainSupportDetails querySwapChainSupport(vk::PhysicalDevice device);
    static vk::SurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats);
    static vk::PresentModeKHR chooseSwapPresentMode(const std::vector<vk::PresentModeKHR>& availablePresentModes);
    vk::Extent2D chooseSwapExtent(const vk::SurfaceCapabilitiesKHR& capabilities);
    vk::ShaderModule createShaderModule(const std::vector<char>& code);
    void recordCommandBuffer(vk::CommandBuffer commandBuffer, uint32_t imageIndex);
    void createBuffer(vk::DeviceSize size, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags properties, vk::Buffer& buffer, vk::DeviceMemory& bufferMemory);
    void copyBuffer(vk::Buffer srcBuffer, vk::Buffer dstBuffer, vk::DeviceSize size);
    uint32_t findMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlags properties);
    void drawFrame();
};
