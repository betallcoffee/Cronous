EXECUTABLE = Cronous

INCLUDES = -I.. -I../Classes \
		   -I../Classes/Scenes \
		   -I../Classes/Storage \
		   -I../Classes/Network \
		   -I../Classes/Util
		   
#INCLUDES += -I../libs/jsoncpp/include/json/

SOURCES = main.cpp \
        ../Classes/AppDelegate.cpp \
        ../Classes/Scenes/FightLayer.cpp \
		../Classes/Scenes/HomeScene.cpp \
		../Classes/Scenes/IntroAnimateScene.cpp \
		../Classes/Scenes/LevelMapLayer.cpp \
		../Classes/Scenes/LoadingLayer.cpp \
		../Classes/Scenes/LoginScene.cpp \
		../Classes/Scenes/PersonalLayer.cpp \
		../Classes/Scenes/RolesScene.cpp \
		../Classes/Scenes/StartScene.cpp \
		../Classes/Scenes/StatusBarLayer.cpp

#SOURCES += ../Classes/Network/ETSocket.cpp \
#		   ../Classes/Network/ETSocketClient.cpp \
#		   ../Classes/Network/ETSocketManager.cpp
#
#SOURCES += ../Classes/Util/ETBuffer.cpp \
#		   ../Classes/Util/ETMessage.cpp \
#		   ../Classes/Util/ETMessageQueue.cpp


COCOS_ROOT = ../..
include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

INCLUDES += -I$(COCOS_ROOT)/CocosDenshion/include/ \
            -I$(COCOS_ROOT)/extensions/ \
            -I$(COCOS_ROOT)/external/chipmunk/include/chipmunk/
            
SHAREDLIBS += -lcocos2d -lcocosdenshion -l extension
COCOS_LIBS = $(LIB_DIR)/libcocos2d.so \

$(TARGET): $(OBJECTS) $(STATICLIBS) $(COCOS_LIBS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_LINK)$(CXX) $(CXXFLAGS) $(OBJECTS) -o $@ $(SHAREDLIBS) $(STATICLIBS)

$(OBJ_DIR)/%.o: %.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@
