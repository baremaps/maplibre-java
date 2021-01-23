
#include "com_baremaps_maplibre_MapLibre.h"
#include <mbgl/gfx/headless_backend.hpp>
#include <mbgl/gfx/headless_frontend.hpp>
#include <mbgl/map/map.hpp>
#include <mbgl/map/map_options.hpp>
#include <mbgl/style/style.hpp>
#include <mbgl/util/default_styles.hpp>
#include <mbgl/util/image.hpp>
#include <mbgl/layermanager/layer_manager.hpp>
#include <mbgl/util/run_loop.hpp>

#include <csignal>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <array>

using namespace mbgl;

// https://github.com/kildevaeld/mbglc/blob/master/src/mbglc.cpp
// https://dhilst.github.io/2016/10/15/JNI-CPP.html

struct maplibre
{
    std::unique_ptr<HeadlessFrontend> frontend;
    std::unique_ptr<mbgl::Map> map;
};

JNIEXPORT jlong JNICALL Java_com_baremaps_maplibre_MapLibre_startRunLoop
        (JNIEnv *, jclass) {
    util::RunLoop *loop = new util::RunLoop();
    return reinterpret_cast<jlong>(loop);
}

JNIEXPORT jlong JNICALL Java_com_baremaps_maplibre_MapLibre_createMapLibre
        (JNIEnv *, jobject, jdouble width, jdouble height, jdouble pixelRatio) {
    auto frontend = std::make_unique<HeadlessFrontend>(Size{static_cast<uint32_t>(width), static_cast<uint32_t>(height)}, pixelRatio);
    auto map = std::make_unique<Map>(*frontend, MapObserver::nullObserver(), MapOptions().withSize(frontend->getSize()).withMapMode(MapMode::Static), ResourceOptions());
    auto ml = new maplibre{std::move(frontend), std::move(map)};
    return reinterpret_cast<jlong>(ml);
}

static maplibre *getMapLibre(JNIEnv *env, jobject self) {
    jclass cls = env->GetObjectClass(self);
    if (!cls)
        env->FatalError("GetObjectClass failed");

    jfieldID mapLibrePointerID = env->GetFieldID(cls, "mapLibrePointer", "J");
    if (!mapLibrePointerID)
        env->FatalError("GetFieldID failed");

    jlong mapLibrePointer = env->GetLongField(self, mapLibrePointerID);
    return reinterpret_cast<maplibre *>(mapLibrePointer);
}

JNIEXPORT void JNICALL Java_com_baremaps_maplibre_MapLibre_loadUrlStyle
        (JNIEnv *env, jobject self, jstring url) {
    maplibre* mapLibre = getMapLibre(env, self);
    std::string urlStr(std::string(env->GetStringUTFChars(url, NULL)));
    mapLibre->map->getStyle().loadURL(urlStr);
}

JNIEXPORT void JNICALL Java_com_baremaps_maplibre_MapLibre_setPosition
        (JNIEnv *env, jobject self, jdouble latitude, jdouble longitude, jint zoom) {
    maplibre* mapLibre = getMapLibre(env, self);
    LatLng center{latitude, longitude};
    mapLibre->map->jumpTo(CameraOptions().withCenter(center).withZoom(zoom));
}

JNIEXPORT void JNICALL Java_com_baremaps_maplibre_MapLibre_setCenter
        (JNIEnv *env, jobject self, jdouble latitude, jdouble longitude) {
    maplibre* mapLibre = getMapLibre(env, self);
    LatLng center{latitude, longitude};
    mapLibre->map->jumpTo(CameraOptions().withCenter(center));
}

JNIEXPORT void JNICALL Java_com_baremaps_maplibre_MapLibre_setZoom
        (JNIEnv *env, jobject self, jint zoom) {
    maplibre* mapLibre = getMapLibre(env, self);
    mapLibre->map->jumpTo(CameraOptions().withZoom(zoom));
}

JNIEXPORT jbyteArray JNICALL Java_com_baremaps_maplibre_MapLibre_render
        (JNIEnv *env, jobject self) {
    maplibre* mapLibre = getMapLibre(env, self);

    auto result = mapLibre->frontend->render(*(mapLibre->map));
    auto buf = encodePNG(result.image);

    jbyte *png = (jbyte *) std::malloc(sizeof(jbyte) * buf.size());
    std::copy(buf.begin(), buf.end() - 1, png);

    jbyteArray ret = env->NewByteArray(buf.size());
    env->SetByteArrayRegion(ret, 0, buf.size(), png);

    return ret;
}
