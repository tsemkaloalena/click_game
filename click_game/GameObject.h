#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

namespace GameObject {
    bool CollisionTest(const Sprite& Object1, const Sprite& Object2, int AlphaLimit = 0);
    bool CollisionsTest(const Sprite& Object, const Sprite* Objects);
    bool MaskedTexture(Texture& LoadInto, const std::string& Filename);
    bool CursorCheck(int x, int y, Text Object);
    void ScoreRecord(int score);
    std::string getScoreList(int &start, int k);
    std::string getBestResult();

    class MaskOfGameObject
    {
    public:
        MaskOfGameObject();
        int GetPixel(const int* mask, const Texture* tex, int x, int y);
        int* GetMask(const Texture* tex);
        int* CreateMask(const Texture* tex, const Image& img);
    private:
        std::map<const Texture*, int*> Bitmasks;
    };
};