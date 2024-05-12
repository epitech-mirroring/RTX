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
    std::optional<uint32_t> graphicsAndComputeFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsAndComputeFamily.has_value() && presentFamily.has_value();
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

struct InputUBO {
    alignas(8) glm::vec2 iResolution;
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
    alignas(4) unsigned int iFrameCount;
};

class Application {
protected:
    std::string _appName;
    bool _running;
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
    vk::Queue _computeQueue;
    const std::vector<const char*> _deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME,
#ifdef __APPLE__
            "VK_KHR_portability_subset",
#endif
    };
    vk::SwapchainKHR _swapChain;
    std::vector<vk::Image> _swapChainImages;
    vk::Format _swapChainImageFormat;
    vk::Extent2D _swapChainExtent{};
    std::vector<vk::ImageView> _swapChainImageViews;
    vk::DescriptorSetLayout _screenDescriptorSetLayout;
    vk::DescriptorSetLayout _computeDescriptorSetLayout;
    vk::PipelineLayout _pipelineLayout;
    vk::PipelineLayout _computePipelineLayout;
    vk::RenderPass _renderPass;
    vk::Pipeline _graphicsPipeline;
    vk::Pipeline _computePipeline;
    std::vector<vk::Framebuffer> _swapChainFrameBuffers;
    vk::CommandPool _commandPool;
    std::vector<vk::CommandBuffer> _commandBuffers;
    std::vector<vk::CommandBuffer> _computeCommandBuffers;
    const std::size_t MAX_FRAMES_IN_FLIGHT = 1;
    std::vector<vk::Semaphore> _imageAvailableSemaphores;
    std::vector<vk::Semaphore> _renderFinishedSemaphores;
    std::vector<vk::Fence> _inFlightFences;
    std::vector<vk::Fence> _computeInFlightFences;
    std::vector<vk::Semaphore> _computeFinishedSemaphores;
    uint32_t _currentFrame = 0;
    std::size_t _frameIndex = 0;
    vk::DescriptorPool _screenDescriptorPool;
    std::vector<vk::DescriptorSet> _screenDescriptorSets;
    vk::DescriptorPool _computeDescriptorPool;
    std::vector<vk::DescriptorSet> _computeDescriptorSets;
    std::size_t _lastFrameTime = 0;
    vk::Buffer _screenVertexBuffer;
    vk::DeviceMemory _screenVertexBufferMemory;
    vk::Buffer _screenIndexBuffer;
    vk::DeviceMemory _screenIndexBufferMemory;
    vk::Image _textureImage;
    vk::ImageView _textureImageView;
    vk::DeviceMemory _textureImageMemory;
    // Compute shader
    // Input image
    vk::Image _computeInputImage;
    vk::ImageView _computeInputImageView;
    vk::DeviceMemory _computeInputImageMemory;
    // Output image
    vk::Image _computeOutputImage;
    vk::ImageView _computeOutputImageView;
    vk::DeviceMemory _computeOutputImageMemory;


    std::vector<vk::Buffer> _inputBuffers;
    std::vector<vk::DeviceMemory> _inputBuffersMemory;
    std::vector<void*> _inputBuffersMapped;

    std::vector<vk::Buffer> _viewBuffers;
    std::vector<vk::DeviceMemory> _viewBuffersMemory;
    std::vector<void*> _viewBuffersMapped;

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
    std::size_t _frameCount = 0;

    std::size_t _mainTextureTotalWidth = 0;
    std::size_t _mainTextureMaxHeight = 0;

    vk::Image _mainTextureImage;
    vk::ImageView _mainTextureImageView;
    vk::DeviceMemory _mainTextureImageMemory;

    vk::Sampler _mainTextureSampler;
public:
    Application(glm::vec2 windowSize, const std::string &appName, Scene *scene);
    Application(unsigned int width, unsigned int height, const std::string &appName, Scene *scene);
    ~Application();
    void run(const std::function<void()>& update = nullptr);

    void useCamera(std::size_t idx);
    void updateScene();
    [[nodiscard]] std::size_t getFrameIndex() const;
    vk::Image &getCurrentImage();
    void screenshot(const std::string &filename);
    void stop();
protected:
    void computeMainTextureSize();
    void createMainTexture();
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
    void createImages();
    void createRenderPass();
    void createFrameBuffers();
    void createGraphicsPipeline();
    void createComputePipeline();
    void createCommandPool();
    void createCommandBuffer();
    void createSyncObjects();
    void createVertexBuffer();
    void createIndexBuffer();
    void createDescriptorSetLayout();
    void createComputeDescriptorSetLayout();
    void createUniformBuffers();
    void updateUniformBuffer(uint32_t currentImage);
    void updateComputeUniformBuffer(uint32_t currentImage);
    void createDescriptorPool();
    void createDescriptorSets();
    void createComputeDescriptorPool();
    void createComputeDescriptorSets();
    void recreateSwapChain();
    void cleanupSwapChain();
    void createComputeCommandBuffers();
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
    void recordComputeCommandBuffer(vk::CommandBuffer commandBuffer);
    void createBuffer(vk::DeviceSize size, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags properties, vk::Buffer& buffer, vk::DeviceMemory& bufferMemory);
    void copyBuffer(vk::Buffer srcBuffer, vk::Buffer dstBuffer, vk::DeviceSize size);
    uint32_t findMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlags properties);
    void drawFrame();
    vk::CommandBuffer beginSingleTimeCommands();

    void createImage(uint32_t width, uint32_t height, vk::Format format, vk::ImageTiling tiling, vk::ImageUsageFlags usage, vk::MemoryPropertyFlags properties, vk::Image& image, vk::DeviceMemory& imageMemory);
    void transitionImageLayout(vk::Image image, vk::Format format, vk::ImageLayout oldLayout, vk::ImageLayout newLayout);
};
