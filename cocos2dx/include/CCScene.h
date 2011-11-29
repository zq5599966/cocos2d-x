/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CCSCENE_H__
#define __CCSCENE_H__

#include "CCNode.h"

namespace   cocos2d {

typedef enum
{
    ccNormalScene     = 1 << 0,
    ccTransitionScene = 1 << 1,
} ccSceneFlag;

/** @brief CCScene is a subclass of CCNode that is used only as an abstract concept.

CCScene an CCNode are almost identical with the difference that CCScene has it's
anchor point (by default) at the center of the screen.

For the moment CCScene has no other logic than that, but in future releases it might have
additional logic.

It is a good practice to use and CCScene as the parent of all your nodes.
*/
class CC_DLL CCScene : public CCNode
{
public:
    CCScene();
    virtual ~CCScene();
    bool init();
    static CCScene *node(void);
    inline ccSceneFlag getSceneType(void) {
        return m_eSceneType;
    }
    
#if LUA_ENGINE
    virtual void onEnter();
    virtual void onExit();

    void registerScriptEventsHandler(int functionRefID);
    void unregisterScriptEventsHandler(void);
#endif // LUA_ENGINE

protected:
    ccSceneFlag m_eSceneType;

#if LUA_ENGINE
    int m_eventsFunctionRefID;
#endif
};

}//namespace   cocos2d

// for the subclass of CCScene, each has to implement the static "node" method
#define SCENE_NODE_FUNC(scene) \
static scene* node() \
{ \
	scene *pRet = new scene(); \
	if (pRet && pRet->init()) \
	{ \
		pRet->autorelease(); \
		return pRet; \
	} \
	else \
	{ \
		delete pRet; \
		pRet = NULL; \
		return NULL; \
	} \
};

#define SCENE_FUNC_PARAM(__TYPE__,__PARAMTYPE__,__PARAM__) \
	static cocos2d::CCScene* node(__PARAMTYPE__ __PARAM__) \
{ \
	cocos2d::CCScene * scene = NULL; \
	do  \
{ \
	scene = cocos2d::CCScene::node(); \
	CC_BREAK_IF(! scene); \
	__TYPE__ *layer = __TYPE__::node(__PARAM__); \
	CC_BREAK_IF(! layer); \
	scene->addChild(layer); \
} while (0); \
	return scene; \
};



#endif // __CCSCENE_H__
