#include "precomp.h"
#include "colllider.h"
#include "central.h"
#include "utils.h"


// Constructors
Collider::Collider(string layer, Sprite* sprite) : layer(layer)
{
	//collisionSystem = scene->GetCollisionSystem();
	size.x = (float)sprite->GetWidth();
	size.y = (float)sprite->GetHeight();

	//UpdateRect(); // Cant be here because GameObject only gets set after constructor runs, set in first Tick
}

Collider::Collider(string layer, float2 size) : layer(layer), size(size)
{
	//collisionSystem = scene->GetCollisionSystem();
};

Collider::~Collider()
{
	//collisionSystem->Deregister(this); // Causes an issue on program shutdown - need to fix later
}


void Collider::Start()
{
	UpdateRect(gameObject->pos);// Idk if it actually matters whether this runs in Start() or only in first Tick()
	collisionSystem->Register(layer, this);
}

void Collider::Tick()
{
	UpdateRect(gameObject->pos);
	DrawCollider();
}

void Collider::UpdateRect(float2 pos)
{
	p1.x = round(pos.x - size.x / 2);
	p1.y = round(pos.y - size.y / 2);
	p2.x = round(pos.x + size.x / 2);
	p2.y = round(pos.y + size.y / 2);
}



bool CheckCollisionAxis(float aMin, float aMax, float bMin, float bMax)
{
	return aMin < bMax && aMax > bMin;
}

bool Collider::CollideAt(const float2 pos, Collider* col)
{
	if (!col->active) return false;
	// Cache pos
	float2 originalPos = gameObject->pos;

	// Move rect to check position
	UpdateRect(pos);

	const float2 colP1 = col->GetP1(); // float2 and pointer are both 8 bytes, so does it matter whther I pass by value or ptr / ref?
	const float2 colP2 = col->GetP2(); // Pass by pointer would cause more cache misses ??

	// AABB logic
	bool xCollision = CheckCollisionAxis(p1.x, p2.x, colP1.x, colP2.x);
	bool yCollision = CheckCollisionAxis(p1.y, p2.y, colP1.y, colP2.y);

	// Move rect back
	UpdateRect(originalPos);

	if (xCollision && yCollision) return true;
	else return false;
};

bool Collider::CollideAt(Tmpl8::float2 pos, std::string layer)
{
	// Cache pos
	float2 originalPos = gameObject->pos;

	for (auto& col : collisionSystem->GetLayer(layer))
	{
		if (!col->active) continue;
		// Move rect to check position
		UpdateRect(pos);

		const float2 colP1 = col->GetP1(); // float2 and pointer are both 8 bytes, so does it matter whther I pass by value or ptr / ref?
		const float2 colP2 = col->GetP2(); // Pass by pointer would cause more cache misses ??

		// AABB logic
		bool xCollision = CheckCollisionAxis(p1.x, p2.x, colP1.x, colP2.x);
		bool yCollision = CheckCollisionAxis(p1.y, p2.y, colP1.y, colP2.y);

		// Move rect back
		UpdateRect(originalPos);


		if (xCollision && yCollision)
		{
			//cout << "I'm colliding!!!" << endl;
			return true;
		}
	}
	return false;
}


Collider* Collider::CollideWith(const float2 pos, Collider* col)
{
	if (!col->active) return nullptr;
	// Cache pos
	float2 originalPos = gameObject->pos;

	// Move rect to check position
	UpdateRect(pos);

	const float2 colP1 = col->GetP1(); // float2 and pointer are both 8 bytes, so does it matter whther I pass by value or ptr / ref?
	const float2 colP2 = col->GetP2(); // Pass by pointer would cause more cache misses ??

	// AABB logic
	bool xCollision = CheckCollisionAxis(p1.x, p2.x, colP1.x, colP2.x);
	bool yCollision = CheckCollisionAxis(p1.y, p2.y, colP1.y, colP2.y);

	// Move rect back
	UpdateRect(originalPos);

	if (xCollision && yCollision) return col;
	else return nullptr;
};


Collider* Collider::CollideWith(Tmpl8::float2 pos, std::string layer)
{

	// Cache pos
	float2 originalPos = gameObject->pos;

	for (auto& col : collisionSystem->GetLayer(layer))
	{
		if (!col->active) continue;
		// Move rect to check position
		UpdateRect(pos);

		const float2 colP1 = col->GetP1(); // float2 and pointer are both 8 bytes, so does it matter whther I pass by value or ptr / ref?
		const float2 colP2 = col->GetP2(); // Pass by pointer would cause more cache misses ??

		// AABB logic
		bool xCollision = CheckCollisionAxis(p1.x, p2.x, colP1.x, colP2.x);
		bool yCollision = CheckCollisionAxis(p1.y, p2.y, colP1.y, colP2.y);

		// Move rect back
		UpdateRect(originalPos);


		if (xCollision && yCollision)
		{
			//cout << "I'm colliding!!!" << endl;
			return col;
		}
	}
	return nullptr;
}




void Collider::MoveAndCollide(string layer, float2 distance)
{
	float2& pos = gameObject->pos;

	auto& colliders = collisionSystem->GetLayer(layer);

	float2 targetPos = pos + distance;
	int xMoveSign = utils::sign(distance.x);
	int yMoveSign = utils::sign(distance.y);

	bool xCollide = false;
	bool yCollide = false;

	// Check for collisions against every collider in scene
	for (int i = 0; i < colliders.size(); i++)
	{
		Collider* col = colliders[i];

		for (int j = 0; j < abs(distance.x); j++)
		{
			xCollide = CollideAt(
				float2(pos.x + (j + 1 * xMoveSign), pos.y),
				col);

			if (xCollide)
			{
				targetPos.x = (pos.x + (j)*xMoveSign);
				break;
			}
		}

		for (int j = 0; j < abs(distance.y); j++)
		{
			yCollide = CollideAt(
				float2(pos.x, pos.y + (j + 1 * yMoveSign)),
				col);

			if (yCollide)
			{
				targetPos.y = (pos.y + (j)*yMoveSign);
				break;
			}
		}
	}

	// Handle x and y separately
	pos.x = targetPos.x;

	pos.y = targetPos.y;
}

void Collider::DrawCollider()
{
	if (!gameObject->debug) return;

	if (Central::camera == nullptr) return;

	float2 offset = Central::camera->pos;

	Central::surface->Box(
		(int)round(p1.x - offset.x),
		(int)round(p1.y - offset.y),
		(int)round(p2.x - offset.x),
		(int)round(p2.y - offset.y),
		0xFF0000);
};
