#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class ShaderNode : public cocos2d::Node {
public:

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(ShaderNode);

    // 関数宣言
    void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags);
    void onDraw(const cocos2d::Mat4& transform, uint32_t flags);

    // 変数宣言
    cocos2d::GLProgram* m_pProgram;

    int uniform_sampler;
    int uniform_wvp_matrix;
    int uniform_center;
    int uniform_size_div2;
    int uniform_time;
    float m_time;

    cocos2d::Texture2D* m_pTexture;

    int counter;

    // カスタムコマンド
    cocos2d::CustomCommand _customCommand;

    cocos2d::Mat4 matWVP;

    cocos2d::Vec3 m_pos[6];
    cocos2d::Vec4 m_color[6];
    cocos2d::Vec2 m_uv[6];
};

#endif // __HELLOWORLD_SCENE_H__