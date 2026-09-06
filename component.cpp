#include "precomp.h"
#include "component.h"

Component::~Component() = default;

// leaving them empty, but not gonna make it pure virtual cos not every component will need a start/update
void Component::Start() {};

void Component::Tick() {};


