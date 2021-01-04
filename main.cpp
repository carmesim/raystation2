#include "light.h"
#include "ray.h"
#include "sphere.h"
#include "vector.h"
#include <cmath>
#include <cstdlib>
#ifndef _EE
#include <fstream>
#include <iostream>
#endif
#include <cstdint>
#include <unistd.h>
#include <vector>

#ifdef _EE
#include <gsKit.h>

struct gsGlobal *gs;
struct gsTexture texBuffer;
#endif

constexpr Vec3f origin {0, 0, 0};

static constexpr size_t width = 320;
static constexpr size_t height = 240;

#ifdef _EE
std::vector<u32> ps2Framebuffer;
#else
using u32 = uint32_t;
#endif

void render(const std::vector<Sphere> &spheres, const std::vector<Light>&lights,
            u32 *ps2Fb = nullptr) {
    const float fov      = static_cast<float>(M_PI)/2.f;
#ifndef _EE
    std::vector<Vec3f> framebuffer;
    framebuffer.resize(width*height);
    (void)(ps2Fb);
#endif

    for (size_t j = 0; j<height; j++) {
        for (size_t i = 0; i<width; i++) {
            float x =  (2.f*(i + 0.5f)/width  - 1)*tanf(fov/2.f)*width/height;
            float y = -(2.f*(j + 0.5f)/height - 1)*tanf(fov/2.f);
            Vec3f dir = Vec3f(x, y, -1).normalize();
            Ray ray(origin, dir);
#ifdef _EE
            ps2Fb[i + j * width] = ray.cast(spheres, lights).asGsColor();
#else
            framebuffer[i+j*width] = ray.cast(spheres, lights);
#endif
        }
    }

#ifndef _EE
    std::ofstream outStream("out.ppm");
    outStream << "P3\n" << width << ' ' << height << '\n';
    outStream << 65535 << '\n';
    for (size_t line = 0; line < height; line++)
    {
        for (size_t col = 0; col < width; col++)
        {
            uint16_t r = std::max(std::min(framebuffer[line * width + col].x, 1.f), .0f) * 65535;
            uint16_t g = std::max(std::min(framebuffer[line * width + col].y, 1.f), .0f) * 65535;
            uint16_t b = std::max(std::min(framebuffer[line * width + col].z, 1.f), .0f) * 65535;

            outStream << r << ' ' << g << ' ' << b << "  ";
        }
        outStream << '\n';
    }
#endif

    // TODO: save the framebuffer to the PS2's framebuffer
    // Preferably directly, within the loop above.
}

int main() {
#ifdef _EE
    ps2Framebuffer.resize(width * height);
    gs = gsKit_init_global();
    texBuffer.PSM = GS_PSM_CT32;
    texBuffer.Width = width;
    texBuffer.Height = height;
    texBuffer.Vram = gsKit_vram_alloc(gs, gsKit_texture_size(texBuffer.Width, texBuffer.Height, texBuffer.PSM), GSKIT_ALLOC_USERBUFFER);
    gs->DrawOrder = GS_OS_PER;
    gs->Interlace = GS_NONINTERLACED;
    gs->Field = GS_FIELD;
    gs->DrawField = GS_FIELD_EVEN;
    gs->Width = width;
    gs->Height = height;
    gs->PSM = GS_PSM_CT32;
    gs->PSMZ = GS_PSMZ_16S;
    gs->ZBuffering = GS_SETTING_ON;
    dmaKit_init(D_CTRL_RELE_OFF,D_CTRL_MFD_OFF, D_CTRL_STS_UNSPEC,
                D_CTRL_STD_OFF, D_CTRL_RCYC_8, 1 << DMA_CHANNEL_GIF);
    dmaKit_chan_init(DMA_CHANNEL_GIF);
    gsKit_init_screen(gs);
    gsKit_clear(gs, GS_SETREG_RGBAQ(0xFF,0xFF,0xFF,0x00,0x00)); // Clear with white
    gsKit_mode_switch(gs, GS_PERSISTENT);
    gsKit_set_test(gs, GS_ZTEST_OFF);
    gsKit_queue_exec(gs);
    gsKit_sync_flip(gs);
#endif

    Material ivory(
                  Vec3f(0.4, 0.4, 0.3), // Color
                  Vec3f(0.6,  0.3, 0),  // Albedo
                  50.);                 // Specular exponent
    Material red_rubber (
                  Vec3f(0.3, 0.1, 0.1), // Color
                  Vec3f(0.9,  0.1, 0),  // Albedo
                  10.);                 // Specular exponent

    std::vector<Light> lights;
    lights.emplace_back(Vec3f(-20, 20,  20), 1.5);
    lights.emplace_back(Vec3f( 30, 50, -25), 1.8);
    lights.emplace_back(Vec3f( 30, 20,  30), 1.7);

    std::vector<Sphere> spheres;
    spheres.emplace_back(Vec3f(-3,    0,   -16), 2,      ivory);
    spheres.emplace_back(Vec3f(-1.0, -1.5, -12), 2, red_rubber);
    spheres.emplace_back(Vec3f( 1.5, -0.5, -18), 3, red_rubber);
    spheres.emplace_back(Vec3f( 7,    5,   -18), 4,      ivory);

    render(spheres, lights
#ifdef _EE
           , &ps2Framebuffer[0]
#endif
           );
#ifdef _EE
    gsKit_clear(gs, GS_SETREG_RGBAQ(0x00,0xAA,0x00,0x00,0x00)); // Clear with green
    texBuffer.Mem = &ps2Framebuffer[0];
    gsKit_texture_upload(gs, &texBuffer);
    gsKit_prim_sprite_texture(gs, &texBuffer,
        0,                                     /* X1 */
        0,                                     /* Y1 */
        0,                                     /* U1 */
        0,                                     /* V1 */
        gs->Width,                                 /* X2 */ // Stretch to screen width
        gs->Height,                                /* Y2 */ // Stretch to screen height
        texBuffer.Width,                       /* U2 */
        texBuffer.Height,                      /* V2 */
        2,                                     /* Z  */
        GS_SETREG_RGBA(0x80, 0x80, 0x80, 0x00) /* RGBA */
    );
    gsKit_queue_exec(gs);
    gsKit_sync_flip(gs);
    while (1)
    {

    }
#endif

    return 0;
}
