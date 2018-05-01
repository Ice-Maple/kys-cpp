#pragma once
#include "Engine.h"
#include <map>
#include <vector>

//ͼƬ�����࣬���ִ��ͱ��������
//һ�����������԰���10���������������������ģ�⶯̬Ч��
//ÿ��ͼƬ��ƫ��������int16[n][2]�����棬��Ҫע����ǣ�UIԪ��ʹ�õ�ͼƬ�����ƫ�ƶ���Ϊ0�����������귶Χʱ����һЩ���⣬ʹ������Ҳ�Ƚ��鷳

class TextureManager
{
private:
    TextureManager();
    virtual ~TextureManager();
    static TextureManager texture_manager_;
    std::string path_ = "../game/resource/";

    enum
    {
        SUB_TEXTURE_COUNT = 10,
    };

    struct Texture
    {
        BP_Texture* tex[SUB_TEXTURE_COUNT];
        int w = 0, h = 0, dx = 0, dy = 0;
        bool loaded = false;
        int count = 1;
        Texture()
        {
            for (int i = 0; i < SUB_TEXTURE_COUNT; tex[i++] = nullptr);
        }
        ~Texture() { destory(); }
        void setTex(BP_Texture* t)
        {
            destory();
            tex[0] = t;
            count = 1;
            loaded = true;
            Engine::getInstance()->queryTexture(t, &w, &h);
        }
        BP_Texture* getTexture(int i = 0) { return tex[i]; }
    private:
        void destory()
        {
            for (int i = 0; i < SUB_TEXTURE_COUNT; i++)
            {
                if (tex[i])
                {
                    Engine::destroyTexture(tex[i]);
                }
            }
        }
    };

public:
    enum Type
    {
        MainMap = 0,
        Scene,
        Battle,
        Cloud,
        MaxType
    };

    std::map<const std::string, std::vector<Texture*>> map_;

    static TextureManager* getInstance() { return &texture_manager_; }

    void renderTexture(Texture* tex, BP_Rect r,
        BP_Color c = { 255, 255, 255, 255 }, uint8_t alpha = 255);
    void renderTexture(const std::string& path, int num, BP_Rect r,
        BP_Color c = { 255, 255, 255, 255 }, uint8_t alpha = 255);

    void renderTexture(Texture* tex, int x, int y,
        BP_Color c = { 255, 255, 255, 255 }, uint8_t alpha = 255, double zoom_x = 1, double zoom_y = 1);
    void renderTexture(const std::string& path, int num, int x, int y,
        BP_Color c = { 255, 255, 255, 255 }, uint8_t alpha = 255, double zoom_x = 1, double zoom_y = 1);

    Texture* loadTexture(const std::string& path, int num);
    int getTextureGroupCount(const std::string& path);
	void TextureManager::loadBigPic(const std::string& path, int picnum, int x, int y);
private:
    void initialTextureGroup(const std::string& path, bool load_all = false);
    void loadTexture2(const std::string& path, int num, Texture* t);
};

