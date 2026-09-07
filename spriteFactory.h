#pragma once




class SpriteFactory
{

	void Init();
	static inline const char* addresses[10];
	static inline int frameCounts[10];

public:
	
	static Sprite* BuildSprite(int sprite);

};




