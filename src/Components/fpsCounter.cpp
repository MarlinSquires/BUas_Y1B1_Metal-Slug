#include "precomp.h"
#include "fpsCounter.h"
#include "central.h"
#include "textRenderer.h"

void FpsCounter::Start()
{
    rend = gameObject->GetComponent<TextRenderer>();
    //rend->text = to_string(smoothedFPS).c_str();
}


void FpsCounter::Tick()
{
    float realFPS = (1 / Central::dts);

    // Higher value as the gap between realFPS and smoothedFPS increases,
    // stops it from taking ages to catch up
    float dynamicSmoothing = (abs(1 - realFPS / smoothedFPS)) / smoothing;

    smoothedFPS = (int)lerp(smoothedFPS, realFPS, dynamicSmoothing);
    snprintf(textBuffer, sizeof(textBuffer), "%d", smoothedFPS);
    rend->text = textBuffer;
    //printf("FPS: %d \n", smoothedFPS);

}