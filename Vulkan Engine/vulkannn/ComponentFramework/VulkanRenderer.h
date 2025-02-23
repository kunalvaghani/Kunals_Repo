#ifndef VULKANRENDERER_H 
#define VULKANRENDERER_H

#include <SDL.h>
#include <SDL_vulkan.h>
#include <SDL_image.h>
#include <vulkan/vulkan.h>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <optional>
#include <set>
#include <unordered_map>
#include <array>
#include <Vector.h>
#include <VMath.h>
#include <MMath.h>
#include <Hash.h>
using namespace MATH;

#include "Renderer.h"

#ifdef NDEBUG /// only use validation layers if in debug mode
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

//void SetNormalMatrix(Matrix4 normalMatrix_);

struct QueueFamilyIndices {
    /// optional means that it contains no value until it is assigned
    /// has_value() returns false if no has ever been assigned. 
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

// model matrix push constant

struct ModelMatrixPushConst {
    Matrix4 modelMatrix;
    Matrix4 normalMatrix;
};


struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

    struct Vertex {
        Vec3 pos;
        Vec3 normal;
        Vec2 texCoord;

         /// Used in vertex deduplication
        bool operator == (const Vertex& other) const {
            return pos == other.pos && normal == other.normal && texCoord == other.texCoord;
        }   


        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, normal);

            attributeDescriptions[2].binding = 0;
            attributeDescriptions[2].location = 2;
            attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

            return attributeDescriptions;
        }
       
    }; /// End of struct Vertex


    /// Generate a hash of a Vertex, used in vertex deduplication
    /// Adding this to namespace std is called a namespace injection
    namespace std {
        template<> struct hash<Vertex> {
            size_t operator()(Vertex const& vertex) const noexcept {
                size_t hash1 = hash<Vec3>()(vertex.pos);
                size_t hash2 = hash<Vec3>()(vertex.normal);
                size_t hash3 = hash<Vec2>()(vertex.texCoord);
                size_t result = ((hash1 ^ (hash2 << 1)) >> 1) ^ (hash3 << 1);
                return result;
            }
        };
    }

struct BufferMemory {
    VkBuffer bufferID;
    VkDeviceMemory bufferMemoryID;
    VkDeviceMemory bufferMemoryLength;
};

struct IndexedVertexBuffer {
    VkBuffer vertBufferID;
    VkDeviceMemory vertBufferMemoryID;
    VkDeviceSize vertBufferLength;

    VkBuffer indexBufferID;
    VkDeviceMemory indexBufferMemoryID;
    VkDeviceSize indexBufferLength;
};

struct Sampler2Ddata {
    VkImage Textureimage;
    VkDeviceMemory textureimageMemory;
    VkImageView textureimageView;
	VkSampler texturesampler;
};

struct CameraUBO { /// A UniformBufferObject
    Matrix4 projectionMatrix;
    Matrix4 viewMatrix;
    Matrix4 modelMatrix;/// This doesn't belong here. We'll fix it.
};

#define MAX_LIGHTS 4
struct LightUBO { /// A UniformBufferObject
    Vec4 position[MAX_LIGHTS];
    Vec4 diffuse[MAX_LIGHTS];
    uint32_t numberoflights;

};


struct Sampler2D {
    VkImage image;
    VkDeviceMemory imageDeviceMemory;
    VkImageView imageView;
    VkSampler sampler;
};

struct PipeLine {
    VkPipeline pipelineID;
    VkPipelineLayout pipelineLayout;
};

class VulkanRenderer : public Renderer {
    /// C11 precautions 
    VulkanRenderer(const VulkanRenderer&) = delete;  /// Copy constructor
    VulkanRenderer(VulkanRenderer&&) = delete;       /// Move constructor
    VulkanRenderer& operator=(const VulkanRenderer&) = delete; /// Copy operator
    VulkanRenderer& operator=(VulkanRenderer&&) = delete;      /// Move operator

public: /// Member functions
    VulkanRenderer();
    ~VulkanRenderer();
    SDL_Window* CreateWindow(std::string name_, int width, int height);
    SDL_Window* GetWindow() { return window; }
    void SetModelMatrix(const Matrix4& modelMatrix_,const Matrix4& modelMatrix_1);

    bool OnCreate();
    void OnDestroy();
    void Render();
    

    void SetCameraUBO(const Matrix4& projection, const Matrix4& view, const Matrix4& model);
    void SetLightUBO(const Vec4 pos[MAX_LIGHTS], const Vec4 diffuse[MAX_LIGHTS], uint32_t numberoflights);
    void Create2DTextureImage(const char* texureFile, Sampler2Ddata& textureData);
    PipeLine CreateGraphicsPipeline(const char* vertFile, const char* fragFile, const char* geomFile);

    IndexedVertexBuffer LoadModelIndexed(const char* filename);
    void RecreateSwapChain();

private: /// Private member variables
    const size_t MAX_FRAMES_IN_FLIGHT = 2;
    size_t currentFrame = 0;
    SDL_Event sdlEvent;
    uint32_t windowWidth;
    uint32_t windowHeight;
    SDL_Window* window;
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkRenderPass renderPass;
    VkDescriptorPool descriptorPool;
    VkDescriptorSetLayout descriptorSetLayout;
   // std::vector<ModelMatrixPushConst> pushConst;
    ModelMatrixPushConst pushConst;
    ModelMatrixPushConst pushConst1;
    
   
    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;
    VkCommandPool commandPool;

    //Textures
    Sampler2Ddata textures[2];
    bool isTexture1 = true;
  

    VkSwapchainKHR swapChain;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;

    /// These are in vectors because they depend of the number of swapchains
    std::vector<VkDescriptorSet> descriptorSets;
    std::vector<VkCommandBuffer> commandBuffers;
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    std::vector<VkFence> imagesInFlight;
    std::vector<VkImage> swapChainImages;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;
    template<class T>
    std::vector<BufferMemory> createUniformBuffers();

    VkQueue graphicsQueue;
    VkQueue presentQueue;
    Sampler2D texture2D;
    CameraUBO cameraUBO;
    LightUBO lightUBO;
    CameraUBO cameraUBOdata;
    LightUBO lightUBOdata;
    std::vector<IndexedVertexBuffer> indexedVertexBuffers;
    std::vector<BufferMemory> cameraUboBuffers;
    std::vector<BufferMemory> lightUboBuffers;
    std::vector<PipeLine> graphicsPipelines;

private: /// Member functions
    bool hasStencilComponent(VkFormat format);
    void createInstance();
    void createSurface();
    void createLogicalDevice();
    void createSwapChain();
    void createImageViews();

    template <class T>
    void updateUniformBuffer(const T srcData, const BufferMemory& bufferMemory);
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
    void createRenderPass();
    void createDescriptorSetLayout();
   
    void createFramebuffers();
    void recordCommandBuffer();
    void createCommandPool();
    void createDepthResources();
   
    void createTextureImageView(Sampler2Ddata& textureData);
    void createTextureSampler(Sampler2Ddata& textureData);
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling,
        VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
   
    /// A helper function for createVertexBuffer()
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);

    void createVertexBuffer(IndexedVertexBuffer &indexedVertexBuffer, const std::vector<Vertex> &vertices);
    void createIndexBuffer(IndexedVertexBuffer &indexedVertexBuffer, const std::vector<uint32_t> &indices);
  
    void createDescriptorPool();
    void createDescriptorSets(Sampler2Ddata& textureData);
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    void createCommandBuffers();
    void createSyncObjects();
    void cleanupSwapChain();
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);

    VkFormat findDepthFormat();
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

    VkResult createDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    void destroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void setupDebugMessenger();

    void pickPhysicalDevice();
    bool isDeviceSuitable(VkPhysicalDevice device);
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    std::vector<const char*> getRequiredExtensions();
    bool checkValidationLayerSupport();

    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
    VkShaderModule createShaderModule(const std::vector<char>& code);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, 
         VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
    static std::vector<char> readFile(const std::string& filename);
};
#endif 

