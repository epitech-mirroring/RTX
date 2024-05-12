/*
** EPITECH PROJECT, 2024
** RTX
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Application.hpp"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <thread>
#include <utility>

QueueFamilyIndices Application::findQueueFamilies(vk::PhysicalDevice device)
{
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    device.getQueueFamilyProperties(&queueFamilyCount, nullptr);

    std::vector<vk::QueueFamilyProperties> queueFamilies(queueFamilyCount);
    device.getQueueFamilyProperties(&queueFamilyCount, queueFamilies.data());


    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        vk::Bool32 presentSupport = false;
        if (device.getSurfaceSupportKHR(i, _surface, &presentSupport) != vk::Result::eSuccess) {
            throw std::runtime_error("Failed to get surface support!");
        }
        if ((queueFamily.queueFlags & vk::QueueFlagBits::eGraphics) && (queueFamily.queueFlags & vk::QueueFlagBits::eCompute)) {
            indices.graphicsAndComputeFamily = i;
        }
        if (presentSupport) {
            indices.presentFamily = i;
        }
        if (indices.isComplete()) {
            break;
        }

        i++;
    }

    return indices;
}

bool Application::isDeviceSuitable(vk::PhysicalDevice device)
{
    QueueFamilyIndices indices = findQueueFamilies(device);

    bool extensionsSupported = checkDeviceExtensionSupport(device);

    bool swapChainAdequate = false;
    if (extensionsSupported) {
        SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }

    return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

bool Application::checkDeviceExtensionSupport(vk::PhysicalDevice device) {
    uint32_t extensionCount;
    if (device.enumerateDeviceExtensionProperties(nullptr, &extensionCount, nullptr) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to enumerate device extension properties!");
    }

    std::vector<vk::ExtensionProperties> availableExtensions(extensionCount);
    if (device.enumerateDeviceExtensionProperties(nullptr, &extensionCount, availableExtensions.data()) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to enumerate device extension properties!");
    }

    std::set<std::string> requiredExtensions(_deviceExtensions.begin(), _deviceExtensions.end());

    for (const auto& extension : availableExtensions) {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();
}

static VKAPI_ATTR vk::Bool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData) {

    (void) messageType;
    (void) pUserData;
    if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT ||
        messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
        std::cerr << pCallbackData->pMessage << std::endl;

    return vk::False;
}

static vk::Result createDebugUtilsMessengerEXT(vk::Instance instance, const vk::DebugUtilsMessengerCreateInfoEXT* pCreateInfo, const vk::AllocationCallbacks* pAllocator, vk::DebugUtilsMessengerEXT* pDebugMessenger)
{
    auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(instance.getProcAddr("vkCreateDebugUtilsMessengerEXT"));
    if (func != nullptr) {
        return vk::Result(func(instance, reinterpret_cast<const VkDebugUtilsMessengerCreateInfoEXT*>(pCreateInfo), reinterpret_cast<const VkAllocationCallbacks*>(pAllocator), reinterpret_cast<VkDebugUtilsMessengerEXT*>(pDebugMessenger)));
    } else {
        return vk::Result::eErrorExtensionNotPresent;
    }
}

void destroyDebugUtilsMessengerEXT(vk::Instance instance, vk::DebugUtilsMessengerEXT debugMessenger, const vk::AllocationCallbacks *pAllocator) {
    auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(instance.getProcAddr("vkDestroyDebugUtilsMessengerEXT"));
    if (func != nullptr) {
        func(instance, debugMessenger,
             reinterpret_cast<const VkAllocationCallbacks *>(pAllocator));
    }
}

static void populateDebugMessengerCreateInfo(vk::DebugUtilsMessengerCreateInfoEXT& createInfo) {
    createInfo = vk::DebugUtilsMessengerCreateInfoEXT();
    createInfo.sType = vk::StructureType::eDebugUtilsMessengerCreateInfoEXT;
    createInfo.messageSeverity = vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError;
    createInfo.messageType = vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance;
    createInfo.pfnUserCallback = debugCallback;
}

static std::vector<char> readFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file!");
    }
    std::size_t fileSize = (std::size_t) file.tellg();
    std::vector<char> buffer(fileSize);
    file.seekg(0);
    file.read(buffer.data(), (long) fileSize);
    file.close();

    return buffer;
}

Application::Application(glm::vec2 windowSize, const std::string &appName, Scene *scene)
{
    _running = false;
    _windowSize = windowSize;
    _appName = appName;
    _window = nullptr;
    _instance = nullptr;
    _debugMessenger = nullptr;
    _physicalDevice = VK_NULL_HANDLE;
    _device = VK_NULL_HANDLE;
    _surface = VK_NULL_HANDLE;
    _swapChain = VK_NULL_HANDLE;
    _graphicsQueue = VK_NULL_HANDLE;
    _presentQueue = VK_NULL_HANDLE;
    _swapChainImageFormat = vk::Format::eUndefined;
    _pipelineLayout = VK_NULL_HANDLE;
    _renderPass = VK_NULL_HANDLE;
    _graphicsPipeline = VK_NULL_HANDLE;
    _commandPool = VK_NULL_HANDLE;
    _screenVertexBuffer = VK_NULL_HANDLE;
    _screenVertexBufferMemory = VK_NULL_HANDLE;
    _screenIndexBuffer = VK_NULL_HANDLE;
    _screenIndexBufferMemory = VK_NULL_HANDLE;
    _scene = scene;
    _camera = &scene->getMainCamera();
    _numMeshes = 0;
    _numTriangles = 0;
    for (auto mesh : _scene->getObjects()) {
        _numTriangles+=mesh->getTriangles().size();
        _numMeshes++;
    }
    _screenDescriptorSetLayout = VK_NULL_HANDLE;
    _screenDescriptorPool = VK_NULL_HANDLE;
    _frameCount = 0;
}

Application::Application(unsigned int width, unsigned int height, const std::string &appName, Scene *scene)
{
    _running = false;
    _windowSize = glm::vec2(width, height);
    _appName = appName;
    _window = nullptr;
    _instance = nullptr;
    _debugMessenger = nullptr;
    _physicalDevice = VK_NULL_HANDLE;
    _device = VK_NULL_HANDLE;
    _surface = VK_NULL_HANDLE;
    _swapChain = VK_NULL_HANDLE;
    _graphicsQueue = VK_NULL_HANDLE;
    _presentQueue = VK_NULL_HANDLE;
    _swapChainImageFormat = vk::Format::eUndefined;
    _pipelineLayout = VK_NULL_HANDLE;
    _renderPass = VK_NULL_HANDLE;
    _graphicsPipeline = VK_NULL_HANDLE;
    _commandPool = VK_NULL_HANDLE;
    _screenVertexBuffer = VK_NULL_HANDLE;
    _screenVertexBufferMemory = VK_NULL_HANDLE;
    _screenIndexBuffer = VK_NULL_HANDLE;
    _screenIndexBufferMemory = VK_NULL_HANDLE;
    _scene = scene;
    _camera = &scene->getMainCamera();
    _numMeshes = 0;
    _numTriangles = 0;
    for (auto mesh : _scene->getObjects()) {
        _numTriangles+=mesh->getTriangles().size();
        _numMeshes++;
    }
    _frameCount = 0;

    for (const auto mesh : _scene->getObjects()) {
        std::size_t start_idx = _triangles.size();
        glm::vec3 boundingBoxMax = {0, 0, 0};
        glm::vec3 boundingBoxMin = {0, 0, 0};
        _triangles.reserve(_triangles.size() + mesh->getTriangles().size());
        for (const auto &triangle : mesh->getTriangles()) {
            _triangles.push_back(triangle);
        }
        std::size_t end_idx = _triangles.size();
        Mesh m{};
        m.startIdx = start_idx;
        m.endIdx = end_idx;
        m.boundingBoxMax = boundingBoxMax;
        m.boundingBoxMin = boundingBoxMin;
        m.transform = mesh->getTransform().getTransformationMatrix();
        RaytracingMaterial material{};
        material.color = mesh->getMaterial().getColor();
        material.emission = mesh->getMaterial().getEmission();
        material.emissionIntensity = (float) mesh->getMaterial().getBrightness();
        material.roughness = (float) mesh->getMaterial().getRoughness();
        material.transparency = (float) mesh->getMaterial().getTransparency();
        material.refractionIndex = (float) mesh->getMaterial().getRefractionIndex();
        material.hasCheckerPattern = mesh->getMaterial().hasCheckerPattern();
        m.material = material;

        _meshes.push_back(m);
    }
    _screenDescriptorSetLayout = VK_NULL_HANDLE;
    _screenDescriptorPool = VK_NULL_HANDLE;
}

void Application::run(const std::function<void()>& update)
{
    _running = true;
    initWindow();
    initVulkan();
    loop(update);
    cleanup();
}

void Application::initWindow()
{
    if (glfwInit() == GLFW_FALSE) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    _window = glfwCreateWindow((int) _windowSize.x, (int) _windowSize.y, _appName.c_str(), nullptr, nullptr);
    if (_window == nullptr) {
        throw std::runtime_error("Failed to create window");
    }
}

void Application::initVulkan()
{
    createInstance();
    setupDebugMessenger();
    createSurface();
    pickPhysicalDevice();
    createLogicalDevice();
    createSwapChain();
    createImageViews();
    createImages();
    createRenderPass();
    createDescriptorSetLayout();
    createComputeDescriptorSetLayout();
    createGraphicsPipeline();
    createComputePipeline();
    createFrameBuffers();
    createCommandPool();
    createVertexBuffer();
    createIndexBuffer();
    createUniformBuffers();
    createDescriptorPool();
    createComputeDescriptorPool();
    createDescriptorSets();
    createComputeDescriptorSets();
    createCommandBuffer();
    createComputeCommandBuffers();
    createSyncObjects();
}

std::vector<const char*> Application::getRequiredExtensions() const
{
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

#ifndef NDEBUG
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif
#ifdef __APPLE__
    extensions.push_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
    extensions.push_back(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
#endif

    return extensions;
}

void Application::createInstance()
{
    if (!checkValidationLayerSupport()) {
#ifndef NDEBUG
        throw std::runtime_error("Validation layers requested, but not available!");
#endif
    }

    vk::ApplicationInfo appInfo;
    appInfo.sType = vk::StructureType::eApplicationInfo;
    appInfo.pApplicationName = _appName.c_str();
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_MAKE_VERSION(1, 0, 0);

    vk::InstanceCreateInfo createInfo;
    createInfo.sType = vk::StructureType::eInstanceCreateInfo;
    createInfo.pApplicationInfo = &appInfo;

    createInfo.flags |= vk::InstanceCreateFlagBits::eEnumeratePortabilityKHR;
    auto extensions = getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    vk::DebugUtilsMessengerCreateInfoEXT debugCreateInfo;
#ifndef NDEBUG
    createInfo.enabledLayerCount = static_cast<uint32_t>(_validationLayers.size());
    createInfo.ppEnabledLayerNames = _validationLayers.data();

    populateDebugMessengerCreateInfo(debugCreateInfo);
    createInfo.pNext = (vk::DebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;
#else
    createInfo.enabledLayerCount = 0;

    createInfo.pNext = nullptr;
#endif

    vk::Result result = vk::createInstance(&createInfo, nullptr, &_instance);
    if (result != vk::Result::eSuccess) {
        if (result == vk::Result::eErrorIncompatibleDriver) {
            throw std::runtime_error("Failed to create Vulkan instance: VK_ERROR_INCOMPATIBLE_DRIVER");
        } else {
            throw std::runtime_error("Failed to create Vulkan instance: Unknown error");
        }
    }
}

void Application::pickPhysicalDevice()
{
    uint32_t deviceCount = 0;
    if (_instance.enumeratePhysicalDevices(&deviceCount, nullptr) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to find GPUs with Vulkan support!");
    }

    if (deviceCount == 0) {
        throw std::runtime_error("Failed to find GPUs with Vulkan support!");
    }
    std::vector<vk::PhysicalDevice> devices(deviceCount);
    if (_instance.enumeratePhysicalDevices(&deviceCount, devices.data()) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to find GPUs with Vulkan support!");
    }
    std::size_t score = 0;
    for (const auto& device : devices) {
        if (isDeviceSuitable(device)) {
            std::size_t newScore = 0;

            vk::PhysicalDeviceProperties deviceProperties;
            device.getProperties(&deviceProperties);
            vk::PhysicalDeviceFeatures deviceFeatures;
            device.getFeatures(&deviceFeatures);

            if (deviceProperties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu) {
                newScore += 1000;
            }
            newScore += deviceProperties.limits.maxImageDimension2D;

            if (!deviceFeatures.geometryShader) {
                newScore = 0;
            }

            if (newScore > score || _physicalDevice == VK_NULL_HANDLE) {
                _physicalDevice = device;
                score = newScore;
            }
        }
    }
    if (_physicalDevice == VK_NULL_HANDLE) {
        throw std::runtime_error("Failed to find a suitable GPU!");
    }
}

void Application::createLogicalDevice()
{
    float queuePriority = 1.0f;
    QueueFamilyIndices indices = findQueueFamilies(_physicalDevice);
    std::vector<vk::DeviceQueueCreateInfo> queueCreateInfos;
    vk::PhysicalDeviceFeatures deviceFeatures;
    vk::DeviceCreateInfo createInfo;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsAndComputeFamily.value(), indices.presentFamily.value()};

    for (uint32_t queueFamily : uniqueQueueFamilies) {
        vk::DeviceQueueCreateInfo queueCreateInfo;
        queueCreateInfo.sType = vk::StructureType::eDeviceQueueCreateInfo;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.push_back(queueCreateInfo);
    }
    createInfo.sType = vk::StructureType::eDeviceCreateInfo;
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.pEnabledFeatures = &deviceFeatures;
    createInfo.enabledExtensionCount = static_cast<uint32_t>(_deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = _deviceExtensions.data();

    createInfo.enabledLayerCount = 0;
    if (_physicalDevice.createDevice(&createInfo, nullptr, &_device) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to create logical device!");
    }
    _device.getQueue(indices.graphicsAndComputeFamily.value(), 0, &_graphicsQueue);
    _device.getQueue(indices.presentFamily.value(), 0, &_presentQueue);
    _device.getQueue(indices.graphicsAndComputeFamily.value(), 0, &_computeQueue);
}

void Application::createSurface()
{
    VkSurfaceKHR surface = VkSurfaceKHR(_surface);
    if (glfwCreateWindowSurface(VkInstance(_instance), _window, nullptr, &surface) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create window surface!");
    }
    _surface = vk::SurfaceKHR(surface);
}

void Application::loop(const std::function<void()>& update)
{
    while (!glfwWindowShouldClose(_window) && _running) {
        drawFrame();
        if (update) {
            update();
        }
        glfwPollEvents();
        _frameIndex++;
    }

    vkDeviceWaitIdle(_device);
}

void Application::setupDebugMessenger()
{
#ifndef NDEBUG
    vk::DebugUtilsMessengerCreateInfoEXT createInfo;
    populateDebugMessengerCreateInfo(createInfo);

    if (createDebugUtilsMessengerEXT(_instance, &createInfo, nullptr, &_debugMessenger) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to set up debug messenger!");
    }
#endif
}

void Application::cleanup()
{
    cleanupSwapChain();

    _device.destroyPipeline(_graphicsPipeline, nullptr);
    _device.destroyPipelineLayout(_pipelineLayout, nullptr);
    _device.destroyRenderPass(_renderPass, nullptr);

    _device.destroyPipeline(_computePipeline, nullptr);
    _device.destroyPipelineLayout(_computePipelineLayout, nullptr);

    for (std::size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        _device.destroyBuffer(_inputBuffers[i], nullptr);
        _device.freeMemory(_inputBuffersMemory[i], nullptr);

        _device.destroyBuffer(_viewBuffers[i], nullptr);
        _device.freeMemory(_viewBuffersMemory[i], nullptr);

        _device.destroyBuffer(_sceneBuffers[i], nullptr);
        _device.freeMemory(_sceneBuffersMemory[i], nullptr);

        _device.destroyBuffer(_triangleBuffers[i], nullptr);
        _device.freeMemory(_triangleBuffersMemory[i], nullptr);

        _device.destroyBuffer(_meshBuffers[i], nullptr);
        _device.freeMemory(_meshBuffersMemory[i], nullptr);
    }

    // Destroy the images
    _device.destroyImageView(_textureImageView, nullptr);
    _device.destroyImage(_textureImage, nullptr);
    _device.freeMemory(_textureImageMemory, nullptr);

    _device.destroyImageView(_computeInputImageView, nullptr);
    _device.destroyImage(_computeInputImage, nullptr);
    _device.freeMemory(_computeInputImageMemory, nullptr);

    _device.destroyImageView(_computeOutputImageView, nullptr);
    _device.destroyImage(_computeOutputImage, nullptr);
    _device.freeMemory(_computeOutputImageMemory, nullptr);

    _device.destroyDescriptorPool(_screenDescriptorPool, nullptr);
    _device.destroyDescriptorSetLayout(_screenDescriptorSetLayout, nullptr);

    _device.destroyDescriptorPool(_computeDescriptorPool, nullptr);
    _device.destroyDescriptorSetLayout(_computeDescriptorSetLayout, nullptr);

    _device.destroyBuffer(_screenIndexBuffer, nullptr);
    _device.freeMemory(_screenIndexBufferMemory, nullptr);

    _device.destroyBuffer(_screenVertexBuffer, nullptr);
    _device.freeMemory(_screenVertexBufferMemory, nullptr);

    for (std::size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        _device.destroySemaphore(_renderFinishedSemaphores[i], nullptr);
        _device.destroySemaphore(_imageAvailableSemaphores[i], nullptr);
        _device.destroySemaphore(_computeFinishedSemaphores[i], nullptr);
        _device.destroyFence(_inFlightFences[i], nullptr);
        _device.destroyFence(_computeInFlightFences[i], nullptr);
    }
    _device.destroyCommandPool(_commandPool, nullptr);
    _device.destroy();

#ifndef NDEBUG
    destroyDebugUtilsMessengerEXT(_instance, _debugMessenger, nullptr);
#endif
    _instance.destroySurfaceKHR(_surface, nullptr);
    _instance.destroy();

    glfwDestroyWindow(_window);
    glfwTerminate();
}

bool Application::checkValidationLayerSupport() {
    uint32_t layerCount;
    if (vk::enumerateInstanceLayerProperties(&layerCount, nullptr) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to enumerate instance layer properties!");
    }

    std::vector<vk::LayerProperties> availableLayers(layerCount);
    if (vk::enumerateInstanceLayerProperties(&layerCount, availableLayers.data()) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to enumerate instance layer properties!");
    }

    for (const char* layerName : _validationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }
    return true;
}

SwapChainSupportDetails Application::querySwapChainSupport(vk::PhysicalDevice device) {
    SwapChainSupportDetails details;
    if (device.getSurfaceCapabilitiesKHR(_surface, &details.capabilities) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to get surface capabilities!");
    }

    uint32_t formatCount;
    if (device.getSurfaceFormatsKHR(_surface, &formatCount, nullptr) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to get surface formats!");
    }

    if (formatCount != 0) {
        details.formats.resize(formatCount);
        if (device.getSurfaceFormatsKHR(_surface, &formatCount, details.formats.data()) != vk::Result::eSuccess) {
            throw std::runtime_error("Failed to get surface formats!");
        }
    }

    uint32_t presentModeCount;
    if (device.getSurfacePresentModesKHR(_surface, &presentModeCount, nullptr) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to get surface present modes!");
    }

    if (presentModeCount != 0) {
        details.presentModes.resize(presentModeCount);
        if (device.getSurfacePresentModesKHR(_surface, &presentModeCount, details.presentModes.data()) != vk::Result::eSuccess) {
            throw std::runtime_error("Failed to get surface present modes!");
        }
    }

    return details;
}

vk::SurfaceFormatKHR Application::chooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats)
{
    for (const auto& availableFormat : availableFormats) {
        if (availableFormat.format == vk::Format::eB8G8R8A8Srgb
            && availableFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
            return availableFormat;
        }
    }

    return availableFormats[0];
}

vk::PresentModeKHR Application::chooseSwapPresentMode(const std::vector<vk::PresentModeKHR>& availablePresentModes)
{
    for (const auto& availablePresentMode : availablePresentModes) {
        if (availablePresentMode == vk::PresentModeKHR::eMailbox) {
            return availablePresentMode;
        }
    }

    return vk::PresentModeKHR::eFifo;
}

vk::Extent2D Application::chooseSwapExtent(const vk::SurfaceCapabilitiesKHR& capabilities)
{
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return capabilities.currentExtent;
    } else {
        int width, height;
        glfwGetFramebufferSize(_window, &width, &height);

        vk::Extent2D actualExtent = {
                static_cast<uint32_t>(width),
                static_cast<uint32_t>(height)
        };

        actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

        return actualExtent;
    }
}

void Application::createSwapChain()
{
    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(_physicalDevice);

    vk::SurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    vk::PresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
    vk::Extent2D extent = chooseSwapExtent(swapChainSupport.capabilities);
    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }

    vk::SwapchainCreateInfoKHR createInfo;
    createInfo.sType = vk::StructureType::eSwapchainCreateInfoKHR;
    createInfo.surface = _surface;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = vk::ImageUsageFlagBits::eColorAttachment | vk::ImageUsageFlagBits::eSampled;

    QueueFamilyIndices indices = findQueueFamilies(_physicalDevice);
    uint32_t queueFamilyIndices[] = {indices.graphicsAndComputeFamily.value(), indices.presentFamily.value()};

    if (indices.graphicsAndComputeFamily != indices.presentFamily) {
        createInfo.imageSharingMode = vk::SharingMode::eConcurrent;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        createInfo.imageSharingMode = vk::SharingMode::eExclusive;
        createInfo.queueFamilyIndexCount = 0; // Optional
        createInfo.pQueueFamilyIndices = nullptr; // Optional
    }
    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
    createInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;
    _swapChainImageFormat = surfaceFormat.format;
    _swapChainExtent = extent;

    if (_device.createSwapchainKHR(&createInfo, nullptr, &_swapChain) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to create swap chain!");
    }
    if (_device.getSwapchainImagesKHR(_swapChain, &imageCount, nullptr) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to get swap chain images!");
    }
    _swapChainImages.resize(imageCount);
    if (_device.getSwapchainImagesKHR(_swapChain, &imageCount, _swapChainImages.data()) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to get swap chain images!");
    }
}

void Application::createImages()
{
    // Create Image that will be used as a texture
    vk::ImageCreateInfo imageInfo;
    imageInfo.sType = vk::StructureType::eImageCreateInfo;
    imageInfo.imageType = vk::ImageType::e2D;
    imageInfo.extent.width = _swapChainExtent.width;
    imageInfo.extent.height = _swapChainExtent.height;
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.format = vk::Format::eR8G8B8A8Unorm;
    imageInfo.tiling = vk::ImageTiling::eOptimal;
    imageInfo.initialLayout = vk::ImageLayout::eUndefined;
    imageInfo.usage = vk::ImageUsageFlagBits::eSampled | vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eTransferSrc | vk::ImageUsageFlagBits::eStorage | vk::ImageUsageFlagBits::eColorAttachment;
    imageInfo.sharingMode = vk::SharingMode::eExclusive;
    imageInfo.samples = vk::SampleCountFlagBits::e1;

    if (_device.createImage(&imageInfo, nullptr, &_textureImage) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to create texture image!");
    }

    // Allocate memory for the image
    vk::MemoryRequirements memRequirements;
    _device.getImageMemoryRequirements(_textureImage, &memRequirements);

    vk::MemoryAllocateInfo allocInfo;
    allocInfo.sType = vk::StructureType::eMemoryAllocateInfo;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal);

    if (_device.allocateMemory(&allocInfo, nullptr, &_textureImageMemory) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to allocate texture image memory!");
    }

    _device.bindImageMemory(_textureImage, _textureImageMemory, 0);

    // Create Image View
    vk::ImageViewCreateInfo viewInfo;
    viewInfo.sType = vk::StructureType::eImageViewCreateInfo;
    viewInfo.image = _textureImage;
    viewInfo.viewType = vk::ImageViewType::e2D;
    viewInfo.format = vk::Format::eR8G8B8A8Unorm;
    viewInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;

    if (_device.createImageView(&viewInfo, nullptr, &_textureImageView) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to create texture image view!");
    }

    // Create the input image for the raytracing
    imageInfo = vk::ImageCreateInfo();
    imageInfo.sType = vk::StructureType::eImageCreateInfo;
    imageInfo.imageType = vk::ImageType::e2D;
    imageInfo.extent.width = _swapChainExtent.width;
    imageInfo.extent.height = _swapChainExtent.height;
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.format = vk::Format::eR32G32B32A32Sfloat;
    imageInfo.tiling = vk::ImageTiling::eOptimal;
    imageInfo.initialLayout = vk::ImageLayout::eUndefined;
    imageInfo.usage = vk::ImageUsageFlagBits::eStorage | vk::ImageUsageFlagBits::eTransferSrc | vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled;
    imageInfo.sharingMode = vk::SharingMode::eExclusive;
    imageInfo.samples = vk::SampleCountFlagBits::e1;

    if (_device.createImage(&imageInfo, nullptr, &_computeInputImage) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to create input image!");
    }

    memRequirements = vk::MemoryRequirements();
    _device.getImageMemoryRequirements(_computeInputImage, &memRequirements);

    allocInfo = vk::MemoryAllocateInfo();
    allocInfo.sType = vk::StructureType::eMemoryAllocateInfo;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal);

    if (_device.allocateMemory(&allocInfo, nullptr, &_computeInputImageMemory) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to allocate input image memory!");
    }

    _device.bindImageMemory(_computeInputImage, _computeInputImageMemory, 0);

    // Create the input image view
    viewInfo = vk::ImageViewCreateInfo();
    viewInfo.sType = vk::StructureType::eImageViewCreateInfo;
    viewInfo.image = _computeInputImage;
    viewInfo.viewType = vk::ImageViewType::e2D;
    viewInfo.format = vk::Format::eR32G32B32A32Sfloat;
    viewInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;

    if (_device.createImageView(&viewInfo, nullptr, &_computeInputImageView) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to create input image view!");
    }

    // Create the output image for the raytracing
    imageInfo = vk::ImageCreateInfo();
    imageInfo.sType = vk::StructureType::eImageCreateInfo;
    imageInfo.imageType = vk::ImageType::e2D;
    imageInfo.extent.width = _swapChainExtent.width;
    imageInfo.extent.height = _swapChainExtent.height;
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.format = vk::Format::eR32G32B32A32Sfloat;
    imageInfo.tiling = vk::ImageTiling::eOptimal;
    imageInfo.initialLayout = vk::ImageLayout::eUndefined;
    imageInfo.usage = vk::ImageUsageFlagBits::eStorage | vk::ImageUsageFlagBits::eTransferSrc | vk::ImageUsageFlagBits::eTransferDst | vk::ImageUsageFlagBits::eSampled;
    imageInfo.sharingMode = vk::SharingMode::eExclusive;
    imageInfo.samples = vk::SampleCountFlagBits::e1;

    if (_device.createImage(&imageInfo, nullptr, &_computeOutputImage) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to create output image!");
    }

    _device.getImageMemoryRequirements(_computeOutputImage, &memRequirements);

    allocInfo = vk::MemoryAllocateInfo();
    allocInfo.sType = vk::StructureType::eMemoryAllocateInfo;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal);

    if (_device.allocateMemory(&allocInfo, nullptr, &_computeOutputImageMemory) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to allocate output image memory!");
    }

    _device.bindImageMemory(_computeOutputImage, _computeOutputImageMemory, 0);

    // Create the output image view
    viewInfo = vk::ImageViewCreateInfo();
    viewInfo.sType = vk::StructureType::eImageViewCreateInfo;
    viewInfo.image = _computeOutputImage;
    viewInfo.viewType = vk::ImageViewType::e2D;
    viewInfo.format = vk::Format::eR32G32B32A32Sfloat;
    viewInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
    viewInfo.subresourceRange.baseMipLevel = 0;
    viewInfo.subresourceRange.levelCount = 1;
    viewInfo.subresourceRange.baseArrayLayer = 0;
    viewInfo.subresourceRange.layerCount = 1;

    if (_device.createImageView(&viewInfo, nullptr, &_computeOutputImageView) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to create output image view!");
    }
}

void Application::createImageViews() {
    _swapChainImageViews.resize(_swapChainImages.size());

    for (size_t i = 0; i < _swapChainImages.size(); i++) {
        vk::ImageViewCreateInfo createInfo;
        createInfo.sType = vk::StructureType::eImageViewCreateInfo;
        createInfo.image = _swapChainImages[i];
        createInfo.viewType = vk::ImageViewType::e2D;
        createInfo.format = _swapChainImageFormat;
        createInfo.components.r = vk::ComponentSwizzle::eIdentity;
        createInfo.components.g = vk::ComponentSwizzle::eIdentity;
        createInfo.components.b = vk::ComponentSwizzle::eIdentity;
        createInfo.components.a = vk::ComponentSwizzle::eIdentity;
        createInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;

        if (_device.createImageView(&createInfo, nullptr, &_swapChainImageViews[i]) != vk::Result::eSuccess) {
            throw std::runtime_error("Failed to create image views!");
        }
    }
}

void Application::createGraphicsPipeline()
{
    // Create shaders
    auto screenVert = readFile("shaders/screen.spv");
    auto textureScreenFrag = readFile("shaders/texture_screen.spv");

    vk::ShaderModule screenShaderModule = createShaderModule(screenVert);
    vk::ShaderModule textureShaderModule = createShaderModule(textureScreenFrag);

    // Raytracing pipeline
    vk::PipelineShaderStageCreateInfo screenShaderStageInfo;
    screenShaderStageInfo.sType = vk::StructureType::ePipelineShaderStageCreateInfo;
    screenShaderStageInfo.stage = vk::ShaderStageFlagBits::eVertex;
    screenShaderStageInfo.module = screenShaderModule;
    screenShaderStageInfo.pName = "main";

    vk::PipelineShaderStageCreateInfo textureShaderStageInfo;
    textureShaderStageInfo.sType = vk::StructureType::ePipelineShaderStageCreateInfo;
    textureShaderStageInfo.stage = vk::ShaderStageFlagBits::eFragment;
    textureShaderStageInfo.module = textureShaderModule;
    textureShaderStageInfo.pName = "main";

    vk::PipelineShaderStageCreateInfo shaderStages[] = {screenShaderStageInfo, textureShaderStageInfo};
    vk::PipelineVertexInputStateCreateInfo vertexInputInfo;
    vertexInputInfo.sType = vk::StructureType::ePipelineVertexInputStateCreateInfo;
    auto bindingDescription = Vertex::getBindingDescription();
    auto attributeDescriptions = Vertex::getAttributeDescriptions();
    vertexInputInfo.vertexBindingDescriptionCount = 1;
    vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
    vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
    vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

    vk::PipelineInputAssemblyStateCreateInfo inputAssembly;
    inputAssembly.sType = vk::StructureType::ePipelineInputAssemblyStateCreateInfo;
    inputAssembly.topology = vk::PrimitiveTopology::eTriangleList;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    vk::PipelineViewportStateCreateInfo viewportState;
    viewportState.sType = vk::StructureType::ePipelineViewportStateCreateInfo;
    viewportState.viewportCount = 1;
    viewportState.scissorCount = 1;

    vk::PipelineRasterizationStateCreateInfo rasterizer;
    rasterizer.sType = vk::StructureType::ePipelineRasterizationStateCreateInfo;
    rasterizer.depthClampEnable = vk::False;
    rasterizer.rasterizerDiscardEnable = vk::False;
    rasterizer.polygonMode = vk::PolygonMode::eFill;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = vk::CullModeFlagBits::eBack;
    rasterizer.frontFace = vk::FrontFace::eClockwise;
    rasterizer.depthBiasEnable = vk::False;

    vk::PipelineMultisampleStateCreateInfo multisampling;
    multisampling.sType = vk::StructureType::ePipelineMultisampleStateCreateInfo;
    multisampling.sampleShadingEnable = vk::False;
    multisampling.rasterizationSamples = vk::SampleCountFlagBits::e1;

    vk::PipelineColorBlendAttachmentState colorBlendAttachment;
    colorBlendAttachment.colorWriteMask = vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG | vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
    colorBlendAttachment.blendEnable = vk::False;

    vk::PipelineColorBlendStateCreateInfo colorBlending;
    colorBlending.sType = vk::StructureType::ePipelineColorBlendStateCreateInfo;
    colorBlending.logicOpEnable = vk::False;
    colorBlending.logicOp = vk::LogicOp::eCopy;
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f;
    colorBlending.blendConstants[1] = 0.0f;
    colorBlending.blendConstants[2] = 0.0f;
    colorBlending.blendConstants[3] = 0.0f;

    std::vector<vk::DynamicState> dynamicStates = {
            vk::DynamicState::eViewport,
            vk::DynamicState::eScissor
    };
    vk::PipelineDynamicStateCreateInfo dynamicState;
    dynamicState.sType = vk::StructureType::ePipelineDynamicStateCreateInfo;
    dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
    dynamicState.pDynamicStates = dynamicStates.data();


    vk::PipelineLayoutCreateInfo pipelineLayoutInfo;
    pipelineLayoutInfo.sType = vk::StructureType::ePipelineLayoutCreateInfo;
    pipelineLayoutInfo.setLayoutCount = 1;
    pipelineLayoutInfo.pSetLayouts = &_screenDescriptorSetLayout;
    pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
    pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

    if (_device.createPipelineLayout(&pipelineLayoutInfo, nullptr, &_pipelineLayout) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to create pipeline layout!");
    }
    vk::GraphicsPipelineCreateInfo pipelineInfo;
    pipelineInfo.sType = vk::StructureType::eGraphicsPipelineCreateInfo;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pDepthStencilState = nullptr; // Optional
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.pDynamicState = &dynamicState;
    pipelineInfo.layout = _pipelineLayout;
    pipelineInfo.renderPass = _renderPass;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
    pipelineInfo.basePipelineIndex = -1; // Optional

    if (_device.createGraphicsPipelines(VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &_graphicsPipeline) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to create graphics pipeline!");
    }

    _device.destroyShaderModule(screenShaderModule, nullptr);
    _device.destroyShaderModule(textureShaderModule, nullptr);
}

void Application::createComputePipeline()
{
    // Create shaders
    auto computeShaderCode = readFile("shaders/raytracing.spv");
    vk::ShaderModule computeShaderModule = createShaderModule(computeShaderCode);

    vk::PipelineShaderStageCreateInfo computeShaderStageInfo;
    computeShaderStageInfo.sType = vk::StructureType::ePipelineShaderStageCreateInfo;
    computeShaderStageInfo.stage = vk::ShaderStageFlagBits::eCompute;
    computeShaderStageInfo.module = computeShaderModule;
    computeShaderStageInfo.pName = "main";

    vk::PipelineLayoutCreateInfo pipelineLayoutInfo;
    pipelineLayoutInfo.sType = vk::StructureType::ePipelineLayoutCreateInfo;
    pipelineLayoutInfo.setLayoutCount = 1;
    pipelineLayoutInfo.pSetLayouts = &_computeDescriptorSetLayout;
    pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
    pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

    if (_device.createPipelineLayout(&pipelineLayoutInfo, nullptr, &_computePipelineLayout) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to create compute pipeline layout!");
    }

    vk::ComputePipelineCreateInfo pipelineInfo;
    pipelineInfo.sType = vk::StructureType::eComputePipelineCreateInfo;
    pipelineInfo.stage = computeShaderStageInfo;
    pipelineInfo.layout = _computePipelineLayout;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
    pipelineInfo.basePipelineIndex = -1; // Optional

    if (_device.createComputePipelines(VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &_computePipeline) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to create compute pipeline!");
    }

    _device.destroyShaderModule(computeShaderModule, nullptr);
}

vk::ShaderModule Application::createShaderModule(const std::vector<char>& code)
{
    vk::ShaderModuleCreateInfo createInfo;
    createInfo.sType = vk::StructureType::eShaderModuleCreateInfo;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    vk::ShaderModule shaderModule;
    if (_device.createShaderModule(&createInfo, nullptr, &shaderModule) != vk::Result::eSuccess) {
        throw std::runtime_error("Failed to create shader module!");
    }

    return shaderModule;
}

void Application::createRenderPass()
{
    // Create scene render pass
    vk::AttachmentDescription colorAttachment;
    colorAttachment.format = _swapChainImageFormat;
    colorAttachment.samples = vk::SampleCountFlagBits::e1;
    colorAttachment.loadOp = vk::AttachmentLoadOp::eClear;
    colorAttachment.storeOp = vk::AttachmentStoreOp::eStore;
    colorAttachment.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
    colorAttachment.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
    colorAttachment.initialLayout = vk::ImageLayout::eUndefined;
    colorAttachment.finalLayout = vk::ImageLayout::ePresentSrcKHR;

    vk::AttachmentReference colorAttachmentRef;
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = vk::ImageLayout::eColorAttachmentOptimal;

    vk::SubpassDescription subPass;
    subPass.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
    subPass.colorAttachmentCount = 1;
    subPass.pColorAttachments = &colorAttachmentRef;

    vk::SubpassDependency dependency;
    dependency.srcSubpass = vk::SubpassExternal;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
    dependency.srcAccessMask = vk::AccessFlagBits::eColorAttachmentWrite;
    dependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
    dependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite;

    std::array<vk::SubpassDependency, 1> dependencies = {dependency};
    std::array<vk::AttachmentDescription, 1> attachments = {colorAttachment};
    std::array<vk::SubpassDescription, 1> subPasses = {subPass};

    vk::RenderPassCreateInfo renderPassInfo;
    renderPassInfo.sType = vk::StructureType::eRenderPassCreateInfo;
    renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
    renderPassInfo.pAttachments = attachments.data();
    renderPassInfo.subpassCount = static_cast<uint32_t>(subPasses.size());
    renderPassInfo.pSubpasses = subPasses.data();
    renderPassInfo.dependencyCount = static_cast<uint32_t>(dependencies.size());
    renderPassInfo.pDependencies = dependencies.data();

    if (_device.createRenderPass(&renderPassInfo, nullptr, &_renderPass) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to create render pass!");
    }
}

void Application::createFrameBuffers()
{
    _swapChainFrameBuffers.resize(_swapChainImageViews.size());

    for (size_t i = 0; i < _swapChainImageViews.size(); i++) {
        std::array<vk::ImageView, 1> attachments = {
                _swapChainImageViews[i],
        };

        vk::FramebufferCreateInfo framebufferInfo;
        framebufferInfo.sType = vk::StructureType::eFramebufferCreateInfo;
        framebufferInfo.renderPass = _renderPass;
        framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        framebufferInfo.pAttachments = attachments.data();
        framebufferInfo.width = _swapChainExtent.width;
        framebufferInfo.height = _swapChainExtent.height;
        framebufferInfo.layers = 1;

        if (_device.createFramebuffer(&framebufferInfo, nullptr, &_swapChainFrameBuffers[i]) != vk::Result::eSuccess) {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }
}

void Application::createCommandPool()
{
    QueueFamilyIndices queueFamilyIndices = findQueueFamilies(_physicalDevice);

    vk::CommandPoolCreateInfo poolInfo;
    poolInfo.sType = vk::StructureType::eCommandPoolCreateInfo;
    poolInfo.flags = vk::CommandPoolCreateFlagBits::eResetCommandBuffer;
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsAndComputeFamily.value();

    if (_device.createCommandPool(&poolInfo, nullptr, &_commandPool) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to create command pool!");
    }
}

void Application::createCommandBuffer() {
    _commandBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    vk::CommandBufferAllocateInfo allocInfo;
    allocInfo.sType = vk::StructureType::eCommandBufferAllocateInfo;
    allocInfo.commandPool = _commandPool;
    allocInfo.level = vk::CommandBufferLevel::ePrimary;
    allocInfo.commandBufferCount = (uint32_t) _commandBuffers.size();

    if (_device.allocateCommandBuffers(&allocInfo, _commandBuffers.data()) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to allocate command buffers!");
    }
}

void Application::createComputeCommandBuffers() {
    _computeCommandBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    vk::CommandBufferAllocateInfo allocInfo;
    allocInfo.sType = vk::StructureType::eCommandBufferAllocateInfo;
    allocInfo.commandPool = _commandPool;
    allocInfo.level = vk::CommandBufferLevel::ePrimary;
    allocInfo.commandBufferCount = (uint32_t) _computeCommandBuffers.size();

    if (_device.allocateCommandBuffers(&allocInfo, _computeCommandBuffers.data()) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to allocate compute command buffers!");
    }
}

void Application::recordCommandBuffer(vk::CommandBuffer commandBuffer, uint32_t imageIndex)
{
    vk::CommandBufferBeginInfo beginInfo;
    beginInfo.sType = vk::StructureType::eCommandBufferBeginInfo;
    beginInfo.pInheritanceInfo = nullptr; // Optional

    if (commandBuffer.begin(&beginInfo) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }

    vk::RenderPassBeginInfo renderPassInfo;
    renderPassInfo.sType = vk::StructureType::eRenderPassBeginInfo;
    renderPassInfo.renderPass = _renderPass;
    renderPassInfo.framebuffer = _swapChainFrameBuffers[imageIndex];
    renderPassInfo.renderArea.offset = vk::Offset2D{0, 0};
    renderPassInfo.renderArea.extent = _swapChainExtent;

    vk::ClearValue clearColor = vk::ClearValue{{std::array<float, 4>{0.0f, 0.0f, 0.0f, 1.0f}}};
    std::array<vk::ClearValue, 2> clearValues = {clearColor, clearColor};
    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues = clearValues.data();
    commandBuffer.beginRenderPass(&renderPassInfo, vk::SubpassContents::eInline);

    commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, _graphicsPipeline);

    vk::Viewport viewport;
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float) _swapChainExtent.width;
    viewport.height = (float) _swapChainExtent.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    commandBuffer.setViewport(0, 1, &viewport);

    vk::Rect2D scissor;
    scissor.offset = vk::Offset2D{0, 0};
    scissor.extent = _swapChainExtent;
    commandBuffer.setScissor(0, 1, &scissor);

    vk::Buffer vertexBuffers[] = {_screenVertexBuffer};
    vk::DeviceSize offsets[] = {0};
    commandBuffer.bindVertexBuffers(0, 1, vertexBuffers, offsets);
    commandBuffer.bindIndexBuffer(_screenIndexBuffer, 0, vk::IndexType::eUint16);

    commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, _pipelineLayout, 0, 1, &_screenDescriptorSets[_currentFrame], 0, nullptr);

    commandBuffer.drawIndexed(static_cast<uint32_t>(_screenIndices.size()), 1, 0, 0, 0);

    commandBuffer.endRenderPass();

    commandBuffer.end();
}

void Application::recordComputeCommandBuffer(vk::CommandBuffer commandBuffer) {
    vk::CommandBufferBeginInfo beginInfo;
    beginInfo.sType = vk::StructureType::eCommandBufferBeginInfo;

    if (commandBuffer.begin(&beginInfo) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to begin recording compute command buffer!");
    }
    commandBuffer.bindPipeline(vk::PipelineBindPoint::eCompute, _computePipeline);

    commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eCompute, _computePipelineLayout, 0, 1, &_computeDescriptorSets[_currentFrame], 0, nullptr);

    // Blit the texture image to the input image
    vk::ImageMemoryBarrier transferToInputBarrier;
    transferToInputBarrier.sType = vk::StructureType::eImageMemoryBarrier;
    transferToInputBarrier.oldLayout = vk::ImageLayout::eUndefined;
    transferToInputBarrier.newLayout = vk::ImageLayout::eTransferDstOptimal;
    transferToInputBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    transferToInputBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    transferToInputBarrier.image = _computeInputImage;
    transferToInputBarrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
    transferToInputBarrier.subresourceRange.baseMipLevel = 0;
    transferToInputBarrier.subresourceRange.levelCount = 1;
    transferToInputBarrier.subresourceRange.baseArrayLayer = 0;
    transferToInputBarrier.subresourceRange.layerCount = 1;
    transferToInputBarrier.srcAccessMask = vk::AccessFlagBits::eShaderRead;
    transferToInputBarrier.dstAccessMask = vk::AccessFlagBits::eTransferWrite;

    vk::ImageMemoryBarrier inputToTransferBarrier;
    inputToTransferBarrier.sType = vk::StructureType::eImageMemoryBarrier;
    inputToTransferBarrier.oldLayout = vk::ImageLayout::eUndefined;
    inputToTransferBarrier.newLayout = vk::ImageLayout::eTransferSrcOptimal;
    inputToTransferBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    inputToTransferBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    inputToTransferBarrier.image = _textureImage;
    inputToTransferBarrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
    inputToTransferBarrier.subresourceRange.baseMipLevel = 0;
    inputToTransferBarrier.subresourceRange.levelCount = 1;
    inputToTransferBarrier.subresourceRange.baseArrayLayer = 0;
    inputToTransferBarrier.subresourceRange.layerCount = 1;
    inputToTransferBarrier.srcAccessMask = vk::AccessFlagBits::eShaderRead;
    inputToTransferBarrier.dstAccessMask = vk::AccessFlagBits::eTransferRead;

    std::array<vk::ImageMemoryBarrier, 2> transferInputBarriers = {transferToInputBarrier, inputToTransferBarrier};

    commandBuffer.pipelineBarrier(vk::PipelineStageFlagBits::eComputeShader, vk::PipelineStageFlagBits::eTransfer, vk::DependencyFlagBits::eByRegion, 0, nullptr, 0, nullptr, static_cast<uint32_t>(transferInputBarriers.size()), transferInputBarriers.data());

    vk::ImageBlit blitInput;
    blitInput.srcOffsets[0] = vk::Offset3D{0, 0, 0};
    blitInput.srcOffsets[1] = vk::Offset3D{(int32_t) _swapChainExtent.width, (int32_t) _swapChainExtent.height, 1};
    blitInput.srcSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
    blitInput.srcSubresource.mipLevel = 0;
    blitInput.srcSubresource.baseArrayLayer = 0;
    blitInput.srcSubresource.layerCount = 1;
    blitInput.dstOffsets[0] = vk::Offset3D{0, 0, 0};
    blitInput.dstOffsets[1] = vk::Offset3D{(int32_t) _swapChainExtent.width, (int32_t) _swapChainExtent.height, 1};
    blitInput.dstSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
    blitInput.dstSubresource.mipLevel = 0;
    blitInput.dstSubresource.baseArrayLayer = 0;
    blitInput.dstSubresource.layerCount = 1;

    commandBuffer.blitImage(_textureImage, vk::ImageLayout::eTransferSrcOptimal, _computeInputImage, vk::ImageLayout::eTransferDstOptimal, 1, &blitInput, vk::Filter::eLinear);

    // Transition image layout from undefined to general
    vk::ImageMemoryBarrier inputBarrier;
    inputBarrier.sType = vk::StructureType::eImageMemoryBarrier;
    inputBarrier.oldLayout = vk::ImageLayout::eUndefined;
    inputBarrier.newLayout = vk::ImageLayout::eGeneral;
    inputBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    inputBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    inputBarrier.image = _computeInputImage;
    inputBarrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
    inputBarrier.subresourceRange.baseMipLevel = 0;
    inputBarrier.subresourceRange.levelCount = 1;
    inputBarrier.subresourceRange.baseArrayLayer = 0;
    inputBarrier.subresourceRange.layerCount = 1;
    inputBarrier.srcAccessMask = vk::AccessFlagBits::eShaderWrite;
    inputBarrier.dstAccessMask = vk::AccessFlagBits::eShaderRead;

    vk::ImageMemoryBarrier outputBarrier;
    outputBarrier.sType = vk::StructureType::eImageMemoryBarrier;
    outputBarrier.oldLayout = vk::ImageLayout::eUndefined;
    outputBarrier.newLayout = vk::ImageLayout::eGeneral;
    outputBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    outputBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    outputBarrier.image = _computeOutputImage;
    outputBarrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
    outputBarrier.subresourceRange.baseMipLevel = 0;
    outputBarrier.subresourceRange.levelCount = 1;
    outputBarrier.subresourceRange.baseArrayLayer = 0;
    outputBarrier.subresourceRange.layerCount = 1;
    outputBarrier.srcAccessMask = vk::AccessFlagBits::eShaderWrite;
    outputBarrier.dstAccessMask = vk::AccessFlagBits::eShaderRead;

    std::array<vk::ImageMemoryBarrier, 2> barriers = {inputBarrier, outputBarrier};

    commandBuffer.pipelineBarrier(vk::PipelineStageFlagBits::eComputeShader, vk::PipelineStageFlagBits::eComputeShader, vk::DependencyFlagBits::eByRegion, 0, nullptr, 0, nullptr, static_cast<uint32_t>(barriers.size()), barriers.data());
    commandBuffer.dispatch(_swapChainExtent.width / 16, _swapChainExtent.height / 16, 1);

    // Blit the output image to _textureImage
    vk::ImageMemoryBarrier outputToTransferBarrier;
    outputToTransferBarrier.sType = vk::StructureType::eImageMemoryBarrier;
    outputToTransferBarrier.oldLayout = vk::ImageLayout::eGeneral;
    outputToTransferBarrier.newLayout = vk::ImageLayout::eTransferSrcOptimal;
    outputToTransferBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    outputToTransferBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    outputToTransferBarrier.image = _computeOutputImage;
    outputToTransferBarrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
    outputToTransferBarrier.subresourceRange.baseMipLevel = 0;
    outputToTransferBarrier.subresourceRange.levelCount = 1;
    outputToTransferBarrier.subresourceRange.baseArrayLayer = 0;
    outputToTransferBarrier.subresourceRange.layerCount = 1;
    outputToTransferBarrier.srcAccessMask = vk::AccessFlagBits::eShaderWrite;
    outputToTransferBarrier.dstAccessMask = vk::AccessFlagBits::eTransferRead;

    vk::ImageMemoryBarrier transferToOutputBarrier;
    transferToOutputBarrier.sType = vk::StructureType::eImageMemoryBarrier;
    transferToOutputBarrier.oldLayout = vk::ImageLayout::eUndefined;
    transferToOutputBarrier.newLayout = vk::ImageLayout::eTransferDstOptimal;
    transferToOutputBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    transferToOutputBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    transferToOutputBarrier.image = _textureImage;
    transferToOutputBarrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
    transferToOutputBarrier.subresourceRange.baseMipLevel = 0;
    transferToOutputBarrier.subresourceRange.levelCount = 1;
    transferToOutputBarrier.subresourceRange.baseArrayLayer = 0;
    transferToOutputBarrier.subresourceRange.layerCount = 1;
    transferToOutputBarrier.srcAccessMask = vk::AccessFlagBits::eShaderWrite;
    transferToOutputBarrier.dstAccessMask = vk::AccessFlagBits::eTransferWrite;

    std::array<vk::ImageMemoryBarrier, 2> transferBarriers = {outputToTransferBarrier, transferToOutputBarrier};

    commandBuffer.pipelineBarrier(vk::PipelineStageFlagBits::eComputeShader, vk::PipelineStageFlagBits::eTransfer, vk::DependencyFlagBits::eByRegion, 0, nullptr, 0, nullptr, static_cast<uint32_t>(transferBarriers.size()), transferBarriers.data());

    vk::ImageBlit blit;
    blit.srcOffsets[0] = vk::Offset3D{0, 0, 0};
    blit.srcOffsets[1] = vk::Offset3D{(int32_t) _swapChainExtent.width, (int32_t) _swapChainExtent.height, 1};
    blit.srcSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
    blit.srcSubresource.mipLevel = 0;
    blit.srcSubresource.baseArrayLayer = 0;
    blit.srcSubresource.layerCount = 1;
    blit.dstOffsets[0] = vk::Offset3D{0, 0, 0};
    blit.dstOffsets[1] = vk::Offset3D{(int32_t) _swapChainExtent.width, (int32_t) _swapChainExtent.height, 1};
    blit.dstSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
    blit.dstSubresource.mipLevel = 0;
    blit.dstSubresource.baseArrayLayer = 0;
    blit.dstSubresource.layerCount = 1;

    commandBuffer.blitImage(_computeOutputImage, vk::ImageLayout::eTransferSrcOptimal, _textureImage, vk::ImageLayout::eTransferDstOptimal, 1, &blit, vk::Filter::eLinear);

    // Transition image layout from undefined to general
    vk::ImageMemoryBarrier barrier;
    barrier.sType = vk::StructureType::eImageMemoryBarrier;
    barrier.oldLayout = vk::ImageLayout::eUndefined;
    barrier.newLayout = vk::ImageLayout::eGeneral;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = _textureImage;
    barrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
    barrier.subresourceRange.baseMipLevel = 0;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount = 1;
    barrier.srcAccessMask = vk::AccessFlagBits::eShaderWrite;
    barrier.dstAccessMask = vk::AccessFlagBits::eShaderRead;

    commandBuffer.pipelineBarrier(vk::PipelineStageFlagBits::eComputeShader, vk::PipelineStageFlagBits::eFragmentShader, vk::DependencyFlagBits::eByRegion, 0, nullptr, 0, nullptr, 1, &barrier);


    commandBuffer.end();
}

void Application::createSyncObjects()
{
    _imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    _renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    _inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
    _computeInFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
    _computeFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);

    vk::SemaphoreCreateInfo semaphoreInfo;
    semaphoreInfo.sType = vk::StructureType::eSemaphoreCreateInfo;

    vk::FenceCreateInfo fenceInfo;
    fenceInfo.sType = vk::StructureType::eFenceCreateInfo;
    fenceInfo.flags = vk::FenceCreateFlagBits::eSignaled;

    for (std::size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        if (_device.createSemaphore(&semaphoreInfo, nullptr, &_imageAvailableSemaphores[i]) != vk::Result::eSuccess ||
            _device.createSemaphore(&semaphoreInfo, nullptr, &_renderFinishedSemaphores[i]) != vk::Result::eSuccess ||
            _device.createFence(&fenceInfo, nullptr, &_inFlightFences[i]) != vk::Result::eSuccess ||
            _device.createFence(&fenceInfo, nullptr, &_computeInFlightFences[i]) != vk::Result::eSuccess ||
            _device.createSemaphore(&semaphoreInfo, nullptr, &_computeFinishedSemaphores[i]) != vk::Result::eSuccess) {

            throw std::runtime_error("Failed to create synchronization objects for a frame!");
        }
    }
}

void Application::drawFrame()
{
    vk::SubmitInfo submitInfo;
    submitInfo.sType = vk::StructureType::eSubmitInfo;

    // Compute submission
    if (_device.waitForFences(1, &_computeInFlightFences[_currentFrame], VK_TRUE, std::numeric_limits<uint64_t>::max()) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to wait for a fence!");
    }

    updateComputeUniformBuffer(_currentFrame);

    if (_device.resetFences(1, &_computeInFlightFences[_currentFrame]) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to reset fence!");
    }

    _computeCommandBuffers[_currentFrame].reset();
    recordComputeCommandBuffer(_computeCommandBuffers[_currentFrame]);

    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &_computeCommandBuffers[_currentFrame];
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = &_computeFinishedSemaphores[_currentFrame];

    if (_computeQueue.submit(1, &submitInfo, _computeInFlightFences[_currentFrame]) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to submit compute command buffer!");
    };


    if (_device.waitForFences(1, &_inFlightFences[_currentFrame], vk::True, std::numeric_limits<uint64_t>::max()) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to wait for a fence!");
    }

    uint32_t imageIndex;
    vk::Result result = _device.acquireNextImageKHR(_swapChain, std::numeric_limits<uint64_t>::max(), _imageAvailableSemaphores[_currentFrame], VK_NULL_HANDLE, &imageIndex);

    if (result == vk::Result::eErrorOutOfDateKHR || result == vk::Result::eSuboptimalKHR) {
        recreateSwapChain();
    } else if (result != vk::Result::eSuccess) {
        throw std::runtime_error("failed to acquire swap chain image!");
    }
    if (_device.resetFences(1, &_inFlightFences[_currentFrame]) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to reset fence!");
    }

    updateUniformBuffer(_currentFrame);

    _commandBuffers[_currentFrame].reset();
    recordCommandBuffer(_commandBuffers[_currentFrame], imageIndex);

    submitInfo = vk::SubmitInfo();
    submitInfo.sType = vk::StructureType::eSubmitInfo;

    vk::Semaphore waitSemaphores[] = {_computeFinishedSemaphores[_currentFrame], _imageAvailableSemaphores[_currentFrame]};
    vk::PipelineStageFlags waitStages[] = {vk::PipelineStageFlagBits::eVertexInput, vk::PipelineStageFlagBits::eColorAttachmentOutput};
    submitInfo.waitSemaphoreCount = 2;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &_commandBuffers[_currentFrame];

    vk::Semaphore signalSemaphores[] = {_renderFinishedSemaphores[_currentFrame]};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    if (_graphicsQueue.submit(1, &submitInfo, _inFlightFences[_currentFrame]) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }

    vk::PresentInfoKHR presentInfo;
    presentInfo.sType = vk::StructureType::ePresentInfoKHR;

    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;
    vk::SwapchainKHR swapChains[] = {_swapChain};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;

    // If last frame was displayed less than 1/60th of a second ago, wait
    if ((_lastFrameTime + 1000 / 60) > (std::size_t) (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count())) {
        std::this_thread::sleep_for(std::chrono::milliseconds(_lastFrameTime + 1000 / 60 - std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()));
    }
    _lastFrameTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

    if (_presentQueue.presentKHR(&presentInfo) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to present swap chain image!");
    }
    _currentFrame = (_currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void Application::createVertexBuffer()
{
    auto bufferSize = (int) (sizeof(_screenVertices[0]) * _screenVertices.size());

    vk::Buffer stagingBuffer;
    vk::DeviceMemory stagingBufferMemory;
    createBuffer(bufferSize, vk::BufferUsageFlagBits::eTransferSrc, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent, stagingBuffer, stagingBufferMemory);

    void* data;
    if (_device.mapMemory(stagingBufferMemory, 0, bufferSize, vk::MemoryMapFlags(), &data) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to map memory!");
    }
    memcpy(data, _screenVertices.data(), (std::size_t) bufferSize);
    _device.unmapMemory(stagingBufferMemory);

    createBuffer(bufferSize, vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eVertexBuffer, vk::MemoryPropertyFlagBits::eDeviceLocal, _screenVertexBuffer, _screenVertexBufferMemory);

    copyBuffer(stagingBuffer, _screenVertexBuffer, bufferSize);

    _device.destroyBuffer(stagingBuffer, nullptr);
    _device.freeMemory(stagingBufferMemory, nullptr);
}

void Application::createIndexBuffer()
{
    vk::DeviceSize bufferSize = sizeof(_screenIndices[0]) * _screenIndices.size();

    vk::Buffer stagingBuffer;
    vk::DeviceMemory stagingBufferMemory;
    createBuffer(bufferSize, vk::BufferUsageFlagBits::eTransferSrc, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent, stagingBuffer, stagingBufferMemory);

    void* data;
    if (_device.mapMemory(stagingBufferMemory, 0, bufferSize, vk::MemoryMapFlags(), &data) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to map memory!");
    }
    memcpy(data, _screenIndices.data(), (size_t) bufferSize);
    _device.unmapMemory(stagingBufferMemory);

    createBuffer(bufferSize, vk::BufferUsageFlagBits::eTransferDst | vk::BufferUsageFlagBits::eIndexBuffer, vk::MemoryPropertyFlagBits::eDeviceLocal, _screenIndexBuffer, _screenIndexBufferMemory);
    copyBuffer(stagingBuffer, _screenIndexBuffer, bufferSize);

    _device.destroyBuffer(stagingBuffer, nullptr);
    _device.freeMemory(stagingBufferMemory, nullptr);
}


void Application::createBuffer(vk::DeviceSize size, vk::BufferUsageFlags usage, vk::MemoryPropertyFlags properties, vk::Buffer& buffer, vk::DeviceMemory& bufferMemory)
{
    vk::BufferCreateInfo bufferInfo;
    bufferInfo.sType = vk::StructureType::eBufferCreateInfo;
    bufferInfo.size = size > 0 ? size : 1;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = vk::SharingMode::eExclusive;

    if (_device.createBuffer(&bufferInfo, nullptr, &buffer) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to create buffer!");
    }

    vk::MemoryRequirements memRequirements;
    _device.getBufferMemoryRequirements(buffer, &memRequirements);

    vk::MemoryAllocateInfo allocInfo;
    allocInfo.sType = vk::StructureType::eMemoryAllocateInfo;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

    if (_device.allocateMemory(&allocInfo, nullptr, &bufferMemory) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to allocate buffer memory!");
    }

    _device.bindBufferMemory(buffer, bufferMemory, 0);
}

void Application::copyBuffer(vk::Buffer srcBuffer, vk::Buffer dstBuffer, vk::DeviceSize size)
{
    vk::CommandBufferAllocateInfo allocInfo;
    allocInfo.sType = vk::StructureType::eCommandBufferAllocateInfo;
    allocInfo.level = vk::CommandBufferLevel::ePrimary;
    allocInfo.commandPool = _commandPool;
    allocInfo.commandBufferCount = 1;

    vk::CommandBuffer commandBuffer;
    if (_device.allocateCommandBuffers(&allocInfo, &commandBuffer) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to allocate command buffer!");
    }

    vk::CommandBufferBeginInfo beginInfo;
    beginInfo.sType = vk::StructureType::eCommandBufferBeginInfo;
    beginInfo.flags = vk::CommandBufferUsageFlagBits::eOneTimeSubmit;

    if (commandBuffer.begin(&beginInfo) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }

    vk::BufferCopy copyRegion;
    copyRegion.size = size;
    commandBuffer.copyBuffer(srcBuffer, dstBuffer, 1, &copyRegion);

    commandBuffer.end();

    vk::SubmitInfo submitInfo;
    submitInfo.sType = vk::StructureType::eSubmitInfo;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffer;

    if (_graphicsQueue.submit(1, &submitInfo, VK_NULL_HANDLE) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to submit copy command buffer!");
    }
    _graphicsQueue.waitIdle();

    _device.freeCommandBuffers(_commandPool, 1, &commandBuffer);
}


uint32_t Application::findMemoryType(uint32_t typeFilter, vk::MemoryPropertyFlags properties)
{
    vk::PhysicalDeviceMemoryProperties memProperties;
    _physicalDevice.getMemoryProperties(&memProperties);

    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            return i;
        }
    }

    throw std::runtime_error("failed to find suitable memory type!");
}

void Application::createUniformBuffers()
{

    _inputBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    _inputBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
    _inputBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

    _viewBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    _viewBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
    _viewBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

    _sceneBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    _sceneBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
    _sceneBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

    _triangleBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    _triangleBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
    _triangleBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

    _meshBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    _meshBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
    _meshBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

    for (std::size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        createBuffer(sizeof(InputUBO), vk::BufferUsageFlagBits::eUniformBuffer, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent, _inputBuffers[i], _inputBuffersMemory[i]);
        if (_device.mapMemory(_inputBuffersMemory[i], 0, sizeof(InputUBO), vk::MemoryMapFlags(), &_inputBuffersMapped[i]) != vk::Result::eSuccess) {
            throw std::runtime_error("failed to map memory of InputUBO!");
        }

        createBuffer(sizeof(ViewUBO), vk::BufferUsageFlagBits::eUniformBuffer, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent,
                     _viewBuffers[i], _viewBuffersMemory[i]);
        if (_device.mapMemory(_viewBuffersMemory[i], 0, sizeof(ViewUBO), vk::MemoryMapFlags(), &_viewBuffersMapped[i]) != vk::Result::eSuccess) {
            throw std::runtime_error("failed to map memory of ViewUBO!");
        }

        createBuffer(sizeof(SceneUBO), vk::BufferUsageFlagBits::eUniformBuffer, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent, _sceneBuffers[i], _sceneBuffersMemory[i]);
        if (_device.mapMemory(_sceneBuffersMemory[i], 0, sizeof(SceneUBO), vk::MemoryMapFlags(), &_sceneBuffersMapped[i]) != vk::Result::eSuccess) {
            throw std::runtime_error("failed to map memory of SceneUBO!");
        }

        createBuffer((int) (sizeof(Triangle) * _numTriangles), vk::BufferUsageFlagBits::eStorageBuffer, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent | vk::MemoryPropertyFlagBits::eDeviceLocal, _triangleBuffers[i], _triangleBuffersMemory[i]);
        if (_device.mapMemory(_triangleBuffersMemory[i], 0, (int) (sizeof(Triangle) * _numTriangles), vk::MemoryMapFlags(), &_triangleBuffersMapped[i]) != vk::Result::eSuccess) {
            throw std::runtime_error("failed to map memory of Triangles!");
        }

        createBuffer((int) (sizeof(Mesh) * _numMeshes), vk::BufferUsageFlagBits::eStorageBuffer, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent | vk::MemoryPropertyFlagBits::eDeviceLocal, _meshBuffers[i], _meshBuffersMemory[i]);
        if (_device.mapMemory(_meshBuffersMemory[i], 0, (int) (sizeof(Mesh) * _numMeshes), vk::MemoryMapFlags(), &_meshBuffersMapped[i]) != vk::Result::eSuccess) {
            throw std::runtime_error("failed to map memory of Meshes!");
        }
    }
}

static vk::DescriptorSetLayoutBinding createDescriptorSetLayoutBinding(uint32_t binding, vk::DescriptorType descriptorType, vk::ShaderStageFlags stageFlags)
{
    vk::DescriptorSetLayoutBinding layoutBinding;
    layoutBinding.binding = binding;
    layoutBinding.descriptorType = descriptorType;
    layoutBinding.descriptorCount = 1;
    layoutBinding.stageFlags = stageFlags;
    layoutBinding.pImmutableSamplers = nullptr;
    return layoutBinding;
}

void Application::createDescriptorSetLayout()
{
    vk::DescriptorSetLayoutBinding inputImageLayoutBinding = createDescriptorSetLayoutBinding(0, vk::DescriptorType::eStorageImage, vk::ShaderStageFlagBits::eFragment);
    vk::DescriptorSetLayoutBinding inputsLayoutBinding = createDescriptorSetLayoutBinding(1, vk::DescriptorType::eUniformBuffer, vk::ShaderStageFlagBits::eFragment);

    vk::DescriptorSetLayoutBinding bindings[] = {inputImageLayoutBinding, inputsLayoutBinding};
    vk::DescriptorSetLayoutCreateInfo layoutInfo;
    layoutInfo.sType = vk::StructureType::eDescriptorSetLayoutCreateInfo;
    layoutInfo.bindingCount = 2;
    layoutInfo.pBindings = bindings;

    if (_device.createDescriptorSetLayout(&layoutInfo, nullptr, &_screenDescriptorSetLayout) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
}

void Application::createComputeDescriptorSetLayout()
{
    // Binding 0: Input image
    // Binding 1: Output image
    // Binding 2: View UBO
    // Binding 3: Scene UBO
    // Binding 4: Triangle buffer
    // Binding 5: Mesh buffer
    vk::DescriptorSetLayoutBinding inputImageLayoutBinding = createDescriptorSetLayoutBinding(0, vk::DescriptorType::eStorageImage, vk::ShaderStageFlagBits::eCompute);
    vk::DescriptorSetLayoutBinding outputImageLayoutBinding = createDescriptorSetLayoutBinding(1, vk::DescriptorType::eStorageImage, vk::ShaderStageFlagBits::eCompute);
    vk::DescriptorSetLayoutBinding viewLayoutBinding = createDescriptorSetLayoutBinding(2, vk::DescriptorType::eUniformBuffer, vk::ShaderStageFlagBits::eCompute);
    vk::DescriptorSetLayoutBinding sceneLayoutBinding = createDescriptorSetLayoutBinding(3, vk::DescriptorType::eUniformBuffer, vk::ShaderStageFlagBits::eCompute);
    vk::DescriptorSetLayoutBinding triangleLayoutBinding = createDescriptorSetLayoutBinding(4, vk::DescriptorType::eStorageBuffer, vk::ShaderStageFlagBits::eCompute);
    vk::DescriptorSetLayoutBinding meshLayoutBinding = createDescriptorSetLayoutBinding(5, vk::DescriptorType::eStorageBuffer, vk::ShaderStageFlagBits::eCompute);

    std::array<vk::DescriptorSetLayoutBinding, 6> bindings = {inputImageLayoutBinding, outputImageLayoutBinding, viewLayoutBinding, sceneLayoutBinding, triangleLayoutBinding, meshLayoutBinding};
    vk::DescriptorSetLayoutCreateInfo layoutInfo;
    layoutInfo.sType = vk::StructureType::eDescriptorSetLayoutCreateInfo;
    layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
    layoutInfo.pBindings = bindings.data();

    if (_device.createDescriptorSetLayout(&layoutInfo, nullptr, &_computeDescriptorSetLayout) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to create compute descriptor set layout!");
    }
}

void Application::updateUniformBuffer(uint32_t currentImage)
{
    // Prepare input buffer
    InputUBO inputUBO{};
    inputUBO.iResolution = glm::vec2(_swapChainExtent.width, _swapChainExtent.height);
    // Copy to buffer
    memcpy(_inputBuffersMapped[currentImage], &inputUBO, sizeof(inputUBO));
}

void Application::updateComputeUniformBuffer(uint32_t currentImage)
{
    if (!_scene)
        return;

    ViewUBO viewUBO{};
    viewUBO.iCameraMatrix = _camera->getTransform().getTransformationMatrix();
    viewUBO.iCameraPosition = _camera->getTransform().getPosition();
    viewUBO.iResolution =
            glm::vec2(_swapChainExtent.width, _swapChainExtent.height);
    viewUBO.iViewPlaneParams = _camera->getViewParams();

    memcpy(_viewBuffersMapped[currentImage], &viewUBO, sizeof(viewUBO));

    if (_sceneChanged) {
        _frameCount = 0;
    }

    SceneUBO sceneUBO{};
    sceneUBO.iNumTriangles = _numTriangles;
    sceneUBO.iNumMeshes = _numMeshes;
    sceneUBO.iSceneChanged = _sceneChanged ? 1 : 0;
    sceneUBO.iSkyboxEnabled = _scene->isSkyBoxEnabled() ? 1 : 0;
    sceneUBO.iFrameIndex = _frameIndex;
    sceneUBO.iFrameCount = _frameCount;
    memcpy(_sceneBuffersMapped[currentImage], &sceneUBO, sizeof(sceneUBO));

    if (_sceneChanged) {
        for (std::size_t i = 0; i < _numMeshes; i++) {
            _meshes[i].transform = _scene->getObject((int) i)
                                           ->getTransform()
                                           .getTransformationMatrix();
        }
    }

    memcpy(_triangleBuffersMapped[currentImage], _triangles.data(), sizeof(Triangle) * _numTriangles);

    memcpy(_meshBuffersMapped[currentImage], _meshes.data(), sizeof(Mesh) * _numMeshes);
    _sceneChanged = false;
    _frameCount++;
}

void Application::createDescriptorPool()
{
    vk::DescriptorPoolSize uniforms;
    uniforms.type = vk::DescriptorType::eUniformBuffer;
    uniforms.descriptorCount = static_cast<uint32_t>(1);

    vk::DescriptorPoolSize image;
    image.type = vk::DescriptorType::eStorageImage;
    image.descriptorCount = static_cast<uint32_t>(1);

    std::array<vk::DescriptorPoolSize, 2> poolSizes = {uniforms, image};

    vk::DescriptorPoolCreateInfo poolInfo;
    poolInfo.sType = vk::StructureType::eDescriptorPoolCreateInfo;
    poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
    poolInfo.pPoolSizes = poolSizes.data();
    poolInfo.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

    if (_device.createDescriptorPool(&poolInfo, nullptr, &_screenDescriptorPool) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to create descriptor pool!");
    }
}

void Application::createComputeDescriptorPool()
{
    vk::DescriptorPoolSize imagePool;
    imagePool.type = vk::DescriptorType::eStorageImage;
    imagePool.descriptorCount = static_cast<uint32_t>(2);

    vk::DescriptorPoolSize uniformPool;
    uniformPool.type = vk::DescriptorType::eUniformBuffer;
    uniformPool.descriptorCount = static_cast<uint32_t>(2);

    vk::DescriptorPoolSize storagePool;
    storagePool.type = vk::DescriptorType::eStorageBuffer;
    storagePool.descriptorCount = static_cast<uint32_t>(2);

    std::array<vk::DescriptorPoolSize, 3> poolSizes = {imagePool, uniformPool, storagePool};

    vk::DescriptorPoolCreateInfo poolInfo;
    poolInfo.sType = vk::StructureType::eDescriptorPoolCreateInfo;
    poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
    poolInfo.pPoolSizes = poolSizes.data();
    poolInfo.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

    if (_device.createDescriptorPool(&poolInfo, nullptr, &_computeDescriptorPool) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to create compute descriptor pool!");
    }
}

void Application::createDescriptorSets()
{
    std::vector<vk::DescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT,
                                                 _screenDescriptorSetLayout);

    vk::DescriptorSetAllocateInfo allocInfo;
    allocInfo.sType = vk::StructureType::eDescriptorSetAllocateInfo;
    allocInfo.descriptorPool = _screenDescriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(layouts.size());
    allocInfo.pSetLayouts = layouts.data();

    _screenDescriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
    if (_device.allocateDescriptorSets(&allocInfo,
                                       _screenDescriptorSets.data()) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to allocate descriptor sets!");
    }

    for (std::size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vk::DescriptorImageInfo imageInfo;
        imageInfo.imageLayout = vk::ImageLayout::eGeneral;
        imageInfo.imageView = _textureImageView;

        vk::WriteDescriptorSet imageDescriptorWrite;
        imageDescriptorWrite.sType = vk::StructureType::eWriteDescriptorSet;
        imageDescriptorWrite.dstSet = _screenDescriptorSets[i];
        imageDescriptorWrite.dstBinding = 0;
        imageDescriptorWrite.dstArrayElement = 0;
        imageDescriptorWrite.descriptorType = vk::DescriptorType::eStorageImage;
        imageDescriptorWrite.descriptorCount = 1;
        imageDescriptorWrite.pImageInfo = &imageInfo;

        vk::DescriptorBufferInfo inputBufferInfo;
        inputBufferInfo.buffer = _inputBuffers[i];
        inputBufferInfo.offset = 0;
        inputBufferInfo.range = sizeof(InputUBO);

        vk::WriteDescriptorSet inputDescriptorWrite;
        inputDescriptorWrite.sType = vk::StructureType::eWriteDescriptorSet;
        inputDescriptorWrite.dstSet = _screenDescriptorSets[i];
        inputDescriptorWrite.dstBinding = 1;
        inputDescriptorWrite.dstArrayElement = 0;
        inputDescriptorWrite.descriptorType = vk::DescriptorType::eUniformBuffer;
        inputDescriptorWrite.descriptorCount = 1;
        inputDescriptorWrite.pBufferInfo = &inputBufferInfo;

        std::array<vk::WriteDescriptorSet, 2> descriptorWrites = {imageDescriptorWrite, inputDescriptorWrite};
        if (!descriptorWrites.empty()) {
            _device.updateDescriptorSets(static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
        }
    }
}

void Application::createComputeDescriptorSets()
{
    std::vector<vk::DescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT,
                                                 _computeDescriptorSetLayout);

    vk::DescriptorSetAllocateInfo allocInfo;
    allocInfo.sType = vk::StructureType::eDescriptorSetAllocateInfo;
    allocInfo.descriptorPool = _computeDescriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(layouts.size());
    allocInfo.pSetLayouts = layouts.data();
    _computeDescriptorSets.resize(MAX_FRAMES_IN_FLIGHT);

    if (_device.allocateDescriptorSets(&allocInfo,
                                       _computeDescriptorSets.data()) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to allocate descriptor sets!");
    }

    for (std::size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        // Input image
        vk::DescriptorImageInfo inputImageInfo;
        inputImageInfo.imageLayout = vk::ImageLayout::eGeneral;
        inputImageInfo.imageView = _computeInputImageView;

        vk::WriteDescriptorSet inputImageDescriptorWrite;
        inputImageDescriptorWrite.sType = vk::StructureType::eWriteDescriptorSet;
        inputImageDescriptorWrite.dstSet = _computeDescriptorSets[i];
        inputImageDescriptorWrite.dstBinding = 0;
        inputImageDescriptorWrite.dstArrayElement = 0;
        inputImageDescriptorWrite.descriptorType = vk::DescriptorType::eStorageImage;
        inputImageDescriptorWrite.descriptorCount = 1;
        inputImageDescriptorWrite.pImageInfo = &inputImageInfo;

        // Output image
        vk::DescriptorImageInfo outputImageInfo;
        outputImageInfo.imageLayout = vk::ImageLayout::eGeneral;
        outputImageInfo.imageView = _computeOutputImageView;

        vk::WriteDescriptorSet outputImageDescriptorWrite;
        outputImageDescriptorWrite.sType = vk::StructureType::eWriteDescriptorSet;
        outputImageDescriptorWrite.dstSet = _computeDescriptorSets[i];
        outputImageDescriptorWrite.dstBinding = 1;
        outputImageDescriptorWrite.dstArrayElement = 0;
        outputImageDescriptorWrite.descriptorType = vk::DescriptorType::eStorageImage;
        outputImageDescriptorWrite.descriptorCount = 1;
        outputImageDescriptorWrite.pImageInfo = &outputImageInfo;


        vk::DescriptorBufferInfo viewBufferInfo;
        viewBufferInfo.buffer = _viewBuffers[i];
        viewBufferInfo.offset = 0;
        viewBufferInfo.range = sizeof(ViewUBO);

        vk::WriteDescriptorSet viewDescriptorWrite;
        viewDescriptorWrite.sType = vk::StructureType::eWriteDescriptorSet;
        viewDescriptorWrite.dstSet = _computeDescriptorSets[i];
        viewDescriptorWrite.dstBinding = 2;
        viewDescriptorWrite.dstArrayElement = 0;
        viewDescriptorWrite.descriptorType = vk::DescriptorType::eUniformBuffer;
        viewDescriptorWrite.descriptorCount = 1;
        viewDescriptorWrite.pBufferInfo = &viewBufferInfo;

        vk::DescriptorBufferInfo sceneBufferInfo;
        sceneBufferInfo.buffer = _sceneBuffers[i];
        sceneBufferInfo.offset = 0;
        sceneBufferInfo.range = sizeof(SceneUBO);

        vk::WriteDescriptorSet sceneDescriptorWrite;
        sceneDescriptorWrite.sType = vk::StructureType::eWriteDescriptorSet;
        sceneDescriptorWrite.dstSet = _computeDescriptorSets[i];
        sceneDescriptorWrite.dstBinding = 3;
        sceneDescriptorWrite.dstArrayElement = 0;
        sceneDescriptorWrite.descriptorType = vk::DescriptorType::eUniformBuffer;
        sceneDescriptorWrite.descriptorCount = 1;
        sceneDescriptorWrite.pBufferInfo = &sceneBufferInfo;

        vk::DescriptorBufferInfo triangleBufferInfo;
        triangleBufferInfo.buffer = _triangleBuffers[i];
        triangleBufferInfo.offset = 0;
        triangleBufferInfo.range = (int) (sizeof(Triangle) * _numTriangles);

        vk::WriteDescriptorSet triangleDescriptorWrite;
        triangleDescriptorWrite.sType = vk::StructureType::eWriteDescriptorSet;
        triangleDescriptorWrite.dstSet = _computeDescriptorSets[i];
        triangleDescriptorWrite.dstBinding = 4;
        triangleDescriptorWrite.dstArrayElement = 0;
        triangleDescriptorWrite.descriptorType = vk::DescriptorType::eStorageBuffer;
        triangleDescriptorWrite.descriptorCount = 1;
        triangleDescriptorWrite.pBufferInfo = &triangleBufferInfo;

        vk::DescriptorBufferInfo meshesBufferInfo;
        meshesBufferInfo.buffer = _meshBuffers[i];
        meshesBufferInfo.offset = 0;
        meshesBufferInfo.range = (int) (sizeof(Mesh) * _numMeshes);

        vk::WriteDescriptorSet meshesDescriptorWrite;
        meshesDescriptorWrite.sType = vk::StructureType::eWriteDescriptorSet;
        meshesDescriptorWrite.dstSet = _computeDescriptorSets[i];
        meshesDescriptorWrite.dstBinding = 5;
        meshesDescriptorWrite.dstArrayElement = 0;
        meshesDescriptorWrite.descriptorType = vk::DescriptorType::eStorageBuffer;
        meshesDescriptorWrite.descriptorCount = 1;
        meshesDescriptorWrite.pBufferInfo = &meshesBufferInfo;


        std::array<vk::WriteDescriptorSet, 6> descriptorWrites = {inputImageDescriptorWrite, outputImageDescriptorWrite, viewDescriptorWrite, sceneDescriptorWrite, triangleDescriptorWrite, meshesDescriptorWrite};
        if (!descriptorWrites.empty()) {
            _device.updateDescriptorSets(static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
        }
    }

}

void Application::useCamera(std::size_t idx)
{
    _camera = &_scene->getCamera((int) idx);
}

void Application::cleanupSwapChain()
{
    for (auto & _swapChainFrameBuffer : _swapChainFrameBuffers) {
        _device.destroyFramebuffer(_swapChainFrameBuffer, nullptr);
    }

    for (auto & _swapChainImageView : _swapChainImageViews) {
        _device.destroyImageView(_swapChainImageView, nullptr);
    }

    _device.destroySwapchainKHR(_swapChain, nullptr);
}

void Application::recreateSwapChain()
{
    _device.waitIdle();

    cleanupSwapChain();

    createSwapChain();
    createImageViews();
    createFrameBuffers();
}

void Application::updateScene()
{
    _sceneChanged = true;
}

std::size_t Application::getFrameIndex() const
{
    return _frameIndex;
}

vk::Image &Application::getCurrentImage()
{
    return _computeOutputImage;
}

void Application::stop()
{
    _running = false;
}

vk::CommandBuffer Application::beginSingleTimeCommands()
{
    vk::CommandBufferAllocateInfo allocInfo;
    allocInfo.sType = vk::StructureType::eCommandBufferAllocateInfo;
    allocInfo.level = vk::CommandBufferLevel::ePrimary;
    allocInfo.commandPool = _commandPool;
    allocInfo.commandBufferCount = 1;

    vk::CommandBuffer commandBuffer;
    if (_device.allocateCommandBuffers(&allocInfo, &commandBuffer) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to allocate command buffer!");
    }

    vk::CommandBufferBeginInfo beginInfo;
    beginInfo.sType = vk::StructureType::eCommandBufferBeginInfo;
    beginInfo.flags = vk::CommandBufferUsageFlagBits::eOneTimeSubmit;

    if (commandBuffer.begin(&beginInfo) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }

    return commandBuffer;
}

void Application::screenshot(const std::string &filename)
{
    vk::Image src = getCurrentImage();

    vk::ImageCreateInfo imageInfo;
    imageInfo.sType = vk::StructureType::eImageCreateInfo;
    imageInfo.imageType = vk::ImageType::e2D;
    imageInfo.extent.width = _swapChainExtent.width;
    imageInfo.extent.height = _swapChainExtent.height;
    imageInfo.extent.depth = 1;
    imageInfo.mipLevels = 1;
    imageInfo.arrayLayers = 1;
    imageInfo.format = vk::Format::eR32G32B32A32Sfloat;
    imageInfo.tiling = vk::ImageTiling::eLinear;
    imageInfo.initialLayout = vk::ImageLayout::eUndefined;
    imageInfo.usage = vk::ImageUsageFlagBits::eTransferDst;
    imageInfo.samples = vk::SampleCountFlagBits::e1;
    imageInfo.sharingMode = vk::SharingMode::eExclusive;

    vk::Image dst;
    vk::DeviceMemory dstMemory;
    if (_device.createImage(&imageInfo, nullptr, &dst) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to create image!");
    }

    vk::MemoryRequirements memRequirements;
    _device.getImageMemoryRequirements(dst, &memRequirements);

    vk::MemoryAllocateInfo allocInfo;
    allocInfo.sType = vk::StructureType::eMemoryAllocateInfo;
    allocInfo.allocationSize = memRequirements.size;
    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent);

    if (_device.allocateMemory(&allocInfo, nullptr, &dstMemory) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to allocate image memory!");
    }

    _device.bindImageMemory(dst, dstMemory, 0);

    vk::CommandBuffer copyCommandBuffer = beginSingleTimeCommands();

    // Transition dst image to transfer destination layout
    vk::ImageMemoryBarrier barrier;
    barrier.sType = vk::StructureType::eImageMemoryBarrier;
    barrier.oldLayout = vk::ImageLayout::eUndefined;
    barrier.newLayout = vk::ImageLayout::eTransferDstOptimal;
    barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
    barrier.image = dst;
    barrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
    barrier.subresourceRange.baseMipLevel = 0;
    barrier.subresourceRange.levelCount = 1;
    barrier.subresourceRange.baseArrayLayer = 0;
    barrier.subresourceRange.layerCount = 1;
    barrier.srcAccessMask = vk::AccessFlags();
    barrier.dstAccessMask = vk::AccessFlagBits::eTransferWrite;

    copyCommandBuffer.pipelineBarrier(vk::PipelineStageFlagBits::eTopOfPipe, vk::PipelineStageFlagBits::eTransfer, vk::DependencyFlags(), nullptr, nullptr, barrier);

    // Transition src image to transfer source layout
    barrier.image = src;
    barrier.oldLayout = vk::ImageLayout::eTransferSrcOptimal;
    barrier.newLayout = vk::ImageLayout::eTransferSrcOptimal;
    barrier.srcAccessMask = vk::AccessFlags();
    barrier.dstAccessMask = vk::AccessFlagBits::eTransferRead;

    copyCommandBuffer.pipelineBarrier(vk::PipelineStageFlagBits::eTopOfPipe, vk::PipelineStageFlagBits::eTransfer, vk::DependencyFlags(), nullptr, nullptr, barrier);

    // Blit image
    vk::ImageBlit blit;
    blit.srcOffsets[0] = vk::Offset3D(0, 0, 0);
    blit.srcOffsets[1] = vk::Offset3D(_swapChainExtent.width, _swapChainExtent.height, 1);
    blit.srcSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
    blit.srcSubresource.mipLevel = 0;
    blit.srcSubresource.baseArrayLayer = 0;
    blit.srcSubresource.layerCount = 1;
    blit.dstOffsets[0] = vk::Offset3D(0, 0, 0);
    blit.dstOffsets[1] = vk::Offset3D(_swapChainExtent.width, _swapChainExtent.height, 1);
    blit.dstSubresource.aspectMask = vk::ImageAspectFlagBits::eColor;
    blit.dstSubresource.mipLevel = 0;
    blit.dstSubresource.baseArrayLayer = 0;
    blit.dstSubresource.layerCount = 1;

    copyCommandBuffer.blitImage(src, vk::ImageLayout::eTransferSrcOptimal, dst, vk::ImageLayout::eTransferDstOptimal, 1, &blit, vk::Filter::eLinear);

    // Transition dst image to general layout
    barrier.image = dst;
    barrier.oldLayout = vk::ImageLayout::eTransferDstOptimal;
    barrier.newLayout = vk::ImageLayout::eGeneral;
    barrier.srcAccessMask = vk::AccessFlagBits::eTransferWrite;
    barrier.dstAccessMask = vk::AccessFlags();

    copyCommandBuffer.pipelineBarrier(vk::PipelineStageFlagBits::eTransfer, vk::PipelineStageFlagBits::eTopOfPipe, vk::DependencyFlags(), nullptr, nullptr, barrier);

    // Transition src image to general layout
    barrier.image = src;
    barrier.oldLayout = vk::ImageLayout::eTransferSrcOptimal;
    barrier.newLayout = vk::ImageLayout::eGeneral;
    barrier.srcAccessMask = vk::AccessFlagBits::eTransferRead;
    barrier.dstAccessMask = vk::AccessFlags();

    copyCommandBuffer.pipelineBarrier(vk::PipelineStageFlagBits::eTransfer, vk::PipelineStageFlagBits::eTopOfPipe, vk::DependencyFlags(), nullptr, nullptr, barrier);

    // End command buffer
    copyCommandBuffer.end();

    // Submit command buffer
    vk::SubmitInfo submitInfo;
    submitInfo.sType = vk::StructureType::eSubmitInfo;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &copyCommandBuffer;

    if (_graphicsQueue.submit(1, &submitInfo, VK_NULL_HANDLE) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to submit command buffer!");
    }

    // Wait for queue to finish
    _graphicsQueue.waitIdle();

    // Get layout of the image
    vk::ImageSubresource subResource;
    subResource.aspectMask = vk::ImageAspectFlagBits::eColor;

    vk::SubresourceLayout subResourceLayout;
    _device.getImageSubresourceLayout(dst, &subResource, &subResourceLayout);

    const char *data;
    if (_device.mapMemory(dstMemory, 0, memRequirements.size, vk::MemoryMapFlags(), (void **) &data) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to map memory!");
    }

    // Save image
    std::ofstream file(filename, std::ios::out | std::ios::binary);
    file << "P6\n" << _swapChainExtent.width << " " << _swapChainExtent.height << "\n255\n";
    for (uint32_t y = 0; y < _swapChainExtent.height; y++) {
        for (uint32_t x = 0; x < _swapChainExtent.width; x++) {
            auto pixel = reinterpret_cast<const glm::vec4 *>(data);

            // Pixel format is R32G32B32A32SFloat
            // We need to convert it to R8G8B8A8
            float r = (float) (std::min(1.0f, std::max(0.0f, pixel->r)) * 255.0f);
            float g = (float) (std::min(1.0f, std::max(0.0f, pixel->g)) * 255.0f);
            float b = (float) (std::min(1.0f, std::max(0.0f, pixel->b)) * 255.0f);

            // Crank up the gamma
            float gamma = 1.0f / 2.2f;
            r = (255.0f * powf(r / 255.0f, gamma));
            g = (255.0f * powf(g / 255.0f, gamma));
            b = (255.0f * powf(b / 255.0f, gamma));

            // Convert to 8-bit
            uint8_t r8 = (uint8_t) r;
            uint8_t g8 = (uint8_t) g;
            uint8_t b8 = (uint8_t) b;

            file.write((char *) &r8, sizeof(uint8_t));
            file.write((char *) &g8, sizeof(uint8_t));
            file.write((char *) &b8, sizeof(uint8_t));
            data += sizeof(glm::vec4);
        }
    }
    file.close();

    // Unmap memory
    _device.unmapMemory(dstMemory);

    // Cleanup
    _device.freeCommandBuffers(_commandPool, 1, &copyCommandBuffer);
    _device.destroyImage(dst, nullptr);
    _device.freeMemory(dstMemory, nullptr);
}

Application::~Application() = default;
