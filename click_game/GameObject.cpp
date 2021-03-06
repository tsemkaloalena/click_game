#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <map>
#include <fstream>
#include <ctime>
#include "GameObject.h"
using namespace sf;

GameObject::MaskOfGameObject::MaskOfGameObject() {
    std::map<const Texture*, int*>::const_iterator end = Bitmasks.end();
    for (std::map<const Texture*, int*>::const_iterator iter = Bitmasks.begin(); iter != end; iter++) {
        delete[] iter->second;
    }
}
int GameObject::MaskOfGameObject::GetPixel(const int* mask, const Texture* texture, int x, int y) {
    if (x > texture->getSize().x || y > texture->getSize().y) {
        return 0;
    }
    return mask[x + y * texture->getSize().x];
}

int* GameObject::MaskOfGameObject::GetMask(const Texture* texture) {
    int* mask;
    std::map<const Texture*, int*>::iterator it = Bitmasks.find(texture);
    if (it == Bitmasks.end()) {
        Image img = texture->copyToImage();
        mask = CreateMask(texture, img);
    }
    else {
        mask = it->second;
    }
    return mask;
}

int* GameObject::MaskOfGameObject::CreateMask(const Texture* texture, const Image& img) {
    int* mask = new int[texture->getSize().y * texture->getSize().x];

    for (int y = 0; y < texture->getSize().y; y++)
    {
        for (int x = 0; x < texture->getSize().x; x++) {
            mask[x + y * texture->getSize().x] = img.getPixel(x, y).a;
        }
    }

    Bitmasks.insert(std::pair<const Texture*, int*>(texture, mask));

    return mask;
}

GameObject::MaskOfGameObject Bitmasks;

bool GameObject::CollisionTest(const Sprite& Object1, const Sprite& Object2, int AlphaLimit) {
    FloatRect Intersection;
    if (Object1.getGlobalBounds().intersects(Object2.getGlobalBounds(), Intersection)) {
        IntRect Rectangle1 = Object1.getTextureRect();
        IntRect Rectangle2 = Object2.getTextureRect();

        int* mask1 = Bitmasks.GetMask(Object1.getTexture());
        int* mask2 = Bitmasks.GetMask(Object2.getTexture());

        // Loop through our pixels
        for (int i = Intersection.left; i < Intersection.left + Intersection.width; i++) {
            for (int j = Intersection.top; j < Intersection.top + Intersection.height; j++) {

                Vector2f vector1 = Object1.getInverseTransform().transformPoint(i, j);
                Vector2f vector2 = Object2.getInverseTransform().transformPoint(i, j);

                // Make sure pixels fall within the sprite's subrect
                if (vector1.x > 0 && vector2.y > 0 && vector2.x > 0 && vector2.y > 0 &&
                    vector1.x < Rectangle1.width && vector1.y < Rectangle1.height &&
                    vector2.x < Rectangle2.width && vector2.y < Rectangle2.height) {

                    if (Bitmasks.GetPixel(mask1, Object1.getTexture(), (int)(vector1.x) + Rectangle1.left, (int)(vector1.y) + Rectangle1.top) > AlphaLimit &&
                        Bitmasks.GetPixel(mask2, Object2.getTexture(), (int)(vector2.x) + Rectangle2.left, (int)(vector2.y) + Rectangle2.top) > AlphaLimit)
                        return true;

                }
            }
        }
    }
    return false;
}

bool GameObject::CollisionsTest(const Sprite& Object, const Sprite* Objects) {
    for (int i = 0; i < sizeof(Objects); i++) {
        if (CollisionTest(Object, Objects[i])) {
            return true;
        }
    }
    return false;
}

bool GameObject::MaskedTexture(Texture& LoadInto, const std::string& Filename)
{
    Image img;
    if (!img.loadFromFile(Filename))
        return false;
    if (!LoadInto.loadFromImage(img))
        return false;

    Bitmasks.CreateMask(&LoadInto, img);
    return true;
}

bool GameObject::CursorCheck(int x, int y, Text Object) {
    if (x > Object.getPosition().x and x < Object.getPosition().x + Object.getLocalBounds().width) {
        if (y > Object.getPosition().y and y < Object.getPosition().y + Object.getLocalBounds().height) {
            return true;
        }
    }
    return false;
}
void GameObject::ScoreRecord(int score) {
    std::ofstream fout("./data/scorelist.txt", std::ios::app);
    struct tm* tim;
    time_t tt = time(NULL);
    tim = localtime(&tt);
    fout << tim->tm_mday << "." << tim->tm_mon + 1 << "." << tim->tm_year + 1900 << " " << tim->tm_hour << ":" << tim->tm_min << " - ";
    fout << score << " points" << std::endl;
    fout.close();

    std::fstream data;
    int t;
    data.open("./data/best_result.txt", std::ios::in);
    data >> t;
    data.close();
    if (score > t) {
        std::ofstream fout("./data/best_result.txt", std::ios::out);
        fout << score;
        fout.close();
    }

}
std::string GameObject::getScoreList(int &start, int k) {
    std::vector<std::string> text;
    std::string str_text = "";
    int i = 0;
    std::string line;
    std::fstream data;
    data.open("./data/scorelist.txt", std::ios::in);
    while (getline(data, line)) {
        text.push_back(line);
    }
    if (text.size() < k) {
        k = text.size();
    }
    if (text.size() - start < k) {
        start = text.size() - k;
    }
    for (int i = start; i < k + start; i++) {
        str_text += text[i] + "\n";
    }
    return str_text;
}

std::string GameObject::getBestResult() {
    std::string m;
    std::string line;
    std::fstream data;
    data.open("./data/best_result.txt", std::ios::in);
    data >> m;
    data.close();
    return m;
}
