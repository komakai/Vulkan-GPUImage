#pragma once

#include "VideoRenderer.h"

#include <memory>
#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

class VideoRendererContext
{
public:
	struct jni_fields_t
	{
		jfieldID context;
	};

	VideoRendererContext(int type);
	~VideoRendererContext() = default;

    void init(ANativeWindow* window, size_t width, size_t height,AAssetManager* manager);
	void render();
	void draw(uint8_t *buffer, size_t length, size_t width, size_t height, int rotation);
	void setParameters(uint32_t params);
	void setProgress(uint32_t params);
	uint32_t getParameters();

	static void createContext(JNIEnv *env, jobject obj, jint type);
	static void storeContext(JNIEnv *env, jobject obj, VideoRendererContext *context);
	static void deleteContext(JNIEnv *env, jobject obj);
	static VideoRendererContext* getContext(JNIEnv *env, jobject obj);


private:
    std::unique_ptr<VideoRenderer> m_pVideoRenderer;

	static jni_fields_t jni_fields;

};
