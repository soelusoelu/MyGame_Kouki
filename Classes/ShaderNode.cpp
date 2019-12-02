#include "ShaderNode.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool ShaderNode::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// 子ノードがいれば、子ノードも一緒に変形する
	//Sprite* spr = Sprite::create("HelloWorld.png");
	//this->addChild(spr);
	//spr->setPosition(Vec2(200, 0));

	GLenum error;

	m_pProgram = new GLProgram;
	m_pProgram->initWithFilenames("shaders/flower.vsh", "shaders/flower.fsh");

	m_pProgram->bindAttribLocation("a_position", GLProgram::VERTEX_ATTRIB_POSITION);
	m_pProgram->bindAttribLocation("a_color", GLProgram::VERTEX_ATTRIB_COLOR);
	//m_pProgram->bindAttribLocation("a_texCoord", GLProgram::VERTEX_ATTRIB_TEX_COORD);

	m_pProgram->link();

	m_pProgram->updateUniforms();

	//uniform_sampler = glGetUniformLocation(m_pProgram->getProgram(), "sampler");
	uniform_wvp_matrix = glGetUniformLocation(m_pProgram->getProgram(), "u_wvp_matrix");
    uniform_center = glGetUniformLocation(m_pProgram->getProgram(), "center");
    uniform_size = glGetUniformLocation(m_pProgram->getProgram(), "size_div2");

	m_pTexture = Director::getInstance()->getTextureCache()->addImage("texture.jpg");

	// 背景色の指定
	Director::getInstance()->setClearColor(Color4F(0, 1, 0, 0));

	counter = 0;

    return true;
}

void ShaderNode::draw(Renderer* renderer, const Mat4& transform, uint32_t flags)
{
	// onDrawをCustomCommandを利用して、描画コマンドとして
	// レンダラーに予約
	_customCommand.init(_globalZOrder, transform, flags);
	_customCommand.func = CC_CALLBACK_0(ShaderNode::onDraw, this, transform, flags);
	renderer->addCommand(&_customCommand);

	counter++;

	Size size = getContentSize();

	// 三角形１つめ
	m_pos[0] = Vec3(-size.width / 2.0f, -size.height / 2.0f, 0);
	m_pos[1] = Vec3(-size.width / 2.0f,  size.height / 2.0f, 0);
	m_pos[2] = Vec3( size.width / 2.0f, -size.height / 2.0f, 0);
	m_pos[3] = Vec3( size.width / 2.0f,  size.height / 2.0f, 0);

	m_color[0] = Vec4(_realColor.r / 255.0f, _realColor.g / 255.0f, _realColor.b / 255.0f, _realOpacity / 255.0f);
	m_color[1] = Vec4(_realColor.r / 255.0f, _realColor.g / 255.0f, _realColor.b / 255.0f, _realOpacity / 255.0f);
	m_color[2] = Vec4(_realColor.r / 255.0f, _realColor.g / 255.0f, _realColor.b / 255.0f, _realOpacity / 255.0f);
	m_color[3] = Vec4(_realColor.r / 255.0f, _realColor.g / 255.0f, _realColor.b / 255.0f, _realOpacity / 255.0f);

	m_uv[0] = Vec2(0, 1);
	m_uv[1] = Vec2(0, 0);
	m_uv[2] = Vec2(1, 1);
	m_uv[3] = Vec2(1, 0);

	// ワールドビュープロジェクション行列の生成
	Mat4 matProjection;

	// ２Ｄの座標系に変換
	matProjection = _director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
	matWVP = matProjection * transform;
}

void ShaderNode::onDraw(const Mat4& transform, uint32_t /*flags*/)
{
	// 半透明
	GL::blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR | GL::VERTEX_ATTRIB_FLAG_TEX_COORD);
	GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);

	m_pProgram->use();

	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 3, GL_FLOAT, GL_FALSE, 0, m_pos);
	glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, m_color);
	//glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, m_uv);

	//glUniform1i(uniform_sampler, 0);
	//GL::bindTexture2D(m_pTexture->getName());

	glUniformMatrix4fv(uniform_wvp_matrix, 1, GL_FALSE, matWVP.m);
    Vec2 pos = getPosition();
    glUniform2f(uniform_center, pos.x, pos.y);
    Vec2 size = getContentSize();
    glUniform2f(uniform_size, size.x, size.y);

	// ４頂点での描画
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}


void ShaderNode::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}