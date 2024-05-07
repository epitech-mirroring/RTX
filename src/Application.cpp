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
        if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics) {
            indices.graphicsFamily = i;
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
    _descriptorSetLayout = VK_NULL_HANDLE;
    _descriptorPool = VK_NULL_HANDLE;
}

Application::Application(unsigned int width, unsigned int height, const std::string &appName, Scene *scene)
{
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
        m.material = material;

        _meshes.push_back(m);
    }
    _descriptorSetLayout = VK_NULL_HANDLE;
    _descriptorPool = VK_NULL_HANDLE;
}

void Application::run(const std::function<void()>& update)
{
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
    createRenderPass();
    createDescriptorSetLayout();
    createGraphicsPipeline();
    createFrameBuffers();
    createCommandPool();
    createVertexBuffer();
    createIndexBuffer();
    createUniformBuffers();
    createDescriptorPool();
    createDescriptorSets();
    createCommandBuffer();
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
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

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
    _device.getQueue(indices.graphicsFamily.value(), 0, &_graphicsQueue);
    _device.getQueue(indices.presentFamily.value(), 0, &_presentQueue);
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
    while (!glfwWindowShouldClose(_window)) {
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

    for (std::size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        _device.destroyBuffer(_uniformBuffers[i], nullptr);
        _device.freeMemory(_uniformBuffersMemory[i], nullptr);

        _device.destroyBuffer(_sceneBuffers[i], nullptr);
        _device.freeMemory(_sceneBuffersMemory[i], nullptr);

        _device.destroyBuffer(_triangleBuffers[i], nullptr);
        _device.freeMemory(_triangleBuffersMemory[i], nullptr);

        _device.destroyBuffer(_meshBuffers[i], nullptr);
        _device.freeMemory(_meshBuffersMemory[i], nullptr);
    }
    _device.destroyDescriptorPool(_descriptorPool, nullptr);
    _device.destroyDescriptorSetLayout(_descriptorSetLayout, nullptr);

    _device.destroyBuffer(_screenIndexBuffer, nullptr);
    _device.freeMemory(_screenIndexBufferMemory, nullptr);

    _device.destroyBuffer(_screenVertexBuffer, nullptr);
    _device.freeMemory(_screenVertexBufferMemory, nullptr);

    for (std::size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        _device.destroySemaphore(_renderFinishedSemaphores[i], nullptr);
        _device.destroySemaphore(_imageAvailableSemaphores[i], nullptr);
        _device.destroyFence(_inFlightFences[i], nullptr);
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
    uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    if (indices.graphicsFamily != indices.presentFamily) {
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
    auto raytracingFrag = readFile("shaders/raytracing.spv");

    vk::ShaderModule screenShaderModule = createShaderModule(screenVert);
    vk::ShaderModule raytracingShaderModule = createShaderModule(raytracingFrag);

    // Raytracing pipeline
    vk::PipelineShaderStageCreateInfo screenShaderStageInfo;
    screenShaderStageInfo.sType = vk::StructureType::ePipelineShaderStageCreateInfo;
    screenShaderStageInfo.stage = vk::ShaderStageFlagBits::eVertex;
    screenShaderStageInfo.module = screenShaderModule;
    screenShaderStageInfo.pName = "main";

    vk::PipelineShaderStageCreateInfo raytracingShaderStageInfo;
    raytracingShaderStageInfo.sType = vk::StructureType::ePipelineShaderStageCreateInfo;
    raytracingShaderStageInfo.stage = vk::ShaderStageFlagBits::eFragment;
    raytracingShaderStageInfo.module = raytracingShaderModule;
    raytracingShaderStageInfo.pName = "main";

    vk::PipelineShaderStageCreateInfo shaderStages[] = {screenShaderStageInfo, raytracingShaderStageInfo};
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
    pipelineLayoutInfo.pSetLayouts = &_descriptorSetLayout;
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
    _device.destroyShaderModule(raytracingShaderModule, nullptr);
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

    vk::RenderPassCreateInfo renderPassInfo;
    renderPassInfo.sType = vk::StructureType::eRenderPassCreateInfo;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subPass;
    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &dependency;

    if (_device.createRenderPass(&renderPassInfo, nullptr, &_renderPass) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to create render pass!");
    }
}

void Application::createFrameBuffers()
{
    _swapChainFrameBuffers.resize(_swapChainImageViews.size());

    for (size_t i = 0; i < _swapChainImageViews.size(); i++) {
        vk::ImageView attachments[] = {
                _swapChainImageViews[i]
        };

        vk::FramebufferCreateInfo framebufferInfo;
        framebufferInfo.sType = vk::StructureType::eFramebufferCreateInfo;
        framebufferInfo.renderPass = _renderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
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
    poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

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
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;
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

    commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, _pipelineLayout, 0, 1, &_descriptorSets[_currentFrame], 0, nullptr);
    commandBuffer.drawIndexed(static_cast<uint32_t>(_screenIndices.size()), 1, 0, 0, 0);

    commandBuffer.endRenderPass();

    commandBuffer.end();
}

void Application::createSyncObjects()
{
    _imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    _renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
    _inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

    vk::SemaphoreCreateInfo semaphoreInfo;
    semaphoreInfo.sType = vk::StructureType::eSemaphoreCreateInfo;

    vk::FenceCreateInfo fenceInfo;
    fenceInfo.sType = vk::StructureType::eFenceCreateInfo;
    fenceInfo.flags = vk::FenceCreateFlagBits::eSignaled;

    for (std::size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        if (_device.createSemaphore(&semaphoreInfo, nullptr, &_imageAvailableSemaphores[i]) != vk::Result::eSuccess ||
            _device.createSemaphore(&semaphoreInfo, nullptr, &_renderFinishedSemaphores[i]) != vk::Result::eSuccess ||
            _device.createFence(&fenceInfo, nullptr, &_inFlightFences[i]) != vk::Result::eSuccess) {

            throw std::runtime_error("Failed to create synchronization objects for a frame!");
        }
    }
}

void Application::drawFrame()
{
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

    vk::SubmitInfo submitInfo;
    submitInfo.sType = vk::StructureType::eSubmitInfo;

    vk::Semaphore waitSemaphores[] = {_imageAvailableSemaphores[_currentFrame]};
    vk::PipelineStageFlags waitStages[] = {vk::PipelineStageFlagBits::eColorAttachmentOutput};
    submitInfo.waitSemaphoreCount = 1;
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

    _uniformBuffers.resize(MAX_FRAMES_IN_FLIGHT);
    _uniformBuffersMemory.resize(MAX_FRAMES_IN_FLIGHT);
    _uniformBuffersMapped.resize(MAX_FRAMES_IN_FLIGHT);

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
        createBuffer(sizeof(ViewUBO), vk::BufferUsageFlagBits::eUniformBuffer, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent, _uniformBuffers[i], _uniformBuffersMemory[i]);
        if (_device.mapMemory(_uniformBuffersMemory[i], 0, sizeof(ViewUBO), vk::MemoryMapFlags(), &_uniformBuffersMapped[i]) != vk::Result::eSuccess) {
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
    vk::DescriptorSetLayoutBinding viewLayoutBinding = createDescriptorSetLayoutBinding(0, vk::DescriptorType::eUniformBuffer, vk::ShaderStageFlagBits::eFragment);
    vk::DescriptorSetLayoutBinding sceneLayoutBinding = createDescriptorSetLayoutBinding(1, vk::DescriptorType::eUniformBuffer, vk::ShaderStageFlagBits::eFragment | vk::ShaderStageFlagBits::eVertex);
    vk::DescriptorSetLayoutBinding triangleLayoutBinding = createDescriptorSetLayoutBinding(2, vk::DescriptorType::eStorageBuffer, vk::ShaderStageFlagBits::eFragment | vk::ShaderStageFlagBits::eVertex);
    vk::DescriptorSetLayoutBinding meshLayoutBinding = createDescriptorSetLayoutBinding(3, vk::DescriptorType::eStorageBuffer, vk::ShaderStageFlagBits::eFragment | vk::ShaderStageFlagBits::eVertex);

    vk::DescriptorSetLayoutBinding bindings[] = {viewLayoutBinding, sceneLayoutBinding, triangleLayoutBinding, meshLayoutBinding};

    vk::DescriptorSetLayoutCreateInfo layoutInfo;
    layoutInfo.sType = vk::StructureType::eDescriptorSetLayoutCreateInfo;
    layoutInfo.bindingCount = 4;
    layoutInfo.pBindings = bindings;

    if (_device.createDescriptorSetLayout(&layoutInfo, nullptr, &_descriptorSetLayout) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to create descriptor set layout!");
    }
}

void Application::updateUniformBuffer(uint32_t currentImage)
{
    if (!_camera) {
        static auto startTime = std::chrono::high_resolution_clock::now();

        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(
                             currentTime - startTime)
                             .count();

        Transform transform;
        transform.rotate(glm::vec3(0.f, 1.f, 0.f), time * glm::radians(90.f));
        Camera camera(transform, 60.0f, _windowSize.x / _windowSize.y, 1.f);

        ViewUBO viewUBO{};
        viewUBO.iCameraMatrix = camera.getTransform().getTransformationMatrix();
        viewUBO.iCameraPosition = camera.getTransform().getPosition();
        viewUBO.iResolution =
                glm::vec2(_swapChainExtent.width, _swapChainExtent.height);
        viewUBO.iViewPlaneParams = camera.getViewParams();

        memcpy(_uniformBuffersMapped[currentImage], &viewUBO, sizeof(viewUBO));
    } else {
        ViewUBO viewUBO{};
        viewUBO.iCameraMatrix = _camera->getTransform().getTransformationMatrix();
        viewUBO.iCameraPosition = _camera->getTransform().getPosition();
        viewUBO.iResolution =
                glm::vec2(_swapChainExtent.width, _swapChainExtent.height);
        viewUBO.iViewPlaneParams = _camera->getViewParams();

        memcpy(_uniformBuffersMapped[currentImage], &viewUBO, sizeof(viewUBO));
    }

    if (!_scene) {
        return;
    }

    SceneUBO sceneUBO{};
    sceneUBO.iNumTriangles = _numTriangles;
    sceneUBO.iNumMeshes = _numMeshes;
    sceneUBO.iSceneChanged = _sceneChanged ? 1 : 0;
    sceneUBO.iSkyboxEnabled = _scene->isSkyBoxEnabled() ? 1 : 0;
    sceneUBO.iFrameIndex = _frameIndex;
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
}

void Application::createDescriptorPool()
{
    vk::DescriptorPoolSize uniforms;
    uniforms.type = vk::DescriptorType::eUniformBuffer;
    uniforms.descriptorCount = static_cast<uint32_t>(2);

    vk::DescriptorPoolSize storageBuffers;
    storageBuffers.type = vk::DescriptorType::eStorageBuffer;
    storageBuffers.descriptorCount = static_cast<uint32_t>(2);

    std::array<vk::DescriptorPoolSize, 2> poolSizes = {uniforms, storageBuffers};

    vk::DescriptorPoolCreateInfo poolInfo;
    poolInfo.sType = vk::StructureType::eDescriptorPoolCreateInfo;
    poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
    poolInfo.pPoolSizes = poolSizes.data();
    poolInfo.maxSets = static_cast<uint32_t>(MAX_FRAMES_IN_FLIGHT);

    if (_device.createDescriptorPool(&poolInfo, nullptr, &_descriptorPool) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to create descriptor pool!");
    }
}

void Application::createDescriptorSets()
{
    std::vector<vk::DescriptorSetLayout> layouts(MAX_FRAMES_IN_FLIGHT, _descriptorSetLayout);

    vk::DescriptorSetAllocateInfo allocInfo;
    allocInfo.sType = vk::StructureType::eDescriptorSetAllocateInfo;
    allocInfo.descriptorPool = _descriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(layouts.size());
    allocInfo.pSetLayouts = layouts.data();

    _descriptorSets.resize(MAX_FRAMES_IN_FLIGHT);
    if (_device.allocateDescriptorSets(&allocInfo, _descriptorSets.data()) != vk::Result::eSuccess) {
        throw std::runtime_error("failed to allocate descriptor sets!");
    }

    for (std::size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vk::DescriptorBufferInfo viewBufferInfo;
        viewBufferInfo.buffer = _uniformBuffers[i];
        viewBufferInfo.offset = 0;
        viewBufferInfo.range = sizeof(ViewUBO);

        vk::WriteDescriptorSet viewDescriptorWrite;
        viewDescriptorWrite.sType = vk::StructureType::eWriteDescriptorSet;
        viewDescriptorWrite.dstSet = _descriptorSets[i];
        viewDescriptorWrite.dstBinding = 0;
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
        sceneDescriptorWrite.dstSet = _descriptorSets[i];
        sceneDescriptorWrite.dstBinding = 1;
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
        triangleDescriptorWrite.dstSet = _descriptorSets[i];
        triangleDescriptorWrite.dstBinding = 2;
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
        meshesDescriptorWrite.dstSet = _descriptorSets[i];
        meshesDescriptorWrite.dstBinding = 3;
        meshesDescriptorWrite.dstArrayElement = 0;
        meshesDescriptorWrite.descriptorType = vk::DescriptorType::eStorageBuffer;
        meshesDescriptorWrite.descriptorCount = 1;
        meshesDescriptorWrite.pBufferInfo = &meshesBufferInfo;

        std::array<vk::WriteDescriptorSet, 4> descriptorWrites = {viewDescriptorWrite, sceneDescriptorWrite, triangleDescriptorWrite, meshesDescriptorWrite};
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

Application::~Application() = default;
