#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"
#include "FileSystem.h"
#include "Cloth.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void PassData();
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
Shader ourShader;
unsigned int VBO, VAO;
unsigned int texture;
Cloth cloth;
// world space positions of our cubes
glm::vec3 cubePositions = glm::vec3( 0.0f,  0.0f,  0.0f);
int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    //glfwSetCursorPosCallback(window, mouse_callback);
    //glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    ourShader =  Shader("camera.vs", "camera.fs");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        PassData();
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        // activate shader
        ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        // render boxes
        glBindVertexArray(VAO);
        
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, cubePositions);
        float angle = 0.0f;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        ourShader.setMat4("model", model);

        glDrawArrays(GL_TRIANGLES, 0, cloth.triangles.size()*3);
        cloth.Update();
        

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

void PassData()
{
    int g_width = cloth.cols;
    int g_height = cloth.rows;
    float vertices[5 * 6 * (g_width - 1) * (g_height - 1)];
    for(int i = 1; i < g_height; i++)
    {
        for(int j = 1; j < g_width; j++)
        {
            // (i,j)
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1)] =  cloth.particles[i * g_width + j].pos_cur[0]/100.0 * 1.3 - 0.65;
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 1] =  cloth.particles[i * g_width + j].pos_cur[1]/100.0 - 0.5;
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 2] =  cloth.particles[i * g_width + j].pos_cur[2]/100.0;
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 3] =  1.0 / g_width * j;
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 4] =  1.0 / g_height * i;
            
            // (i-1,j-1)
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 5] =  cloth.particles[(i - 1) * g_width + j - 1].pos_cur[0]/100.0 * 1.3 - 0.65;
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 6] =  cloth.particles[(i - 1) * g_width + j - 1].pos_cur[1]/100.0 - 0.5;
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 7] =  cloth.particles[(i - 1) * g_width + j - 1].pos_cur[2]/100.0;
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 8] =  1.0 / g_width * (j - 1);
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 9] =  1.0 / g_height * (i - 1);

            // (i,j-1)
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 10] =  cloth.particles[i * g_width + j - 1].pos_cur[0]/100.0 * 1.3 - 0.65;
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 11] =  cloth.particles[i * g_width + j - 1].pos_cur[1]/100.0 - 0.5;
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 12] =  cloth.particles[i * g_width + j - 1].pos_cur[2]/100.0;
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 13] =  1.0 / g_width * (j - 1);
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 14] =  1.0 / g_height * i;
            
            // (i,j)
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 15] =  cloth.particles[i * g_width + j].pos_cur[0]/100.0 * 1.3 - 0.65;
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 16] =  cloth.particles[i * g_width + j].pos_cur[1]/100.0 - 0.5;
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 17] =  cloth.particles[i * g_width + j].pos_cur[2]/100.0;
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 18] =  1.0 / g_width * j;
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 19] =  1.0 / g_height * i;

            // (i-1,j)
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 20] =  cloth.particles[(i - 1) * g_width + j].pos_cur[0]/100.0 * 1.3 - 0.65;
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 21] =  cloth.particles[(i - 1) * g_width + j].pos_cur[1]/100.0 - 0.5;
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 22] =  cloth.particles[(i - 1) * g_width + j].pos_cur[2]/100.0;
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 23] =  1.0 / g_width * j;
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 24] =  1.0 / g_height * (i - 1);
            
            // (i-1,j-1)
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 25] =  cloth.particles[(i - 1) * g_width + j - 1].pos_cur[0]/100.0 * 1.3 - 0.65;
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 26] =  cloth.particles[(i - 1) * g_width + j - 1].pos_cur[1]/100.0 - 0.5;
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 27] =  cloth.particles[(i - 1) * g_width + j - 1].pos_cur[2]/100.0;
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 28] =  1.0 / g_width * (j - 1);
            vertices[30 * ( (i - 1) * (g_width - 1) + j - 1) + 29] =  1.0 / g_height * (i - 1);
        }
    }



    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    // load and create a texture 
    // -------------------------

    // texture 1
    // ---------
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char *data = stbi_load(FileSystem::getPath("./texture/fu.jpg").c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    ourShader.setInt("texture", 0);

}