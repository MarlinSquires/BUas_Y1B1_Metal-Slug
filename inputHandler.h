#pragma once

class InputHandler
{
public:
    InputHandler();
    ~InputHandler();

    // Call once per frame before input processing
    void Update();

    // Query input state
    bool IsKeyPressed(int key);      // Key is currently held
    bool IsKeyDown(int key);         // Key just pressed this frame
    bool IsKeyUp(int key);           // Key just released this frame

    // Set key state (called from GLFW callback)
    void SetKeyState(int key, bool pressed);

    // Access to raw keystate for direct queries
    const unsigned char* GetKeyStateBuffer() const { return m_KeyState; }

private:
    unsigned char m_KeyState[512];      // Current frame key states
    unsigned char m_PrevKeyState[512];  // Previous frame key states
};

