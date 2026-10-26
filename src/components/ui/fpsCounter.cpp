#include "precomp.h"
#include "fpsCounter.h"
#include "central.h"
#include "textRenderer.h"

void FpsCounter::Start()
{
    _rend = _gameObject->GetComponent<TextRenderer>();
}


void FpsCounter::Tick()
{
    float realFPS = (1 / Central::dts);

    // Higher value as the gap between realFPS and smoothedFPS increases,
    // stops it from taking ages to catch up
    float dynamicSmoothing = (abs(1 - realFPS / _smoothedFPS)) / _smoothing;

    _smoothedFPS = (int)lerp(_smoothedFPS, realFPS, dynamicSmoothing);
    _rend->SetText(_converter.SetString(_smoothedFPS));

}