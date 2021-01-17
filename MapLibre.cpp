
#include "MapLibre.h"
#include <mbgl/gfx/backend.hpp>
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

JNIEXPORT jbyteArray JNICALL Java_MapLibre_render
        (JNIEnv *env, jobject, jint height, jint width, jdouble pixelRation, jdouble lat, jdouble lon, jdouble zoom) {
    util::RunLoop loop;

    HeadlessFrontend frontend(Size{static_cast<uint32_t>(width), static_cast<uint32_t>(height)}, pixelRation);
    MapObserver mapObserver = MapObserver::nullObserver();

    MapOptions mapOptions;
    mapOptions.withSize(frontend.getSize());
    mapOptions.withMapMode(MapMode::Static);

    ResourceOptions resourceOptions;
    //resourceOptions.withAccessToken("pk.eyJ1IjoiYmNoYXB1aXMiLCJhIjoiY2loNmUycGw0MDAyMnZybTExYzlrcHBoeSJ9.LuJcf0_spqjJ4NkXrYPf4A");
    //resourceOptions.withCachePath("");
    //resourceOptions.withAssetPath("");

    Map map(frontend, mapObserver, mapOptions, resourceOptions);

    LatLng center{lat, lon};
    map.jumpTo(CameraOptions().withCenter(center).withZoom(zoom));

    map.getStyle().loadURL("https://tiles.baremaps.com/style.json");

    auto result = frontend.render(map);
    auto buf = encodePNG(result.image);

    jbyte *png = (jbyte *) std::malloc(sizeof(jbyte) * buf.size());
    std::copy(buf.begin(), buf.end() - 1, png);

    jbyteArray ret = env->NewByteArray(buf.size());
    env->SetByteArrayRegion(ret, 0, buf.size(), png);

    return ret;
}
