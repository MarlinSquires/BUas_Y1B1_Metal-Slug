#include "precomp.h"
#include "inputHandler.h"

InputHandler::InputHandler()
{
    // Zero-initialize both arrays
    for (int i = 0; i < 512; ++i)
    {
        m_KeyState[i] = 0;
        m_PrevKeyState[i] = 0;
    }
}

InputHandler::~InputHandler()
{
}

void InputHandler::Update()
{
    // Save current state as previous
    for (int i = 0; i < 512; ++i)
    {
        m_PrevKeyState[i] = m_KeyState[i];
    }
}

bool InputHandler::IsKeyPressed(int key)
{
    int index = key & 511;
    return m_KeyState[index] != 0;
}

bool InputHandler::IsKeyDown(int key)
{
    int index = key & 511;
    return m_KeyState[index] != 0 && m_PrevKeyState[index] == 0;
}

bool InputHandler::IsKeyUp(int key)
{
    int index = key & 511;
    return m_KeyState[index] == 0 && m_PrevKeyState[index] != 0;
}

void InputHandler::SetKeyState(int key, bool pressed)
{
    int index = key & 511;
    m_KeyState[index] = pressed ? 1 : 0;
}









