//#include <SFML/Graphics.hpp>
//#include <map>
//#include "Collision.h"
//using namespace sf;
//
//namespace Collision
//{
//    class BitmaskManager
//    {
//    public:
//        ~BitmaskManager() {
//            std::map<const Texture*, Uint8*>::const_iterator end = Bitmasks.end();
//            for (std::map<const Texture*, Uint8*>::const_iterator iter = Bitmasks.begin(); iter != end; iter++)
//                delete[] iter->second;
//        }
//
//        Uint8 GetPixel(const Uint8* mask, const Texture* tex, unsigned int x, unsigned int y) {
//            if (x > tex->getSize().x || y > tex->getSize().y)
//                return 0;
//
//            return mask[x + y * tex->getSize().x];
//        }
//
//        Uint8* GetMask(const Texture* tex) {
//            Uint8* mask;
//            std::map<const Texture*, Uint8*>::iterator pair = Bitmasks.find(tex);
//            if (pair == Bitmasks.end())
//            {
//                Image img = tex->copyToImage();
//                mask = CreateMask(tex, img);
//            }
//            else
//                mask = pair->second;
//
//            return mask;
//        }
//
//        Uint8* CreateMask(const Texture* tex, const Image& img) {
//            Uint8* mask = new Uint8[tex->getSize().y * tex->getSize().x];
//
//            for (unsigned int y = 0; y < tex->getSize().y; y++)
//            {
//                for (unsigned int x = 0; x < tex->getSize().x; x++)
//                    mask[x + y * tex->getSize().x] = img.getPixel(x, y).a;
//            }
//
//            Bitmasks.insert(std::pair<const Texture*, Uint8*>(tex, mask));
//
//            return mask;
//        }
//    private:
//        std::map<const Texture*, Uint8*> Bitmasks;
//    };
//
//    BitmaskManager Bitmasks;
//
//    bool PixelPerfectTest(const Sprite& Object1, const Sprite& Object2, Uint8 AlphaLimit) {
//        FloatRect Intersection;
//        if (Object1.getGlobalBounds().intersects(Object2.getGlobalBounds(), Intersection)) {
//            IntRect O1SubRect = Object1.getTextureRect();
//            IntRect O2SubRect = Object2.getTextureRect();
//
//            Uint8* mask1 = Bitmasks.GetMask(Object1.getTexture());
//            Uint8* mask2 = Bitmasks.GetMask(Object2.getTexture());
//
//            // Loop through our pixels
//            for (int i = Intersection.left; i < Intersection.left + Intersection.width; i++) {
//                for (int j = Intersection.top; j < Intersection.top + Intersection.height; j++) {
//
//                    Vector2f o1v = Object1.getInverseTransform().transformPoint(i, j);
//                    Vector2f o2v = Object2.getInverseTransform().transformPoint(i, j);
//
//                    // Make sure pixels fall within the sprite's subrect
//                    if (o1v.x > 0 && o1v.y > 0 && o2v.x > 0 && o2v.y > 0 &&
//                        o1v.x < O1SubRect.width && o1v.y < O1SubRect.height &&
//                        o2v.x < O2SubRect.width && o2v.y < O2SubRect.height) {
//
//                        if (Bitmasks.GetPixel(mask1, Object1.getTexture(), (int)(o1v.x) + O1SubRect.left, (int)(o1v.y) + O1SubRect.top) > AlphaLimit &&
//                            Bitmasks.GetPixel(mask2, Object2.getTexture(), (int)(o2v.x) + O2SubRect.left, (int)(o2v.y) + O2SubRect.top) > AlphaLimit)
//                            return true;
//
//                    }
//                }
//            }
//        }
//        return false;
//    }
//
//    bool CreateTextureAndBitmask(Texture& LoadInto, const std::string& Filename)
//    {
//        Image img;
//        if (!img.loadFromFile(Filename))
//            return false;
//        if (!LoadInto.loadFromImage(img))
//            return false;
//
//        Bitmasks.CreateMask(&LoadInto, img);
//        return true;
//    }
//
//    Vector2f GetSpriteCenter(const Sprite& Object)
//    {
//        FloatRect AABB = Object.getGlobalBounds();
//        return Vector2f(AABB.left + AABB.width / 2.f, AABB.top + AABB.height / 2.f);
//    }
//
//    Vector2f GetSpriteSize(const Sprite& Object)
//    {
//        IntRect OriginalSize = Object.getTextureRect();
//        Vector2f Scale = Object.getScale();
//        return Vector2f(OriginalSize.width * Scale.x, OriginalSize.height * Scale.y);
//    }
//
//}